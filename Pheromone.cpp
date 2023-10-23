#include "Pheromone.h"

Pheromone::Pheromone()
{

}

Pheromone::Pheromone(double locationX, double locationY)
{
    pheromoneLocation = {locationX, locationY};
}

void Pheromone::update_pheromone()
{
    decrease_strength();
}

void Pheromone::set_strength(double newStrength)
{
    pheromoneStrength = newStrength;
}

void Pheromone::set_location(double newXLocation, double newYLocation)
{
    pheromoneLocation = {newXLocation, newYLocation};
}

double Pheromone::get_strength()
{
    return pheromoneStrength;
}

std::vector<double> Pheromone::get_locations()
{
    return pheromoneLocation;
}

void Pheromone::set_trail_type(bool thisIsFood)
{
    if(thisIsFood)
    {
        isFood = true;
        isColony = false;
    }
    else
    {
        isFood = false;
        isColony = true;
    }
}

double Pheromone::get_strength_range()
{
    return pheromoneStrengthRange;
}

double Pheromone::get_pheromone_strength() const
{
    return pheromoneStrength;
}

void Pheromone::set_pheromone_strength(double newPheromoneStrength)
{
    pheromoneStrength = newPheromoneStrength;
}

void Pheromone::decrease_strength()
{
    if(pheromoneStrength>0)
    {
        pheromoneStrength--;
    }
}
