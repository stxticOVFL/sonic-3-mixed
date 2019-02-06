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

    if (Act == 1) {
        Sound::SoundBank[0] = new ISound("Music/CNZ1.ogg", false);
		Sound::Audio->LoopPoint[0] = 0;

        Str_TileConfigBin = "Stages/CNZ1/TileConfig.bin";
        Str_SceneBin = "Stages/CNZ1/Scene.bin";
        Str_TileSprite = "Stages/CNZ1/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/CNZ1/Animated Tiles.gif";
    }
    else if (Act == 2) {
        Sound::SoundBank[0] = new ISound("Music/CNZ2.ogg", false);
		Sound::Audio->LoopPoint[0] = 0;

        Str_TileConfigBin = "Stages/CNZ2/TileConfig.bin";
        Str_SceneBin = "Stages/CNZ2/Scene.bin";
        Str_TileSprite = "Stages/CNZ2/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/CNZ2/Animated Tiles.gif";
    }

    sprintf(LevelName, "CARNIVAL NIGHT");
    sprintf(LevelNameDiscord, "Carnival Night");

    if (Act == 1) {
        // PlayerStartX = 0x32C0;
        // PlayerStartY = 0x020C;
    }
    else if (Act == 2) {

    }
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
    	SpriteMapIDs[0x01] = ItemsSprite;
        SpriteMapIDs[0x04] = CNZObjectsSprite;
        SpriteMapIDs[0x05] = CNZObjectsSprite;
    	SpriteMapIDs[0x07] = ObjectsSprite;
    	SpriteMapIDs[0x08] = ObjectsSprite;
        SpriteMapIDs[0x09] = CNZObjectsSprite;
        SpriteMapIDs[0x0A] = CNZObjectsSprite;
        SpriteMapIDs[0x0C] = CNZObjectsSprite;
        SpriteMapIDs[0x0D] = CNZObjectsSprite;
        SpriteMapIDs[0x0F] = CNZObjectsSprite;
    	SpriteMapIDs[0x2F] = CNZObjectsSprite;
    	//SpriteMapIDs[0x33] = SpriteMap["HCZ"];
    	SpriteMapIDs[0x34] = ObjectsSprite;
        SpriteMapIDs[0x35] = CNZObjectsSprite;

    	SpriteMapIDs[0x51] = CNZObjectsSprite;
    }
    else {
    	SpriteMapIDs[0x01] = ItemsSprite;
        SpriteMapIDs[0x04] = CNZObjectsSprite;
        SpriteMapIDs[0x05] = CNZObjectsSprite;
        SpriteMapIDs[0x06] = CNZObjectsSprite;
    	SpriteMapIDs[0x07] = ObjectsSprite;
    	SpriteMapIDs[0x08] = ObjectsSprite;
        SpriteMapIDs[0x09] = CNZObjectsSprite;
        SpriteMapIDs[0x0A] = CNZObjectsSprite;
        SpriteMapIDs[0x0C] = CNZObjectsSprite;
        SpriteMapIDs[0x0D] = CNZObjectsSprite;
        SpriteMapIDs[0x0F] = CNZObjectsSprite;
    	SpriteMapIDs[0x2F] = CNZObjectsSprite;
    	//SpriteMapIDs[0x33] = SpriteMap["HCZ"];
    	SpriteMapIDs[0x34] = ObjectsSprite;
        SpriteMapIDs[0x35] = CNZObjectsSprite;

    	SpriteMapIDs[0x51] = CNZObjectsSprite;
        SpriteMapIDs[0x8C] = CNZObjectsSprite;
    }
}

PUBLIC void Level_CNZ::LoadZoneSpecificSprites() {
    if (!CNZObjectsSprite) {
		CNZObjectsSprite = new ISprite("Sprites/CNZ/Objects.gif", App);
		CNZObjectsSprite->Print = true;

        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Breakable Wall.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Balloon.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Button.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Cork Floor.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Cylinder.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Door Horizontal.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/End Boss.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Light Bulb.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Miniboss.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Rising Platform.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Trap Door.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Cannon.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Cannon Ball.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Cannon Base.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Bumper.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Clamer.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Batbot.bin");
        CNZObjectsSprite->LoadAnimation("Sprites/CNZ/Sparkle.bin");
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

PUBLIC void Level_CNZ::FinishResults() {
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
	}
	else {
		Level_ICZ* NextAct = new Level_ICZ(App, G, 1);
		TransferCommonLevelData(NextAct);
		App->NextScene = NextAct;
	}
}

PUBLIC void Level_CNZ::EarlyUpdate() {
    if (Act == 1) {
        // During the boss fight
        if (false) {
            Data->layers[1].Flags |= 0 | 2 | 4;
            Data->layers[1].OffsetX = 0x3180;
            Data->layers[1].OffsetY -= 4;
            if (Data->layers[1].OffsetY < 0x40)
                Data->layers[1].OffsetY += 0x100;
            Data->layers[3].OffsetY -= 4;
            if (Data->layers[3].OffsetY < -0x500)
                Data->layers[3].OffsetY += 0x100;

            CameraMinY = 0x1C0;

            CameraMinX = 0x31E0;
            CameraMaxX = 0x33A0 - App->WIDTH;
        }
        else {
            Data->layers[1].Visible = false;
        }
    }
    else if (Act == 2) {
        // Layer Flags:
        // 0x1: Collidable
        // 0x2: Don't Repeat X
        // 0x3: Don't Repeat Y
        Data->layers[1].Flags |= 0 | 2 | 4;
        Data->layers[1].OffsetX = 0x3480;
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

    }
    else if (Act == 2) {

    }
    LevelScene::HandleCamera();
}
