#ifndef TRAIL_H
#define TRAIL_H

#include "Pheromone.h"

class Trail
{
public:
    Trail();
    Trail(bool isThisFood);

    void update_trail();
    void add_pheromone(Pheromone newPheromone);
    void set_if_trail_type_is_food(bool isThisFood);

    bool return_if_trail_type_is_food();

    int get_size_of_trail();

    std::vector<Pheromone> trail_pheromones{};


protected:
    bool isFood{false};
    bool isColony{false};

};

#endif // TRAIL_H
