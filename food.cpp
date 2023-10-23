#include "food.h"

//Food::Food()
//{
//}

//Food::Food(double foodX, double foodY, int foodAmount)
//{
//    foodLocation = {foodX, foodY};
//    amountOfFood = foodAmount;
//}

//Food::Food(double foodX, double foodY)
//{
//    foodLocation = {foodX, foodY};
//    amountOfFood = foodInitializeAmount;
//}

void Food::update_food()
{
    foodLogic.update_food(amountOfFood);
}

int Food::get_amount_of_food()
{
    return amountOfFood;
}

void Food::set_amount_of_food(int newFoodAmount)
{
    foodLogic.set_amount_of_food(amountOfFood, newFoodAmount);
}

void Food::set_location(double newXLocation, double newYLocation)
{
    foodLogic.set_location(foodLocation[0], foodLocation[1], newXLocation, newYLocation);
}

std::vector<double> Food::get_food_location()
{
    return foodLocation;
}
