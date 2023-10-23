#ifndef ANT_H
#define ANT_H

#include "AntLogic.hpp"

class Ant
{
public:
    Ant():antLocation{0, 0}{};
    Ant(double newAntPositionX, double newAntPositionY, double newAntAngle):antLocation{newAntPositionX, newAntPositionY}, antAngle(newAntAngle){};



    void update_ant();
    void update_ant(double newChangeAngle);
    void update_ant(bool isOnEdge, bool isSeperateFunction);
    void set_position(double newPositionX, double newPositionY);
    void set_angle(double newAngle);
    void give_food();
    void take_food();
    void setHasFoundATrail(bool newHasFoundATrail);

    bool check_food();
    bool getHasFoundATrail() const;

    double get_angle();
    std::vector<double> get_position();

    bool hasFoundATrail{false};

protected:
    std::vector<double> antLocation{0,0};
    double antAngle{0};
    bool hasFood{false};
    AntLogic antLogic{};
};

#endif // ANT_H
