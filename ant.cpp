#include "ant.h"
#include "AntLogic.hpp"

#define PI 3.14159265

void Ant::update_ant()
{
    antLogic.update_ant(antLocation[0], antLocation[1], antAngle, hasFoundATrail);
}

void Ant::update_ant(double newChangeAngle)
{
    antLogic.update_ant(antLocation[0], antLocation[1], antAngle, hasFoundATrail, newChangeAngle);
}

void Ant::update_ant(bool isOnEdge, bool isSeperateFunction)
{
    antLogic.update_ant(antLocation[0], antLocation[1], antAngle);
}

void Ant::set_position(double newPositionX, double newPositionY)
{
    antLogic.set_position(antLocation[0], antLocation[1], newPositionX, newPositionY);
}

void Ant::set_angle(double newAngle)
{
    antLogic.set_angle(antAngle, newAngle);
}

std::vector<double> Ant::get_position()
{
    return antLocation;
}

bool Ant::getHasFoundATrail() const
{
    return hasFoundATrail;
}

void Ant::setHasFoundATrail(bool newHasFoundATrail)
{
    antLogic.set_has_found_a_trail(hasFoundATrail, newHasFoundATrail);
}

double Ant::get_angle()
{
    return antAngle;
}

bool Ant::check_food()
{
    return hasFood;
}

void Ant::give_food()
{
    antLogic.give_food(hasFood);
}

void Ant::take_food()
{
    antLogic.take_food(hasFood);
}
