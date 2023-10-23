#include "FoodLogic.hpp"

FoodLogic::FoodLogic()
{
}

void FoodLogic::update_food(int& currentAmountOfFood)
{
    if(currentAmountOfFood>0)
    {
        currentAmountOfFood--;
    }
    else
    {
        currentAmountOfFood = 0;
    }
}

void FoodLogic::set_amount_of_food(int& currentAmountOfFood, int& newFoodAmount)
{
    if(newFoodAmount >= 0)
    {
        currentAmountOfFood = newFoodAmount;
    }
    else
    {
        currentAmountOfFood = 0;
    }
}

void FoodLogic::set_location(double& currentXLocation, double& currentYLocation, double& newXLocation, double& newYLocation)
{
    currentXLocation = newXLocation;
    currentYLocation = newYLocation;
}
