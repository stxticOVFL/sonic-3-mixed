#if INTERFACE
#include <Game/LevelScene.h>

class Level_FBZ : public LevelScene {
public:

};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/FBZ.h>

PUBLIC Level_FBZ::Level_FBZ(IApp* app, IGraphics* g, int ACT) : LevelScene(app, g) {
    ZoneID = 8;
    Act = ACT;

    if (Act == 1) {
        Str_TileConfigBin = "Stages/FBZ1/TileConfig.bin";
        Str_SceneBin = "Stages/FBZ1/Scene.bin";
        Str_TileSprite = "Stages/FBZ1/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/FBZ1/Animated Tiles.gif";
    }
    else {
        Str_TileConfigBin = "Stages/FBZ2/TileConfig.bin";
        Str_SceneBin = "Stages/FBZ2/Scene.bin";
        Str_TileSprite = "Stages/FBZ2/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/FBZ2/Animated Tiles.gif";
    }

    sprintf(LevelName, "FLYING BATTERY");
    sprintf(LevelNameDiscord, "Flying Battery");
}

PUBLIC void Level_FBZ::RestartStage(bool doActTransition, bool drawBackground) {
    LevelScene::RestartStage(doActTransition, drawBackground);
}

PUBLIC void Level_FBZ::AssignSpriteMapIDs() {
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

PUBLIC void Level_FBZ::LoadZoneSpecificSprites() {
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

PUBLIC void Level_FBZ::EarlyUpdate() {
    if (Act == 1) {

    }
    else if (Act == 2) {

    }

    LevelScene::EarlyUpdate();
}
PUBLIC void Level_FBZ::Subupdate() {
    LevelScene::Subupdate();
}

PUBLIC void Level_FBZ::HandleCamera() {


    LevelScene::HandleCamera();
}
