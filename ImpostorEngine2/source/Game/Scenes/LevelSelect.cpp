#if INTERFACE
#include <Engine/IScene.h>

class Scene_LevelSelect : public IScene {
public:
    int selected = 0;
};
#endif

#include <Game/LevelScene.h>
#include <Game/Levels/AIZ.h>
#include <Game/Levels/HCZ.h>
#include <Game/Levels/MGZ.h>
//#include <Game/Levels/CNZ.h>
//#include <Game/Levels/ICZ.h>
#include <Game/Levels/LBZ.h>
#include <Game/Levels/MHZ.h>
#include <Game/Levels/FBZ.h>
//#include <Game/Levels/SOZ.h>
//#include <Game/Levels/LRZ.h>
//#include <Game/Levels/HPZ.h>
//#include <Game/Levels/SSZ.h>
//#include <Game/Levels/DEZ.h>
//#include <Game/Levels/TDZ.h>
#include <Game/Levels/SpecialStage.h>

#include <Game/Scenes/LevelSelect.h>

int character = 0;

PUBLIC Scene_LevelSelect::Scene_LevelSelect(IApp* app, IGraphics* g) {
    App = app;
    G = g;

    Sound::Audio = App->Audio;
    Sound::Init();

    if (!Sound::SoundBank[0]) {
    	Sound::SoundBank[0] = new ISound("Music/SaveSelectTria.ogg", true);
    	Sound::Audio->LoopPoint[0] = 131859;
    }
}

PUBLIC void Scene_LevelSelect::Init() {
    if (!App->Audio->IsPlayingMusic(Sound::SoundBank[0])) {
        App->Audio->ClearMusic();
        App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
    }

    FadeTimerMax = 30;
    FadeIn = true;
}

PUBLIC void Scene_LevelSelect::Update() {
    if (FadeTimer == -1 && FadeTimerMax > 1)
        FadeTimer = FadeTimerMax;
    if (FadeTimer > 0) {
        FadeTimer--;
        if (!FadeIn)
            G->SetFade(int((1.0 - float(FadeTimer - 1) / FadeTimerMax) * FadeMax));
        else
            G->SetFade(int((float(FadeTimer) / FadeTimerMax) * FadeMax));
    }

    // Do Fade actions
    if (FadeTimer == 0) {
        FadeTimer = -1;
        FadeTimerMax = 0;

        if (!FadeIn) {
            switch (selected) {
                case 0:
                case 1:
                    App->Audio->ClearMusic();
                    if (Sound::SoundBank[0]) Sound::SoundBank[0]->Cleanup();
                    delete Sound::SoundBank[0];
                    Sound::SoundBank[0] = NULL;

                    App->NextScene = new Level_AIZ(App, G, (selected % 2) + 1);
                    ((LevelScene*)App->NextScene)->CharacterFlag = character;
                    break;
                case 2:
                case 3:
                    App->Audio->ClearMusic();
                    if (Sound::SoundBank[0]) Sound::SoundBank[0]->Cleanup();
                    delete Sound::SoundBank[0];
                    Sound::SoundBank[0] = NULL;

                    App->NextScene = new Level_HCZ(App, G, (selected % 2) + 1);
                    ((LevelScene*)App->NextScene)->CharacterFlag = character;
                    break;
                case 4:
                case 5:
                    App->Audio->ClearMusic();
                    if (Sound::SoundBank[0]) Sound::SoundBank[0]->Cleanup();
                    delete Sound::SoundBank[0];
                    Sound::SoundBank[0] = NULL;

                    App->NextScene = new Level_MGZ(App, G, (selected % 2) + 1);
                    ((LevelScene*)App->NextScene)->CharacterFlag = character;
                    break;
                case 10:
                    App->Audio->ClearMusic();
                    if (Sound::SoundBank[0]) Sound::SoundBank[0]->Cleanup();
                    delete Sound::SoundBank[0];
                    Sound::SoundBank[0] = NULL;

                    App->NextScene = new Level_LBZ(App, G);
                    ((LevelScene*)App->NextScene)->CharacterFlag = character;
                    break;
                case 12:
                case 13:
                    App->Audio->ClearMusic();
                    if (Sound::SoundBank[0]) Sound::SoundBank[0]->Cleanup();
                    delete Sound::SoundBank[0];
                    Sound::SoundBank[0] = NULL;

                    App->NextScene = new Level_MHZ(App, G);
                    ((LevelScene*)App->NextScene)->CharacterFlag = character;
                    break;
                case 14:
                case 15:
                    App->Audio->ClearMusic();
                    if (Sound::SoundBank[0]) Sound::SoundBank[0]->Cleanup();
                    delete Sound::SoundBank[0];
                    Sound::SoundBank[0] = NULL;

                    App->NextScene = new Level_FBZ(App, G, (selected % 2) + 1);
                    ((LevelScene*)App->NextScene)->CharacterFlag = character;
                    break;
                default:
                    break;
            }
        }
    }

    if (FadeIn) {
        if (App->Input->GetControllerInput(0)[IInput::I_UP_PRESSED]) {
            selected--;
            if (selected < 0)
                selected = 25;

            Sound::Play(Sound::SFX_MENUBLEEP);
        }
        if (App->Input->GetControllerInput(0)[IInput::I_DOWN_PRESSED]) {
            selected++;
            if (selected > 25)
                selected = 0;

            Sound::Play(Sound::SFX_MENUBLEEP);
        }

        if (App->Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED]) {
            character--;
            if (character < 0)
                character = 4;

            Sound::Play(Sound::SFX_MENUBLEEP);
        }
        if (App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED]) {
            character++;

            Sound::Play(Sound::SFX_MENUBLEEP);
        }
    }

    character = character % 5;

    if (App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED]) {
        bool acc = false;
        switch (selected) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 10:
            case 12:
            case 13:
            case 14:
            case 15:
                acc = true;
                break;
        }
        if (acc) {
            Sound::Play(Sound::SFX_MENUACCEPT);
            FadeIn = false;
            FadeTimerMax = 30;
        }
        else {
            Sound::Play(Sound::SFX_PUSHING);
        }

    }
}

PUBLIC void Scene_LevelSelect::Render() {
    const char* wordGRoup[16] = {
        "ANGEL ISLAND",
        "HYDROCITY",
        "MARBLE GARDEN",
        "CARNIVAL NIGHT",
        "ICECAP",
        "LAUNCH BASE",
        "MUSHROOM HILL",
        "FLYING BATTERY",
        "SANDOPOLIS",
        "LAVA REEF",
        "SKY SANCTUARY",
        "DEATH EGG",
        "THE DOOMSDAY",
        "BONUS",
        "SPECIAL STAGE",
        "SOUND TEST",
    };

    G->SetFilter(IE_FILTER_FADEABLE);

    G->DrawRectangle(0, 0, App->WIDTH, App->HEIGHT, 0x0022EE);

    for (int i = 0; i < 13; i++) {
        Uint32 col = 0x999999;
        switch (i) {
            case 0:
            case 1:
            case 2:
            // case 5:
            // case 6:
            case 7:
                col = 0xFFFFFF;
                break;
        }
        G->DrawTextShadow(4, 4 + i * 18, wordGRoup[i], selected / 2 == i ? 0xFFFF00 : col);
    }
    char poop[20];
    for (int i = 0; i < 26; i++) {
        Uint32 col = 0x999999;
        switch (i / 2) {
            case 0:
            case 1:
            case 2:
            // case 5:
            // case 6:
            case 7:
                col = 0xFFFFFF;
                break;
        }
        sprintf(poop, "%d", (i % 2) + 1);
        G->DrawTextShadow(4 + 16 * 8, 4 + i * 9, poop, selected == i ? 0xFFFF00 : col);
    }

    if (character == 0)
        sprintf(poop, "%s", "Sonic");
    else if (character == 1)
        sprintf(poop, "%s", "Tails");
    else if (character == 2)
        sprintf(poop, "%s", "Knuckles");
    else if (character == 3)
        sprintf(poop, "%s", "Mighty");
    else if (character == 4)
        sprintf(poop, "%s", "Ray");
    G->DrawTextShadow(App->WIDTH - 4 - strlen(poop) * 8, App->HEIGHT - 4 - 8, poop, character == 3 ? 0x999999 : 0xFFFFFF);
}
