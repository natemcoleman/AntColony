#include "AntLogic.hpp"

AntLogic::AntLogic()
{
}

void AntLogic::set_angle(double& currentAntAngle, double& newAntAngle)
{
    currentAntAngle=newAntAngle;
}

void AntLogic::set_position(double& currentPositionX, double& currentPositionY, double& newPositionX, double& newPositionY)
{
    currentPositionX = newPositionX;
    currentPositionY = newPositionY;
}

void AntLogic::give_food(bool& antHasFood)
{
    antHasFood = true;
}

void AntLogic::take_food(bool& antHasFood)
{
    antHasFood = false;
}

void AntLogic::set_has_found_a_trail(bool& currentHasATrail, bool newHasATrail)
{
    currentHasATrail = newHasATrail;
}

void AntLogic::update_ant(double& currentAntX, double& currentAntY, double& currentAntAngle)
{
    currentAntX+= sin((currentAntAngle*PI)/180);
    currentAntY-=cos((currentAntAngle*PI)/180);
}

void AntLogic::update_ant(double& currentAntX, double& currentAntY, double& currentAntAngle, bool& antHasFoundATrail)
{
    if(!antHasFoundATrail)
    {
        currentAntAngle += generate_random_angle();
    }
    currentAntX+= sin((currentAntAngle*PI)/180);
    currentAntY-=cos((currentAntAngle*PI)/180);
}

void AntLogic::update_ant(double& currentAntX, double& currentAntY, double& currentAntAngle, bool& antHasFoundATrail, double changeAngle)
{
    if(!antHasFoundATrail)
    {
        currentAntAngle += generate_non_random_angle(changeAngle);
    }
    currentAntX+= sin((currentAntAngle*PI)/180);
    currentAntY-=cos((currentAntAngle*PI)/180);
}

double AntLogic::generate_random_angle()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minRandomAngle, maxRandomAngle);
    return dis(gen);
}

double AntLogic::generate_non_random_angle(double& returnAngle)
{
    return returnAngle;
}
