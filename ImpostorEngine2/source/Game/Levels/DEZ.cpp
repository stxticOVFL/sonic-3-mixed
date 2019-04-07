#if INTERFACE
#include <Game/LevelScene.h>

class Level_DEZ : public LevelScene {
public:
    int  CutsceneRoutineNumber = 0x00;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/DEZ.h>

PUBLIC Level_DEZ::Level_DEZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 7;
    Act = act;
	sprintf(ZoneLetters, "DEZ");
	PlayMusic(act, SaveGame::CurrentMode == 0 ? (act == 1 ? 0 : 0) : (act == 1 ? 76070 : 0), SaveGame::CurrentMode);

	if (SaveGame::CurrentMode >= 1)
	{
		if (Act == 1) {
			Str_TileConfigBin = "Mixed/Stages/DEZ1/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/DEZ1/Scene.bin";
			Str_TileSprite = "Mixed/Stages/DEZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/DEZ1/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/DEZ1/Stageconfig.bin";
		}
		else {
			Str_TileConfigBin = "Mixed/Stages/DEZ2/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/DEZ2/Scene.bin";
			Str_TileSprite = "Mixed/Stages/DEZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/DEZ2/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/DEZ2/Stageconfig.bin";
		}
	}
	else
	{
		if (Act == 1) {
			Str_TileConfigBin = "Classic/Stages/DEZ1/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/DEZ1/Scene.bin";
			Str_TileSprite = "Classic/Stages/DEZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/DEZ1/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/DEZ1/Stageconfig.bin";
		}
		else {
			Str_TileConfigBin = "Classic/Stages/DEZ2/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/DEZ2/Scene.bin";
			Str_TileSprite = "Classic/Stages/DEZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/DEZ2/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/DEZ2/Stageconfig.bin";
		}
	}

    sprintf(LevelName, "DEATH EGG");
    sprintf(LevelNameDiscord, "Death Egg");

    if (Act == 1) {
        // PlayerStartX = 0x00D8;
        // PlayerStartY = 0x0500;
    }
    else {

    }
}

PUBLIC void Level_DEZ::LoadZoneSpecificSprites() {
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

PUBLIC void Level_DEZ::RestartStage(bool doActTransition, bool drawBackground) {
    LevelScene::RestartStage(doActTransition, drawBackground);

    if (Act == 1) {

    }
}

PUBLIC void Level_DEZ::EarlyUpdate() {
    if (Act == 1) {

    }
    else if (Act == 2) {

    }

    LevelScene::EarlyUpdate();
}
PUBLIC void Level_DEZ::Subupdate() {
    LevelScene::Subupdate();
}

PUBLIC void Level_DEZ::HandleCamera() {
    if (Act == 1) {
        //int off = App->WIDTH / 2 - 0xA0;
        //int ToS3X = CameraX + off;
        if (false) { // SKAlone
            CameraMinX = 0x680;
            if (CameraX < 0x680) {
                CameraX = 0x680;
            }
        }
        else {
            if (Player->EZY < 0x580) {
                CameraMinX = 0xC0;
                if (CameraX < 0xC0) {
                    CameraX = 0xC0;
                }
            }
        }

        /*int MaxY = 0x0;
        MaxY += 0xE0;
        MaxY -= App->HEIGHT;
        if (CameraY > MaxY) {
            CameraY = MaxY;
        }*/
    }

    LevelScene::HandleCamera();
}
