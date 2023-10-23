#ifndef ANTWORLD_H
#define ANTWORLD_H

#include "Colony.h"
#include "food.h"
#include "AntWorldLogic.hpp"

class AntWorld
{
public:
    AntWorld();

    void update_world();
    void add_food(double foodX, double foodY);
    void add_colony(double colonyX, double colonyY);
    void add_colony(double colonyX, double colonyY, int foodAmount);
    void reset_world();

    int get_number_of_colonies();
    double get_size_of_world();
    int get_total_world_ants();

    std::vector<Colony> get_colonies();
    std::vector<Food> get_food();
    std::vector<Colony> worldColonies{};

    int colonyPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP] = {0};
    int foodPheromoneArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP] = {0};

    AntWorldLogic antWorldLogic{};
    int totalWorldAnts{0};
    int pheromoneMaxStrength{WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP*(12/10)};
    std::vector<Food> worldFood{};

protected:
    int worldArray[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP];
};


#endif // ANTWORLD_H
