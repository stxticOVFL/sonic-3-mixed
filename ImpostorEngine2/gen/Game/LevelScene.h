#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;
class ISprite;
class IModel;
class ISound;

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

    LevelScene(IApp* app, IGraphics* g);
    virtual void PlayMusic(const char* path, int loop);
    virtual void PlayMusic(const char* path, int loop, int vol);
    virtual void PlayMusic(int act, int loop, int mode);
    virtual void PlayMusic(int act, int loop, int mode, int vol);
    static bool IsZoneCurrently(const char* CheckZoneLetters);
    virtual void AssignSpriteMapIDs();
    virtual void LoadZoneSpecificSprites();
    void SaveState();
    void LoadState();
    static size_t LoadSpriteBin(const char* Filename);
    static ISprite* LoadSpriteFromBin(const char* Filename);
    static ISprite* GetSpriteFromBinIndex(size_t index);
    virtual void CreateAttributeValue(AttributeValue* Attribute);
    virtual void LoadData();
    virtual void Init();
    static int LoadStatic(void* data);
    void LoadInBackground();
    virtual void RestartStage(bool doActTransition, bool drawBackground);
    virtual void PatchLayer(int layer);
    virtual int FindLayer(std::string name);
    virtual void UpdateDiscord();
    bool CollisionAt(int probeX, int probeY);
    bool CollisionAt(int probeX, int probeY, Object* IgnoreObject);
    bool CollisionAt(int probeX, int probeY, int* angle);
    bool CollisionAt(int probeX, int probeY, int* angle, int anglemode);
    bool CollisionAtClimbable(int probeX, int probeY, int* angle, int anglemode, IPlayer* player);
    bool CollisionAt(int probeX, int probeY, int* angle, int anglemode, IPlayer* player);
    virtual bool CollisionAt(int probeX, int probeY, int* angle, int anglemode, IPlayer* player, Object* IgnoreObject);
    void AddActiveRing(int x, int y, int xs, int ys, int mag);
    Explosion* AddExplosion(int animation, bool flip, int x, int y);
    Explosion* AddExplosion(int animation, bool flip, int x, int y, int vl);
    Explosion* AddExplosion(ISprite* sprite, int animation, bool flip, int x, int y);
    Explosion* AddExplosion(ISprite* sprite, int animation, bool flip, int x, int y, int vl);
    void AddScoreGhost(int frame, int x, int y);
    void AddFallingTile(int til, int x, int y, int offX, int offY, bool flipX, bool flipY, int hold);
    void AddFallingTile(int til, int x, int y, int offX, int offY, bool flipX, bool flipY, int xspeed, int yspeed);
    void AddMovingSprite(ISprite* sprite, int x, int y, int left, int top, int w, int h, int offX, int offY, bool flipX, bool flipY, int xspeed, int yspeed, int grv, int hold);
    void AddMovingSprite(ISprite* sprite, int x, int y, int left, int top, int w, int h, int offX, int offY, bool flipX, bool flipY, int xspeed, int yspeed, int grv);
    void AddMovingSprite(ISprite* sprite, int x, int y, int animation, int frame, bool flipX, bool flipY, int xspeed, int yspeed, int grv);
    void AddMovingSprite(ISprite* sprite, int x, int y, int animation, int frame, bool flipX, bool flipY, int xspeed, int yspeed, int grv, int life, int hold);
    void AddAnimal(int x, int y, bool flipX, bool flipY, int xspeed, int yspeed, bool escaping);
    Object* AddNewObject(int ID, int SubType, int X, int Y, bool FLIPX, bool FLIPY);
    Object* AddNewObject(char* ObjName, int X, int Y);
    void AddNewDebugObjectID(int16_t ID);
    virtual void SpawnPlayer(int ID, bool Sidekick, bool Main, int X, int Y);
    virtual void EarlyUpdate();
    virtual void Subupdate();
    virtual void DoResults();
    virtual void FinishResults();
    virtual void GoToNextAct();
    virtual void TransferCommonLevelData(LevelScene* NextAct);
    virtual void DoCustomFadeAction();
    void OnEvent(Uint32 event);
    void Update();
    virtual void HandleCamera();
    void AddSelfToRegistry(Object* obj, const char* where);
    void CleanupObjects();
    void RenderAnimatedSprites(int layer);
    void RenderRings();
    void RenderHUD();
    void RenderTitleCard();
    void RenderPauseScreen();
    void RenderResults();
    virtual void RenderAboveBackground();
    virtual void RenderAboveForeground();
    void DrawThing(int l);
    virtual void RenderEverything();
    virtual void Render();
    virtual void Cleanup();
protected:
    static size_t ResetSpriteBin(const char* Filename);
    static bool FindSpriteBin(std::string filename);
};

#endif /* LEVELSCENE_H */
