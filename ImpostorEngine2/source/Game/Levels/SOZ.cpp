#if INTERFACE
#include <Game/LevelScene.h>

class Level_SOZ : public LevelScene {
public:

};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/SOZ.h>

PUBLIC Level_SOZ::Level_SOZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 9;
    VisualAct = Act = act;
	sprintf(ZoneLetters, "SOZ");
	PlayMusic(act, 0, SaveGame::CurrentMode);

	if (SaveGame::CurrentMode >= 1)
	{
		if (Act == 1) {
			Str_TileConfigBin = "Mixed/Stages/SOZ1/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/SOZ1/Scene.bin";
			Str_TileSprite = "Mixed/Stages/SOZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/SOZ1/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/SOZ1/Stageconfig.bin";
		}
		else {
			Str_TileConfigBin = "Mixed/Stages/SOZ2/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/SOZ2/Scene.bin";
			Str_TileSprite = "Mixed/Stages/SOZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/SOZ2/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/SOZ2/Stageconfig.bin";
			ScreenYWrapValue = 0x7FF;
		}
	}
	else
	{
		if (Act == 1) {
			Str_TileConfigBin = "Classic/Stages/SOZ1/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/SOZ1/Scene.bin";
			Str_TileSprite = "Classic/Stages/SOZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/SOZ1/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/SOZ1/Stageconfig.bin";
		}
		else {
			Str_TileConfigBin = "Classic/Stages/SOZ2/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/SOZ2/Scene.bin";
			Str_TileSprite = "Classic/Stages/SOZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/SOZ2/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/SOZ2/Stageconfig.bin";
			ScreenYWrapValue = 0x7FF;
		}
	}

    sprintf(LevelName, "SANDOPOLIS");
    sprintf(LevelNameDiscord, "Sandopolis");

    if (Act == 1) {

    }
    else if (Act == 2) {

    }
}

PUBLIC void Level_SOZ::RestartStage(bool doActTransition, bool drawBackground) {
    App->Audio->ClearMusic();
    if (Sound::SoundBank[0])
        App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

    LevelScene::RestartStage(doActTransition, drawBackground);
}

PUBLIC void Level_SOZ::LoadZoneSpecificSprites() {
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

PUBLIC void Level_SOZ::EarlyUpdate() {
    if (Act == 1) {

    }
    else if (Act == 2) {

    }
    LevelScene::EarlyUpdate();
}
PUBLIC void Level_SOZ::Subupdate() {
    LevelScene::Subupdate();
}

PUBLIC void Level_SOZ::HandleCamera() {
    if (Act == 1) {

    }
    else if (Act == 2) {

    }
    LevelScene::HandleCamera();
}
