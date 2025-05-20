#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Bullet/Fire.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "FireTurret.hpp"
#include "Scene/PlayScene.hpp"

const int FireTurret::Price = 10;
FireTurret::FireTurret(float x, float y) : Turret("play/tower-base.png", "play/turret-5.png", x, y, 300, Price, 0.5) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void FireTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new Fire(Position + normalized * 36, diff, rotation, this));
    AudioHelper::PlayAudio("fireball-whoosh.wav");
}
//DONE implement FireTurret