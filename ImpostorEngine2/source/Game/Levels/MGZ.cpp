#if INTERFACE
#include <Game/LevelScene.h>

class Level_MGZ : public LevelScene {
public:
	ISprite* MGZObjectsSprite = NULL;
	int32_t FloorY = 0; //
};
#endif

#include <Game/Explosion.h>
#include <Game/LevelScene.h>

#include <Game/Objects/Gen/ObjectListing.h>

#include <Game/Levels/MGZ.h>
#include <Game/Levels/CNZ.h>
#include <Game/Levels/FBZ.h>

#define ADD_OBJECT() ObjectProp op; op.X = X; op.Y = Y; op.ID = ID; op.SubType = SubType; op.LoadFlag = PRIORITY; op.FlipX = FLIPX; op.FlipY = FLIPY; ObjectProps[ObjectPropCount++] = op; Object* obj = GetNewObjectFromID(ID); if (obj) { obj->G = G; obj->App = App; obj->Scene = this; obj->InitialX = X; obj->InitialY = Y; obj->FlipX = FLIPX == 1; obj->FlipY = FLIPY == 1; while (!SpriteMapIDs.at(ID]) ID--; obj->Sprite = SpriteMapIDs.at(ID]; obj->SubType = SubType; obj->Create(); Objects[ObjectCount++] = obj; }

PUBLIC Level_MGZ::Level_MGZ(IApp* app, IGraphics* g, int act) : LevelScene(app, g) {
	ZoneID = 3;
	VisualAct = Act = act;
	sprintf(ZoneLetters, "MGZ");
	TintColor = 0xFF9034;
    
	if (SaveGame::CurrentMode >= 1)
	{
		if (Act == 1) {
			Str_TileConfigBin = "Mixed/Stages/MGZ1/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/MGZ1/Scene.bin";
			Str_TileSprite = "Mixed/Stages/MGZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/MGZ1/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/MGZ1/Stageconfig.bin";
		}
		else {
			Str_TileConfigBin = "Mixed/Stages/MGZ2/TileConfig.bin";
			Str_SceneBin = "Mixed/Stages/MGZ2/Scene.bin";
			Str_TileSprite = "Mixed/Stages/MGZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Mixed/Stages/MGZ2/Animated Tiles.gif";
			Str_StageBin = "Mixed/Stages/MGZ2/Stageconfig.bin";
		}
	}
	else
	{
		if (Act == 1) {
			Str_TileConfigBin = "Classic/Stages/MGZ1/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/MGZ1/Scene.bin";
			Str_TileSprite = "Classic/Stages/MGZ1/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/MGZ1/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/MGZ1/Stageconfig.bin";
		}
		else {
			Str_TileConfigBin = "Classic/Stages/MGZ2/TileConfig.bin";
			Str_SceneBin = "Classic/Stages/MGZ2/Scene.bin";
			Str_TileSprite = "Classic/Stages/MGZ2/16x16Tiles.gif";
			Str_AnimatedSprites = "Classic/Stages/MGZ2/Animated Tiles.gif";
			Str_StageBin = "Classic/Stages/MGZ2/Stageconfig.bin";
		}
	}

    AddNewDebugObjectID(Obj_TopPlatform); // Top Platform
    AddNewDebugObjectID(Obj_Spiker); 
    AddNewDebugObjectID(Obj_Mantis); 
    AddNewDebugObjectID(Obj_BubblesBadnik); 
    //Soon
	//AddNewDebugObjectID(Obj_TunnelBot); 
    //AddNewDebugObjectID(Obj_DrillMobile); 

	sprintf(LevelName, "MARBLE GARDEN");
	sprintf(LevelNameDiscord, "Marble Garden");
}

PUBLIC void Level_MGZ::Init() {
	PlayMusic(Act, SaveGame::CurrentMode == 0 ? (Act == 1 ? 0 : 193952) : 0, SaveGame::CurrentMode);

	LevelScene::Init();
}

PUBLIC void Level_MGZ::RestartStage(bool doActTransition, bool drawBackground) {
	App->Audio->ClearMusic();
	App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);

	LevelScene::RestartStage(doActTransition, drawBackground);

	// Data->Layers[1].IsScrollingVertical = true;
	// Data->Layers[2].IsScrollingVertical = true;

	if (Act == 1) {
		if (Checkpoint == -1)
			for (int p = 0; p < PlayerCount; p++)
				Players[p]->Action = ActionType::Peril;
	}
}

PUBLIC void Level_MGZ::FinishResults() {
	if (VisualAct == 1) {
		LevelScene::FinishResults();
	}
	else {
		FadeAction = FadeActionType::NEXT_ZONE;
		FadeTimerMax = 90;
		FadeMax = 0x140;
		G->FadeToWhite = false;
	}
}
PUBLIC void Level_MGZ::GoToNextAct() {
	if (VisualAct == 1) {
		Level_MGZ* NextAct = new Level_MGZ(App, G, 2);

		TransferCommonLevelData(NextAct);
		NextAct->MGZObjectsSprite = MGZObjectsSprite;
		MGZObjectsSprite = NULL;
		// Enable Title Card with no fade-in
		NextAct->LevelCardTimer = 0.0;
		NextAct->FadeTimer = 0;
		NextAct->FadeAction = 0;
		NextAct->LevelCardHide = false;
		// Transfer over current frame
		NextAct->Frame = Frame;
		// Set player spawn position relative to their previous position
		NextAct->SpecialSpawnPositionX = Player->EZX - 0x2E00;
		NextAct->SpecialSpawnPositionY = Player->EZY - 0x600;
		NextAct->RoutineNumber = 0x00;

		App->NextScene = NextAct;
	}
	else {
		Level_CNZ* NextAct = new Level_CNZ(App, G, 1);
		TransferCommonLevelData(NextAct);
		App->NextScene = NextAct;
	}
}

PUBLIC void Level_MGZ::AssignSpriteMapIDs() {
	LevelScene::AssignSpriteMapIDs();

	SpriteMapIDs.at(0x0D) = MGZObjectsSprite;
	SpriteMapIDs.at(0x0F) = MGZObjectsSprite;
	SpriteMapIDs.at(0x2F) = MGZObjectsSprite;
	SpriteMapIDs.at(0x51) = MGZObjectsSprite;
	SpriteMapIDs.at(0x52) = MGZObjectsSprite;
	SpriteMapIDs.at(0x5B) = MGZObjectsSprite;
	SpriteMapIDs.at(0x9B) = MGZObjectsSprite;
	SpriteMapIDs.at(0x9C) = MGZObjectsSprite;
	SpriteMapIDs.at(0x9D) = MGZObjectsSprite;
	SpriteMapIDs.at(0x9E) = MGZObjectsSprite;
	SpriteMapIDs.at(0x9F) = MGZObjectsSprite;
	SpriteMapIDs.at(0xA0) = MGZObjectsSprite;
	SpriteMapIDs.at(0xA1) = MGZObjectsSprite;
}

PUBLIC void Level_MGZ::LoadZoneSpecificSprites() {
	if (!MGZObjectsSprite) {
		MGZObjectsSprite = new ISprite("MGZ/Objects.gif", App);
		MGZObjectsSprite->Print = true;

		MGZObjectsSprite->LoadAnimation("MGZ/Collapsing Bridge.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Dash Trigger.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Floating Platform.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Head Trigger.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Pulley.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Breakable Wall.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Trigger Platform.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Swinging Platform.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Moving Spike Platform.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Smashing Pillar.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Swinging Spike Ball.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Top Platform.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Tunnelbot.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/DrillMobile.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Non Animated Sprites.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Bubbles.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Spiker.bin");
		MGZObjectsSprite->LoadAnimation("MGZ/Mantis.bin");
	}

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

PUBLIC void Level_MGZ::RenderAboveBackground() {
}
PUBLIC void Level_MGZ::RenderAboveForeground() {
}

PUBLIC void Level_MGZ::RenderEverything() {
	LevelScene::RenderEverything();
}

PUBLIC void Level_MGZ::EarlyUpdate() {
	// bool Thremixed = true;

	LevelScene::EarlyUpdate();
}
PUBLIC void Level_MGZ::Subupdate() {
	LevelScene::Subupdate();
}


PUBLIC void Level_MGZ::Cleanup() {
	#define CLEANUP(name) if (name) { name->Cleanup(); delete name; name = NULL; }

	CLEANUP(MGZObjectsSprite);
	LevelScene::Cleanup();
}

PUBLIC void Level_MGZ::HandleCamera() {
	// int offX = App->WIDTH / 2 - 0xA0;
	// int offY = App->HEIGHT / 2 - 0x70;

	// Layer Flags:
	// 0x1: Collidable
	// 0x2: Don't Repeat X
	// 0x3: Don't Repeat Y

	if (Act == 1) {
		Data->Layers[1].IsScrollingVertical = true;
		Data->Layers[2].IsScrollingVertical = true;
	}
	else if (Act == 2) {
		Data->Layers[1].Flags |= 1 | 0 | 4;
		Data->Layers[1].OffsetX = 0x3480;
		if (RoutineNumber == 0) {
			Data->Layers[1].OffsetY = 0x0B00;

			if (Player->EZX >= 0x36C0 &&
				Player->EZY >= 0xAD0) {
				RoutineNumber = 1;
			}
		}

		if (RoutineNumber == 1) {
			if (!(Frame & 0xF)) {
				Sound::Play(Sound::SFX_RUMBLE);
			}
			if ((FloorY >> 16) < 0x1C0) {
				FloorY += 0x00006000;
				ShakeTimer = -1;
			}
			if ((FloorY >> 16) >= 0x1C0) {
				ShakeTimer = 20;
				Sound::Stop(Sound::SFX_RUMBLE);
				Sound::Play(Sound::SFX_IMPACT4);
				RoutineNumber = 2;
			}
		}
		Data->Layers[1].OffsetY = 0x0B00 - (FloorY >> 16);

		if (Player->EZX >= 0x3000 &&
			Player->EZY >= 0x0680 &&
			Player->EZX < 0x3660 &&
			Player->EZY < 0x07F0) {
			Data->Layers[0].RelativeY = 0x0100;
			Data->Layers[0].OffsetX = 0x3580;
			Data->Layers[0].OffsetY = -0x8F0 + (FloorY >> 16);

			BackgroundColor = TileSprite->GetPalette(0x3A);
		}
		else if (Player->EZX >= 0x3000 &&
			Player->EZY >= 0x07F0 &&
			Player->EZX < 0x3E80 &&
			Player->EZY < 0x0C00) {
			Data->Layers[0].RelativeY = 0x0100;
			Data->Layers[0].OffsetX = 0x3580;
			Data->Layers[0].OffsetY = -0x8F0 + (FloorY >> 16);

			BackgroundColor = TileSprite->GetPalette(0x3A);
		}
		else if (Player->EZX > 0x3920 && Player->EZY < 0x7E8) {
			Data->Layers[0].RelativeY = 0x0030;
			Data->Layers[0].OffsetX = 0;
			Data->Layers[0].OffsetY = -0x00F0;

			BackgroundColor = TileSprite->GetPalette(0x31);
		}
		else {
			Data->Layers[0].RelativeY = 0x0030;
			Data->Layers[0].OffsetY = 0;
			BackgroundColor = TileSprite->GetPalette(0x3A);
		}
	}

	LevelScene::HandleCamera();
}