#include "AntWorld.h"

#define PI 3.14159265

AntWorld::AntWorld()
{
}

void AntWorld::update_world()
{
    antWorldLogic.update_world(worldColonies, worldFood, foodPheromoneArray, colonyPheromoneArray, totalWorldAnts);
}

void AntWorld::add_food(double foodX, double foodY)
{
    Food newWorldFood{foodX, foodY};
    worldFood.push_back(newWorldFood);
}

void AntWorld::add_colony(double colonyX, double colonyY)
{
    Colony newWorldColony{colonyX, colonyY};
    worldColonies.push_back(newWorldColony);
}

void AntWorld::add_colony(double colonyX, double colonyY, int foodAmount)
{
    Colony newWorldColony{colonyX, colonyY, foodAmount};
    worldColonies.push_back(newWorldColony);
}

int AntWorld::get_number_of_colonies()
{
    return static_cast<int>(worldColonies.size());
}

std::vector<Colony> AntWorld::get_colonies()
{
    return worldColonies;
}

std::vector<Food> AntWorld::get_food()
{
    return worldFood;
}

double AntWorld::get_size_of_world()
{
    return sqrt(sizeof(worldArray)/ sizeof(int));
}

int AntWorld::get_total_world_ants()
{
    totalWorldAnts = 0;

    for(int i = 0; i < worldColonies.size(); i++)
    {
        totalWorldAnts+=worldColonies.at(i).get_number_of_ants();
    }

    return totalWorldAnts;
}

void AntWorld::reset_world()
{
    for(int i = 0; i < worldColonies.size(); i++)
    {
        worldColonies.at(i).colonyAnts.clear();
        worldColonies.at(i).reset_number_of_ants();
    }
    totalWorldAnts = 0;

    worldColonies.clear();
    worldFood.clear();

    memset(foodPheromoneArray, 0, sizeof(foodPheromoneArray[0][0]) * WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP * WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP);
    memset(colonyPheromoneArray, 0, sizeof(colonyPheromoneArray[0][0]) * WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP * WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP);
}
