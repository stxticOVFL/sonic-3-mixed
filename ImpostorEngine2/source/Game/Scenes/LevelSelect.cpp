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
#include <Game/Levels/CNZ.h>
#include <Game/Levels/ICZ.h>
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

#include <Game/SaveGame.h>

#include <Game/Scenes/LevelSelect.h>

int character = 0;
int partner = 0xFF;

PUBLIC Scene_LevelSelect::Scene_LevelSelect(IApp* app, IGraphics* g) {
    App = app;
    G = g;

    Sound::Audio = App->Audio;
    Sound::Init();

    // Sound::SoundBank[0] = new ISound("Music/Mixed/SaveSelectTria.ogg", true);
    // Sound::Audio->LoopPoint[0] = 131859;
	if (!Sound::SoundBank[0] || strcmp(Sound::SoundBank[0]->Name, "Music/Data Select.ogg")) {
		Sound::SoundBank[0] = new ISound("Music/Data Select.ogg", true);
		Sound::Audio->LoopPoint[0] = 40308;
	}

    selected = 1;
}

PUBLIC void Scene_LevelSelect::Init() {
    if (!App->Audio->IsPlayingMusic(Sound::SoundBank[0])) {
        App->Audio->ClearMusic();
        App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
    }

    App->Input->UseTouchController = true;

    FadeTimerMax = 30;
    FadeIn = true;

	SaveGame::CurrentSaveFile = -1;
	SaveGame::CurrentUsedZoneRings = 0x0000;
	SaveGame::CurrentEmeralds = 0xFFFF;
}

bool HaveStage[24] = {
    true, // AIZ
    true,
    true, // HCZ
    true,
    true, // MGZ
    true,
    true, // CNZ
    true,
    true, // ICZ
    true,
    true, // LBZ
    true,
	false, // MHZ
	false,
	false, // FBZ
	false,
	false, // SOZ
	false,
	false, // LRZ
	false, // HPZ
	false, // SSZ
	false, // DEZ
	false,
	false, // TDZ
};

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
            if (selected < 12) {
                if (HaveStage[selected]) {
                    App->Audio->ClearMusic();
                    if (Sound::SoundBank[0]) Sound::SoundBank[0]->Cleanup();
                    delete Sound::SoundBank[0];
                    Sound::SoundBank[0] = NULL;

                    switch (selected) {
                        case 0:
                        case 1:
                            App->NextScene = new Level_AIZ(App, G, (selected % 2) + 1);
                            break;
                        case 2:
                        case 3:
                            App->NextScene = new Level_HCZ(App, G, (selected % 2) + 1);
                            break;
                        case 4:
                        case 5:
                            App->NextScene = new Level_MGZ(App, G, (selected % 2) + 1);
                            break;
                        case 6:
                        case 7:
                            App->NextScene = new Level_CNZ(App, G, (selected % 2) + 1);
                            break;
                        case 8:
                        case 9:
                            App->NextScene = new Level_ICZ(App, G, (selected % 2) + 1);
                            break;
                        case 10:
                        case 11:
                            App->NextScene = new Level_LBZ(App, G, (selected % 2) + 1);
                            break;
                        default:
                            break;
                    }

                    SaveGame::CurrentCharacterFlag = character;
                    SaveGame::CurrentPartnerFlag = partner; //0xFF for no partner
                }
            }
        }
    }

    if (FadeTimer == -1) {
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

		if (App->Input->GetControllerInput(0)[IInput::I_EXTRA_PRESSED]) {
			partner--;
			if (partner == 0xFF)
				partner = 4;
			if (partner < 0)
				partner = 0xFF;
			Sound::Play(Sound::SFX_MENUBLEEP);
		}
		if (App->Input->GetControllerInput(0)[IInput::I_EXTRA2_PRESSED]) {
			partner++;

			if (partner == 0xFF)
				partner = 0;
			if (partner > 4)
				partner = 0xFF;
			Sound::Play(Sound::SFX_MENUBLEEP);
		}
    }

    character = character % 5;
	if (partner != 0xFF) partner %= 5;

    if (App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED]) {
        bool acc = false;
        if (selected < 12) {
            if (HaveStage[selected]) {
                acc = true;
            }
        }
        if (acc) {
            Sound::Play(Sound::SFX_MENUACCEPT);
            FadeIn = false;
            FadeTimerMax = 30;
            App->Audio->FadeMusic(0.5);
        }
        else {
            Sound::Play(Sound::SFX_MENUFAIL);
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
        if (i * 2 < 12) {
            if (HaveStage[i * 2] || HaveStage[i * 2 + 1]) {
                col = 0xFFFFFF;
            }
        }
        G->DrawTextShadow(4, 4 + i * 18, wordGRoup[i], selected / 2 == i ? 0xFFFF00 : col);
    }
    char poop[20];
    char poopbuddy[20];
    for (int i = 0; i < 26; i++) {
        Uint32 col = 0x999999;
        if (i < 12) {
            if (HaveStage[i]) {
                col = 0xFFFFFF;
            }
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

	if (partner == 0)
		sprintf(poopbuddy, "%s", "Sonic");
	else if (partner == 1)
		sprintf(poopbuddy, "%s", "Tails");
	else if (partner == 2)
		sprintf(poopbuddy, "%s", "Knuckles");
	else if (partner == 3)
		sprintf(poopbuddy, "%s", "Mighty");
	else if (partner == 4)
		sprintf(poopbuddy, "%s", "Ray");
	else
		sprintf(poopbuddy, "%s", "Alone");

    G->DrawTextShadow(App->WIDTH - 4 - strlen(poop) * 8, App->HEIGHT - 4 - 16, poop, 0xFFFFFF);
    G->DrawTextShadow(App->WIDTH - 4 - strlen(poopbuddy) * 8, App->HEIGHT - 4 - 8, poopbuddy, 0xFFFFFF);
}
