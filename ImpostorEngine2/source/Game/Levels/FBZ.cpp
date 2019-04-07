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

	if (SaveGame::CurrentMode >= 1)
	{
		if (Act == 1) {
			Str_TileConfigBin = "Mixed/Stages/FBZ1/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/FBZ1/Scene.bin";
			Str_TileSprite = "Mixed/Stages/FBZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/FBZ1/Animated Tiles.gif";
		}
		else {
			Str_TileConfigBin = "Mixed/Stages/FBZ2/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/FBZ2/Scene.bin";
			Str_TileSprite = "Mixed/Stages/FBZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/FBZ2/Animated Tiles.gif";
		}
	}
	else
	{
		if (Act == 1) {
			Str_TileConfigBin = "Classic/Stages/FBZ1/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/FBZ1/Scene.bin";
			Str_TileSprite = "Classic/Stages/FBZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/FBZ1/Animated Tiles.gif";
		}
		else {
			Str_TileConfigBin = "Classic/Stages/FBZ2/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/FBZ2/Scene.bin";
			Str_TileSprite = "Classic/Stages/FBZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/FBZ2/Animated Tiles.gif";
		}
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
	SpriteMapIDs.at(0x34) = ObjectsSprite;
}

PUBLIC void Level_FBZ::LoadZoneSpecificSprites() {

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
