#if INTERFACE
#include <Engine/IScene.h>

class Scene_LevelSelect : public IScene {
public:
    int selected = 0;
	bool GoBack = false;
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
#include <Game/Levels/SOZ.h>
#include <Game/Levels/LRZ.h>
#include <Game/Levels/HPZ.h>
#include <Game/Levels/SSZ.h>
#include <Game/Levels/DEZ.h>
#include <Game/Levels/TDZ.h>
#include <Game/Levels/TSZ.h>

#include <Game/Levels/SpecialStage.h>

#include <Game/Levels/ALZ.h>
#include <Game/Levels/BPZ.h>
#include <Game/Levels/CGZ.h>
#include <Game/Levels/DPZ.h>
#include <Game/Levels/EMZ.h>
#include <Game/Levels/ASZ.h>

#include <Game/SaveGame.h>

#include <Game/Scenes/LevelSelect.h>
#include <Game/Scenes/MainMenu.h>

int character = 0; 
int partner = 0xFF;
int mode = 0;

PUBLIC Scene_LevelSelect::Scene_LevelSelect(IApp* app, IGraphics* g) {
    App = app;
    G = g;

    Sound::Audio = App->Audio;
    Sound::Init();

    // Sound::SoundBank[0] = new ISound("Music/Mixed/SaveSelectTria.ogg", true);
    // Sound::Audio->LoopPoint[0] = 131859;

	Discord_UpdatePresence("Main Menu", "Level Select", "icon", false);

    selected = 1;
}

PUBLIC void Scene_LevelSelect::Init() {
	int at = 0;
	if (Sound::SoundBank[0]) {
		char* ct = strstr(Sound::SoundBank[0]->Name, "Menu");
		if (ct != NULL)
			at = Sound::SoundBank[0]->GetPosition();
		//free(ct);
	}
	App->Audio->ClearMusic();
	Sound::PlayStream(0, "Music/Menu2.ogg", true, 0, at, true);

    App->Input->UseTouchController = true;

    FadeTimerMax = 30;
    FadeIn = true;

	SaveGame::CurrentSaveFile = -1;
	SaveGame::CurrentUsedZoneRings = 0x0000;
	SaveGame::CurrentEmeralds = 0xFFFF;
}

bool HaveStage[36] = {
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
	true, // MHZ
	true,
	true, // FBZ
	true,
	true, // SOZ
	true,
	true, // LRZ
	true, // HPZ
	true, // SSZ
	true, // DEZ
	true,
	true, // TDZ
	//LOCKED ON
	true, //ALZ
	true,
	true, //DPZ
	true,
	true, //BPZ
	true,
	true, //ASZ
	true,
	true, //EMZ
	true,
	true, //CGZ
	true,
};

bool HaveSpecial[16]{
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true
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
            //if (selected < 12 || selected > 25) {
                if (HaveStage[selected] || (selected > 25 && HaveSpecial[selected - 26])) {
                    App->Audio->ClearMusic();
                    if (Sound::SoundBank[0]) Sound::SoundBank[0]->Cleanup();
                    delete Sound::SoundBank[0];
                    Sound::SoundBank[0] = NULL;
					if (mode != 2) {
						IApp::Print(0, "%d", selected);
						switch (selected) {
							LevelScene* ls;
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
						//case 10:
						//case 11:
						//	App->NextScene = new Level_LBZ(App, G, (selected % 2) + 1);
						//	break;
						case 12:
						case 13:
							App->NextScene = new Level_MHZ(App, G, (selected % 2) + 1);
							break;
						case 14:
						case 15:
							App->NextScene = new Level_FBZ(App, G, (selected % 2) + 1);
							break;
						case 16:
						case 17:
							App->NextScene = new Level_SOZ(App, G, (selected % 2) + 1);
							break;
						case 18:
						case 19:
							App->NextScene = new Level_LRZ(App, G, (selected % 2) + 1);
							break;
						case 20:
							App->NextScene = new Level_HPZ(App, G, 1);
							break;
						case 21:
							App->NextScene = new Level_SSZ(App, G, 1);
							break;
						case 22:
						case 23:
							App->NextScene = new Level_DEZ(App, G, (selected % 2) + 1);
							break;
						case 24:
							App->NextScene = new Level_TDZ(App, G, 1);
							break;
						default:
							//BENT LETTUCE BABY
							/*SaveGame::CurrentEmeralds = 0x0000;
							ls = new LevelScene(App, G);
							Sound::SoundBank[0] = new ISound("Stages/MSZ/Act2.ogg", true);
							Sound::Audio->LoopPoint[0] = 179390 / 4;
							ls->Str_StageBin = "Stages/MSZ/StageConfig.bin";
							ls->Str_TileConfigBin = "Stages/MSZ/TileConfig.bin";
							ls->Str_SceneBin = "Stages/MSZ/Scene1.bin";
							ls->Str_TileSprite = "Stages/MSZ/16x16Tiles.gif";
							ls->PlayerStartX = 0x13A0;
							ls->PlayerStartY = 0x041A;
							SaveGame::CurrentMode = 1; //Force it to mixed mode
							App->Print(0, "Poop! %d", SaveGame::CurrentMode);
							ls->ZoneID = 1;
							ls->VisualAct = 2;
							sprintf(ls->LevelName, "BENT LETTUCE");
							sprintf(ls->LevelNameDiscord, "Bent Lettuce Zone");
							App->NextScene = ls;*/
                            
                            App->NextScene = new Level_TSZ(App, G, (selected % 2) + 1);
							break;
						}
						//handle SPECIALS
						if (selected > 25) {
							Level_SpecialStage* NextScene = new Level_SpecialStage(App, G);
							NextScene->ZoneID = 0xFF; //go to menu	

							int toLevel = selected - 26;
							NextScene->Act = toLevel;
							App->NextScene = NextScene;
							
						}
					}

                    SaveGame::CurrentCharacterFlag = character;
                    SaveGame::CurrentPartnerFlag = partner; //0xFF for no partner
					SaveGame::CurrentMode = mode;
                }
            //}

				if (GoBack) {
					Scene_MainMenu* NextScene = new Scene_MainMenu(App, G);
					/*NextScene->MenuSprite = MenuSprite;
					NextScene->SuperButtonsSprite = SuperButtonsSprite;
					NextScene->TextSprite = TextSprite;

					// Make these NULL so they don't get accidentally cleaned up later
					MenuSprite = NULL;
					SuperButtonsSprite = NULL;
					TextSprite = NULL;*/

					App->NextScene = NextScene;
				}
        }
    }

    if (FadeTimer == -1) {
        if (App->Input->GetControllerInput(0)[IInput::I_UP_PRESSED]) {
            selected--;
			if (mode != 2) {
				if (selected < 0)
					selected = 41;
			}
			else {
				if (selected < 0)
					selected = 11;
			}

            Sound::Play(Sound::SFX_MENUBLEEP);
        }
		if (App->Input->GetControllerInput(0)[IInput::I_DOWN_PRESSED]) {
			selected++;
			if (mode != 2) {
				if (selected > 41)
					selected = 0;
			}
			else {
				if (selected > 11)
					selected = 0;
			}

            Sound::Play(Sound::SFX_MENUBLEEP);
        }

        if (App->Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED] && !App->Input->GetControllerInput(0)[IInput::I_EXTRA]) {
            character--;
            if (character < 0)
                character = 4;

            Sound::Play(Sound::SFX_MENUBLEEP);
        }
        if (App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED] && !App->Input->GetControllerInput(0)[IInput::I_EXTRA]) {
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

		if (App->Input->GetControllerInput(0)[IInput::I_EXTRA] && App->Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED]) {
			mode--;
			if (mode < 0)
				mode = 2;
			if (mode == 2)
				selected = 0;
			partner++;
			if (partner == 0xFF)
				partner = 0;
			if (partner > 4)
				partner = 0xFF;
			Sound::Play(Sound::SFX_MENUBLEEP);
		}
		if (App->Input->GetControllerInput(0)[IInput::I_EXTRA] && App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED]) {
			mode++;
			if (mode > 2)
				mode = 0;
			if (mode == 2)
				selected = 0;
			partner--;
			if (partner == 0xFF)
				partner = 4;
			if (partner < 0)
				partner = 0xFF;
			Sound::Play(Sound::SFX_MENUBLEEP);
		}

    }

    character = character % 5;
	if (partner != 0xFF) partner %= 5;

    if (App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED]) {
        bool acc = false;
        //if (selected < 12) {
            if (HaveStage[mode != 2 ? selected : selected + 26]) {
                acc = true;
            }
        //}
		if (selected > 25 && HaveSpecial[selected - 26])
			acc = true;
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
	if (App->Input->GetControllerInput(0)[IInput::I_PAUSE_PRESSED]) {
		mode++;
		if (mode > 2)
		{
			mode = 0;
		}
	}
	SaveGame::CurrentMode = mode;

	if (App->Input->GetControllerInput(0)[IInput::I_DENY_PRESSED]) {
		GoBack = true;
		FadeIn = false;
		FadeTimerMax = 30;
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
        "BONUS STAGES",
        "SPECIAL STAGE",
        "SOUND TEST",
    };

	const char* lockedOn[6] = {
		"AZURE LAKE",
		"DESERT PALACE",
		"BALLOON PARK",
		"ANGEL SHORE",
		"ENDLESS MINE",
		"CHROME GADGET"
	};

	const char* specialStages[1]{
		"SPECIAL STAGES"
	};

    G->SetFilter(IE_FILTER_FADEABLE);

	//BG
    G->DrawRectangle(0, 0, App->WIDTH, App->HEIGHT, 0x0022EE);

	//Regular Zones
    for (int i = 0; i < 13; i++) {
        Uint32 col = 0x999999;
        //if (i * 2 < 12) {
            if (HaveStage[i * 2] || HaveStage[i * 2 + 1]) {
                col = 0xFFFFFF;
            }
        //}
        G->DrawTextShadow(4, 4 + i * 18, wordGRoup[i], (selected / 2 == i && mode != 2) ? 0xFFFF00 : col);
    }

	//Comp Zones
	for (int i = 0; i < 6; i++) {
		Uint32 col = 0x999999;
		if ((i * 2) + 13 < 18) {
			if (HaveStage[(i * 2) + 26] || HaveStage[(i * 2 + 1) + 26]) {
				col = 0xFFFFFF;
			}
		}
		G->DrawTextShadow(180, 4 + i * 18, lockedOn[i], (selected / 2 == i && mode == 2) ? 0xFFFF00 : col);
	}
	G->DrawTextShadow(180, 112, specialStages[0], selected > 25 ? 0xFFFF00 : 0xFFFFFF);

    char poop[20];
    char poopbuddy[20];
	char poopmode[20];

	//Act Numbers
    for (int i = 0; i < 26; i++) {
		Uint32 col = 0x999999;
		//if (i < 12) {
		if (HaveStage[i]) {
			col = 0xFFFFFF;
		}
		//}
		if (i != 25)
		{
			sprintf(poop, "%d", (i % 2) + 1);
			G->DrawTextShadow(4 + 16 * 8, 4 + i * 9, poop, (selected == i && mode != 2) ? 0xFFFF00 : col);
		}
    }

	//Bonus Stages?
	for (int i = 0; i < 12; i++) {
		Uint32 col = 0x999999;
		if (i + 26 < 18) {
			if (HaveStage[i + 26]) {
				col = 0xFFFFFF;
			}
		}	
		sprintf(poop, "%d", ((i + 26) % 2) + 1);
		G->DrawTextShadow(180 + 16 * 8, 4 + i * 9, poop, (selected == i && mode == 2) ? 0xFFFF00 : col);
	}

	//Special Stage IDs
	for (int i = 0; i < 16; i++) {
		Uint32 col = 0x999999;
		if (HaveSpecial[i]) {
			col = 0xFFFFFF;
		}
		sprintf(poop, "%d", i + 1);
		G->DrawTextShadow(180 + ((i / 8)) * 30, 4 + 122 + (i / 8 == 0 ? i : i - 8) * 9, poop, selected == i + 26 ? 0xFFFF00 : col);
	}
    
	//Main Char
    switch (character) {
        case 0:
            sprintf(poop, "%s", "Sonic");
            break;
        case 1:
            sprintf(poop, "%s", "Tails");
            break;
        case 2:
            sprintf(poop, "%s", "Knuckles");
            break;
        case 3:
            sprintf(poop, "%s", "Mighty");
            break;
        case 4:
            sprintf(poop, "%s", "Ray");
            break;
        default:
            sprintf(poop, "%s", "Sonic");
            break;
    }
    
	//Partner Char
    switch (partner) {
        case 0:
            sprintf(poopbuddy, "%s", "Sonic");
            break;
        case 1:
            sprintf(poopbuddy, "%s", "Tails");
            break;
        case 2:
            sprintf(poopbuddy, "%s", "Knuckles");
            break;
        case 3:
            sprintf(poopbuddy, "%s", "Mighty");
            break;
        case 4:
            sprintf(poopbuddy, "%s", "Ray");
            break;
        default:
            sprintf(poopbuddy, "%s", "Alone");
            break;
    }
    
	//Mode
    switch (mode) {
        default:
            sprintf(poopmode, "%s", "Classic");
            break;
        case 1:
            sprintf(poopmode, "%s", "Mixed");
            break;
		case 2:
            sprintf(poopmode, "%s", "Locked On");
            break;
    }

    G->DrawTextShadow(App->WIDTH - 4 - strlen(poop) * 8, App->HEIGHT - 4 - 16, poop, 0xFFFFFF);
    G->DrawTextShadow(App->WIDTH - 4 - strlen(poopbuddy) * 8, App->HEIGHT - 4 - 8, poopbuddy, 0xFFFFFF);
	G->DrawTextShadow(App->WIDTH - 4 - strlen(poopmode) * 8, App->HEIGHT - 4 - 24, poopmode, 0xFFFFFF);
}

PUBLIC void Scene_LevelSelect::Cleanup() {
#define CLEANUP(name) if (name) { name->Cleanup(); delete name; name = NULL; }

	App->Audio->ClearMusic();
	CLEANUP(Sound::SoundBank[0]);
}