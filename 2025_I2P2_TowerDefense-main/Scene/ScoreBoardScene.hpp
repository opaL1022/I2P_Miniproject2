//DONE Define the ScoreBoardScene
#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP
#include <memory>

#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>

class ScoreBoardScene final : public Engine::IScene {
private:
    Group *UIGroup;
    int halfW;
    int halfH;
    const int pagesize = 5;
    int curpage;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    std::vector<std::pair<std::string,std::string>> name_scores;
    std::vector<Engine::Label *> labels;

public:
    explicit ScoreBoardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void PrevOnClick(int stage);
    void NextOnClick(int stage);
};
#endif
