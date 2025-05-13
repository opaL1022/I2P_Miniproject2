//TODO Define the ScoreBoardScene
#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP
#include <memory>

#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>

class ScoreBoardScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;

public:
    explicit ScoreBoardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void PrevOnClick(int stage);
    void NextOnClick(int stage);
};
#endif
