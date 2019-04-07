#if INTERFACE
#include <Game/LevelScene.h>

class Level_CNZ : public LevelScene {
public:
    ISprite* CNZObjectsSprite = NULL;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/CNZ.h>
#include <Game/Levels/ICZ.h>

Uint32 AnPal_PalCNZ_1[48] = {
    0x000000,
    0x666600,
    0xEEEE00,
    0x222200,
    0x444400,
    0xCCCC00,
    0x444400,
    0x222200,
    0xAAAA00,
    0x666600,
    0x000000,
    0x888800,
    0x888800,
    0x000000,
    0x666600,
    0xAAAA00,
    0x222200,
    0x444400,
    0xCCCC00,
    0x444400,
    0x222200,
    0xEEEE00,
    0x666600,
    0x000000,
    0xEEEE00,
    0x888800,
    0x000000,
    0xCCCC00,
    0xAAAA00,
    0x222200,
    0xAAAA00,
    0xCCCC00,
    0x444400,
    0x888800,
    0xEEEE00,
    0x666600,
    0x666600,
    0xEEEE00,
    0x888800,
    0x444400,
    0xCCCC00,
    0xAAAA00,
    0x222200,
    0xAAAA00,
    0xCCCC00,
    0x000000,
    0x888800,
    0xEEEE00,
};
Uint32 AnPal_PalCNZ_2[48] = {
    0x000088,
    0x000088,
    0x668888,
    0x000088,
    0x000088,
    0x446688,
    0x000088,
    0x000088,
    0x224488,
    0x000088,
    0x000088,
    0x002288,
    0x002288,
    0x000088,
    0x000088,
    0x224488,
    0x000088,
    0x000088,
    0x446688,
    0x000088,
    0x000088,
    0x668888,
    0x000088,
    0x000088,
    0x668888,
    0x002288,
    0x000088,
    0x446688,
    0x224488,
    0x000088,
    0x224488,
    0x446688,
    0x000088,
    0x002288,
    0x668888,
    0x000088,
    0x000088,
    0x668888,
    0x002288,
    0x000088,
    0x446688,
    0x224488,
    0x000088,
    0x224488,
    0x446688,
    0x000088,
    0x002288,
    0x668888,
};
Uint32 AnPal_PalCNZ_3[90] = {
    0x0022EE,
    0xAA8800,
    0xEE00CC,
    0x2244CC,
    0xCC6600,
    0xEE00EE,
    0x4466AA,
    0xCC4400,
    0xCC00EE,
    0x448888,
    0xEE2200,
    0xAA00EE,
    0x66AA66,
    0xEE0000,
    0x8800EE,
    0x66CC44,
    0xEE0022,
    0x6600EE,
    0x88EE22,
    0xEE0044,
    0x4400EE,
    0x88EE00,
    0xEE0066,
    0x2200EE,
    0x88CC00,
    0xEE0088,
    0x0000EE,
    0xAAAA00,
    0xEE00AA,
    0x0000EE,
    0xAA8800,
    0xEE00CC,
    0x0022EE,
    0xCC6600,
    0xEE00EE,
    0x2244CC,
    0xCC4400,
    0xCC00EE,
    0x4466AA,
    0xEE2200,
    0xAA00EE,
    0x448888,
    0xEE0000,
    0x8800EE,
    0x66AA66,
    0xEE0022,
    0x6600EE,
    0x66CC44,
    0xEE0044,
    0x4400EE,
    0x88EE22,
    0xEE0066,
    0x2200EE,
    0x88EE00,
    0xEE0088,
    0x0000EE,
    0x88CC00,
    0xEE00AA,
    0x0000EE,
    0xAAAA00,
    0xEE00CC,
    0x0022EE,
    0xAA8800,
    0xEE00EE,
    0x2244CC,
    0xCC6600,
    0xCC00EE,
    0x4466AA,
    0xCC4400,
    0xAA00EE,
    0x448888,
    0xEE2200,
    0x8800EE,
    0x66AA66,
    0xEE0000,
    0x6600EE,
    0x66CC44,
    0xEE0022,
    0x4400EE,
    0x88EE22,
    0xEE0044,
    0x2200EE,
    0x88EE00,
    0xEE0066,
    0x0000EE,
    0x88CC00,
    0xEE0088,
    0x0000EE,
    0xAAAA00,
    0xEE00AA,
};
Uint32 AnPal_PalCNZ_5[32] = {
    0x00EE22,
    0xEECCEE,
    0x22EE44,
    0xCCAAEE,
    0x44EE66,
    0xAA88EE,
    0x66EE88,
    0x8866EE,
    0x88EEAA,
    0x6644EE,
    0xAAEECC,
    0x4422EE,
    0xCCEEEE,
    0x2200EE,
    0xEEEEEE,
    0x0000EE,
    0xCCEEEE,
    0x2200EE,
    0xAAEECC,
    0x4422EE,
    0x88EEAA,
    0x6644EE,
    0x66EE88,
    0x8866EE,
    0x44EE66,
    0xAA88EE,
    0x22EE44,
    0xCCAAEE,
    0x00EE22,
    0xEECCEE,
    0x00EE00,
    0xEEEEEE,
};
Uint32 AnPal_PalCNZ_4[122] = {
    0x0022EE,
    0xAA88EE,
    0xAA00EE,
    0x2244EE,
    0xAA66EE,
    0xAA00EE,
    0x4466EE,
    0xAA44EE,
    0xAA00EE,
    0x4488EE,
    0xAA22EE,
    0xAA00EE,
    0x66AAEE,
    0xAA00EE,
    0x8800EE,
    0x66CCEE,
    0xAA00EE,
    0x6600EE,
    0x88EEEE,
    0xAA00EE,
    0x4400EE,
    0x88EEEE,
    0xAA00EE,
    0x2200EE,
    0x88CCEE,
    0xAA00EE,
    0x0000EE,
    0xAAAAEE,
    0xAA00EE,
    0x0000EE,
    0xAA88EE,
    0xAA00EE,
    0x0022EE,
    0xAA66EE,
    0xAA00EE,
    0x2244CC,
    0xAA44EE,
    0xAA00EE,
    0x4466EE,
    0xAA22EE,
    0xAA00EE,
    0x4488EE,
    0xAA00EE,
    0x8800EE,
    0x66AAEE,
    0xAA00EE,
    0x6600EE,
    0x66CCEE,
    0xAA00EE,
    0x4400EE,
    0x88EEEE,
    0xAA00EE,
    0x2200EE,
    0x88EEEE,
    0xAA00EE,
    0x0000EE,
    0x88CCEE,
    0xAA00EE,
    0x0000EE,
    0xAAAAEE,
    0xAA00EE,
    0x0022EE,
    0xAA88EE,
    0xAA00EE,
    0x2244EE,
    0xAA66EE,
    0xAA00EE,
    0x4466EE,
    0xAA44EE,
    0xAA00EE,
    0x4488EE,
    0xAA22EE,
    0x8800EE,
    0x66AAEE,
    0xAA00EE,
    0x6600EE,
    0x66CCEE,
    0xAA00EE,
    0x4400EE,
    0x88EEEE,
    0xAA00EE,
    0x2200EE,
    0x88EEEE,
    0xAA00EE,
    0x0000EE,
    0x88CCEE,
    0xAA00EE,
    0x0000EE,
    0xAAAAEE,
    0xAA00EE,
    0x004488,
    0xAACCEE,
    0x226688,
    0xAAAAEE,
    0x448888,
    0x8888EE,
    0x66AA88,
    0x6666EE,
    0x88EEAA,
    0x4444EE,
    0xAAEECC,
    0x2222EE,
    0xCCEEEE,
    0x0000EE,
    0xCCEEEE,
    0x0000EE,
    0xCCEEEE,
    0x0000EE,
    0xAAEECC,
    0x2222EE,
    0x88EEAA,
    0x4444EE,
    0x66AA88,
    0x6666EE,
    0x448888,
    0x8888EE,
    0x226688,
    0xAAAAEE,
    0x004488,
    0xAACCEE,
    0x222288,
    0xAACCEE,
};

PUBLIC Level_CNZ::Level_CNZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 4;
    VisualAct = Act = act;
	sprintf(ZoneLetters, "CNZ");
	PlayMusic(act, 0, SaveGame::CurrentMode, 0x1A0);

	if (SaveGame::CurrentMode >= 1)
	{
		if (Act == 1) {
			Str_TileConfigBin = "Mixed/Stages/CNZ1/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/CNZ1/Scene.bin";
			Str_TileSprite = "Mixed/Stages/CNZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/CNZ1/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/CNZ1/Stageconfig.bin";
		}
		else {
			Str_TileConfigBin = "Mixed/Stages/CNZ2/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/CNZ2/Scene.bin";
			Str_TileSprite = "Mixed/Stages/CNZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/CNZ2/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/CNZ2/Stageconfig.bin";
		}
	}
	else
	{
		if (Act == 1) {
			Str_TileConfigBin = "Classic/Stages/CNZ1/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/CNZ1/Scene.bin";
			Str_TileSprite = "Classic/Stages/CNZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/CNZ1/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/CNZ1/Stageconfig.bin";
		}
		else {
			Str_TileConfigBin = "Classic/Stages/CNZ2/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/CNZ2/Scene.bin";
			Str_TileSprite = "Classic/Stages/CNZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/CNZ2/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/CNZ2/Stageconfig.bin";
		}
	}

    sprintf(LevelName, "CARNIVAL NIGHT");
    sprintf(LevelNameDiscord, "Carnival Night");

    if (Act == 1) {
        // PlayerStartX = 0x32C0;
        // PlayerStartY = 0x020C;
    }
    else if (Act == 2) {

    }

	AddNewDebugObjectID(Obj_Balloon);
	AddNewDebugObjectID(Obj_Batbright);
	AddNewDebugObjectID(Obj_Bumper);
}

PUBLIC void Level_CNZ::RestartStage(bool doActTransition, bool drawBackground) {
    App->Audio->ClearMusic();
    if (Sound::SoundBank[0])
        App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

    LevelScene::RestartStage(doActTransition, drawBackground);
}

PUBLIC void Level_CNZ::AssignSpriteMapIDs() {
    LevelScene::AssignSpriteMapIDs();

    if (Act <= 1) {
    	SpriteMapIDs.at(0x01) = ItemsSprite;
        SpriteMapIDs.at(0x04) = CNZObjectsSprite;
        SpriteMapIDs.at(0x05) = CNZObjectsSprite;
    	SpriteMapIDs.at(0x07) = ObjectsSprite;
    	SpriteMapIDs.at(0x08) = ObjectsSprite;
        SpriteMapIDs.at(0x09) = CNZObjectsSprite;
        SpriteMapIDs.at(0x0A) = CNZObjectsSprite;
        SpriteMapIDs.at(0x0C) = CNZObjectsSprite;
        SpriteMapIDs.at(0x0D) = CNZObjectsSprite;
        SpriteMapIDs.at(0x0F) = CNZObjectsSprite;
    	SpriteMapIDs.at(0x2F) = CNZObjectsSprite;
    	SpriteMapIDs.at(0x34) = ObjectsSprite;
        SpriteMapIDs.at(0x35) = CNZObjectsSprite;
        SpriteMapIDs.at(0x4A) = CNZObjectsSprite;

    	SpriteMapIDs.at(0x51) = CNZObjectsSprite;
        SpriteMapIDs.at(0xA5) = CNZObjectsSprite;
    } else {
    	SpriteMapIDs.at(0x01) = ItemsSprite;
        SpriteMapIDs.at(0x04) = CNZObjectsSprite;
        SpriteMapIDs.at(0x05) = CNZObjectsSprite;
        SpriteMapIDs.at(0x06) = CNZObjectsSprite;
    	SpriteMapIDs.at(0x07) = ObjectsSprite;
    	SpriteMapIDs.at(0x08) = ObjectsSprite;
        SpriteMapIDs.at(0x09) = CNZObjectsSprite;
        SpriteMapIDs.at(0x0A) = CNZObjectsSprite;
        SpriteMapIDs.at(0x0C) = CNZObjectsSprite;
        SpriteMapIDs.at(0x0D) = CNZObjectsSprite;
        SpriteMapIDs.at(0x0F) = CNZObjectsSprite;
    	SpriteMapIDs.at(0x2F) = CNZObjectsSprite;
    	SpriteMapIDs.at(0x34) = ObjectsSprite;
        SpriteMapIDs.at(0x35) = CNZObjectsSprite;
		SpriteMapIDs.at(0x35) = CNZObjectsSprite;

    	SpriteMapIDs.at(0x51) = CNZObjectsSprite;
        SpriteMapIDs.at(0x8C) = CNZObjectsSprite;
        SpriteMapIDs.at(0xA5) = CNZObjectsSprite;
    }
}

PUBLIC void Level_CNZ::LoadZoneSpecificSprites() {
    if (!CNZObjectsSprite) {
		CNZObjectsSprite = new ISprite("CNZ/Objects.gif", App);
		CNZObjectsSprite->Print = true;

        CNZObjectsSprite->LoadAnimation("CNZ/Breakable Wall.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Balloon.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Button.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Cork Floor.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Cylinder.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Door Horizontal.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/End Boss.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Light Bulb.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Miniboss.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Rising Platform.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Trap Door.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Cannon.bin");
		CNZObjectsSprite->LoadAnimation("CNZ/Cannon Ball.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Cannon Base.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Bumper.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Clamer.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Batbot.bin");
        CNZObjectsSprite->LoadAnimation("CNZ/Sparkle.bin");
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

PUBLIC void Level_CNZ::FinishResults() {
	if (VisualAct == 1) {
		LevelScene::FinishResults();
	} else {
		FadeAction = FadeActionType::NEXT_ZONE;
		FadeTimerMax = 90;
		FadeMax = 0x140;
		G->FadeToWhite = false;
	}
}

PUBLIC void Level_CNZ::GoToNextAct() {
	if (VisualAct == 1) {
		Level_CNZ* NextAct = new Level_CNZ(App, G, 2);

		TransferCommonLevelData(NextAct);
		NextAct->CNZObjectsSprite = CNZObjectsSprite;
		// Enable Title Card with no fade-in
		NextAct->LevelCardTimer = 0.0;
		NextAct->FadeTimer = 0;
		NextAct->FadeAction = 0;
		NextAct->LevelCardHide = false;
		// Transfer over current frame
		NextAct->Frame = Frame;
		// Set player spawn position relative to their previous position
		NextAct->SpecialSpawnPositionX = Player->EZX - 0x3000;
		NextAct->SpecialSpawnPositionY = Player->EZY + 0x200;
		NextAct->RoutineNumber = 0x00;

		App->NextScene = NextAct;
	} else {
		Level_ICZ* NextAct = new Level_ICZ(App, G, 1);
		TransferCommonLevelData(NextAct);
		App->NextScene = NextAct;
	}
}

PUBLIC void Level_CNZ::EarlyUpdate() {
    if (Act == 1) {
        // During the boss fight
        if (false) {
            Data->Layers[1].Flags |= 0 | 2 | 4;
            Data->Layers[1].OffsetX = 0x3180;
            Data->Layers[1].OffsetY -= 4;
            if (Data->Layers[1].OffsetY < 0x40)
                Data->Layers[1].OffsetY += 0x100;
            Data->Layers[3].OffsetY -= 4;
            if (Data->Layers[3].OffsetY < -0x500)
                Data->Layers[3].OffsetY += 0x100;

            CameraMinY = 0x1C0;

            CameraMinX = 0x31E0;
            CameraMaxX = 0x33A0 - App->WIDTH;
        } else {
            Data->Layers[1].Visible = false;
        }
    } else if (Act == 2) {
        // Layer Flags:
        // 0x1: Collidable
        // 0x2: Don't Repeat X
        // 0x3: Don't Repeat Y
        Data->Layers[1].Flags |= 0 | 2 | 4;
        Data->Layers[1].OffsetX = 0x3480;
    }
    if (Frame % 4 == 0) {
        TileSprite->SetPalette(0x39, AnPal_PalCNZ_1[(Frame / 4 * 3) % 48]);
        TileSprite->SetPalette(0x3A, AnPal_PalCNZ_1[(Frame / 4 * 3) % 48 + 1]);
        TileSprite->SetPalette(0x3B, AnPal_PalCNZ_1[(Frame / 4 * 3) % 48 + 2]);
        TileSprite->SetPaletteAlt(0x39, AnPal_PalCNZ_2[(Frame / 4 * 3) % 48]);
        TileSprite->SetPaletteAlt(0x3A, AnPal_PalCNZ_2[(Frame / 4 * 3) % 48 + 1]);
        TileSprite->SetPaletteAlt(0x3B, AnPal_PalCNZ_2[(Frame / 4 * 3) % 48 + 2]);

        TileSprite->SetPalette(0x29, AnPal_PalCNZ_3[(Frame / 4 * 3) % 90]);
        TileSprite->SetPalette(0x2A, AnPal_PalCNZ_3[(Frame / 4 * 3) % 90 + 1]);
        TileSprite->SetPalette(0x2B, AnPal_PalCNZ_3[(Frame / 4 * 3) % 90 + 2]);
        TileSprite->SetPaletteAlt(0x29, AnPal_PalCNZ_4[(Frame / 4 * 3) % 90]);
        TileSprite->SetPaletteAlt(0x2A, AnPal_PalCNZ_4[(Frame / 4 * 3) % 90 + 1]);
        TileSprite->SetPaletteAlt(0x2B, AnPal_PalCNZ_4[(Frame / 4 * 3) % 90 + 2]);

        TileSprite->SetPalette(0x27, AnPal_PalCNZ_5[(Frame / 4 * 2) % 32]);
        TileSprite->SetPalette(0x28, AnPal_PalCNZ_5[(Frame / 4 * 2) % 32 + 1]);
        TileSprite->SetPaletteAlt(0x27, AnPal_PalCNZ_5[(Frame / 4 * 2) % 32]);
        TileSprite->SetPaletteAlt(0x28, AnPal_PalCNZ_5[(Frame / 4 * 2) % 32 + 1]);
    }
    LevelScene::EarlyUpdate();
}
PUBLIC void Level_CNZ::Subupdate() {
    LevelScene::Subupdate();
}

PUBLIC void Level_CNZ::HandleCamera() {
    if (Act == 1) {

    } else if (Act == 2) {

    }
    LevelScene::HandleCamera();
}
