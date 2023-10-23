#include "Colony.h"

void Colony::update_colony()
{
    colonyLogic.update_colony(amountOfFoodInColony, numberOfAnts, colonyAnts, colonyLocation);
}

void Colony::add_food_to_colony()
{
    colonyLogic.add_food_to_colony(amountOfFoodInColony);
}

void Colony::add_ant(double antPositionX, double antPositionY)
{
    colonyLogic.add_ant_to_colony(colonyAnts, numberOfAnts, antPositionX, antPositionY);
}

void Colony::add_ant(double antPositionX, double antPositionY, double antAngle)
{
    colonyLogic.add_ant_to_colony(colonyAnts, numberOfAnts, antPositionX, antPositionY, antAngle);
}

std::vector<double> Colony::get_colony_location()
{
    return colonyLocation;
}

std::vector<Ant> Colony::get_colony_ants()
{
    return colonyAnts;
}

int Colony::get_amount_of_food_in_colony()
{
    return amountOfFoodInColony;
}

int Colony::get_number_of_ants()
{
    return numberOfAnts;
}

void Colony::reset_number_of_ants()
{
    colonyLogic.reset_number_of_ants(numberOfAnts);
}
