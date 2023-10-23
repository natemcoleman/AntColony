#ifndef PHEROMONE_H
#define PHEROMONE_H

#include <vector>
#include <iostream>
#include <random>

class Pheromone
{
public:
    Pheromone();
    Pheromone(double xLocation, double yLocation);

    void update_pheromone();
    void set_strength(double newStrength);
    void set_location(double newXLocation, double newYLocation);
    void decrease_strength();
    void set_trail_type(bool thisIsFood);
    void set_pheromone_strength(double newPheromoneStrength);

    double get_strength();
    double get_strength_range();
    double get_pheromone_strength() const;

    std::vector<double> get_locations();

protected:
    double pheromoneStrengthRange{0};//CHANGE BACK
    double pheromoneStrength{pheromoneStrengthRange};

    std::vector<double> pheromoneLocation {0,0};
    bool isFood{false};
    bool isColony{true};

};

#endif // PHEROMONE_H
