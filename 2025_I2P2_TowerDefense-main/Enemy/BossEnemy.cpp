#include <allegro5/base.h>
#include <random>
#include <string>

#include "Engine/Point.hpp"
#include "Engine/Group.hpp"
#include "BossEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include "UI/Animation/HealthEffect.hpp"
#include "UI/Animation/DirtyEffect.hpp"

BossEnemy::BossEnemy(int x, int y)
    : Enemy("play/enemy-6.png", x, y, 20, 20, 1000, 1000),
      head("play/enemy-5.png", x, y), targetRotation(0) {
}
void BossEnemy::Draw() const {
    Enemy::Draw();
    head.Draw();
}
void BossEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    head.Position = Position;
    // Choose arbitrary one.
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0.0f, 4.0f);
    float rnd = dist(rng);
    if (rnd < deltaTime) {
        // Head arbitrary rotation.
        std::uniform_real_distribution<> distRadian(-ALLEGRO_PI, ALLEGRO_PI);
        targetRotation = distRadian(rng);
    }
    head.Rotation = (head.Rotation + deltaTime * targetRotation) / (1 + deltaTime);
    reload -= deltaTime;
    if(reload<=0)
    {
        Heal();
        reload = cooldown;
    }
    if(burntime>0)
    {
        head.Tint = al_map_rgba(255, 128, 128, 255);
    }
    else
    {
        head.Tint = al_map_rgba(255, 255, 255, 255);
    }
}
void BossEnemy::Heal()
{
    PlayScene* scene = getPlayScene();
    AllianceGroup = scene->EnemyGroup;
    for(auto &it : AllianceGroup->GetObjects())
    {
        Engine::Point target = it->Position;
        scene->EffectGroup->AddNewObject(new HealthEffect(target.x, target.y));
        dynamic_cast<Enemy*>(it)->Hit(-healamt);
    }
}