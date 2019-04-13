#if INTERFACE
#include <Utils/Standard.h>

#include <Engine/IScene.h>
#include <Engine/IResources.h>
#include <Engine/IStreamer.h>
#include <Engine/IGraphics.h>
#include <Engine/IModel.h>
#include <Engine/ISound.h>
#include <Engine/IAudio.h>

#include <Game/LevelSceneExt.h>
#include <Game/Object.h>
#include <Game/Player.h>
#include <Game/ObjectNames.h>

#include <Game/Explosion.h>

class LevelScene : public IScene {
    public:
        SceneData* Data = NULL;
        ISprite* TileSprite = NULL;
        ISprite* AnimTileSprite = NULL;
        int FGLayer = 0;

        int RingAnimationFrame = 0;
        int WaterAnimationFrame = 0;

        int32_t CameraX = 0;
        int32_t CameraY = 0;
        int32_t CameraMinX = 0;
        int32_t CameraMinY = 0;
        int32_t CameraMaxX = 0xFFFF;
        int32_t CameraMaxY = 0xFFFF;
        int32_t CameraDeltaX = 0;
        int32_t CameraDeltaY = 0;
        int CameraAutoScrollX = 0;
        int CameraAutoScrollY = 0;
        size_t ScreenXWrapValue = -1;
        size_t ScreenYWrapValue = -1;
        int Frame = 0;
        int Timer = 0;
        int Score = 0;

        int WaterLevel = 0xFFFF;
        int VisualWaterLevel = 0xFFFF;

        int PauseAnim[8];
        int PauseSelectedMenuItem = 0;
        bool Paused = false;
        bool PauseFinished = false;
        int paltimer = 0;
        int palframe = 0;

        ISprite* PauseSprite = NULL;
        ISprite* GlobalDisplaySprite = NULL;
        ISprite* MobileButtonsSprite = NULL;
        ISprite* SuperButtonsSprite = NULL;
        ISprite* EditorSprite = NULL;
        ISprite* ItemsSprite = NULL;
        ISprite* AnimalsSprite = NULL;
        ISprite* ObjectsSprite = NULL;
        ISprite* Objects2Sprite = NULL;
        ISprite* Objects3Sprite = NULL;
        ISprite* RobotnikSprite = NULL;
        ISprite* ExplosionSprite = NULL;
        ISprite* WaterSprite = NULL;
        ISprite* KnuxSprite[6];

        IPlayer* Player = NULL;
        IPlayer* Players[7];
        IPlayer* PlayerBuffer[2];
        int PlayerCount = 1;
        PlaneSwitch*PlaneSwitchers = NULL;
        int PlaneSwitchCount = 0;

        int PlayerStartX = -1;
        int PlayerStartY = -1;

        int RoutineNumber = 0;
        int LevelTriggerFlag = 0;

        int FadeAction = 0;
        enum FadeActionType {
            FADEIN = 1,
            RESTART = 2,
            EXIT = 3,
            DIED = 4,
            TO_BONUS_STAGE = 5,
            TO_SPECIAL_STAGE = 7,
            NEXT_ZONE = 8,
            CUSTOM_FADE_ACTION = 9,
        };

		//0 = Itemball, 1 = Pachinko, 2 = Slots
		int NextBonusStage = 0;

        //For RPC
        char* ModeName;

        int maxLayer = 1;
		Uint8 SceneMode = 0xFF;
        bool Thremixed = false;
        bool DeformObjects = false;
        bool DeformPlayer = false;

        //Object** Objects;
        std::vector<Object*> Objects;
        int ObjectCount = 0;
        int ObjectNewCount = 0;

        std::vector<Object*> ObjectsSolid;
        int ObjectSolidCount = 0;

        std::vector<Object*> ObjectsSpring;
        int ObjectSpringCount = 0;

        std::vector<Enemy*> ObjectsEnemies;
        int ObjectEnemiesCount = 0;

        std::vector<Object*> ObjectsBreakable;
        int ObjectBreakableCount = 0;

        std::vector<Object*> ObjectsPathSwitcher;
        int ObjectPathSwitcherCount = 0;

        int16_t* DebugObjectIDList;
        int32_t DebugObjectIDCount = 0;

        std::unordered_map<std::string, ISprite*> SpriteMap;
        std::vector<ISprite *> SpriteMapIDs;

        static std::unordered_map<std::string, size_t> SpriteBinMap;
        static std::vector<ISprite *> SpriteBinMapIDs;

        int ZoneID = 0;
        int Act = 1;
        int VisualAct = 1;
        bool CanWaterRun = true;
        static char ZoneLetters[3];

        int DEBUG_MOUSE_X = -1;
        int DEBUG_MOUSE_Y = -1;

        std::vector<Object*> TempObjects;
        std::vector<Object*> TempObjectTiles;

        struct ObjectProp {
            uint16_t X = 0x00;
            int16_t Y = 0x00;
            uint8_t ID = 0x00;
            uint8_t SubType = 0x00;
            bool LoadFlag = false;
            bool FlipX = false;
            bool FlipY = false;
        };

        std::vector<ObjectProp> ObjectProps;
        int ObjectPropCount = 0;

        std::vector<ObjectProp> RingProps;
        int RingPropCount = 0;

        ObjectProp* AnimatedSprite0Props = NULL;
        int AnimatedSprite0PropCount = 0;

        ObjectProp* AnimatedSprite1Props = NULL;
        int AnimatedSprite1PropCount = 0;

        double LevelCardTimer = 0.0;
        bool LevelCardHide = false;

        char LevelName[20];
        char LevelNameDiscord[30];
        bool SKAlone = false;

        bool HUDVisible = true;
        int HUDAnim = 0x00;
        bool ControlsVisible = true;
        int ControlsAnim = 0x00;

        bool ManiaLevel = false;
        bool SonicKnucklesLevel = false;

        const char* Str_TileConfigBin = NULL;
        const char* Str_SceneBin = NULL;
        const char* Str_TileSprite = NULL;
        const char* Str_StageBin = NULL;
        const char* Str_AnimatedSprites = NULL;
        const char* Str_ObjectsList = NULL;
        const char* Str_RingsList = NULL;

        uint8_t CharacterFlag = 0;

        int BackgroundRepeatTileX = 0;
        int BackgroundRepeatTileWidth = 0;

        IModel* GiantRingModel = NULL;

        int Checkpoint = -1;
        int SavedPositionX = -1;
        int SavedPositionY = -1;
        uint32_t*  SavedPalette = NULL;

        int WaterEnteredCounter = 0;

        ISound** SoundBank = NULL;

        uint8_t* PerspectiveMap;

        int ShakeTimer = 0;

        bool ResetTimer = true;
        bool StopTimer = false;
        bool ShowResults = false;
        bool DoneSpinning = false;
        int ResultsTimer = 0;
        int TimerTotal = 0;
        int TotalToAdd = 0;

        int SpecialSpawnPositionX = -1;
        int SpecialSpawnPositionY = -1;

        bool CollisionCheckForClimbable = false;
        bool CollisionCheckForAlternate = false;
        bool CollisionCheckForAlternate2 = false;

        uint32_t BackgroundColor = 0x000000;
		uint32_t TintColor = 0x000000;
        bool SepThread = false;
        uint16_t Signal[8]; //

        bool ViewPalettes = false;
        bool ViewPathswitchers = false;
        bool ViewPlayerStats = false;
        bool ViewPlayerUpdateStats = false;
        bool ViewTileInfo = false;
        bool ViewTileCollision = false;
        
        void* operator new(size_t const size);
        void* operator new(size_t const size, std::nothrow_t const&) noexcept;
        void operator delete(void* const block) noexcept;

		enum Achevements {
			ACHIEVEMENT_RINGHOG,
			ACHIEVEMENT_POWERHOUR,
			ACHIEVEMENT_SUPERAQUIRED,
			ACHIEVEMENT_HYPERAQUIRED,
		};
};
#endif

#include <Engine/IInput.h>

#include <Game/Ring.h>
#include <Game/FallingTile.h>
#include <Game/MovingSprite.h>
#include <Game/ScoreGhost.h>
#include <Game/LevelScene.h>
#include <Game/Animal.h>
#include <Game/Sound.h>

#include <Game/Objects/Gen/ObjectListing.h>
#include <Game/Object.h>

#include <Game/Scenes/DataSelect.h>
#include <Game/Scenes/LevelSelect.h>

#include <Game/Levels/SpecialStage.h>
#include <Game/Levels/BonusStage.h>

#include <Game/SaveGame.h>
#include <Engine/Diagnostics/Memory.h>

#define ADD_OBJECT() ObjectProp op; op.X = X; op.Y = Y; op.ID = ID; op.SubType = SubType; op.LoadFlag = PRIORITY; op.FlipX = FLIPX; op.FlipY = FLIPY; ObjectPropCount++; ObjectProps.push_back(op); Object* obj = GetNewObjectFromID(ID); if (obj) { obj->G = G; obj->App = App; obj->Scene = this; obj->InitialX = X; obj->InitialY = Y; obj->FlipX = FLIPX == 1; obj->FlipY = FLIPY == 1; obj->ID = ID; while (!SpriteMapIDs.at(ID)) ID--; obj->Sprite = SpriteMapIDs.at(ID); obj->SubType = SubType; ObjectCount++; Objects.push_back(obj); }
const char* ObjectName[347];

int BlankTile = 0;

std::unordered_map<std::string, size_t> LevelScene::SpriteBinMap;
std::vector<ISprite *> LevelScene::SpriteBinMapIDs;
char LevelScene::ZoneLetters[3];

PUBLIC LevelScene::LevelScene(IApp* app, IGraphics* g) {
	App = app;
	G = g;

	int ObjectID = GetObjectIDFromName("Motobug");
	App->Print(0, "ObjectID: %d", ObjectID);
	// Memory::ClearTrackedMemory();

	//Create Achievements Here (may change later lol)
	App->Achievements->CreateAchievement("Ring Hog");
	App->Achievements->CreateAchievement("Power Hour");
	App->Achievements->CreateAchievement("Super Form Aquired!");
	App->Achievements->CreateAchievement("Hyper Form Aquired");

	//Load up our achievement states
	for (int i = 0; i < TOTAL_ACHIEVEMENT_COUNT; i++)
	{
		App->Achievements->AchievementList[i].Achieved = SaveGame::AchievementData[i];
	}

	if (App->DEV) {
		App->Settings->GetBool("dev", "viewPalettes", &ViewPalettes);
		App->Settings->GetBool("dev", "viewPathswitchers", &ViewPathswitchers);
		App->Settings->GetBool("dev", "viewPlayerStats", &ViewPlayerStats);
		App->Settings->GetBool("dev", "viewPlayerUpdateStats", &ViewPlayerUpdateStats);
		App->Settings->GetBool("dev", "viewTileInfo", &ViewTileInfo);
		App->Settings->GetBool("dev", "viewTileCollision", &ViewTileCollision);
	}

	uint64_t startTime = SDL_GetTicks();

	Sound::Audio = App->Audio;
	Sound::Init();
	SaveGame::Init();

	IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "Sound::Init()", (SDL_GetTicks() - startTime) / 1000.0);
	startTime = SDL_GetTicks();

	std::memset(Signal, 0, sizeof(Signal));

	Objects.reserve(2000);
    Objects.assign(2000, NULL);
	ObjectsSolid.reserve(1000);
    ObjectsSolid.assign(1000, NULL);
	ObjectsSpring.reserve(300);
    ObjectsSpring.assign(300, NULL);
	ObjectsEnemies.reserve(300);
    ObjectsEnemies.assign(300, NULL);
	ObjectsBreakable.reserve(300);
    ObjectsBreakable.assign(300, NULL);
	ObjectsPathSwitcher.reserve(300);
    ObjectsPathSwitcher.assign(300, NULL);

	DebugObjectIDList = (int16_t*)Memory::TrackedCalloc("LevelScene::DebugObjectIDList", 0xFF, sizeof(int16_t));
	for (int i = 0; i < 0xFF; i++) {
		DebugObjectIDList[i] = 0;
	}
	AddNewDebugObjectID(Obj_Ring); // Ring
	AddNewDebugObjectID(Obj_Monitor); // Monitor
	AddNewDebugObjectID(Obj_StarPost); // StarPost
	AddNewDebugObjectID(Obj_Signpost); // SignPost
	AddNewDebugObjectID(Obj_EggCapsule); // SignPost
	AddNewDebugObjectID(Obj_SpecialRing); // Special Ring
	AddNewDebugObjectID(Obj_Spring); // Spring
	AddNewDebugObjectID(Obj_Spikes); // Spikes
	if (App->DEV) {
		AddNewDebugObjectID(Obj_AutomaticTunnel); // Automatic Tunnel
		AddNewDebugObjectID(Obj_RollEnforcer); // Roll Enforcer
		AddNewDebugObjectID(Obj_InvisibleBlockH); // Invisible Block
		AddNewDebugObjectID(Obj_InvisibleSpikes); // Invisible Spikes
		AddNewDebugObjectID(Obj_InvisibleDeath); // Invisible Death
		AddNewDebugObjectID(Obj_ViewCollisionToggler); // View Collision Toggler
        AddNewDebugObjectID(Obj_Motobug); // Motobug
	}

	ObjectProps.reserve(0x400);
	RingProps.reserve(0x400);

	AnimatedSprite0Props = (ObjectProp*)Memory::TrackedCalloc("LevelScene::AnimatedSprite0Props", 0x100, sizeof(ObjectProp));
	AnimatedSprite1Props = (ObjectProp*)Memory::TrackedCalloc("LevelScene::AnimatedSprite1Props", 0x100, sizeof(ObjectProp));

	SavedPalette = (uint32_t*)Memory::TrackedCalloc("LevelScene::SavedPalette", 0x100, sizeof(uint32_t));

	SoundBank = (ISound**)Memory::TrackedCalloc("LevelScene::SoundBank", 0x100, sizeof(ISound*));

	IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "Memory Allocation", (SDL_GetTicks() - startTime) / 1000.0);
	startTime = SDL_GetTicks();

	/*
	GlobalDisplaySprite = new ISprite("Mixed/Sprites/Sprites/Global/Display.gif", App);
	GlobalDisplaySprite->LoadAnimation("Mixed/Sprites/Sprites/Global/HUD.bin");
	GlobalDisplaySprite->LoadAnimation("Mixed/Sprites/Sprites/Global/TitleCard.bin");
	GlobalDisplaySprite->LoadAnimation("Mixed/Sprites/Sprites/Global/ScoreBonus.bin");

	MobileButtonsSprite = new ISprite("Mixed/Sprites/Sprites/UI/Mobile Buttons.gif", App);
	ISprite::Animation an;
	an.Name = NULL;
	an.FrameCount = 8;
	an.Frames = (ISprite::AnimFrame*)Memory::TrackedCalloc("LevelScene::MobileButtonsSprite::AnimFrame", 8, sizeof(ISprite::AnimFrame));
	for (int i = 0; i < 8; i++) {
		ISprite::AnimFrame ts_af;
		ts_af.X = i * 64;
		ts_af.Y = 0;
		ts_af.W = ts_af.H = 64;
		ts_af.OffX = ts_af.OffY = -32;
		an.Frames[i] = ts_af;
		G->MakeFrameBufferID(MobileButtonsSprite, an.Frames + i);
	}
	MobileButtonsSprite->Animations.push_back(an);
	MobileButtonsSprite->SetTransparentColorIndex(0x05);
	MobileButtonsSprite->UpdatePalette();

	PauseSprite = new ISprite("Mixed/Sprites/Sprites/UI/PauseEN.gif", App);
	PauseSprite->LoadAnimation("Mixed/Sprites/Sprites/UI/TextEN.bin");
	//*/

	IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "Creating GlobalDisplaySprite...", (SDL_GetTicks() - startTime) / 1000.0);
	startTime = SDL_GetTicks();

	std::memset(PauseAnim, 0, sizeof(PauseAnim));

	IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "Creating PauseSprite...", (SDL_GetTicks() - startTime) / 1000.0);
	startTime = SDL_GetTicks();

	std::memset(KnuxSprite, 0, sizeof(KnuxSprite));

	VisualAct = Act;


}

int MusicVolume = 0xFF;

PUBLIC VIRTUAL void LevelScene::PlayMusic(const char* path, int loop) {
	PlayMusic(path, loop, 0xFF);
}

PUBLIC VIRTUAL void LevelScene::PlayMusic(const char* path, int loop, int vol) {
	Sound::SoundBank[0] = new ISound(path, true);
	Sound::Audio->LoopPoint[0] = loop;
	MusicVolume = vol;
	Sound::Audio->PushMusic(Sound::SoundBank[0], loop, true);
}

PUBLIC VIRTUAL void LevelScene::PlayMusic(int act, int loop, int mode) {
	PlayMusic(act, loop, mode, 0xFF);
}

PUBLIC VIRTUAL void LevelScene::PlayMusic(int act, int loop, int mode, int vol) {
	char MusicPath[0x100];
	const char* ModePath = mode == 0 ? "Classic" : "Mixed";
	if (mode != -1)
		sprintf(MusicPath, "%s/Music/%s%d.ogg", ModePath, ZoneLetters, act);
	else 
		sprintf(MusicPath, "Music/%s%d.ogg", ZoneLetters, act);
	PlayMusic(MusicPath, loop, vol);
}

PUBLIC STATIC bool LevelScene::IsZoneCurrently(const char* CheckZoneLetters) {
    char NewCheckZoneLetters[4];
    char NewZoneLetters[4];
    NewCheckZoneLetters[3] = '\0';
    NewZoneLetters[3] = '\0';
    
    sprintf(NewCheckZoneLetters, CheckZoneLetters);
    sprintf(NewZoneLetters, ZoneLetters);

    return !strcmp(NewZoneLetters, NewCheckZoneLetters);
}

PUBLIC VIRTUAL void LevelScene::AssignSpriteMapIDs() {
    SpriteMapIDs.at(0x00) = ItemsSprite;
	SpriteMapIDs.at(0x01) = ItemsSprite;
	SpriteMapIDs.at(0x07) = ObjectsSprite;
	SpriteMapIDs.at(0x08) = ObjectsSprite;
	SpriteMapIDs.at(0x33) = ObjectsSprite;
	SpriteMapIDs.at(0x34) = ObjectsSprite; // Star Post
	SpriteMapIDs.at(0x81) = ObjectsSprite;

	SpriteMapIDs.at(0x408) = ObjectsSprite; // Warp Star
}

PUBLIC VIRTUAL void LevelScene::LoadZoneSpecificSprites() {

}

ISprite* GlobalDisplaySpriteS3K = NULL;
Object* LastObjectUpdated = NULL;

bool StateSaved = false;
int StatePlayerSpawnX = -1;
int StatePlayerSpawnY = -1;
int StateTimer = 0;
int StateLives = 0;
int StateRings = 0;
int StateShield = 0;

PUBLIC void LevelScene::SaveState() {
	if (StateSaved) return;

	StateSaved = true;
	StateTimer = Timer;
	StateRings = Player->Rings;
	StateLives = Player->Lives;
	StatePlayerSpawnX = Player->X;
	StatePlayerSpawnY = Player->Y;
	StateShield = (int)Player->Shield;
}

PUBLIC void LevelScene::LoadState() {
	if (!StateSaved) return;

	StateSaved = false;
	ResetTimer = false;
	Timer = StateTimer;
	Player->Rings = StateRings;
	Player->Lives = StateLives;
	SpecialSpawnPositionX = StatePlayerSpawnX;
	SpecialSpawnPositionY = StatePlayerSpawnY;

	for (int i = 0; i < PlayerCount; i++)
	{
		Players[i]->X = StatePlayerSpawnX;
		Players[i]->Y = StatePlayerSpawnY;
	}

	Player->Shield = (ShieldType)StateShield;
}

PUBLIC STATIC size_t LevelScene::LoadSpriteBin(const char* Filename) {
    if (IApp::GlobalApp == NULL) {
        return 0xFFFFFFFF;
    }

    if (FindSpriteBin(std::string(Filename)) && SpriteBinMap.find(std::string(Filename))->second != -1) {
        size_t BinIndex = SpriteBinMap.find(std::string(Filename))->second;
        // If BinIndex is bigger then SpriteBinMapIDs.size(), Then a clear happened,
        // And for some reason the SpriteBinMap wasn't also cleared.
        if (BinIndex > SpriteBinMap.size() || GetSpriteFromBinIndex(BinIndex) == nullptr) {
            return ResetSpriteBin(Filename);
        } else {
            return BinIndex;
        }
    } else {
        ISprite* BinSprite = new ISprite(Filename, IApp::GlobalApp);
        SpriteBinMapIDs.push_back(BinSprite);
        SpriteBinMapIDs.shrink_to_fit();
        size_t BinIndex = SpriteBinMapIDs.size() - 1;

        if (!FindSpriteBin(std::string(Filename))) {
            std::pair<std::string, size_t> pair(std::string(Filename), BinIndex);
            SpriteBinMap.insert(pair);
        }
        return BinIndex;
    }
};

PUBLIC STATIC size_t LevelScene::LoadSpriteBin(const char* Filename, byte Mode) {
	if (IApp::GlobalApp == NULL) {
		return 0xFFFFFFFF;
	}

	string fullFileName;

	/*switch (Mode)
	{
	case 0:
		fullFileName.append("Classic/");
		break;
	case 1:
	case 2:
	default:
		fullFileName.append("Mixed/");
		break;
	}*/

	fullFileName.append(Filename);

	if (FindSpriteBin(fullFileName) && SpriteBinMap.find(fullFileName)->second != -1) {
		size_t BinIndex = SpriteBinMap.find(fullFileName)->second;
		// If BinIndex is bigger then SpriteBinMapIDs.size(), Then a clear happened,
		// And for some reason the SpriteBinMap wasn't also cleared.
		if (BinIndex > SpriteBinMap.size() || GetSpriteFromBinIndex(BinIndex) == nullptr) {
			return ResetSpriteBin(fullFileName.c_str());
		}
		else {
			return BinIndex;
		}
	}
	else {
		ISprite* BinSprite = new ISprite(fullFileName.c_str(), IApp::GlobalApp, Mode);
		SpriteBinMapIDs.push_back(BinSprite);
		SpriteBinMapIDs.shrink_to_fit();
		size_t BinIndex = SpriteBinMapIDs.size() - 1;

		if (!FindSpriteBin(fullFileName)) {
			std::pair<std::string, size_t> pair(fullFileName, BinIndex);
			SpriteBinMap.insert(pair);
		}
		return BinIndex;
	}
};

PROTECTED STATIC size_t LevelScene::ResetSpriteBin(const char* Filename) {
#define CLEANUP(name) if (name) { name->Cleanup(); delete name; name = NULL; }
    if (IApp::GlobalApp == NULL) {
        return 0xFFFFFFFF;
    }
    ISprite* BinSprite = new ISprite(Filename, IApp::GlobalApp);
    SpriteBinMapIDs.push_back(BinSprite);
    SpriteBinMapIDs.shrink_to_fit();
    size_t BinIndex = SpriteBinMapIDs.size() - 1;

    if (!FindSpriteBin(std::string(Filename))) {
        std::pair<std::string, size_t> pair(std::string(Filename), BinIndex);
        SpriteBinMap.insert(pair);
    } else {
		auto it = SpriteBinMap.find(std::string(Filename));
        SpriteBinMap.erase(it);
        std::pair<std::string, size_t> pair(std::string(Filename), BinIndex);
        SpriteBinMap.insert(pair);
    }
    return BinIndex;
};

PUBLIC STATIC ISprite* LevelScene::LoadSpriteFromBin(const char* Filename) {
    if (IApp::GlobalApp == NULL) {
        return NULL;
    }

    if (FindSpriteBin(std::string(Filename)) && SpriteBinMap.find(std::string(Filename))->second != -1) {
        ISprite* sprite = SpriteBinMapIDs.at(SpriteBinMap.find(std::string(Filename))->second);
        if (sprite == nullptr) {
            sprite = SpriteBinMapIDs.at(ResetSpriteBin(Filename));
        }
        return sprite;
    } else {
        ISprite* BinSprite = new ISprite(Filename, IApp::GlobalApp);
        SpriteBinMapIDs.push_back(BinSprite);
        SpriteBinMapIDs.shrink_to_fit();
        size_t BinIndex = SpriteBinMapIDs.size() - 1;

        if (!FindSpriteBin(std::string(Filename))) {
            std::pair<std::string, size_t> pair(std::string(Filename), BinIndex);
            SpriteBinMap.insert(pair);
        }
        return BinSprite;
    }
}

PUBLIC STATIC ISprite* LevelScene::LoadSpriteFromBin(const char* Filename, byte Mode) {
	if (IApp::GlobalApp == NULL) {
		return NULL;
	}

	if (FindSpriteBin(std::string(Filename)) && SpriteBinMap.find(std::string(Filename))->second != -1) {
		ISprite* sprite = SpriteBinMapIDs.at(SpriteBinMap.find(std::string(Filename))->second);
		if (sprite == nullptr) {
			sprite = SpriteBinMapIDs.at(ResetSpriteBin(Filename));
		}
		return sprite;
	}
	else {
		ISprite* BinSprite = new ISprite(Filename, IApp::GlobalApp, Mode);
		SpriteBinMapIDs.push_back(BinSprite);
		SpriteBinMapIDs.shrink_to_fit();
		size_t BinIndex = SpriteBinMapIDs.size() - 1;

		if (!FindSpriteBin(std::string(Filename))) {
			std::pair<std::string, size_t> pair(std::string(Filename), BinIndex);
			SpriteBinMap.insert(pair);
		}
		return BinSprite;
	}
}

PUBLIC STATIC ISprite* LevelScene::GetSpriteFromBinIndex(size_t index) {
	if (index < 0 || index >= SpriteBinMapIDs.size()) {
        IApp::Print(2, "LevelScene::GetSpriteFromBinIndex: index '%d' was not valid!", index);
		return nullptr;
	} else {
		return SpriteBinMapIDs.at(index);
	}
};

PROTECTED STATIC bool LevelScene::FindSpriteBin(std::string filename) {
    auto it = SpriteBinMap.find(filename);
    if (it == SpriteBinMap.end()) {
        return false;
    } else {
        return true;
    }
}

PUBLIC VIRTUAL void LevelScene::CreateAttributeValue(AttributeValue* Attribute) {
	Attribute->ValBool = false;
	Attribute->ValColor.r = 255;
	Attribute->ValColor.g = 255;
	Attribute->ValColor.b = 255;
	Attribute->ValInt16 = 0;
	Attribute->ValInt32 = 0;
	Attribute->ValInt8 = 0;
	Attribute->ValPosition.X = 0;
	Attribute->ValPosition.Y = 0;
	Attribute->ValString = "String";
	Attribute->ValUint16 = 0;
	Attribute->ValUint32 = 0;
	Attribute->ValUint8 = 0;
	Attribute->ValVariable = 0;
}

PUBLIC VIRTUAL void LevelScene::LoadData() {
	/// Init
	bool AlreadyLoaded = true;
	uint64_t startTime = SDL_GetTicks();
	if (!Data) {
		AlreadyLoaded = false;

		FadeAction = FadeActionType::FADEIN;
		FadeTimerMax = 90;
		FadeMax = 0x140;
		G->FadeToWhite = false;

		startTime = SDL_GetTicks();

		// Test Loading Models
		if (!GiantRingModel) {
			GiantRingModel = new IModel("Meshes/SpecialRing.bin", G);
        }

		IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "GiantRingModel", (SDL_GetTicks() - startTime) / 1000.0);
		startTime = SDL_GetTicks();

		if (!PauseSprite) {
			PauseSprite = new ISprite("Mixed/Sprites/UI/PauseMenu.bin", App);
			PauseSprite->SetTransparentColorIndex(0);
		}
		if (!GlobalDisplaySprite) {
			GlobalDisplaySprite = new ISprite("Mixed/Sprites/Global/Display.gif", App);
			GlobalDisplaySprite->Print = App->DEV;
			GlobalDisplaySprite->LoadAnimation("Mixed/Sprites/Global/HUD.bin");
			GlobalDisplaySprite->LoadAnimation("Mixed/Sprites/Global/TitleCard.bin");
			GlobalDisplaySprite->LoadAnimation("Mixed/Sprites/Global/PlaneSwitch.bin");
		}
		if (!GlobalDisplaySpriteS3K) {
			GlobalDisplaySpriteS3K = new ISprite("Classic/Sprites/Global/HUD.bin", App);
		}
		if (!SuperButtonsSprite) {
			SuperButtonsSprite = new ISprite("Mixed/Sprites/UI/SuperButtons.bin", App);
			SuperButtonsSprite->SetPalette(1, 0x282028);
			SuperButtonsSprite->UpdatePalette();
		}
		if (!MobileButtonsSprite) {
			MobileButtonsSprite = new ISprite("Mixed/Sprites/UI/Mobile Buttons.gif", App);
			ISprite::Animation an;
			an.Name = "";
			an.FrameCount = 8;
			an.Frames = new ISprite::AnimFrame[an.FrameCount];
			for (int i = 0; i < 8; i++) {
				ISprite::AnimFrame ts_af;
				ts_af.X = i * 64;
				ts_af.Y = 0;
				ts_af.W = ts_af.H = 64;
				ts_af.OffX = ts_af.OffY = -32;
				an.Frames[i] = ts_af;
				G->MakeFrameBufferID(MobileButtonsSprite, an.Frames + i);
			}
			MobileButtonsSprite->Animations.push_back(an);
			MobileButtonsSprite->SetTransparentColorIndex(0x05);
			MobileButtonsSprite->UpdatePalette();
		}
		if (!EditorSprite) {
			EditorSprite = new ISprite("Mixed/Sprites/Editor/Icons.gif", App);
			EditorSprite->LoadAnimation("Mixed/Sprites/Editor/PlayerIcons.bin");
			EditorSprite->LoadAnimation("Mixed/Sprites/Editor/EditorIcons.bin");
		}
		if (!ItemsSprite) {
			if (SaveGame::CurrentMode == 1) {
				ItemsSprite = new ISprite("Mixed/Sprites/Global/Items.gif", App);
				ItemsSprite->LoadAnimation("Mixed/Sprites/Global/ItemBox.bin");
				ItemsSprite->LoadAnimation("Mixed/Sprites/Global/Ring.bin");
				ItemsSprite->LoadAnimation("Mixed/Sprites/Special/Ring.bin");
				ItemsSprite->SetTransparentColorIndex(0x0);
			} else {
				ItemsSprite = new ISprite("Classic/Sprites/Global/Items.gif", App);
				ItemsSprite->LoadAnimation("Classic/Sprites/Global/ItemBox.bin");
				ItemsSprite->LoadAnimation("Classic/Sprites/Global/Ring.bin");
			}
		}
		if (!AnimalsSprite) {
			AnimalsSprite = new ISprite("Mixed/Sprites/Global/Animals.bin", App);
		}
		if (!ObjectsSprite) {
			if (SaveGame::CurrentMode == 1) {
				ObjectsSprite = new ISprite("Mixed/Sprites/Global/Objects.gif", App);
				ObjectsSprite->LoadAnimation("Mixed/Sprites/Global/Springs.bin");
				ObjectsSprite->LoadAnimation("Mixed/Sprites/Global/Spikes.bin");
				ObjectsSprite->LoadAnimation("Mixed/Sprites/Global/StarPost.bin");
				ObjectsSprite->LoadAnimation("Mixed/Sprites/Global/ScoreBonus.bin");
				ObjectsSprite->SetTransparentColorIndex(0x0);
			}
			else {
				ObjectsSprite = new ISprite("Classic/Sprites/Global/Objects.gif", App);
				ObjectsSprite->LoadAnimation("Classic/Sprites/Global/Springs.bin");
				ObjectsSprite->LoadAnimation("Classic/Sprites/Global/Spikes.bin");
				ObjectsSprite->LoadAnimation("Classic/Sprites/Global/StarPost.bin");
				ObjectsSprite->LoadAnimation("Classic/Sprites/Global/ScoreBonus.bin");

				ObjectsSprite->LoadAnimation("Classic/Sprites/Global/Gray Button.bin");
				ObjectsSprite->LoadAnimation("Classic/Sprites/Global/EggPrison.bin");
			}
		}
		if (!Objects2Sprite) {
			Objects2Sprite = new ISprite("Mixed/Sprites/Global/SignPost.bin", App);
			Objects2Sprite->SetTransparentColorIndex(0x0);
		}
		if (!Objects3Sprite) {
			Objects3Sprite = new ISprite("Mixed/Sprites/Global/Objects3.gif", App);
			Objects3Sprite->LoadAnimation("Mixed/Sprites/Global/SpecialRing.bin");
			Objects3Sprite->LoadAnimation("Mixed/Sprites/Global/SuperSparkle.bin");
			Objects3Sprite->LoadAnimation("Mixed/Sprites/Global/Shields.bin");
			Objects3Sprite->SetTransparentColorIndex(0x0);
		}
		if (!RobotnikSprite) {
			RobotnikSprite = new ISprite("Classic/Sprites/Global/Robotnik.gif", App);
			RobotnikSprite->LoadAnimation("Classic/Sprites/Global/EggMobile.bin");
			RobotnikSprite->LoadAnimation("Classic/Sprites/Global/Crane.bin");
		}
		if (!ExplosionSprite) {
			if (SaveGame::CurrentMode == 1) {
				ExplosionSprite = new ISprite("Mixed/Sprites/Global/Explosions.gif", App);
				ExplosionSprite->LoadAnimation("Mixed/Sprites/Global/Dust.bin");
				ExplosionSprite->LoadAnimation("Mixed/Sprites/Global/Explosions.bin");
			} else {
				ExplosionSprite = new ISprite("Classic/Sprites/Global/Explosions.gif", App);
				ExplosionSprite->LoadAnimation("Classic/Sprites/Global/Dust.bin");
				ExplosionSprite->LoadAnimation("Classic/Sprites/Global/Explosions.bin");
			}
		}
		if (!WaterSprite) {
			WaterSprite = new ISprite("Mixed/Sprites/Global/Water.gif", App, true);
            WaterSprite->LoadAnimation("Mixed/Sprites/Global/Water.bin");
		}

		IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "Common Sprites", (SDL_GetTicks() - startTime) / 1000.0);
		startTime = SDL_GetTicks();

		LoadZoneSpecificSprites();
		IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "LoadZoneSpecificSprites", (SDL_GetTicks() - startTime) / 1000.0);
		startTime = SDL_GetTicks();

		AssignSpriteMapIDs();
		IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "AssignSpriteMapIDs", (SDL_GetTicks() - startTime) / 1000.0);
		startTime = SDL_GetTicks();

		// Instead of filling it on a per by per basis, Fill the whole thing and
		// have the replacements fill the spots needed.
		for (int i = 0x0; i <= 346; i++) {
			ObjectName[i] = "Unused";
		}

		// If Sonic 3 level...
		if (ZoneID < 7) {
			ObjectName[0x00] = "Obj_Ring";
			ObjectName[0x01] = "Obj_Monitor";
			ObjectName[0x02] = "Obj_PlaneSwitch";
			ObjectName[0x03] = "Obj_HollowTree";
			ObjectName[0x04] = "Obj_CollapsingPlatform";
			ObjectName[0x05] = "Obj_Rock";
			ObjectName[0x06] = "Obj_RideVine";
			ObjectName[0x07] = "Obj_Spring";
			ObjectName[0x08] = "Obj_Spikes";
			ObjectName[0x09] = "Obj_TreeBark";
			ObjectName[0x0A] = "Obj_RopePeg";
			ObjectName[0x0B] = "Obj_Ring";
			ObjectName[0x0C] = "Obj_SwingVine";
			ObjectName[0x0D] = "Obj_BreakableWall";
			ObjectName[0x0E] = "Obj_Ridge";
			ObjectName[0x0F] = "Obj_CollapsingBridge";
			ObjectName[0x10] = "Obj_TubeElevator";
			ObjectName[0x11] = "Obj_MovingPlatform";
			ObjectName[0x12] = "Obj_FlagPlatform";
			ObjectName[0x13] = "Obj_LBZExplodingTrigger";
			ObjectName[0x14] = "Obj_TriggerBridge";
			ObjectName[0x15] = "Obj_LBZPlayerLauncher";
			ObjectName[0x16] = "Obj_LBZFlameThrower";
			ObjectName[0x17] = "Obj_RideGrapple";
			ObjectName[0x18] = "Obj_CupElevator";
			ObjectName[0x19] = "Obj_CupElevatorPole";
			ObjectName[0x1A] = "Obj_P2RotateObject"; // Purpose unknown.
			ObjectName[0x1B] = "Obj_PipePlug";
			ObjectName[0x1C] = "Obj_Ring";
			ObjectName[0x1D] = "Obj_HangPlatform";
			ObjectName[0x1E] = "Obj_SpinLauncher";
			ObjectName[0x1F] = "Obj_LoweringGrapple";
			ObjectName[0x20] = "Obj_SmashingPillar";
			ObjectName[0x21] = "Obj_GateLaser";
			ObjectName[0x22] = "Obj_Siren";
			ObjectName[0x23] = "Obj_ContactForcePeril"; // Unused
			ObjectName[0x24] = "Obj_AutomaticTunnel";
			ObjectName[0x25] = "Obj_Ring";
			ObjectName[0x26] = "Obj_RollEnforcer";
			ObjectName[0x27] = "Obj_LavaCollisionMarker"; // Unused
			ObjectName[0x28] = "Obj_InvisibleBlock";
			ObjectName[0x29] = "Obj_DisappearingFloor";
			ObjectName[0x2A] = "Obj_CorkFloor";
			ObjectName[0x2B] = "Obj_FlippingBridge";
			ObjectName[0x2C] = "Obj_CollapsingLogBridge";
			ObjectName[0x2D] = "Obj_FallingLog";
			ObjectName[0x2E] = "Obj_SpikedLog";
			ObjectName[0x2F] = "Obj_NonAnimSprite";
			ObjectName[0x30] = "Obj_AnimSprite";
			ObjectName[0x31] = "Obj_RotatingCylinder";
			ObjectName[0x32] = "Obj_DrawBridge";
			ObjectName[0x33] = "Obj_Button";
			ObjectName[0x34] = "Obj_StarPost";
			ObjectName[0x35] = "Obj_ForegroundPlant";
			ObjectName[0x36] = "Obj_BreakableBar";
			ObjectName[0x37] = "Obj_VWaterStream";
			ObjectName[0x38] = "Obj_Fan";
			ObjectName[0x39] = "Obj_LargeFan";
			ObjectName[0x3A] = "Obj_HandLauncher";
			ObjectName[0x3B] = "Obj_WaterWall";
			ObjectName[0x3C] = "Obj_Door";
			ObjectName[0x3D] = "Obj_RetractingSpring";
			ObjectName[0x3E] = "Obj_ConveyorBelt";
			ObjectName[0x3F] = "Obj_ConveyorSpike";
			ObjectName[0x40] = "Obj_Block";
			ObjectName[0x41] = "Obj_Balloon";
			ObjectName[0x42] = "Obj_Cannon";
			ObjectName[0x43] = "Obj_RisingPlatform";
			ObjectName[0x44] = "Obj_TrapDoor";
			ObjectName[0x45] = "Obj_LightBulb";
			ObjectName[0x46] = "Obj_HoverFan";
			ObjectName[0x47] = "Obj_RotatingBarrel";
			ObjectName[0x48] = "Obj_VacuumTube";
			ObjectName[0x49] = "Obj_RotatingWheel";
			ObjectName[0x4A] = "Obj_Bumper";
			ObjectName[0x4B] = "Obj_BouncepadSprings";
			ObjectName[0x4C] = "Obj_Corkscrew";
			ObjectName[0x4D] = "Obj_BarberPoleSprite";
			ObjectName[0x4E] = "Obj_CNZRotatingMesh";
			ObjectName[0x4F] = "Obj_QuickMud";
			ObjectName[0x50] = "Obj_RunAroundPole";
			ObjectName[0x51] = "Obj_FloatingPlatform";
			ObjectName[0x52] = "Obj_SmashingPillar";
			ObjectName[0x53] = "Obj_MGZSwingingPlatform";
			ObjectName[0x54] = "Obj_Bubbler";
			ObjectName[0x55] = "Obj_Relief";
			ObjectName[0x56] = "Obj_MovingSpikePlatform";
			ObjectName[0x57] = "Obj_TriggerPlatform";
			ObjectName[0x58] = "Obj_MGZSwingingSpikeBall";
			ObjectName[0x59] = "Obj_DashTrigger";
			ObjectName[0x5A] = "Obj_Pulley";
			ObjectName[0x5B] = "Obj_TopPlatform";
			ObjectName[0x5C] = "Obj_TopLauncher";
			ObjectName[0x5D] = "Obj_TriangularSprings";
			ObjectName[0x5E] = "Obj_BladePlatform";
			ObjectName[0x5F] = "Obj_RetractingSpring2P";
			ObjectName[0x60] = "Obj_ElephantBlock";
			ObjectName[0x61] = "Obj_BPZBalloon";
			ObjectName[0x62] = "Obj_DisolvingSandBar";
			ObjectName[0x63] = "Obj_DPZButton";
			ObjectName[0x64] = "Obj_Item2P";
			ObjectName[0x65] = "Obj_GoalMarker2P";
			ObjectName[0x66] = "Obj_Dripper";
			ObjectName[0x67] = "Obj_SnakeBlocks";
			ObjectName[0x68] = "Obj_SpinningColumn";
			ObjectName[0x69] = "Obj_Slide";
			ObjectName[0x6A] = "Obj_InvisibleHurtBlockHorizontal";
			ObjectName[0x6B] = "Obj_InvisibleHurtBlockVertical";
			ObjectName[0x6C] = "Obj_TensionBridge";
			ObjectName[0x6D] = "Obj_WaterSplash";
			ObjectName[0x6E] = "Obj_WaterDrop";
			ObjectName[0x6F] = "Obj_FBZRotatingMesh"; //
			ObjectName[0x70] = "Obj_TwistingCylinders";
			ObjectName[0x71] = "Obj_FBZFloatingPlatform"; //
			ObjectName[0x72] = "Obj_ChainLink";
			ObjectName[0x73] = "Obj_MagneticSpikeBall";
			ObjectName[0x74] = "Obj_MagneticPlatform";
			ObjectName[0x75] = "Obj_SnakePlatform";
			ObjectName[0x76] = "Obj_BentPipe";
			ObjectName[0x77] = "Obj_FBZRotatingPlatform";
			ObjectName[0x78] = "Obj_FBZDEZPlayerLauncher";
			ObjectName[0x79] = "Obj_DisappearingPlatform";
			ObjectName[0x7A] = "Obj_ScrewDoor";
			ObjectName[0x7B] = "Obj_FanPole";
			ObjectName[0x7C] = "Obj_Propeller";
			ObjectName[0x7D] = "Obj_Piston";
			ObjectName[0x7E] = "Obj_PlatformBlocks";
			ObjectName[0x7F] = "Obj_MissileLauncher";
			ObjectName[0x80] = "Obj_HiddenMonitor";
			ObjectName[0x81] = "Obj_EggCapsule";
			ObjectName[0x82] = "Obj_CutsceneKnuckles";
			ObjectName[0x83] = "Obj_CutsceneButton";
			ObjectName[0x84] = "Obj_AIZCutsceneSonic";
			ObjectName[0x85] = "Obj_SpecialRing";
			ObjectName[0x86] = "Obj_GumballSetup";
			ObjectName[0x87] = "Obj_GumballSideSpring";
			ObjectName[0x88] = "Obj_BreakableWaterRisingFloor";
			ObjectName[0x89] = "Obj_LightSwitch";
			ObjectName[0x8A] = "Obj_FBZ2CutsceneObjects";
			ObjectName[0x8B] = "Obj_SpriteMasker";
			ObjectName[0x8C] = "Obj_Bloominator";
			ObjectName[0x8D] = "Obj_RhinoBot";
			ObjectName[0x8E] = "Obj_MonkeyDude";
			ObjectName[0x8F] = "Obj_CaterkillerJr";
			ObjectName[0x90] = "Obj_AIZMinibossCutscene";
			ObjectName[0x91] = "Obj_AIZMiniboss";
			ObjectName[0x92] = "Obj_AIZBoss";
			ObjectName[0x93] = "Obj_Jawz";
			ObjectName[0x94] = "Obj_Blastoid";
			ObjectName[0x95] = "Obj_Buggernaut";
			ObjectName[0x96] = "Obj_TurboSpiker";
			ObjectName[0x97] = "Obj_MegaChomper";
			ObjectName[0x98] = "Obj_Pointdexter";
			ObjectName[0x99] = "Obj_HCZMiniboss";
			ObjectName[0x9A] = "Obj_HCZBoss";
			ObjectName[0x9B] = "Obj_BubblesBadnik";
			ObjectName[0x9C] = "Obj_Spiker";
			ObjectName[0x9D] = "Obj_Mantis";
			ObjectName[0x9E] = "Obj_MGZMinibossCutscene";
			ObjectName[0x9F] = "Obj_MGZMiniboss";
			ObjectName[0xA0] = "Obj_MGZDrillingEggman";
			ObjectName[0xA1] = "Obj_MGZBoss";
			ObjectName[0xA2] = "Obj_MGZKnucklesBoss";
			ObjectName[0xA3] = "Obj_Clamer";
			ObjectName[0xA4] = "Obj_Sparkle";
			ObjectName[0xA5] = "Obj_Batbright";
			ObjectName[0xA6] = "Obj_CNZMiniboss";
			ObjectName[0xA7] = "Obj_CNZBoss";
			ObjectName[0xA8] = "Obj_Blaster";
			ObjectName[0xA9] = "Obj_TechnoSqueek";
			ObjectName[0xAA] = "Obj_FBZMiniboss";
			ObjectName[0xAB] = "Obj_FBZLaserBoss";
			ObjectName[0xAC] = "Obj_FBZBoss";
			ObjectName[0xAD] = "Obj_Penguinator";
			ObjectName[0xAE] = "Obj_StarPointer";
			ObjectName[0xAF] = "Obj_CrushingColumn";
			ObjectName[0xB0] = "Obj_PathFollowPlatform";
			ObjectName[0xB1] = "Obj_ICZBreakableWall";
			ObjectName[0xB2] = "Obj_Freezer";
			ObjectName[0xB3] = "Obj_SegmentColumn";
			ObjectName[0xB4] = "Obj_ICZSwingingPlatform"; //
			ObjectName[0xB5] = "Obj_Stalagtite";
			ObjectName[0xB6] = "Obj_IceCube";
			ObjectName[0xB7] = "Obj_IceSpikes";
			ObjectName[0xB8] = "Obj_HarmfulIce";
			ObjectName[0xB9] = "Obj_SnowPile";
			ObjectName[0xBA] = "Obj_TensionPlatform";
			ObjectName[0xBB] = "Obj_RightTrampolineSupport";
			ObjectName[0xBC] = "Obj_ICZMiniboss";
			ObjectName[0xBD] = "Obj_ICZBoss";
			ObjectName[0xBE] = "Obj_SnaleBlaster";
			ObjectName[0xBF] = "Obj_Ribot";
			ObjectName[0xC0] = "Obj_Orbinaut";
			ObjectName[0xC1] = "Obj_Corkey";
			ObjectName[0xC2] = "Obj_Flybot767";
			ObjectName[0xC3] = "Obj_LBZEggmanFlee";
			ObjectName[0xC4] = "Obj_LBZMinibossBox";
			ObjectName[0xC5] = "Obj_LBZMinibossBoxKnuckles";
			ObjectName[0xC6] = "Obj_LRZEggMobile";
			ObjectName[0xC7] = "Obj_Ring";
			ObjectName[0xC8] = "Obj_LRZDeathEggLaunchTowers";
			ObjectName[0xC9] = "Obj_LBZMiniboss";
			ObjectName[0xCA] = "Obj_LBZBoss2";
			ObjectName[0xCB] = "Obj_LBZBoss1";
			ObjectName[0xCC] = "Obj_LBZBossBigArms";
			ObjectName[0xCD] = "Obj_LBZBoss2Knuckles";
			ObjectName[0xCE] = "Obj_FBZExitDoor";
			ObjectName[0xCF] = "Obj_FBZEggCapsule";
			ObjectName[0xD0] = "Obj_SpringPlunger";
			ObjectName[0xD1] = "Obj_Ring";
			ObjectName[0xD2] = "Obj_Ring";
			ObjectName[0xD3] = "Obj_Ring";
			ObjectName[0xD4] = "Obj_Ring";
			ObjectName[0xD5] = "Obj_Ring";
			ObjectName[0xD6] = "Obj_Ring";
			ObjectName[0xD7] = "Obj_Ring";
			ObjectName[0xD8] = "Obj_Ring";
			ObjectName[0xD9] = "Obj_Ring";
			ObjectName[0xDA] = "Obj_Ring";
			ObjectName[0xDB] = "Obj_Ring";
			ObjectName[0xDC] = "Obj_Ring";
			ObjectName[0xDD] = "Obj_Ring";
			ObjectName[0xDE] = "Obj_Ring";
			ObjectName[0xDF] = "Obj_Ring";
			ObjectName[0xE0] = "Obj_WallMissile";
			ObjectName[0xE1] = "Obj_Mine";
			ObjectName[0xE2] = "Obj_Elevator";
			ObjectName[0xE3] = "Obj_TrapSpring";
			ObjectName[0xE4] = "Obj_FBZFlameThrower";
			ObjectName[0xE5] = "Obj_SpiderCrane";
			ObjectName[0xE6] = "Obj_PachinkoTriangleBumper";
			ObjectName[0xE7] = "Obj_PachinkoFlipper";
			ObjectName[0xE8] = "Obj_PachinkoEnergyTrap";
			ObjectName[0xE9] = "Obj_PachinkoInvisibleUnknown";
			ObjectName[0xEA] = "Obj_PachinkoPlatform";
			ObjectName[0xEB] = "Obj_GumballItem";
			ObjectName[0xEC] = "Obj_MagneticOrb";
			ObjectName[0xED] = "Obj_PachinkoItemOrb";
			ObjectName[0xEE] = "Obj_Ring";
			ObjectName[0xEF] = "Obj_Ring";
			ObjectName[0xF0] = "Obj_Ring";
			ObjectName[0xF1] = "Obj_Ring";
			ObjectName[0xF2] = "Obj_Ring";
			ObjectName[0xF3] = "Obj_Ring";
			ObjectName[0xF4] = "Obj_Ring";
			ObjectName[0xF5] = "Obj_Ring";
			ObjectName[0xF6] = "Obj_Ring";
			ObjectName[0xF7] = "Obj_Ring";
			ObjectName[0xF8] = "Obj_Ring";
			ObjectName[0xF9] = "Obj_Ring";
			ObjectName[0xFA] = "Obj_Ring";
			ObjectName[0xFB] = "Obj_Ring";
			ObjectName[0xFC] = "Obj_Ring";
			ObjectName[0xFD] = "Obj_Ring";
			ObjectName[0xFE] = "Obj_Ring";
			ObjectName[0xFF] = "Obj_FBZMagneticPendulum";
		}
		// If Sonic & Knuckles level...
		else if (ZoneID < 13) {
			ObjectName[0x00] = "Obj_Ring";
			ObjectName[0x01] = "Obj_Monitor";
			ObjectName[0x02] = "Obj_PathSwap";
			ObjectName[0x03] = "Obj_CTwistVine";
			ObjectName[0x04] = "Obj_CollapsingPlatform";
			ObjectName[0x05] = "Obj_Rock";
			ObjectName[0x06] = "Obj_PulleyLift";
			ObjectName[0x07] = "Obj_Spring";
			ObjectName[0x08] = "Obj_Spikes";
			ObjectName[0x09] = "Obj_CurledVine";
			ObjectName[0x0A] = "Obj_StickyVine";
			ObjectName[0x0B] = "Obj_SwingBarHorizontal";
			ObjectName[0x0C] = "Obj_SwingBarVertical";
			ObjectName[0x0D] = "Obj_BreakableWall";
			ObjectName[0x0E] = "Obj_Ridge";
			ObjectName[0x0F] = "Obj_CollapsingBridge";
			ObjectName[0x10] = "Obj_MHZSwingVine";
			ObjectName[0x11] = "Obj_MushroomPlatform";
			ObjectName[0x12] = "Obj_MushroomParachute";
			ObjectName[0x13] = "Obj_MushroomCatapult";
			ObjectName[0x14] = "Obj_WindTunnel";
			ObjectName[0x15] = "Obj_VerticalCylinder";
			ObjectName[0x16] = "Obj_LRZ_TwirlTunnel";
			ObjectName[0x17] = "Obj_LRZ_SinkingRock";
			ObjectName[0x18] = "Obj_LRZ_FallingSpike";
			ObjectName[0x19] = "Obj_LRZ_Door";
			ObjectName[0x1A] = "Obj_LRZ_BigDoor";
			ObjectName[0x1B] = "Obj_LRZ_FireballLauncher";
			ObjectName[0x1C] = "Obj_LRZ_ButtonHorizontal";
			ObjectName[0x1D] = "Obj_LRZ_ShootingTrigger";
			ObjectName[0x1E] = "Obj_LRZ_DashElevator";
			ObjectName[0x1F] = "Obj_LRZ_LavaFall";
			ObjectName[0x20] = "Obj_LRZSwingingSpikeBall";
			ObjectName[0x21] = "Obj_LRZ_SmashingSpikePlatform";
			ObjectName[0x22] = "Obj_LRZ_SpikeBall";
			ObjectName[0x23] = "Obj_MHZ_MushroomCap";
			ObjectName[0x24] = "Obj_AutomaticTunnel";
			ObjectName[0x25] = "Obj_LRZ_ChainedPlatforms";
			ObjectName[0x26] = "Obj_RollEnforcer";
			ObjectName[0x27] = "Obj_LavaCollisionMarker";
			ObjectName[0x28] = "Obj_InvisibleBarrier";
			ObjectName[0x29] = "Obj_LRZFlameThrower";
			ObjectName[0x2A] = "Obj_CorkFloor";
			ObjectName[0x2B] = "Obj_LRZ_OrbitingSpikeBallHorizontal";
			ObjectName[0x2C] = "Obj_LRZ_OrbitingSpikeBallVertical";
			ObjectName[0x2D] = "Obj_LRZ_SolidMovingPlatforms";
			ObjectName[0x2E] = "Obj_LRZ_SolidRock";
			ObjectName[0x2F] = "Obj_StillSprite";
			ObjectName[0x30] = "Obj_AnimatedStillSprite";
			ObjectName[0x31] = "Obj_LRZ_CollapsingBridge";
			ObjectName[0x32] = "Obj_LRZ_TurbineSprites";
			ObjectName[0x33] = "Obj_Button";
			ObjectName[0x34] = "Obj_StarPost";
			ObjectName[0x35] = "Obj_ForegroundPlant";
			ObjectName[0x36] = "Obj_BreakableBar";
			ObjectName[0x37] = "Obj_LRZ_SpikeBallLauncher";
			ObjectName[0x38] = "Obj_SOZ_SandFalls";
			ObjectName[0x39] = "Obj_SOZ_SpawningSandBlocks";
			ObjectName[0x3A] = "Obj_SOZ_DoubleLoopPathSwapper";
			ObjectName[0x3B] = "Obj_SOZ_SpringLoopPathSwapper";
			ObjectName[0x3C] = "Obj_Door";
			ObjectName[0x3D] = "Obj_RetractingSpring";
			ObjectName[0x3E] = "Obj_SOZ_PushableRock";
			ObjectName[0x3F] = "Obj_SOZ_SpringVine";
			ObjectName[0x40] = "Obj_SOZ_RisingSandWall";
			ObjectName[0x41] = "Obj_SOZLightSwitch";
			ObjectName[0x42] = "Obj_SOZ_FloatingPillar";
			ObjectName[0x43] = "Obj_SOZSwingingPlatform"; //
			ObjectName[0x44] = "Obj_SOZ_BreakableSandRock";
			ObjectName[0x45] = "Obj_SOZ_PushSwitch";
			ObjectName[0x46] = "Obj_SOZ_Door";
			ObjectName[0x47] = "Obj_SOZ_SandCork";
			ObjectName[0x48] = "Obj_SOZ_RapelWire";
			ObjectName[0x49] = "Obj_SOZ_SolidSprites";
			ObjectName[0x4A] = "Obj_DEZFloatingPlatform";
			ObjectName[0x4B] = "Obj_TiltingBridge";
			ObjectName[0x4C] = "Obj_DEZ_HangCarrier";
			ObjectName[0x4D] = "Obj_DEZ_TorpedoLauncher";
			ObjectName[0x4E] = "Obj_DEZ_LiftPad";
			ObjectName[0x4F] = "Obj_DEZ_Staircase";
			ObjectName[0x50] = "Obj_DEZConveyorBelt"; //
			ObjectName[0x51] = "Obj_FloatingPlatform";
			ObjectName[0x52] = "Obj_DEZ_Lightning";
			ObjectName[0x53] = "Obj_DEZ_ConveyorPad";
			ObjectName[0x54] = "Obj_Bubbler";
			ObjectName[0x55] = "Obj_DEZ_EnergyBridge";
			ObjectName[0x56] = "Obj_DEZ_CurvedEnergyBridge";
			ObjectName[0x57] = "Obj_DEZ_TunnelLauncher";
			ObjectName[0x58] = "Obj_DEZ_GravitySwitch";
			ObjectName[0x59] = "Obj_DEZ_ReverseGravityTunnel";
			ObjectName[0x5A] = "Obj_DEZ_TwirlTunnel";
			ObjectName[0x5B] = "Obj_DEZ_GravityReverser";
			ObjectName[0x5C] = "Obj_DEZ_TunnelJunction";
			ObjectName[0x5D] = "Obj_DEZRetractingSpring"; //
			ObjectName[0x5E] = "Obj_DEZ_HoverMachine";
			ObjectName[0x5F] = "Obj_DEZ_SpecialEngineController";
			ObjectName[0x60] = "Obj_DEZ_BumperWall";
			ObjectName[0x61] = "Obj_DEZ_GravityPuzzle";
			ObjectName[0x62] = "Obj_Ring";
			ObjectName[0x63] = "Obj_Ring";
			ObjectName[0x64] = "Obj_Ring";
			ObjectName[0x65] = "Obj_Ring";
			ObjectName[0x66] = "Obj_Ring";
			ObjectName[0x67] = "Obj_Ring";
			ObjectName[0x68] = "Obj_Ring";
			ObjectName[0x69] = "Obj_Ring";
			ObjectName[0x6A] = "Obj_InvisibleHurtBlockHorizontal";
			ObjectName[0x6B] = "Obj_InvisibleHurtBlockVertical";
			ObjectName[0x6C] = "Obj_TensionBridge";
			ObjectName[0x6D] = "Obj_ElectricInvisibleBlock";
			ObjectName[0x6E] = "Obj_FlamingInvisibleBlock";
			ObjectName[0x6F] = "Obj_Ring";
			ObjectName[0x70] = "Obj_Ring";
			ObjectName[0x71] = "Obj_Ring";
			ObjectName[0x72] = "Obj_Ring";
			ObjectName[0x73] = "Obj_Ring";
			ObjectName[0x74] = "Obj_SSZRetractingSpring"; //
			ObjectName[0x75] = "Obj_SSZ_SwingingCarrier";
			ObjectName[0x76] = "Obj_SSZRotatingPlatform"; //
			ObjectName[0x77] = "Obj_SSZ_RetractingBridge";
			ObjectName[0x78] = "Obj_FBZDEZPlayerLauncher";
			ObjectName[0x79] = "Obj_SSZ_HPZTeleporter";
			ObjectName[0x7A] = "Obj_SSZ_ElevatorBar";
			ObjectName[0x7B] = "Obj_SSZ_CollapsingBridgeDiagonal";
			ObjectName[0x7C] = "Obj_SSZ_CollapsingBridge";
			ObjectName[0x7D] = "Obj_SSZ_BouncyCloud";
			ObjectName[0x7E] = "Obj_SSZ_CollapsingColumn";
			ObjectName[0x7F] = "Obj_SSZFloatingPlatform";
			ObjectName[0x80] = "Obj_HiddenMonitor";
			ObjectName[0x81] = "Obj_EggCapsule";
			ObjectName[0x82] = "Obj_CutsceneKnuckles";
			ObjectName[0x83] = "Obj_CutsceneButton";
			ObjectName[0x84] = "Obj_AIZCutsceneSonic";
			ObjectName[0x85] = "Obj_SpecialRing";
			ObjectName[0x86] = "Obj_GumballSetup";
			ObjectName[0x87] = "Obj_GumballSideSpring";
			ObjectName[0x88] = "Obj_BreakableWaterRisingFloor";
			ObjectName[0x89] = "Obj_LightSwitch";
			ObjectName[0x8A] = "Obj_FBZ2CutsceneObjects";
			ObjectName[0x8B] = "Obj_SpriteMasker";
			ObjectName[0x8C] = "Obj_Madmole";
			ObjectName[0x8D] = "Obj_Mushmeanie";
			ObjectName[0x8E] = "Obj_Dragonfly";
			ObjectName[0x8F] = "Obj_Butterdroid";
			ObjectName[0x90] = "Obj_Cluckoid";
			ObjectName[0x91] = "Obj_MHZ_ChopTree";
			ObjectName[0x92] = "Obj_MHZ_Miniboss";
			ObjectName[0x93] = "Obj_MHZ_EndBoss";
			ObjectName[0x94] = "Obj_Skorp";
			ObjectName[0x95] = "Obj_Sandworm";
			ObjectName[0x96] = "Obj_Rockn";
			ObjectName[0x97] = "Obj_SOZ_Miniboss";
			ObjectName[0x98] = "Obj_SOZ_EndBoss";
			ObjectName[0x99] = "Obj_Fireworm";
			ObjectName[0x9A] = "Obj_LRZ_ExplodingRock";
			ObjectName[0x9B] = "Obj_Toxomister";
			ObjectName[0x9C] = "Obj_LRZ_RockCrusher";
			ObjectName[0x9D] = "Obj_LRZ_Miniboss";
			ObjectName[0x9E] = "Obj_LRZ_TorpedoLauncher";
			ObjectName[0x9F] = "Obj_Ring";
			ObjectName[0xA0] = "Obj_EggRobo";
			ObjectName[0xA1] = "Obj_SSZ_GHZBoss";
			ObjectName[0xA2] = "Obj_SSZ_MTZBoss";
			ObjectName[0xA3] = "Obj_SSZ_MechaSonicBoss";
			ObjectName[0xA4] = "Obj_Spikebonker";
			ObjectName[0xA5] = "Obj_Chainspike";
			ObjectName[0xA6] = "Obj_DEZ_Miniboss";
			ObjectName[0xA7] = "Obj_DEZ_EndBoss";
			ObjectName[0xA8] = "Obj_MHZ_ForceCrouch";
			ObjectName[0xA9] = "Obj_MHZ_KnucklesButton";
			ObjectName[0xAA] = "Obj_SOZ_Ghosts";
			ObjectName[0xAB] = "Obj_SOZ2_GhostCapsuleLoader";
			ObjectName[0xAC] = "Obj_SOZ2_GhostCapsule";
			ObjectName[0xAD] = "Obj_LRZ3_Platforms";
			ObjectName[0xAE] = "Obj_LRZ_KnucklesEndHelper";
			ObjectName[0xAF] = "Obj_SSZ_KnucklesButton";
			ObjectName[0xB0] = "Obj_HPZ_MasterEmerald";
			ObjectName[0xB1] = "Obj_HPZ_MidwayPalleteChanger";
			ObjectName[0xB2] = "Obj_SSZ_EggRobo";
			ObjectName[0xB3] = "Obj_ContactLevelChanger";
			ObjectName[0xB4] = "Obj_HPZ_SuperEmeralds";
			ObjectName[0xB5] = "Obj_HPZ_SpecialStageCreater";
			ObjectName[0xB6] = "Obj_DDZ_BossShip";
			ObjectName[0xB7] = "Obj_DDZ_Asteroid";
			ObjectName[0xB8] = "Obj_DDZ_Missile";
		}
		// If 3'Mixed level...
		else {
			ObjectName[ThremixedIDS::Ring] = "Obj_Ring";
			ObjectName[ThremixedIDS::Monitor] = "Obj_Monitor";
			ObjectName[ThremixedIDS::PathSwap] = "Obj_PathSwap";
			ObjectName[ThremixedIDS::CollapsingPlatform] = "Obj_CollapsingPlatform";
			ObjectName[ThremixedIDS::Spring] = "Obj_Spring";
			ObjectName[ThremixedIDS::Spikes] = "Obj_Spikes";
			ObjectName[ThremixedIDS::BreakableWall] = "Obj_BreakableWall";
			ObjectName[ThremixedIDS::Ridge] = "Obj_Ridge";
			ObjectName[ThremixedIDS::CollapsingBridge] = "Obj_CollapsingBridge";
			ObjectName[ThremixedIDS::ContactFirceFallAnimator] = "Obj_ContactFirceFallAnimator"; // Unused
			ObjectName[ThremixedIDS::AutomaticTunnel] = "Obj_AutomaticTunnel";
			ObjectName[ThremixedIDS::RollEnforcer] = "Obj_RollEnforcer";
			ObjectName[ThremixedIDS::LavaCollisionMarker] = "Obj_LavaCollisionMarker"; // Unused
			ObjectName[ThremixedIDS::InvisibleBarrier] = "Obj_InvisibleBarrier";
			ObjectName[ThremixedIDS::CorkFloor] = "Obj_CorkFloor";
			ObjectName[ThremixedIDS::StillSprite] = "Obj_StillSprite";
			ObjectName[ThremixedIDS::AnimatedStillSprite] = "Obj_AnimatedStillSprite";
			ObjectName[ThremixedIDS::Button] = "Obj_Button";
			ObjectName[ThremixedIDS::StarPost] = "Obj_StarPost";
			ObjectName[ThremixedIDS::BreakableBar] = "Obj_BreakableBar";
			ObjectName[ThremixedIDS::Door] = "Obj_Door";
			ObjectName[ThremixedIDS::RetractingSpring] = "Obj_RetractingSpring";
			ObjectName[ThremixedIDS::FloatingPlatform] = "Obj_FloatingPlatform";
			ObjectName[ThremixedIDS::Bubbler] = "Obj_Bubbler";
			ObjectName[ThremixedIDS::InvisibleHurtBlockHorizontal] = "Obj_InvisibleHurtBlockHorizontal";
			ObjectName[ThremixedIDS::InvisibleHurtBlockVertical] = "Obj_InvisibleHurtBlockVertical";
			ObjectName[ThremixedIDS::TensionBridge] = "Obj_TensionBridge";
			ObjectName[ThremixedIDS::WaterDrop] = "Obj_WaterDrop";
			ObjectName[ThremixedIDS::HiddenMonitor] = "Obj_HiddenMonitor";
			ObjectName[ThremixedIDS::EggCapsule] = "Obj_EggCapsule";
			ObjectName[ThremixedIDS::CutsceneKnuckles] = "Obj_CutsceneKnuckles";
			ObjectName[ThremixedIDS::CutsceneButton] = "Obj_CutsceneButton";
			ObjectName[ThremixedIDS::SpriteMasker] = "Obj_SpriteMasker";
			ObjectName[ThremixedIDS::Tulipon] = "Obj_Tulipon";
			ObjectName[ThremixedIDS::RhinoBot] = "Obj_RhinoBot";
			ObjectName[ThremixedIDS::MonkeyDude] = "Obj_MonkeyDude";
			ObjectName[ThremixedIDS::CaterKillerJr] = "Obj_CaterKillerJr";
			ObjectName[ThremixedIDS::Jawz] = "Obj_Jawz";
			ObjectName[ThremixedIDS::Blastoid] = "Obj_Blastoid";
			ObjectName[ThremixedIDS::Buggernaut] = "Obj_Buggernaut";
			ObjectName[ThremixedIDS::TurboSpiker] = "Obj_TurboSpiker";
			ObjectName[ThremixedIDS::MegaChomper] = "Obj_MegaChomper";
			ObjectName[ThremixedIDS::Poindexter] = "Obj_Poindexter";
			ObjectName[ThremixedIDS::BubblesBadnik] = "Obj_BubblesBadnik";
			ObjectName[ThremixedIDS::Spiker] = "Obj_Spiker";
			ObjectName[ThremixedIDS::Mantis] = "Obj_Mantis";
			ObjectName[ThremixedIDS::Clamer] = "Obj_Clamer";
			ObjectName[ThremixedIDS::Batbright] = "Obj_Batbright";
			ObjectName[ThremixedIDS::Blaster] = "Obj_Blaster";
			ObjectName[ThremixedIDS::TechnoSqueek] = "Obj_TechnoSqueek";
			ObjectName[ThremixedIDS::Penguinator] = "Obj_Penguinator";
			ObjectName[ThremixedIDS::StarPointer] = "Obj_StarPointer";
			ObjectName[ThremixedIDS::SnaleBlaster] = "Obj_SnaleBlaster";
			ObjectName[ThremixedIDS::Ribot] = "Obj_Ribot";
			ObjectName[ThremixedIDS::Orbinaut] = "Obj_Orbinaut";
			ObjectName[ThremixedIDS::Corkey] = "Obj_Corkey";
			ObjectName[ThremixedIDS::Flybot767] = "Obj_Flybot767";
			ObjectName[ThremixedIDS::GumballItem] = "Obj_GumballItem";
			ObjectName[ThremixedIDS::MagneticOrb] = "Obj_MagneticOrb";
			ObjectName[ThremixedIDS::TiltingBridge] = "Obj_TiltingBridge";
			ObjectName[ThremixedIDS::ElectricInvisibleBlock] = "Obj_ElectricInvisibleBlock";
			ObjectName[ThremixedIDS::FlamingInvisibleBlock] = "Obj_FlamingInvisibleBlock";
			ObjectName[ThremixedIDS::Madmole] = "Obj_Madmole";
			ObjectName[ThremixedIDS::Mushmeanie] = "Obj_Mushmeanie";
			ObjectName[ThremixedIDS::Dragonfly] = "Obj_Dragonfly";
			ObjectName[ThremixedIDS::Butterdroid] = "Obj_Butterdroid";
			ObjectName[ThremixedIDS::Cluckoid] = "Obj_Cluckoid";
			ObjectName[ThremixedIDS::Skorp] = "Obj_Skorp";
			ObjectName[ThremixedIDS::Sandworm] = "Obj_Sandworm";
			ObjectName[ThremixedIDS::Rockn] = "Obj_Rockn";
			ObjectName[ThremixedIDS::Fireworm] = "Obj_Fireworm";
			ObjectName[ThremixedIDS::Toxomister] = "Obj_Toxomister";
			ObjectName[ThremixedIDS::EggRobo] = "Obj_EggRobo";
			ObjectName[ThremixedIDS::Spikebonker] = "Obj_Spikebonker";
			ObjectName[ThremixedIDS::Chainspike] = "Obj_Chainspike";
			ObjectName[ThremixedIDS::ContactLevelChanger] = "Obj_ContactLevelChanger";

			ObjectName[ThremixedIDS::P2RotateObject] = "Obj_P2RotateObject"; // Purpose unknown.

			ObjectName[ThremixedIDS::RetractingSpring2P] = "Obj_RetractingSpring2P";
			ObjectName[ThremixedIDS::Item2P] = "Obj_Item2P";
			ObjectName[ThremixedIDS::GoalMarker2P] = "Obj_GoalMarker2P";

			ObjectName[ThremixedIDS::AIZ_HollowTree] = "Obj_AIZ_HollowTree";
			ObjectName[ThremixedIDS::AIZ_LRZ_EMZ_Rock] = "Obj_AIZ_LRZ_EMZ_Rock";
			ObjectName[ThremixedIDS::AIZ_RideVine] = "Obj_AIZ_RideVine";
			ObjectName[ThremixedIDS::AIZ_SwingVine] = "Obj_AIZ_SwingVine";
			ObjectName[ThremixedIDS::AIZ_DisappearingFloor] = "Obj_AIZ_DisappearingFloor";
			ObjectName[ThremixedIDS::AIZ_FlippingBridge] = "Obj_AIZ_FlippingBridge";
			ObjectName[ThremixedIDS::AIZ_CollapsingLogBridge] = "Obj_AIZ_CollapsingLogBridge";
			ObjectName[ThremixedIDS::AIZ_FallingLog] = "Obj_AIZ_FallingLog";
			ObjectName[ThremixedIDS::AIZ_SpikedLog] = "Obj_AIZ_SpikedLog";
			ObjectName[ThremixedIDS::AIZ_DrawBridge] = "Obj_AIZ_DrawBridge";
			ObjectName[ThremixedIDS::AIZ_ForegroundPlant] = "Obj_AIZ_ForegroundPlant";
			ObjectName[ThremixedIDS::AIZ_CutsceneSonic] = "Obj_AIZ_CutsceneSonic";
			ObjectName[ThremixedIDS::AIZ_Miniboss_Cutscene] = "Obj_AIZ_Miniboss_Cutscene";
			ObjectName[ThremixedIDS::AIZ_Miniboss] = "Obj_AIZ_Miniboss";
			ObjectName[ThremixedIDS::AIZ_EndBoss] = "Obj_AIZ_EndBoss";
			ObjectName[ThremixedIDS::AIZ1_TreeBark] = "Obj_AIZ1_TreeBark";
			ObjectName[ThremixedIDS::AIZ1_RopePeg] = "Obj_AIZ1_RopePeg";

			ObjectName[ThremixedIDS::HCZ_VWaterStream] = "Obj_HCZ_VWaterStream";
			ObjectName[ThremixedIDS::HCZ_CGZ_Fan] = "Obj_HCZ_CGZ_Fan";
			ObjectName[ThremixedIDS::HCZ_LargeFan] = "Obj_HCZ_LargeFan";
			ObjectName[ThremixedIDS::HCZ_HandLauncher] = "Obj_HCZ_HandLauncher";
			ObjectName[ThremixedIDS::HCZ_WaterWall] = "Obj_HCZ_WaterWall";
			ObjectName[ThremixedIDS::HCZ_ConveyorBelt] = "Obj_HCZ_ConveyorBelt";
			ObjectName[ThremixedIDS::HCZ_ConveyorSpike] = "Obj_HCZ_ConveyorSpike";
			ObjectName[ThremixedIDS::HCZ_Block] = "Obj_HCZ_Block";
			ObjectName[ThremixedIDS::HCZ_SnakeBlocks] = "Obj_HCZ_SnakeBlocks";
			ObjectName[ThremixedIDS::HCZ_SpinningColumn] = "Obj_HCZ_SpinningColumn";
			ObjectName[ThremixedIDS::HCZ_Slide] = "Obj_HCZ_Slide";
			ObjectName[ThremixedIDS::HCZ_WaterSplash] = "Obj_HCZ_WaterSplash";
			ObjectName[ThremixedIDS::HCZ_Miniboss] = "Obj_HCZ_Miniboss";
			ObjectName[ThremixedIDS::HCZ_EndBoss] = "Obj_HCZ_EndBoss";

			ObjectName[ThremixedIDS::MGZ_LBZSmashingPillar] = "Obj_MGZ_LBZSmashingPillar";
			ObjectName[ThremixedIDS::MGZ_QuickMud] = "Obj_MGZ_QuickMud";
			ObjectName[ThremixedIDS::MGZ_RunAroundPole] = "Obj_MGZ_RunAroundPole";
			ObjectName[ThremixedIDS::MGZ_SwingingPlatform] = "Obj_MGZ_SwingingPlatform";
			ObjectName[ThremixedIDS::MGZ_HeadTrigger] = "Obj_MGZ_HeadTrigger";
			ObjectName[ThremixedIDS::MGZ_MovingSpikePlatform] = "Obj_MGZ_MovingSpikePlatform";
			ObjectName[ThremixedIDS::MGZ_TriggerPlatform] = "Obj_MGZ_TriggerPlatform";
			ObjectName[ThremixedIDS::MGZ_SwingingSpikeBall] = "Obj_MGZ_SwingingSpikeBall";
			ObjectName[ThremixedIDS::MGZ_DashTrigger] = "Obj_MGZ_DashTrigger";
			ObjectName[ThremixedIDS::MGZ_Pulley] = "Obj_MGZ_Pulley";
			ObjectName[ThremixedIDS::MGZ_TopPlatform] = "Obj_MGZ_TopPlatform";
			ObjectName[ThremixedIDS::MGZ_TopLauncher] = "Obj_MGZ_TopLauncher";
			ObjectName[ThremixedIDS::MGZ_CutsceneMiniBoss] = "Obj_MGZ_CutsceneMiniBoss";
			ObjectName[ThremixedIDS::MGZ_CTwistVine] = "Obj_MGZ_CTwistVine";
			ObjectName[ThremixedIDS::MGZ_MiniBoss] = "Obj_MGZ_MiniBoss";
			ObjectName[ThremixedIDS::MGZ_Boss] = "Obj_MGZ_Boss";
			ObjectName[ThremixedIDS::MGZ_KnucklesBoss] = "Obj_MGZ_KnucklesBoss";
			ObjectName[ThremixedIDS::MGZ2_DrillingEggman] = "Obj_MGZ2_DrillingEggman";

			ObjectName[ThremixedIDS::CNZ_Balloon] = "Obj_CNZ_Balloon";
			ObjectName[ThremixedIDS::CNZ_Cannon] = "Obj_CNZ_Cannon";
			ObjectName[ThremixedIDS::CNZ_RisingPlatform] = "Obj_CNZ_RisingPlatform";
			ObjectName[ThremixedIDS::CNZ_TrapDoor] = "Obj_CNZ_TrapDoor";
			ObjectName[ThremixedIDS::CNZ_LightBulb] = "Obj_CNZ_LightBulb";
			ObjectName[ThremixedIDS::CNZ_HoverFan] = "Obj_CNZ_HoverFan";
			ObjectName[ThremixedIDS::CNZ_RotatingBarrel] = "Obj_CNZ_RotatingBarrel";
			ObjectName[ThremixedIDS::CNZ_VacuumTubes] = "Obj_CNZ_VacuumTubes";
			ObjectName[ThremixedIDS::CNZ_RotatingWheel] = "Obj_CNZ_RotatingWheel";
			ObjectName[ThremixedIDS::CNZ_Bumper] = "Obj_CNZ_Bumper";
			ObjectName[ThremixedIDS::CNZ_BouncepadSprings] = "Obj_CNZ_BouncepadSprings";
			ObjectName[ThremixedIDS::CNZ_Corkscrew] = "Obj_CNZ_Corkscrew";
			ObjectName[ThremixedIDS::CNZ_BarberPoleSprite] = "Obj_CNZ_BarberPoleSprite";
			ObjectName[ThremixedIDS::CNZ_RotatingMesh] = "Obj_CNZ_RotatingMesh";
			ObjectName[ThremixedIDS::CNZ_BreakableWaterRisingFloor] = "Obj_CNZ_BreakableWaterRisingFloor";
			ObjectName[ThremixedIDS::CNZ_LightSwitch] = "Obj_CNZ_LightSwitch";
			ObjectName[ThremixedIDS::CNZ_Blastoid] = "Obj_CNZ_Blastoid";
			ObjectName[ThremixedIDS::CNZ_Miniboss] = "Obj_CNZ_Miniboss";
			ObjectName[ThremixedIDS::CNZ_EndBoss] = "Obj_CNZ_EndBoss";

			ObjectName[ThremixedIDS::ICZ_CrushingColumn] = "Obj_ICZ_CrushingColumn";
			ObjectName[ThremixedIDS::ICZ_PathFollowPlatform] = "Obj_ICZ_PathFollowPlatform";
			ObjectName[ThremixedIDS::ICZ_BreakableWall] = "Obj_ICZ_BreakableWall";
			ObjectName[ThremixedIDS::ICZ_Freezer] = "Obj_ICZ_Freezer";
			ObjectName[ThremixedIDS::ICZ_SegmentColumn] = "Obj_ICZ_SegmentColumn";
			ObjectName[ThremixedIDS::ICZ_SwingingPlatform] = "Obj_ICZ_SwingingPlatform";
			ObjectName[ThremixedIDS::ICZ_Stalagtite] = "Obj_ICZ_Stalagtite";
			ObjectName[ThremixedIDS::ICZ_IceCube] = "Obj_ICZ_IceCube";
			ObjectName[ThremixedIDS::ICZ_IceSpikes] = "Obj_ICZ_IceSpikes";
			ObjectName[ThremixedIDS::ICZ_HarmfulIce] = "Obj_ICZ_HarmfulIce";
			ObjectName[ThremixedIDS::ICZ_SnowPile] = "Obj_ICZ_SnowPile";
			ObjectName[ThremixedIDS::ICZ_TensionPlatform] = "Obj_ICZ_TensionPlatform";
			ObjectName[ThremixedIDS::ICZ_RightTrampolineSupport] = "Obj_ICZ_RightTrampolineSupport";
			ObjectName[ThremixedIDS::ICZ_Miniboss] = "Obj_ICZ_Miniboss";
			ObjectName[ThremixedIDS::ICZ_EndBoss] = "Obj_ICZ_EndBoss";

			ObjectName[ThremixedIDS::MHZ_PulleyLift] = "Obj_MHZ_PulleyLift";
			ObjectName[ThremixedIDS::MHZ_CurledVine] = "Obj_MHZ_CurledVine";
			ObjectName[ThremixedIDS::MHZ_StickyVine] = "Obj_MHZ_StickyVine";
			ObjectName[ThremixedIDS::MHZ_SwingBarHorizontal] = "Obj_MHZ_SwingBarHorizontal";
			ObjectName[ThremixedIDS::MHZ_SwingBarVertical] = "Obj_MHZ_SwingBarVertical";
			ObjectName[ThremixedIDS::MHZ_SwingVine] = "Obj_MHZ_SwingVine";
			ObjectName[ThremixedIDS::MHZ_MushroomPlatform] = "Obj_MHZ_MushroomPlatform";
			ObjectName[ThremixedIDS::MHZ_MushroomParachute] = "Obj_MHZ_MushroomParachute";
			ObjectName[ThremixedIDS::MHZ_MushroomCatapult] = "Obj_MHZ_MushroomCatapult";
			ObjectName[ThremixedIDS::MHZ_MushroomCap] = "Obj_MHZ_MushroomCap";
			ObjectName[ThremixedIDS::MHZ_WindTunnel] = "Obj_MHZ_WindTunnel";
			ObjectName[ThremixedIDS::MHZ_ChopTree] = "Obj_MHZ_ChopTree";
			ObjectName[ThremixedIDS::MHZ_ForceCrouch] = "Obj_MHZ_ForceCrouch";
			ObjectName[ThremixedIDS::MHZ_KnucklesButton] = "Obj_MHZ_KnucklesButton";
			ObjectName[ThremixedIDS::MHZ_Miniboss] = "Obj_MHZ_Miniboss";
			ObjectName[ThremixedIDS::MHZ_EndBoss] = "Obj_MHZ_EndBoss";

			ObjectName[ThremixedIDS::FBZ_RotatingMesh] = "Obj_FBZ_RotatingMesh";
			ObjectName[ThremixedIDS::FBZ_TwistingCylinders] = "Obj_FBZ_TwistingCylinders";
			ObjectName[ThremixedIDS::FBZ_FloatingPlatform] = "Obj_FBZ_FloatingPlatform";
			ObjectName[ThremixedIDS::FBZ_ChainLink] = "Obj_FBZ_ChainLink";
			ObjectName[ThremixedIDS::FBZ_MagneticSpikeBall] = "Obj_FBZ_MagneticSpikeBall";
			ObjectName[ThremixedIDS::FBZ_MagneticPlatform] = "Obj_FBZ_MagneticPlatform";
			ObjectName[ThremixedIDS::FBZ_SnakePlatform] = "Obj_FBZ_SnakePlatform";
			ObjectName[ThremixedIDS::FBZ_BentPipe] = "Obj_FBZ_BentPipe";
			ObjectName[ThremixedIDS::FBZ_RotatingPlatform] = "Obj_FBZ_RotatingPlatform";
			ObjectName[ThremixedIDS::FBZ_DEZPlayerLauncher] = "Obj_FBZ_DEZPlayerLauncher";
			ObjectName[ThremixedIDS::FBZ_DisappearingPlatform] = "Obj_FBZ_DisappearingPlatform";
			ObjectName[ThremixedIDS::FBZ_ScrewDoor] = "Obj_FBZ_ScrewDoor";
			ObjectName[ThremixedIDS::FBZ_FanPole] = "Obj_FBZ_FanPole";
			ObjectName[ThremixedIDS::FBZ_Propeller] = "Obj_FBZ_Propeller";
			ObjectName[ThremixedIDS::FBZ_Piston] = "Obj_FBZ_Piston";
			ObjectName[ThremixedIDS::FBZ_PlatformBlocks] = "Obj_FBZ_PlatformBlocks";
			ObjectName[ThremixedIDS::FBZ_MissileLauncher] = "Obj_FBZ_MissileLauncher";
			ObjectName[ThremixedIDS::FBZ_ExitDoor] = "Obj_FBZ_ExitDoor";
			ObjectName[ThremixedIDS::FBZ_EggPrison] = "Obj_FBZ_EggPrison";
			ObjectName[ThremixedIDS::FBZ_SpringPlunger] = "Obj_FBZ_SpringPlunger";
			ObjectName[ThremixedIDS::FBZ_WallMissile] = "Obj_FBZ_WallMissile";
			ObjectName[ThremixedIDS::FBZ_Mine] = "Obj_FBZ_Mine";
			ObjectName[ThremixedIDS::FBZ_Elevator] = "Obj_FBZ_Elevator";
			ObjectName[ThremixedIDS::FBZ_TrapSpring] = "Obj_FBZ_TrapSpring";
			ObjectName[ThremixedIDS::FBZ_Flamethrower] = "Obj_FBZ_Flamethrower";
			ObjectName[ThremixedIDS::FBZ_SpiderCrane] = "Obj_FBZ_SpiderCrane";
			ObjectName[ThremixedIDS::FBZ_MagneticPendulum] = "Obj_FBZ_MagneticPendulum";
			ObjectName[ThremixedIDS::FBZ_Laser_Boss] = "Obj_FBZ_Laser_Boss";
			ObjectName[ThremixedIDS::FBZ_EndBoss] = "Obj_FBZ_EndBoss";
			ObjectName[ThremixedIDS::FBZ1_Boss] = "Obj_FBZ1_Boss";
			ObjectName[ThremixedIDS::FBZ2_CutsceneObjects] = "Obj_FBZ2_CutsceneObjects";

			ObjectName[ThremixedIDS::LRZ_TubeElevator] = "Obj_LRZ_TubeElevator";
			ObjectName[ThremixedIDS::LRZ_MovingPlatform] = "Obj_LRZ_MovingPlatform";
			ObjectName[ThremixedIDS::LRZ_FlagPlatform] = "Obj_LRZ_FlagPlatform"; // Unused
			ObjectName[ThremixedIDS::LRZ_Door] = "Obj_LRZ_Door";
			ObjectName[ThremixedIDS::LRZ_BigDoor] = "Obj_LRZ_BigDoor";
			ObjectName[ThremixedIDS::LRZ_ExplodingTrigger] = "Obj_LRZ_ExplodingTrigger";
			ObjectName[ThremixedIDS::LRZ_TriggerBridge] = "Obj_LRZ_TriggerBridge";
			ObjectName[ThremixedIDS::LRZ_PlayerLauncher] = "Obj_LRZ_PlayerLauncher";
			ObjectName[ThremixedIDS::LRZ_FlameThrower] = "Obj_LRZ_FlameThrower";
			ObjectName[ThremixedIDS::LRZ_RideGrapple] = "Obj_LRZ_RideGrapple";
			ObjectName[ThremixedIDS::LRZ_CupElevator] = "Obj_LRZ_CupElevator";
			ObjectName[ThremixedIDS::LRZ_CupElevatorPole] = "Obj_LRZ_CupElevatorPole";
			ObjectName[ThremixedIDS::LRZ_PipePlug] = "Obj_LRZ_PipePlug";
			ObjectName[ThremixedIDS::LRZ_HangPlatform] = "Obj_LRZ_HangPlatform";
			ObjectName[ThremixedIDS::LRZ_FireballLauncher] = "Obj_LRZ_FireballLauncher";
			ObjectName[ThremixedIDS::LRZ_ButtonHorizontal] = "Obj_LRZ_ButtonHorizontal";
			ObjectName[ThremixedIDS::LRZ_ShootingTrigger] = "Obj_LRZ_ShootingTrigger";
			ObjectName[ThremixedIDS::LRZ_DashElevator] = "Obj_LRZ_DashElevator";
			ObjectName[ThremixedIDS::LRZ_LavaFall] = "Obj_LRZ_LavaFall";
			ObjectName[ThremixedIDS::LRZ_SwingingSpikeBall] = "Obj_LRZ_SwingingSpikeBall";
			ObjectName[ThremixedIDS::LRZ_SmashingSpikePlatform] = "Obj_LRZ_SmashingSpikePlatform";
			ObjectName[ThremixedIDS::LRZ_SpikeBall] = "Obj_LRZ_SpikeBall";
			ObjectName[ThremixedIDS::LRZ_SpikeBallLauncher] = "Obj_LRZ_SpikeBallLauncher";
			ObjectName[ThremixedIDS::LRZ_OrbitingSpikeBallHorizontal] = "Obj_LRZ_OrbitingSpikeBallHorizontal";
			ObjectName[ThremixedIDS::LRZ_OrbitingSpikeBallVertical] = "Obj_LRZ_OrbitingSpikeBallVertical";
			ObjectName[ThremixedIDS::LRZ_SolidMovingPlatforms] = "Obj_LRZ_SolidMovingPlatforms";
			ObjectName[ThremixedIDS::LRZ_SolidRock] = "Obj_LRZ_SolidRock";
			ObjectName[ThremixedIDS::LRZ_SpinLauncher] = "Obj_LRZ_SpinLauncher";
			ObjectName[ThremixedIDS::LRZ_LoweringGrapple] = "Obj_LRZ_LoweringGrapple";
			ObjectName[ThremixedIDS::LRZ_GateLaser] = "Obj_LRZ_GateLaser";
			ObjectName[ThremixedIDS::LRZ_Siren] = "Obj_LRZ_Siren";
			ObjectName[ThremixedIDS::LRZ_ChainedPlatforms] = "Obj_LRZ_ChainedPlatforms";
			ObjectName[ThremixedIDS::LRZ_FallingSpike] = "Obj_LRZ_FallingSpike";
			ObjectName[ThremixedIDS::LRZ_SinkingRock] = "Obj_LRZ_SinkingRock";
			ObjectName[ThremixedIDS::LRZ_ExplodingRock] = "Obj_LRZ_ExplodingRock";
			ObjectName[ThremixedIDS::LRZ_RockCrusher] = "Obj_LRZ_RockCrusher";
			ObjectName[ThremixedIDS::LRZ_TorpedoLauncher] = "Obj_LRZ_TorpedoLauncher";
			ObjectName[ThremixedIDS::LRZ_RotatingCylinders] = "Obj_LRZ_RotatingCylinders";
			ObjectName[ThremixedIDS::LRZ_VerticalCylinder] = "Obj_LRZ_VerticalCylinder";
			ObjectName[ThremixedIDS::LRZ_CollapsingBridge] = "Obj_LRZ_CollapsingBridge";
			ObjectName[ThremixedIDS::LRZ_TurbineSprites] = "Obj_LRZ_TurbineSprites";
			ObjectName[ThremixedIDS::LRZ_TwirlTunnel] = "Obj_LRZ_TwirlTunnel";
			ObjectName[ThremixedIDS::LRZ_KnucklesEndHelper] = "Obj_LRZ_KnucklesEndHelper";
			ObjectName[ThremixedIDS::LRZ_Miniboss] = "Obj_LRZ_Miniboss";
			ObjectName[ThremixedIDS::LRZ_FinalBoss1] = "Obj_LRZ_FinalBoss1";
			ObjectName[ThremixedIDS::LRZ_FinalBoss2] = "Obj_LRZ_FinalBoss2";
			ObjectName[ThremixedIDS::LRZ_EndBoss] = "Obj_LRZ_EndBoss";
			ObjectName[ThremixedIDS::LRZ1_Eggman] = "Obj_LRZ1_Eggman";
			ObjectName[ThremixedIDS::LRZ1_MiniBoss] = "Obj_LRZ1_MiniBoss";
			ObjectName[ThremixedIDS::LRZ1_KnucklesMiniBossBox] = "Obj_LRZ1_KnucklesMiniBossBox";
			ObjectName[ThremixedIDS::LRZ2_EggMobile] = "Obj_LRZ2_EggMobile";
			ObjectName[ThremixedIDS::LRZ2_TallBoss] = "Obj_LRZ2_TallBoss";
			ObjectName[ThremixedIDS::LRZ3_Platforms] = "Obj_LRZ3_Platforms";

			ObjectName[ThremixedIDS::SOZ_SandFalls] = "Obj_SOZ_SandFalls";
			ObjectName[ThremixedIDS::SOZ_SpawningSandBlocks] = "Obj_SOZ_SpawningSandBlocks";
			ObjectName[ThremixedIDS::SOZ_DoubleLoopPathSwapper] = "Obj_SOZ_DoubleLoopPathSwapper";
			ObjectName[ThremixedIDS::SOZ_SpringLoopPathSwapper] = "Obj_SOZ_SpringLoopPathSwapper";
			ObjectName[ThremixedIDS::SOZ_PushableRock] = "Obj_SOZ_PushableRock";
			ObjectName[ThremixedIDS::SOZ_SpringVine] = "Obj_SOZ_SpringVine";
			ObjectName[ThremixedIDS::SOZ_RisingSandWall] = "Obj_SOZ_RisingSandWall";
			ObjectName[ThremixedIDS::SOZ_LightSwitch] = "Obj_SOZ_LightSwitch";
			ObjectName[ThremixedIDS::SOZ_FloatingPillar] = "Obj_SOZ_FloatingPillar";
			ObjectName[ThremixedIDS::SOZ_SwingingPlatform] = "Obj_SOZ_SwingingPlatform";
			ObjectName[ThremixedIDS::SOZ_BreakableSandRock] = "Obj_SOZ_BreakableSandRock";
			ObjectName[ThremixedIDS::SOZ_PushSwitch] = "Obj_SOZ_PushSwitch";
			ObjectName[ThremixedIDS::SOZ_Door] = "Obj_SOZ_Door";
			ObjectName[ThremixedIDS::SOZ_SandCork] = "Obj_SOZ_SandCork";
			ObjectName[ThremixedIDS::SOZ_RapelWire] = "Obj_SOZ_RapelWire";
			ObjectName[ThremixedIDS::SOZ_SolidSprites] = "Obj_SOZ_SolidSprites";
			ObjectName[ThremixedIDS::SOZ_Ghosts] = "Obj_SOZ_Ghosts";
			ObjectName[ThremixedIDS::SOZ_Miniboss] = "Obj_SOZ_Miniboss";
			ObjectName[ThremixedIDS::SOZ_EndBoss] = "Obj_SOZ_EndBoss";
			ObjectName[ThremixedIDS::SOZ2_GhostCapsuleLoader] = "Obj_SOZ2_GhostCapsuleLoader";
			ObjectName[ThremixedIDS::SOZ2_GhostCapsule] = "Obj_SOZ2_GhostCapsule";

			ObjectName[ThremixedIDS::HPZ_MasterEmerald] = "Obj_HPZ_MasterEmerald";
			ObjectName[ThremixedIDS::HPZ_MidwayPalleteChanger] = "Obj_HPZ_MidwayPalleteChanger";
			ObjectName[ThremixedIDS::HPZ_SuperEmeralds] = "Obj_HPZ_SuperEmeralds";
			ObjectName[ThremixedIDS::HPZ_SpecialStageCreater] = "Obj_HPZ_SpecialStageCreater";

			ObjectName[ThremixedIDS::SSZ_RetractingSpring] = "Obj_SSZ_RetractingSpring";
			ObjectName[ThremixedIDS::SSZ_SwingingCarrier] = "Obj_SSZ_SwingingCarrier";
			ObjectName[ThremixedIDS::SSZ_RotatingPlatform] = "Obj_SSZ_RotatingPlatform";
			ObjectName[ThremixedIDS::SSZ_RetractingBridge] = "Obj_SSZ_RetractingBridge";
			ObjectName[ThremixedIDS::SSZ_HPZTeleporter] = "Obj_SSZ_HPZTeleporter";
			ObjectName[ThremixedIDS::SSZ_ElevatorBar] = "Obj_SSZ_ElevatorBar";
			ObjectName[ThremixedIDS::SSZ_CollapsingBridgeDiagonal] = "Obj_SSZ_CollapsingBridgeDiagonal";
			ObjectName[ThremixedIDS::SSZ_CollapsingBridge] = "Obj_SSZ_CollapsingBridge";
			ObjectName[ThremixedIDS::SSZ_BouncyCloud] = "Obj_SSZ_BouncyCloud";
			ObjectName[ThremixedIDS::SSZ_CollapsingColumn] = "Obj_SSZ_CollapsingColumn";
			ObjectName[ThremixedIDS::SSZ_FloatingPlatform] = "Obj_SSZ_FloatingPlatform";
			ObjectName[ThremixedIDS::SSZ_KnucklesButton] = "Obj_SSZ_KnucklesButton";
			ObjectName[ThremixedIDS::SSZ_EggRobo] = "Obj_SSZ_EggRobo";
			ObjectName[ThremixedIDS::SSZ_GHZBoss] = "Obj_SSZ_GHZBoss";
			ObjectName[ThremixedIDS::SSZ_MTZBoss] = "Obj_SSZ_MTZBoss";
			ObjectName[ThremixedIDS::SSZ_MechaSonicBoss] = "Obj_SSZ_MechaSonicBoss";

			ObjectName[ThremixedIDS::DEZ_FloatingPlatform] = "Obj_DEZ_FloatingPlatform";
			ObjectName[ThremixedIDS::DEZ_HangCarrier] = "Obj_DEZ_HangCarrier";
			ObjectName[ThremixedIDS::DEZ_TorpedoLauncher] = "Obj_DEZ_TorpedoLauncher";
			ObjectName[ThremixedIDS::DEZ_LiftPad] = "Obj_DEZ_LiftPad";
			ObjectName[ThremixedIDS::DEZ_Staircase] = "Obj_DEZ_Staircase";
			ObjectName[ThremixedIDS::DEZ_ConveyorBelt] = "Obj_DEZ_ConveyorBelt";
			ObjectName[ThremixedIDS::DEZ_Lightning] = "Obj_DEZ_Lightning";
			ObjectName[ThremixedIDS::DEZ_ConveyorPad] = "Obj_DEZ_ConveyorPad";
			ObjectName[ThremixedIDS::DEZ_EnergyBridge] = "Obj_DEZ_EnergyBridge";
			ObjectName[ThremixedIDS::DEZ_CurvedEnergyBridge] = "Obj_DEZ_CurvedEnergyBridge";
			ObjectName[ThremixedIDS::DEZ_TunnelLauncher] = "Obj_DEZ_TunnelLauncher";
			ObjectName[ThremixedIDS::DEZ_GravitySwitch] = "Obj_DEZ_GravitySwitch";
			ObjectName[ThremixedIDS::DEZ_ReverseGravityTunnel] = "Obj_DEZ_ReverseGravityTunnel";
			ObjectName[ThremixedIDS::DEZ_TwirlTunnel] = "Obj_DEZ_TwirlTunnel";
			ObjectName[ThremixedIDS::DEZ_GravityReverser] = "Obj_DEZ_GravityReverser";
			ObjectName[ThremixedIDS::DEZ_TunnelJunction] = "Obj_DEZ_TunnelJunction";
			ObjectName[ThremixedIDS::DEZ_RetractingSpring] = "Obj_DEZ_RetractingSpring";
			ObjectName[ThremixedIDS::DEZ_HoverMachine] = "Obj_DEZ_HoverMachine";
			ObjectName[ThremixedIDS::DEZ_SpecialEngineController] = "Obj_DEZ_SpecialEngineController";
			ObjectName[ThremixedIDS::DEZ_BumperWall] = "Obj_DEZ_BumperWall";
			ObjectName[ThremixedIDS::DEZ_GravityPuzzle] = "Obj_DEZ_GravityPuzzle";
			ObjectName[ThremixedIDS::DEZ_Miniboss] = "Obj_DEZ_Miniboss";
			ObjectName[ThremixedIDS::DEZ_EndBoss] = "Obj_DEZ_EndBoss";
			ObjectName[ThremixedIDS::DeathEgg_LaunchTowers] = "Obj_DeathEgg_LaunchTowers";

			ObjectName[ThremixedIDS::DDZ_BossShip] = "Obj_DDZ_BossShip";
			ObjectName[ThremixedIDS::DDZ_Asteroid] = "Obj_DDZ_Asteroid";
			ObjectName[ThremixedIDS::DDZ_Missile] = "Obj_DDZ_Missile";

			ObjectName[ThremixedIDS::CGZ_TriangularSprings] = "Obj_CGZ_TriangularSprings";
			ObjectName[ThremixedIDS::CGZ_BladePlatform] = "Obj_CGZ_BladePlatform";

			ObjectName[ThremixedIDS::BPZ_ElephantBlock] = "Obj_BPZ_ElephantBlock";
			ObjectName[ThremixedIDS::BPZ_Balloon] = "Obj_BPZ_Balloon";

			ObjectName[ThremixedIDS::DPZ_DisolvingSandBar] = "Obj_DPZ_DisolvingSandBar";
			ObjectName[ThremixedIDS::DPZ_Button] = "Obj_DPZ_Button";

			ObjectName[ThremixedIDS::EMZ_Dripper] = "Obj_EMZ_Dripper";

			ObjectName[ThremixedIDS::SS_EntryRing] = "Obj_SS_EntryRing";
			ObjectName[ThremixedIDS::SS_GumballLevel] = "Obj_SS_GumballLevel";
			ObjectName[ThremixedIDS::SS_GumballSideSpring] = "Obj_SS_GumballSideSpring";

			ObjectName[ThremixedIDS::Pachinko_TriangleBumper] = "Obj_Pachinko_TriangleBumper";
			ObjectName[ThremixedIDS::Pachinko_Flipper] = "Obj_Pachinko_Flipper";
			ObjectName[ThremixedIDS::Pachinko_EnergyTrap] = "Obj_Pachinko_EnergyTrap";
			ObjectName[ThremixedIDS::Pachinko_InvisibleUnknown] = "Obj_Pachinko_InvisibleUnknown";
			ObjectName[ThremixedIDS::Pachinko_Platform] = "Obj_Pachinko_Platform";
			ObjectName[ThremixedIDS::Pachinko_ItemOrb] = "Obj_Pachinko_ItemOrb";
		}

		IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "Object Name Assignments", (SDL_GetTicks() - startTime) / 1000.0);
		startTime = SDL_GetTicks();

		if (!Player) {
			Player = new IPlayer();
			Player->G = G;
			Player->App = App;
			Player->Scene = this;
			Player->Character = (CharacterType)(SaveGame::CurrentCharacterFlag & 0xF);
			Player->PlayerID = 0;
			Player->Shield = (ShieldType)(SaveGame::Savefiles[SaveGame::CurrentSaveFile].Shield < 5 ? (uint8_t)SaveGame::Savefiles[SaveGame::CurrentSaveFile].Shield : 0);
			Player->Thremixed = SaveGame::CurrentMode == 1;
			Player->Create();
			Player->Lives = SaveGame::GetLives();
			Players[0] = Player;

			PlayerCount = 1;

			if (SaveGame::CurrentPartnerFlag != 0xFF) {
				Players[1] = new IPlayer();
				Players[1]->G = G;
				Players[1]->App = App;
				Players[1]->Scene = this;
				Players[1]->Sidekick = true;
				Players[1]->Character = (CharacterType)SaveGame::CurrentPartnerFlag;
				Players[1]->PlayerID = 1;
				Players[1]->Thremixed = SaveGame::CurrentMode == 1;
				Players[1]->Create();

				PlayerCount = 2;
			}

			//UNCOMMEN FOR SOME FUCKIN FUN LMAO
			/*for (int i = 0; i < 5; i++) {
				Players[i + 2] = new IPlayer();
				IPlayer* poopler = Players[i + 2];
				poopler->G = G;
				poopler->App = App;
				poopler->Scene = this;
				poopler->Sidekick = true;
				poopler->Character = (CharacterType)(SaveGame::CurrentCharacterFlag & 0xF);
				poopler->PlayerID = i + 2;
				poopler->Thremixed = SaveGame::CurrentMode == 1;
				poopler->Create();
				poopler->Lives = SaveGame::GetLives();
			}
			PlayerCount = 7;
			//uncomment if ever bored*/

			IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "Player Creation", (SDL_GetTicks() - startTime) / 1000.0);
			startTime = SDL_GetTicks();//*/
		}

		Data = new SceneData();
	}

	if (AlreadyLoaded) App->Print(2, "Already loaded %s Act %d! Skipping!!!", LevelNameDiscord, Act);

	if (AlreadyLoaded) return;

	startTime = SDL_GetTicks();

	TileSprite = new ISprite(Str_TileSprite, App);
	TileSprite->SetTransparentColorIndex(0x30);

	if (Str_AnimatedSprites) {
		AnimTileSprite = new ISprite(Str_AnimatedSprites, App);
		AnimTileSprite->LinkPalette(TileSprite);
	}

	if (!SaveGame::CurrentMode == 1) {
		ItemsSprite->LinkPalette(TileSprite);
		ExplosionSprite->LinkPalette(TileSprite);
		ObjectsSprite->LinkPalette(TileSprite);
	}

	IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "TileSprite loading", (SDL_GetTicks() - startTime) / 1000.0);
	startTime = SDL_GetTicks();

	ISprite::Animation an;
	an.Name = "";
	an.FrameCount = 0x400;
	an.Frames = new ISprite::AnimFrame[an.FrameCount];
	if (TileSprite->Width > 16) {
		for (int i = 0; i < 0x400; i++) {
			ISprite::AnimFrame ts_af;
			ts_af.X = (i & 0x1F) << 4;
			ts_af.Y = (i >> 5) << 4;
			ts_af.W = ts_af.H = 16;
			ts_af.OffX = ts_af.OffY = -8;
			an.Frames[i] = ts_af;
			G->MakeFrameBufferID(TileSprite, an.Frames + i);
		}
	} else {
		for (int i = 0; i < 0x400; i++) {
			ISprite::AnimFrame ts_af;
			ts_af.X = 0;
			ts_af.Y = i << 4;
			ts_af.W = ts_af.H = 16;
			ts_af.OffX = ts_af.OffY = -8;
			an.Frames[i] = ts_af;
			G->MakeFrameBufferID(TileSprite, an.Frames + i);
		}
	}
	TileSprite->Animations.push_back(an);

	IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "TileSprite frame buffering", (SDL_GetTicks() - startTime) / 1000.0);
	startTime = SDL_GetTicks();

	// Loading TileConfig
	IResource* TileConfig = IResources::Load(Str_TileConfigBin); // Stages/MSZ/TileConfig.bin
	if (TileConfig) {
		IStreamer tileReader(TileConfig);
		Memory::Free(tileReader.ReadByte4()); // Magic Word

		unsigned char* TileData = tileReader.ReadCompressed();
		IResources::Close(TileConfig);

		Data->tiles1 = new TileCfg[0x400];
		Data->tiles2 = new TileCfg[0x400];

		// Amount of bytes per Tile Definition
		int maxDataBytes = 0x26;
		// Collision Plane 1
		for (int i = 0; i < 0x400; i++) {
			int n = i * maxDataBytes;

			memcpy(Data->tiles1[i].Collision, TileData + n + 0x00, 0x10);
			memcpy(Data->tiles1[i].HasCollision, TileData + n + 0x10, 0x10);
			Data->tiles1[i].IsCeiling = TileData[n + 0x20];
			memcpy(Data->tiles1[i].Config, TileData + n + 0x21, 0x05);
		}
		// Collision Plane 2
		for (int i = 0; i < 0x400; i++) {
			int n = (i + 0x400) * maxDataBytes;

			memcpy(Data->tiles2[i].Collision, TileData + n + 0x00, 0x10);
			memcpy(Data->tiles2[i].HasCollision, TileData + n + 0x10, 0x10);
			Data->tiles2[i].IsCeiling = TileData[n + 0x20];
			memcpy(Data->tiles2[i].Config, TileData + n + 0x21, 0x05);
		}
		delete[] TileData;
	} else {
		App->Print(2, "TileConfig at '%s' could not be read.", Str_TileConfigBin);
		system("pause");
		exit(1);
	}

	IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "TileConfig loading", (SDL_GetTicks() - startTime) / 1000.0);
	startTime = SDL_GetTicks();

	// Loading StageConfig
	// Stageconfig has to be loaded before the scene file so we get the object names
	if (Str_StageBin) {
		App->Print(0, "Loading StageConfig...");
		IResource* StageBin = IResources::Load(Str_StageBin);
		if (StageBin) {
			IStreamer stageReader(StageBin);
			free(stageReader.ReadByte4()); // Magic CFG0
			stageReader.ReadByte(); // UseGameObjects

			//Free previous Object Names
			clearObjectNames();
			//for (int i = 0; i < ObjectNameList.size(); i++)
			//{
				//free(ObjectNameList.at(i));
			//}

			// Read objects names
			int object_count = stageReader.ReadByte();
			for (int i = 0; i < object_count; i++) {
				SetObjectName(stageReader.ReadRSDKString()); // Object name
				//free(stageReader.ReadRSDKString());
			}

			// Read palette
			TileSprite->PaletteSize = 0x100;
			int pp = 0;
			for (int i = 0; i < 8; i++) {
				// IApp::Print(0, "yup: %X", pp);
				int ii = 0;
				int bitmap = stageReader.ReadUInt16();

				int size = 0;
				for (int col = 0; col < 16; col++) {
					if ((bitmap & (1 << col)) != 0) {
						size += 0x10;
					}
				}
				// IApp::Print(0, "size: %X", size);
				for (int col = 0; col < 16; col++) {
					if ((bitmap & (1 << col)) != 0) {
						for (int d = 0; d < 16; d++) {
							uint8_t R = stageReader.ReadByte();
							uint8_t G = stageReader.ReadByte();
							uint8_t B = stageReader.ReadByte();

							uint32_t colour = R << 16 | G << 8 | B;

							Data->Palette[i][col * 16 + d] = colour;

							pp++;
							ii++;
						}
					}
					else
					{
						for (int d = 0; d < 16; d++) {
							uint32_t colour = 0xFF00FF;

							Data->Palette[i][col * 16 + d] = colour;
						}
					}
				}
			}
			TileSprite->UpdatePalette();

			/*
			FILE* f;
			f = fopen(IFILE("Stages/HCZ/ManiaPalette.bin"), "wb");
			fwrite(TileSprite->Palette + 128, 4, 128, f);
			fwrite(TileSprite->PaletteAlt + 128, 4, 128, f);
			fwrite(TileSprite->PaletteAlt, 4, 96, f);
			fclose(f);
			//*/

			// Read WAV channel's max concurrent play
			int wavs_count = stageReader.ReadByte();
			for (int i = 0; i < wavs_count; i++) {
				stageReader.ReadRSDKString(); // WAV name
				stageReader.ReadByte(); // Max Concurrent Play
				//App->Print(0, "WAV: '%s' (max: %d)", wav_name, max_concurrent_play);
			}

			IResources::Close(StageBin);
		}
		else {
			App->Print(2, "StageConfig at '%s' could not be read.", Str_StageBin);
			exit(1);
		}
	}
	else {
		if ((TileSprite->GetPalette(0x81) & 0xFFFFFF) == 0x000000) {
			TileSprite->PaletteSize = 0x80;
		}
		TileSprite->SplitPalette();
		TileSprite->UpdatePalette();

		if (AnimTileSprite) {
			if ((AnimTileSprite->GetPalette(0x81) & 0xFFFFFF) == 0x000000)
				AnimTileSprite->PaletteSize = 0x80;
			AnimTileSprite->SplitPalette();
			AnimTileSprite->UpdatePalette();
		}

		ItemsSprite->SplitPalette();
		ObjectsSprite->SplitPalette();
		ExplosionSprite->SplitPalette();

		ItemsSprite->UpdatePalette();
		ObjectsSprite->UpdatePalette();
		ExplosionSprite->UpdatePalette();
	}

	// Loading SceneBin
	IResource* SceneBin = IResources::Load(Str_SceneBin); // Stages/MSZ/Scene2.bin
	if (SceneBin) {
		IStreamer reader(SceneBin);
		uint32_t mag = reader.ReadUInt32BE(); // magic
		if (mag == 0x4953434E) {
			std::string LevelTitle = reader.ReadRSDKString();
			strcpy(LevelNameDiscord, LevelTitle.c_str());
			strcpy(LevelName, LevelTitle.c_str());

			IApp::Print(2, "Loading '%s'...", LevelName);

			char *TitleCheck = LevelName;
			while (*TitleCheck) {
				if (*TitleCheck >= 'a' && *TitleCheck >= 'z') {
					*TitleCheck += 'A' - 'a';
				} else if (*TitleCheck == ' ') {
					*TitleCheck = ' ';
				} else {
					*TitleCheck = ' ';
                }
				//IApp::Print(2, "Invalid character '%c' in Level Title.", *LevelTitle);
				TitleCheck++;
			}

			ZoneID = reader.ReadByte();
			Act = reader.ReadByte();
			HUDVisible = reader.ReadByte();
			HUDAnim = (HUDVisible ^ 1) * 0x100;
			reader.ReadRSDKString(); // Song File
			reader.ReadUInt32(); // Loop Point
			reader.ReadUInt32(); // Background Color
		} else {
			delete[] reader.ReadBytes(16);
			reader.ReadRSDKString();
			Data->CameraLayer = reader.ReadByte(); // UnknownByte2
		}

		Data->CameraLayer = -1;
		Data->layerCount = reader.ReadByte();
		for (int i = 0; i < Data->layerCount; i++) {
			reader.ReadByte(); // Ignored Byte

			Data->Layers[i].Name = reader.ReadRSDKString();
			Data->Layers[i].IsScrollingVertical = reader.ReadByte() == 1 ? true : false;
			Data->Layers[i].Flags = reader.ReadByte();
			if (Data->Layers[i].Flags & 0x10) {
				Data->Layers[i].Visible = false;
            }

            Data->Layers[i].DeformX = (int8_t*)Memory::TrackedCalloc("LevelScene::Data->Layers[i].DeformX", 1, App->HEIGHT);
			Data->Layers[i].DeformY = (int8_t*)Memory::TrackedCalloc("LevelScene::Data->Layers[i].DeformY", 1, App->WIDTH);

			int Width = (int)reader.ReadUInt16();
			int Height = (int)reader.ReadUInt16();

			Data->Layers[i].RelativeY = reader.ReadUInt16();
			Data->Layers[i].ConstantY = reader.ReadUInt16();

			Data->Layers[i].InfoCount = (int)reader.ReadUInt16();

			if (Data->Layers[i].InfoCount) {
				Data->Layers[i].Info = new ScrollingInfo[Data->Layers[i].InfoCount];
            }

			App->Print(3, "Layer %d (%s): Width (%d) Height (%d) Infos (%d) Vertical Scrolling (%d) UnknownFlags (%d) %s", i, Data->Layers[i].Name.c_str(), Width, Height, Data->Layers[i].InfoCount, Data->Layers[i].IsScrollingVertical, Data->Layers[i].Flags, i == Data->CameraLayer ? " IS CAMERA LAYER" : "");

			for (int g = 0; g < Data->Layers[i].InfoCount; g++) {
				Data->Layers[i].Info[g].RelativeX = reader.ReadUInt16(); // actually is Scrolling Multiplier X
				Data->Layers[i].Info[g].ConstantX = reader.ReadUInt16(); // actually is Constant movement X

				Data->Layers[i].Info[g].Behaviour = reader.ReadByte();
				Data->Layers[i].Info[g].DrawLayer = reader.ReadByte();

				if (Data->CameraLayer == -1) {
					if (Data->Layers[i].RelativeY == 0x100 &&
						Data->Layers[i].ConstantY == 0x000 &&
						Data->Layers[i].Info[g].RelativeX == 0x100 &&
						Data->Layers[i].Info[g].ConstantX == 0x000 &&
						Data->Layers[i].Name[0] == 'F' &&
						Data->Layers[i].InfoCount == 1)
						Data->CameraLayer = i;
				}

				//App->Print(0, " > ScrollInfo %d: RelX (%X) ConstX (%X) %d %d", g, Data->Layers[i].Info[g].RelativeX, Data->Layers[i].Info[g].ConstantX, Data->Layers[i].Info[g].Behaviour, Data->Layers[i].Info[g].Byte2);
			}

			if ((mag >> 24) == 'S') {
				Data->Layers[i].Flags = 0;
				if (Data->Layers[i].RelativeY == 0x100 &&
					Data->Layers[i].ConstantY == 0x000 &&
					Data->Layers[i].Info[0].RelativeX == 0x100 &&
					Data->Layers[i].Info[0].ConstantX == 0x000 &&
					Data->Layers[i].Name[0] == 'F' &&
					Data->Layers[i].InfoCount == 1)
					Data->Layers[i].Flags = 1;
			}

			// FUN FACT:
			// With all compressed data, we already know the size of the data. (using Width, Height, etc.)

			unsigned char* ScrollIndexes = reader.ReadCompressed();

			int cnt = 0;
			if (Height > 0) { // Just in case
				int s_start = 0;
				int value = ScrollIndexes[0];
				int s = 0;
				for (; s < Height * 16; s++) {
					int v = ScrollIndexes[s];
					if (v != value) {
						cnt++;
						s_start = s;
						value = v;
					}
				}
				cnt++;
				Data->Layers[i].ScrollIndexCount = cnt;
			}
            
			Data->Layers[i].ScrollIndexes = new ScrollingIndex[cnt];

			if (Height > 0) { // Just in case
				int sc = 0;
				int s_start = 0;
				int value = ScrollIndexes[0];
				int s = 0;
				for (; s < Height * 16; s++) {
					// ScrollingIndex
					int v = ScrollIndexes[s];
					// If we find a different value, cap it off and start anew.
					if (v != value) {
						Data->Layers[i].ScrollIndexes[sc].Index = value;
						Data->Layers[i].ScrollIndexes[sc].Size = s - s_start;
						//App->Print(0, " - ScrollIndex %d: Index %d Size %d", sc, Data->Layers[i].ScrollIndexes[sc].Index, Data->Layers[i].ScrollIndexes[sc].Size);

						sc++;
						s_start = s;
						value = v;
					}
				}
				// Data->Layers[i].ScrollIndexes[sc] = ScrollingIndex { value, s - s_start, NULL };
				Data->Layers[i].ScrollIndexes[sc].Index = value;
				Data->Layers[i].ScrollIndexes[sc].Size = s - s_start;
				//App->Print(0, " - ScrollIndex %d: Index %d Size %d", sc, Data->Layers[i].ScrollIndexes[sc].Index, Data->Layers[i].ScrollIndexes[sc].Size);
			}
			delete[] ScrollIndexes;

			Data->Layers[i].Width = Width;
			Data->Layers[i].Height = Height;
			unsigned char* Tilesss = reader.ReadCompressed();

			Data->Layers[i].Tiles = new short[Width * Height * sizeof(short)];
			Data->Layers[i].TilesBackup = new short[Width * Height * sizeof(short)];
			Data->Layers[i].TileOffsetY = (short*)Memory::TrackedCalloc("LevelScene::Data->Layers[i].TileOffsetY", sizeof(short), Width);


			IStreamer creader(Tilesss);
			for (int y = 0; y < Height; y++) {
				for (int x = 0; x < Width; x++) {
					Data->Layers[i].Tiles[x + y * Width] = creader.ReadUInt16();
				}
			}

			PatchLayer(i);

			memcpy(Data->Layers[i].TilesBackup, Data->Layers[i].Tiles, Width * Height * sizeof(short));
			delete[] Tilesss;
		}

		enum {
			OBJ_SPRING = 0x2802B89EU, //
			OBJ_STARPOST = 0xC8B337E6U, //
			OBJ_SPIKES = 0x44BC7B0EU, //
			OBJ_SPECIALRING = 0xABC2C658U, //

			OBJ_PLANESWITCHER = 0x91586422U, // 0x91586422U
			OBJ_PLAYER = 0xD68AF920U,
			OBJ_RING = 0x2EA61FD6U,
			OBJ_MONITOR = 0xD028F874U, // 0xB3C47F67U
		};

		enum {
			ATTRIBUTE_UINT8,
			ATTRIBUTE_UINT16,
			ATTRIBUTE_UINT32,
			ATTRIBUTE_INT8,
			ATTRIBUTE_INT16,
			ATTRIBUTE_INT32,
			ATTRIBUTE_VAR,
			ATTRIBUTE_BOOL,
			ATTRIBUTE_STRING,
			ATTRIBUTE_POSITION,
			ATTRIBUTE_UNKNOWN,
			ATTRIBUTE_COLOR,
		};

		PlaneSwitchers = (PlaneSwitch*)Memory::TrackedMalloc("LevelScene::PlaneSwitchers", 113 * sizeof(PlaneSwitch));

		Data->IsAnims = (short*)Memory::TrackedMalloc("LevelScene::Data->IsAnims", 0x400 * sizeof(short));
		std::memset(Data->IsAnims, 0xFF, 0x400 * sizeof(short));

		// Mania-type Object Loading
		if ((mag >> 24) == 'S') {
			BlankTile = 0x3FF;
			ManiaLevel = true;

			unordered_map<string, const char*> ObjectHashes;
			for (int i = 0; i < 554; i++) {
				string Hash = MD5I(string(ObjectNames(i)));
				ObjectHashes[Hash] = ObjectNames(i);
			}

			for (int i = 0; i < GetObjectNamesSize(); i++) {
				string Hash = MD5I(string(GetObjectName(i))); // Create a hash for the name
				ObjectHashes[Hash] = GetObjectName(i); // Set the name to be associated with said hash
			}

			int AttributeTypes[0x40];
			AttributeValue Attributes[0x40];

			// Clear objects
			Objects.clear();
			ObjectCount = 0;
			ObjectNewCount = 0;

			Data->ObjectDefinitionCount = reader.ReadByte();
			for (int i = 0; i < Data->ObjectDefinitionCount; i++) {
				char str[16];
				char HashString[33];
				sprintf(HashString, "%s", "");

				// Read the Object's Hash
				for (int n = 0; n < 16; n++) {
					str[n] = reader.ReadByte();
					sprintf(HashString, "%s%02x", HashString, (unsigned char)str[n]);
				}

				// Get our object name
				const char* ObjectName = ObjectHashes[HashString];
				if (ObjectName == NULL) {
                    ObjectName = "Unimplemented Object";
                }
				App->Print(0, ObjectName);
				uint32_t ObjHash = crc32((char*)str, 16);

				// Allocate our types.
				int AttributeCount = reader.ReadByte();

				// Clear out the Attributes we'll use.
				for (int n = 1; n < AttributeCount; n++)
				{
					AttributeTypes[n] = 0xFF;
					CreateAttributeValue(&Attributes[n]);
				}

				// Load Attribute Names
				// Skip 'filter' (it's handled weirdly)
				for (int n = 1; n < AttributeCount; ++n) {
					// Read our attribute hash into our array
					for (int n2 = 0; n2 < 16; n2++) {
						Attributes[n].NameHash[n2] = reader.ReadByte();
					}

					// Read what type this attribute is
					int AttributeType = reader.ReadByte();
					AttributeTypes[n] = AttributeType;
				}

				int EntityCount = reader.ReadUInt16();

				// Load all Entities
				for (int n = 0; n < EntityCount; ++n) {
					// Spawn in our entity
					Object* obj = GetNewObjectFromCRC32(ObjHash);

					if (obj == NULL) {
                        obj = new BlankObject();
                    }

					unsigned short SlotID = reader.ReadUInt16(); //SlotID
					if (obj) { 
                        obj->SlotID = SlotID;
                    }

					unsigned short X_low = reader.ReadUInt16();
					short X_high = reader.ReadInt16();
					unsigned short Y_low = reader.ReadUInt16();
					short Y_high = reader.ReadInt16();

					if (obj) {
						obj->InitialX = X_high + ((float)X_low / 0x10000);
						obj->InitialY = Y_high + ((float)Y_low / 0x10000);
						obj->X = X_high + ((float)X_low / 0x10000);
						obj->Y = Y_high + ((float)Y_low / 0x10000);
					}

					// If we have more than one attribute
					if (AttributeCount > 1) {
						for (int a = 1; a < AttributeCount; a++) {
							switch (AttributeTypes[a]) {
                                case ATTRIBUTE_INT8:
                                    Attributes[a].ValInt8 = (char)reader.ReadByte();
                                    break;
                                case ATTRIBUTE_UINT8:
                                    Attributes[a].ValUint8 = (unsigned char)reader.ReadByte();
                                    break;
                                case ATTRIBUTE_INT16:
                                    Attributes[a].ValInt16 = (short)reader.ReadInt16();
                                case ATTRIBUTE_UINT16:
                                    Attributes[a].ValUint16 = (unsigned short)reader.ReadUInt16();
                                    break;
                                case ATTRIBUTE_VAR:
                                    Attributes[a].ValVariable = (unsigned int)reader.ReadUInt32();
                                    break;
                                case ATTRIBUTE_BOOL:
                                    Attributes[a].ValBool = reader.ReadUInt32() != 0;
                                    break;
                                case ATTRIBUTE_COLOR:
                                    Attributes[a].ValColor.b = reader.ReadByte();
                                    Attributes[a].ValColor.g = reader.ReadByte();
                                    Attributes[a].ValColor.r = reader.ReadByte();
                                    Attributes[a].ValColor.a = reader.ReadByte();
                                    break;
                                case ATTRIBUTE_INT32:
                                    Attributes[a].ValInt32 = (int)reader.ReadInt32();
                                    break;
                                case ATTRIBUTE_UINT32:
                                    Attributes[a].ValUint32 = (unsigned int)reader.ReadUInt32();
                                    break;
                                case ATTRIBUTE_STRING:
                                    Attributes[a].ValString = reader.ReadRSDKUnicodeString();
                                    break;
                                case ATTRIBUTE_POSITION:

                                    Attributes[a].ValPosition.X = reader.ReadInt16() + ((float)reader.ReadUInt16() / 0x10000);
                                    Attributes[a].ValPosition.Y = reader.ReadInt16() + ((float)reader.ReadUInt16() / 0x10000);
                                    break;
							}
							if (obj) {
								std::string HashString = std::string(Attributes[a].NameHash);
								if (HashString.size() > 16) {
                                    HashString.erase(16);
                                }
								obj->ObjectAttributes.emplace(HashString, Attributes[a]);
								obj->ObjectAttributeCount++;
							}
						}
					}

					if (obj && (ObjHash != OBJ_RING && ObjHash != OBJ_PLANESWITCHER)) {
						obj->G = G;
						obj->App = App;
						obj->Scene = this;

						obj->Sprite = App->NullSprite;

						//Store our name
						obj->Name = ObjectName;

						if (obj->BinIndex == 0xFFFFFFFF && (ObjectName != "BlankObject" && ObjectName != "PlayerSpawn")) {
						} else {
							obj->Sprite = SpriteBinMapIDs.at(obj->BinIndex);
						}
						obj->DrawCollisions = App->viewObjectCollision;

						// Dunno what do to with filter so fuck it for now
						obj->ObjectAttributeCount = AttributeCount - 1;

						//Store object type
						obj->ID = GetObjectIDFromName(obj->Name.c_str());

						// Done for backwards compatibility, Returns 0 on error.
						obj->SubType = obj->GetAttribute("Subtype")->ValUint8;

						// Load our filter attribute, And if nothing return 0.
						obj->Filter = obj->GetAttribute("Filter")->ValUint8;

						//Setup object flags
						obj->S3Object = bool(obj->Filter >> 0 & 1);
						obj->SKObject = bool(obj->Filter >> 1 & 1);
						obj->MixedObject = bool(obj->Filter >> 2 & 1);
						obj->LockedOnObject = bool(obj->Filter >> 3 & 1);
						obj->EasyModeObject = bool(obj->Filter >> 4 & 1);
						obj->NormalModeObject = bool(obj->Filter >> 5 & 1);
						obj->HardModeObject = bool(obj->Filter >> 6 & 1);

						// Done for backwards compatibility, Returns false on error.
						obj->FlipX = obj->GetAttribute("FlipX")->ValBool;
						obj->FlipY = obj->GetAttribute("FlipY")->ValBool;

						obj->Create();

						// Add our object to the scene
						Objects.push_back(obj);
						ObjectCount++;
						//ObjectNewCount++;
					} else if (obj && ObjHash == OBJ_RING) {
                        ObjectProp op;
                        op.X = obj->X;
                        op.Y = obj->Y;
                        op.ID = 0xFF;
                        op.LoadFlag = true;

                        RingPropCount++;
                        RingProps.push_back(op);
                        delete obj;
					} 
					if (obj && ObjHash == OBJ_PLANESWITCHER) {
						PlaneSwitchers[PlaneSwitchCount].X = obj->X;
						PlaneSwitchers[PlaneSwitchCount].Y = obj->Y;
						PlaneSwitchers[PlaneSwitchCount].Angle = obj->GetAttribute("Angle")->ValUint32;
						PlaneSwitchers[PlaneSwitchCount].Flags = obj->GetAttribute("Flags")->ValUint32;
						PlaneSwitchers[PlaneSwitchCount].OnPath = obj->GetAttribute("OnPath")->ValBool;
						PlaneSwitchers[PlaneSwitchCount].Size = obj->GetAttribute("Size")->ValUint32;
						if (PlaneSwitchers[PlaneSwitchCount].Size <= 0) PlaneSwitchers[PlaneSwitchCount].Size = 1;
						PlaneSwitchCount++;
					}
				}

				//Figure this out it crash :(
				if (AttributeCount > 1) {
					//free(AttributeTypes);
					//free(attributes);
				}
			}
			//delete[] AttributeTypes;
			//delete[] attributes;
		}
		// ImpostorEngine2-temp-type Loading
		else if ((mag >> 24) == 'U') {
			BlankTile = 0;

			reader.ReadByte(); // to get rid of the leftover "ObjectCount"
			int pX = reader.ReadUInt16();
			int pY = reader.ReadUInt16();
			if (PlayerStartX == -1) { // && Not Playing as Knuckles
				PlayerStartX = pX;
				PlayerStartY = pY;
			}
			pX = reader.ReadUInt16();
			pY = reader.ReadUInt16();
			if (PlayerStartX == -1 && false) { // && Playing as Knuckles
				PlayerStartX = pX;
				PlayerStartY = pY;
			}

			int objectCount = reader.ReadUInt16();
			unsigned char ObjectListUnimpl[0x100];
			std::memset(ObjectListUnimpl, 0, 0x100);
			for (int o = 0; o < objectCount; o++) {
				int X = reader.ReadUInt16BE();
				int Y = reader.ReadUInt16BE();

				int data = (Y & 0xF000) / 0x1000;
				int PRIORITY = (data >> 3) & 0x01;
				int FLIPX = (data >> 1) & 0x01;
				int FLIPY = (data >> 2) & 0x01;
				int ID = reader.ReadByte();
				int SubType = reader.ReadByte();
				Y &= 0x0FFF;

				if (ID == 0x02) {
					int H = (4 << (SubType & 0x03)) - 1;

					int groundOnly = (SubType >> 7) & 0x01;
					int orientation = (SubType >> 2) & 0x01;

					int leftUpPath = ((SubType >> 4) & 0x01);
					int rightDownPath = ((SubType >> 3) & 0x01);
					int leftUpPriority = ((SubType >> 6) & 0x01); //1 is high, 0 is low
					int rightDownPriority = ((SubType >> 5) & 0x01);

					PlaneSwitchers[PlaneSwitchCount].X = X;
					PlaneSwitchers[PlaneSwitchCount].Y = Y;

					PlaneSwitchers[PlaneSwitchCount].Flags = rightDownPath << 3 | rightDownPriority << 2 | leftUpPath << 1 | leftUpPriority;
					PlaneSwitchers[PlaneSwitchCount].Size = H;
					PlaneSwitchers[PlaneSwitchCount].Angle = orientation * 0xC0;
					PlaneSwitchers[PlaneSwitchCount].OnPath = groundOnly == 1;
					PlaneSwitchCount++;
				} else {
					ObjectProp op;
					op.X = X;
					op.Y = Y;
					op.ID = ID;
					op.SubType = SubType;
					op.LoadFlag = PRIORITY;
					op.FlipX = FLIPX;
					op.FlipY = FLIPY;

					ObjectPropCount++;
                    ObjectProps.push_back(op);

					Object* obj = GetNewObjectFromID(ID);
					if (obj == NULL) obj = new BlankObject();
					if (obj) {
						obj->G = G;
						obj->App = App;
						obj->Scene = this;
						obj->InitialX = X;
						obj->InitialY = Y;
						obj->FlipX = FLIPX == 1;
						obj->FlipY = FLIPY == 1;
						obj->ID = ID;

                        if (obj->BinIndex == 0xFFFFFFFF) {
                            while (obj->ID >= SpriteMapIDs.size() || !SpriteMapIDs.at(ID)) {
                                ID--;
                            }

                            obj->Sprite = SpriteMapIDs.at(ID);
                        } else if (obj->BinIndex < SpriteBinMapIDs.size()) {
                            obj->Sprite = SpriteBinMapIDs.at(obj->BinIndex);
                        }

						obj->DrawCollisions = App->viewObjectCollision;

						obj->SubType = SubType;
						ObjectCount++;
						Objects.push_back(obj);
					} else {
						ObjectListUnimpl[ID] = 0xFF;
					}
				}
			}
			for (int i = 0; i < 0x100; i++) {
				if (ObjectListUnimpl[i] != 0)
					App->Print(1, "Object %02X (%s) has not been implemented!", i, ObjectName[i] ? ObjectName[i] : "(null)");
			}

			int ringCount = reader.ReadUInt16();
			for (int o = 0; o < ringCount; o++) {
				int X = reader.ReadUInt16BE();
				int Y = reader.ReadUInt16BE();

				ObjectProp op;
				op.X = X;
				op.Y = Y;
				op.ID = 0xFF;
				op.LoadFlag = true;

                RingPropCount++;
                RingProps.push_back(op);
			}

			int animTilesCount = reader.ReadUInt16();
			vector<int> tils;
			for (int o = 0; o < animTilesCount; o++) {
				int til = reader.ReadUInt16();
				int row = reader.ReadByte();
				int whichanim = reader.ReadByte();
				Data->IsAnims[til] = row << 8 | whichanim;

				tils.push_back(Data->IsAnims[til]);
			}

			Data->animatedTilesCount = reader.ReadUInt16();

			Data->animatedTileFrames = (int*)Memory::TrackedCalloc("Data->animatedTileFrames", Data->animatedTilesCount, sizeof(int));

			Data->animatedTileDurations = (int**)Memory::TrackedCalloc("Data->animatedTileDurations", Data->animatedTilesCount, sizeof(int*));
			for (int o = 0; o < Data->animatedTilesCount; o++) {
				int framecount = reader.ReadUInt16();
				Data->animatedTileDurations[o] = (int*)Memory::TrackedCalloc("Data->animatedTileDurations[o]", framecount + 2, sizeof(int));
				Data->animatedTileDurations[o][0] = framecount;

				int sum = 0;
				for (int g = 1; g < framecount + 1; g++) {
					Data->animatedTileDurations[o][g] = reader.ReadByte();
					sum += Data->animatedTileDurations[o][g];
				}
				Data->animatedTileDurations[o][framecount + 1] = sum;
			}

			for (int o = 0; o < animTilesCount; o++) {
				int framecount = Data->animatedTileDurations[tils[o] & 0xFF][0];

				if (!framecount) {
					App->Print(2, "Encountered a frame count of 0 on Animation Tile %d out of %d!", o, animTilesCount);
					exit(1);
				}

				ISprite::Animation an;
				an.Name = "";
				an.FrameCount = framecount;
				an.Frames = new ISprite::AnimFrame[an.FrameCount];
				for (int i = 0; i < framecount; i++) {
					ISprite::AnimFrame ts_af;
					ts_af.X = i << 4;
					ts_af.Y = o << 4;
					ts_af.W = ts_af.H = 16;
					ts_af.OffX = ts_af.OffY = -8;
					an.Frames[i] = ts_af;
					G->MakeFrameBufferID(AnimTileSprite, an.Frames + i);
				}
				AnimTileSprite->Animations.push_back(an);
			}
		}
		// ImpostorEngine2-type Object Loading
		else if ((mag >> 24) == 'I') {
			BlankTile = 0;

			Data->ObjectDefinitionCount = reader.ReadUInt16();
			for (int i = 0; i < Data->ObjectDefinitionCount; i++) {
				uint32_t objHash = reader.ReadUInt32();
				std::string name = reader.ReadRSDKString();

				int AttributeCount = reader.ReadByte();
				int* AttributeTypes = (int*)Memory::TrackedCalloc("temp AttributeTypes", AttributeCount, sizeof(int));
				for (int n = 0; n < AttributeCount; n++) {
					AttributeTypes[n] = reader.ReadByte();
				}

				int ObjCount = reader.ReadUInt16();
				App->Print(2, "Object Hash: %08X (%s) Count: %d AttributeCount: %d", objHash, name.c_str(), ObjCount, AttributeCount);

				for (int n = 0; n < ObjCount; n++) {
					unsigned int X = reader.ReadUInt16();
					unsigned int Y = reader.ReadUInt16();
					bool FlipX = reader.ReadByte();
					bool FlipY = reader.ReadByte();
					bool Priority = reader.ReadByte();
					bool Unused = reader.ReadByte();

					int* args = (int*)Memory::TrackedCalloc("temp args", sizeof(int), AttributeCount);
					for (int a = 0; a < AttributeCount; a++) {
						args[a] = reader.ReadUInt32();
						if (objHash == 0xB3C47F67U) {
							App->Print(0, "Argument %d value: %d", a, args[a]);
						}
					}

					PlayerStartX = 64;
					PlayerStartY = 64;

					switch (objHash) {
						/*
						case OBJ_PLANESWITCHER:
							PlaneSwitchers[PlaneSwitchCount].X = X;
							PlaneSwitchers[PlaneSwitchCount].Y = Y;

							PlaneSwitchers[PlaneSwitchCount].Flags = args[0];
							PlaneSwitchers[PlaneSwitchCount].Size = args[1];
							PlaneSwitchers[PlaneSwitchCount].Angle = args[2];
							PlaneSwitchers[PlaneSwitchCount].OnPath = args[3] == 1;
							PlaneSwitchCount++;
							break;
						case OBJ_PLAYER:
						{
							if (args[0] == CharacterFlag) {
								PlayerStartX = X2 + (X1 >> 16);
								PlayerStartY = Y2 + (Y1 >> 16) - 4;
							}
							break;
						}
						case OBJ_SPRING:
						{
							int ID = 0x07;
							int X = X2;
							int Y = Y2;
							int SubType = 0x00;
							if ((args[0] & 0x1) == 0)
								SubType |= 0x02;

							int ttty = args[0] >> 1 & 0x3;
							bool FLIPX = (args[1] >> 0) & 1;
							bool FLIPY = (args[1] >> 1) & 1;
							bool PRIORITY = false;

							if (ttty == 0) {
								if (FLIPY)
									SubType |= 0x20;
								else
									SubType |= 0x0;
							}
							else if (ttty == 1) {
								SubType |= 0x10;
							}
							else if (ttty == 2) {
								if (!FLIPY)
									SubType |= 0x30;
								else
									SubType |= 0x40;
							}

							ADD_OBJECT();
							break;
						}
						case OBJ_SPECIALRING:
						{
							int ID = 0x85;
							int X = X2;
							int Y = Y2;
							int SubType = args[0];
							bool FLIPX = false;
							bool FLIPY = false;
							bool PRIORITY = false;

							ADD_OBJECT();
							break;
						}
						case OBJ_SPIKES:
						{
							int ID = 0x08;
							int X = X2;
							int Y = Y2;
							int SubType = 0x00;
							bool FLIPX = false;
							bool FLIPY = false;
							bool PRIORITY = false;

							if (args[1] == 1)
								SubType |= 0x02;
							if (args[0] == 2) {
								SubType |= 0x40;
								FLIPX = true;
							}

							ADD_OBJECT();
							break;
						}
						case OBJ_STARPOST:
						{
							int ID = Obj_StarPost;
							int X = X2;
							int Y = Y2;
							int SubType = args[0];

							bool FLIPX = false;
							bool FLIPY = false;
							bool PRIORITY = false;

							ADD_OBJECT();
							break;
						}
						case OBJ_RING:
						{
							ObjectProp op;
							op.X = X2;
							op.Y = Y2;
							op.ID = 0xFF;
							op.LoadFlag = true;

                            RingPropCount++;
                            RingProps.push_back(op);
							break;
						}
						//*/

					case OBJ_MONITOR:
						objHash = 0xB3C47F67U;
					default:
						Object * obj = GetNewObjectFromCRC32(objHash);
						if (obj == NULL) obj = new BlankObject();
						if (obj) {
							if (objHash != 0xA5066DF4U &&
								objHash != 0xB3C47F67U) {
								IApp::Print(1, "Unimplemented object: %s", name);
								break;
							}

							obj->X = X;
							obj->Y = Y;
							obj->G = G;
							obj->App = App;
							obj->Scene = this;
							obj->InitialX = X;
							obj->InitialY = Y;
							obj->FlipX = false;
							obj->FlipY = false;
							obj->ID = 0;

							if (objHash == 0xB3C47F67U) {
								obj->Sprite = ItemsSprite;
							}

							obj->DrawCollisions = App->viewObjectCollision;

							ObjectCount++;
							Objects.push_back(obj);
						}
						break;
					}

					Memory::Free(args);
				}

				Memory::Free(AttributeTypes);
			}
		}

		for (int i = 0; i < Data->layerCount; i++) {
			// Build buffers for GL renderer
			if (Data->Layers[i].InfoCount) {
				int y = 0;
				int siT, x;
				int tile = 0, flipY = 0, flags = 0;//, wheree = 0;
				int heightSize = 0, tilindx = 0, tilindy = 0, tilindpos = 0, word = 0;
				Layer layer = Data->Layers[i];

				int bufHeight = 0;
				for (int s = 0; s < layer.ScrollIndexCount; s++) {
					for (siT = 0; siT < layer.ScrollIndexes[s].Size; siT += heightSize) {
						heightSize = 16;
						if (heightSize > layer.ScrollIndexes[s].Size - siT)
							heightSize = layer.ScrollIndexes[s].Size - siT;
						if (heightSize > ((y + siT + 0x10) & ~0xF) - (y + siT)) // Rounded-up
							heightSize = ((y + siT + 0x10) & ~0xF) - (y + siT);

						bufHeight++;
					}
					y += layer.ScrollIndexes[s].Size;
				}

				y = 0;
				int buf = 0;
				int fullFlip;
				// layer.Width * bufHeight
				layer.ScrollIndexes[0].TileBuffers = (int*)calloc(bufHeight, sizeof(int));
				for (int s = 0; s < layer.ScrollIndexCount; s++) {
					for (siT = 0; siT < layer.ScrollIndexes[s].Size; siT += heightSize) {
						heightSize = 16;
						if (heightSize > layer.ScrollIndexes[s].Size - siT)
							heightSize = layer.ScrollIndexes[s].Size - siT;
						if (heightSize > ((y + siT + 0x10) & ~0xF) - (y + siT)) // Rounded-up
							heightSize = ((y + siT + 0x10) & ~0xF) - (y + siT);

						G->BeginSpriteListBuffer();

						for (x = 0; x < layer.Width; x++) {
							tilindy = ((y + siT) >> 4);
							tilindx = x;
							tilindpos = x + (tilindy)* layer.Width;

							word = layer.Tiles[tilindpos];
							fullFlip = ((word >> 10) & 3);
							flipY = ((word >> 11) & 1);
							tile = word & 0x3FF;

							if (tile != BlankTile) {
								int anID = Data->IsAnims[tile] & 0xFF;

								flags = 0;
								if (flipY)
									flags |= IE_FLIPY;

								int wheree = (y + siT) & 0xF;
								if (flipY)
									wheree = 0x10 - wheree - heightSize;

								if (anID == 0xFF) {
									/*
									// Data->Layers[i].ScrollIndexes[0].TileBuffers[x + buf * layer.Width] =
									G->MakeFrameBufferID(TileSprite, &Data->Layers[i].ScrollIndexes[0].TileBuffers[x + buf * layer.Width], ((tile & 0x1F) << 4), ((tile >> 5) << 4) + wheree, 16, heightSize, -8, -heightSize / 2, fullFlip);
									//*/
									if (TileSprite->Width > 16)
										G->AddToSpriteListBuffer(TileSprite, ((tile & 0x1F) << 4), ((tile >> 5) << 4) + wheree, 16, heightSize, -8 + (x << 4), -heightSize / 2, fullFlip);
									else
										G->AddToSpriteListBuffer(TileSprite, 0, (tile << 4) + wheree, 16, heightSize, -8 + (x << 4), -heightSize / 2, fullFlip);
								}
							}
						}

						Data->Layers[i].ScrollIndexes[0].TileBuffers[buf] = G->FinishSpriteListBuffer();
						buf++;
					}

					y += layer.ScrollIndexes[s].Size;
				}
			}
		}

		IResources::Close(SceneBin);
	}
	else {
		App->Print(2, "Scene.bin at '%s' could not be read.", Str_SceneBin);
		exit(1);
	}

	IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "Scene loading", (SDL_GetTicks() - startTime) / 1000.0);
	startTime = SDL_GetTicks();
}

PUBLIC VIRTUAL void LevelScene::Init() {
	SpriteMapIDs.reserve(0x600);
	SpriteMapIDs.assign(0x600, NULL);

	SpriteBinMapIDs.reserve(0x600);
	SpriteBinMapIDs.assign(0x600, NULL);

	LoadData();
	//App->Print(0, "%d", SaveGame::CurrentEmeralds);

	uint64_t startTime = SDL_GetTicks();
	RestartStage(true, false);
	IApp::Print(-1, "LevelScene \"%s\" took %0.3fs to run.", "Init RestartStage()", (SDL_GetTicks() - startTime) / 1000.0);
	if (TintColor != 0x000000 && SaveGame::CurrentMode != 0)
		for (int i = 0; i < 256; i++)
			for (int j = 0; j < PlayerCount; j++)
				Players[j]->Sprites[0]->SetPalette(i, G->ColorBlendHex(Players[j]->Sprites[0]->GetPalette(i), TintColor, 50));

	switch (ZoneID) {
	case 2:
		if (Act == 2) {
			int X = 0x40C8;
			int Y = 0x7D0;
			int ID = 0x81;
			int SubType = 0;
			int PRIORITY = true;
			int FLIPX = 0;
			int FLIPY = 0;
			ADD_OBJECT();
			obj->Create();
		}
		break;
	case 3:
		if (Act == 1) {
			int X = 0x2F00;
			int Y = 0xE60;
			int ID = 0x81;
			int SubType = 0;
			int PRIORITY = true;
			int FLIPX = 0;
			int FLIPY = 0;
			// ADD_OBJECT();
			// obj->Create();
		}
		else {
			int X = 0x3D00;
			int Y = 0x720;
			int ID = 0x81;
			int SubType = 0;
			int PRIORITY = true;
			int FLIPX = 0;
			int FLIPY = 0;
			ADD_OBJECT();
			obj->Create();
		}
		break;
	case 4:
		if (Act == 1) {
			int X = 0x32C0;
			int Y = 0x20C;
			int ID = 0x81;
			int SubType = 0;
			int PRIORITY = true;
			int FLIPX = 0;
			int FLIPY = 1;
			ADD_OBJECT();
			obj->Create();
		}
		else {
			int X = 0x4940;
			int Y = 0x270;
			int ID = 0x81;
			int SubType = 0;
			int PRIORITY = true;
			int FLIPX = 0;
			int FLIPY = 1;
			ADD_OBJECT();
			obj->Create();
		}
		break;
	case 5:
		if (Act == 1) {
			int X = 0x6540;
			int Y = 0x05A0;
			int ID = 0x81;
			int SubType = 0;
			int PRIORITY = true;
			int FLIPX = 0;
			int FLIPY = 0;
			ADD_OBJECT();
			obj->Create();
		}
		else {
			int X = 0x4590;
			int Y = 0x0680;
			int ID = 0x81;
			int SubType = 0;
			int PRIORITY = true;
			int FLIPX = 0;
			int FLIPY = 0;
			ADD_OBJECT();
			obj->Create();
		}
		break;
	}
}

PUBLIC STATIC int LevelScene::LoadStatic(void* data) {
	LevelScene* self = (LevelScene*)data;
	self->LoadData();
	return 0;
}

PUBLIC void LevelScene::LoadInBackground() {
	SDL_DetachThread(SDL_CreateThread(LevelScene::LoadStatic, "LevelScene::LoadInBackground", this));
}

PUBLIC VIRTUAL void LevelScene::RestartStage(bool doActTransition, bool drawBackground) {
#define CLEANUP(name) if (name) { name->Cleanup(); delete name; name = NULL; }

	if (Sound::SoundBank[0]) {
		App->Audio->ClearMusic();
		App->Audio->PushMusic(Sound::SoundBank[0], true, Sound::Audio->LoopPoint[0]);
	}

	LoadState();

	SaveGame::SetLives(Player->Lives);
	if (ZoneID < 0xF0) SaveGame::SetZone(ZoneID - 1);
	SaveGame::Savefiles[SaveGame::CurrentSaveFile].Shield = (uint8_t)Player->Shield < 5 ? (uint8_t)Player->Shield : 0;
	SaveGame::Savefiles[SaveGame::CurrentSaveFile].BlueRing = 0;
	SaveGame::Flush();

	ObjectsSolid.clear();
	ObjectsSpring.clear();
	ObjectsEnemies.clear();
	ObjectsBreakable.clear();

	DoneSpinning = false;

	StopTimer = false;
	ShowResults = false;
	ResultsTimer = 0;
	TimerTotal = 0;
	TotalToAdd = 0;

	ObjectSolidCount = 0;
	ObjectSpringCount = 0;
	ObjectEnemiesCount = 0;
	ObjectBreakableCount = 0;
	ObjectPathSwitcherCount = 0;

	for (int i = 0; i < Data->layerCount; i++) {
        memcpy(Data->Layers[i].Tiles, Data->Layers[i].TilesBackup, Data->Layers[i].Width * Data->Layers[i].Height * sizeof(short));
    }

	StopTimer = false;

	int pX = PlayerStartX;
	int pY = PlayerStartY;
	if (SavedPalette && SavedPalette[0]) {
		// TileSprite->SetPalette(0, 256, SavedPalette);
	}
	if (SavedPositionX > 0) {
		pX = SavedPositionX;
		pY = SavedPositionY;
	}
	if (SpecialSpawnPositionX > 0) {
		pX = SpecialSpawnPositionX;
		pY = SpecialSpawnPositionY;
		SpecialSpawnPositionX = -1;
	}

	for (int p = 0; p < PlayerCount; p++) {

		Players[p]->EZX = (pX - p * 16);
		Players[p]->EZY = pY;
		Players[p]->DisplayX = Players[p]->X;
		Players[p]->DisplayY = Players[p]->Y;
		Players[p]->Action = ActionType::Normal;

		Players[p]->GroundSpeed = 0;
		Players[p]->XSpeed = 0;
		Players[p]->YSpeed = 0;
		Players[p]->Flip = 1;
		Players[p]->DisplayFlip = 1;

		Players[p]->ControlLocked = false;
		Players[p]->ObjectControlled = 0x00;

		if (ResetTimer)
			Players[p]->Rings = 0;

		Players[p]->Create();
		Players[p]->LateUpdate();
	}

	if (ResetTimer)
		Timer = 0;

	if (!doActTransition) {
		RoutineNumber = 0x00;
		LevelTriggerFlag = 0x00;
	}

	std::memset(Signal, 0, sizeof(Signal));
	std::memset(&PauseAnim[0], 0, 8 * sizeof(int));
	LevelCardTimer = 0.0;

	// Set Camera on player
	CameraX = (Player->EZX + Player->CameraX) - App->WIDTH / 2;
	if (ManiaLevel) {
		CameraY = (Player->EZY + Player->CameraY - 4) - App->HEIGHT / 2;
	} else {
		CameraY = (Player->EZY + Player->CameraY + 8) - App->HEIGHT / 2;
	}

	CameraMinX = 0;
	CameraMinY = 0;
	CameraMaxX = 0x7FFF;
	CameraMaxY = 0x7FFF;
	CameraDeltaX = 0;
	CameraDeltaY = 0;
	CameraAutoScrollX = 0;
	CameraAutoScrollY = 0;

	HandleCamera();

	ObjectCount = Objects.size() - ObjectNewCount;

	for (int i = ObjectCount; i < ObjectCount + ObjectNewCount; i++) {
		Objects.at(i)->OnDestroy();
		delete Objects.at(i);
		Objects.at(i) = NULL;
	}
	Objects.erase(Objects.begin() + ObjectCount, Objects.begin() + (ObjectCount + ObjectNewCount));
	Objects.shrink_to_fit();


	ObjectNewCount = 0;

	for (int i = 0; i < ObjectCount; i++) {
		Object *object = Objects.at(i);
		if (object != NULL) {
			object->Create();
			object->DrawCollisions = App->viewObjectCollision;
		}
	}

	for (int o = 0; o < RingPropCount; o++) {
		RingProps.at(o).ID = 0xFF;
	}

	for (size_t i = 0; i < TempObjects.size(); i++) {
        if (TempObjects.at(i) != NULL) {
            delete TempObjects.at(i);
            TempObjects.at(i) = NULL;
        }
	}
	TempObjects.clear();

	for (size_t i = 0; i < TempObjectTiles.size(); i++) {
        if (TempObjectTiles.at(i) != NULL) {
            delete TempObjectTiles.at(i);
            TempObjectTiles.at(i) = NULL;
        }
	}
    TempObjectTiles.clear();

	UpdateDiscord();
}

PUBLIC VIRTUAL void LevelScene::PatchLayer(int layer) {
	if (ZoneID == 1 && Act == 2 && layer == 1) {
		int Width = Data->Layers[layer].Width;
		for (int xx = 0x4; xx < 0xB; xx++) {
			for (int yy = 0x23; yy < 0x28; yy++) {
				Data->Layers[layer].Tiles[xx + Width * yy] = 0x5B;
			}
		}
	}
}

PUBLIC VIRTUAL int LevelScene::FindLayer(std::string name) {
	if (Data)
	{
		for (int i = 0; i < Data->layerCount; i++)
		{
			if (Data->Layers[i].Name == name)
			{
				//Success!
				return i;
			}
		}
	}
	//Fail
	return 0;
}

PUBLIC VIRTUAL void LevelScene::UpdateDiscord() {
	char imgkey[15];
	char levelname[50];
	sprintf(imgkey, "%d", ZoneID);
	sprintf(levelname, "%s%s%d", LevelNameDiscord, " Act ", VisualAct);


	char* ModeName;
	if (SaveGame::CurrentMode == 0) {
		ModeName = "Classic Mode";
	} else if (SaveGame::CurrentMode == 1) {
		ModeName = "Mixed Mode";
	} else if (SaveGame::CurrentMode == 2) {
		ModeName = "Mixed Mode";
	}

	Discord_UpdatePresence(ModeName, levelname, imgkey, true);
}


PUBLIC bool LevelScene::CollisionAt(int probeX, int probeY) {
	return CollisionAt(probeX, probeY, NULL, 0, NULL, NULL, -1);
}

PUBLIC bool LevelScene::CollisionAt(int probeX, int probeY, Object* IgnoreObject) {
	return CollisionAt(probeX, probeY, NULL, 0, NULL, IgnoreObject, -1);
}

PUBLIC bool LevelScene::CollisionAt(int probeX, int probeY, int* angle) {
	return CollisionAt(probeX, probeY, angle, 0, NULL, NULL, -1);
}

PUBLIC bool LevelScene::CollisionAt(int probeX, int probeY, int* angle, int anglemode) {
	return CollisionAt(probeX, probeY, angle, anglemode, NULL, NULL, -1);
}

PUBLIC bool LevelScene::CollisionAtClimbable(int probeX, int probeY, int* angle, int anglemode, IPlayer* player) {
	CollisionCheckForClimbable = true;
	bool gh = CollisionAt(probeX, probeY, angle, anglemode, player);
	CollisionCheckForClimbable = false;
	return gh;
}

PUBLIC bool LevelScene::CollisionAt(int probeX, int probeY, int* angle, int anglemode, IPlayer* player) {
	return CollisionAt(probeX, probeY, angle, anglemode, player, NULL,-1);
}

PUBLIC VIRTUAL bool LevelScene::CollisionAt(int probeX, int probeY, int* angle, int anglemode, IPlayer* player, Object* IgnoreObject, int ObjID) {
	if (!Data) return false;

	int tileX = probeX / 16;
	int tileY = probeY / 16;

	// Layer Flags:
	// 0x1: Collidable
	// 0x2: Don't Repeat X
	// 0x3: Don't Repeat Y

	int probeXOG = probeX;
	int probeYOG = probeY;

	for (int l = 0; l < Data->layerCount; l++) {
		if (!(Data->Layers[l].Flags & 1)) continue;

		probeX = probeXOG;
		probeY = probeYOG;

		probeX -= Data->Layers[l].OffsetX;
		probeY -= Data->Layers[l].OffsetY;

		if (probeX < 0)
			continue;
		if (probeX >= Data->Layers[l].Width * 16)
			continue;
		if (Data->Layers[l].IsScrollingVertical) {
			int hh = Data->Layers[l].Height * 16;
			probeY = ((probeY % hh) + hh) % hh;
		}
		else {
			if (probeY < 0)
				continue;
			if (probeY >= Data->Layers[l].Height * 16)
				continue;
		}

		tileX = probeX >> 4;
		tileY = probeY >> 4;

		int tileID = Data->Layers[l].Tiles[tileX + tileY * Data->Layers[l].Width];
		if ((tileID & 0x3FF) != 0x3FF && (tileID & 0x3FF) != 0x0) {
			bool tileData1 = ((tileID >> 15) & 1) == 1;
			bool tileData2 = ((tileID >> 14) & 1) == 1;
			bool tileData3 = ((tileID >> 13) & 1) == 1;
			bool tileData4 = ((tileID >> 12) & 1) == 1;

			bool tileDatas[4] = { tileData4, tileData3, tileData2, tileData1 };

			bool flipX = ((tileID >> 10) & 1) == 1;
			bool flipY = ((tileID >> 11) & 1) == 1;

			tileID = tileID & 0x3FF;

			///*
			if (player) {
				if (!tileDatas[player->Layer * 2] && !tileDatas[player->Layer * 2 + 1])
					continue;

				if (player->AngleMode != 0 && !tileDatas[player->Layer * 2] && tileDatas[player->Layer * 2 + 1])
					continue;
			}
			else {
				if (!tileDatas[Player->Layer * 2] && !tileDatas[Player->Layer * 2 + 1])
					continue;
			}

			// TODO: When exporting levels check to make sure we don't double jumpthrough blocks

			//*/

			for (int c = 0; c < 16; c++) {
				int eex = c;
				if (flipX)
					eex = 15 - c;

				int tX = tileX * 16;
				int tY = tileY * 16;

				int h1 = Data->tiles1[tileID].Collision[c];
				int h2 = Data->tiles2[tileID].Collision[c];

				if (BlankTile == 0x3FF && (Data->tiles1[tileID].IsCeiling || Data->tiles2[tileID].IsCeiling)) {
					h1 = 15 - h1;
					h2 = 15 - h2;
				}

				int which = 0;
				if (anglemode == 0)
					which = 0 + flipY * 3;
				if (anglemode == 2)
					which = 3 - flipY * 3;

				if (anglemode == 1) {
					which = 1 + flipX;
				}
				if (anglemode == 3)
					which = 2 - flipX;

				if (player) {
					if (Data->tiles1[tileID].HasCollision[c] && player->Layer == 0) {
						if ((Data->tiles1[tileID].IsCeiling ^ flipY)) {
							if (!tileDatas[player->Layer * 2 + 1] && (anglemode != 0 || player->EZY < tY))
								continue;

							if (probeX == tX + eex &&
								probeY >= tY &&
								probeY < tY + 16 - h1) {
								if (angle != NULL) {
									int tempAngle = Data->tiles1[tileID].Config[which];
									// if (which == 1 && tempAngle >= 0xC0 && tempAngle > 0xF0) tempAngle = 0xC0;
									//tempAngle = tempAngle * -45.f / 32;
									if (tempAngle != 0) {
										if (flipX) tempAngle = 256 - tempAngle;
										if (flipY) tempAngle = 128 - tempAngle;
									}

									*angle = tempAngle & 0xFF; //(int)wrapAngle(tempAngle);
								}

								player->LastObject = NULL;
								return true;
							}
						}
						else {
							if (!tileDatas[player->Layer * 2 + 1] && (anglemode != 0 || player->EZY > tY))
								continue;

							if (probeX == tX + eex &&
								probeY >= tY + h1 &&
								probeY < tY + 16) {
								if (angle != NULL) {
									int tempAngle = Data->tiles1[tileID].Config[which];
									// if (which == 1 && tempAngle >= 0xC0 && tempAngle > 0xF0) tempAngle = 0xC0;
									//tempAngle = tempAngle * -45.f / 32;
									if (tempAngle != 0) {
										if (flipX) tempAngle = 256 - tempAngle;
										if (flipY) tempAngle = 128 - tempAngle;
									}

									*angle = tempAngle & 0xFF; //(int)wrapAngle(tempAngle);
								}

								player->LastObject = NULL;
								return true;
							}
						}
					}
					if (Data->tiles2[tileID].HasCollision[c] && player->Layer == 1) {
						if (Data->tiles2[tileID].IsCeiling ^ flipY) {
							if (!tileDatas[player->Layer * 2 + 1] && (anglemode != 0 || player->EZY < tY))
								continue;

							if (probeX == tX + eex &&
								probeY >= tY &&
								probeY < tY + 16 - h2) {
								if (angle != NULL) {
									int tempAngle = Data->tiles2[tileID].Config[which];
									// if (which == 1 && tempAngle >= 0xC0 && tempAngle > 0xF0) tempAngle = 0xC0;
									//tempAngle = tempAngle * -45.f / 32;
									if (tempAngle != 0) {
										if (flipX) tempAngle = 256 - tempAngle;
										if (flipY) tempAngle = 128 - tempAngle;
									}

									*angle = tempAngle & 0xFF; //(int)wrapAngle(tempAngle);
								}

								player->LastObject = NULL;
								return true;
							}
						}
						else {
							if (!tileDatas[player->Layer * 2 + 1] && (anglemode != 0 || player->EZY > tY))
								continue;

							if (probeX == tX + eex &&
								probeY >= tY + h2 &&
								probeY < tY + 16) {
								if (angle != NULL) {
									int tempAngle = Data->tiles2[tileID].Config[which];
									// if (which == 1 && tempAngle >= 0xC0 && tempAngle > 0xF0) tempAngle = 0xC0;
									//tempAngle = tempAngle * -45.f / 32;
									if (tempAngle != 0) {
										if (flipX) tempAngle = 256 - tempAngle;
										if (flipY) tempAngle = 128 - tempAngle;
									}

									*angle = tempAngle & 0xFF; //(int)wrapAngle(tempAngle);
								}

								player->LastObject = NULL;
								return true;
							}
						}
					}
				}
				else {
					if (Data->tiles1[tileID].HasCollision[c]) {
						if ((Data->tiles1[tileID].IsCeiling ^ flipY)) {
							if (probeX == tX + eex &&
								probeY >= tY &&
								probeY < tY + 16 - h1) {
								if (angle != NULL) {
									int tempAngle = Data->tiles1[tileID].Config[which];
									// if (which == 1 && tempAngle >= 0xC0 && tempAngle > 0xF0) tempAngle = 0xC0;
									if (tempAngle != 0) {
										if (flipX) tempAngle = 256 - tempAngle;
										if (flipY) tempAngle = 128 - tempAngle;
									}
									*angle = tempAngle & 0xFF;
								}
								return true;
							}
						}
						else {
							if (probeX == tX + eex &&
								probeY >= tY + h1 &&
								probeY < tY + 16) {
								if (angle != NULL) {
									int tempAngle = Data->tiles1[tileID].Config[which];
									// if (which == 1 && tempAngle >= 0xC0 && tempAngle > 0xF0) tempAngle = 0xC0;
									if (tempAngle != 0) {
										if (flipX) tempAngle = 256 - tempAngle;
										if (flipY) tempAngle = 128 - tempAngle;
									}
									*angle = tempAngle & 0xFF;
								}
								return true;
							}
						}
					}
					if (Data->tiles2[tileID].HasCollision[c]) {
						if (Data->tiles2[tileID].IsCeiling ^ flipY) {
							if (probeX == tX + eex &&
								probeY >= tY &&
								probeY < tY + 16 - h2) {
								if (angle != NULL) {
									int tempAngle = Data->tiles2[tileID].Config[which];
									// if (which == 1 && tempAngle >= 0xC0 && tempAngle > 0xF0) tempAngle = 0xC0;
									if (tempAngle != 0) {
										if (flipX) tempAngle = 256 - tempAngle;
										if (flipY) tempAngle = 128 - tempAngle;
									}
									*angle = tempAngle & 0xFF;
								}
								return true;
							}
						}
						else {
							if (probeX == tX + eex &&
								probeY >= tY + h2 &&
								probeY < tY + 16) {
								if (angle != NULL) {
									int tempAngle = Data->tiles2[tileID].Config[which];
									// if (which == 1 && tempAngle >= 0xC0 && tempAngle > 0xF0) tempAngle = 0xC0;

									if (tempAngle != 0) {
										if (flipX) tempAngle = 256 - tempAngle;
										if (flipY) tempAngle = 128 - tempAngle;
									}
									*angle = tempAngle & 0xFF;
								}
								return true;
							}
						}
					}
				}
			}
		}
	}
	for (unsigned int o = 0; o < (unsigned int)ObjectSolidCount; o++) {
		Object* obj = ObjectsSolid[o];
		if (!obj) continue;
		if (!obj->Active) continue;
		if (!obj->OnScreen) continue;

		if (CollisionCheckForClimbable) continue;

		//TO-DO: make this work with the new system ok bye
		if (ObjID != -1)
		{
			if (obj->ID != ObjID) continue;
		}

		if (obj->SolidCustomized) {
			if (player) {
				if (obj->CustomSolidityCheck(probeX, probeY, player->PlayerID, anglemode == 0)) {
					if (angle)
						*angle = 0;
					player->LastObject = obj;
					return true;
				}
			}
		} else {
			bool playerCheck = true;
			if (player)
				playerCheck = player->YSpeed >= 0 && player->EZY < obj->Y - obj->H / 2;

			if (obj != IgnoreObject && (obj->Solid || (obj->SolidTop && anglemode == 0 && playerCheck))) {
				int obj_X = obj->X;
				int obj_Y = obj->Y;
				int obj_W = obj->W / 2;
				int obj_H = obj->H / 2;
				if (probeX >= obj_X - obj_W &&
					probeY >= obj_Y - obj_H &&
					probeX < obj_X + obj_W &&
					probeY < obj_Y + obj_H) {
					if (angle)
						*angle = 0;

					if (player)
						player->LastObject = obj;

					return true;
				}
			}
		}
	}
	return false;
}

PUBLIC void LevelScene::AddActiveRing(int x, int y, int xs, int ys, int mag) {
	Ring* ring = (Ring*)GetNewObjectFromID(0);
	ring->Create();
	ring->X = x;
	ring->Y = y;
	ring->MyX = x << 8;
	ring->MyY = y << 8;
	ring->G = G;
	ring->App = App;
	ring->XSpeed = xs;
	ring->YSpeed = ys;
	ring->Scene = this;
	ring->Active = true;
	ring->Priority = true;
	ring->MagnetizedTo = mag;
	ring->DrawCollisions = App->viewObjectCollision;
	Objects.push_back(ring);
	ObjectCount++;
	ObjectNewCount++;
}

PUBLIC Explosion* LevelScene::AddExplosion(int animation, bool flip, int x, int y) {
	return AddExplosion(ExplosionSprite, animation, flip, x, y, 0);
}

PUBLIC Explosion* LevelScene::AddExplosion(int animation, bool flip, int x, int y, int vl) {
	return AddExplosion(ExplosionSprite, animation, flip, x, y, vl);
}

PUBLIC Explosion* LevelScene::AddExplosion(ISprite* sprite, int animation, bool flip, int x, int y) {
	return AddExplosion(sprite, animation, flip, x, y, 0);
}

PUBLIC Explosion* LevelScene::AddExplosion(ISprite* sprite, int animation, bool flip, int x, int y, int vl) {
	Explosion* dropdashdust;
	dropdashdust = new Explosion();
	dropdashdust->G = G;
	dropdashdust->App = App;
	dropdashdust->CurrentAnimation = animation;
	dropdashdust->FlipX = flip;
	dropdashdust->Active = true;
	dropdashdust->Sprite = sprite;
	dropdashdust->VisualLayer = vl;
	dropdashdust->X = x;
	dropdashdust->Y = y;
	TempObjects.push_back(dropdashdust);

	return dropdashdust;
}

PUBLIC void LevelScene::AddScoreGhost(int frame, int x, int y) {
	ScoreGhost* dropdashdust;
	dropdashdust = new ScoreGhost();
	dropdashdust->G = G;
	dropdashdust->App = App;
	dropdashdust->Scene = this;
	dropdashdust->CurrentAnimation = 14;
	dropdashdust->CurrentFrame = frame;
	dropdashdust->Active = true;
	dropdashdust->Sprite = ObjectsSprite;
	dropdashdust->X = x;
	dropdashdust->Y = y;
	dropdashdust->SubY = y - 32;
	TempObjects.push_back(dropdashdust);
}

PUBLIC void LevelScene::AddFallingTile(int til, int x, int y, int offX, int offY, bool flipX, bool flipY, int hold) {
	FallingTile* tile = new FallingTile();
	tile->G = G;
	tile->App = App;
	tile->Scene = this;
	tile->Tile = til;
	tile->Hold = hold;
	tile->FlipX = flipX;
	tile->FlipY = flipY;
	tile->Active = true;
	tile->X = x + offX;
	tile->Y = y + offY;
	TempObjectTiles.push_back(tile);
}

PUBLIC void LevelScene::AddFallingTile(int til, int x, int y, int offX, int offY, bool flipX, bool flipY, int xspeed, int yspeed) {
	FallingTile* tile = new FallingTile();
	tile->G = G;
	tile->App = App;
	tile->Scene = this;
	tile->Tile = til;
	tile->Hold = 0;
	tile->grv = 0x70;
	tile->FlipX = flipX;
	tile->FlipY = flipY;
	tile->Active = true;
	tile->X = x + offX;
	tile->Y = y + offY;
	tile->XSpeed = xspeed;
	tile->YSpeed = yspeed;
	TempObjectTiles.push_back(tile);
}

PUBLIC void LevelScene::AddMovingSprite(ISprite* sprite, int x, int y, int left, int top, int w, int h, int offX, int offY, bool flipX, bool flipY, int xspeed, int yspeed, int grv, int hold) {
	MovingSprite* tile = new MovingSprite();
	tile->G = G;
	tile->App = App;
	tile->Scene = this;
	tile->Sprite = sprite;
	tile->Hold = hold;
	tile->FlipX = flipX;
	tile->FlipY = flipY;
	tile->Active = true;
	tile->Gravity = grv;
	tile->Left = left;
	tile->Top = top;
	tile->Width = w;
	tile->Height = h;
	tile->SubX = (x) << 16;
	tile->SubY = (y) << 16;
	tile->OffX = offX;
	tile->OffY = offY;
	tile->XSpeed = xspeed;
	tile->YSpeed = yspeed;
	if (LastObjectUpdated) {
		tile->VisualLayer = LastObjectUpdated->VisualLayer;
    }
	TempObjectTiles.push_back(tile);
}

PUBLIC void LevelScene::AddMovingSprite(ISprite* sprite, int x, int y, int left, int top, int w, int h, int offX, int offY, bool flipX, bool flipY, int xspeed, int yspeed, int grv) {
	AddMovingSprite(sprite, x, y, left, top, w, h, offX, offY, flipX, flipY, xspeed, yspeed, grv, 0);
}

PUBLIC void LevelScene::AddMovingSprite(ISprite* sprite, int x, int y, int animation, int frame, bool flipX, bool flipY, int xspeed, int yspeed, int grv) {
	AddMovingSprite(sprite, x, y, animation, frame, flipX, flipY, xspeed, yspeed, grv, -1, 0);
}

PUBLIC void LevelScene::AddMovingSprite(ISprite* sprite, int x, int y, int animation, int frame, bool flipX, bool flipY, int xspeed, int yspeed, int grv, int life, int hold) {
	ISprite::AnimFrame animframe = sprite->Animations[animation].Frames[frame];

	int animState = G->CheckAnimation(sprite, animation, frame);
	if (animState == 1) animation = 0;
	if (animState == 2) frame = 0;
	if (animState == 3) {
		animation = 0; frame = 0;
	}

	MovingSprite* tile = new MovingSprite();
	tile->G = G;
	tile->App = App;
	tile->Scene = this;
	tile->Sprite = sprite;
	tile->Hold = hold;
	tile->FlipX = flipX;
	tile->FlipY = flipY;
	tile->Active = true;
	tile->Gravity = grv;
	tile->CurrentAnimation = animation;
	tile->Frame = frame;
	tile->LifeSpan = life;
	tile->Left = -1;
	tile->Top = animframe.Y;
	tile->Width = animframe.W;
	tile->Height = animframe.H;
	tile->SubX = (x) << 16;
	tile->SubY = (y) << 16;
	tile->XSpeed = xspeed;
	tile->YSpeed = yspeed;
	if (LastObjectUpdated) {
		tile->VisualLayer = LastObjectUpdated->VisualLayer;
    }
	TempObjectTiles.push_back(tile);
}

PUBLIC void LevelScene::AddAnimal(int x, int y, bool flipX, bool flipY, int xspeed, int yspeed, bool escaping) {
	int animalZones[14 * 2] = {
		0, 5,
		2, 6,
		0, 5,
		2, 0,
		1, 0,
		3, 6,
		0, 5,
		1, 5,
		2, 5,
		0, 5,
		2, 5,
		1, 5,
		1, 5,
		0, 5,
	};
	int animalSpeeds[7 * 2] = {
		-0x440, -0x400,
		-0x300, -0x400,
		-0x180, -0x300,
		-0x140, -0x180,
		-0x1C0, -0x300,
		-0x200, -0x300,
		-0x140, -0x380,
	};

	int animalType = animalZones[(ZoneID - 1) * 2 + (Frame & 1)];

	Animal* flicky = new Animal();
	flicky->G = G;
	flicky->App = App;
	flicky->Scene = this;
	flicky->Sprite = AnimalsSprite;
	flicky->FlipX = true;
	flicky->FlipY = flipY;
	flicky->Active = true;

	flicky->CurrentAnimation = animalType * 2;
	flicky->CurrentFrame = 0 << 8;

	flicky->SubX = (x) << 16;
	flicky->SubY = (y) << 16;
	flicky->XSpeed = animalSpeeds[animalType * 2 + 0];
	flicky->YSpeed = -0x400;
	flicky->JumpSpeed = animalSpeeds[animalType * 2 + 1];
	TempObjects.push_back(flicky);
}

PUBLIC Object* LevelScene::AddNewObject(int ID, int SubType, int X, int Y, bool FLIPX, bool FLIPY) {
	ObjectNewCount++;

	Object* obj = GetNewObjectFromID(ID);
	if (obj) {
		obj->G = G;
		obj->App = App;
		obj->Scene = this;
		obj->InitialX = X;
		obj->InitialY = Y;
		obj->FlipX = FLIPX == 1;
		obj->FlipY = FLIPY == 1;
		obj->ID = ID;
        if (obj->BinIndex == 0xFFFFFFFF) {
            while (!SpriteMapIDs.at(ID)) {
                ID--;
            }

            obj->Sprite = SpriteMapIDs.at(ID);
        } else {
            obj->Sprite = SpriteBinMapIDs.at(obj->BinIndex);
        }

		obj->SubType = SubType;
		obj->Create();
		obj->DrawCollisions = App->viewObjectCollision;
		ObjectCount++;
		Objects.push_back(obj);
	}
	return obj;
}

PUBLIC Object* LevelScene::AddNewObject(int ID, int X, int Y, bool FLIPX, bool FLIPY) {
	ObjectNewCount++;

	Object* obj = GetNewObjectFromID(ID);
	if (obj) {
		obj->G = G;
		obj->App = App;
		obj->Scene = this;
		obj->InitialX = X;
		obj->InitialY = Y;
		obj->FlipX = FLIPX == 1;
		obj->FlipY = FLIPY == 1;
		obj->ID = ID;
		if (obj->BinIndex == 0xFFFFFFFF) {
			while (!SpriteMapIDs.at(ID)) {
				ID--;
			}

			obj->Sprite = SpriteMapIDs.at(ID);
		}
		else {
			obj->Sprite = SpriteBinMapIDs.at(obj->BinIndex);
		}

		obj->Create();
		obj->DrawCollisions = App->viewObjectCollision;
		ObjectCount++;
		Objects.push_back(obj);
	}
	return obj;
}

PUBLIC Object* LevelScene::AddNewObject(int ID, int X, int Y) {
	ObjectNewCount++;

	Object* obj = GetNewObjectFromID(ID);
	if (obj) {
		obj->G = G;
		obj->App = App;
		obj->Scene = this;
		obj->InitialX = X;
		obj->InitialY = Y;
		obj->FlipX = false;
		obj->FlipY = false;
		obj->ID = ID;
		if (obj->BinIndex == 0xFFFFFFFF) {
			while (!SpriteMapIDs.at(ID)) {
				ID--;
			}

			obj->Sprite = SpriteMapIDs.at(ID);
		}
		else {
			obj->Sprite = SpriteBinMapIDs.at(obj->BinIndex);
		}

		obj->Create();
		obj->DrawCollisions = App->viewObjectCollision;
		ObjectCount++;
		Objects.push_back(obj);
	}
	return obj;
}

PUBLIC Object* LevelScene::AddNewObject(char* ObjName, int X, int Y) {
	ObjectNewCount++;

	MD5 md5 = MD5(ObjName);

	std::string hash = md5.getdigest();

	char hashdata[16];

	for (int i = 0; i < 16; i++)
	{
		hashdata[i] = hash[i];
	}

	uint32_t objHash = crc32((char*)hashdata, 16);

	Object* obj = GetNewObjectFromCRC32(objHash);
	if (obj) {
		obj->G = G;
		obj->App = App;
		obj->Scene = this;
		obj->InitialX = X;
		obj->InitialY = Y;

		obj->Filter = obj->GetAttribute("Filter")->ValUint8;
		obj->SubType = obj->GetAttribute("Subtype")->ValUint8;
		obj->FlipX = obj->GetAttribute("FlipX")->ValBool;
		obj->FlipY = obj->GetAttribute("FlipY")->ValBool;
		obj->Create();
		obj->DrawCollisions = App->viewObjectCollision;
		ObjectCount++;
		Objects.push_back(obj);
	}
	return obj;
}

PUBLIC void LevelScene::AddNewDebugObjectID(int16_t ID) {
	DebugObjectIDList[DebugObjectIDCount++] = ID;
}

PUBLIC VIRTUAL void LevelScene::SpawnPlayer(int ID, bool Sidekick, bool Main, int X, int Y) {
	if (Main)
	{
		Player = new IPlayer();
		Player->G = G;
		Player->App = App;
		Player->Scene = this;
		Player->Character = (CharacterType)(SaveGame::CurrentCharacterFlag & 0xF);
		Player->PlayerID = 0;
		Player->Sidekick = Sidekick;
		Player->Shield = (ShieldType)(SaveGame::Savefiles[SaveGame::CurrentSaveFile].Shield < 5 ? (uint8_t)SaveGame::Savefiles[SaveGame::CurrentSaveFile].Shield : 0);
		Player->Thremixed = SaveGame::CurrentMode > 0;
		Player->Lives = SaveGame::GetLives();
		Player->X = X;
		Player->Y = Y;
		Player->ControlLocked = false;
		Player->ObjectControlled = 0x00;
		Player->Create();

		Players[ID] = Player;
	}
	else
	{
		Players[ID] = new IPlayer();
		Players[ID]->G = G;
		Players[ID]->App = App;
		Players[ID]->Scene = this;
		Players[ID]->Sidekick = Sidekick;
		Players[ID]->Character = (CharacterType)SaveGame::CurrentPartnerFlag;
		Players[ID]->PlayerID = 1;
		Players[ID]->Thremixed = SaveGame::CurrentMode > 0;
		Players[ID]->X = X;
		Players[ID]->Y = Y;
		Players[ID]->ControlLocked = false;
		Players[ID]->ObjectControlled = 0x00;
		Players[ID]->Create();

		LevelScene::PlayerCount = ID;
	}
}

PUBLIC VIRTUAL void LevelScene::EarlyUpdate() {
}

PUBLIC VIRTUAL void LevelScene::Subupdate() {
	//Probably just for bent lettuce?
	/*if (ManiaLevel) {
		int8_t DeformDelta[64] = {
			0,    0,    1,    1,    0,    0,    0,    0,    1,    0,    0,    0,    0,    1,    0,    0,
			0,    0,    0,    0,    0,    0,    0,    0,    0,    1,    0,    0,    1,    1,    0,    0,
			0,    0,    1,    1,    0,    0,    0,    0,    1,    0,    0,    0,    0,    1,    0,    0,
			0,    0,    0,    0,    0,    0,    0,    0,    0,    1,    0,    0,    1,    1,    0,    0
		};
		for (int i = 0; i < App->HEIGHT; i++) {
			G->Deform[i] = DeformDelta[(i + (Frame >> 1) + CameraY) & 0x3F] - 1;
		}
	}*/
}

PUBLIC VIRTUAL void LevelScene::DoResults() {
	ShowResults = true;
	ResultsTimer = 0;
	if (Timer < 60 * 60)
		TimerTotal = 50000;
	else if (Timer < 90 * 60)
		TimerTotal = 10000;
	else if (Timer < 120 * 60)
		TimerTotal = 5000;
	else if (Timer < 150 * 60)
		TimerTotal = 4000;
	else if (Timer < 180 * 60)
		TimerTotal = 3000;
	else if (Timer < 210 * 60)
		TimerTotal = 1000;
	else if (Timer < 599 * 60)
		TimerTotal = 100;
	else
		TimerTotal = 100000;
	TotalToAdd = 0;
	Player->DoVictory();
	App->Audio->ClearMusic();
	App->Audio->PushMusic(Sound::SoundBank[0xFC], false, 0);
}

PUBLIC VIRTUAL void LevelScene::FinishResults() {
	GoToNextAct();
}

PUBLIC VIRTUAL void LevelScene::GoToNextAct() {
}

int pauseAnimTimer = 60;
int PauseMusicFade = 0;

PUBLIC VIRTUAL void LevelScene::TransferCommonLevelData(LevelScene* NextAct) {
	NextAct->GiantRingModel = GiantRingModel;

	NextAct->GlobalDisplaySprite = GlobalDisplaySprite;
	NextAct->MobileButtonsSprite = MobileButtonsSprite;
	NextAct->EditorSprite = EditorSprite;
	NextAct->ItemsSprite = ItemsSprite;
	NextAct->AnimalsSprite = AnimalsSprite;
	NextAct->ObjectsSprite = ObjectsSprite;
	NextAct->Objects2Sprite = Objects2Sprite;
	NextAct->Objects3Sprite = Objects3Sprite;
	NextAct->RobotnikSprite = RobotnikSprite;
	NextAct->ExplosionSprite = ExplosionSprite;
	NextAct->WaterSprite = WaterSprite;
	for (int i = 0; i < 5; i++) {
		NextAct->KnuxSprite[i] = KnuxSprite[i];
	}

	NextAct->Player = Player;
	for (int p = 0; p < PlayerCount; p++) {
		NextAct->Players[p] = Players[p];
		NextAct->Players[p]->Scene = NextAct;
	}
	NextAct->PlayerCount = PlayerCount;
	NextAct->Score = Score;

	// Set all these to NULL so they do not get cleaned up
	PlayerCount = 0;
	KnuxSprite[0] = NULL;
	KnuxSprite[1] = NULL;
	KnuxSprite[2] = NULL;
	KnuxSprite[3] = NULL;
	KnuxSprite[4] = NULL;
	PauseSprite = NULL;
	GlobalDisplaySprite = NULL;
	GlobalDisplaySpriteS3K = NULL;
	MobileButtonsSprite = NULL;
	EditorSprite = NULL;
	ItemsSprite = NULL;
	AnimalsSprite = NULL;
	ObjectsSprite = NULL;
	Objects2Sprite = NULL;
	Objects3Sprite = NULL;
	RobotnikSprite = NULL;
	ExplosionSprite = NULL;
	WaterSprite = NULL;
	GiantRingModel = NULL;

	// #PauseSprite#
	// #GlobalDisplaySprite#
	// #MobileButtonsSprite#
	// #ItemsSprite#
	// #AnimalsSprite#
	// #ObjectsSprite#
	// #Objects2Sprite#
	// #Objects3Sprite#
	// #RobotnikSprite#
	// #ExplosionSprite#
	// #WaterSprite#
}

PUBLIC VIRTUAL void LevelScene::DoCustomFadeAction() {
}

#include <time.h>

bool activated = false;
uint64_t playerUpdateCount[8];
float    playerUpdateTimers[8];
uint64_t playerLateUpdateCount[8];
float    playerLateUpdateTimers[8];

PUBLIC void LevelScene::OnEvent(Uint32 event) {
	if (event != SDL_APP_WILLENTERBACKGROUND) return;

	if (!Paused && !PauseFinished) {
		LevelCardTimer = 6.0;

		PauseFinished = true;
		Paused = true;
		pauseAnimTimer = 60;
		std::memset(&PauseAnim[0], 0, 8 * sizeof(int));

		PauseSelectedMenuItem = 0;

		if (MusicVolume == -1)
			App->Audio->AudioPauseAll();
		Sound::Play(Sound::SFX_MENUACCEPT);
	}
}

PUBLIC void LevelScene::Update() {
	if (MusicVolume != -1)
		if (App->Audio->MusicStack.size() != 0)
				App->Audio->MusicStack[0]->Volume = MusicVolume - (PauseMusicFade * 3); //you're not welcome rdc fuck you
	if (!Paused) {
		if (MusicVolume == -1 && App->Audio->Paused)
			App->Audio->AudioUnpauseAll();
		pauseAnimTimer += 12;
		if (pauseAnimTimer > 100)
			pauseAnimTimer = 100;
		PauseMusicFade -= 4;
		if (PauseMusicFade < 0)
			PauseMusicFade = 0;
	}
	else
		if (MusicVolume == -1 && !App->Audio->Paused)
			App->Audio->AudioPauseAll();
	// Pause function
	if (FadeAction == 0 && !ShowResults) {
		// Toggle pause
		if (App->Input->GetControllerInput(0)[IInput::I_PAUSE_PRESSED] && LevelCardTimer >= 4.0) {
			if (!Paused && !PauseFinished) {
				PauseFinished = true;
				Paused = true;
				pauseAnimTimer = 60;
				std::memset(&PauseAnim[0], 0, 8 * sizeof(int));

				PauseSelectedMenuItem = 0;

				if (MusicVolume == -1)
					App->Audio->AudioPauseAll();
				Sound::Play(Sound::SFX_MENUACCEPT);
			}
			else {
				Paused = false;
				if (MusicVolume == -1)
					App->Audio->AudioUnpauseAll();
				//Sound::Play(Sound::SFX_MENUACCEPT);
			}
		}

		if (App->Input->GetControllerInput(0)[IInput::I_EXTRA_PRESSED] && Player) {
			if (maxLayer == 1) {
				Player->XSpeed = 0;
				Player->YSpeed = 0;
				Player->GroundSpeed = 0;
				Player->ObjectControlled = 0;
				Player->DoCollision = 0;
				Player->Action = ActionType::Normal;
			}
			else if (maxLayer == 0) {
				Player->DoCollision = 1;
				if (Player->DebugObjectIndex > -1) {
					Player->DebugObjectIndex -= 1;
				}
				if (Player->DebugObject != NULL && Player->DebugObject->isHeldDebugObject) {
					Player->DebugObject->Active = false;
					Player->DebugObject = NULL;
				}
				if (Player->Hidden) {
					Player->Hidden = false;
				}
			}
			maxLayer = 1 - maxLayer;
		}
	}

	if (!activated) {
		std::memset(playerUpdateCount, 0, sizeof(playerUpdateCount));
		std::memset(playerUpdateTimers, 0, sizeof(playerUpdateTimers));
		std::memset(playerLateUpdateCount, 0, sizeof(playerLateUpdateCount));
		std::memset(playerLateUpdateTimers, 0, sizeof(playerLateUpdateTimers));
		activated = true;
	}

	// Unpaused
	if (!PauseFinished) {
		Frame++;

		// Animate animated tiles
		if (Data) {
			for (int o = 0; o < Data->animatedTilesCount; o++) {
				int framecount = Data->animatedTileDurations[o][0];
				int max = Data->animatedTileDurations[o][framecount + 1];

				int f = Frame % max;
				int sum = 0;
				for (int g = 1; g < framecount + 1; g++) {
					sum += Data->animatedTileDurations[o][g];

					if (f < sum) {
						Data->animatedTileFrames[o] = g - 1;
						break;
					}
				}
			}
		}

		if (LevelCardTimer >= 0.25)
			ControlsVisible = true;

		if (HUDVisible) {
			if (HUDAnim > 0x000)
				HUDAnim -= 0x10;
		}
		else {
			if (HUDAnim < 0x100)
				HUDAnim += 0x10;
		}

		if (ControlsVisible) {
			if (ControlsAnim > 0x000)
				ControlsAnim -= 0x10;
		}
		else {
			if (ControlsAnim < 0x100)
				ControlsAnim += 0x10;
		}

		if (Player) {
			if (LevelCardTimer >= 1.5 && Player->Action != ActionType::Dead && FadeAction < FadeActionType::TO_BONUS_STAGE && !StopTimer)
				Timer++;
		}

		if (LevelCardTimer < 5.0)
			LevelCardTimer += 1.0 / 60.0;

		// Max timer
		if (Timer > 10 * 60 * 60 - 1) Timer = 10 * 60 * 60 - 1;

		if (FadeAction == 0 && LevelCardTimer >= 1.5 && FadeAction < FadeActionType::TO_BONUS_STAGE) {
			if (Player) {
				Player->InputController = 0;
				Player->InputUp = App->Input->GetControllerInput(Player->InputController)[IInput::I_UP];
				Player->InputDown = App->Input->GetControllerInput(Player->InputController)[IInput::I_DOWN];
				Player->InputLeftPress = App->Input->GetControllerInput(Player->InputController)[IInput::I_LEFT_PRESSED];
				Player->InputLeft = App->Input->GetControllerInput(Player->InputController)[IInput::I_LEFT];
				Player->InputRightPress = App->Input->GetControllerInput(Player->InputController)[IInput::I_RIGHT_PRESSED];
				Player->InputRight = App->Input->GetControllerInput(Player->InputController)[IInput::I_RIGHT];
				Player->InputJump = App->Input->GetControllerInput(Player->InputController)[IInput::I_CONFIRM_PRESSED];
				Player->InputJumpHold = App->Input->GetControllerInput(Player->InputController)[IInput::I_CONFIRM];

				if (Player->Action == ActionType::Dead && Player->EZY > CameraY + App->HEIGHT + 32) {
					if (Player->Lives > 0 && FadeAction == 0) {
						Player->Lives--;
						FadeAction = FadeActionType::DIED;
						FadeTimerMax = 64;
						FadeMax = 0x100;
						G->FadeToWhite = false;
						App->Audio->FadeMusic(0.75);
					}
					else {
						FadeAction = FadeActionType::EXIT;
						FadeTimerMax = 60 * 5;
						FadeMax = 0x100;
						G->FadeToWhite = false;
						App->Audio->FadeMusic(1);
					}
				}
			}
		}

		/*if (FadeAction == 0 && LevelCardTimer >= 1.5 && FadeAction == FadeActionType::TO_BONUS_STAGE) {
			if (Player) {
			}
			App->Print(3, "imagine we went to the bonus stage uwu");
		}*/

		if (Player && SaveGame::CurrentPartnerFlag != 0xFF)
		{
			if (App->Input->GetControllerInput(0)[IInput::I_DENY_PRESSED] && maxLayer)
			{
				//"Save" the players
				PlayerBuffer[1] = Players[0];
				PlayerBuffer[0] = Players[1];

				//copy the players back
				Players[0] = PlayerBuffer[0];
				Players[1] = PlayerBuffer[1];

				//render as player 1
				Players[0]->PlayerID = 0;
				Players[1]->PlayerID = 1;

				//set whos in charge
				Players[0]->Sidekick = false;
				Players[1]->Sidekick = true;

				//make sure our stuff is set
				Players[0]->Lives = Players[1]->Lives;
				Players[0]->Rings = Players[1]->Rings;
				Players[0]->Shield = Players[1]->Shield;
				Players[1]->Shield = ShieldType::None;
				Players[0]->HyperRings = Players[1]->HyperRings;
				Players[0]->HyperForm = Players[1]->HyperForm;
				Players[0]->SuperForm = Players[1]->SuperForm;

				if (Players[0]->SuperForm || Players[0]->HyperForm)
				{
					Players[0]->DoSuperTransform();
				}

				//Partner can't go super/hyper
				if (Players[1]->SuperForm || Players[1]->HyperForm)
				{
					Players[1]->Deform();
				}

				//Set the controlled player
				Player = Players[0];

				//Probably helpful idk
				PlayerBuffer[0] = NULL;
				PlayerBuffer[1] = NULL;
			}
		}

		if (Player && SaveGame::CurrentPartnerFlag != 0xFF)
		{
			if (!Players[1]->OnScreen && Players[0]->Action == ActionType::LookUp)
			{
				Players[1]->X = Players[0]->X;
				Players[1]->Y = CameraY - 20;
			}
		}

		if (!maxLayer) {
			// We're in debug mode! Time to have fun!

			//Set these so we unstick from shit
			Player->ForceRoll = false;
			Player->UnderwaterTimer = 0x1000;

			if (Player->InputLeft || Player->InputRight || Player->InputUp || Player->InputDown) {
				Player->GroundSpeed += 0x40;
				if (Player->GroundSpeed >= 0x1800) {
					Player->GroundSpeed = 0x1800;
				}
			}
			else {
				Player->GroundSpeed = 0;
			}
			if (Player->GroundSpeed >= 0x400) {
				Player->EZX -= (Player->InputLeft) * (Player->GroundSpeed >> 8);
				Player->EZX += (Player->InputRight) * (Player->GroundSpeed >> 8);
				Player->EZY -= (Player->InputUp) * (Player->GroundSpeed >> 8);
				Player->EZY += (Player->InputDown) * (Player->GroundSpeed >> 8);
			}
			else {
				Player->EZX -= App->Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED];
				Player->EZX += App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED];
				Player->EZY -= App->Input->GetControllerInput(0)[IInput::I_UP_PRESSED];
				Player->EZY += App->Input->GetControllerInput(0)[IInput::I_DOWN_PRESSED];
			}

			Player->DisplayX = Player->EZX;
			Player->DisplayY = Player->EZY;

			if (Player->DebugObject != nullptr && Player->DebugObject->OnScreen) {
				Player->DebugObject->X = Player->DisplayX;
				Player->DebugObject->Y = Player->DisplayY;
			}
			else if (Player->Hidden) {
				Player->Hidden = false;
				if (Player->DebugObjectIndex > -1) {
					Player->DebugObjectIndex -= 1;
				}
			}

			if (Player->InputJump) {
				if (ObjectCount < Objects.max_size() && ObjectSolidCount < ObjectsSolid.max_size() && ObjectSpringCount < ObjectsSpring.max_size() &&
					ObjectEnemiesCount < ObjectsEnemies.max_size() && ObjectBreakableCount < ObjectsBreakable.max_size() && ObjectPathSwitcherCount < ObjectsPathSwitcher.max_size()) {
					Player->Hidden = true;
					Player->DebugObjectIndex++;
					Player->DebugObjectIndex = Player->DebugObjectIndex % DebugObjectIDCount;

					if (Player->DebugObject && Player->DebugObject->isHeldDebugObject) {
						Player->DebugObject->Active = false;
						Player->DebugObject = NULL;
					}
					int16_t objId = DebugObjectIDList[Player->DebugObjectIndex];

					Object* obj = NULL;
					Ring *ring = NULL;

					if (objId != Player->LastDebugObjId) {
						Player->LastDebugObjId = objId;
						Player->DebugObjectSubIndex = 0;
					}

					switch (objId) {
					case 0x00: // Ring
						ring = (Ring*)GetNewObjectFromID(0);
						ring->Create();
						ring->X = Player->DisplayX;
						ring->Y = Player->DisplayY;
						ring->MyX = Player->DisplayX << 8;
						ring->MyY = Player->DisplayY << 8;
						ring->Scene = this;
						ring->Priority = true;
						ring->Timer = -1;
						ring->ShouldRingFall = false;
						obj = (Object *)ring;
						ring = NULL;
						break;
					case Obj_InvisibleSpikes: // Invisible Spikes
					case Obj_InvisibleDeath: // Invisible Death
					case Obj_InvisibleBlockH: // Invisible Block H
					case Obj_InvisibleBlockV: // Invisible Block V
						obj = GetNewObjectFromID(objId);
						Player->DebugObjectSubIndex = 17;
						break;
					default:
						obj = GetNewObjectFromID(objId);
						break;
					}
					if (obj != NULL) {
						obj->G = G;
						obj->App = App;
						obj->Scene = this;
						obj->InitialX = Player->EZX;
						obj->InitialY = Player->EZY;
						obj->FlipX = 0;
						obj->FlipY = 0;
						obj->ID = objId;
                        if (obj->BinIndex == 0xFFFFFFFF) {
                            while (obj->ID >= SpriteMapIDs.size() || !SpriteMapIDs.at(obj->ID)) {
                                obj->ID--;
                            }

                            obj->Sprite = SpriteMapIDs.at(obj->ID);
                        } else if (obj->BinIndex < SpriteBinMapIDs.size()) {
                            obj->Sprite = SpriteBinMapIDs.at(obj->BinIndex);
                        }

						obj->SubType = Player->DebugObjectSubIndex;

						obj->isDebugModeObject = true;
						obj->isHeldDebugObject = true;
						obj->DebugCreate();

						if (!obj->Active) {
							obj->Active = true;
						}

						obj->DrawCollisions = App->viewObjectCollision;

						ObjectCount++;
						Objects.push_back(obj);
						//Objects[ObjectCount++] = obj;
						Player->DebugObject = obj;

						//App->Print(0, "Created Object %d via Debug Mode!", objId);
					}
					else {
						Player->Hidden = false;
						Player->DebugObjectIndex = -1;
						Player->DebugObject = NULL;
					}
				}
				else {
					Player->Hidden = false;
					Player->DebugObjectIndex = -1;
					Player->DebugObject = NULL;
				}
			}

			if (App->Input->GetControllerInput(0)[IInput::I_EXTRA2_PRESSED]) {
				if (ObjectCount < Objects.max_size() && ObjectSolidCount < ObjectsSolid.max_size() && ObjectSpringCount < ObjectsSpring.max_size() &&
					ObjectEnemiesCount < ObjectsEnemies.max_size() && ObjectBreakableCount < ObjectsBreakable.max_size() && ObjectPathSwitcherCount < ObjectsPathSwitcher.max_size()) {
					if (Player->DebugObject && Player->DebugObject->OnScreen) {
						// We want to create a copy for easy use, So we do.
						uint8_t oldSubType = Player->DebugObject->SubType;
						Player->DebugObject->isHeldDebugObject = false;
						Player->DebugObject = NULL;
						int16_t objId = DebugObjectIDList[Player->DebugObjectIndex];

						Object* obj = NULL;
						Ring *ring = NULL;

						switch (objId) {
						case 0x00:
							ring = (Ring*)GetNewObjectFromID(0);
							ring->Create();
							ring->X = Player->DisplayX;
							ring->Y = Player->DisplayY;
							ring->MyX = Player->DisplayX << 8;
							ring->MyY = Player->DisplayY << 8;
							ring->Scene = this;
							ring->Priority = true;
							ring->Timer = -1;
							ring->ShouldRingFall = false;
							obj = (Object *)ring;
							ring = NULL;
							break;
						default:
							obj = GetNewObjectFromID(objId);
							break;
						}
						if (obj != NULL) {
							obj->G = G;
							obj->App = App;
							obj->Scene = this;
							obj->InitialX = Player->EZX;
							obj->InitialY = Player->EZY;
							obj->FlipX = 0;
							obj->FlipY = 0;
							obj->ID = objId;
                            if (obj->BinIndex == 0xFFFFFFFF) {
                                while (obj->ID >= SpriteMapIDs.size() || !SpriteMapIDs.at(obj->ID)) {
                                    obj->ID--;
                                }

                                obj->Sprite = SpriteMapIDs.at(obj->ID);
                            } else if (obj->BinIndex < SpriteBinMapIDs.size()) {
                                obj->Sprite = SpriteBinMapIDs.at(obj->BinIndex);
                            }

							obj->SubType = oldSubType;

							obj->isDebugModeObject = true;
							obj->isHeldDebugObject = true;
							obj->DebugCreate();

							if (!obj->Active) {
								obj->Active = true;
							}

							obj->DrawCollisions = App->viewObjectCollision;

							ObjectCount++;
							Objects.push_back(obj);
							//Objects[ObjectCount++] = obj;
							Player->DebugObject = obj;
						}
						else {
							Player->Hidden = false;
							Player->DebugObjectIndex = -1;
							Player->DebugObject = NULL;
						}
					}
				}
				else {
					if (Player->DebugObject && Player->DebugObject->OnScreen) {
						Player->DebugObject->isHeldDebugObject = false;
						Player->DebugObject = NULL;
					}
					Player->Hidden = false;
					Player->DebugObjectIndex = -1;
					Player->DebugObject = NULL;
				}
			}

			if (App->Input->GetControllerInput(0)[IInput::I_DENY_PRESSED]) {
				if (Player->DebugObject) {
					Player->DebugObjectSubIndex = (Player->DebugObject->SubType + Player->DebugObject->GetSubTypeIncrement()) % Player->DebugObject->GetSubTypeMax();
					Player->DebugObject->SubType = Player->DebugObjectSubIndex;
					Player->DebugObject->UpdateSubType();
				}
			}

			Player->YSpeed = 0;
		}

		if (!(Frame & 3) && ItemsSprite && SaveGame::CurrentMode == 1) {
			ISprite* spr = ItemsSprite;
			Uint32 temp = spr->GetPalette(0x3C + 4 - 1);
			for (int i = 4 - 1; i >= 1; i--) {
				spr->SetPalette(0x3C + i, spr->GetPalette(0x3C + i - 1));
			}
			spr->SetPalette(0x3C, temp);

			temp = spr->GetPaletteAlt(0x3C + 4 - 1);
			for (int i = 4 - 1; i >= 1; i--) {
				spr->SetPaletteAlt(0x3C + i, spr->GetPaletteAlt(0x3C + i - 1));
			}
			spr->SetPaletteAlt(0x3C, temp);

			spr->UpdatePalette();
		}

		EarlyUpdate();

		if (maxLayer) {
			if (LevelCardTimer >= 1.0 && FadeAction < FadeActionType::TO_BONUS_STAGE) {
				for (int p = 0; p < PlayerCount; p++) {
					playerUpdateCount[p]++;

					clock_t start_t = clock();

					Players[p]->Update();

					playerUpdateTimers[p] += ((clock() - start_t) * 1000.0f / CLOCKS_PER_SEC - playerUpdateTimers[p]) / playerUpdateCount[p];
				}
			}
		}

		if (Player)
		{
			for (unsigned int o = 0; o < (unsigned int)ObjectCount && Player->Action != ActionType::Dead; o++) {
				Object* obj = Objects[o];
				if (obj != NULL) {
					if (obj->Active) {
						LastObjectUpdated = obj;

						//int32_t NoNegativeCamY = CameraY + App->HEIGHT / 2;

						bool OnScreen = false;

						if (Data->Layers[Data->CameraLayer].IsScrollingVertical) {
							// Reverse Engineered code from Sonic 3 & Knuckles, Ported to our form.
							/*
							// Original Version
							OnScreen |= (
									 -1 < (obj->X - CameraX) + obj->W &&
									 ((obj->X - CameraX) - obj->W) < 0x140 &&
									 ((obj->Y - CameraY) + obj->H & ScreenYWrapValue) < ((obj->H * 2) + 0xe0));

							// Split up version.
							OnScreen |= (
								   (-1 < ((obj->X - CameraX) + obj->W)) &&
								   (((obj->X - CameraX) - obj->W) < 0x140) &&
								   ((obj->Y - CameraY) + obj->H & ScreenYWrapValue) &&
								   (((obj->Y - CameraY) - obj->H & ScreenYWrapValue) < 0xe0));

							// If this was true in the original, It'd skip the part where the
							// flag for being visible was modified.
							OnScreen |= (
								   (((obj->X - CameraX) + obj->W) < 0) ||
								   (0x13f < ((obj->X - CameraX) - obj->W)) ||
								   obj->H * 2 + 0xe0 <= ((obj->Y - CameraY) + obj->H & ScreenYWrapValue));

							// Modified version to work the reverse of the one above.
							OnScreen |= (
								   (((obj->X - CameraX) + obj->W) >= 0) ||
								   (0x13f >= ((obj->X - CameraX) - obj->W)) ||
								   obj->H * 2 + 0xe0 > ((obj->Y - CameraY) + obj->H & ScreenYWrapValue));

							OnScreen |= (
								   (-1 < ((obj->X - 0x80) + obj->W)) &&
								   (((obj->X - 0x80) - obj->W) < 0x140) &&
								   (-1 < ((obj->Y - 0x80) + obj->H)) &&
								   (((obj->Y - 0x80) - obj->H) < 0xe0));
						   */

							if (obj->VisW > obj->W || obj->VisH > obj->H) {
								OnScreen |= (
									-1 < (obj->X - CameraX) + obj->VisW &&
									((obj->X - CameraX) - obj->VisW) < 0x140 &&
									((obj->Y - CameraY) + obj->VisH & ScreenYWrapValue) < ((obj->VisH * 2) + 0xe0));

								/*
								OnScreen |= (
									obj->X + obj->VisW / 2 >= CameraX - 0x80 &&
									(obj->Y + obj->VisH / 2) % (Data->Layers[Data->CameraLayer].Height * 16) >= CameraY - 0x80 &&
									obj->X - obj->VisW / 2 < CameraX + App->WIDTH + 0x80 &&
									(obj->Y - obj->VisH / 2) % (Data->Layers[Data->CameraLayer].Height * 16) < CameraY + App->HEIGHT + 0x80);
								*/
							}
							else {
								int16_t Calc = (obj->Y - CameraY) + obj->H & ScreenYWrapValue;
								if ((obj->Y - CameraY) + obj->H > ScreenYWrapValue) {
									Calc = (((obj->Y - CameraY) + obj->H) + ScreenYWrapValue) & ScreenYWrapValue;
								}
								OnScreen |= (
									-1 < (obj->X - CameraX) + obj->W &&
									((obj->X - CameraX) - obj->W) < 0x140 &&
									(Calc < (obj->H * 2) + 0xe0));

								if (obj->PrintDebuggingInfo) {
									App->Print(0, "%04X, %04X", Calc, (obj->H * 2) + 0xe0);
								}

								/*
								OnScreen |= (
									obj->X + obj->W / 2 >= CameraX - 0x80 &&
									(obj->Y + obj->H / 2) % (Data->Layers[Data->CameraLayer].Height * 16) >= CameraY - 0x80 &&
									obj->X - obj->W / 2 < CameraX + App->WIDTH + 0x80 &&
									(obj->Y - obj->H / 2) % (Data->Layers[Data->CameraLayer].Height * 16) < CameraY + App->HEIGHT + 0x80);
								*/
							}
						}
						else {
							if (obj->VisW > obj->W || obj->VisH > obj->H) {
								OnScreen |= (
									obj->X + obj->VisW >= CameraX - 0x80 &&
									obj->Y + obj->VisH >= CameraY - 0x80 &&
									obj->X - obj->VisW < CameraX + App->WIDTH + 0x80 &&
									obj->Y - obj->VisH < CameraY + App->HEIGHT + 0x80);
							}
							else {
								OnScreen |= (
									obj->X + obj->W / 2 >= CameraX - 0x80 &&
									obj->Y + obj->H / 2 >= CameraY - 0x80 &&
									obj->X - obj->W / 2 < CameraX + App->WIDTH + 0x80 &&
									obj->Y - obj->H / 2 < CameraY + App->HEIGHT + 0x80);
							}
						}

						if (obj->OnScreen && !OnScreen) {
							obj->OnScreen = OnScreen;
							obj->OnLeaveScreen();
						}

						obj->OnScreen = OnScreen;
						if (obj->Priority || OnScreen) {
							obj->CollidingWithPlayer = false;
							for (int p = 0; p < PlayerCount && maxLayer; p++) {
								if (obj->X + obj->W / 2 >= Players[p]->EZX - Players[p]->W / 2 - 1 &&
									obj->Y + obj->H / 2 >= Players[p]->EZY - Players[p]->H / 2 - 1 &&
									obj->X - obj->W / 2 < Players[p]->EZX + Players[p]->W / 2 + 1 &&
									obj->Y - obj->H / 2 < Players[p]->EZY + Players[p]->H / 2 + 1) {
									if (Players[p]->Action == ActionType::Dead) continue;

									int wy = (Player->W + obj->W) * ((int)Players[p]->EZY - (int)obj->Y);
									int hx = (Player->H + obj->H) * ((int)Players[p]->EZX - (int)obj->X);

									int hitFrom = (int)CollideSide::RIGHT;

									if (wy > hx) {
										if (wy > -hx) {
											hitFrom = (int)CollideSide::BOTTOM;
										}
										else {
											hitFrom = (int)CollideSide::LEFT;
										}
									}
									else {
										if (wy > -hx) {
											hitFrom = (int)CollideSide::RIGHT;
										}
										else {
											hitFrom = (int)CollideSide::TOP;
										}
									}

									obj->CollidingWithPlayer |= obj->OnCollisionWithPlayer(Players[p]->PlayerID, hitFrom, 0);

									if (obj->Pushable) {
										obj->OnPush(Players[p]->PlayerID, hitFrom);
									}
								}

								if (obj->X + obj->W / 2 >= Players[p]->EZX - Players[p]->W / 2 &&
									obj->X - obj->W / 2 < Players[p]->EZX + Players[p]->W / 2 &&
									Players[p]->EZY + Players[p]->H / 2 >= obj->Y - obj->H / 2 - 4 &&
									Players[p]->EZY + Players[p]->H / 2 < obj->Y - obj->H / 2 + 2 &&
									Players[p]->YSpeed >= 0 &&
									Players[p]->Ground) {
									obj->BeingStoodOn = true;
								}
								else
									obj->BeingStoodOn = false;
							}

							obj->Update();
						}
					}
				}
			}
		}

		if (maxLayer) {
			if (LevelCardTimer >= 1.0 && FadeAction < FadeActionType::TO_BONUS_STAGE) {
				for (int p = 0; p < PlayerCount; p++) {
					playerLateUpdateCount[p]++;

					clock_t start_t = clock();

					Players[p]->LateUpdate();

					playerLateUpdateTimers[p] += ((clock() - start_t) * 1000.0f / CLOCKS_PER_SEC - playerLateUpdateTimers[p]) / playerLateUpdateCount[p];
				}
			}
		}

		for (vector<Object*>::iterator it = TempObjects.begin(); it != TempObjects.end(); ++it) {
            Object* tempObject = (*it);
            if (tempObject != NULL && tempObject->Active) {
                tempObject->Update();
            }
		}

		for (vector<Object*>::iterator it = TempObjectTiles.begin(); it != TempObjectTiles.end(); ++it) {
            Object* tempTileObject = (*it);
            if (tempTileObject != NULL && tempTileObject->Active) {
                tempTileObject->Update();
            }
		}

		RingAnimationFrame += 0x80;
		RingAnimationFrame &= 0xFFF;

		if (WaterSprite) {
			WaterAnimationFrame = (Frame % 40) << 6;
		}

		HandleCamera();
		Subupdate();

		if (ShakeTimer > 0)
			ShakeTimer--;
	}
	// Pause menu
	else {
		if (Paused) {
			PauseAnim[0] += (260 * 0x100 - PauseAnim[0]) / 3;
			PauseAnim[1] += (100 * 0x100 - PauseAnim[1]) / 3;
			PauseAnim[2] += (210 * 0x100 - PauseAnim[2]) / 3;
		}
		else {
			PauseAnim[0] += (-10 * 0x100 - PauseAnim[0]) / 3;
			PauseAnim[1] += (-10 * 0x100 - PauseAnim[1]) / 3;
			PauseAnim[2] += (-10 * 0x100 - PauseAnim[2]) / 3;

			if (PauseAnim[0] <= 0) {
				PauseFinished = false;
				std::memset(&PauseAnim[0], 0, 8 * sizeof(int));
			}
		}
		PauseAnim[3] = (PauseAnim[3] + 11) % (360);
		for (int i = 0; i < 4; i++)
			if (i == PauseSelectedMenuItem)
				PauseAnim[4 + i] = IMath::min(2, PauseAnim[4 + i] + 1);
			else
				PauseAnim[4 + i] = IMath::max(0, PauseAnim[4 + i] - 1);

		//Messy ikik
		bool inBox = false;
		int before = PauseSelectedMenuItem;
		if (App->Input->MouseY > 197 && App->Input->MouseY < (197 + 35)) {
			//Resume
			if (App->Input->MouseX > 81 && App->Input->MouseX < (81 + 35))
			{
				PauseSelectedMenuItem = 0;
				inBox = true;
			}
			//Restart
			else if (App->Input->MouseX > 124 && App->Input->MouseX < (124 + 35))
			{
				PauseSelectedMenuItem = 1;
				inBox = true;
			}
			//Settings
			else if (App->Input->MouseX > 167 && App->Input->MouseX < (167 + 35))
			{
				PauseSelectedMenuItem = 2;
				inBox = true;
			}
			//Exit
			else if (App->Input->MouseX > 210 && App->Input->MouseX < (210 + 35))
			{
				PauseSelectedMenuItem = 3;
				inBox = true;
			}
			//Radio
			else if (App->Input->MouseX > 253 && App->Input->MouseX < (253 + 35))
			{
				PauseSelectedMenuItem = 4;
				inBox = true;
			}
			else
			{
				inBox = false;
			}
			if (inBox && before != PauseSelectedMenuItem) {
				Sound::Play(Sound::SFX_MENUBLEEP);
			}
		}

		if (FadeAction == 0) {
			if (App->Input->GetControllerInput(0)[IInput::I_LEFT_PRESSED] || App->Input->MouseReleased && inBox) {
				PauseSelectedMenuItem--;
				Sound::Play(Sound::SFX_MENUBLEEP);
			}
			if (App->Input->GetControllerInput(0)[IInput::I_RIGHT_PRESSED] || App->Input->MouseReleased && inBox) {
				PauseSelectedMenuItem++;
				Sound::Play(Sound::SFX_MENUBLEEP);
			}

			if (App->Input->GetControllerInput(0)[IInput::I_CONFIRM_PRESSED] || App->Input->MouseReleased && inBox) { // confirm
				if (PauseSelectedMenuItem == 0) {
					Paused = false;
					//Sound::Play(Sound::SFX_MENUACCEPT);
				}
				else if (PauseSelectedMenuItem == 1) {
					FadeAction = FadeActionType::RESTART;
					FadeTimerMax = 80;
					FadeMax = 0x200;
					G->FadeToWhite = false;
					SavedPositionX = -1;
					SavedPositionY = -1;
					Checkpoint = -1;

					App->Audio->FadeMusic(1);

					Sound::Play(Sound::SFX_MENUACCEPT);
				}
				else if (PauseSelectedMenuItem == 3) {
					FadeAction = FadeActionType::EXIT;
					FadeTimerMax = 48;
					FadeMax = 0x120;
					G->FadeToWhite = false;
					App->Audio->FadeMusic(1);

					Sound::Play(Sound::SFX_MENUACCEPT);
				}
				else {
					Sound::Play(Sound::SFX_MENUFAIL);
					App->Print(0, "Other pause items not implemented yet!");
				}
			}
			else if (App->Input->GetControllerInput(0)[IInput::I_DENY_PRESSED]) { // deny
				Paused = false;
			}
		}

		if (PauseSelectedMenuItem < 0)
			PauseSelectedMenuItem = 4;
		if (PauseSelectedMenuItem > 4)
			PauseSelectedMenuItem = 0;
	}

	if (ShowResults) {
		if (ResultsTimer > 300) {
			ControlsVisible = false;
			if (!DoneSpinning) {
				if (App->Input->GetControllerInput(0)[IInput::I_ANY_PRESSED]) {
					while (TimerTotal > 0) {
						int amountToSubtract = 100;
						if (TimerTotal < amountToSubtract)
							amountToSubtract = TimerTotal;

						TimerTotal -= amountToSubtract;
						TotalToAdd += amountToSubtract;
					}

					while (Player->Rings > 0) {
						Player->Rings--;
						TotalToAdd += 100;
					}

					DoneSpinning = true;
				}
				else {
					if (Frame % 3 == 0) {
						Sound::Play(Sound::SFX_SCORE_ADD);
					}

					if (TimerTotal > 0) {
						int amountToSubtract = 100;
						if (TimerTotal < amountToSubtract)
							amountToSubtract = TimerTotal;

						TimerTotal -= amountToSubtract;
						TotalToAdd += amountToSubtract;
					}
					if (Player->Rings > 0) {
						Player->Rings--;
						TotalToAdd += 100;
					}

					ResultsTimer--;

					if (Player->Rings == 0 && TimerTotal == 0)
						DoneSpinning = true;
				}

				if (DoneSpinning) {
					Sound::Play(Sound::SFX_SCORE_TOTAL);
					Score += TotalToAdd;
				}
			}
		}
		if (ResultsTimer > 390 + 60) {
			Timer = 0;

			ShowResults = false;

			FinishResults();
		}
		ResultsTimer++;
	}

	// Fade functionality
	if (FadeTimer == -1 && FadeTimerMax > 1)
		FadeTimer = FadeTimerMax;
	if (FadeTimer > 0) {
		FadeTimer--;
		if (FadeAction != FADEIN)
			G->SetFade((int)((1.0f - (float)FadeTimer / FadeTimerMax) * FadeMax));
		else
			//G->SetFade((int)(((float)FadeTimer / FadeTimerMax) * FadeMax));
			G->SetFade(0xFF - (int)((IMath::clampDoubleDown(LevelCardTimer, 1.0, 1.5) / 0.5) * 0xFF));
	}

	// Fade actions
	if (FadeTimer == 0) {
		if (FadeAction == FadeActionType::RESTART) {
			Paused = false;
			PauseFinished = true;
			if (Player) Player->Shield = ShieldType::None;
			SaveGame::Savefiles[SaveGame::CurrentSaveFile].Shield = 0;
			RestartStage(false, true);
			FadeAction = FadeActionType::FADEIN;
			FadeTimerMax = 90;
			FadeMax = 0x140;
			G->FadeToWhite = false;
		}
		else if (FadeAction == FadeActionType::DIED) {
			Paused = false;
			PauseFinished = true;
			RestartStage(false, true);
			FadeAction = FadeActionType::FADEIN;
			FadeTimerMax = 90;
			FadeMax = 0x140;
			G->FadeToWhite = false;
		}
		else if (FadeAction == FadeActionType::EXIT) {
			//App->Running = false;
			//FadeAction = 0;
			//FadeTimerMax = 1;
			//Cleanup();

			StateSaved = false;
			App->NextScene = new Scene_DataSelect(App, G, SaveGame::CurrentMode);
		}
		else if (FadeAction == FadeActionType::FADEIN) {
			FadeAction = 0;
			FadeTimerMax = 1;
		}
		else if (FadeAction == FadeActionType::TO_SPECIAL_STAGE) {
			FadeAction = 0;
			FadeTimerMax = 1;

			Level_SpecialStage* NextScene = new Level_SpecialStage(App, G);
			NextScene->ZoneID = 0x100 | VisualAct;

			int toLevel = 0;
			while (toLevel < 16) {
				if (!SaveGame::GetEmerald(toLevel)) break;
				toLevel++;
			}

			NextScene->Act = toLevel;
			App->NextScene = NextScene;
		}
		if (FadeAction == FadeActionType::TO_BONUS_STAGE) {
			FadeAction = 0;
			FadeTimerMax = 1;

			Level_BonusStage* NextScene = new Level_BonusStage(App, G, NextBonusStage);
			NextScene->ZoneID = 0x100 | VisualAct;
			App->NextScene = NextScene;
		}
		else if (FadeAction == FadeActionType::NEXT_ZONE) {
			FadeAction = 0;
			FadeTimerMax = 1;
			GoToNextAct();
		}
		else if (FadeAction == FadeActionType::CUSTOM_FADE_ACTION) {
			FadeAction = 0;
			FadeTimerMax = 1;
			DoCustomFadeAction();
		}
		FadeTimer = -1;
	}

	CleanupObjects();
}

PUBLIC VIRTUAL void LevelScene::HandleCamera() {
	int d0 = Data->Layers[Data->CameraLayer].Width * 16 - App->WIDTH;
	int d1 = Data->Layers[Data->CameraLayer].Height * 16 - App->HEIGHT;

	if (Data->Layers[Data->CameraLayer].IsScrollingVertical) {
		d1 = 0xFFFFF;
    }

	if (CameraMaxX > d0) {
		CameraMaxX = d0;
    }
	if (CameraMaxY < d1) {
		CameraMaxY = d1;
    }

	int OffsetX = 0, OffsetY = 0;
	if (Player) {
		if (Player->Action == ActionType::Dead)
			return;

		bool OffCenteredCamera = false;
		if (CameraAutoScrollX != 0) {
			CameraX += CameraAutoScrollX;
			CameraDeltaX += CameraAutoScrollX;
			// CameraDeltaY += CameraAutoScrollY;

			if (Player->EZX - Player->W / 2 < CameraX) {
				Player->EZX = IMath::max(CameraX + Player->W / 2, Player->EZX);
				if (Player->Ground) {
					if (Player->GroundSpeed < CameraAutoScrollX * 0x100)
						Player->GroundSpeed = CameraAutoScrollX * 0x100;
				}
				else {
					// if (Player->XSpeed < CameraAutoScrollX)
					//     Player->XSpeed = CameraAutoScrollX;
				}
			}
			if (Player->EZX > -8 * OffCenteredCamera + CameraX + App->WIDTH / 2) {
				Player->EZX = IMath::min(-8 * OffCenteredCamera + CameraX + App->WIDTH / 2, Player->EZX);
			}

			return;
		}

		if (Data->Layers[Data->CameraLayer].IsScrollingVertical) {
			if (Player->EZY < 0) {
				Player->EZY += Data->Layers[Data->CameraLayer].Height * 16;
				CameraY += Data->Layers[Data->CameraLayer].Height * 16;
			}

			if (Player->EZY >= Data->Layers[Data->CameraLayer].Height * 16) {
				Player->EZY -= Data->Layers[Data->CameraLayer].Height * 16;
				CameraY -= Data->Layers[Data->CameraLayer].Height * 16;
			}
		}

		for (int p = 0; p < PlayerCount; p++) {
			IPlayer* Player = Players[p];
			if (Player->Action == ActionType::Dead)
				continue;

			if (maxLayer == 0) continue;

			if (!Data->Layers[Data->CameraLayer].IsScrollingVertical && Player->EZY > CameraMaxY + App->HEIGHT && maxLayer) {
				Player->Die(false);
            }

			if (CameraX == CameraMinX ||
				CameraX == CameraMaxX) {
				Player->CameraLockTimer = 0;
			}

			if (Player->CameraLockTimer <= 0) {
				if (Player->X < CameraMinX + 16) {
					Player->X = CameraMinX + 16;
					Player->XSpeed = 0;
					Player->GroundSpeed = 0;
				}

				if (Player->EZX > CameraMaxX + App->WIDTH - 16) {
					Player->EZX = CameraMaxX + App->WIDTH - 16;
					Player->XSpeed = 0;
					Player->GroundSpeed = 0;
				}
			}
			if (!Data->Layers[Data->CameraLayer].IsScrollingVertical && CameraMinY != 0) {
				if (Player->EZY < CameraMinY - 64) {
					Player->EZY = CameraMinY - 64;
					Player->YSpeed = 0;
					Player->GroundSpeed = 0;
					Player->Ground = false;
					Player->Angle = 0;
					Player->AngleMode = 0;
				}
			}
		}

		int camX = int(Player->EZX + Player->CameraX);
		int camY;
		if (ManiaLevel) {
			camY = int(Player->EZY + Player->CameraY - 4);
		} else {
			camY = int(Player->EZY + Player->CameraY + 8);
        }

		if (Player->Action == ActionType::Rolling) {
			camY -= Player->H / 2 - 16;
        }

		OffsetX = (camX - (CameraX + App->WIDTH / 2 - 8 * OffCenteredCamera));
		OffsetY = (camY - (CameraY + App->HEIGHT / 2));

		int Max = 0x18;
		if (ZoneID == 5 && Act == 1 && Player->EZX < 0x3880) {
			Max = 0x90;
		}

		if (IMath::abs(OffsetX) > 8) {
			OffsetX -= 8 * IMath::sign(OffsetX);
		} else {
			OffsetX = 0;
		}

		if (Player->CameraLockTimer > 0) {
			OffsetX = 0;
        }

		OffsetX = IMath::min(IMath::abs(OffsetX), Max) * IMath::sign(OffsetX);

		if (!Player->Ground) {
			if (IMath::abs(OffsetY) > 32) {
				OffsetY -= 32 * IMath::sign(OffsetY);
			} else {
				OffsetY = 0;
            }
		}

		Max = 6;
		if (IMath::abs(Player->YSpeed) >= 0x43C && Player->Ground) {
			Max = 24;
        }

		// NOTE: Mania notes
		// When player lands, wait 16 frames

		if (IMath::abs(Player->YSpeed) < 0x43C && Player->Ground)
			OffsetY = IMath::min(IMath::abs(OffsetY) / 2, Max) * IMath::sign(OffsetY);

		CameraX += OffsetX;
		CameraY += OffsetY;
	}

	if (CameraX < CameraMinX) {
		OffsetX = 0;
    }
	if (CameraX > CameraMaxX) {
		OffsetX = 0;
    }

	CameraDeltaX += OffsetX;
	CameraDeltaY += OffsetY;

	if (CameraX < CameraMinX) {
		CameraX = CameraMinX;
    }
	if (CameraX > CameraMaxX) {
		CameraX = CameraMaxX;
    }

	if (!Data->Layers[Data->CameraLayer].IsScrollingVertical) {
        if (CameraY < CameraMinY) {
			CameraY = CameraMinY;
        }
		if (CameraY > CameraMaxY) {
			CameraY = CameraMaxY;
        }
	} else {
		if (CameraY < CameraMinY && CameraMinY != 0) {
			CameraY = CameraMinY;
        }
		if (CameraY > CameraMaxY && CameraMaxY != Data->Layers[Data->CameraLayer].Height * 16 - App->HEIGHT) {
			CameraY = CameraMaxY;
        }
	}
}

PUBLIC void LevelScene::AddSelfToRegistry(Object* obj, const char* where) {
	if (!strcmp(where, "Solid")) {
		ObjectSolidCount++;
		ObjectsSolid.push_back(obj);
	} else if (!strcmp(where, "Spring")) {
		ObjectSpringCount++;
		ObjectsSpring.push_back(obj);
	} else if (!strcmp(where, "Enemies")) {
		ObjectEnemiesCount++;
		ObjectsEnemies.push_back((Enemy*)obj);
	} else if (!strcmp(where, "Breakable")) {
		ObjectBreakableCount++;
		ObjectsBreakable.push_back(obj);
	} else if (!strcmp(where, "PathSwitcher")) {
        ObjectPathSwitcherCount++;
		ObjectsPathSwitcher.push_back(obj);
	}
}

PUBLIC void LevelScene::CleanupObjects() {
	// Clean up any un-needed Objects.

	std::vector<Object*> RefreshObjects;
	RefreshObjects.reserve(2000);
	int NewerObjectNewCount = ObjectNewCount;

	std::vector<Object*> RefreshObjectsSolid;
	RefreshObjectsSolid.reserve(1000);

	std::vector<Object*> RefreshObjectsSpring;
	RefreshObjectsSpring.reserve(300);

	std::vector<Enemy*> RefreshObjectsEnemies;
	RefreshObjectsEnemies.reserve(300);

	std::vector<Object*> RefreshObjectsBreakable;
	RefreshObjectsBreakable.reserve(300);
	int NewObjectBreakableCount = 0;

    std::vector<Object*> RefreshTempObjects;
    RefreshTempObjects.reserve(TempObjects.size());

	std::vector<Object*> UnrefreshedObjects = Objects;
	int OldObjectCount = ObjectCount;
	int OldObjectNewCount = ObjectNewCount;

	std::vector<Object*> UnrefreshedObjectsSolid = ObjectsSolid;
	int OldObjectSolidCount = ObjectSolidCount;

	std::vector<Object*> UnrefreshedObjectsSpring = ObjectsSpring;
	int OldObjectSpringCount = ObjectSpringCount;

	std::vector<Enemy*> UnrefreshedObjectsEnemies = ObjectsEnemies;
	int OldObjectEnemiesCount = ObjectEnemiesCount;

	std::vector<Object*> UnrefreshedObjectsBreakable = ObjectsBreakable;
	int OldObjectBreakableCount = ObjectBreakableCount;

    std::vector<Object*> UnrefreshedTempObjects = TempObjects;
    size_t UnrefreshedTempObjectsCount = TempObjects.size();

	for (int i = 0; i < ObjectCount; i++) {
		if (Objects.at(i) == nullptr) {
			if (i >= ObjectCount + ObjectNewCount) {
				NewerObjectNewCount--;
			}
			continue;
		} else if (!Objects.at(i)->Active && Objects.at(i)->CleanupInactiveObject) {
			if (i >= ObjectCount + ObjectNewCount) {
				NewerObjectNewCount--;
			}
			continue;
		}
		Objects.at(i)->DrawCollisions = App->viewObjectCollision;
		RefreshObjects.push_back(Objects.at(i));
	}

	for (int i = 0; i < ObjectSolidCount; i++) {
		if (ObjectsSolid.at(i) == nullptr) {
			continue;
		} else if (!ObjectsSolid.at(i)->Active && ObjectsSolid.at(i)->CleanupInactiveObject) {
			continue;
		}
		RefreshObjectsSolid.push_back(ObjectsSolid.at(i));
	}

	for (int i = 0; i < ObjectSpringCount; i++) {
		if (ObjectsSpring.at(i) == nullptr) {
			continue;
		} else if (!ObjectsSpring.at(i)->Active && ObjectsSpring.at(i)->CleanupInactiveObject) {
			continue;
		}
		RefreshObjectsSpring.push_back(ObjectsSpring.at(i));
	}

	for (int i = 0; i < ObjectEnemiesCount; i++) {
		if (ObjectsEnemies.at(i) == nullptr) {
			continue;
		} else if (!ObjectsEnemies.at(i)->Active && ObjectsEnemies.at(i)->CleanupInactiveObject) {
			continue;
		}
		RefreshObjectsEnemies.push_back(ObjectsEnemies.at(i));
	}

	for (int i = 0; i < ObjectBreakableCount; i++) {
		if (ObjectsBreakable.at(i) == nullptr) {
			continue;
		} else if (!ObjectsBreakable.at(i)->Active && ObjectsBreakable.at(i)->CleanupInactiveObject) {
			continue;
		}
		RefreshObjectsBreakable.push_back(ObjectsBreakable.at(i));
	}

	for (size_t i = 0; i < TempObjects.size(); i++) {
		if (TempObjects.at(i) == nullptr) {
			continue;
		} else if (!TempObjects.at(i)->Active) {
			continue;
		}
		RefreshTempObjects.push_back(TempObjects.at(i));
	}

	RefreshObjects.shrink_to_fit();
	Objects = RefreshObjects;
	ObjectCount = RefreshObjects.size();
	ObjectNewCount = NewerObjectNewCount;

	RefreshObjectsSolid.shrink_to_fit();
	ObjectsSolid = RefreshObjectsSolid;
	ObjectSolidCount = RefreshObjectsSolid.size();

	RefreshObjectsSpring.shrink_to_fit();
	ObjectsSpring = RefreshObjectsSpring;
	ObjectSpringCount = RefreshObjectsSpring.size();

	RefreshObjectsEnemies.shrink_to_fit();
	ObjectsEnemies = RefreshObjectsEnemies;
	ObjectEnemiesCount = RefreshObjectsEnemies.size();

	RefreshObjectsBreakable.shrink_to_fit();
	ObjectsBreakable = RefreshObjectsBreakable;
	ObjectBreakableCount = RefreshObjectsBreakable.size();

	RefreshTempObjects.shrink_to_fit();
	TempObjects = RefreshTempObjects;

	// For some reason, Deleting the objects is only fine on Debug builds.
	// This could be because Release might memory manage it automatically.
	// Not sure as of right now. So we'll only delete the UnrefreshedObjects and
	// none of the others for non-debug for now.

	for (int i = 0; i < OldObjectCount; i++) {
		if (UnrefreshedObjects.at(i) == nullptr) {
			continue;
		}
		if (!UnrefreshedObjects.at(i)->Active && UnrefreshedObjects.at(i)->CleanupInactiveObject) {
			delete UnrefreshedObjects.at(i);
			UnrefreshedObjects.at(i) = nullptr;
		}
	}

	for (int i = 0; i < OldObjectSolidCount; i++) {
		if (UnrefreshedObjectsSolid.at(i) == nullptr) {
			continue;
		}
		if (!UnrefreshedObjectsSolid.at(i)->Active && UnrefreshedObjectsSolid.at(i)->CleanupInactiveObject) {
#ifdef _DEBUG
			delete UnrefreshedObjectsSolid.at(i);
#endif
			UnrefreshedObjectsSolid.at(i) = nullptr;
		}
	}

	for (int i = 0; i < OldObjectSpringCount; i++) {
		if (UnrefreshedObjectsSpring.at(i) == nullptr) {
			continue;
		}
		if (!UnrefreshedObjectsSpring.at(i)->Active && UnrefreshedObjectsSpring.at(i)->CleanupInactiveObject) {
#ifdef _DEBUG
			delete UnrefreshedObjectsSpring.at(i);
#endif
			UnrefreshedObjectsSpring.at(i) = nullptr;
		}
	}

	for (int i = 0; i < OldObjectEnemiesCount; i++) {
		if (UnrefreshedObjectsEnemies.at(i) == nullptr) {
			continue;
		}
		if (!UnrefreshedObjectsEnemies.at(i)->Active && UnrefreshedObjectsEnemies.at(i)->CleanupInactiveObject) {
#ifdef _DEBUG
			delete UnrefreshedObjectsEnemies.at(i);
#endif
			UnrefreshedObjectsEnemies.at(i) = nullptr;
		}
	}

	for (int i = 0; i < OldObjectBreakableCount; i++) {
		if (UnrefreshedObjectsBreakable.at(i) == nullptr) {
			continue;
		}
		if (!UnrefreshedObjectsBreakable.at(i)->Active && UnrefreshedObjectsBreakable.at(i)->CleanupInactiveObject) {
#ifdef _DEBUG
			delete UnrefreshedObjectsBreakable.at(i);
#endif
			UnrefreshedObjectsBreakable.at(i) = nullptr;
		}
	}

	for (size_t i = 0; i < UnrefreshedTempObjectsCount; i++) {
		if (UnrefreshedTempObjects.at(i) == nullptr) {
			continue;
		}
		if (!UnrefreshedTempObjects.at(i)->Active) {
			delete UnrefreshedTempObjects.at(i);
			UnrefreshedTempObjects.at(i) = nullptr;
		}
	}

	UnrefreshedObjects.clear();
	UnrefreshedObjectsSolid.clear();
	UnrefreshedObjectsSpring.clear();
	UnrefreshedObjectsEnemies.clear();
	UnrefreshedObjectsBreakable.clear();
    UnrefreshedTempObjects.clear();
}

PUBLIC void LevelScene::RenderAnimatedSprites(int layer) {
}

PUBLIC void LevelScene::RenderRings() {
	for (unsigned int o = 0; o < (unsigned int)RingPropCount; o++) {
		ObjectProp obj = RingProps.at(o);
		if (!obj.ID) continue;

		bool OnScreenH =
			obj.X + 8 >= CameraX &&
			obj.X - 8 < CameraX + App->WIDTH;
		if (!OnScreenH) continue;

		int oY = obj.Y;
		bool OnScreen =
			oY + 8 >= CameraY &&
			oY - 8 < CameraY + App->HEIGHT;

		if (Data->Layers[Data->CameraLayer].IsScrollingVertical && !OnScreen) {
			oY -= Data->Layers[Data->CameraLayer].Height * 16;
			OnScreen =
				oY + 8 >= CameraY &&
				oY - 8 < CameraY + App->HEIGHT;
		}

		if (OnScreen) {
			if (SaveGame::CurrentMode == 1) {
				G->DrawSprite(ItemsSprite, 7, RingAnimationFrame >> 8, obj.X - CameraX, oY - CameraY, 0, IE_NOFLIP);
			}
			else {
				G->DrawSprite(ItemsSprite, 7, RingAnimationFrame >> 10, obj.X - CameraX, oY - CameraY, 0, IE_NOFLIP);
			}
			if (App->viewObjectCollision) {
				G->SetDrawAlpha(0x80);
				G->DrawRectangle(obj.X - (16 / 2) - CameraX, obj.Y - (16 / 2) - CameraY, 16, 16, 0x49ED80);
				G->SetDrawAlpha(0xFF);
			}
		}
	}
}

PUBLIC void LevelScene::RenderHUD() {
	bool Mobile = IApp::Mobile;

	int value;
	int valen;

	int STR_X = 16 - (HUDAnim >> 1);

	ISprite* GlobalDisplaySprite = this->GlobalDisplaySprite;
	if (SaveGame::CurrentMode == 0) {
		GlobalDisplaySprite = GlobalDisplaySpriteS3K;
	}
	// Score
	G->DrawSprite(GlobalDisplaySprite, 0, 0, STR_X, 12, 0, IE_NOFLIP);

	// Time
	G->DrawSprite(GlobalDisplaySprite, 0, 1, STR_X, 28, 0, IE_NOFLIP);

	// Rings
	int CurrentFrame = 3;
	if (Player->Rings == 0 && (this->Frame & 0xF) < 8)
		CurrentFrame = 4;
	G->DrawSprite(GlobalDisplaySprite, 0, CurrentFrame, STR_X, 44, 0, IE_NOFLIP);

	// Score value
	value = Score;
	for (int i = 0; i < 7 && (value > 0 || (value == 0 && i == 0)); i++) {
		G->DrawSprite(GlobalDisplaySprite, 1, value % 10, STR_X + 48 + 8 * 7 - 8 * i - 8, 12 + 14, 0, IE_NOFLIP);
		value /= 10;
	}

	// Timer " and '
	G->DrawSprite(GlobalDisplaySprite, 0, 12, STR_X + 48 + 8 * 1 - 8 + 3, 28 + 14 - 16, 0, IE_NOFLIP);

	// Timer value (Centiseconds)
	value = (Timer % 60) * 100 / 60;
	if (Timer >= 10 * 60 * 60 - 3)
		value = 99;
	for (int i = 0; i < 2; i++) {
		G->DrawSprite(GlobalDisplaySprite, 1, value % 10, STR_X + 48 + 8 * 7 - 8 * i - 8, 28 + 14, 0, IE_NOFLIP);
		value /= 10;
	}
	// Timer value (Seconds)
	value = (Timer / 60) % 60;
	for (int i = 0; i < 2; i++) {
		G->DrawSprite(GlobalDisplaySprite, 1, value % 10, STR_X + 48 + 8 * 4 - 8 * i - 9, 28 + 14, 0, IE_NOFLIP);
		value /= 10;
	}
	// Timer value (Minutes)
	value = (Timer / 60 / 60);
	if (value > 9)
		value = 9;
	G->DrawSprite(GlobalDisplaySprite, 1, value % 10, STR_X + 48 + 8 * 1 - 10, 28 + 14, 0, IE_NOFLIP);

	// Ring value (Or object count value in Debug mode.)
	if (!maxLayer) {
		value = ObjectCount;
	}
	else {
		value = Player->Rings;
	}

	for (int i = 0; i < 7 && (value > 0 || (value == 0 && i == 0)); i++) {
		G->DrawSprite(GlobalDisplaySprite, 1, value % 10, STR_X + 48 + 8 * 7 - 8 * i - 8, 44 + 14, 0, IE_NOFLIP);
		value /= 10;
	}

	int iconX = STR_X;
	int iconY = App->HEIGHT - 12;

	if (Mobile) {
		iconX = App->WIDTH - 64 - 8 - STR_X; // 24 is for Pause Button
		iconY = 12 + 17;
	}

	// Character Icon
	G->DrawSprite(GlobalDisplaySprite, 2, (int)Player->Character, iconX, iconY, 0, IE_NOFLIP);

	// x symbol
	if (SaveGame::CurrentMode == 1)
		G->DrawSprite(GlobalDisplaySprite, 0, 14, iconX, iconY, 0, IE_NOFLIP);

	// Lives value
	int LifeNumberAnim = 1;
	if (!SaveGame::CurrentMode == 1)
		LifeNumberAnim = 10;

	valen = 1;
	value = Player->Lives;
	if (value >= 10)
		valen = 2;
	if (value >= 99)
		value = 99;
	for (int i = 0; i < valen; i++) {
		G->DrawSprite(GlobalDisplaySprite, LifeNumberAnim, value % 10, iconX + 32 + 2 * 8 - i * 8, iconY, 0, IE_NOFLIP);
		value /= 10;
	}

	App->Input->UseTouchController = true;
	App->Input->CenterPauseButton = false;
	if (Mobile && !PauseFinished) {
		G->SetDrawAlpha(0xC0 - (0xC0 * ControlsAnim >> 8));
		int bX = 48;
		int bY = App->HEIGHT - 48;
		if (App->Input->GetControllerInput(0)[IInput::I_UP])
			G->DrawSprite(MobileButtonsSprite, 0, 1, bX, bY, 0, IE_NOFLIP);
		else if (App->Input->GetControllerInput(0)[IInput::I_DOWN])
			G->DrawSprite(MobileButtonsSprite, 0, 2, bX, bY, 0, IE_NOFLIP);
		else if (App->Input->GetControllerInput(0)[IInput::I_LEFT])
			G->DrawSprite(MobileButtonsSprite, 0, 3, bX, bY, 0, IE_FLIPX);
		else if (App->Input->GetControllerInput(0)[IInput::I_RIGHT])
			G->DrawSprite(MobileButtonsSprite, 0, 3, bX, bY, 0, IE_NOFLIP);
		else
			G->DrawSprite(MobileButtonsSprite, 0, 0, bX, bY, 0, IE_NOFLIP);

		// A button
		if (App->Input->GetControllerInput(0)[IInput::I_CONFIRM])
			G->SetDrawAlpha(0xFF);

		G->DrawSprite(MobileButtonsSprite, 0, 4, App->WIDTH - 48, bY, 0, IE_NOFLIP);
		G->SetDrawAlpha(0xFF);

		// Pause
		G->DrawSprite(MobileButtonsSprite, 0, 5, App->WIDTH - 22, 22, 0, IE_NOFLIP);
	}
}

PUBLIC void LevelScene::RenderTitleCard() {
	if (LevelCardHide)
		return;

	if (LevelCardTimer == 0.0) return;

	if (LevelCardTimer > 4.0)
		return;

	int redBar = (int)(G->easeOutQuad(IMath::clampDoubleDown(LevelCardTimer, 0.0, 0.5) / 0.5) * App->HEIGHT) - App->HEIGHT;
	int redBarOriginX = App->WIDTH / 2 - 75;
	int off = (int)(G->easeInQuad(IMath::clampDoubleDown(LevelCardTimer, 3.25, 3.5) / 0.25) * -App->HEIGHT);
	redBar += off;

	G->DrawRectangleSkewedH(
		redBarOriginX - App->HEIGHT + redBar, redBar,
		100, App->HEIGHT, App->HEIGHT, 0xEE0000);

	// G->DrawSprite(GlobalDisplaySprite, CurrentAnimation, CurrentFrame, redBarOriginX + 5 + redBar, 220 + redBar, 0, IE_NOFLIP);

	int text1Off = (int)(G->easeOutBack(IMath::clampDoubleDown(LevelCardTimer, 0.25, 0.75) / 0.5) * -400) + 400;
	int text2Off = (int)(G->easeOutBack(IMath::clampDoubleDown(LevelCardTimer, 0.35, 0.85) / 0.5) * -400) + 400;

	off = (int)(G->easeInBack(IMath::clampDoubleDown(LevelCardTimer, 3.25, 4.0) / 0.75) * 400);
	text1Off += off;
	text2Off += off;

	int textX, textY, textW;

	int ex = 0;

	for (size_t i = 0; i < strlen(LevelName); i++) {
		if (LevelName[i] == ' ') {
			ex += 16;
		}
		else {
			ISprite::AnimFrame Frame;
			Frame = GlobalDisplaySprite->Animations[15].Frames[LevelName[i] - 'A'];
			ex += Frame.W + 1;
		}
	}
	textW = ex;

	textX = App->WIDTH - 34 - textW + text1Off;
	textY = 100;

	G->DrawRectangleSkewedH(
		textX - 30, textY - 8,
		textW + 35, 27, 27, 0x222222);

	G->SetClip(textX - 25, textY - 24, textW + 25, 47);

	ex = 0;
	for (int i = 0; i < (int)strlen(LevelName); i++) {
		if (LevelName[i] == ' ') {
			ex += 16;
		}
		else {
			ISprite::AnimFrame Frame;
			Frame = GlobalDisplaySprite->Animations[15].Frames[LevelName[i] - 'A'];
			G->DrawSprite(GlobalDisplaySprite, 15, LevelName[i] - 'A', textX + ex + Frame.W / 2, textY, 0, IE_NOFLIP);

			ex += Frame.W + 1;
		}
	}

	G->ClearClip();

	//ACT NUMBER STUFF

	//Decoration
	G->DrawSprite(GlobalDisplaySprite, 14, (ZoneID-1), textX + 125, textY + 80, 0, IE_NOFLIP);
	//Act Number Sprite
	G->DrawSprite(GlobalDisplaySprite, 17, (VisualAct-1), textX + 125, textY + 80, 0, IE_NOFLIP);

	textY += 36;

	textX = App->WIDTH - 34 + 8 + text2Off;
	G->DrawRectangleSkewedH(
		textX - 25 - 32 * 4, textY - 5,
		128 + 25, 13, 13, 0xEEEEEE);

	for (int i = 0; i < 4; i++) {
		G->DrawSprite(GlobalDisplaySprite, 16, i, textX, textY, 0, IE_NOFLIP);
	}
}

PUBLIC void LevelScene::RenderPauseScreen() {
	if (!PauseFinished) {
		G->ClearClone();
		return;
	}

	// HACK: For when the Scene cleans up before we render PauseSprite for the last time
	if (!PauseSprite) return;

	paltimer++;
	if (paltimer > 1) {
		palframe += 1 + 18;
		palframe %= 18;
		paltimer = 0;
	}

	int paletteToCycle[9] = {
		0xEAD100,
		0xE4C700,
		0xE0BF00,
		0xDAB600,
		0xD6AE00,
		0xD1A500,
		0xCD9D00,
		0xC89400,
		0xC48C00,
		/*0xBE8200,
		0xB97A00,
		0xB47100,
		0xB06A00,
		0xAA6100,
		0xA65900,
		0xA15000,
		0x9D4800,
		0x993A00,//*/
	};

	int anim_off;

	for (int i = 0; i < 9; i++)
		PauseSprite->SetPalette(60 - i, paletteToCycle[(palframe - i + 9) % 9]);

	//White Tint
	G->SetDrawAlpha((int)((60 - pauseAnimTimer) * 2) < 0 ? 0 : (int)((60 - pauseAnimTimer) * 2)); //theres probably an easier way, dont care
	for (int i = 0; i < 45; i++) {
		G->DrawSprite(PauseSprite, 0, 0, 0, (15 * i) - pauseAnimTimer, 0, IE_NOFLIP);
	}
	G->SetDrawAlpha(0xFF);

	//Base Black BG
	G->DrawSprite(PauseSprite, 0, 2, 0, App->HEIGHT - PauseSprite->Animations[0].Frames[3].H + pauseAnimTimer, 0, IE_NOFLIP);
	//Top BG thingy
	G->DrawSprite(PauseSprite, 0, 2, 0, 23 - pauseAnimTimer, 0, IE_FLIPY);
	//G->DrawSprite(PauseSprite, 0, 2, 0, 0, 0, IE_NOFLIP);

	//Buttons
	//G->DrawSprite(PauseSprite, 0, 3, 0, App->HEIGHT - PauseSprite->Animations[0].Frames[3].H, 0, IE_NOFLIP);
	//G->DrawSprite(PauseSprite, 0, 3, 0, App->HEIGHT - PauseSprite->Animations[0].Frames[3].H, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 1, 0 + (PauseSelectedMenuItem == 0 ? 5 : 0), 81, 197 + pauseAnimTimer, 0, IE_NOFLIP); //Resume
	G->DrawSprite(PauseSprite, 1, 1 + (PauseSelectedMenuItem == 1 ? 5 : 0), 124, 197 + pauseAnimTimer, 0, IE_NOFLIP); //Restart
	G->DrawSprite(PauseSprite, 1, 2 + (PauseSelectedMenuItem == 2 ? 5 : 0), 167, 197 + pauseAnimTimer, 0, IE_NOFLIP); //Settings
	G->DrawSprite(PauseSprite, 1, 3 + (PauseSelectedMenuItem == 3 ? 5 : 0), 210, 197 + pauseAnimTimer, 0, IE_NOFLIP); //Exit
	G->DrawSprite(PauseSprite, 1, 4 + (PauseSelectedMenuItem == 4 ? 5 : 0), 253, 197 + pauseAnimTimer, 0, IE_NOFLIP); //Radio

	//Chaos Emeralds
	G->DrawSprite(PauseSprite, 3, 1 * (SaveGame::CurrentEmeralds >> 0 & 1), 297 + 8, 199 + 8 + pauseAnimTimer, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 3, 2 * (SaveGame::CurrentEmeralds >> 1 & 1), 314 + 8, 199 + 8 + pauseAnimTimer, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 3, 3 * (SaveGame::CurrentEmeralds >> 2 & 1), 331 + 8, 199 + 8 + pauseAnimTimer, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 3, 4 * (SaveGame::CurrentEmeralds >> 3 & 1), 348 + 8, 199 + 8 + pauseAnimTimer, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 3, 5 * (SaveGame::CurrentEmeralds >> 4 & 1), 365 + 8, 199 + 8 + pauseAnimTimer, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 3, 6 * (SaveGame::CurrentEmeralds >> 5 & 1), 382 + 8, 199 + 8 + pauseAnimTimer, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 3, 7 * (SaveGame::CurrentEmeralds >> 6 & 1), 399 + 8, 199 + 8 + pauseAnimTimer, 0, IE_NOFLIP);

	//Super Emeralds
	G->DrawSprite(PauseSprite, 2, 1 * (SaveGame::CurrentEmeralds >> 8 & 1), 297 + 8, 218 + 8 + pauseAnimTimer, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 2, 2 * (SaveGame::CurrentEmeralds >> 9 & 1), 314 + 8, 218 + 8 + pauseAnimTimer, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 2, 3 * (SaveGame::CurrentEmeralds >> 10 & 1), 331 + 8, 218 + 8 + pauseAnimTimer, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 2, 4 * (SaveGame::CurrentEmeralds >> 11 & 1), 348 + 8, 218 + 8 + pauseAnimTimer, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 2, 5 * (SaveGame::CurrentEmeralds >> 12 & 1), 365 + 8, 218 + 8 + pauseAnimTimer, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 2, 6 * (SaveGame::CurrentEmeralds >> 13 & 1), 382 + 8, 218 + 8 + pauseAnimTimer, 0, IE_NOFLIP);
	G->DrawSprite(PauseSprite, 2, 7 * (SaveGame::CurrentEmeralds >> 14 & 1), 399 + 8, 218 + 8 + pauseAnimTimer, 0, IE_NOFLIP);

	int xadj = 10;	
	//Player Heads
	if (SaveGame::CurrentPartnerFlag != 0xFF) {
		G->DrawSprite(PauseSprite, 4, SaveGame::CurrentPartnerFlag, 31, 215 + pauseAnimTimer, 0, IE_NOFLIP);
		xadj = 0;
	}
	G->DrawSprite(PauseSprite, 4, SaveGame::CurrentCharacterFlag, xadj + 1, 215 + pauseAnimTimer, 0, IE_NOFLIP);

	G->DrawSprite(PauseSprite, 0, 3, 148, 6 - pauseAnimTimer, 0, IE_NOFLIP); //"You are currently Paused"

	anim_off = 210 - PauseAnim[2] / 0x100;
	int baseX = 280 + anim_off;
	int baseY = 70 + 20;
	if (pauseAnimTimer != 0 && Paused) pauseAnimTimer -= 10;
	if (PauseMusicFade < 60) PauseMusicFade += 2;
	}

PUBLIC void LevelScene::RenderResults() {
	if (!ShowResults) return;

	int value;

	double resultsTimer = ResultsTimer / 60.0;

	int anim_player_got;
	int anim_through_act;
	int anim_time_bonus;
	int anim_ring_bonus;
	int anim_total;

	if (ResultsTimer > 390) {
		resultsTimer = (60 - (ResultsTimer - 390)) / 60.0;
	}

	anim_player_got = (int)(G->easeOutQuad(IMath::clampDoubleDown(resultsTimer, 0.0, 0.4) / 0.4) * App->WIDTH) - App->WIDTH;
	anim_through_act = (int)(G->easeOutQuad(IMath::clampDoubleDown(resultsTimer, 0.2, 0.6) / 0.4) * -App->WIDTH) + App->WIDTH;
	anim_time_bonus = (int)(G->easeOutQuad(IMath::clampDoubleDown(resultsTimer, 0.5, 0.8) / 0.3) * -App->WIDTH) + App->WIDTH;
	anim_ring_bonus = (int)(G->easeOutQuad(IMath::clampDoubleDown(resultsTimer, 0.6, 0.9) / 0.3) * -App->WIDTH) + App->WIDTH;
	anim_total = (int)(G->easeOutQuad(IMath::clampDoubleDown(resultsTimer, 0.7, 1.0) / 0.3) * -App->WIDTH) + App->WIDTH;

	ISprite* GlobalDisplaySprite = this->GlobalDisplaySprite;

	//NOTE: the S3 sheet doesn't have a title card number thing

	//if (GlobalDisplaySpriteS3K) {
	//	GlobalDisplaySprite = GlobalDisplaySpriteS3K;
	//}

	// Player Name
	G->DrawSprite(GlobalDisplaySprite, 3, (int)Player->Character, App->WIDTH / 2 + anim_player_got, 64, 0, IE_NOFLIP);

	// Got
	G->DrawSprite(GlobalDisplaySprite, 4, 0, App->WIDTH / 2 + anim_player_got, 64, 0, IE_NOFLIP);

	// Through
	G->DrawSprite(GlobalDisplaySprite, 4, 1, App->WIDTH / 2 + anim_through_act, 88, 0, IE_NOFLIP);

	//Act (Number)
	G->DrawSprite(GlobalDisplaySprite, 17, (VisualAct - 1), App->WIDTH / 2 + anim_through_act + 75, 88, 0, IE_NOFLIP);

	// Time Bonus
	G->DrawSprite(GlobalDisplaySprite, 0, 1, App->WIDTH / 2 - 128 + anim_time_bonus, 128, 0, IE_NOFLIP);
	G->DrawSprite(GlobalDisplaySprite, 0, 8, App->WIDTH / 2 - 128 + 40 + anim_time_bonus, 128, 0, IE_NOFLIP);

	// Ring Bonus
	G->DrawSprite(GlobalDisplaySprite, 0, 5, App->WIDTH / 2 - 128 + anim_ring_bonus, 144, 0, IE_NOFLIP);

	G->DrawSprite(GlobalDisplaySprite, 0, 8, App->WIDTH / 2 - 128 + 40 + anim_ring_bonus, 144, 0, IE_NOFLIP);

	// Total
	G->DrawSprite(GlobalDisplaySprite, 0, 9, App->WIDTH / 2 - 112 + anim_total, 176, 0, IE_NOFLIP);

	// Time Bonus Value
	value = TimerTotal;
	for (int i = 0; i < 7 && (value > 0 || (value == 0 && i == 0)); i++) {
		G->DrawSprite(GlobalDisplaySprite, 1, value % 10, App->WIDTH / 2 + 112 - i * 8 - 4 + anim_time_bonus, 128 + 14, 0, IE_NOFLIP);
		value /= 10;
	}

	// Ring Bonus Value
	value = Player->Rings * 100;
	for (int i = 0; i < 7 && (value > 0 || (value == 0 && i == 0)); i++) {
		G->DrawSprite(GlobalDisplaySprite, 1, value % 10, App->WIDTH / 2 + 112 - i * 8 - 4 + anim_ring_bonus, 144 + 14, 0, IE_NOFLIP);
		value /= 10;
	}

	// Total Value
	value = TotalToAdd;
	for (int i = 0; i < 7 && (value > 0 || (value == 0 && i == 0)); i++) {
		G->DrawSprite(GlobalDisplaySprite, 1, value % 10, App->WIDTH / 2 + 112 - i * 8 - 4 + anim_total, 176 + 14, 0, IE_NOFLIP);
		value /= 10;
	}
}

PUBLIC VIRTUAL void LevelScene::RenderAboveBackground() {
}

PUBLIC VIRTUAL void LevelScene::RenderAboveForeground() {
}

PUBLIC void LevelScene::DrawThing(int l) {
	//Layer layer = Data->Layers[l];
	//int EndTileBaseX, EndTileBaseY;
	//int index, TileBaseX, TileBaseY, split, extra, tileHeight, TileSel, TileSelBoost;
}

PUBLIC VIRTUAL void LevelScene::RenderEverything() {
	// TODO: Optimize

	G->DrawRectangle(0, 0, App->WIDTH, App->HEIGHT, BackgroundColor);
	G->WaterPaletteStartLine = VisualWaterLevel - CameraY;

	int highlightedTile = -1;

	Layer layer;
	int fullFlip;
	int s, siT, x, y;
	int tile, flipX, flipY, baseX, baseY, wheree;
	int index, TileBaseX, TileBaseY;
	// int EndTileBaseX, EndTileBaseY;

	//Lazy but works
	TileSprite->SetTransparentColorIndex(0);

	for (int l = 0; l < Data->layerCount; l++) {
		y = 0;

		layer = Data->Layers[l];

		// Draw Tiles
		if (layer.Visible) {
			G->DoDeform = true;
			memcpy(G->DeformX, layer.DeformX, App->HEIGHT);
			memcpy(G->DeformY, layer.DeformY, App->WIDTH);
			if (layer.InfoCount > 1) {
				int buf = 0;
				for (s = 0; s < layer.ScrollIndexCount; s++) {
					index = layer.ScrollIndexes[s].Index;

					int heightSize, tilindx, tilindy, tilindpos, word, fBX;
					for (siT = 0; siT < layer.ScrollIndexes[s].Size; siT += heightSize) {
						heightSize = 16;
						if (heightSize > layer.ScrollIndexes[s].Size - siT)
							heightSize = layer.ScrollIndexes[s].Size - siT;
						if (heightSize > ((y + siT + 0x10) & ~0xF) - (y + siT)) // Rounded-up
							heightSize = ((y + siT + 0x10) & ~0xF) - (y + siT);

						if (layer.UseDeltaCameraX)
							TileBaseX = (CameraDeltaX * layer.Info[index].RelativeX + layer.Info[index].ConstantX * Frame) >> 8;
						else
							TileBaseX = (CameraX * layer.Info[index].RelativeX + layer.Info[index].ConstantX * Frame) >> 8;

						TileBaseY = y + siT;
						if (layer.UseDeltaCameraY)
							TileBaseY -= (CameraDeltaY * layer.RelativeY + layer.ConstantY * Frame) >> 8;
						else
							TileBaseY -= (CameraY * layer.RelativeY + layer.ConstantY * Frame) >> 8;

						TileBaseX -= layer.OffsetX;
						TileBaseY -= layer.OffsetY;

						int bufVal = 0;
						if (TileBaseY + heightSize > 0 && TileBaseY < App->HEIGHT) {
							bufVal = layer.Width * 16;
							fBX = (((-TileBaseX) % bufVal + bufVal) % bufVal);

							for (x = (TileBaseX >> 4) - 1; x < 2 + ((TileBaseX + App->WIDTH) >> 4); x++) {
								tilindy = ((y + siT) >> 4);
								tilindy = (tilindy % layer.Height + layer.Height) % layer.Height; // so it loops
								tilindx = ((x % layer.Width + layer.Width) % layer.Width);
								tilindpos = tilindx + (tilindy)* layer.Width;

								baseX = (x << 4) - TileBaseX;
								baseY = TileBaseY;

								word = layer.Tiles[tilindpos];
								fullFlip = (word >> 10) & 3;
								tile = word & 0x3FF;

								if (tile != BlankTile) {
									int anID = Data->IsAnims[tile] & 0xFF;

									if (anID != 0xFF) {
										G->DrawSprite(AnimTileSprite, Data->IsAnims[tile] >> 8, Data->animatedTileFrames[anID], baseX + 8, baseY + 8, 0, fullFlip);
									}
									else {
										// tilindx + buf * layer.Width
										if (layer.ScrollIndexes[0].TileBuffers && layer.ScrollIndexes[0].TileBuffers[buf] > 0) {
											if (bufVal != 0)
												G->DrawSpriteListBuffer(TileSprite,
													layer.ScrollIndexes[0].TileBuffers[buf], layer.Width,
													fBX + 8, baseY + heightSize / 2);
											G->DrawSpriteListBuffer(TileSprite,
												layer.ScrollIndexes[0].TileBuffers[buf], layer.Width,
												fBX + 8 - bufVal, baseY + heightSize / 2);
											// G->DrawSpriteListBuffer(TileSprite,
											//     layer.ScrollIndexes[0].TileBuffers[buf], layer.Width,
											//     fBX + 8 + bufVal, baseY + heightSize / 2);

											// G->DrawSpriteBuffered(TileSprite,
											//     layer.ScrollIndexes[0].TileBuffers[buf], // bufVal,
											//     // baseX + 8, baseY + heightSize / 2, 0, bufVal);//fullFlip);
											//     TileBaseX + 8, baseY + heightSize / 2, 0, bufVal);//fullFlip);

											bufVal = 0;
										}
										else {
											flipY = ((fullFlip >> 1) & 1);

											wheree = (y + siT) & 0xF;
											if (flipY)
												wheree = 0x10 - wheree - heightSize;

											if (TileSprite->Width > 16)
												G->DrawSprite(TileSprite, ((tile & 0x1F) << 4), wheree + ((tile >> 5) << 4), 16, heightSize, baseX + 8, baseY + heightSize / 2, 0, fullFlip, -8, -heightSize / 2 - (heightSize & flipY));
											else
												G->DrawSprite(TileSprite, 0, wheree + (tile << 4), 16, heightSize, baseX + 8, baseY + heightSize / 2, 0, fullFlip, -8, -heightSize / 2 - (heightSize & flipY));
										}
									}
								}
							}
						}

						buf++;
					}
					y += layer.ScrollIndexes[s].Size;
				}
			}
			else {
				if (layer.Info[0].Behaviour == 1) {
					if (ManiaLevel)
						G->DoDeform = true;
				}

				if (layer.UseDeltaCameraX)
					TileBaseX = (CameraDeltaX * layer.Info[0].RelativeX + layer.Info[0].ConstantX * Frame) >> 8;
				else
					TileBaseX = (CameraX * layer.Info[0].RelativeX + layer.Info[0].ConstantX * Frame) >> 8;

				if (layer.UseDeltaCameraY)
					TileBaseY = (CameraDeltaY * layer.RelativeY + layer.ConstantY * Frame) >> 8;
				else
					TileBaseY = (CameraY * layer.RelativeY + layer.ConstantY * Frame) >> 8;

				TileBaseX -= layer.OffsetX;
				TileBaseY -= layer.OffsetY;

				// EndTileBaseX = 2 + ((TileBaseX + App->WIDTH) >> 4);
				// EndTileBaseY = 2 + ((TileBaseY + App->HEIGHT) >> 4);

				//int lWid = layer.Width;

				// int j;
				// int bufVal;
				int tBX = (TileBaseX >> 4) - 1;
				int tBW = 3 + (App->WIDTH >> 4);
				int tBH = 2 + (App->HEIGHT >> 4);
				int ix = tBX,
					iy = (TileBaseY >> 4),
					fx = 0,
					fy = 0,
					// th = (TileBaseY >> 4) + tBH,
					tw = tBX + tBW;
				int fullSize = tBW * tBH;
				int anID;
				for (int w = 0; w < fullSize; w++) {
					fx = ix;
					fy = iy;
					if (layer.Flags & 0x2) {
						if (fx < 0) {
							// Increment
							ix++;
							if (ix >= tw) {
								ix = tBX;
								iy++;
							}
							continue;
						}
						if (fx >= layer.Width) {
							// Increment
							ix++;
							if (ix >= tw) {
								ix = tBX;
								iy++;
							}
							continue;
						}
					}
					if (layer.Flags & 0x4) {
						if (fy < 0) {
							// Increment
							ix++;
							if (ix >= tw) {
								ix = tBX;
								iy++;
							}
							continue;
						}
						if (fy >= layer.Height) {
							// Increment
							ix++;
							if (ix >= tw) {
								ix = tBX;
								iy++;
							}
							continue;
						}
					}

					while (fx < 0) fx += layer.Width;
					while (fx >= layer.Width) fx -= layer.Width;

					while (fy < 0) fy += layer.Height;
					while (fy >= layer.Height) fy -= layer.Height;

					baseX = (ix << 4) - TileBaseX;
					baseY = (iy << 4) - TileBaseY + layer.TileOffsetY[fx];

					tile = layer.Tiles[fx + fy * layer.Width];
                    
                    bool ColFlipX = ((tile >> 10) & 1) == 1;
                    bool ColFlipY = ((tile >> 11) & 1) == 1;
                    bool SolidTopA = ((tile >> 12) & 1) == 1;
                    bool SolidLrbA = ((tile >> 13) & 1) == 1;
                    bool SolidTopB = ((tile >> 14) & 1) == 1;
                    bool SolidLrbB = ((tile >> 15) & 1) == 1;

					int colTypeA = ((tile >> 12) & 3);
					int colTypeB = ((tile >> 14) & 3);

					fullFlip = (tile >> 10) & 3;
					tile = tile & 0x3FF;

					if (tile != BlankTile) {
						anID = Data->IsAnims[tile] & 0xFF;
						if (anID != 0xFF) {
							G->DrawSprite(AnimTileSprite, Data->IsAnims[tile] >> 8, Data->animatedTileFrames[anID], baseX + 8, baseY + 8, 0, fullFlip);
						} else {
							G->DrawSprite(TileSprite, 0, tile, baseX + 8, baseY + 8, 0, fullFlip);
                        }

						if (ViewTileCollision) {
							for (int c = 0; c < 16; c++) {
								int eex = c;
								if (ColFlipX) {
									eex = 15 - c;
                                }

								int h1 = Data->tiles1[tile].Collision[c];
								int h2 = Data->tiles2[tile].Collision[c];

								if (BlankTile == 0x3FF && (Data->tiles1[tile].IsCeiling || Data->tiles2[tile].IsCeiling)) {
									h1 = 15 - h1;
									h2 = 15 - h2;
								}

								// Yellow - Tiles that are solid from the top. Used for platforms.
								// Red - Tiles that are solid from the bottom and sides. Usually for walls and ceilings.
								// White - Tiles that are solid all over. Usually for the ground.

								if (Player->Layer == 0 && (colTypeA & 1)) {
									//uint32_t col = colTypeB == 3 ? 0 : colTypeB == 2 ? 0xFFFF00 : 0xFFFFFF;
                                    uint32_t col = (SolidTopA && SolidLrbA) ? 0xFFFFFF : (SolidLrbA && !SolidTopA) ? 0xFF0000 : 0xFFFF00;

									if (Data->tiles1[tile].HasCollision[c]) {
										if (Data->tiles1[tile].IsCeiling ^ ColFlipY) {
											G->DrawRectangle(baseX + eex, baseY, 1, 16 - h1, col);
										} else {
											G->DrawRectangle(baseX + eex, baseY + h1, 1, 16 - h1, col);
										}
									}
								} else if (Player->Layer == 1 && (colTypeB & 1)) {
									if (Data->tiles2[tile].HasCollision[c]) {
										uint32_t col = (SolidTopB && SolidLrbB) ? 0xFFFFFF : (SolidLrbB && !SolidTopB) ? 0xFF0000 : 0xFFFF00;

										if (Data->tiles2[tile].IsCeiling ^ ColFlipY) {
											G->DrawRectangle(baseX + eex, baseY, 1, 16 - h2, col);
										} else {
											G->DrawRectangle(baseX + eex, baseY + h2, 1, 16 - h2, col);
										}
									}
								}
							}

							int mx = App->Input->MouseX;
							int my = App->Input->MouseY;
							if (mx >= baseX && my >= baseY && mx < baseX + 16 && my < baseY + 16) {
							}
						}
					}

					ix++;
					if (ix >= tw) {
						ix = tBX;
						iy++;
					}
				}

				if (layer.Info[0].Behaviour) {
					if (ManiaLevel)
						G->DoDeform = false;
				}
			}
		}

		// Rendering above background
		
		if (l == Data->CameraLayer - 1)
			RenderAboveBackground();
		//

		G->DoDeform = DeformObjects;

		// Rendering objects
		for (int i = 0; i < ObjectCount; i++) {
			Object* obj = Objects[i];
			if (obj == NULL) continue;

			if (obj->Active && obj->OnScreen) {
				if (l == Data->CameraLayer + obj->VisualLayer) {
					obj->DrawCollisions = App->viewObjectCollision;
                    if ((obj->BinIndex >= 0 && obj->BinIndex < SpriteBinMapIDs.size()) && SpriteBinMapIDs.at(obj->BinIndex) != obj->Sprite) {
                        obj->Sprite = SpriteBinMapIDs.at(obj->BinIndex);
                    }
					obj->Render(CameraX, CameraY);
				}
			}
		}

		// Rendering rings
		if (l == Data->CameraLayer) {
			RenderRings();
		}

		// Rendering temporary sprites
		for (vector<Object*>::iterator it = TempObjects.begin(); it != TempObjects.end(); ++it) {
			if ((*it)->Active) {
				if (l == Data->CameraLayer + (*it)->VisualLayer) {
					(*it)->Render(CameraX, CameraY);
                }
            }
		}

		// Rendering temporary tile sprites
		for (vector<Object*>::iterator it = TempObjectTiles.begin(); it != TempObjectTiles.end(); ++it) {
			if ((*it)->Active) {
				if (l == Data->CameraLayer + (*it)->VisualLayer) {
					(*it)->Render(CameraX, CameraY);
                }
            }
		}

		G->DoDeform = DeformPlayer;

		// Rendering players
		for (int p = PlayerCount - 1; p >= 0; p--) {
			if (l == Data->CameraLayer + Players[p]->VisualLayer)
				Players[p]->Render(CameraX, CameraY);
		}

		// Rendering above foreground
		/*
		if (l == Data->layerCount - 1)
			RenderAboveForeground();
		//*/
	}

	G->DoDeform = false;

	G->DrawModeOverlay = true;
	switch (ZoneID)
	{
	case 1:
	case 4:
	case 5:
		G->SetDrawAlpha(0x40);
		break;
	case 2:
	case 6:
		G->SetDrawAlpha(0x80);
		break;
	default:
		G->SetDrawAlpha(0x00);
		break;
	}
	if (WaterLevel - CameraY >= -16 &&
		WaterLevel - CameraY < App->HEIGHT + 16) {
		for (int x = CameraX; x <= CameraX + App->WIDTH + 32; x += 32) {
			G->DrawSprite(WaterSprite, 0, WaterAnimationFrame >> 8,
				(x & 0xFFFFFE0) - CameraX, WaterLevel - CameraY, 0, IE_NOFLIP);
		}
	}
	G->DrawModeOverlay = false;
	G->SetDrawAlpha(0xFF);
	RenderHUD();

	if (!ViewPlayerUpdateStats && !maxLayer) {
		int Y = 0;
		size_t strSize1, strSize2, strSizeFinal;
		char tempStr1_X[128], tempStr1_Y[128], tempStr2_X[128], tempStr2_Y[128];

		sprintf(tempStr1_X, "%04X", (Player->EZX < 0) ? -Player->EZX : Player->EZX);
		sprintf(tempStr1_Y, "%04X", (Player->EZY < 0) ? -Player->EZY : Player->EZY);
		strSize1 = strlen(tempStr1_X) + strlen(tempStr1_Y);

		sprintf(tempStr2_X, "%04X", CameraX < 0 ? -CameraX : CameraX);
		sprintf(tempStr2_Y, "%04X", CameraY < 0 ? -CameraY : CameraY);
		strSize2 = strlen(tempStr2_X) + strlen(tempStr2_Y);

		strSizeFinal = std::max(strSize1, strSize2);

		if (Player->EZY >= WaterLevel) {
			G->DrawRectangle(59, 10, 8 * strSizeFinal, 16, TileSprite->GetPaletteAlt(31));
		}
		else {
			G->DrawRectangle(59, 10, 8 * strSizeFinal, 16, TileSprite->GetPalette(31));
		}

		G->DrawTextShadow(59, Y + 10, tempStr1_X, (Player->EZX < 0) ? 0xFF0000 : 0xFFFFFF);
		G->DrawTextShadow(59 + (8 * strlen(tempStr1_X)), Y + 10, tempStr1_Y, (Player->EZY < 0) ? 0xFF0000 : 0xFFFFFF);
		Y += 8;
		G->DrawTextShadow(59, Y + 10, tempStr2_X, (CameraX < 0) ? 0xFF0000 : 0xFFFFFF);
		G->DrawTextShadow(59 + (8 * strlen(tempStr2_X)), Y + 10, tempStr2_Y, (CameraY < 0) ? 0xFF0000 : 0xFFFFFF);
	}

	if (ViewPalettes) {
		char palettetitle[16];
		sprintf(palettetitle, "Normal");
		G->DrawTextShadow(App->WIDTH - 132, App->HEIGHT - 74, palettetitle, 0xFFFFFF);

		sprintf(palettetitle, "Alt");
		G->DrawTextShadow(App->WIDTH - 64, App->HEIGHT - 74, palettetitle, 0xFFFFFF);

		for (int i = 0; i < 256; i++) {
			G->DrawRectangle(App->WIDTH - 132 + ((i & 0xF) << 2), App->HEIGHT - 64 + ((i >> 4) << 2), 4, 4, TileSprite->GetPalette(i));

			G->DrawRectangle(App->WIDTH - 64 + ((i & 0xF) << 2), App->HEIGHT - 64 + ((i >> 4) << 2), 4, 4, TileSprite->GetPaletteAlt(i));
		}

		for (int i = 0; i < 256; i++) {
			G->DrawRectangle(App->WIDTH - 132 + ((i & 0xF) << 2), App->HEIGHT - 64 + ((i >> 4) << 2) - 96, 4, 4, Player->Sprites[0]->GetPalette(i));

			G->DrawRectangle(App->WIDTH - 64 + ((i & 0xF) << 2), App->HEIGHT - 64 + ((i >> 4) << 2) - 96, 4, 4, Player->Sprites[0]->GetPaletteAlt(i));
		}
	}
	if (ViewPathswitchers) {
		for (int i = 0; i < PlaneSwitchCount; i++) {
			//int Len = 16 * PlaneSwitchers[i].Size + 16; // this is the real len, below is radius
			int Len = 8 * PlaneSwitchers[i].Size + 8;

			float cos_ = Player->Sin[PlaneSwitchers[i].Angle];
			float sin_ = Player->Cos[PlaneSwitchers[i].Angle];

			int cos_t = int(cos_ * Len);
			int sin_t = int(sin_ * Len);

			int ox = PlaneSwitchers[i].X;
			int oy = PlaneSwitchers[i].Y;

			int px = int(ox + sin_ * 8);
			int py = int(oy + cos_ * 8);

			G->DrawLine(
				px - cos_t - CameraX,
				py - sin_t - CameraY,
				px + cos_t - CameraX,
				py + sin_t - CameraY, ((PlaneSwitchers[i].Flags >> 3) & 1) ? 0xFF0000 : 0x0000FF);

			px = int(ox + sin_ * 6);
			py = int(oy + cos_ * 6);

			G->DrawLine(
				px - cos_t - CameraX,
				py - sin_t - CameraY,
				px + cos_t - CameraX,
				py + sin_t - CameraY, ((PlaneSwitchers[i].Flags >> 2) & 1) ? 0xFF0000 : 0x0000FF);

			px = int(ox + sin_ * -8);
			py = int(oy + cos_ * -8);

			G->DrawLine(
				px - cos_t - CameraX,
				py - sin_t - CameraY,
				px + cos_t - CameraX,
				py + sin_t - CameraY, ((PlaneSwitchers[i].Flags >> 1) & 1) ? 0xFF0000 : 0x0000FF);

			px = int(ox + sin_ * -6);
			py = int(oy + cos_ * -6);

			G->DrawLine(
				px - cos_t - CameraX,
				py - sin_t - CameraY,
				px + cos_t - CameraX,
				py + sin_t - CameraY, ((PlaneSwitchers[i].Flags) & 1) ? 0xFF0000 : 0x0000FF);

			char ghgh[3];
			sprintf(ghgh, "%02X", PlaneSwitchers[i].Angle & 0xFF);
			G->DrawTextShadow(PlaneSwitchers[i].X - 8 - CameraX, PlaneSwitchers[i].Y - CameraY - 4, ghgh, PlaneSwitchers[i].OnPath ? 0xF2D141 : 0xFFFFFF);
	
			int W = 16 * PlaneSwitchers[i].Size;
			int H = 16 * PlaneSwitchers[i].Size;
			int rnd = (PlaneSwitchers[i].Angle & 0xC0);
			if (rnd == 0x00 ||
				rnd == 0x80) {
				W = 16;
			}
			else {
				H = 16;
			}

			if (rnd != PlaneSwitchers[i].Angle)
				continue; // just don't even deal with angles like these tbh

			G->SetDrawAlpha(0x80);
			G->DrawRectangle(PlaneSwitchers[i].X - (W / 2) - CameraX, PlaneSwitchers[i].Y - (H / 2) - CameraY, W, H, 0xCC53D1);
			G->SetDrawAlpha(0xFF);
		}
	}
	if (ViewPlayerStats) {
		int Y = 0;

		if (ViewPlayerUpdateStats) {
			char tempStr[256];
			G->DrawRectangle(0, 0, 200, 35, 0);
			for (int i = 0; i < PlayerCount; i++) {
				sprintf(tempStr, "Player %d Update: %0.2f ms", i, playerUpdateTimers[i]);
				G->DrawTextShadow(0, Y, tempStr, 0xFFFFFF);
				Y += 8;
				sprintf(tempStr, "    Late Update: %0.2f ms", playerLateUpdateTimers[i]);
				G->DrawTextShadow(0, Y, tempStr, 0xFFFFFF);
				Y += 8;
				Y += 2;
			}
		}

		int16_t X = Player->EZX;
		Y = Player->EZY;

		Y -= 32;
		char pooerp[256];

		if (X < CameraX)
			X = CameraX;
		if (Y < CameraY)
			Y = CameraY;

		///*
		sprintf(pooerp, "%04X %04X (%02X %d)", Player->EZX, Player->EZY, Player->Angle, Player->AngleMode);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFFFFFF);
		Y += 8;

		sprintf(pooerp, "%04X %04X", CameraX, CameraY);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFFFFFF);
		Y += 8;

		sprintf(pooerp, "%04X %04X", Player->CameraX, Player->CameraY);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFFFFFF);
		Y += 8;

		sprintf(pooerp, "Sensor A: %d", Player->SensorA);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0x00FF00);
		Y += 8;

		sprintf(pooerp, "Sensor B: %d", Player->SensorB);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0x00FF99);
		Y += 8;

		sprintf(pooerp, "Sensor C: %d", Player->SensorC);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0x0099FF);
		Y += 8;

		sprintf(pooerp, "Sensor D: %d", Player->SensorD);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFFFF00);
		Y += 8;

		sprintf(pooerp, "Sensor E: %d", Player->SensorE);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFF00FF);
		Y += 8;

		sprintf(pooerp, "Sensor F: %d", Player->SensorF);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFF4444);
		Y += 8;

		sprintf(pooerp, "Ground: %s", Player->Ground ? "TRUE" : "FALSE");
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFFFFFF);
		Y += 8;

		sprintf(pooerp, "GSP: %X", Player->GroundSpeed);
		if (Player->GroundSpeed >= 0)
			sprintf(pooerp, "GSP: %X", Player->GroundSpeed);
		else
			sprintf(pooerp, "GSP: -%X", -Player->GroundSpeed);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFFFFFF);
		Y += 8;

		sprintf(pooerp, "Action: %X", (int)Player->Action);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFFFFFF);
		Y += 8;

		if (Player->XSpeed >= 0)
			sprintf(pooerp, "XSP: %X", Player->XSpeed);
		else
			sprintf(pooerp, "XSP: -%X", -Player->XSpeed);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFF4444);
		Y += 8;

		if (Player->YSpeed >= 0)
			sprintf(pooerp, "YSP: %X", Player->YSpeed);
		else
			sprintf(pooerp, "YSP: -%X", -Player->YSpeed);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0x8888FF);
		Y += 8;

		sprintf(pooerp, "Layer: %d", Player->Layer);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFFFFFF);
		Y += 8;

		sprintf(pooerp, "Frame: %d", Player->CurrentFrame / 0x100);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFFFFFF);
		Y += 8;

		sprintf(pooerp, "UnderwaterTimer: %X", Player->UnderwaterTimer);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFFFFFF);
		Y += 8;
		//*/

		sprintf(pooerp, "LevelTriggerFlag: %X", LevelTriggerFlag);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFFFFFF);
		Y += 8;
		sprintf(pooerp, "RoutineNumber: %X", RoutineNumber);
		G->DrawTextShadow(X - CameraX + 37 - 1, Y - CameraY - 1, pooerp, 0xFFFFFF);
		Y += 8;
	}
	if (ViewTileInfo) {
		int ang = IMath::atanHex(App->Input->MouseX - App->WIDTH / 2, App->Input->MouseY - App->HEIGHT / 2);

		char poop[50];
		sprintf(poop, "Angle %02X", ang);
		G->DrawTextShadow(4, 120, poop, 0xFFFF00);

		G->DrawLine(App->WIDTH / 2, App->HEIGHT / 2, App->WIDTH / 2 + (IMath::cosHex(Frame >> 2) >> 11), App->HEIGHT / 2 + (IMath::sinHex(Frame >> 2) >> 11), 0xFFFFFF);
		G->DrawLine(App->WIDTH / 2, App->HEIGHT / 2, App->WIDTH / 2 + (IMath::cosHex(ang) >> 10), App->HEIGHT / 2 + (IMath::sinHex(ang) >> 10), 0xFF00FF);

		G->DrawLine(App->Input->MouseX - 10, App->Input->MouseY - 10, App->Input->MouseX + 10, App->Input->MouseY + 10, 0xFF0000);
		G->DrawLine(App->Input->MouseX + 10, App->Input->MouseY - 10, App->Input->MouseX - 10, App->Input->MouseY + 10, 0xFF0000);

		int mx = App->Input->MouseX + CameraX;
		int my = App->Input->MouseY + CameraY;
		if (maxLayer) {
			//mx += 8;
			//my += 8;

			mx &= ~0xF;
			my &= ~0xF;
		}
		if (App->Input->MousePressed) {
			DEBUG_MOUSE_X = mx;
			DEBUG_MOUSE_Y = my;
		}
		else  if (App->Input->MouseReleased) {
			DEBUG_MOUSE_X = -1;
			DEBUG_MOUSE_Y = -1;
		}
		if (DEBUG_MOUSE_X == -1) {
			sprintf(poop, "X %d Y %d (%04X %04X)", mx, my, mx, my);
		}
		else {
			sprintf(poop, "X %d Y %d (%d %d)", mx, my, mx - DEBUG_MOUSE_X, my - DEBUG_MOUSE_Y);
			G->DrawRectangleStroke(DEBUG_MOUSE_X - CameraX, DEBUG_MOUSE_Y - CameraY, mx - DEBUG_MOUSE_X, my - DEBUG_MOUSE_Y, 0xFF00FF);
		}

		int dx = App->Input->MouseX;
		if (dx + (int)strlen(poop) * 8 >= App->WIDTH - 3)
			dx = App->WIDTH - 3 - strlen(poop) * 8;
		//G->DrawTextShadow(dx, App->Input->MouseY - 8, poop, 0xFFFFFF);

		mx >>= 4;
		my >>= 4;
		for (int l = 0; l < Data->layerCount; l++) {
			Layer layer = Data->Layers[l];
			int tile = layer.Tiles[mx + my * layer.Width];
			// bool flipX = ((tile >> 10) & 1);
			// bool flipY = ((tile >> 11) & 1);
			tile = tile & 0x3FF;

			sprintf(poop, "%s: %04X", layer.Name, tile);
			G->DrawTextShadow(0, l * 8, poop, 0xFFFFFF);
		}
	}

	if (highlightedTile > 0) {
		int which[4];

		which[0] = Data->tiles1[highlightedTile].Config[0];
		which[1] = Data->tiles1[highlightedTile].Config[1];
		which[2] = Data->tiles1[highlightedTile].Config[2];
		which[3] = Data->tiles1[highlightedTile].Config[3];

		if (which[1] >= 0xC0 && which[1] > 0xD0) which[1] = 0xC0;

		char tex[7];
		sprintf(tex, "%02X %02X %02X %02X",
			which[0],
			which[1],
			which[2],
			which[3]);
		G->DrawTextShadow(64, 64, tex, (Data->tiles1[highlightedTile].IsCeiling ? 0xF2D141 : 0xFFFFFF) - (flipY ? 0xD100 : 0));
	}

	RenderResults();

	int filTemp = G->GetFilter();
	G->SetFilter(0);
	RenderTitleCard();
	G->SetFilter(filTemp);
}

PUBLIC VIRTUAL void LevelScene::Render() {
	if (App->NextScene) return;

	int tCamY = CameraY;
	if (Data) {
		if (CameraX < 0)
			CameraX = 0;
		if (!Data->Layers[Data->CameraLayer].IsScrollingVertical && CameraY < 0)
			CameraY = 0;

		if (ShakeTimer > 0) {
			int Shaking[0x14] = {
				1, -1, 1, -1,
				2, -2, 2, -2,
				3, -3, 3, -3,
				4, -4, 4, -4,
				5, -5, 5, -5
			};
			CameraY = tCamY + Shaking[ShakeTimer];
		}
		else if (ShakeTimer < 0) {
			int Shaking[0x40] = {
				1,  2,  1,  3,  1,  2,  2,  1,  2,  3,  1,  2,  1,  2,  0,  0,
				2,  0,  3,  2,  2,  3,  2,  2,  1,  3,  0,  0,  1,  0,  1,  3,
				1,  2,  1,  3,  1,  2,  2,  1,  2,  3,  1,  2,  1,  2,  0,  0,
				2,  0,  3,  2,  2,  3,  2,  2,  1,  3,  0,  0,  1,  0,  1,  3
			};
			CameraY = tCamY + Shaking[Frame & 0x3F];
		}
		if (!Data->Layers[Data->CameraLayer].IsScrollingVertical && CameraY > Data->Layers[Data->CameraLayer].Height * 16 - App->HEIGHT)
			CameraY = CameraY & Data->Layers[Data->CameraLayer].Height * 16 - App->HEIGHT;
	}

	if (FadeAction != 0)
		G->SetFilter(G->GetFilter() | IE_FILTER_FADEABLE);
	else
		G->SetFilter(G->GetFilter() & ~IE_FILTER_FADEABLE);

	if (!G->HaveClone) {
		//G->SetFilter(G->GetFilter() | PauseFinished);
		RenderEverything();
		//G->SetFilter(G->GetFilter() & ~PauseFinished);
	}
	else {
		G->DrawClone();
	}

	CameraY = tCamY;

	RenderPauseScreen();

	if (ViewTileCollision) {
		bool col = CollisionAt(CameraX + App->Input->MouseX, CameraY + App->Input->MouseY);
		G->DrawRectangle(App->Input->MouseX - 7, App->Input->MouseY, 15, 1, col ? 0x00FF00 : 0xFF00FF);
		G->DrawRectangle(App->Input->MouseX, App->Input->MouseY - 7, 1, 15, col ? 0x00FF00 : 0xFF00FF);
	}

	G->SetFilter(0);
    //App->Print(0, "Unfiltered CameraY is: %04X", (Player->EZY + Player->CameraY + 8));
}

PUBLIC VIRTUAL void LevelScene::Cleanup() {
#define CLEANUP(name) if (name) { printf("%s\n", #name); name->Cleanup(); delete name; name = NULL; }

	App->Audio->ClearMusic();
	CLEANUP(Sound::SoundBank[0]);

	for (int o = 0; o < Data->animatedTilesCount; o++) {
		Memory::Free(Data->animatedTileDurations[o]);
	}
	Memory::Free(Data->animatedTileDurations);
	Memory::Free(Data->animatedTileFrames);

	for (int i = 0; i < Data->layerCount; i++) {
        Memory::Free(Data->Layers[i].DeformX);
		Memory::Free(Data->Layers[i].DeformY);
		delete[] Data->Layers[i].Info;
		delete[] Data->Layers[i].Tiles;
        delete[] Data->Layers[i].TilesBackup;
        Memory::Free(Data->Layers[i].TileOffsetY);
		delete[] Data->Layers[i].ScrollIndexes;
	}
    delete[] Data->tiles1;
    delete[] Data->tiles2;
    Memory::Free(Data->IsAnims);
	delete Data;
	Data = NULL;

	bool ClearedKnuxSprite = false;

	if (KnuxSprite[0]) {
		ClearedKnuxSprite = true;
		for (int i = 0; i < 5; i++) {
			CLEANUP(KnuxSprite[i]);
		}
	}

	for (int i = 0; i < PlayerCount; i++) {
		Players[i]->Cleanup();
		delete Players[i];
	}

	for (int i = 0; i < ObjectCount; i++) {
		Objects.at(i)->OnDestroy();
		delete Objects.at(i);
	}
	ObjectCount = 0;

	for (size_t i = 0; i < 0x400; i++) {
		// I guess we can't run cleanup unless it the original pointer, otherwise it becomes messy
		// ex: cleans up sprite at SpriteMapIDs.at(7) and sets SpriteMapIDs.at(7) to NULL,
		//     but SpriteMapIDs.at(8) is still where that sprite pointed to and isn't NULL, error is caused when invoking the undefined memory

		// tl;dr: only cleanup arrays if each element in it is guaranteed to be unique
		
		/*if (SpriteMapIDs.at(i) == nullptr) {
			continue;
		}
        CLEANUP(SpriteMapIDs.at(i));*/
	}

	for (size_t i = 0; i < SpriteBinMapIDs.size(); i++) {
        CLEANUP(SpriteBinMapIDs.at(i));
	}
	SpriteBinMapIDs.clear();

	for (int i = 0; i < DebugObjectIDCount; i++) {
		DebugObjectIDList[i] = 0;
	}
	DebugObjectIDCount = 0;

	Objects.clear();
	ObjectsSolid.clear();
	ObjectsSpring.clear();
	ObjectsEnemies.clear();
	ObjectsBreakable.clear();
	ObjectsPathSwitcher.clear();
	Memory::Free(DebugObjectIDList);
	ObjectProps.clear();
	RingProps.clear();
	Memory::Free(AnimatedSprite0Props);
	Memory::Free(AnimatedSprite1Props);
	Memory::Free(SoundBank);
	SpriteMapIDs.clear();
    SpriteBinMap.clear();

	for (size_t i = 0; i < TempObjects.size(); i++) {
        if (TempObjects.at(i) != NULL) {
            delete TempObjects.at(i);
            TempObjects.at(i) = NULL;
        }
	}
	TempObjects.clear();

	for (size_t i = 0; i < TempObjectTiles.size(); i++) {
        if (TempObjectTiles.at(i) != NULL) {
            delete TempObjectTiles.at(i);
            TempObjectTiles.at(i) = NULL;
        }
	}
    TempObjectTiles.clear();

	CLEANUP(TileSprite);
	CLEANUP(AnimTileSprite);
	CLEANUP(GiantRingModel);
	CLEANUP(PauseSprite);
	CLEANUP(GlobalDisplaySprite);
	CLEANUP(GlobalDisplaySpriteS3K);
	CLEANUP(MobileButtonsSprite);
	CLEANUP(SuperButtonsSprite);
	CLEANUP(EditorSprite);
	CLEANUP(AnimalsSprite);
	CLEANUP(ItemsSprite);
	CLEANUP(ObjectsSprite);
	CLEANUP(Objects2Sprite);
	CLEANUP(Objects3Sprite);
	CLEANUP(RobotnikSprite);
	CLEANUP(ExplosionSprite);
	CLEANUP(WaterSprite);

	Memory::Free(SavedPalette);
	Memory::Free(PlaneSwitchers);

	IScene::Cleanup();

	//*/
}

void* LevelScene::operator new(size_t const size) {
    for (;;) {
        if (void* const block = Memory::TrackedMalloc("LevelScene", size)) {
            return block;
        }
        if (_callnewh(size) == 0) {
            static const std::bad_alloc nomem;
            _RAISE(nomem);
        }

        // The new handler was successful; try to allocate again...
    }
}

void* LevelScene::operator new(size_t const size, std::nothrow_t const&) noexcept {
    try {
        return operator new(size);
    } catch (...) {
        return nullptr;
    }
}

void LevelScene::operator delete(void* const block) noexcept {
    Memory::Free(block);
}