#ifndef FOOD_H
#define FOOD_H

#include "FoodLogic.hpp"

class Food
{
public:
    Food():foodLocation{0, 0} {};
    Food(double foodX, double foodY, int foodAmount):foodLocation{foodX, foodY}, amountOfFood(foodAmount) {};
    Food(double foodX, double foodY):foodLocation{foodX, foodY} {};

    void update_food();
    void set_amount_of_food(int newFoodAmount);
    void set_location(double xLocation, double yLocation);

    int get_amount_of_food();

    std::vector<double> get_food_location();

    int foodEllipseSize{10};
    int initialFoodEllipseSize{10};

protected:
    int amountOfFood{100};
    std::vector<double> foodLocation{0,0};
    FoodLogic foodLogic{};
};

#endif // FOOD_H
