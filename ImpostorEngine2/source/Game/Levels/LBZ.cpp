#if INTERFACE
#include <Game/LevelScene.h>

class Level_LBZ : public LevelScene {
public:
    ISprite* LBZObjectsSprite = NULL;
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/LBZ.h>

PUBLIC Level_LBZ::Level_LBZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
    ZoneID = 6;
    VisualAct = Act = act;

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
        // PlayerStartX = 0x00C0;
        // PlayerStartY = 0x05BC;

        PlayerStartX = 0x0CC8;
        PlayerStartY = 0x076C;
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
    LevelScene::AssignSpriteMapIDs();

	SpriteMapIDs[0x01] = ItemsSprite;
    SpriteMapIDs[0x04] = LBZObjectsSprite;
    SpriteMapIDs[0x05] = LBZObjectsSprite;
    SpriteMapIDs[0x06] = LBZObjectsSprite;
	SpriteMapIDs[0x07] = ObjectsSprite;
	SpriteMapIDs[0x08] = ObjectsSprite;
    SpriteMapIDs[0x09] = LBZObjectsSprite;
    SpriteMapIDs[0x0A] = LBZObjectsSprite;
    SpriteMapIDs[0x0C] = LBZObjectsSprite;
    SpriteMapIDs[0x0D] = LBZObjectsSprite;
    SpriteMapIDs[0x0F] = LBZObjectsSprite;
	SpriteMapIDs[0x2F] = LBZObjectsSprite;
	//SpriteMapIDs[0x33] = SpriteMap["HCZ"];
	SpriteMapIDs[0x34] = ObjectsSprite;
    SpriteMapIDs[0x35] = LBZObjectsSprite;

	SpriteMapIDs[0x51] = LBZObjectsSprite;
    SpriteMapIDs[0x8C] = LBZObjectsSprite;
}

PUBLIC void Level_LBZ::LoadZoneSpecificSprites() {
    if (!LBZObjectsSprite) {
		LBZObjectsSprite = new ISprite("Sprites/AIZ/Objects.gif", App);
		LBZObjectsSprite->Print = true;

        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Act 1 Tree.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Act 1 Zipline Peg.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Animated Sprites.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Breakable Wall.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Caterkiller Jr.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Collapsing Log Bridge.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Collapsing Platform.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Collapsing Platform 2.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Cork Floor.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Cork Floor 2.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Disappearing Floor.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Disappearing Floor Water.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Drawbridge.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Draw Bridge Fire.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Falling Log (Act 1).bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Falling Log (Act 2).bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Falling Log Splash (Act 1).bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Falling Log Splash (Act 2).bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Flipping Bridge.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Floating Platform.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Floating Platform 2.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Foreground Plant.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Monkey Dude.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Non Animated Sprites.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Rhinobot.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/RhinoBot Dust.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Ride Vine.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Rock.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Rock Bits.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Rock 2.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Rock Bits 2.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Spiked Log.bin");
        LBZObjectsSprite->LoadAnimation("Sprites/AIZ/Tulipon.bin");
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
