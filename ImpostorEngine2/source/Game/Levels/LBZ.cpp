#if INTERFACE
#include <Game/LevelScene.h>

class Level_LBZ : public LevelScene {
public:
    ISprite* AIZ1Sprite = NULL;
    ISprite* AIZ2Sprite = NULL;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/LBZ.h>

PUBLIC Level_LBZ::Level_LBZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 6;
    Act = act;

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
        PlayerStartX = 0x00C0;
        PlayerStartY = 0x05BC;
    }
    else {

    }
}

PUBLIC void Level_LBZ::RestartStage(bool doActTransition, bool drawBackground) {
    App->Audio->ClearMusic();
    if (Sound::SoundBank[0])
        App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

    LevelScene::RestartStage(doActTransition, drawBackground);
}

PUBLIC void Level_LBZ::AssignSpriteMapIDs() {
    if (Act <= 1) {
    	SpriteMapIDs[0x01] = ItemsSprite;
        SpriteMapIDs[0x04] = AIZ1Sprite;
        SpriteMapIDs[0x05] = AIZ1Sprite;
    	SpriteMapIDs[0x07] = ObjectsSprite;
    	SpriteMapIDs[0x08] = ObjectsSprite;
        SpriteMapIDs[0x09] = AIZ1Sprite;
        SpriteMapIDs[0x0A] = AIZ1Sprite;
        SpriteMapIDs[0x0C] = AIZ1Sprite;
        SpriteMapIDs[0x0D] = AIZ1Sprite;
        SpriteMapIDs[0x0F] = AIZ1Sprite;
    	SpriteMapIDs[0x2F] = AIZ1Sprite;
    	//SpriteMapIDs[0x33] = SpriteMap["HCZ"];
    	SpriteMapIDs[0x34] = ObjectsSprite;
        SpriteMapIDs[0x35] = AIZ1Sprite;

    	SpriteMapIDs[0x51] = AIZ1Sprite;
    }
    else {
    	SpriteMapIDs[0x01] = ItemsSprite;
        SpriteMapIDs[0x04] = AIZ2Sprite;
        SpriteMapIDs[0x05] = AIZ2Sprite;
        SpriteMapIDs[0x06] = AIZ1Sprite;
    	SpriteMapIDs[0x07] = ObjectsSprite;
    	SpriteMapIDs[0x08] = ObjectsSprite;
        SpriteMapIDs[0x09] = AIZ1Sprite;
        SpriteMapIDs[0x0A] = AIZ1Sprite;
        SpriteMapIDs[0x0C] = AIZ1Sprite;
        SpriteMapIDs[0x0D] = AIZ2Sprite;
        SpriteMapIDs[0x0F] = AIZ2Sprite;
    	SpriteMapIDs[0x2F] = AIZ1Sprite;
    	//SpriteMapIDs[0x33] = SpriteMap["HCZ"];
    	SpriteMapIDs[0x34] = ObjectsSprite;
        SpriteMapIDs[0x35] = AIZ1Sprite;

    	SpriteMapIDs[0x51] = AIZ2Sprite;
        SpriteMapIDs[0x8C] = AIZ1Sprite;
    }
}

PUBLIC void Level_LBZ::LoadZoneSpecificSprites() {
    if (!AIZ1Sprite) {
        AIZ1Sprite = new ISprite("Sprites/AIZ1/Objects.gif", App);
        AIZ1Sprite->LoadAnimation("Sprites/AIZ1/Bloominator.bin");
        AIZ1Sprite->LoadAnimation("Sprites/AIZ1/CaterkillerJr.bin");
        AIZ1Sprite->LoadAnimation("Sprites/AIZ1/CollapsingPlatform.bin");
        AIZ1Sprite->LoadAnimation("Sprites/AIZ1/CorkFloor.bin");
        AIZ1Sprite->LoadAnimation("Sprites/AIZ1/Decoration.bin");
        AIZ1Sprite->LoadAnimation("Sprites/AIZ1/FallingLog.bin");
        AIZ1Sprite->LoadAnimation("Sprites/AIZ1/MonkeyDude.bin");
        AIZ1Sprite->LoadAnimation("Sprites/AIZ1/Platform.bin");
        AIZ1Sprite->LoadAnimation("Sprites/AIZ1/Rhinobot.bin");
        AIZ1Sprite->LoadAnimation("Sprites/AIZ1/SwingRope.bin");
        AIZ1Sprite->LoadAnimation("Sprites/AIZ1/Tree.bin");
        AIZ1Sprite->LoadAnimation("Sprites/AIZ1/ZiplinePeg.bin");
        // printf("\n");
    }

    if (!AIZ2Sprite) {
        AIZ2Sprite = new ISprite("Sprites/AIZ2/Objects.gif", App);
        AIZ2Sprite->LoadAnimation("Sprites/AIZ1/Bloominator.bin");
        AIZ2Sprite->LoadAnimation("Sprites/AIZ1/CaterkillerJr.bin");
        AIZ2Sprite->LoadAnimation("Sprites/AIZ2/CollapsingPlatform.bin");
        AIZ2Sprite->LoadAnimation("Sprites/AIZ2/CorkFloor.bin");
        AIZ2Sprite->LoadAnimation("Sprites/AIZ1/Decoration.bin"); // HACK: padding
        AIZ2Sprite->LoadAnimation("Sprites/AIZ2/FallingLog.bin");
        AIZ2Sprite->LoadAnimation("Sprites/AIZ1/MonkeyDude.bin"); // HACK: padding
        AIZ2Sprite->LoadAnimation("Sprites/AIZ2/Platform.bin");

        AIZ2Sprite->LoadAnimation("Sprites/AIZ2/BreakableWall.bin");
        AIZ2Sprite->LoadAnimation("Sprites/AIZ2/Drawbridge.bin");
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
