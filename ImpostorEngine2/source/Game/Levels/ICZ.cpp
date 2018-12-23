#if INTERFACE
#include <Game/LevelScene.h>

class Level_ICZ : public LevelScene {
public:

};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/ICZ.h>

PUBLIC Level_ICZ::Level_ICZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 5;
    Act = act;

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

PUBLIC void Level_ICZ::LoadZoneSpecificSprites() {
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

PUBLIC void Level_ICZ::EarlyUpdate() {
    if (Act == 1) {

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
