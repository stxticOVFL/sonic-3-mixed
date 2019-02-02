#if INTERFACE
#include <Game/LevelScene.h>

class Level_ICZ : public LevelScene {
public:
    ISprite* ICZObjectSprite = NULL;
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

    if (Act == 1) {
        Sound::SoundBank[0] = new ISound("Music/ICZ1.ogg", false);
		Sound::Audio->LoopPoint[0] = 0;

        Str_TileConfigBin = "Stages/ICZ1/TileConfig.bin";
        Str_SceneBin = "Stages/ICZ1/Scene.bin";
        Str_TileSprite = "Stages/ICZ1/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/ICZ1/Animated Tiles.gif";
    }
    else if (Act == 2) {
        Sound::SoundBank[0] = new ISound("Music/ICZ2.ogg", false);
		Sound::Audio->LoopPoint[0] = 0;

        Str_TileConfigBin = "Stages/ICZ2/TileConfig.bin";
        Str_SceneBin = "Stages/ICZ2/Scene.bin";
        Str_TileSprite = "Stages/ICZ2/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/ICZ2/Animated Tiles.gif";
    }

    sprintf(LevelName, "ICECAP");
    sprintf(LevelNameDiscord, "IceCap");

    if (Act == 1) {
        PlayerStartX = 0x3E20;
        PlayerStartY = 0x6C8;
    }
    else if (Act == 2) {

    }
}

PUBLIC void Level_ICZ::RestartStage(bool doActTransition, bool drawBackground) {
    App->Audio->ClearMusic();
    if (Sound::SoundBank[0])
        App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

    LevelScene::RestartStage(doActTransition, drawBackground);
}

PUBLIC void Level_ICZ::AssignSpriteMapIDs() {
    LevelScene::AssignSpriteMapIDs();

	SpriteMapIDs[0x01] = ItemsSprite;
    SpriteMapIDs[0x04] = ICZObjectSprite;
    SpriteMapIDs[0x05] = ICZObjectSprite;
	SpriteMapIDs[0x07] = ObjectsSprite;
	SpriteMapIDs[0x08] = ObjectsSprite;
    SpriteMapIDs[0x09] = ICZObjectSprite;
    SpriteMapIDs[0x0A] = ICZObjectSprite;
    SpriteMapIDs[0x0C] = ICZObjectSprite;
    SpriteMapIDs[0x0D] = ICZObjectSprite;
    SpriteMapIDs[0x0F] = ICZObjectSprite;
	SpriteMapIDs[0x2F] = ICZObjectSprite;

	SpriteMapIDs[0x34] = ObjectsSprite;
    SpriteMapIDs[0x35] = ICZObjectSprite;

	SpriteMapIDs[0x51] = ICZObjectSprite;
}

PUBLIC void Level_ICZ::LoadZoneSpecificSprites() {
    if (!ICZObjectSprite) {
        ICZObjectSprite = new ISprite("Sprites/ICZ/Objects.gif", App);
        ICZObjectSprite->Print = true;
        
        ICZObjectSprite->LoadAnimation("Sprites/ICZ/Collapsing Bridge 1.bin");
        ICZObjectSprite->LoadAnimation("Sprites/ICZ/Collapsing Bridge 2.bin");
        ICZObjectSprite->LoadAnimation("Sprites/ICZ/Cork Floor.bin");
        ICZObjectSprite->LoadAnimation("Sprites/ICZ/Cork Floor 2.bin");
        ICZObjectSprite->LoadAnimation("Sprites/ICZ/Platforms.bin");
        ICZObjectSprite->LoadAnimation("Sprites/ICZ/Tension Bridge.bin");
        ICZObjectSprite->LoadAnimation("Sprites/ICZ/Wall and Column.bin");
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
		NextAct->ICZObjectSprite = ICZObjectSprite;
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
        Data->layers[0].Visible = false;
        Data->layers[0].RelativeY = 0x80;
        // Snowpile
        Data->layers[1].Visible = false;
        Data->layers[1].Flags = 0 | 2 | 4;
        // Background (Outside)
        Data->layers[2].RelativeY = 0x1;
        Data->layers[2].UseDeltaCameraY = true;
        // FG Low/High
        Data->layers[3].IsScrollingVertical = true;
        Data->layers[4].IsScrollingVertical = true;

        if (Player->EZX < 0x3960) {
            Data->layers[0].Visible = false;
            Data->layers[2].Visible = true;

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
            Data->layers[0].Visible = true;
            Data->layers[2].Visible = false;

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
