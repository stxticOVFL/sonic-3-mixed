#if INTERFACE
#include <Game/LevelScene.h>

class Level_MGZ : public LevelScene {
public:
    int32_t FloorY = 0;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/MGZ.h>

#define ADD_OBJECT() ObjectProp op; op.X = X; op.Y = Y; op.ID = ID; op.SubType = SubType; op.LoadFlag = PRIORITY; op.FlipX = FLIPX; op.FlipY = FLIPY; ObjectProps[ObjectPropCount++] = op; Object* obj = GetNewObjectFromID(ID); if (obj) { obj->G = G; obj->App = App; obj->Scene = this; obj->InitialX = X; obj->InitialY = Y; obj->FlipX = FLIPX == 1; obj->FlipY = FLIPY == 1; while (!SpriteMapIDs[ID]) ID--; obj->Sprite = SpriteMapIDs[ID]; obj->SubType = SubType; obj->Create(); Objects[ObjectCount++] = obj; }

PUBLIC Level_MGZ::Level_MGZ(IApp* app, IGraphics* g, int ACT) : LevelScene(app, g) {
    ZoneID = 3;
    Act = ACT;

    if (Act == 1) {
		Sound::SoundBank[0] = new ISound("Music/MirageSaloon1K.ogg", true);
		Sound::Audio->LoopPoint[0] = 1007820;

        Str_TileConfigBin = "Stages/MGZ1/TileConfig.bin";
        Str_SceneBin = "Stages/MGZ1/Scene.bin";
        Str_TileSprite = "Stages/MGZ1/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/MGZ1/Animated Tiles.gif";
    }
    else {
        Sound::SoundBank[0] = new ISound("Music/MirageSaloon1K.ogg", true);
		Sound::Audio->LoopPoint[0] = 1007820;

        Str_TileConfigBin = "Stages/MGZ2/TileConfig.bin";
        Str_SceneBin = "Stages/MGZ2/Scene.bin";
        Str_TileSprite = "Stages/MGZ2/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/MGZ2/Animated Tiles.gif";
    }

    sprintf(LevelName, "MARBLE GARDEN");
    sprintf(LevelNameDiscord, "Marble Garden");

    if (Act == 1) {

    }
    else {
        // PlayerStartX = 0x34D8;
        // PlayerStartY = 0x0A30;
    }
}

PUBLIC void Level_MGZ::Init() {
    LevelScene::Init();
}

PUBLIC void Level_MGZ::RestartStage(bool doActTransition, bool drawBackground) {
    App->Audio->ClearMusic();
    App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

    LevelScene::RestartStage(doActTransition, drawBackground);

    // Data->layers[1].IsScrollingVertical = true;
    // Data->layers[2].IsScrollingVertical = true;

    if (Act == 1) {
        if (Checkpoint == -1)
            for (int p = 0; p < PlayerCount; p++)
                Players[p]->Action = ActionType::Peril;
    }
}

PUBLIC void Level_MGZ::GoToNextAct() {
    LevelScene* NextAct = new Level_MGZ(App, G, 2);
    NextAct->LevelCardTimer = 0.0;
    NextAct->FadeTimer = 0;
    NextAct->FadeAction = 0;
    NextAct->LevelCardHide = false;
    NextAct->Frame = Frame;

    NextAct->SpecialSpawnPositionX = Player->EZX - 0x3600;
    NextAct->SpecialSpawnPositionY = Player->EZY;
    NextAct->RoutineNumber = 0x69;

    NextAct->GiantRingModel = GiantRingModel;
    NextAct->ItemsSprite = ItemsSprite;
    NextAct->ItemsSprite = ItemsSprite;
    NextAct->ObjectsSprite = ObjectsSprite;
    NextAct->Objects2Sprite = Objects2Sprite;
    NextAct->ExplosionSprite = ExplosionSprite;
    NextAct->WaterSprite = WaterSprite;

    NextAct->SpriteMap["HCZ"] = SpriteMap["HCZ"];
    NextAct->SpriteMap["HCZ Enemies"] = SpriteMap["HCZ Enemies"];
    NextAct->SpriteMap["HCZ Boss"] = SpriteMap["HCZ Boss"];
    for (int i = 0; i < 5; i++) {
        NextAct->KnuxSprite[i] = KnuxSprite[i];
    }

    Player->ControlLocked = false;
    Player->ObjectControlled = 0x00;
    Player->Action = ActionType::Normal;
    Player->ChangeAnimation(Player->AnimationMap["Idle"]);
    NextAct->Player = Player;
    for (int p = 0; p < PlayerCount; p++) {
        NextAct->Players[p] = Players[p];
        NextAct->Players[p]->Scene = NextAct;
    }
    NextAct->PlayerCount = PlayerCount;

    NextAct->LoadData();
    App->NextScene = NextAct;
}

PUBLIC void Level_MGZ::AssignSpriteMapIDs() {
	SpriteMapIDs[0x01] = ItemsSprite;
	SpriteMapIDs[0x07] = ObjectsSprite;
	SpriteMapIDs[0x08] = ObjectsSprite;
    SpriteMapIDs[0x0D] = SpriteMap["MGZ"];
    SpriteMapIDs[0x0F] = SpriteMap["MGZ"];
	SpriteMapIDs[0x2F] = SpriteMap["HCZ"];
	SpriteMapIDs[0x33] = SpriteMap["HCZ"];
	SpriteMapIDs[0x34] = ObjectsSprite;
	SpriteMapIDs[0x36] = SpriteMap["HCZ"];
	SpriteMapIDs[0x38] = SpriteMap["HCZ"];
	SpriteMapIDs[0x39] = SpriteMap["HCZ"];
	SpriteMapIDs[0x3A] = SpriteMap["HCZ"];
	SpriteMapIDs[0x51] = SpriteMap["MGZ"];

	SpriteMapIDs[0x67] = SpriteMap["HCZ"];
	SpriteMapIDs[0x6C] = SpriteMap["HCZ"];
	SpriteMapIDs[0x6D] = SpriteMap["HCZ"];

	SpriteMapIDs[0x93] = SpriteMap["HCZ Enemies"];
	SpriteMapIDs[0x99] = SpriteMap["HCZ Boss"];
}

PUBLIC void Level_MGZ::LoadZoneSpecificSprites() {
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
	if (!SpriteMap["HCZ Enemies"]) {
		SpriteMap["HCZ Enemies"] = new ISprite("Sprites/HCZ/Enemies.gif", App);
		SpriteMap["HCZ Enemies"]->LoadAnimation("Sprites/HCZ/Blastoid.bin");
		SpriteMap["HCZ Enemies"]->LoadAnimation("Sprites/HCZ/Buggernaut.bin");
		SpriteMap["HCZ Enemies"]->LoadAnimation("Sprites/HCZ/TurboSpiker.bin");
		SpriteMap["HCZ Enemies"]->LoadAnimation("Sprites/HCZ/MegaChomper.bin");
		SpriteMap["HCZ Enemies"]->LoadAnimation("Sprites/HCZ/Pointdexter.bin");
		SpriteMap["HCZ Enemies"]->LoadAnimation("Sprites/HCZ/Jawz.bin");
		// printf("\n");
	}
	if (!SpriteMap["HCZ Boss"]) {
		SpriteMap["HCZ Boss"] = new ISprite("Sprites/HCZ/Boss.gif", App);
		SpriteMap["HCZ Boss"]->LoadAnimation("Sprites/HCZ/LaundroMobile.bin");
		// printf("\n");
	}

    if (!SpriteMap["MGZ"]) {
		SpriteMap["MGZ"] = new ISprite("Sprites/MGZ/Objects.gif", App);
        SpriteMap["MGZ"]->LoadAnimation("Sprites/MGZ/Collapsing Bridge.bin");
        SpriteMap["MGZ"]->LoadAnimation("Sprites/MGZ/Dash Trigger.bin");
        SpriteMap["MGZ"]->LoadAnimation("Sprites/MGZ/Floating Platform.bin");
        SpriteMap["MGZ"]->LoadAnimation("Sprites/MGZ/Head Trigger.bin");
        SpriteMap["MGZ"]->LoadAnimation("Sprites/MGZ/Pulley.bin");
        SpriteMap["MGZ"]->LoadAnimation("Sprites/MGZ/Breakable Wall.bin");
        SpriteMap["MGZ"]->LoadAnimation("Sprites/MGZ/Trigger Platform.bin");
        SpriteMap["MGZ"]->LoadAnimation("Sprites/MGZ/Swinging Platform.bin");
		// printf("\n");
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

PUBLIC void Level_MGZ::RenderAboveBackground() {

}
PUBLIC void Level_MGZ::RenderAboveForeground() {

}

PUBLIC void Level_MGZ::RenderEverything() {
    LevelScene::RenderEverything();
}

PUBLIC void Level_MGZ::EarlyUpdate() {
    // bool Thremixed = true;

    LevelScene::EarlyUpdate();
}
PUBLIC void Level_MGZ::Subupdate() {
    LevelScene::Subupdate();
}

PUBLIC void Level_MGZ::HandleCamera() {
    // int offX = App->WIDTH / 2 - 0xA0;
    // int offY = App->HEIGHT / 2 - 0x70;

    // Layer Flags:
    // 0x1: Collidable
    // 0x2: Don't Repeat X
    // 0x3: Don't Repeat Y

    if (Act == 2) {
        Data->layers[1].Flags |= 1 | 0 | 4;
        Data->layers[1].OffsetX = 0x3480;
        if (RoutineNumber == 0) {
            Data->layers[1].OffsetY = 0x0B00;

            if (Player->EZX >= 0x36C0 &&
                Player->EZY >= 0xAD0) {
                RoutineNumber = 1;
            }
        }

        if (RoutineNumber == 1) {
            if (!(Frame & 0xF)) {
                Sound::Play(Sound::SFX_RUMBLE);
            }
            if ((FloorY >> 16) < 0x1C0) {
                FloorY += 0x00006000;
                ShakeTimer = -1;
            }
            if ((FloorY >> 16) >= 0x1C0) {
                ShakeTimer = 20;
                Sound::Stop(Sound::SFX_RUMBLE);
                Sound::Play(Sound::SFX_IMPACT4);
                RoutineNumber = 2;
            }
        }
        Data->layers[1].OffsetY = 0x0B00 - (FloorY >> 16);

        if (Player->EZX >= 0x3000 &&
            Player->EZY >= 0x0680 &&
            Player->EZX <  0x3660 &&
            Player->EZY <  0x07F0) {
            Data->layers[0].RelativeY = 0x0100;
            Data->layers[0].OffsetX = 0x3580;
            Data->layers[0].OffsetY = -0x8F0 + (FloorY >> 16);

            BackgroundColor = TileSprite->Palette[0x3A];
        }
        else if (Player->EZX >= 0x3000 &&
            Player->EZY >= 0x07F0 &&
            Player->EZX <  0x3E80 &&
            Player->EZY <  0x0C00) {
            Data->layers[0].RelativeY = 0x0100;
            Data->layers[0].OffsetX = 0x3580;
            Data->layers[0].OffsetY = -0x8F0 + (FloorY >> 16);

            BackgroundColor = TileSprite->Palette[0x3A];
        }
        else if (Player->EZX > 0x3920 && Player->EZY < 0x7E8) {
            Data->layers[0].RelativeY = 0x0030;
            Data->layers[0].OffsetX = 0;
            Data->layers[0].OffsetY = -0x00F0;

            BackgroundColor = TileSprite->Palette[0x31];
        }
        else {
            Data->layers[0].RelativeY = 0x0030;
            Data->layers[0].OffsetY = 0;
            BackgroundColor = TileSprite->Palette[0x3A];
        }


    }

    LevelScene::HandleCamera();
}
