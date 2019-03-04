#if INTERFACE
#include <Game/LevelScene.h>

class Level_LBZ : public LevelScene {
public:
    ISprite* LBZObjectsSprite = NULL;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/LBZ.h>

PUBLIC Level_LBZ::Level_LBZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 6;
    VisualAct = Act = act;

    if (Act == 1) {
        Sound::SoundBank[0] = new ISound("Music/LBZ1.ogg", false);
		Sound::Audio->LoopPoint[0] = 0;

        Str_TileConfigBin = "Stages/LBZ1/TileConfig.bin";
        Str_SceneBin = "Stages/LBZ1/Scene.bin";
        Str_TileSprite = "Stages/LBZ1/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/LBZ1/Animated Tiles.gif";
    }
    else if (Act == 2) {
        Sound::SoundBank[0] = new ISound("Music/LBZ2.ogg", false);
		Sound::Audio->LoopPoint[0] = 0;

        Str_TileConfigBin = "Stages/LBZ2/TileConfig.bin";
        Str_SceneBin = "Stages/LBZ2/Scene.bin";
        Str_TileSprite = "Stages/LBZ2/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/LBZ2/Animated Tiles.gif";
    }

    sprintf(LevelName, "LAUNCH BASE");
    sprintf(LevelNameDiscord, "Launch Base");

    if (Act == 1) {
        // PlayerStartX = 0x00C0;
        // PlayerStartY = 0x05BC;

        PlayerStartX = 0x0CC8;
        PlayerStartY = 0x076C;
    }
    else {
		VisualWaterLevel = WaterLevel = 0x660;
    }
}

PUBLIC void Level_LBZ::RestartStage(bool doActTransition, bool drawBackground) {
    App->Audio->ClearMusic();
    if (Sound::SoundBank[0])
        App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

    LevelScene::RestartStage(doActTransition, drawBackground);
}

PUBLIC void Level_LBZ::AssignSpriteMapIDs() {
    LevelScene::AssignSpriteMapIDs();

	SpriteMapIDs[0x01] = ItemsSprite;
    SpriteMapIDs[0x04] = LBZObjectsSprite;
    SpriteMapIDs[0x05] = LBZObjectsSprite;
    SpriteMapIDs[0x06] = LBZObjectsSprite;
	SpriteMapIDs[0x07] = ObjectsSprite;
	SpriteMapIDs[0x08] = ObjectsSprite;
    SpriteMapIDs[0x09] = LBZObjectsSprite;
    SpriteMapIDs[0x0A] = LBZObjectsSprite;
    SpriteMapIDs[0x0C] = LBZObjectsSprite;
    SpriteMapIDs[0x0D] = LBZObjectsSprite;
    SpriteMapIDs[0x0F] = LBZObjectsSprite;
	SpriteMapIDs[0x2F] = LBZObjectsSprite;
	//SpriteMapIDs[0x33] = SpriteMap["HCZ"];
	SpriteMapIDs[0x34] = ObjectsSprite;
    SpriteMapIDs[0x35] = LBZObjectsSprite;

	SpriteMapIDs[0x51] = LBZObjectsSprite;
    SpriteMapIDs[0x8C] = LBZObjectsSprite;
}

PUBLIC void Level_LBZ::LoadZoneSpecificSprites() {
    if (!LBZObjectsSprite) {
		LBZObjectsSprite = new ISprite("Sprites/LBZ/Objects.gif", App);
		LBZObjectsSprite->Print = true;

		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Tunnel Exhaust.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Breakable Wall.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Collapsing Bridge.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Collapsing Ledge.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Cork Floor.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Cup Elevator.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Exploding Trigger.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Flame Thrower.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Exploding Trigger.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Gate Laser.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Knuckles Bomb.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Knuckles Pillar.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Lowering Grapple.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Floating Platform.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/PipePlug.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Player Launcher.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Ride Grapple.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Smashing Spikes.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Spin Launcher.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Trigger Bridge.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Tube Elevator.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Miniboss.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/End Boss.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Final Boss.bin");
		LBZObjectsSprite->LoadAnimation("Sprites/LBZ/Non Animated Sprites.bin");
	}

	if (!KnuxSprite[0]) {
		KnuxSprite[0] = new ISprite("Sprites/Player/Knux1.gif", App);
		KnuxSprite[1] = new ISprite("Sprites/Player/Knux2.gif", App);
		KnuxSprite[2] = new ISprite("Sprites/Player/Knux3.gif", App);
		KnuxSprite[3] = new ISprite("Sprites/Player/KnuxCutsceneAIZ.gif", App);
		KnuxSprite[4] = new ISprite("Sprites/Player/KnuxCutsceneASZ.gif", App);

		KnuxSprite[0]->LoadAnimation("Sprites/Player/Knux.bin");
		KnuxSprite[1]->LinkAnimation(KnuxSprite[0]->Animations);
		KnuxSprite[2]->LinkAnimation(KnuxSprite[0]->Animations);
		KnuxSprite[3]->LinkAnimation(KnuxSprite[0]->Animations);
		KnuxSprite[4]->LinkAnimation(KnuxSprite[0]->Animations);
	}
}

PUBLIC void Level_LBZ::FinishResults() {
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
PUBLIC void Level_LBZ::GoToNextAct() {
	if (VisualAct == 1) {
		Level_LBZ* NextAct = new Level_LBZ(App, G, 2);

		TransferCommonLevelData(NextAct);
		NextAct->LBZObjectsSprite = LBZObjectsSprite;
		// Enable Title Card with no fade-in
		NextAct->LevelCardTimer = 0.0;
		NextAct->FadeTimer = 0;
		NextAct->FadeAction = 0;
		NextAct->LevelCardHide = false;
		// Transfer over current frame
		NextAct->Frame = Frame;
		// Set player spawn position relative to their previous position  
		NextAct->SpecialSpawnPositionX = Player->EZX - 0x3A00;
		NextAct->SpecialSpawnPositionY = Player->EZY;
		NextAct->RoutineNumber = 0x00;

		App->NextScene = NextAct;
	}
	else {
		//Level_CNZ* NextAct = new Level_CNZ(App, G, 1);
		//TransferCommonLevelData(NextAct);
		//App->NextScene = NextAct;
	}
}

PUBLIC void Level_LBZ::EarlyUpdate() {
    if (Act == 1) {

    }
    else if (Act == 2) {

    }
    LevelScene::EarlyUpdate();
}
PUBLIC void Level_LBZ::Subupdate() {
    LevelScene::Subupdate();
}

PUBLIC void Level_LBZ::HandleCamera() {
    if (Act == 1) {

    }
    else if (Act == 2) {

    }
    LevelScene::HandleCamera();
}
