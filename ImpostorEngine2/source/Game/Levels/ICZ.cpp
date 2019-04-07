#if INTERFACE
#include <Game/LevelScene.h>

class Level_ICZ : public LevelScene {
public:
    ISprite* ICZObjectsSprite = NULL;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/ICZ.h>
#include <Game/Levels/LBZ.h>

// Find: \$([A-F0-9])([A-F0-9])([A-F0-9]),
// Replace: 0x$3$3$2$2$1$1,\n

Uint32 AnPal_PalICZ_1[32] = {
    0x2266EE,
    0x0022EE,
    0x4444EE,
    0x0022EE,
    0x4444EE,
    0x0000EE,
    0x2244EE,
    0x0000EE,
    0x2266EE,
    0x0000CC,
    0x2288EE,
    0x0000AA,
    0x22AAEE,
    0x0000CC,
    0x00CCEE,
    0x0000EE,
    0x00EEEE,
    0x0022EE,
    0x44EEEE,
    0x0000EE,
    0x44EEEE,
    0x0000CC,
    0x44EEEE,
    0x0000AA,
    0x00EEEE,
    0x000088,
    0x22CCEE,
    0x0000AA,
    0x22AAEE,
    0x0000CC,
    0x2288EE,
    0x0022EE,
};
Uint32 AnPal_PalICZ_2[36] = {
    0x6600EE,
    0x8800EE,
    0x4400EE,
    0x6600EE,
    0x4400CC,
    0x4400EE,
    0x2200CC,
    0x4400CC,
    0x2200AA,
    0x2200CC,
    0x0000AA,
    0x2200AA,
    0x000088,
    0x0000AA,
    0x000066,
    0x000088,
    0x000066,
    0x000088,
    0x000066,
    0x000088,
    0x000066,
    0x000088,
    0x000088,
    0x0000AA,
    0x0000AA,
    0x2200AA,
    0x2200AA,
    0x2200CC,
    0x2200CC,
    0x4400CC,
    0x4400CC,
    0x4400EE,
    0x4400EE,
    0x6600EE,
    0x6600EE,
    0x8800EE,
};
Uint32 AnPal_PalICZ_3[12] = {
    0x004488,
    0xAAEEEE,
    0x006688,
    0x00EEEE,
    0x0088AA,
    0x00CCEE,
    0x00CCEE,
    0x0088AA,
    0x0088AA,
    0x00CCEE,
    0x006688,
    0x00EEEE,
};
Uint32 AnPal_PalICZ_4[32] = {
    0x88EE00,
    0xCCEECC,
    0x88CC00,
    0xAAEEAA,
    0x88CC00,
    0xAAEEAA,
    0x66AA00,
    0x88EE66,
    0x66AA00,
    0x88EE66,
    0x448800,
    0x88EE00,
    0x448800,
    0x88EE00,
    0x228800,
    0x88CC00,
    0x446600,
    0x66AA00,
    0x446600,
    0x66AA00,
    0x228800,
    0x88CC00,
    0x448800,
    0x88EE00,
    0x66AA00,
    0x88EE66,
    0x88CC00,
    0xAAEEAA,
    0x88EE00,
    0xCCEECC,
    0x88EE00,
    0xCCEECC,
};

PUBLIC Level_ICZ::Level_ICZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 5;
    VisualAct = Act = act;
	sprintf(ZoneLetters, "ICZ");
	PlayMusic(act, SaveGame::CurrentMode == 0 ? (act == 1 ? 206454 : 0) : 0, SaveGame::CurrentMode);

	if (SaveGame::CurrentMode >= 1)
	{
		if (Act == 1) {
			Str_TileConfigBin = "Mixed/Stages/ICZ1/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/ICZ1/Scene.bin";
			Str_TileSprite = "Mixed/Stages/ICZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/ICZ1/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/ICZ1/Stageconfig.bin";
			ScreenYWrapValue = 0x7FF;
		}
		else {
			Str_TileConfigBin = "Mixed/Stages/ICZ2/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/ICZ2/Scene.bin";
			Str_TileSprite = "Mixed/Stages/ICZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/ICZ2/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/ICZ2/Stageconfig.bin";
			ScreenYWrapValue = 0xFFF;
		}
	}
	else
	{
		if (Act == 1) {
			Str_TileConfigBin = "Classic/Stages/ICZ1/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/ICZ1/Scene.bin";
			Str_TileSprite = "Classic/Stages/ICZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/ICZ1/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/ICZ1/Stageconfig.bin";
			ScreenYWrapValue = 0x7FF;
		}
		else {
			Str_TileConfigBin = "Classic/Stages/ICZ2/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/ICZ2/Scene.bin";
			Str_TileSprite = "Classic/Stages/ICZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/ICZ2/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/ICZ2/Stageconfig.bin";
			ScreenYWrapValue = 0xFFF;
		}
	}

    sprintf(LevelName, "ICECAP");
    sprintf(LevelNameDiscord, "IceCap");

    if (Act == 1) {
        PlayerStartX = 0x3880;
        PlayerStartY = 0x698;
    }
    else if (Act == 2) {
        VisualWaterLevel = WaterLevel = 0xAD8;
    }

	AddNewDebugObjectID(Obj_StarPointer);
	AddNewDebugObjectID(Obj_IceCube);
}

PUBLIC void Level_ICZ::RestartStage(bool doActTransition, bool drawBackground) {
    App->Audio->ClearMusic();
    if (Sound::SoundBank[0])
        App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

    LevelScene::RestartStage(doActTransition, drawBackground);
}

PUBLIC void Level_ICZ::AssignSpriteMapIDs() {
    LevelScene::AssignSpriteMapIDs();

	SpriteMapIDs.at(0x01) = ItemsSprite;
    SpriteMapIDs.at(0x04) = ICZObjectsSprite;
    SpriteMapIDs.at(0x05) = ICZObjectsSprite;
	SpriteMapIDs.at(0x07) = ObjectsSprite;
	SpriteMapIDs.at(0x08) = ObjectsSprite;
    SpriteMapIDs.at(0x09) = ICZObjectsSprite;
    SpriteMapIDs.at(0x0A) = ICZObjectsSprite;
    SpriteMapIDs.at(0x0C) = ICZObjectsSprite;
    SpriteMapIDs.at(0x0D) = ICZObjectsSprite;
    SpriteMapIDs.at(0x0F) = ICZObjectsSprite;
	SpriteMapIDs.at(0x2F) = ICZObjectsSprite;

	SpriteMapIDs.at(0x34) = ObjectsSprite;
    SpriteMapIDs.at(0x35) = ICZObjectsSprite;

	SpriteMapIDs.at(0x51) = ICZObjectsSprite;

	SpriteMapIDs.at(0xAE) = ICZObjectsSprite;
	SpriteMapIDs.at(0xB3) = ICZObjectsSprite;
	SpriteMapIDs.at(0xB4) = ICZObjectsSprite;
	SpriteMapIDs.at(0xB5) = ICZObjectsSprite;
	SpriteMapIDs.at(0xB6) = ICZObjectsSprite;
	SpriteMapIDs.at(0xB8) = ICZObjectsSprite;
	SpriteMapIDs.at(0xB9) = ICZObjectsSprite;

	SpriteMapIDs.at(0x410) = ICZObjectsSprite;
	SpriteMapIDs.at(0x411) = ICZObjectsSprite;
}

PUBLIC void Level_ICZ::LoadZoneSpecificSprites() {
    if (!ICZObjectsSprite) {
        ICZObjectsSprite = new ISprite("ICZ/Objects.gif", App);
        ICZObjectsSprite->Print = true;

        ICZObjectsSprite->LoadAnimation("ICZ/Collapsing Bridge 1.bin");
        ICZObjectsSprite->LoadAnimation("ICZ/Collapsing Bridge 2.bin");
        ICZObjectsSprite->LoadAnimation("ICZ/Cork Floor.bin");
        ICZObjectsSprite->LoadAnimation("ICZ/Cork Floor 2.bin");
        ICZObjectsSprite->LoadAnimation("ICZ/Platforms.bin");
		ICZObjectsSprite->LoadAnimation("ICZ/Platforms 3.bin");
		ICZObjectsSprite->LoadAnimation("ICZ/Particles.bin");
        ICZObjectsSprite->LoadAnimation("ICZ/Tension Bridge.bin");
		ICZObjectsSprite->LoadAnimation("ICZ/Wall and Column.bin");
        ICZObjectsSprite->LoadAnimation("ICZ/Star Pointer.bin");
		ICZObjectsSprite->LoadAnimation("ICZ/Ice Cube.bin");
		ICZObjectsSprite->LoadAnimation("ICZ/Harmful Ice.bin");
		ICZObjectsSprite->LoadAnimation("ICZ/Freezer.bin");
		ICZObjectsSprite->LoadAnimation("ICZ/Swinging Platform.bin");
		ICZObjectsSprite->LoadAnimation("ICZ/SnowPile.bin");
		ICZObjectsSprite->LoadAnimation("ICZ/Ring.bin");
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

PUBLIC void Level_ICZ::FinishResults() {
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
PUBLIC void Level_ICZ::GoToNextAct() {
	if (VisualAct == 1) {
		Level_ICZ* NextAct = new Level_ICZ(App, G, 2);

		TransferCommonLevelData(NextAct);
		NextAct->ICZObjectsSprite = ICZObjectsSprite;
		// Enable Title Card with no fade-in
		NextAct->LevelCardTimer = 0.0;
		NextAct->FadeTimer = 0;
		NextAct->FadeAction = 0;
		NextAct->LevelCardHide = false;
		// Transfer over current frame
		NextAct->Frame = Frame;
		// Set player spawn position relative to their previous position
		NextAct->SpecialSpawnPositionX = 0x60;
		NextAct->SpecialSpawnPositionY = 0x3D0;
		NextAct->RoutineNumber = 0x00;

		App->NextScene = NextAct;
	}
	else {
		Level_LBZ* NextAct = new Level_LBZ(App, G, 1);
		TransferCommonLevelData(NextAct);
		App->NextScene = NextAct;
	}
}

PUBLIC void Level_ICZ::EarlyUpdate() {
    if (Act == 1) {
        // Background (Inside)
        Data->Layers[0].Visible = false;
        Data->Layers[0].RelativeY = 0x80;
        // Snowpile
        Data->Layers[1].Visible = false;
        Data->Layers[1].Flags = 0 | 2 | 4;
        // Background (Outside)
        Data->Layers[2].RelativeY = 0x1;
        Data->Layers[2].UseDeltaCameraY = true;
        // FG Low/High
        Data->Layers[3].IsScrollingVertical = true;
        Data->Layers[4].IsScrollingVertical = true;

        if (Player->EZX < 0x3960) {
            Data->Layers[0].Visible = false;
            Data->Layers[2].Visible = true;

            if (TileSprite->GetPalette(0x31) != 0xEEEEEE) {
                TileSprite->SetPalette(0x31, 0xEEEEEE);
                TileSprite->SetPalette(0x32, 0xCCEEEE);
    	        TileSprite->SetPalette(0x33, 0xAAEEEE);
                TileSprite->SetPalette(0x34, 0xAACCEE);
                TileSprite->SetPalette(0x35, 0x88CCEE);
                TileSprite->SetPalette(0x36, 0x66AAEE);
                TileSprite->SetPalette(0x37, 0x6688EE);
                TileSprite->SetPalette(0x38, 0x4466EE);
                TileSprite->SetPalette(0x39, 0x0044EE);
                TileSprite->SetPalette(0x3A, 0x0000EE);
                TileSprite->SetPalette(0x3B, 0x0000CC);
                TileSprite->SetPalette(0x3C, 0x000000);
                TileSprite->SetPalette(0x3D, 0xCCEEAA);
                TileSprite->SetPalette(0x3E, 0xAAEECC);
                TileSprite->SetPalette(0x3F, 0x0088EE);
                TileSprite->UpdatePalette();
            }
        }
        else {
            Data->Layers[0].Visible = true;
            Data->Layers[2].Visible = false;

            if (TileSprite->GetPalette(0x31) != 0x00CCEE) {
                TileSprite->SetPalette(0x31, 0x00CCEE);
                TileSprite->SetPalette(0x32, 0x0044EE);
    	        TileSprite->SetPalette(0x33, 0x4400EE);
                TileSprite->SetPalette(0x34, 0x0000CC);
                TileSprite->SetPalette(0x35, 0x000066);
                TileSprite->SetPalette(0x36, 0x000022);
                TileSprite->SetPalette(0x37, 0x000000);
                TileSprite->SetPalette(0x38, 0x0022EE);
                TileSprite->SetPalette(0x39, 0x4422EE);
                TileSprite->SetPalette(0x3A, 0x2200AA);
                TileSprite->SetPalette(0x3B, 0x220044);
                // TileSprite->SetPalette(0x37, 0x4466EE);
                TileSprite->UpdatePalette();
            }

            if (Frame % 6 == 0) {
                TileSprite->SetPalette(0x2E, AnPal_PalICZ_1[(Frame / 6 * 2) % 32]);
                TileSprite->SetPalette(0x2F, AnPal_PalICZ_1[(Frame / 6 * 2) % 32 + 1]);
                TileSprite->UpdatePalette();
            }
            if (Frame % 10 == 0) {
                TileSprite->SetPalette(0x3E, AnPal_PalICZ_2[(Frame / 10 * 2) % 36]);
                TileSprite->SetPalette(0x3F, AnPal_PalICZ_2[(Frame / 10 * 2) % 36 + 1]);
                TileSprite->UpdatePalette();
            }
            if (Frame % 8 == 0) {
                TileSprite->SetPalette(0x3C, AnPal_PalICZ_3[(Frame / 8 * 2) % 12]);
                TileSprite->SetPalette(0x3D, AnPal_PalICZ_3[(Frame / 8 * 2) % 12 + 1]);

                TileSprite->SetPalette(0x2C, AnPal_PalICZ_4[(Frame / 8 * 2) % 32]);
                TileSprite->SetPalette(0x2D, AnPal_PalICZ_4[(Frame / 8 * 2) % 32 + 1]);
                TileSprite->UpdatePalette();
            }
        }
    }
    else if (Act == 2) {

    }
    LevelScene::EarlyUpdate();
}
PUBLIC void Level_ICZ::Subupdate() {
    LevelScene::Subupdate();
}

PUBLIC void Level_ICZ::HandleCamera() {
    if (Act == 1) {

    }
    else if (Act == 2) {

    }
    LevelScene::HandleCamera();
}
