//DONE implement the ScoreBoardScene
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <algorithm>

#include "Engine/AudioHelper.hpp"
#include "Engine/LOG.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "Scene/ScoreBoardScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Slider.hpp"

void ScoreBoardScene::Initialize() {

    std::ifstream record("C:\\Users\\white\\Documents\\GitHub\\I2P_Miniproject2\\2025_I2P2_TowerDefense-main\\Resource\\scoreboard.txt");
    if(record.is_open())
    {
        std::string line="";
        std::string name="";
        std::string score="";
        while (std::getline(record, line)) 
        {
            score = line;
            std::getline(record, line);
            name = line;
            name_scores.push_back(std::make_pair(name, score));
        }
        std::sort(name_scores.begin(), name_scores.end(), [](const std::pair<std::string, std::string> &a, const std::pair<std::string, std::string> &b) {
            return std::stoi(a.second) > std::stoi(b.second);
        });
        record.close();
    }
    else
    {
        Engine::LOG(Engine::ERROR) << "file open failed";
    }

    curpage = 0;

    AddNewControlObject(UIGroup = new Group());

    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    halfW = w / 2;
    halfH = h / 2;

    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);

    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 700, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::PrevOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev", "pirulen.ttf", 48, halfW - 500, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 300, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::NextOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next", "pirulen.ttf", 48, halfW + 500, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    Engine::Label *label;

    for(int i = 0; i < pagesize; i++)
    {
        if(i==name_scores.size())
        {
            break;
        }
        const std::string name = (name_scores[i]).first;
        const std::string score = (name_scores[i]).second;
        label = new Engine::Label(name, "pirulen.ttf", 48, halfW - 200, 100 + i * 100, 255, 255, 255, 255, 0.5, 0.5);
        UIGroup->AddNewObject(label);
        labels.push_back(label);
        label = new Engine::Label(score, "pirulen.ttf", 48, halfW + 200, 100 + i * 100, 255, 255, 255, 255, 0.5, 0.5);
        UIGroup->AddNewObject(label);
        labels.push_back(label);
    }
}
void ScoreBoardScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void ScoreBoardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void ScoreBoardScene::PrevOnClick(int stage) {
    if(curpage>0)
    {
        Engine::Label *label;
        curpage--;

        while(!labels.empty())
        {
            UIGroup->RemoveObject(labels.back()->GetObjectIterator());
            labels.pop_back();
        }

        int pos = 0;
        for(int i = curpage * pagesize; i < (curpage + 1) * pagesize; i++, pos++)
        {
            const std::string name = (name_scores[i]).first;
            const std::string score = (name_scores[i]).second;
            label = new Engine::Label(name, "pirulen.ttf", 48, halfW - 200, 100 + pos * 100, 255, 255, 255, 255, 0.5, 0.5);
            UIGroup->AddNewObject(label);
            labels.push_back(label);
            label = new Engine::Label(score, "pirulen.ttf", 48, halfW + 200, 100 + pos * 100, 255, 255, 255, 255, 0.5, 0.5);
            UIGroup->AddNewObject(label);
            labels.push_back(label);
        }
    }
}
void ScoreBoardScene::NextOnClick(int stage) {
    if(curpage+1<(name_scores.size()+pagesize-1)/pagesize)
    {
        Engine::Label *label;
        curpage++;

        while(!labels.empty())
        {
            UIGroup->RemoveObject(labels.back()->GetObjectIterator());
            labels.pop_back();
        }

        int pos = 0;
        for(int i = curpage * pagesize; i < std::min((curpage + 1) * pagesize, (int)name_scores.size()); i++, pos++)
        {
            const std::string name = (name_scores[i]).first;
            const std::string score = (name_scores[i]).second;
            label = new Engine::Label(name, "pirulen.ttf", 48, halfW - 200, 100 + pos * 100, 255, 255, 255, 255, 0.5, 0.5);
            UIGroup->AddNewObject(label);
            labels.push_back(label);
            label = new Engine::Label(score, "pirulen.ttf", 48, halfW + 200, 100 + pos * 100, 255, 255, 255, 255, 0.5, 0.5);
            UIGroup->AddNewObject(label);
            labels.push_back(label);
        }
    }
}
