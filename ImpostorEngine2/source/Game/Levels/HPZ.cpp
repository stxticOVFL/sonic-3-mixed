#if INTERFACE
#include <Game/LevelScene.h>

class Level_HPZ : public LevelScene {
public:
    int  CutsceneRoutineNumber = 0x00;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/HPZ.h>

PUBLIC Level_HPZ::Level_HPZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 7;
    Act = act;
	sprintf(ZoneLetters, "HPZ");
	PlayMusic(act, 0, SaveGame::CurrentMode);
	if (Act == 1) {
        Str_TileConfigBin = "Stages/HPZ/TileConfig1.bin";
        Str_SceneBin = "Stages/HPZ/Scene1.bin";
        Str_TileSprite = "Stages/HPZ/16x16Tiles1.gif";
        //Str_AnimatedSprites = "HPZ/AnimatedTiles";
        Str_ObjectsList = "Stages/HPZ/Objects1.bin";
        Str_RingsList = "Stages/HPZ/Rings1.bin";
    }

    sprintf(LevelName, "HIDDEN PALACE");
    sprintf(LevelNameDiscord, "Hidden Palace");

    if (Act == 1) {
        // PlayerStartX = 0x00D8;
        // PlayerStartY = 0x0500;
    }
    else {

    }
}

PUBLIC void Level_HPZ::LoadZoneSpecificSprites() {
	if (!KnuxSprite[0]) {
<<<<<<< HEAD
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
=======
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
>>>>>>> 8ca042d82762e8a747aa4b41005ffff6b63e5665
}

PUBLIC void Level_HPZ::RestartStage(bool doActTransition, bool drawBackground) {
    LevelScene::RestartStage(doActTransition, drawBackground);

    if (Act == 1) {

    }
}

PUBLIC void Level_HPZ::EarlyUpdate() {
    if (Act == 1) {

    }
    else if (Act == 2) {

    }

    LevelScene::EarlyUpdate();
}
PUBLIC void Level_HPZ::Subupdate() {
    LevelScene::Subupdate();
}

PUBLIC void Level_HPZ::HandleCamera() {
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
