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

PUBLIC Level_FBZ::Level_FBZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 8;
    VisualAct = Act = act;
	sprintf(ZoneLetters, "FBZ");
	PlayMusic(act, 0, SaveGame::CurrentMode);

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
    LevelScene::AssignSpriteMapIDs();

	SpriteMapIDs.at(0x01) = ItemsSprite;
	SpriteMapIDs.at(0x07) = ObjectsSprite;
	SpriteMapIDs.at(0x08) = ObjectsSprite;
    SpriteMapIDs.at(0x0D) = SpriteMap["MGZ"];
    SpriteMapIDs.at(0x0F) = SpriteMap["MGZ"];
	SpriteMapIDs.at(0x2F) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x34) = ObjectsSprite;
	SpriteMapIDs.at(0x36) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x38) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x39) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x3A) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x51) = SpriteMap["MGZ"];

	SpriteMapIDs.at(0x67) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x6C) = SpriteMap["HCZ"];
	SpriteMapIDs.at(0x6D) = SpriteMap["HCZ"];

	SpriteMapIDs.at(0x93) = SpriteMap["HCZ Enemies"];
	SpriteMapIDs.at(0x99) = SpriteMap["HCZ Boss"];
}

PUBLIC void Level_FBZ::LoadZoneSpecificSprites() {
	if (!SpriteMap["HCZ"]) {
		SpriteMap["HCZ"] = new ISprite("HCZ/Objects.gif", App);
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
		SpriteMap["HCZ Boss"]->LoadAnimation("HCZ/LaundroMobile.bin");
	}

    if (!SpriteMap["MGZ"]) {
		SpriteMap["MGZ"] = new ISprite("MGZ/Objects.gif", App);
        SpriteMap["MGZ"]->LoadAnimation("MGZ/Collapsing Bridge.bin");
        SpriteMap["MGZ"]->LoadAnimation("MGZ/Dash Trigger.bin");
        SpriteMap["MGZ"]->LoadAnimation("MGZ/Floating Platform.bin");
        SpriteMap["MGZ"]->LoadAnimation("MGZ/Head Trigger.bin");
        SpriteMap["MGZ"]->LoadAnimation("MGZ/Pulley.bin");
        SpriteMap["MGZ"]->LoadAnimation("MGZ/Breakable Wall.bin");
        SpriteMap["MGZ"]->LoadAnimation("MGZ/Trigger Platform.bin");
        SpriteMap["MGZ"]->LoadAnimation("MGZ/Swinging Platform.bin");
	}

    if (!KnuxSprite[0]) {
        KnuxSprite[0] = new ISprite("Players/Knux1.gif", App);
        KnuxSprite[1] = new ISprite("Players/Knux2.gif", App);
        KnuxSprite[2] = new ISprite("Players/Knux3.gif", App);
        KnuxSprite[3] = new ISprite("Players/KnuxCutsceneAIZ.gif", App);
        KnuxSprite[4] = new ISprite("Players/KnuxCutsceneHPZ.gif", App);

        KnuxSprite[0]->LoadAnimation("Players/Knux.bin");
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
