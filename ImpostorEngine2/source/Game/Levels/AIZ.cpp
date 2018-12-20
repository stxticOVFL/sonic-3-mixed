#if INTERFACE
#include <Game/LevelScene.h>

class Level_AIZ : public LevelScene {
public:
    bool OnBeach = false;
    bool SuperSonicMoving = true;
    int  CutsceneRoutineNumber = 0x00;
    int  Cutscene_SonicWaitTimer = 0;
    int  Cutscene_KnucklesBackForth = 0;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/AIZ.h>

PUBLIC Level_AIZ::Level_AIZ(IApp* app, IGraphics* g, int ACT) : LevelScene(app, g) {
    ZoneID = 1;
    Act = ACT;

    IApp::Print(0, "Starting AIZ...");

    uint64_t startTime = SDL_GetTicks();

    if (Act == 0) {
        Sound::SoundBank[0] = new ISound("Music/3M_AIZ1.ogg", true);
		Sound::Audio->LoopPoint[0] = 0;

        Str_TileConfigBin = "Stages/AIZ/TileConfig1.bin";
        Str_SceneBin = "Stages/AIZ/Scene0.bin";
        Str_TileSprite = "Stages/AIZ/16x16Tiles0.gif";
        Str_ObjectsList = "Stages/AIZ/Objects0.bin";
        Str_RingsList = "Stages/AIZ/Rings0.bin";
    }
    else if (Act == 1) {
        Sound::SoundBank[0] = new ISound("Music/3M_AIZ1.ogg", true);
		Sound::Audio->LoopPoint[0] = 1;

        Str_TileConfigBin = "Stages/AIZ1/TileConfig.bin";
        Str_SceneBin = "Stages/AIZ1/Scene.bin";
        Str_TileSprite = "Stages/AIZ1/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/AIZ1/Animated Tiles.gif";
    }
    else if (Act == 2) {
        Sound::SoundBank[0] = new ISound("Music/3M_AIZ2.ogg", true);
		Sound::Audio->LoopPoint[0] = 0;

        Str_TileConfigBin = "Stages/AIZ2/TileConfig.bin";
        Str_SceneBin = "Stages/AIZ2/Scene.bin";
        Str_TileSprite = "Stages/AIZ2/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/AIZ2/Animated Tiles.gif";

        VisualAct = 2;
    }

    sprintf(LevelName, "ANGEL ISLAND");
    sprintf(LevelNameDiscord, "Angel Island");

    if (Act == 0) {
        PlayerStartX = 0x01E0;
        PlayerStartY = 0x041A;

        HUDVisible = false;
    }
    else if (Act == 1) {
        // PlayerStartX = 0x13E0;
        // PlayerStartY = 0x041A;
        //
        // PlayerStartX = 0x2656;
        // PlayerStartY = 0x04A2;

        PlayerStartX = 0x19D0;
        PlayerStartY = 0x1BC;
    }
    else {
        PlayerStartX = 0x2820;
        PlayerStartY = 0x04D0;
    }

    IApp::Print(-1, "%s Act %d Constructor took %0.3fs to run.", LevelNameDiscord, Act, (SDL_GetTicks() - startTime) / 1000.0);
}

PUBLIC void Level_AIZ::RestartStage(bool doActTransition, bool drawBackground) {
    App->Audio->ClearMusic();
    App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

    BackgroundRepeatTileWidth = 32;

    LevelScene::RestartStage(doActTransition, drawBackground);

    if (Act == 1) {
        VisualWaterLevel = 0x508;
        WaterLevel = 0x508;
    }
    else {
        VisualWaterLevel = 0x528;
        WaterLevel = 0x528;
    }

    if (Act == 0) {
        LevelCardTimer = 0.0;
        LevelCardHide = true;
        FadeAction = FadeActionType::FADEIN;
        FadeTimerMax = 90;
        FadeMax = 0x140;
        OnBeach = false;
        SuperSonicMoving = true;
        CutsceneRoutineNumber = 0x00;

        Cutscene_SonicWaitTimer = -1;
        Cutscene_KnucklesBackForth = -1;

        Player->Cutscene = true;
        Player->ControlLocked = true;
        Player->ChangeAnimation(Player->AnimationMap["S_Run"]);
    }
}

PUBLIC void Level_AIZ::AssignSpriteMapIDs() {
    if (Act <= 1) {
    	SpriteMapIDs[0x01] = SpriteMap["Items"];
        SpriteMapIDs[0x04] = SpriteMap["AIZ"];
        SpriteMapIDs[0x05] = SpriteMap["AIZ"];
    	SpriteMapIDs[0x07] = SpriteMap["Objects"];
    	SpriteMapIDs[0x08] = SpriteMap["Objects"];
        SpriteMapIDs[0x09] = SpriteMap["AIZ"];
        SpriteMapIDs[0x0A] = SpriteMap["AIZ"];
        SpriteMapIDs[0x0C] = SpriteMap["AIZ"];
        SpriteMapIDs[0x0D] = SpriteMap["AIZ"];
        SpriteMapIDs[0x0F] = SpriteMap["AIZ"];
    	SpriteMapIDs[0x2F] = SpriteMap["AIZ"];
    	//SpriteMapIDs[0x33] = SpriteMap["HCZ"];
    	SpriteMapIDs[0x34] = SpriteMap["Objects"];
        SpriteMapIDs[0x35] = SpriteMap["AIZ"];

    	SpriteMapIDs[0x51] = SpriteMap["AIZ"];
    }
    else {
    	SpriteMapIDs[0x01] = SpriteMap["Items"];
        SpriteMapIDs[0x04] = SpriteMap["AIZ2"];
        SpriteMapIDs[0x05] = SpriteMap["AIZ2"];
    	SpriteMapIDs[0x07] = SpriteMap["Objects"];
    	SpriteMapIDs[0x08] = SpriteMap["Objects"];
        SpriteMapIDs[0x09] = SpriteMap["AIZ"];
        SpriteMapIDs[0x0A] = SpriteMap["AIZ"];
        SpriteMapIDs[0x0C] = SpriteMap["AIZ"];
        SpriteMapIDs[0x0D] = SpriteMap["AIZ2"];
        SpriteMapIDs[0x0F] = SpriteMap["AIZ"];
    	SpriteMapIDs[0x2F] = SpriteMap["AIZ"];
    	//SpriteMapIDs[0x33] = SpriteMap["HCZ"];
    	SpriteMapIDs[0x34] = SpriteMap["Objects"];
        SpriteMapIDs[0x35] = SpriteMap["AIZ"];

    	SpriteMapIDs[0x51] = SpriteMap["AIZ2"];
        SpriteMapIDs[0x8C] = SpriteMap["AIZ"];
    }
}

PUBLIC void Level_AIZ::LoadZoneSpecificSprites() {
	if (!SpriteMap["HCZ"]) {
		SpriteMap["HCZ"] = new ISprite("Sprites/HCZ/Objects.gif", App);
		SpriteMap["HCZ"]->LoadAnimation("Sprites/HCZ/Button.bin");
		SpriteMap["HCZ"]->LoadAnimation("Sprites/HCZ/Fan.bin");
		SpriteMap["HCZ"]->LoadAnimation("Sprites/HCZ/HandLauncher.bin");
		SpriteMap["HCZ"]->LoadAnimation("Sprites/HCZ/BreakBar.bin");
		SpriteMap["HCZ"]->LoadAnimation("Sprites/HCZ/Decoration.bin");
		SpriteMap["HCZ"]->LoadAnimation("Sprites/HCZ/Platform.bin");
		SpriteMap["HCZ"]->LoadAnimation("Sprites/HCZ/Wake.bin");
		SpriteMap["HCZ"]->LoadAnimation("Sprites/HCZ/Bridge.bin");
		// printf("\n");
	}

    if (Act <= 1) {
        if (!SpriteMap["AIZ"]) {
    		SpriteMap["AIZ"] = new ISprite("Sprites/AIZ1/Objects.gif", App);
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/Bloominator.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/CaterkillerJr.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/CollapsingPlatform.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/CorkFloor.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/Decoration.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/FallingLog.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/MonkeyDude.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/Platform.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/Rhinobot.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/SwingRope.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/Tree.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/ZiplinePeg.bin");
    		// printf("\n");
    	}
    }
    else {
        if (!SpriteMap["AIZ"]) {
    		SpriteMap["AIZ"] = new ISprite("Sprites/AIZ1/Objects.gif", App);
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/Bloominator.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/CaterkillerJr.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/CollapsingPlatform.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/CorkFloor.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/Decoration.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/FallingLog.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/MonkeyDude.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/Platform.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/Rhinobot.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/SwingRope.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/Tree.bin");
            SpriteMap["AIZ"]->LoadAnimation("Sprites/AIZ1/ZiplinePeg.bin");
    		// printf("\n");
    	}

        if (!SpriteMap["AIZ2"]) {
            SpriteMap["AIZ2"] = new ISprite("Sprites/AIZ2/Objects.gif", App);
            SpriteMap["AIZ2"]->LoadAnimation("Sprites/AIZ2/BreakableWall.bin");
            SpriteMap["AIZ2"]->LoadAnimation("Sprites/AIZ1/Drawbridge.bin");
            SpriteMap["AIZ2"]->LoadAnimation("Sprites/AIZ2/CollapsingPlatform.bin");
            SpriteMap["AIZ2"]->LoadAnimation("Sprites/AIZ2/CorkFloor.bin");
            SpriteMap["AIZ2"]->LoadAnimation("Sprites/AIZ1/Decoration.bin"); // HACK: padding
            SpriteMap["AIZ2"]->LoadAnimation("Sprites/AIZ2/FallingLog.bin");
            SpriteMap["AIZ2"]->LoadAnimation("Sprites/AIZ1/MonkeyDude.bin"); // HACK: padding
            SpriteMap["AIZ2"]->LoadAnimation("Sprites/AIZ2/Platform.bin");
            // printf("\n");
        }
    }

    if (!KnuxSprite[0]) {
        KnuxSprite[0] = new ISprite("Player/Knux1.gif", App);
        KnuxSprite[1] = new ISprite("Player/Knux2.gif", App);
        KnuxSprite[2] = new ISprite("Player/Knux3.gif", App);
        KnuxSprite[3] = new ISprite("Player/KnuxCutsceneAIZ.gif", App);
        KnuxSprite[4] = new ISprite("Player/KnuxCutsceneHPZ.gif", App);

        KnuxSprite[0]->LoadAnimation("Player/Knux.bin");
        KnuxSprite[1]->LinkAnimation(KnuxSprite[0]->Animations);
        KnuxSprite[2]->LinkAnimation(KnuxSprite[0]->Animations);
        KnuxSprite[3]->LinkAnimation(KnuxSprite[0]->Animations);
        KnuxSprite[4]->LinkAnimation(KnuxSprite[0]->Animations);
    }
}

PUBLIC void Level_AIZ::Subupdate() {
    if (Act == 0) {
        if (LevelCardTimer >= 1.5) {
            LevelCardTimer = 5.0;
        }
        if (LevelCardTimer >= 5.0) {
            LevelCardHide = false;
        }

        if (CutsceneRoutineNumber == 1) {
            if (Player->Ground && Cutscene_SonicWaitTimer < 0) {
                Player->Action = ActionType::Normal;
                Player->ChangeAnimation(Player->AnimationMap["Bored 1"]);
                Cutscene_SonicWaitTimer = 120;
            }

            if (Cutscene_SonicWaitTimer == 0) {
                CutsceneRoutineNumber = 2;
                Player->ChangeAnimation(Player->AnimationMap["Balance 2"]);
                Cutscene_KnucklesBackForth = 60;
                Player->EZX -= 4;
            }
        }
        else if (CutsceneRoutineNumber == 2) {
            if (Cutscene_KnucklesBackForth == 0) {
                CutsceneRoutineNumber = 3;
                Player->ChangeAnimation(Player->AnimationMap["Idle"]);
                Player->EZX += 4;
                Cutscene_SonicWaitTimer = 120;
            }
        }
        else if (CutsceneRoutineNumber == 3) {
            if (Cutscene_SonicWaitTimer == 0) {
                Player->Cutscene = false;
                Player->ControlLocked = false;
                Player->Rings = 0;

                LevelCardTimer = 0.0;
                LevelCardHide = false;

                HUDVisible = true;
                Timer = 0;

                Frame--;

                Act = 1;
                PlayerStartX = 0x13E0;
                PlayerStartY = 0x041A;
                Str_TileConfigBin = "Stages/AIZ/TileConfig1.bin";
                Str_SceneBin = "Stages/AIZ/Scene1.bin";
                Str_TileSprite = "Stages/AIZ/16x16Tiles1.gif";
                //Str_AnimatedSprites = "Sprites/AIZ/AnimatedTiles";
                Str_ObjectsList = "Stages/AIZ/Objects1.bin";
                Str_RingsList = "Stages/AIZ/Rings1.bin";
                Init();
            }
        }


        if (Cutscene_SonicWaitTimer > 0)
            Cutscene_SonicWaitTimer--;
        if (Cutscene_KnucklesBackForth > 0)
            Cutscene_KnucklesBackForth--;
    }
    else if (Act == 1) {
        if (Frame & 0x1) {
            int water = VisualWaterLevel - CameraY;
            if (water < App->HEIGHT) {
                if (water < 0) {
                    water = 0;
                }
                else {
                    memset(Data->layers[1].Deform, 0, water);
                }

                int8_t AIZ1_WaterDeformDelta[64] = {
                    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    0,    0,    0,    0,
                	0,    0,    0,    0,    0,    0,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,    0,    0,    0,    0,
                	0,    0,    0,    0,    0,    0,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1
                };
                for (int i = water; i < App->HEIGHT; i++) {
                    Data->layers[1].Deform[i] = AIZ1_WaterDeformDelta[(i + (Frame >> 1) + CameraY) & 0x3F];
                }
            }
            else {
                memset(Data->layers[1].Deform, 0, App->HEIGHT);
            }
            memcpy(Data->layers[2].Deform, Data->layers[1].Deform, App->HEIGHT);
            memcpy(Data->layers[3].Deform, Data->layers[1].Deform, App->HEIGHT);
        }

        if (Player->EZX > 0x2F30) {
            TileSprite->Palette[0x31] = 0xEE4400;
            TileSprite->Palette[0x32] = 0xEE6600;
            TileSprite->Palette[0x33] = 0xEEAA00;
            TileSprite->Palette[0x34] = 0xEECC00;
	        TileSprite->Palette[0x35] = 0xEEEE22;
            TileSprite->Palette[0x36] = 0xEEEEAA;

            Data->layers[4].OffsetY--;

            TileSprite->UpdatePalette();
        }
    }
    else if (Act == 2) {
        if (Frame & 0x1) {
            int water = VisualWaterLevel - CameraY;
            if (water < 0) {
                water = 0;
            }
            if (water > App->HEIGHT - 1) {
                water = App->HEIGHT - 1;
            }
            // Deform = (int8_t*)calloc(App->HEIGHT, 1);

            int8_t AIZ2_BGDeformDelta[64] = {
                -2,     1,    2,    2,-1,    2,    2,    1,    2,-1,-2,-2,-2,    1,-1,-1,
                -1,     0,-2,    0,    0,    0,-2,    0,-2,    2,    0,-2,    2,    2,-1,-2,
                -2,     1,    2,    2,-1,    2,    2,    1,    2,-1,-2,-2,-2,    1,-1,-1,
                -1,     0,-2,    0,    0,    0,-2,    0,-2,    2,    0,-2,    2,    2,-1,-2,
            };
            for (int i = 0; i < App->HEIGHT; i++) {
               Data->layers[0].Deform[i] = AIZ2_BGDeformDelta[(i + (Frame >> 2) + CameraY) & 0x3F];
            }

            memset(Data->layers[1].Deform, 0, water);

            int8_t AIZ2_FGDeformDelta[64] = {
                0,    0,    1,    1,    0,    0,    0,    0,    1,    0,    0,    0,    0,    1,    0,    0,
        	    0,    0,    0,    0,    0,    0,    0,    0,    0,    1,    0,    0,    1,    1,    0,    0,
        	    0,    0,    1,    1,    0,    0,    0,    0,    1,    0,    0,    0,    0,    1,    0,    0,
        	    0,    0,    0,    0,    0,    0,    0,    0,    0,    1,    0,    0,    1,    1,    0,    0
            };
            for (int i = 0; i < water; i++) {
               Data->layers[1].Deform[i] = AIZ2_FGDeformDelta[(i + (Frame >> 1) + CameraY) & 0x3F];
            }

            int8_t AIZ1_WaterDeformDelta[64] = {
                1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    0,    0,    0,    0,
            	0,    0,    0,    0,    0,    0,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
               -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,    0,    0,    0,    0,
            	0,    0,    0,    0,    0,    0,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1
            };
            for (int i = water; i < App->HEIGHT; i++) {
                Data->layers[1].Deform[i] = AIZ1_WaterDeformDelta[(i + (Frame >> 1) + CameraY) & 0x3F];
            }

            memcpy(Data->layers[2].Deform, Data->layers[1].Deform, App->HEIGHT);
        }

        if (RoutineNumber >> 0 & 1) {
            if (Data->layers[1].Tiles[0x270 + 0x3B * Data->layers[1].Width] != 0x0000) {
                for (int i = 0x3B; i < 0x53; i++) {
                    memset(&Data->layers[1].Tiles[0x270 + i * Data->layers[1].Width], 0x00, 8 * sizeof(short));
                }
            }
        }

        if (CameraX >= 0x2440) {
            if (WaterLevel < 0x618 && (RoutineNumber >> 0 & 1)) {
                VisualWaterLevel = WaterLevel += 2;
                ShakeTimer = -1;
            }
            else {
                ShakeTimer = 0;
            }
        }
        else {
            if (WaterLevel > 0x528)
                VisualWaterLevel = WaterLevel -= 2;
        }
    }
    else if (Act == 2) {
    }

    // Do palette stuffs
    if (Act <= 1) {
        if (Frame % 8 == 0) {
            // Waterfalls
            TileSprite->RotatePaletteLeft(TileSprite->Palette + 0x2B, 4);
            TileSprite->RotatePaletteLeft(TileSprite->PaletteAlt + 0x2B, 4);

            // Flower / Log BG / Tree BG
            int palstart = 0x2F;
            if (CameraX < 0x2BB0 - App->WIDTH / 2) {
                TileSprite->Palette[palstart] = 0xEE0022;
            }
            else if (CameraX < 0x2E50 - App->WIDTH / 2) {
                TileSprite->Palette[palstart] = 0x444422;
            }
            else {
                TileSprite->Palette[palstart] = 0x2200CC;
            }

            TileSprite->UpdatePalette();
        }
    }
    else {
        if (Frame % 6 == 0) {
            TileSprite->RotatePaletteLeft(TileSprite->Palette + 0x3C, 4);
            TileSprite->RotatePaletteLeft(TileSprite->PaletteAlt + 0x3C, 4);
            TileSprite->UpdatePalette();
        }
    }

    LevelScene::Subupdate();
}

PUBLIC void Level_AIZ::HandleCamera() {
    if (Act != 0)
        LevelScene::HandleCamera();
    else {
        if (SuperSonicMoving) {
            if (OnBeach)
                CameraX += 16;
            else
                CameraX += 8 * 2 * 4;
        }
    }

    if (Act == 0) {
        if (SuperSonicMoving) {
            if (CameraX < 0x1400 && !OnBeach) {
                BackgroundRepeatTileWidth = 32;
                Data->layers[1].Visible = false;
                Data->layers[2].Visible = false;
                // Intro sequence camera stuff
            }
            else if (CameraX >= 0x1400 && !OnBeach) {
                CameraX = 0x000;
                //Player->EZX -= 0x800;
                BackgroundRepeatTileWidth = 0;
                Data->layers[1].Visible = true;
                Data->layers[2].Visible = true;
                Data->layers[0].ScrollIndexes[0].Size = 0x7FFF;
                OnBeach = true;
            }

            Player->EZX = CameraX + App->WIDTH / 2 - 4;
            Player->EZY = CameraY + App->HEIGHT / 2 + 32;
            Player->GroundSpeed = 0xC00;
            Player->Ground = true;

            if (CameraX >= 0x1308 && OnBeach) {
                CameraX = 0x1308;

                SuperSonicMoving = false;
                Player->GroundSpeed = 0x0;
                Player->XSpeed = 0x0;
                Player->Rings = 1;
                Player->Hurt(Player->EZX + 1, false);
                Player->Deform();
                Player->ChangeAnimation(Player->AnimationMap["Hurt"]);

                CutsceneRoutineNumber = 1;
            }
        }

        int MaxY = 0x400 - 8;
        CameraY = MaxY - App->HEIGHT / 2;
        if (Player->EZY > 0x480) {
            Player->EZY = 0x480;
        }
    }
    else if (Act == 1) {
        int MaxY = 0x0;
        int ToS3X = CameraX + App->WIDTH / 2 - 0xA0;

        int CameraBoundCount = 6;
        int CameraBounds[12] = {
            0x1650, 0x390,
            0x1B00, 0x3B0,
            0x2000, 0x430,
            0x2B00, 0x4C0,
            0x2D80, 0x3B0,
            0x7FFF, 0x2E0,
        };

        for (int i = 0; i < CameraBoundCount; i++) {
            if (ToS3X <= CameraBounds[i * 2]) {
                MaxY = CameraBounds[i * 2 + 1];
                break;
            }
        }

        if (RoutineNumber == 0x00) {
            if (CameraMinX < 0x1308)
                CameraMinX = 0x1308;
            CameraMaxY = MaxY;

            MaxY += 0xE0;
            MaxY -= App->HEIGHT;
            if (CameraY > MaxY) {
                CameraY = MaxY;
            }
            if (CameraX < 0x1308) {
                CameraX = 0x1308;
            }
        }
    }
    else {
        if (CameraX >= 0x3D00) {
            Data->layers[0].OffsetY = 0xA8;
        }
        else {
            Data->layers[0].OffsetY = 0;
        }
    }
}

PUBLIC void Level_AIZ::UpdateDiscord() {
    char imgkey[15];
    char levelname[50];
    sprintf(imgkey, "%d", ZoneID);
    if (Act == 0)
        sprintf(levelname, "%s%s%d", LevelNameDiscord, " Act ", 1);
    else
        sprintf(levelname, "%s%s%d", LevelNameDiscord, " Act ", Act);
    Discord_UpdatePresence("Sonic 3:", levelname, imgkey);
}

PUBLIC void Level_AIZ::Cleanup() {
    #define CLEANUP(name) if (name) { name->Cleanup(); delete name; name = NULL; }

    CLEANUP(SpriteMap["AIZ"]);
    // CLEANUP(SpriteMap["AIZ Enemies"]);
    // CLEANUP(SpriteMap["AIZ Boss"]);

    LevelScene::Cleanup();
}
