#ifndef ANTWORLDLOGIC_HPP
#define ANTWORLDLOGIC_HPP

#include "ant.h"
#include "Colony.h"
#include "food.h"

#define WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP 100

class AntWorldLogic
{
public:
    AntWorldLogic();

    void add_colony(std::vector<Colony>& worldColonies, double& colonyX, double& colonyY);
    void add_food(std::vector<Food>& worldFood, double& newFoodX, double& newFoodY, int& newFoodAmount);
    void reset_world(std::vector<Colony>& worldColonies, int& totalWorldAnts, std::vector<Food>& worldFood, int (&foodPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP], int (&colonyPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP]);

    virtual void update_world(std::vector<Colony>& worldColonies, std::vector<Food>& worldFood, int (&foodPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP], int (&colonyPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP], int& totalWorldAnts);

    void check_world_ants_location(std::vector<Colony>& worldColonies, double sizeOfWorld, int& totalWorldAnts);
    void check_world_ants_and_food(std::vector<Colony>& worldColonies, std::vector<Food>& worldFood, double checkDistance);
    void check_world_ants_and_colonies(std::vector<Colony>& worldColonies, double checkSize);
    void check_pheromone_trail(std::vector<Colony>& worldColonies, std::vector<Food> &worldFood, int (&foodPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP], int (&colonyPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP]);
    void update_world_colonies(std::vector<Colony>& worldColonies);

    int get_number_of_colonies(std::vector<Colony>& worldColonies);
    int generate_random_int(int numFoodInWorld);

    double get_strongest_pheromone_direction(std::vector<Colony>& worldColonies, std::vector<Food>& worldFood, Ant& currentAnt, int& xLocation, int& yLocation, bool hasFood, int (&foodPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP], int (&colonyPheromoneArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP], double originalAngle);
    double get_size_of_world(int (&worldArray)[WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP][WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP]);
    double generate_random_double();

    int pheromoneMaxStrength{WORLD_SIZE_DEFINED_IN_ANTWORLDLOGICHPP*(12/10)};
    int checkColonyDistance{5};
    int checkFoodDistance{3};


protected:
    double frameoffset{2};
    double addNum{1};
};

#endif // ANTWORLDLOGIC_HPP
