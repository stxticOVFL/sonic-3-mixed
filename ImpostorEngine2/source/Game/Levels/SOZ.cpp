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

    if (Act == 1) {
        Sound::SoundBank[0] = new ISound("Music/SOZ1.ogg", false);
		Sound::Audio->LoopPoint[0] = 0;

        Str_TileConfigBin = "Stages/SOZ1/TileConfig.bin";
        Str_SceneBin = "Stages/SOZ1/Scene.bin";
        Str_TileSprite = "Stages/SOZ1/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/SOZ1/Animated Tiles.gif";
    }
    else if (Act == 2) {
        Sound::SoundBank[0] = new ISound("Music/SOZ2.ogg", false);
		Sound::Audio->LoopPoint[0] = 0;

        Str_TileConfigBin = "Stages/SOZ2/TileConfig.bin";
        Str_SceneBin = "Stages/SOZ2/Scene.bin";
        Str_TileSprite = "Stages/SOZ2/16x16Tiles.gif";
        Str_AnimatedSprites = "Stages/SOZ2/Animated Tiles.gif";
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
