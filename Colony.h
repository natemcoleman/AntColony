#ifndef COLONY_H
#define COLONY_H

#include "ant.h"
#include "ColonyLogic.hpp"

class Colony
{
public:
    Colony(){};
    Colony(double xPosition, double yPosition): colonyLocation{xPosition, yPosition}{};
    Colony(double xPosition, double yPosition, int initialFoodAmount): colonyLocation{xPosition, yPosition}, amountOfFoodInColony(initialFoodAmount){};


    void update_colony();
    void add_food_to_colony();
    void add_ant(double antPositionX, double antPositionY);
    void add_ant(double antPositionX, double antPositionY, double antAngle);
    void reset_number_of_ants();

    int get_number_of_ants();
    int get_amount_of_food_in_colony();

    std::vector<double> get_colony_location();
    std::vector<Ant> get_colony_ants();
    std::vector<Ant> colonyAnts{};

    int colonyEllipseSize{25};
    const int initialColonyEllipseSize{25};
    const int maxRandomNumber{360};


protected:
    int amountOfFoodInColony{10};
    std::vector<double> colonyLocation{0,0};
    int numberOfAnts{0};
    ColonyLogic colonyLogic{};
};

#endif // COLONY_H
