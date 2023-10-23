#ifndef ANTLOGIC_HPP
#define ANTLOGIC_HPP

#include <vector>
#include <random>
#include <iostream>

#define PI 3.14159265

class AntLogic
{
public:
    AntLogic();

    double maxRandomAngle{20};
    double minRandomAngle{-maxRandomAngle};

    void set_angle(double& currentAntAngle, double& newAntAngle);
    void set_position(double& currentPositionX, double& currentPositionY, double& newPositionX, double& newPositionY);
    void give_food(bool& anthasFood);
    void take_food(bool& anthasFood);
    void set_has_found_a_trail(bool& currentHasATrail, bool newHasATrail);

    void update_ant(double& currentAntX, double& currentAntY, double& currentAntAngle);
    void update_ant(double& currentAntX, double& currentAntY, double& currentAntAngle, bool& antHasFoundATrail);
    void update_ant(double& currentAntX, double& currentAntY, double& currentAntAngle, bool& antHasFoundATrail, double nonRandomAngle);

    double generate_random_angle();
    double generate_non_random_angle(double &returnAngle);
};


#endif // ANTLOGIC_HPP
