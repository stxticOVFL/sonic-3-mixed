#if INTERFACE
#include <Game/LevelScene.h>

class Level_LBZ : public LevelScene {
public:
    int  CutsceneRoutineNumber = 0x00;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/LBZ.h>

PUBLIC Level_LBZ::Level_LBZ(IApp* app, IGraphics* g) : LevelScene(app, g) {
    ZoneID = 6;
    Act = 1;

    if (Act == 1) {
        Sound::SoundBank[0] = new ISound("Music/LBZ1.ogg", false);
		Sound::Audio->LoopPoint[0] = 0;

        Str_TileConfigBin = "Stages/LBZ/TileConfig1.bin";
        Str_SceneBin = "Stages/LBZ/Scene1.bin";
        Str_TileSprite = "Stages/LBZ/16x16Tiles1.gif";
        //Str_AnimatedSprites = "Sprites/LBZ/AnimatedTiles";
        Str_ObjectsList = "Stages/LBZ/Objects1.bin";
        Str_RingsList = "Stages/LBZ/Rings1.bin";
    }

    sprintf(LevelName, "LAUNCH BASE");
    sprintf(LevelNameDiscord, "Launch Base");

    if (Act == 1) {
        PlayerStartX = 0x00C0;
        PlayerStartY = 0x05BC;
    }
    else {

    }
}

PUBLIC void Level_LBZ::RestartStage(bool doActTransition, bool drawBackground) {
    App->Audio->ClearMusic();
    App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

    LevelScene::RestartStage(doActTransition, drawBackground);

    if (Act == 1) {

    }
}

PUBLIC void Level_LBZ::LoadZoneSpecificSprites() {
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

    LevelScene::HandleCamera();
}
