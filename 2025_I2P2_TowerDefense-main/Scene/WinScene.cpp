#include <functional>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/LOG.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "WinScene.hpp"

void WinScene::Initialize() {

    score = std::to_string(dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->GetMoney());
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH-200, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
    
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 300, halfH+100, 600, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::TextBoxOnClick, this, 3));
    AddNewControlObject(btn);
    textbox = new Engine::Label("", "pirulen.ttf", 36, halfW, halfH+150, 0, 0, 0, 255, 0.5, 0.5);
    AddNewObject(textbox);

    bgmId = AudioHelper::PlayAudio("win.wav");
}
void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}
void WinScene::BackOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void WinScene::TextBoxOnClick(int stage) {
    // Change to select scene.
    if(textbox->Text.size() == 0)
    {
        textbox->Text = "UNKNOWN";
    }
    WriteFile(score);
    WriteFile(textbox->Text);
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
}
void WinScene::OnKeyDown(int keyCode)
{
    if(keyCode <= 26)
    {
        if(textbox->Text.size() < 10)
        {
            textbox->Text += (char)(keyCode + 96);
        }
        else
        {
            Engine::LOG(Engine::INFO) << "Name too long";
        }
    }
    else if(keyCode == ALLEGRO_KEY_BACKSPACE)
    {
        textbox->Text = textbox->Text.substr(0, textbox->Text.size()-1);
    }
    else if(keyCode == ALLEGRO_KEY_SPACE)
    {
        textbox->Text += ' ';
    }
    else if(keyCode == ALLEGRO_KEY_ENTER)
    {
        if(textbox->Text.size() == 0)
        {
            textbox->Text = "UNKNOWN";
        }
        WriteFile(score);
        WriteFile(textbox->Text);
        Engine::GameEngine::GetInstance().ChangeScene("stage-select");
    }
}
void WinScene::WriteFile(const std::string str)
{
    std::ofstream record("C:\\Users\\white\\Documents\\GitHub\\I2P_Miniproject2\\2025_I2P2_TowerDefense-main\\Resource\\scoreboard.txt", std::ios::app);
    if(record.is_open())
    {
        record << str << std::endl;
        record.close();
    }
    else
    {
        Engine::LOG(Engine::ERROR) << "file create failed.";
    }
}
//DONE add text box to enter name and change to scoreboard scene