#ifndef COLONYLOGIC_HPP
#define COLONYLOGIC_HPP

#include "ant.h"

class ColonyLogic
{
public:
    ColonyLogic();

    void reset_number_of_ants(int& currentNumberOfAnts);
    void update_colony(int& amountOfFoodInColony, int& numberOfAnts, std::vector<Ant>& colonyAnts, std::vector<double>& colonyLocation);
    void add_ant_to_colony(std::vector<Ant>& colonyAnts, int& numberOfAnts, double newAntX, double newAntY);
    void add_ant_to_colony(std::vector<Ant>& colonyAnts, int& numberOfAnts, double newAntX, double newAntY, double setAngle);
    void add_food_to_colony(int& amountOfFoodInColony);

    double generate_random_double();
    double generate_non_random_double(double returnDouble);
    double maxRandomAngle{360};
};

#endif // COLONYLOGIC_HPP
