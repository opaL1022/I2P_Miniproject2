#ifndef BOSSENEMY_HPP
#define BOSSENEMY_HPP
#include "Enemy.hpp"
#include "Engine/Sprite.hpp"

namespace Engine
{
    class Group;
}

class BossEnemy : public Enemy {
private:
    Sprite head;
    float targetRotation;
    float reload;
    const float cooldown=10;
    const float healamt=30;
    void Heal();

public:
    BossEnemy(int x, int y);
    void Draw() const override;
    void Update(float deltaTime) override;
    Engine::Group* AllianceGroup;
};
#endif  
