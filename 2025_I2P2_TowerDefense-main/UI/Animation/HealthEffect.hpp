#ifndef HEALTHEFFECT_HPP
#define HEALTHEFFECT_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <vector>

#include "Engine/Sprite.hpp"

class PlayScene;

class HealthEffect : public Engine::Sprite {
protected:
    PlayScene *getPlayScene();
    float timeTicks;
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
    float timeSpan = 0.5;

public:
    HealthEffect(float x, float y);
    void Update(float deltaTime) override;
};
#endif
