#ifndef FOODLOGIC_HPP
#define FOODLOGIC_HPP

#include <vector>

class FoodLogic
{
public:
    FoodLogic();

    void update_food(int& currentAmountOfFood);
    void set_amount_of_food(int& currentAmountOfFood, int& newFoodAmount);
    void set_location(double& currentXLocation, double& currentYLocation, double& newXLocation, double& newLocation);
    void decrease_food();
};

#endif // FOODLOGIC_HPP
