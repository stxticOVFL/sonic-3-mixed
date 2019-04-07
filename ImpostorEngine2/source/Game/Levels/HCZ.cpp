#if INTERFACE
#include <Game/LevelScene.h>

class Level_HCZ : public LevelScene {
public:
    ISprite* WaterLine = NULL;

    int WallX = 0x4000000;
    int WallY = 0x600;
    int WallMoving = false;
    int WallStopped = false; //
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/HCZ.h>
#include <Game/Levels/MGZ.h>
#include <Engine/Diagnostics/Memory.h>

int DrainTimer = 0;
int HCZ_WaterTunnels[126] = {
    /*  Min X,  Min Y,  Max X,  Max Y,  X Velo, Y Velo, Player can influence which axis flag (Set = X, Clear = Y) */
    0x0380, 0x0580, 0x05A0, 0x05C0, 0x03F0, 0xFFE0, 0x0000,
    0x05A0, 0x0560, 0x0A80, 0x05C0, 0x03F0, 0xFFF0, 0x0000,
    0x1400, 0x0A80, 0x15A0, 0x0AC0, 0x0400, 0x0000, 0x0000,
    0x15A0,	0x0A40, 0x1960, 0x0AC0, 0x0400, 0xFFC0, 0x0000,
    0x1990,	0x0580, 0x19E0, 0x07F0, 0x0000, 0xF700, 0x0200,
    0x1990, 0x07F0, 0x19F0, 0x0878, 0xFEC0, 0xFD00, 0x0100,
    0x1990, 0x0878, 0x19F0, 0x08FD, 0x0140, 0xFD00, 0x0100,
    0x1990, 0x08FD, 0x19F0, 0x0978, 0xFEC0, 0xFD00, 0x0100,
    0x1990, 0x0978, 0x19F0, 0x0A10, 0x0100, 0xFD00, 0x0100,
    0x1960, 0x0A10, 0x19D0, 0x0A80, 0x0300, 0xFD80, 0x0100,
    0x2B00, 0x0800, 0x2C20, 0x0840, 0x0400, 0x0000, 0x0000,
    0x2C20,	0x07B0, 0x2EE0, 0x0840, 0x0400, 0xFFC0, 0x0000,
    0x2EE0,	0x0790, 0x2F10, 0x0800, 0x0300, 0xFD00, 0x0100,
    0x2F10, 0x0700, 0x2F30, 0x0790, 0x0200, 0xFD00, 0x0100,
    0x2F30, 0x0700, 0x2F70, 0x0700, 0x0100, 0xFD00, 0x0100,
    0x2F30, 0x0480, 0x2F70, 0x0700, 0x0000, 0xF700, 0x0200,

    0x3A00, 0x0800, 0x3AA0, 0x0840, 0x0400, 0x0000, 0x0000,
    0x3AA0, 0x07C0, 0x3F00, 0x0840, 0x0400, 0x0000, 0x0000,
};
int copymake[4 * 16] = {
    // from     to
    0x80, 0x80, 0, 0,
    0x80, 0x80, 8, 0,
    0x80, 0x80, 16, 0,
    0xF0, 0x10, 24, 0,

    0x98, 0x88, 0, 8,
    0xA0, 0x88, 8, 8,
    0xA8, 0x88, 16, 8,
    0xF0, 0x18, 24, 8,

    0x90, 0x88, 0, 16,
    0x98, 0x88, 8, 16,
    0xA0, 0x88, 16, 16,
    0xF0, 0x18, 24, 16,

    0xB8, 0x28, 0, 24,
    0xB8, 0x28, 8, 24,
    0xB8, 0x28, 16, 24,
    0x178, 0x30, 24, 24,
};

#define ADD_OBJECT() ObjectProp op; op.X = X; op.Y = Y; op.ID = ID; op.SubType = SubType; op.LoadFlag = PRIORITY; op.FlipX = FLIPX; op.FlipY = FLIPY; ObjectPropCount++; ObjectProps.push_back(op); Object* obj = GetNewObjectFromID(ID); if (obj) { obj->G = G; obj->App = App; obj->Scene = this; obj->InitialX = X; obj->InitialY = Y; obj->FlipX = FLIPX == 1; obj->FlipY = FLIPY == 1; while (!SpriteMapIDs.at(ID)) ID--; obj->Sprite = SpriteMapIDs.at(ID); obj->SubType = SubType; obj->Create(); ObjectCount++; Objects.push_back(obj); }

PUBLIC Level_HCZ::Level_HCZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 2;
    VisualAct = Act = act;
	sprintf(ZoneLetters, "HCZ");

	if (SaveGame::CurrentMode >= 1)
	{
		if (Act == 1) {
			Str_TileConfigBin = "Mixed/Stages/HCZ1/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/HCZ1/Scene.bin";
			Str_TileSprite = "Mixed/Stages/HCZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/HCZ1/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/HCZ1/Stageconfig.bin";

			WaterLine = new ISprite("HCZ/AniTiles2.gif", App);
		}
		else {
			Str_TileConfigBin = "Mixed/Stages/HCZ2/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/HCZ2/Scene.bin";
			Str_TileSprite = "Mixed/Stages/HCZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/HCZ2/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/HCZ2/Stageconfig.bin";
		}
	}
	else
	{
		if (Act == 1) {
			Str_TileConfigBin = "Classic/Stages/HCZ1/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/HCZ1/Scene.bin";
			Str_TileSprite = "Classic/Stages/HCZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/HCZ1/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/HCZ1/Stageconfig.bin";

			WaterLine = new ISprite("HCZ/AniTiles2.gif", App);
		}
		else {
			Str_TileConfigBin = "Classic/Stages/HCZ2/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/HCZ2/Scene.bin";
			Str_TileSprite = "Classic/Stages/HCZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/HCZ2/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/HCZ2/Stageconfig.bin";
		}
	}

    sprintf(LevelName, "HYDROCITY");
    sprintf(LevelNameDiscord, "Hydrocity");

    if (Act == 1) {
        // PlayerStartX = 0x0280;
        // PlayerStartY = 0x0000;

        //PlayerStartX = 0x32E0;
        //PlayerStartY = 0x02EC;
    }
    else {
        // PlayerStartX = 0x0170;
        // PlayerStartY = 0x082C;

        // PlayerStartX = 0x1A2E;
        // PlayerStartY = 0x056C;

        VisualWaterLevel = 0x700;
        WaterLevel = 0x700;
    }

	AddNewDebugObjectID(Obj_HCZSnakeBlocks);
	AddNewDebugObjectID(Obj_Blastoid);
	AddNewDebugObjectID(Obj_TurboSpiker);
	AddNewDebugObjectID(Obj_Buggernaut);
	AddNewDebugObjectID(Obj_MegaChomper);
	AddNewDebugObjectID(Obj_Jawz);
	AddNewDebugObjectID(Obj_Pointdexter);
	AddNewDebugObjectID(Obj_BigShaker);
	AddNewDebugObjectID(Obj_ScrewMobile);
}

PUBLIC void Level_HCZ::Init() {
	PlayMusic(Act, SaveGame::CurrentMode == 0 ? (Act == 1 ? 0 : 407013) : (Act == 1 ? 942525 : 0), SaveGame::CurrentMode, SaveGame::CurrentMode == 0 ? (Act == 1 ? 0xA0 : 0xE0) : 0xFF);

    LevelScene::Init();

    bool Thremixed = false;
    if (Thremixed) {
        IResource* StageBin = IResources::Load("Objects/HCZSetup.bin");
        if (StageBin) {
            IStreamer reader(StageBin);
			delete[] reader.ReadBytes(128 * 4);

            uint8_t* n = reader.ReadBytes(128 * 4);
            memcpy(TileSprite->PaletteAlt + 128, n, 128 * 4);
            memcpy(SpriteMap["HCZ"]->PaletteAlt + 128, n, 128 * 4);
            memcpy(SpriteMap["HCZ Enemies"]->PaletteAlt + 128, n, 128 * 4);
            memcpy(SpriteMap["HCZ Boss"]->PaletteAlt + 128, n, 128 * 4);
            memcpy(SpriteMap["HCZ Boss2"]->PaletteAlt + 128, n, 128 * 4);
            if (Act == 1)
                memcpy(WaterLine->PaletteAlt + 128, n, 128 * 4);
            delete[] n;

            n = reader.ReadBytes(96 * 4);
            memcpy(SpriteMap["HCZ"]->PaletteAlt, n, 96 * 4);
            memcpy(SpriteMap["HCZ Enemies"]->PaletteAlt, n, 96 * 4);
            memcpy(SpriteMap["HCZ Boss"]->PaletteAlt, n, 96 * 4);
            memcpy(SpriteMap["HCZ Boss2"]->PaletteAlt, n, 96 * 4);
            memcpy(ItemsSprite->PaletteAlt, n, 96 * 4);
            memcpy(ObjectsSprite->PaletteAlt, n, 96 * 4);
            for (int p = 0; p < 3; p++)
                if (Player->Sprites[p])
                    memcpy(Player->Sprites[p]->PaletteAlt, n, 96 * 4);
			delete[] n;

            TileSprite->SetPaletteAlt(0, 0xFF00FF);

            TileSprite->Paletted = 2;
            SpriteMap["HCZ"]->Paletted = 2;
            SpriteMap["HCZ Enemies"]->Paletted = 2;
            SpriteMap["HCZ Boss"]->Paletted = 2;
            SpriteMap["HCZ Boss2"]->Paletted = 2;
            ItemsSprite->Paletted = 2;
            ObjectsSprite->Paletted = 2;
            if (Act == 1)
                WaterLine->Paletted = 2;

            TileSprite->UpdatePalette();
            SpriteMap["HCZ"]->UpdatePalette();
            SpriteMap["HCZ Enemies"]->UpdatePalette();
            SpriteMap["HCZ Boss"]->UpdatePalette();
            SpriteMap["HCZ Boss2"]->UpdatePalette();
            ItemsSprite->UpdatePalette();
            ObjectsSprite->UpdatePalette();
            if (Act == 1)
                WaterLine->UpdatePalette();

            IResources::Close(StageBin);
        }
    }

    if (Act == 2) {
        bool EasyMode = false;
        if (EasyMode) {
            int X = 0x970;
            int Y = 0x620;
            int ID = 0x3C;
            int SubType = 0;
            int PRIORITY = false;
            int FLIPX = 0;
            int FLIPY = 0;
            ADD_OBJECT();
        }
    }
}

PUBLIC void Level_HCZ::RestartStage(bool doActTransition, bool drawBackground) {
    App->Audio->ClearMusic();
    App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

    LevelScene::RestartStage(doActTransition, drawBackground);

    WallX = 0x4000000;
    WallY = 0x600;
    WallMoving = false;
    WallStopped = false;
    ShakeTimer = 0;

    if (Act == 1) {
        if (Checkpoint == -1)
            for (int p = 0; p < PlayerCount; p++)
                Players[p]->Action = ActionType::Peril;
    }
    else {
        if (Checkpoint == -1 && RoutineNumber != 0x69) {
            VisualWaterLevel = 0x700;
            WaterLevel = 0x700;
        }
        else if (Checkpoint == -1 && RoutineNumber == 0x69) {

        }
    }
}

PUBLIC void Level_HCZ::FinishResults() {
    if (VisualAct == 1) {
        LevelScene::FinishResults();
    }
    else {
        FadeAction = FadeActionType::NEXT_ZONE;
        FadeTimerMax = 90;
        FadeMax = 0x140;
        G->FadeToWhite = false;
    }
}
PUBLIC void Level_HCZ::GoToNextAct() {
    if (VisualAct == 1) {
        Level_HCZ* NextAct = new Level_HCZ(App, G, 2);

        Player->ControlLocked = false;
        Player->ObjectControlled = 0x00;
        Player->Action = ActionType::Normal;
        Player->ChangeAnimation(Player->AnimationMap["Idle"]);
        TransferCommonLevelData(NextAct);
        NextAct->SpriteMap["HCZ"] = SpriteMap["HCZ"];
        NextAct->SpriteMap["HCZ Enemies"] = SpriteMap["HCZ Enemies"];
        NextAct->SpriteMap["HCZ Boss"] = SpriteMap["HCZ Boss"];
        NextAct->SpriteMap["HCZ Boss2"] = SpriteMap["HCZ Boss2"];
        // Enable Title Card with no fade-in
        NextAct->LevelCardTimer = 0.0;
        NextAct->FadeTimer = 0;
        NextAct->FadeAction = 0;
        NextAct->LevelCardHide = false;
        // Transfer over current frame
        NextAct->Frame = Frame;
        NextAct->WaterAnimationFrame = (Frame % 40) << 6;
        // Set water level
        NextAct->VisualWaterLevel = 0x6A0;
        NextAct->WaterLevel = 0x6A0;
        // Set player spawn position relative to their previous position
        NextAct->SpecialSpawnPositionX = Player->EZX - 0x3600;
        NextAct->SpecialSpawnPositionY = Player->EZY;
        NextAct->RoutineNumber = 0x69;

        App->NextScene = NextAct;
    }
    else {
        Level_MGZ* NextAct = new Level_MGZ(App, G, 1);
        TransferCommonLevelData(NextAct);
        App->NextScene = NextAct;
    }
}

PUBLIC void Level_HCZ::AssignSpriteMapIDs() {
    LevelScene::AssignSpriteMapIDs();

	SpriteMapIDs.at(0x2F) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x33) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x36) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x38) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x39) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x3A) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x51) = SpriteMap["HCZ"];

	SpriteMapIDs.at(0x67) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x6C) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x6D) = SpriteMap["HCZ"];

	SpriteMapIDs.at(0x93) = SpriteMap["HCZ Enemies"];
	SpriteMapIDs.at(0x99) = SpriteMap["HCZ Boss"];
	SpriteMapIDs.at(0x9A) = SpriteMap["HCZ Boss2"];
    
    SpriteMapIDs.at(0x40F) = SpriteMap["HCZ Enemies"];
}

PUBLIC void Level_HCZ::LoadZoneSpecificSprites() {
	if (!SpriteMap["HCZ"]) {
		SpriteMap["HCZ"] = new ISprite("HCZ/Objects.gif", App);
		SpriteMap["HCZ"]->Print = true;

		SpriteMap["HCZ"]->LoadAnimation("HCZ/Button.bin");
		SpriteMap["HCZ"]->LoadAnimation("HCZ/Fan.bin");
		SpriteMap["HCZ"]->LoadAnimation("HCZ/HandLauncher.bin");
		SpriteMap["HCZ"]->LoadAnimation("HCZ/BreakBar.bin");
		SpriteMap["HCZ"]->LoadAnimation("HCZ/Decoration.bin");
		SpriteMap["HCZ"]->LoadAnimation("HCZ/Platform.bin");
		SpriteMap["HCZ"]->LoadAnimation("HCZ/Wake.bin");
		SpriteMap["HCZ"]->LoadAnimation("HCZ/Bridge.bin");
	}
	if (!SpriteMap["HCZ Enemies"]) {
		SpriteMap["HCZ Enemies"] = new ISprite("HCZ/Enemies.gif", App);
		SpriteMap["HCZ Enemies"]->LoadAnimation("HCZ/Blastoid.bin");
		SpriteMap["HCZ Enemies"]->LoadAnimation("HCZ/Buggernaut.bin");
		SpriteMap["HCZ Enemies"]->LoadAnimation("HCZ/TurboSpiker.bin");
		SpriteMap["HCZ Enemies"]->LoadAnimation("HCZ/MegaChomper.bin");
		SpriteMap["HCZ Enemies"]->LoadAnimation("HCZ/Pointdexter.bin");
		SpriteMap["HCZ Enemies"]->LoadAnimation("HCZ/Jawz.bin");
	}
	if (!SpriteMap["HCZ Boss"]) {
		SpriteMap["HCZ Boss"] = new ISprite("HCZ/Boss.gif", App);
		SpriteMap["HCZ Boss"]->LoadAnimation("HCZ/BigShaker.bin");
	}
	if (!SpriteMap["HCZ Boss2"]) {
		SpriteMap["HCZ Boss2"] = new ISprite("HCZ/Objects2.gif", App);
		SpriteMap["HCZ Boss2"]->LoadAnimation("HCZ/ScrewMobile.bin");
	}

    if (!KnuxSprite[0]) {
		if (SaveGame::CurrentMode >= 1)
		{
			KnuxSprite[0] = new ISprite("PlayersMixed/Knux1.gif", App);
			KnuxSprite[1] = new ISprite("PlayersMixed/Knux2.gif", App);
			KnuxSprite[2] = new ISprite("PlayersMixed/Knux3.gif", App);
			KnuxSprite[3] = new ISprite("PlayersMixed/KnuxCutsceneAIZ.gif", App);
			KnuxSprite[4] = new ISprite("PlayersMixed/KnuxCutsceneHPZ.gif", App);

			KnuxSprite[0]->LoadAnimation("PlayersMixed/Knux.bin");
		}
		else
		{
			KnuxSprite[0] = new ISprite("PlayersClassic/Knux1.gif", App);
			KnuxSprite[1] = new ISprite("PlayersClassic/Knux2.gif", App);
			KnuxSprite[2] = new ISprite("PlayersClassic/Knux3.gif", App);
			KnuxSprite[3] = new ISprite("PlayersClassic/KnuxCutsceneAIZ.gif", App);
			KnuxSprite[4] = new ISprite("PlayersClassic/KnuxCutsceneHPZ.gif", App);

			KnuxSprite[0]->LoadAnimation("PlayersClassic/Knux.bin");
		}
        KnuxSprite[1]->LinkAnimation(KnuxSprite[0]->Animations);
        KnuxSprite[2]->LinkAnimation(KnuxSprite[0]->Animations);
        KnuxSprite[3]->LinkAnimation(KnuxSprite[0]->Animations);
        KnuxSprite[4]->LinkAnimation(KnuxSprite[0]->Animations);
    }
}

PUBLIC void Level_HCZ::Cleanup() {
    #define CLEANUP(name) if (name) { name->Cleanup(); delete name; name = NULL; }

    CLEANUP(WaterLine);
    CLEANUP(SpriteMap["HCZ"]);
    CLEANUP(SpriteMap["HCZ Enemies"]);
    CLEANUP(SpriteMap["HCZ Boss"]);

    LevelScene::Cleanup();
}

PUBLIC void Level_HCZ::RenderAboveBackground() {
    if (Act == 1) {
        if (WaterLine) {
            int Y = 0x200 - (CameraY >> 2);
            int WY = VisualWaterLevel - CameraY;


            int xBase = CameraX >> 2;
            for (int X = xBase; X < xBase + App->WIDTH + 0x10; X += 0x10) {
                if (Y < WY) {
                    if (WY - Y < 128)
                        G->DrawSprite(WaterLine, 0, 0, 16, 112, (X & ~0xF) - xBase, Y, 0, IE_NOFLIP, 0, 0, 16, WY - Y);
                    else
                        G->DrawSprite(WaterLine, 0, 0, 16, 112, (X & ~0xF) - xBase, Y, 0, IE_NOFLIP, 0, 0, 16, 128);
                }
                else if (Y - WY > 0) {
                    if (Y - WY < 128)
                        G->DrawSprite(WaterLine, 0, 112, 16, 112, (X & ~0xF) - xBase, WY, 0, IE_NOFLIP, 0, 0, 16, Y - WY);
                    else
                        G->DrawSprite(WaterLine, 0, 112, 16, 112, (X & ~0xF) - xBase, Y - 128, 0, IE_NOFLIP, 0, 0, 16, 128);
                }
            }
        }
    }
}
PUBLIC void Level_HCZ::RenderAboveForeground() {
    if (SaveGame::CurrentMode == 1) {
        if (Act == 2) {
            for (int i = 0; i < sizeof(copymake) / sizeof(int); i += 4) {
                for (int x = copymake[i]; x < copymake[i] + 8; x++) {
                    for (int y = copymake[i + 1]; y < copymake[i + 1] + 8; y++) {
                        int tile = Data->Layers[4].Tiles[x + y * Data->Layers[4].Width];
                        int flipX = ((tile >> 10) & 1);
                        int flipY = ((tile >> 11) & 1);
                        tile = tile & 0x3FF;

                        G->DrawSprite(TileSprite, 0, tile, 8 + (WallX >> 16) - CameraX + ((x - copymake[i] + copymake[i + 2]) << 4), 8 + WallY - CameraY + ((y - copymake[i + 1] + copymake[i + 3]) << 4), 0, (flipX * IE_FLIPX) | (flipY * IE_FLIPY));
                    }
                }
            }
        }
    }
}

PUBLIC void Level_HCZ::RenderEverything() {
    LevelScene::RenderEverything();
}

PUBLIC bool Level_HCZ::CollisionAt(int probeX, int probeY, int* angle, int anglemode, IPlayer* player) {
    if (probeX >= (WallX >> 16) &&
        probeY >= WallY &&
        probeX <  (WallX >> 16) + 0x200 &&
        probeY <  WallY + 0x200 && player) {
        if (player->EZX < 0xCD0 && player->EZY > 0x5A0)
            return true;
    }

    if (player) {
        if (ZoneID == 2 && player->Ground && abs(player->GroundSpeed) > 0x700 && player->Angle == 0 && !player->Underwater && (player->Y >> 16) < WaterLevel && CanWaterRun) {
            if (probeY >= WaterLevel) {
                player->WaterRunning = true;
    			if (angle) {
    				*angle = 0;
    			}
                return true;
            }
        }
        else {
            player->WaterRunning = false;
        }
    }

    return LevelScene::CollisionAt(probeX, probeY, angle, anglemode, player);
}

PUBLIC void Level_HCZ::EarlyUpdate() {
    if (Act == 1) {
        // Do palette stuffs
        if (SaveGame::CurrentMode == 1) {
            if (Frame % 4 == 0) {
                TileSprite->RotatePaletteRight(TileSprite->Palette + 0xB0, 7);
                TileSprite->UpdatePalette();
            }
        }
        else {
            // Flip color of beginning water area tiles based on camera.
            if (CameraX < 0x910 && CameraY >= 0x406) {
                // Dark green
                TileSprite->SetPalette(0x38, 0x008866); // lightest
                TileSprite->SetPalette(0x39, 0x004422); // mid
                TileSprite->SetPalette(0x3A, 0x002222); // darkest
            }
            else {
                // White, used for candles in BG.
                TileSprite->SetPalette(0x38, 0xEEEECC); // lightest
                TileSprite->SetPalette(0x39, 0xEECCAA); // mid
                TileSprite->SetPalette(0x3A, 0xAA8800); // darkest
            }

            if (Frame % 8 == 0) {
                TileSprite->RotatePaletteLeft(TileSprite->Palette + 0x23, 4);
                TileSprite->RotatePaletteLeft(TileSprite->PaletteAlt + 0x23, 4);
            }
            TileSprite->UpdatePalette();
        }

        if (Player->EZX < 0x800) {
            WaterLevel = 0x500;
            VisualWaterLevel = 0x7FFF;
        }
        else if (Player->EZX < 0x35B0) {
            WaterLevel = 0x680;
            VisualWaterLevel = 0x680;
        }
        else {
            WaterLevel = 0x6A0;
            VisualWaterLevel = 0x6A0;
        }
    }
    else if (Act == 2) {
        // Do palette stuffs
        if (SaveGame::CurrentMode == 1) {
            /*// rotate left
            Uint32 temp = TileSprite->GetPalette(0xB0);
            for (int i = 0; i < 7 - 1; i++) {
                TileSprite->SetPalette(0xB0 + i, TileSprite->GetPalette(0xB0 + i + 1));
            }
            TileSprite->SetPalette(0xB0 + 7 - 1, temp);
            //*/

            // rotate right
            Uint32 temp = TileSprite->GetPalette(0xB0 + 7 - 1);
            for (int i = 7 - 1; i >= 1; i--) {
                TileSprite->SetPalette(0xB0 + i, TileSprite->GetPalette(0xB0 + i - 1));
            }
            TileSprite->SetPalette(0xB0, temp);

            TileSprite->UpdatePalette();
            //*/
        }

        // Slides that make you Flume
        for (int p = 0; p < PlayerCount; p++) {
            IPlayer* Player = Players[p];
            if (Player->Action == ActionType::Dead) continue;

            if (!Player->Ground) continue;
            if (Player->Layer != 1) continue;

            if (Player->EZX >= 0x2CC0 && Player->EZX < 0x3100) {
                if (Player->EZY >= 0x0000 && Player->EZY < 0x0500) {
                    Player->Action = ActionType::Slide;
                }
            }
            else if (Player->EZX >= 0x1240 && Player->EZX < 0x1500) {
                if (Player->EZY >= 0x0000 && Player->EZY < 0x0460) {
                    Player->Action = ActionType::Slide;
                }
            }
        }

        // Wall shit (part 1)
        if (Player->EZX >= 0x0680 && !WallStopped) {
            WallMoving = true;
        }
        if (WallStopped && !WallMoving && ShakeTimer == -1) {
            ShakeTimer = 0;
        }
        if (WallMoving) {
            if (Player->EZX >= 0x0A88)
                WallX += 0x14000;
            else
                WallX += 0xE000;

            ShakeTimer = -1;

            if (!(Frame & 0xF)) {
                Sound::Play(Sound::SFX_RUMBLE);
            }

            if (WallX >= 0x0A000000 && !WallStopped) {
                WallX = 0x0A000000;
                WallMoving = false;
                WallStopped = true;
                ShakeTimer = 20;
                Sound::Play(Sound::SFX_IMPACT4);
            }
            else if (Player->EZX >= 0xCD0 || (Player->EZY < 0x5A0 && Player->Action != ActionType::Dead)) {
                WallMoving = false;
                WallStopped = true;
                ShakeTimer = 0;
                WallX = 0x0A000000;
            }
        }
        for (int p = 0; p < PlayerCount; p++) {
            IPlayer* Player = Players[p];
            if (Player->Action == ActionType::Dead) continue;

            if (Player->EZX >= 0xCD0 || Player->EZY < 0x5A0)
                continue;

            int EFPos = Player->EZY;
            if (Player->Ground)
                EFPos += 8;

            if (EFPos >= WallY &&
                EFPos <  WallY + 0x200) {
                if (Player->EZX >= (WallX >> 16) &&
                    Player->EZX - 11 + (Player->XSpeed >> 8) <  (WallX >> 16) + 0x200) {
                    Player->EZX = (WallX >> 16) + 0x200 + 11;
                    if (Player->XSpeed < 0)
                        Player->XSpeed = 0;
                }
            }

            if (Player->YSpeed < 0) {
                if (Player->EZX + 9 >= (WallX >> 16) &&
                    Player->EZX - 9 <  (WallX >> 16) + 0x200) {
                    if (Player->EZY - Player->H / 2 < WallY + 0x200) {
                        Player->EZY = WallY + 0x200 + Player->H / 2;
                        Player->YSpeed = 0;
                        Player->FlyFlag = 8;
                    }
                }
            }
        }

        Data->Layers[3].OffsetX = WallX >> 16;
        Data->Layers[3].OffsetY = WallY;

        // Boss water and camera management
        if (Player->Action != ActionType::Dead) {
            if (Player->EZX > 0x3F00 && Player->EZY > 0x6A0) {
                if (WaterLevel < 0x7E0) {
                    WaterLevel++;
                    VisualWaterLevel = WaterLevel;
                }

                int ToMax = 0x820 - App->HEIGHT;
                if (CameraMaxY > CameraY)
                    CameraMaxY = CameraY;

                if (CameraMaxY > ToMax)
                    CameraMaxY--;

                if (CameraMaxY < ToMax)
                    CameraMaxY = ToMax;

                CameraMinY = ToMax;

                if (CameraX < 0x4000) {
                    CameraMinX = CameraX;
                }
                else if (CameraMinX < 0x4000) {
                    // Push Main Boss theme onto stack
                    // App->Audio->PushMusic(Sound::SoundBank[0xF0], true, 264600);
                    App->Audio->PushMusic(Sound::SoundBank[0xF0], true, 0);
                    // Push Mini Boss theme onto stack
                    //App->Audio->PushMusic(Sound::SoundBank[0xF1], true, 276105);
                    CameraMinX = 0x4000;
                    CameraMaxX = 0x4000 + 0x190 - App->WIDTH;
                    if (CameraMaxX < 0x4000)
                        CameraMaxX = 0x4000;
                }
            }
            else if (Player->EZX > 0x4000 && Player->EZY < 0x6A0) {
                if (WaterLevel > 0x360) {
                    WaterLevel = 0x360;
                    VisualWaterLevel = WaterLevel;
                }

                int offX = App->WIDTH / 2 - 0xA0;
                // int offY = App->HEIGHT / 2 - 0x70;

                if (CameraX > 0x44E0 - offX) {
                    int ToMax = 0x398 - App->HEIGHT;
                    if (CameraMaxY > CameraY)
                        CameraMaxY = CameraY;

                    if (CameraMaxY > ToMax)
                        CameraMaxY--;

                    if (CameraMaxY < ToMax)
                        CameraMaxY = ToMax;

                    CameraMinY = ToMax;

                    if (CameraX < 0x4540) {
                        CameraMinX = CameraX;
                    }
                    else {
                        CameraMinX = 0x4540;
                        CameraMaxX = 0x4540 + 0x190 - App->WIDTH;
                        if (CameraMaxX < 0x4540)
                            CameraMaxX = 0x4540;
                    }
                }
            }
        }
    }

    for (int p = 0; p < PlayerCount; p++) {
        IPlayer* Player = Players[p];
        if (Player->Action == ActionType::Dead) continue;

        bool Found = false;
        if (Player->Action != ActionType::InStreamGrab && Player->Action != ActionType::Hurt) {
            if (Act == 1) {
                int px1 = Player->EZX;
                int px2 = Player->EZX;
                int py1 = Player->EZY;
                int py2 = Player->EZY;

                if (LevelTriggerFlag >> 0 & 1) {
                    for (int i = 0; i < 2; i++) {
                        if (px1 >= HCZ_WaterTunnels[i * 7 + 0] &&
                            py1 >= HCZ_WaterTunnels[i * 7 + 1] &&
                            px2 <  HCZ_WaterTunnels[i * 7 + 2] &&
                            py2 <  HCZ_WaterTunnels[i * 7 + 3]) {
                            Player->Action = ActionType::InStream;
                            Player->XSpeed = HCZ_WaterTunnels[i * 7 + 4] << 1;
                            Player->YSpeed = HCZ_WaterTunnels[i * 7 + 5] << 1;
                            Player->Ground = false;
                            Found = true;
                        }
                    }
                }

                for (int i = 2; i < 16; i++) {
                    if (px1 >= HCZ_WaterTunnels[i * 7 + 0] &&
                        py1 >= HCZ_WaterTunnels[i * 7 + 1] &&
                        px2 <  HCZ_WaterTunnels[i * 7 + 2] &&
                        py2 <  HCZ_WaterTunnels[i * 7 + 3]) {
                        if ((HCZ_WaterTunnels[i * 7 + 6] & 0x200) == 0x200) {
                            if (Player->Action == ActionType::InStream) {
                                Player->Action = ActionType::InStream;
                                Player->XSpeed = HCZ_WaterTunnels[i * 7 + 4] << 1;
                                Player->YSpeed = HCZ_WaterTunnels[i * 7 + 5] << 1;
                                Player->Ground = false;
                                Found = true;
                            }
                        }
                        else {
                            Player->Action = ActionType::InStream;
                            Player->XSpeed = HCZ_WaterTunnels[i * 7 + 4] << 1;
                            Player->YSpeed = HCZ_WaterTunnels[i * 7 + 5] << 1;
                            Player->Ground = false;
                            Found = true;
                        }
                    }
                }

                if (px1 >= 0x2FA0 &&
                    px2 <  0x3300) {
                    LevelTriggerFlag &= ~(1 << 0);
                }
            }
            else {
                int px1 = Player->EZX;
                int px2 = Player->EZX;
                int py1 = Player->EZY;
                int py2 = Player->EZY;

                for (int i = 16; i < 18; i++) {
                    if (px1 >= HCZ_WaterTunnels[i * 7 + 0] &&
                        py1 >= HCZ_WaterTunnels[i * 7 + 1] &&
                        px2 <  HCZ_WaterTunnels[i * 7 + 2] &&
                        py2 <  HCZ_WaterTunnels[i * 7 + 3]) {
                        if ((HCZ_WaterTunnels[i * 7 + 6] & 0x200) == 0x200) {
                            if (Player->Action == ActionType::InStream) {
                                Player->XSpeed = HCZ_WaterTunnels[i * 7 + 4] << 1;
                                Player->YSpeed = HCZ_WaterTunnels[i * 7 + 5] << 1;
                                Player->Ground = false;
                                Found = true;
                            }
                        }
                        else {
                            Player->Action = ActionType::InStream;
                            Player->XSpeed = HCZ_WaterTunnels[i * 7 + 4] << 1;
                            Player->YSpeed = HCZ_WaterTunnels[i * 7 + 5] << 1;
                            Player->Ground = false;
                            Found = true;
                        }
                    }
                }
            }
            if (!Found && Player->Action == ActionType::InStream) {
                Player->Action = ActionType::Peril;
                Player->XSpeed >>= 1;
            }
        }
    }

    LevelScene::EarlyUpdate();
}
PUBLIC void Level_HCZ::Subupdate() {
    LevelScene::Subupdate();

    // Wall shit (part 2)
    if (Act == 2) {
        Data->Layers[3].Visible = true;
        Data->Layers[3].Flags = 0 | 2 | 4;

        for (int p = 0; p < PlayerCount; p++) {
            IPlayer* Player = Players[p];
            if (Player->Action == ActionType::Dead) continue;

            if (Player->EZX >= 0xCD0 || Player->EZY < 0x5A0)
                continue;

            int EFPos = Player->EZY;
            if (Player->Ground)
                EFPos += 8;

            if (EFPos >= WallY &&
                EFPos <  WallY + 0x200) {
                if (Player->EZX >= (WallX >> 16) &&
                    Player->EZX - 11 + (Player->XSpeed >> 8) <  (WallX >> 16) + 0x200) {
                    Player->EZX = (WallX >> 16) + 0x200 + 11;
                    if (Player->XSpeed < 0)
                        Player->XSpeed = 0;
					if (Player->GroundSpeed < 0)
						Player->GroundSpeed = 0;
                }
            }

            if (Player->YSpeed < 0) {
                if (Player->EZX + 9 >= (WallX >> 16) &&
                    Player->EZX - 9 <  (WallX >> 16) + 0x200) {
                    if (Player->EZY - Player->H / 2 < WallY + 0x200) {
                        Player->EZY = WallY + 0x200 + Player->H / 2;
                        Player->YSpeed = 0;
                        Player->FlyFlag = 8;
                    }
                }
            }
        }

        if (RoutineNumber == 0x69) {
            DrainTimer++;

            int offX = App->WIDTH / 2 - 0xA0;
            int offY = App->HEIGHT / 2 - 0x70;
            if (DrainTimer >= 90 - 2) {
                if (CameraY < 0x7CC - offY) {
                    CameraY += 2;
                    CameraMinY = CameraY;
                    CameraMaxY = 0xFFFF;

                    VisualWaterLevel--;
                }

                for (int p = 0; p < PlayerCount; p++) {
                    IPlayer* Player = Players[p];
                    if (Player->Action == ActionType::Dead) continue;

                    Player->EZX = CameraX + App->WIDTH / 2 + (IMath::sinHex((DrainTimer << 2) + p * 32) >> 10);
                    Player->SubY = 0x6F00000 + (DrainTimer - 90) * 0x18000;
                    Player->Action = ActionType::Normal;
                    Player->ChangeAnimation2(Player->AnimationMap["Fan"], (DrainTimer >> 1) % 8);
                    Player->DisplayFlip = 1;
                    Player->ObjectControlled = 0x80;
                    Player->UnderwaterTimer = 1800;
                }

                if (DrainTimer >= 90 + 157 + 36) {
                    RoutineNumber = 0;
                    CameraMinY = 0;
                    CameraMaxY = 0xFFFF;
                    CameraMaxX = 0x6000;

                    VisualWaterLevel = 0x700;
                    WaterLevel = 0x700;

                    for (int p = 0; p < PlayerCount; p++) {
                        IPlayer* Player = Players[p];
                        if (Player->Action == ActionType::Dead) continue;

                        Player->Action = ActionType::Normal;
                        Player->ObjectControlled = 0x0;
                    }
                }
            }
            else {
                CameraMinX = 0x0080 - offX;
                CameraMaxX = 0x0080 - offX;
                CameraMinY = 0x638 - offY;
                CameraMaxY = 0x638 - offY;
            }
        }
    }
}

PUBLIC void Level_HCZ::HandleCamera() {
    int offX = App->WIDTH / 2 - 0xA0;
    int offY = App->HEIGHT / 2 - 0x70;
    if (Act == 1) {
        if (Player->EZX > 0x35B0) {
            if (CameraMinY < 0x300)
                CameraMinY = 0x300;

            if (Player->EZY > 0x600)
                CameraMinY = CameraY;
            else
                CameraMinX = CameraX;
            CameraMaxX = 0x3680 - offX;

            CameraMaxY = 0x638 - offY;
			if (CameraMinY > CameraMaxY)
				CameraMinY = CameraMaxY;
        }
    }
    else if (Act == 2) {
        if (RoutineNumber == 0x69 && DrainTimer < 45) {
            CameraMinX = 0x0080 - offX;
            CameraMaxX = 0x0080 - offX;
            CameraMinY = 0x638 - offY;
            CameraMaxY = 0x638 - offY;
        }
    }

    LevelScene::HandleCamera();
}
