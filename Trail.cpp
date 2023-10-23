#include "trail.h"
#include "Pheromone.h"

Trail::Trail()
{

}

Trail::Trail(bool isThisFood)
{
    isFood = isThisFood;
    isColony = !isThisFood;
}

void Trail::update_trail()
{
    for(int i = 0; i < trail_pheromones.size(); i++)
    {
        trail_pheromones.at(i).update_pheromone();
        if(trail_pheromones.at(i).get_strength() == 0)
        {
            trail_pheromones.erase(trail_pheromones.begin());
        }
    }

}

void Trail::add_pheromone(Pheromone newPheromone)
{
    trail_pheromones.push_back(newPheromone);
}

void Trail::set_if_trail_type_is_food(bool isThisFood)
{
    if(isThisFood) //FIXME:: update with = ! modifier
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

bool Trail::return_if_trail_type_is_food()
{
    return isFood;
}

int Trail::get_size_of_trail()
{
    return static_cast<int>(trail_pheromones.size());
}
