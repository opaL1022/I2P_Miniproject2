#ifndef FIRETURRET_HPP
#define FIRETURRET_HPP
#include "Turret.hpp"

class FireTurret : public Turret {
public:
    static const int Price;
    FireTurret(float x, float y);
    void CreateBullet() override;
};
#endif   // FIRETURRET_HPP
