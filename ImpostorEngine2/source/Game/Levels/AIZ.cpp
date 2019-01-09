#if INTERFACE
#include <Game/LevelScene.h>

class Level_AIZ : public LevelScene {
public:
    bool OnBeach = false;
    bool SuperSonicMoving = true;
    int  CutsceneRoutineNumber = 0x00;
    int  Cutscene_SonicWaitTimer = 0;
    int  Cutscene_KnucklesBackForth = 0;

    ISprite* AIZObjectsSprite = NULL;
    ISprite* AIZBossSprite = NULL;

    Level_AIZ* Act2Preload = NULL;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/AIZ.h>

Uint32 AIZ1_GlitteringWaterPalette[24] = {
    0x44AAEE,
    0x0066EE,
    0x22EEEE,
    0x44AAEE,
    0x88EEEE,
    0x44AAEE,
    0x0066EE,
    0x88EEEE,
    0xEEEEEE,
    0x0066EE,
    0x22EEEE,
    0x22EEEE,
    0x88EEEE,
    0x44AAEE,
    0x44AAEE,
    0x22EEEE,
    0x0066EE,
    0x0066EE,
    0x22EEEE,
    0x0066EE,
    0xEEEEEE,
    0x22EEEE,
    0x0066EE,
    0x88EEEE,
};
Uint32 AnPal_PalAIZ2_2[24] = {
    0x442200,
    0x444400,
    0xEE8800,
    0x662200,
    0x664400,
    0xEEAA00,
    0x442200,
    0x884400,
    0xEE8800,
    0x662200,
    0xAA4400,
    0xEEAA00,
    0x442200,
    0xCC4400,
    0xEE8800,
    0x662200,
    0xAA4400,
    0xEEAA00,
    0x442200,
    0x884400,
    0xEE8800,
    0x442200,
    0x664400,
    0xEE8800,
};
Uint32 AnPal_PalAIZ2_3[24] = {
    0x442200,
    0x444400,
    0xCC0000,
    0x662200,
    0x664400,
    0xEE0000,
    0x442200,
    0x884400,
    0xCC0000,
    0x662200,
    0xAA4400,
    0xEE0000,
    0x442200,
    0xCC4400,
    0xCC0000,
    0x662200,
    0xAA4400,
    0xEE0000,
    0x442200,
    0x884400,
    0xCC0000,
    0x442200,
    0x664400,
    0xCC0000,
};
Uint32 AnPal_PalAIZ2_4[26] = {
    0xEE6600,
    0xEE6600,
    0xEE6600,
    0xEE6600,
    0xEE8822,
    0xEEAA44,
    0xEEAA66,
    0xEECC88,
    0xEEEE88,
    0xEEEEAA,
    0xEEEEAA,
    0xEEEEAA,
    0xEEEEAA,
    0xEEEEAA,
    0xEEEE88,
    0xEEEE88,
    0xEEEE88,
    0xEEEE88,
    0xEECC88,
    0xEECC88,
    0xEECC88,
    0xEEAA66,
    0xEEAA66,
    0xEEAA44,
    0xEEAA44,
    0xEE8822,
};
Uint32 AnPal_PalAIZ2_5[26] = {
    0xCC0000,
    0xCC0000,
    0xCC0000,
    0xCC0000,
    0xCC2200,
    0xEE0000,
    0xEE2200,
    0xEE4400,
    0xEE6600,
    0xEE8800,
    0xEE8800,
    0xEE8800,
    0xEE8800,
    0xEE8800,
    0xEE6600,
    0xEE4400,
    0xEE4400,
    0xEE4400,
    0xEE2200,
    0xEE2200,
    0xEE2200,
    0xEE0000,
    0xEE0000,
    0xCC2200,
    0xCC2200,
    0xCC2200,
};

PUBLIC Level_AIZ::Level_AIZ(IApp* app, IGraphics* g, int ACT) : LevelScene(app, g) {
    ZoneID = 1;
    Act = ACT;

    IApp::Print(0, "Starting AIZ...");

    uint64_t startTime = SDL_GetTicks();

    if (Act == 0) {
        Sound::SoundBank[0] = new ISound("Music/3M_AIZ1.ogg", true);
		Sound::Audio->LoopPoint[0] = 1;

        Str_TileConfigBin = "Stages/AIZ/TileConfig1.bin";
        Str_SceneBin = "Stages/AIZ/Scene0.bin";
        Str_TileSprite = "Stages/AIZ/16x16Tiles0.gif";
        Str_ObjectsList = "Stages/AIZ/Objects0.bin";
        Str_RingsList = "Stages/AIZ/Rings0.bin";

        VisualAct = 1;
    }
    else if (Act == 1) {
        Sound::SoundBank[0] = new ISound("Music/3M_AIZ1.ogg", true);
		Sound::Audio->LoopPoint[0] = 2381;

        Str_TileConfigBin = "Stages/AIZ1/TileConfig.bin";
        Str_SceneBin = "Stages/AIZ1/Scene.bin";
        Str_TileSprite = "Stages/AIZ1/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/AIZ1/Animated Tiles.gif";

        VisualAct = 1;
    }
    else if (Act == 2) {
        Sound::SoundBank[0] = new ISound("Music/3M_AIZ2.ogg", true);
		Sound::Audio->LoopPoint[0] = 85113;

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

        // PlayerStartX = 0x1E40;
        // PlayerStartY = 0x26C;
    }
    else {
        // PlayerStartX = 0x2820;
        // PlayerStartY = 0x04D0;
    }

    IApp::Print(0, "%s Act %d Constructor took %0.3fs to run.", LevelNameDiscord, Act, (SDL_GetTicks() - startTime) / 1000.0);
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

        if (RoutineNumber == 69) {
            LevelCardTimer = 6.0;
            LevelCardHide = true;
        }
        else {
            LevelCardTimer = 0.0;
            LevelCardHide = false;
        }
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
    	SpriteMapIDs[0x01] = ItemsSprite;
        SpriteMapIDs[0x04] = AIZObjectsSprite;
        SpriteMapIDs[0x05] = AIZObjectsSprite;
    	SpriteMapIDs[0x07] = ObjectsSprite;
    	SpriteMapIDs[0x08] = ObjectsSprite;
        SpriteMapIDs[0x09] = AIZObjectsSprite;
        SpriteMapIDs[0x0A] = AIZObjectsSprite;
        SpriteMapIDs[0x0C] = AIZObjectsSprite;
        SpriteMapIDs[0x0D] = AIZObjectsSprite;
        SpriteMapIDs[0x0F] = AIZObjectsSprite;
    	SpriteMapIDs[0x2F] = AIZObjectsSprite;
    	//SpriteMapIDs[0x33] = SpriteMap["HCZ"];
    	SpriteMapIDs[0x34] = ObjectsSprite;
        SpriteMapIDs[0x35] = AIZObjectsSprite;
    	SpriteMapIDs[0x51] = AIZObjectsSprite;
        SpriteMapIDs[0x90] = AIZBossSprite;
    }
    else {
    	SpriteMapIDs[0x01] = ItemsSprite;
        SpriteMapIDs[0x04] = AIZObjectsSprite;
        SpriteMapIDs[0x05] = AIZObjectsSprite;
        SpriteMapIDs[0x06] = AIZObjectsSprite;
    	SpriteMapIDs[0x07] = ObjectsSprite;
    	SpriteMapIDs[0x08] = ObjectsSprite;
        SpriteMapIDs[0x09] = AIZObjectsSprite;
        SpriteMapIDs[0x0A] = AIZObjectsSprite;
        SpriteMapIDs[0x0C] = AIZObjectsSprite;
        SpriteMapIDs[0x0D] = AIZObjectsSprite;
        SpriteMapIDs[0x0F] = AIZObjectsSprite;
    	SpriteMapIDs[0x2F] = AIZObjectsSprite;
    	//SpriteMapIDs[0x33] = SpriteMap["HCZ"];
    	SpriteMapIDs[0x34] = ObjectsSprite;
        SpriteMapIDs[0x35] = AIZObjectsSprite;
    	SpriteMapIDs[0x51] = AIZObjectsSprite;
        SpriteMapIDs[0x8C] = AIZObjectsSprite;
        SpriteMapIDs[0x90] = AIZBossSprite;
    }
}

PUBLIC void Level_AIZ::LoadZoneSpecificSprites() {
    if (!AIZObjectsSprite) {
		AIZObjectsSprite = new ISprite("Sprites/AIZ/Objects.gif", App);
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Act 1 Tree.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Act 1 Zipline Peg.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Animated Sprites.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Breakable Wall.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Caterkiller Jr.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Collapsing Log Bridge.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Collapsing Platform.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Collapsing Platform 2.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Cork Floor.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Cork Floor 2.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Disappearing Floor.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Disappearing Floor Water.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Drawbridge.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Draw Bridge Fire.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Falling Log (Act 1).bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Falling Log (Act 2).bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Falling Log Splash (Act 1).bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Falling Log Splash (Act 2).bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Flipping Bridge.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Floating Platform.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Floating Platform 2.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Foreground Plant.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Monkey Dude.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Non Animated Sprites.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Rhinobot.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/RhinoBot Dust.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Ride Vine.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Rock.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Rock Bits.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Rock 2.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Rock Bits 2.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Spiked Log.bin");
        AIZObjectsSprite->LoadAnimation("Sprites/AIZ/Tulipon.bin");
	}

    if (!AIZBossSprite) {
        AIZBossSprite = new ISprite("Sprites/AIZ/Boss.gif", App);



        AIZBossSprite->LoadAnimation("Sprites/AIZ/Act 2 Background Tree.bin");
        AIZBossSprite->LoadAnimation("Sprites/AIZ/Act 2 Bomb Explosion.bin");
        AIZBossSprite->LoadAnimation("Sprites/AIZ/Act 2 Boss Small.bin");
        AIZBossSprite->LoadAnimation("Sprites/AIZ/Act 2 Ship Propeller.bin");
        AIZBossSprite->LoadAnimation("Sprites/AIZ/End Boss.bin");
        AIZBossSprite->LoadAnimation("Sprites/AIZ/Miniboss.bin");
        AIZBossSprite->LoadAnimation("Sprites/AIZ/Miniboss Flame.bin");
        AIZBossSprite->LoadAnimation("Sprites/AIZ/Miniboss Small.bin");
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

PUBLIC void Level_AIZ::LoadData() {
    LevelScene::LoadData();
    AIZObjectsSprite->LinkPalette(TileSprite);
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

        if (LevelTriggerFlag) {
            // Swap palette and preload Act 2
            if (TileSprite->GetPalette(0x31) != 0xEE4400) {
                TileSprite->SetPalette(0x31, 0xEE4400);
                TileSprite->SetPalette(0x32, 0xEE6600);
                TileSprite->SetPalette(0x33, 0xEEAA00);
                TileSprite->SetPalette(0x34, 0xEECC00);
    	        TileSprite->SetPalette(0x35, 0xEEEE22);
                TileSprite->SetPalette(0x36, 0xEEEEAA);

                TileSprite->UpdatePalette();

                StartAct2Preload();
            }

            if (Data->layers[4].OffsetY > -0x100)
                Data->layers[4].OffsetY--;

            if (Data->layers[4].OffsetY == -0x80)
                GoToNextAct();

            if (Frame % 6 == 0)
                Data->layers[4].OffsetX += 0x60;

            short firetileoffsets[16] = {
                0x100, 0xFF, 0xFE, 0xFB,
                0xF8,  0xF6, 0xF3, 0xF2,
                0xF1,  0xF2, 0xF3, 0xF6,
                0xF9,  0xFB, 0xFE, 0xFF
            };

            for (int i = 0; i < 20; i++) {
                Data->layers[4].TileOffsetY[i] = (firetileoffsets[(Frame / 4 + i * 2) & 0xF] - 0x100);
            }
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

        if (LevelTriggerFlag >> 0 & 1) {
            if (Data->layers[1].Tiles[0x270 + 0x3B * Data->layers[1].Width] != 0x0000) {
                for (int i = 0x3B; i < 0x53; i++) {
                    memset(&Data->layers[1].Tiles[0x270 + i * Data->layers[1].Width], 0x00, 8 * sizeof(short));
                }
            }
        }

        if (CameraX >= 0x2440) {
            if (WaterLevel < 0x618 && (LevelTriggerFlag >> 0 & 1)) {
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

            // Glittering Water
            // Find: \$([A-F0-9])([A-F0-9])([A-F0-9]),
            // Replace: 0x$3$3$2$2$1$1,\n
            for (int i = 0; i < 3; i++)
                TileSprite->SetPalette(0x3C + i, AIZ1_GlitteringWaterPalette[(Frame / 8 * 3) % 24 + i]);
        }

        // Flower / Log BG / Tree BG
        int palstart = 0x2F;
        if (CameraX < 0x2BB0 - App->WIDTH / 2) {
            TileSprite->SetPalette(palstart, 0xEE0022);
        }
        else if (CameraX < 0x2E50 - App->WIDTH / 2) {
            TileSprite->SetPalette(palstart, 0x444422);
        }
        else {
            TileSprite->SetPalette(palstart, 0x2200CC);
        }

        TileSprite->UpdatePalette();
    }
    else {
        if (Frame % 6 == 0) {
            TileSprite->RotatePaletteLeft(TileSprite->Palette + 0x3C, 4);
            TileSprite->RotatePaletteLeft(TileSprite->PaletteAlt + 0x3C, 4);

            if (CameraX < 0x3800) {
                TileSprite->SetPalette(0x24, AnPal_PalAIZ2_2[(Frame / 6 * 3) % 24]);
                TileSprite->SetPalette(0x28, AnPal_PalAIZ2_2[(Frame / 6 * 3) % 24 + 1]);
                TileSprite->SetPalette(0x3B, AnPal_PalAIZ2_2[(Frame / 6 * 3) % 24 + 2]);
            }
            else {
                TileSprite->SetPalette(0x24, AnPal_PalAIZ2_3[(Frame / 6 * 3) % 24]);
                TileSprite->SetPalette(0x28, AnPal_PalAIZ2_3[(Frame / 6 * 3) % 24 + 1]);
                TileSprite->SetPalette(0x3B, AnPal_PalAIZ2_3[(Frame / 6 * 3) % 24 + 2]);

                TileSprite->SetPalette(0x33, 0xCC0000);
                TileSprite->SetPalette(0x34, 0xAA0000);
                TileSprite->SetPalette(0x35, 0x880000);
                TileSprite->SetPalette(0x36, 0x660000);
                TileSprite->SetPalette(0x37, 0x440000);

                TileSprite->SetPalette(0x38, 0xEE8800);
                TileSprite->SetPalette(0x39, 0xEE6600);
                TileSprite->SetPalette(0x3A, 0xEE4400);
            }

            if (CameraX < 0x1C0)
                TileSprite->SetPalette(0x2E, TileSprite->GetPalette(0x4B));
            else
                TileSprite->SetPalette(0x2E, 0xEE00AA);
        }

        if (!(Frame & 1)) {
            if (CameraX < 0x3800)
                TileSprite->SetPalette(0x31, AnPal_PalAIZ2_4[Frame % 26]);
            else
                TileSprite->SetPalette(0x31, AnPal_PalAIZ2_5[Frame % 26]);

            TileSprite->UpdatePalette();
        }
    }

    LevelScene::Subupdate();
}

int CutsceneActTimer = 60;

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

        if (CameraX > 0x2D80) {
            CameraMinX = CameraX;
            CameraMaxX = 0x2F10;

            if (CameraY < 0x3B0) {
                CameraMinY = CameraY;
            }
        }
    }
    else {
        if (VisualAct == 1) {
            if (RoutineNumber == 69) {
                if (CutsceneActTimer > 0) {
                    CameraMinX = 0x10;
                    CameraMaxX = 0x10;
                    CutsceneActTimer--;
                }
                if (CutsceneActTimer == 0) {
                    CameraMinX = 0x0;
                    CameraMaxX = 0x7FFF;
                    CutsceneActTimer = -1;
                }

                if (CameraX > 0xF50 + 160 - App->WIDTH / 2) {
                    RoutineNumber = 0xCD;
                    AddNewObject(Obj_AIZMiniboss, 0x00, 0x11F0, 0x288, false, false);
                }
            }

            if (CameraX < 0x2A0) {
                CameraMinX = 0x0000;
                CameraMaxX = 0x2F00;
                CameraMinY = 0x000;
                CameraMaxY = 0x258;
            }
            else if (CameraX >= 0x980 && CameraX < 0xD60) {
                CameraMinY = 0x000;
                CameraMaxY = 0x590;
            }
            else if (CameraX >= 0xED0 && CameraX < 0xF90) {
                CameraMinY = 0x000;
                CameraMaxY = 0x2B8 + 224 - App->HEIGHT;
            }
            else if (CameraX >= 0xF90 && CameraX < 0x10E0 + 160 - App->WIDTH / 2) {
                CameraMaxX = 0x10E0 + 160 - App->WIDTH / 2;

                CameraMinY = 0x000;
                CameraMaxY = 0x2B8 + 224 - App->HEIGHT;
            }
            else if (CameraX >= 0x10E0 + 160 - App->WIDTH / 2) {
                CameraMinX = CameraX;
                CameraMaxX = 0x10E0 + 160 - App->WIDTH / 2;
                CameraMinY = 0x2B8 + 224 - App->HEIGHT;
                CameraMaxY = 0x2B8 + 224 - App->HEIGHT;
            }
            else if (VisualAct == 1) {
                CameraMaxY = 0x1F58;
            }
        }
        else {
            if (Player->EZX < 0x1370) {
                CameraMinY = 0x2B8 + 224 - App->HEIGHT;
                CameraMaxY = 0x2B8 + 224 - App->HEIGHT;
                CameraMaxX = 0xFFFF;
            }
            else {
                CameraMinY = 0;
                if (CameraMaxY == 0x2B8 + 224 - App->HEIGHT)
                    CameraMaxY = 0xFFFF;
                CameraMaxX = 0xFFFF;
            }
        }

        if (CameraX >= 0x3D00) {
            Data->layers[0].OffsetY = 0xA8;
            UseDeltaCamera = true;
        }
        else {
            Data->layers[0].OffsetY = 0;
        }

        int ToS3X = CameraX + App->WIDTH / 2 - 0xA0;
        if (Player->EZX >= 0x3F30) {
            CameraMinY = 0x15A;
        }
        if (ToS3X >= 0x4000) {
            CameraMaxY = 0x15A;
        }

        if (CameraX >= 0x4580 - App->WIDTH) {
            CameraX -= 0x300;
            Player->EZX -= 0x300;
        }
    }
}

PUBLIC void Level_AIZ::UpdateDiscord() {
    char imgkey[15];
    char levelname[50];
    sprintf(imgkey, "%d", ZoneID);
    sprintf(levelname, "%s%s%d", LevelNameDiscord, " Act ", VisualAct);
    Discord_UpdatePresence("Classic Mode:", levelname, imgkey);
}

PUBLIC void Level_AIZ::StartAct2Preload() {
    Act2Preload = new Level_AIZ(App, G, 2);

    Act2Preload->VisualWaterLevel = Act2Preload->WaterLevel = 0x528;
    Act2Preload->Frame = Frame;
    Act2Preload->WaterAnimationFrame = (Frame % 40) << 6;
    Act2Preload->VisualAct = 1;

    Act2Preload->SpecialSpawnPositionX = Player->EZX - 0x2F00;
    Act2Preload->SpecialSpawnPositionY = Player->EZY - 0x80;
    Act2Preload->RoutineNumber = 69;
    Act2Preload->LevelTriggerFlag = 0x00;

    Act2Preload->GiantRingModel = GiantRingModel;
    Act2Preload->ItemsSprite = ItemsSprite;
    Act2Preload->AnimalsSprite = AnimalsSprite;
    Act2Preload->ObjectsSprite = ObjectsSprite;
    Act2Preload->Objects2Sprite = Objects2Sprite;
    Act2Preload->Objects3Sprite = Objects3Sprite;
    Act2Preload->ExplosionSprite = ExplosionSprite;
    Act2Preload->WaterSprite = WaterSprite;

    Act2Preload->AIZObjectsSprite = AIZObjectsSprite;
    Act2Preload->AIZBossSprite = AIZBossSprite;
    for (int i = 0; i < 5; i++) {
        Act2Preload->KnuxSprite[i] = KnuxSprite[i];
    }
    Act2Preload->Player = Player;

    Act2Preload->LoadInBackground();
}

PUBLIC void Level_AIZ::GoToNextAct() {
    if (Act == 1 && VisualAct == 1) {
		Level_AIZ* NextAct = Act2Preload;
        if (!NextAct)
            NextAct = new Level_AIZ(App, G, 2);

        if (!Act2Preload)
            NextAct->LoadData();

        // Player->ControlLocked = false;
        // Player->ObjectControlled = 0x00;
        // Player->Action = ActionType::Normal;
        // Player->ChangeAnimation(Player->AnimationMap["Idle"]);
        for (int p = 0; p < PlayerCount; p++) {
            NextAct->Players[p] = Players[p];
            NextAct->Players[p]->Scene = NextAct;
        }
        NextAct->PlayerCount = PlayerCount;

        NextAct->LevelCardTimer = 6.0;
        NextAct->FadeTimer = -1;
        NextAct->FadeAction = 0;
        NextAct->FadeTimerMax = -1;

        App->NextScene = NextAct;
    }
    else if (Act == 2 && VisualAct == 1) {
        VisualAct = 2;
        ResultsTimer = 0;
        ShowResults = false;
        StopTimer = false;
        ResultsTimer = 0;
        TimerTotal = 0;
        TotalToAdd = 0;
        Player->ControlLocked = false;
        Player->ObjectControlled = 0;
        Player->Action = ActionType::Normal;

        LevelCardTimer = 0.0;
        FadeTimer = 0;
        FadeAction = 0;
        LevelCardHide = false;

        App->Audio->ClearMusic();
        App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
    }
    else if (Act == 2 && VisualAct == 2) {

    }
}

PUBLIC void Level_AIZ::Cleanup() {
    #define CLEANUP(name) if (name) { name->Cleanup(); delete name; name = NULL; }

    CLEANUP(AIZObjectsSprite);
    // CLEANUP(SpriteMap["AIZ Enemies"]);
    // CLEANUP(SpriteMap["AIZ Boss"]);

    LevelScene::Cleanup();
}
