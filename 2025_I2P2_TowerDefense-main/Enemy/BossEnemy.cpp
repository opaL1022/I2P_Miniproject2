//TODO make Boss Enemy
#include <allegro5/base.h>
#include <random>
#include <string>

#include "Bullet/LaserBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Point.hpp"
#include "BossEnemy.hpp"
#include "Scene/PlayScene.hpp"

BossEnemy::BossEnemy(int x, int y)
    : Enemy("play/enemy-6.png", x, y, 20, 20, 100, 50),
      head("play/enemy-5.png", x, y) {
}
void BossEnemy::Draw() const {
    Enemy::Draw();
    head.Draw();
}
void BossEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    PlayScene *scene = getPlayScene();
    head.Position = Position;
    if (Target) {
        Engine::Point diff = Target->Position - Position;
        if (diff.Magnitude() > CollisionRadius) {
            Target->lockedAlliance.erase(lockedAllianceIterator);
            Target = nullptr;
            lockedAllianceIterator = std::list<Enemy *>::iterator();
        }
    }
    if (!Target) {
        // Lock first seen target.
        // Can be improved by Spatial Hash, Quad Tree, ...
        // However simply loop through all enemies is enough for this program.
        for (auto &it : scene->EnemyGroup->GetObjects()) {
            Engine::Point diff = it->Position - head.Position;
            if(diff.Magnitude()==0)
            {
                continue;
            }
            if (diff.Magnitude() <= CollisionRadius) {
                Target = dynamic_cast<Enemy *>(it);
                Target->lockedAlliance.push_back(this);
                lockedAllianceIterator = std::prev(Target->lockedAlliance.end());
                break;
            }
        }
    }
    if (Target) {
        Engine::Point originRotation = Engine::Point(cos(head.Rotation - ALLEGRO_PI / 2), sin(head.Rotation - ALLEGRO_PI / 2));
        Engine::Point targetRotation = (Target->Position - head.Position).Normalize();
        float maxRotateRadian = rotateRadian * deltaTime;
        float cosTheta = originRotation.Dot(targetRotation);
        // Might have floating-point precision error.
        if (cosTheta > 1) cosTheta = 1;
        else if (cosTheta < -1) cosTheta = -1;
        float radian = acos(cosTheta);
        Engine::Point rotation;
        if (abs(radian) <= maxRotateRadian)
            rotation = targetRotation;
        else
            rotation = ((abs(radian) - maxRotateRadian) * originRotation + maxRotateRadian * targetRotation) / radian;
        // Add 90 degrees (PI/2 radian), since we assume the image is oriented upward.
        head.Rotation = atan2(rotation.y, rotation.x) + ALLEGRO_PI / 2;
        // Shoot reload.
        reload -= deltaTime;
        if (reload <= 0) {
            // shoot.
            reload = coolDown;
            CreateBullet();
        }
    }
}
void BossEnemy::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(head.Rotation - ALLEGRO_PI / 2), sin(head.Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
    // Change bullet position to the front of the gun barrel.
    AudioHelper::PlayAudio("laser.wav");
}
