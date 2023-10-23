#include "ColonyLogic.hpp"

ColonyLogic::ColonyLogic()
{
}

void ColonyLogic::reset_number_of_ants(int& currentNumberOfAnts)
{
    currentNumberOfAnts = 0;
}

void ColonyLogic::update_colony(int& amountOfFoodInColony, int& numberOfAnts, std::vector<Ant>& colonyAnts, std::vector<double>& colonyLocation)
{
    while(amountOfFoodInColony>numberOfAnts)
    {
        amountOfFoodInColony-=1;
        add_ant_to_colony(colonyAnts, numberOfAnts, colonyLocation[0], colonyLocation[1]);
    }
    numberOfAnts = static_cast<int>(colonyAnts.size());
}

void ColonyLogic::add_ant_to_colony(std::vector<Ant>& colonyAnts, int& numberOfAnts, double newAntX, double newAntY)
{
    Ant newAnt{newAntX, newAntY, generate_random_double()};
    colonyAnts.push_back(newAnt);
    numberOfAnts++;
}

void ColonyLogic::add_ant_to_colony(std::vector<Ant> &colonyAnts, int& numberOfAnts, double newAntX, double newAntY, double setAngle)
{
    Ant newAnt{newAntX, newAntY, generate_non_random_double(setAngle)};
    colonyAnts.push_back(newAnt);
    numberOfAnts++;
}

void ColonyLogic::add_food_to_colony(int& amountOfFoodInColony)
{
    amountOfFoodInColony++;
}

double ColonyLogic::generate_random_double()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, maxRandomAngle);
    return dis(gen);
}

double ColonyLogic::generate_non_random_double(double returnDouble)
{
    return returnDouble;
}
