#include "AntWorldLogic.hpp"

AntWorldLogic::AntWorldLogic()
{
}

double PheromoneAngleAlgorithm(double angle)
{
    if(angle<0)
    {
        angle+=360;
    }
    angle-=90;
    if(angle<0)
    {
        angle+=360;
    }
    angle = 360-angle;

    return angle;
}

void AntWorldLogic::add_colony(std::vector<Colony>& worldColonies, double& colonyX, double& colonyY)
{
    Colony newWorldColony{colonyX, colonyY};
    worldColonies.push_back(newWorldColony);
}

void AntWorldLogic::add_food(std::vector<Food>& worldFood, double& newFoodX, double& newFoodY, int& newFoodAmount)
{
    Food newWorldFood{newFoodX, newFoodY, newFoodAmount};
    worldFood.push_back(newWorldFood);
}

void AntWorldLogic::reset_world(std::vector<Colony>& worldColonies, int& totalWorldAnts, std::vector<Food>& worldFood, int (&foodPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP], int (&colonyPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP])
{
    for(int i = 0; i < worldColonies.size(); i++)
    {
        worldColonies.at(i).colonyAnts.clear();
        worldColonies.at(i).reset_number_of_ants();
    }
    totalWorldAnts = 0;

    worldColonies.clear();
    worldFood.clear();

    size_t resetSize{static_cast<size_t>(get_size_of_world(foodPheromoneArray))};

    memset(foodPheromoneArray, 0, sizeof(foodPheromoneArray[0][0]) * resetSize * resetSize);
    memset(colonyPheromoneArray, 0, sizeof(colonyPheromoneArray[0][0]) * resetSize * resetSize);
}

int AntWorldLogic::get_number_of_colonies(std::vector<Colony>& worldColonies)
{
    return static_cast<int>(worldColonies.size());
}

void AntWorldLogic::update_world(std::vector<Colony>& worldColonies, std::vector<Food>& worldFood, int (&foodPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP], int (&colonyPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP], int& totalWorldAnts)
{
    totalWorldAnts = 0;

    check_world_ants_location(worldColonies, get_size_of_world(foodPheromoneArray), totalWorldAnts);

    check_world_ants_and_food(worldColonies, worldFood, checkFoodDistance);

    check_world_ants_and_colonies(worldColonies, checkColonyDistance);

    check_pheromone_trail(worldColonies, worldFood, foodPheromoneArray, colonyPheromoneArray);

    update_world_colonies(worldColonies);
}

void AntWorldLogic::check_world_ants_location(std::vector<Colony>& worldColonies, double sizeOfWorld, int& totalWorldAnts)
{
    totalWorldAnts = 0;
    for(int i = 0; i < worldColonies.size(); i++)
    {
        totalWorldAnts+=worldColonies.at(i).get_number_of_ants();
        for(int j = 0; j < worldColonies.at(i).colonyAnts.size(); j++)
        {
            double currentAntAngle = worldColonies.at(i).colonyAnts.at(j).get_angle();
            std::vector<double> locations = worldColonies.at(i).colonyAnts.at(j).get_position();

            if(worldColonies.at(i).colonyAnts.at(j).get_position()[0] >= sizeOfWorld-frameoffset)
            {
                worldColonies.at(i).colonyAnts.at(j).set_angle(360-currentAntAngle);
                locations[0]=locations[0]-addNum;
            }
            else if(worldColonies.at(i).colonyAnts.at(j).get_position()[1] >= sizeOfWorld-frameoffset)
            {
                worldColonies.at(i).colonyAnts.at(j).set_angle(180-currentAntAngle);
                locations[1]=locations[1]-addNum;
            }
            else if(worldColonies.at(i).colonyAnts.at(j).get_position()[0] <= frameoffset)
            {
                worldColonies.at(i).colonyAnts.at(j).set_angle(360-currentAntAngle);
                locations[0]=locations[0]+addNum;
            }
            else if(worldColonies.at(i).colonyAnts.at(j).get_position()[1] <= frameoffset)
            {
                worldColonies.at(i).colonyAnts.at(j).set_angle(180-currentAntAngle);
                locations[1]=locations[1]+addNum;
            }
            worldColonies.at(i).colonyAnts.at(j).set_position(locations[0], locations[1]);
            worldColonies.at(i).colonyAnts.at(j).update_ant();
        }
    } 
}

void AntWorldLogic::check_world_ants_and_food(std::vector<Colony>& worldColonies, std::vector<Food>& worldFood, double checkDistance)
{
    for(int i = 0; i < worldColonies.size(); i++)
    {
        for(int j = 0; j < worldFood.size(); j++)
        {
            if(worldFood.at(j).get_amount_of_food() > 0)
            {
                double foodX{(worldFood.at(j).get_food_location()[0])};
                double foodY{worldFood.at(j).get_food_location()[1]};

                for(int k = 0; k < worldColonies.at(i).colonyAnts.size(); k++)
                {
                    double antX{worldColonies.at(i).colonyAnts.at(k).get_position()[0]};
                    double antY{worldColonies.at(i).colonyAnts.at(k).get_position()[1]};

                    double distanceBetweenAntAndFood{(sqrt(((antX-foodX)*(antX-foodX))+((antY-foodY)*(antY-foodY))))};

                    if(worldColonies.at(i).colonyAnts.at(k).check_food() == false && (distanceBetweenAntAndFood < checkDistance))
                    {
                        worldFood.at(j).update_food();
                        worldColonies.at(i).colonyAnts.at(k).give_food();
                    }
                }
            }
            else
            {
                worldFood.at(j).set_location(generate_random_double(), generate_random_double());
                worldFood.at(j).set_amount_of_food(10);
            }
        }
    }
}

void AntWorldLogic::check_world_ants_and_colonies(std::vector<Colony>& worldColonies, double checkSize)
{
    for(int i = 0; i < worldColonies.size(); i++)
    {
        double colonyX{worldColonies.at(i).get_colony_location()[0]};
        double colonyY{worldColonies.at(i).get_colony_location()[1]};

        for(int j = 0; j < worldColonies.at(i).colonyAnts.size(); j++)
        {
            double antX{worldColonies.at(i).colonyAnts.at(j).get_position()[0]};
            double antY{worldColonies.at(i).colonyAnts.at(j).get_position()[1]};

            double distanceBetweenAntAndColony{sqrt(((antX-colonyX)*(antX-colonyX))+((antY-colonyY)*(antY-colonyY)))};

            if(worldColonies.at(i).colonyAnts.at(j).check_food() == true && distanceBetweenAntAndColony < checkSize)
            {
                worldColonies.at(i).add_food_to_colony();
                worldColonies.at(i).colonyAnts.at(j).take_food();
                worldColonies.at(i).colonyAnts.at(j).setHasFoundATrail(false);
            }
        }
    }
}

void AntWorldLogic::check_pheromone_trail(std::vector<Colony>& worldColonies, std::vector<Food>& worldFood, int (&foodPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP], int (&colonyPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP])
{
    for(int i = 0; i < worldColonies.size(); i++)
    {
        for(int j = 0; j < worldColonies.at(i).colonyAnts.size(); j++)
        {
            double antX{worldColonies.at(i).colonyAnts.at(j).get_position()[0]};
            double antY{worldColonies.at(i).colonyAnts.at(j).get_position()[1]};

            int antXInt{static_cast<int>(antX)};
            int antYInt{static_cast<int>(antY)};
            double originalAntAngle{worldColonies.at(i).colonyAnts.at(j).get_angle()};

            if(worldColonies.at(i).colonyAnts.at(j).check_food() == true)
            {
                if(colonyPheromoneArray[antXInt][antYInt] > 0 && worldColonies.at(i).colonyAnts.at(j).getHasFoundATrail() == false)
                {
                    worldColonies.at(i).colonyAnts.at(j).set_angle(get_strongest_pheromone_direction(worldColonies, worldFood, worldColonies.at(i).colonyAnts.at(j), antXInt, antYInt, true, foodPheromoneArray, colonyPheromoneArray, originalAntAngle));
                    worldColonies.at(i).colonyAnts.at(j).setHasFoundATrail(true);
                }
                else if(worldColonies.at(i).colonyAnts.at(j).getHasFoundATrail() == true)
                {
                    worldColonies.at(i).colonyAnts.at(j).set_angle(get_strongest_pheromone_direction(worldColonies, worldFood, worldColonies.at(i).colonyAnts.at(j), antXInt, antYInt, true, foodPheromoneArray, colonyPheromoneArray, originalAntAngle));
                }
                foodPheromoneArray[antXInt][antYInt]=pheromoneMaxStrength;
            }
            else
            {
                if(foodPheromoneArray[antXInt][antYInt] > 0 && worldColonies.at(i).colonyAnts.at(j).getHasFoundATrail() == false)
                {
                    worldColonies.at(i).colonyAnts.at(j).set_angle(get_strongest_pheromone_direction(worldColonies, worldFood, worldColonies.at(i).colonyAnts.at(j), antXInt, antYInt, false, foodPheromoneArray, colonyPheromoneArray, originalAntAngle));
                    worldColonies.at(i).colonyAnts.at(j).setHasFoundATrail(true);
                }
                else if(worldColonies.at(i).colonyAnts.at(j).getHasFoundATrail() == true)
                {
                    worldColonies.at(i).colonyAnts.at(j).set_angle(get_strongest_pheromone_direction(worldColonies, worldFood, worldColonies.at(i).colonyAnts.at(j), antXInt, antYInt, false, foodPheromoneArray, colonyPheromoneArray, originalAntAngle));
                }
                colonyPheromoneArray[antXInt][antYInt]=pheromoneMaxStrength;
            }
        }
    }
}

void AntWorldLogic::update_world_colonies(std::vector<Colony> &worldColonies)
{
    for(int i = 0; i < worldColonies.size(); i++)
    {
        worldColonies.at(i).update_colony();
    }
}

double AntWorldLogic::get_strongest_pheromone_direction(std::vector<Colony>& worldColonies, std::vector<Food>& worldFood, Ant& currentAnt,int& xLocation, int& yLocation, bool hasFood, int (&foodPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP], int (&colonyPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP], double originalAngle)
{
    double returnAngle{0};
    int weakestPheromone{10000};
    int xStrongestLocation{0};
    int yStrongestLocation{0};
    int maximumSearchRadius{WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP/8};
    int minimumSearchRadius{1};

    if(hasFood)
    {
//        for(int i = xLocation-maximumSearchRadius; i < xLocation+maximumSearchRadius+1; i++)
//        {
//            for(int j = yLocation-maximumSearchRadius; j < yLocation+maximumSearchRadius+1; j++)
//            {
//                if(abs(xLocation-i)>minimumSearchRadius && abs(yLocation-j)>minimumSearchRadius && colonyPheromoneArray[i][j] < weakestPheromone && colonyPheromoneArray[i][j]>0 && i >= 0 && j >= 0 && i <= get_size_of_world(foodPheromoneArray) && j <= get_size_of_world(foodPheromoneArray))
//                {
//                    xStrongestLocation = i;
//                    yStrongestLocation = j;
//                    weakestPheromone = colonyPheromoneArray[i][j];
//                }
//            }
//        }

        xStrongestLocation = worldColonies.at(0).get_colony_location()[0];
        yStrongestLocation = worldColonies.at(0).get_colony_location()[1];
        weakestPheromone = 1;
    }
    else
    {
        for(int i = xLocation-maximumSearchRadius; i < xLocation+maximumSearchRadius+1; i++)
        {
            for(int j = yLocation-maximumSearchRadius; j < yLocation+maximumSearchRadius+1; j++)
            {
                if(abs(xLocation-i)>minimumSearchRadius && abs(yLocation-j)>minimumSearchRadius && foodPheromoneArray[i][j] < weakestPheromone && foodPheromoneArray[i][j]>0 && i >= 0 && j >= 0 && i <= get_size_of_world(foodPheromoneArray) && j <= get_size_of_world(foodPheromoneArray))
                {
                    xStrongestLocation = i;
                    yStrongestLocation = j;
                    weakestPheromone = foodPheromoneArray[i][j];
                }
            }
        }
//        int foodToGoTo{generate_random_int(worldFood.size())};
//        xStrongestLocation = worldFood.at(foodToGoTo).get_food_location()[0];
//        yStrongestLocation = worldFood.at(foodToGoTo).get_food_location()[1];
//        xStrongestLocation = worldFood.at(0).get_food_location()[0];
//        yStrongestLocation = worldFood.at(0).get_food_location()[1];
//        weakestPheromone = 1;
    }
    if(weakestPheromone == 10000 || xStrongestLocation > WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP-1 || yStrongestLocation < 1)
    {
        currentAnt.setHasFoundATrail(false);
        return originalAngle;
    }

    double y1{-static_cast<double>(yLocation)};
    double y2{-static_cast<double>(yStrongestLocation)};
    double x1{static_cast<double>(xLocation)};
    double x2{static_cast<double>(xStrongestLocation)};

    double angle{atan2((y2-y1),(x2-x1))*(180/PI)};

    returnAngle = PheromoneAngleAlgorithm(angle);

    return returnAngle;
}

double AntWorldLogic::get_size_of_world(int (&worldArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP])
{
    return sqrt(sizeof(worldArray)/ sizeof(int));
}

double AntWorldLogic::generate_random_double()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP-5);
    return dis(gen);
}

int AntWorldLogic::generate_random_int(int numFoodInWorld)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, numFoodInWorld-1);
    return dis(gen);
}
