#ifndef BOSSENEMY_HPP
#define BOSSENEMY_HPP
#include "Enemy.hpp"
#include "Engine/Sprite.hpp"

class PlayScene;

class BossEnemy : public Enemy {
private:
    const float coolDown = 10.0f;
    float reload = 0;
    Sprite head;
    float rotateRadian = 2 * ALLEGRO_PI;
    Enemy *Target = nullptr;
    std::list<Enemy *>::iterator lockedAllianceIterator;;
    PlayScene *getPlayScene();
    void CreateBullet() = 0;

public:
    BossEnemy(int x, int y);
    void Draw() const override;
    void Update(float deltaTime) override;
};
#endif
