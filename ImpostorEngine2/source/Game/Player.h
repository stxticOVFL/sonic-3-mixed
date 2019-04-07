#ifndef S3_PLAYER_H
#define S3_PLAYER_H

class IPlayer;

#include <Utils/Standard.h>
#include <Game/LevelSceneExt.h>
#include <Game/LevelScene.h>
#include <Game/Object.h>
#include <Game/Sound.h>

//#include <Game/../TextureAudio.h>

using namespace std;

/*
 * Player Enums
 */

 // <editor-fold> Player Enums
enum class SpindashType {
	None,
	Standard,
	SCD,
};
enum class InvincibilityType {
	None,
	Temporary,
	Instant,
	Full,
};
enum class ShieldType {
	None,
	Basic,
	Fire,
	Electric,
	Bubble,
	Instashield,
	Invincibility,
};
enum class SuperFormAnimType {
	None,
	Transforming,
	Super,
	Deforming,
};
enum class SpeedCapType {
	None,
	S1,
	SCD,
};
enum class CharacterType {
	Sonic = 0,
	Tails,
	Knuckles,
	Mighty,
	Ray,
};
enum class ActionType {
	Normal,
	Hurt,
	Peril,
	Dead,
	Jumping,
	Fly,
	Rolling,
	Pipe,
	CrouchDown,
	Spindash,
	LookUp,
	Corkscrew,
	Spring,
	Twirl,
	Balancing,

	Glide,
	GlideFall,
	GlideFallLand,
	GlideSlide,

	RayGlide,

	MightyStomp,
	MightyUncurl,

	Climb,
	ClimbRise,

	Transform,
	Deforming,
	Grab,
	GrabFall,
	Quicksand,
	Skid,
	Push,
	Slide,

	Spinning,

	ObjectGrab,

	Fan,
	Conveyor,

	InStream,
	InStreamGrab,
	InStreamPipe,

	Bored1,
	Bored2,

	Respawn,
	CancelableAnim,

	Victory,
};

enum class VibrationType {
	None = 0,
	ImpactSmall, // impacts are short, water does this if YSpeed > 4
	ImpactLarge,
	DamageSmall,
	DamageLarge,
	SpindashRev,
	Death,
};

struct PlayerStatus {
	int16_t     X = 0;
	int16_t     Y = 0;
	bool        InputUp = false;
	bool        InputDown = false;
	bool        InputLeft = false;
	bool        InputLeftPress = false;
	bool        InputRight = false;
	bool        InputRightPress = false;
	bool        InputJump = false;
	bool        InputJumpHold = false;
	ActionType  Action = ActionType::Normal;
	int16_t     XSpeed = 0;
	int16_t     YSpeed = 0;
};

// </editor-fold> Player Enums

class IPlayer : public Object {
public:
	//ISprite* Sprite = NULL;
	ISprite* SpriteDashDust = NULL;
	ISprite* SpriteWaterRun = NULL;

	ISprite* SpriteShields = NULL;
	ISprite* SpriteShields2 = NULL;

	bool ManiaPhysics = false;

	bool ReloadPlayer = true;

	Uint32 PaletteNormal[16];
	Uint32 PaletteSuper[16];
	Uint32 PaletteSuperPulse[16];

	Uint32 PaletteNormalHCZ[16];
	Uint32 PaletteSuperHCZ[16];
	Uint32 PaletteSuperPulseHCZ[16];

	Uint32 PaletteHyper[16];
	Uint32 PaletteHyperBlend[16];
	Uint32 PaletteHyperExtended[32];
	Uint32 PaletteHyperPulse[16];

	/*ITexture* Palette1 = NULL;
	ITexture* Palette2 = NULL;*/

	ISprite::Animation* Animations = NULL;
	int CurrentAnimation = 0;
	int CurrentFrame = 0;
	int ShieldFrame = 0;
	int DashFrame = 0;
	ISprite* Sprites[12];
	int TurnValue = 5;
	int AnimationSpeedMult = 1;

	bool Thremixed = true;
	bool OCMode = false;
	int  PushSpeed = 0x1000;

	int SensorA = 20;
	int SensorB = 20;
	int SensorC = 20;
	int SensorD = 20;
	int SensorE = 20;
	int SensorF = 20;
	bool WallLeft = false;
	bool WallRight = false;
	int ModeSin[4];
	int ModeCos[4];

	unordered_map<string, int> AnimationMap;

	void ChangeAnimation(int animationID);
	void ChangeAnimation(int animationID, int startFrame);
	void ChangeAnimation2(int animationID);
	void ChangeAnimation2(int animationID, int startFrame);

	/*
	 * Player Variables
	 */

	 // <editor-fold> Player Variables
	ActionType          Action = ActionType::Normal;

	CharacterType       Character = CharacterType::Sonic;

	PlayerStatus        PlayerStatusTable[32];
	int                 PlayerStatusTableIndex = 0;

	int16_t&            EZX = *((int16_t*)&SubX + 1);
	int16_t&            EZY = *((int16_t*)&SubY + 1);

	bool                DoCollision = true;

	bool                ControlLocked = false;
	bool                Cutscene = false;

	int                 Lives = 0;
	int                 Rings = 0;
	int                 RingLifeValue = 100;
	bool                LoseAllRings = true;
	bool                HyperRings = false;
	bool                Sidekick = false;

	bool                ObjectCheck = true;
	Object*             LastObject = NULL;
	Object*             LastGrab = NULL;
	int                 GrabTimer = 0;
	bool                CheckJumpThrough = false;
	int                 PlayerID = 0;

	Object*             DebugObject = NULL;
	int16_t             DebugObjectIndex = -1;
	uint8_t             DebugObjectSubIndex = 0;
	int16_t             LastDebugObjId = -1;

	int                 Angle = 0;
	int                 AngleMode = 0;
	int16_t             DisplayAngle = 0x0000;
	int16_t             GroundSpeed = 0;

	float               Flip = 1;
	int32_t             DisplayX = 0;
	int32_t             DisplayY = 0;
	int                 CameraX = 0;
	int                 CameraY = 0;
	int                 DisplayFlip = 1;
	bool                SlowRotationReset = false;
	bool                Hidden = false;

	int                 SpeedMultiplier = 1;
	int                 SpeedSplitAmount = 4;
	float               Acceleration = 0.046875f;
	float               AccelRate = 0.046875f;
	float               SkidRate = 0.5f;
	float               RollingFriction = 0.046875f;
	float               RollingFrictionValue = 0.046875f;

	float               Gravity = 0.0f;
	float               GravityMaxFull = 128.0f;
	float               GravityRate = 0.21875f;
	float               GravityQuicksandRate = 0.35f;

	int                 JumpVariable = 0;
	int                 StoredX = 0;
	int                 StoredY = 0;
	float               JumpValue = -6.5f;
	float               JumpReleaseValue = -4.0f;
	float               JumpValueWater = -3.5f;
	float               JumpReleaseValueWater = -2.0f;
	float               JumpAnimSpeed = 1.0f;

	int                 SpindashMin = 8;
	int                 SpindashMax = 12;
	int                 SpindashRev = 0;
	SpindashType        Spindash = SpindashType::Standard;

	bool                DropDashEnabled = true;
	int                 DropDashRev = 0;

	int                 InvincibilityTimer = 0;
	InvincibilityType   Invincibility = InvincibilityType::None;

	int                 SpeedSneakersTimer = 0;
	bool                SpeedSneakersActive = false;
	
	int                 ShieldAnimation = 0;
	bool                ShieldUsable = true;
	bool                ShieldAction = false;
	ShieldType          Shield = ShieldType::None;

	int                 FlyFlag = 0;
	int                 FlyTimer = 480;
	int                 FlyTimerMax = 480;

	float               GlideTurnSpeed = 0.0f;
	int                 GlideTurnCos = 0;
	bool                GlideTurnFlag = false;

	int                 GlideSpeedStore = 0;
	int                 MaxGlideSpeed = 0;
	int                 RayBoostCount = 0;
	int                 GrabSwingValue = -1;
	bool                AngleBothSensors = false;                  // - If set to true, both sensors must return a terrain object to check for angles.
	int                 AngleModeSwitchMode = 0;                   // - If set to 0, it will follow a more accurate angle mode switch (Reccomended).
	int                 AngleSensorHeight = 90;
	int                 AngleSensorWidth = 6;
	int                 GroundSensorHeight = -1;
	int                 GroundSensorHeightMin = -1;
	int                 TerrainAngle = 0;

	bool				MightyStomping = false;
    bool                ClearKnucklesSprites = false;

	bool                Ground = false;
	bool                Landed = false;
	bool                WaterRunning = false;

	int                 InputAlarm = 0;

	int                 Layer = 0;
	int                 VisualLayer = 0;
	int                 ForegroundLayer = 2;
	int                 EnemyCombo = 0;

	bool                Underwater = false;
	int                 UnderwaterTimer = 1200;

	bool                SuperForm = false;
	bool                HyperForm = false;
	bool                ExtendedHyperPallete = true;
	bool                SuperFlight = false;
	bool                SuperEnabled = true;
	bool                HyperEnabled = false;
	int                 SuperFormTimer = 0;
	SuperFormAnimType   SuperFormAnim = SuperFormAnimType::None;
	int                 SuperFormAnimTimer = -1;
	int                 SuperFormAnimTimerMax = 20;
	int                 LastHyperIndex = 0;
	int                 HyperLoopIndex = 0;

	bool                ForceRoll = false;
	int                 ForceRollBond = -1;
	bool                RollSpeedCap = true;
	bool                RollJumpLock = false;
	SpeedCapType        SpeedCap = SpeedCapType::None;

	int                 CollisionPushMode = 0;                     // - 0: Legacy, 1: Safe
	int                 AngleIslandFlag = 0;                     // - If the number is lower, it will be more accurate, but use more CPU.

	int                 SlopeFactorMode = 0;                     // - 0: Sonic 1 & 2, 1: Sonic 3, 2: Sonic 3?

	bool                InputLockLeftRight = false;                 // - If set to true, the player will only rotate if angle is greater than 45 degrees(Only applies to 360 rotation).
	bool                Use360SpriteRotation = true;   // - If set to true characters will use 360 degree sprite rotations, false for 8 degree rotations.

	bool                FlagsAllowXMovement = true;
	bool                FlagsAllowYMovement = true;
	bool                FlagsAllowObjectHandle = true;

	bool                CameraLag = true;
	int                 CameraLockTimer = 0;
	int                 CameraLookTimer = 0;
	int                 SpringFlip = 0;

	float               Frame = 0;
	int                 AnimationStart = 0;
	int                 AnimationEnd = 0;
	int                 AnimationSpeed = 0;
	bool                AnimationStop = false;
	int                 AnimationDone = 0;
	int                 GenericTimer = -1;

	float               Sin[360];
	float               Cos[360];

	IPlayer*			HoldingPlayer = NULL;

	int                 ObjectControlled = 0;

	int                 RespawnTimer = -1;
	bool                PanicSpindashing = false;

	bool                InputUp = false;
	bool                InputDown = false;
	bool                InputLeft = false;
	bool                InputLeftPress = false;
	bool                InputRight = false;
	bool                InputRightPress = false;
	bool                InputJump = false;
	bool                InputJumpHold = false;
	int                 InputController = -1;
	// </editor-fold> Player Variables

	// <editor-fold> Object-Use Variables
	int                 RingAlarm = 0;
	int                 Data2 = 0;
	int                 Data3 = 0;
	int                 OrigH = 0;
	int                 WaitTimer = -1;
	//LevelScene*			Level = NULL;
	// </editor-fold> Object-Use Variables

	/*
	 * Basic functions
	 */

	 // <editor-fold> Basic functions
	IPlayer();

	void Create();
	void Update();
	void LateUpdate();
	void Render(int CamX, int CamY);
    void Cleanup();

	void AnimSet(int Start, int End, int Speed, bool Stop);
	void AnimExecute();

	void StepBegin();
	void Step();
	void StepEnd();

	void Vibrate(VibrationType v);
	// </editor-fold> Basic functions

	/*
	 * Math functions
	 */

	int AngleDifference(int a, int b);
	int SpecialModulo(int a, int b);

	/*
	 * Collision functions
	 */

	 // <editor-fold> Collision functions
	bool CollisionSensor360(int obj, int len, int A, int no360);
	bool CollisionASensor(int obj, int len);
	bool CollisionBSensor(int obj, int len);
	bool CollisionASensor360(int obj, int len);
	bool CollisionBSensor360(int obj, int len);
	bool CollisionMSensor360(int obj, int len);

	bool CollisionLeftSensor(int obj);
	bool CollisionRightSensor(int obj);

	bool CollisionCSensor(int obj, int len);
	bool CollisionDSensor(int obj, int len);

	bool CollisionSquish();

	bool CollisionCheckLine(float xr, float yr, float x2, float y2, int* angleOut);
	// </editor-fold> Collision functions

	/*
	 * Physics & Movement functions
	 */

	 // <editor-fold> Physics & Movement functions
	int CheckAngle();
	void CheckGroundLevel();
	void BounceAwayFrom(float xx, float yy, float vel);
	float GetSlopeFactor();

	bool PushPlayerX_Id(int obj);
	bool PushPlayerX();
	void PushPlayerY();
	void PushPlayerYLand();
	void PushPlayerYDown();

	bool HandleSprings();
	void HandleEnemies();
	void HandleMonitors();
	void HandlePathSwitchers();
	bool HandleBreakableTerrain();

	void HandleObjects();
	void ActionObjectGrab();

	void WallCollision();
	void SpeedMovement();
	void GravityMovement();

	void HandleAction();
	void ActionPush();
	void ActionNormal();
	void ActionLookUp();
	void ActionRolling();
	void ActionSkid();
	void ActionJumping();
	void ActionCrouchDown();
	void ActionSpindash();
	void ActionSpring();
	void ActionSlide();
	void ActionGrab();
	void ActionFly();
	void ActionInStream();
	void ActionInStreamPipe();
	void ActionInStreamGrab();
	void ActionRespawn();
	void ActionGlide();
	void ActionGlideFall();
	void ActionGlideFallLand();
	void ActionGlideSlide();
	void ActionClimb();
	void ActionClimbRise();
	// </editor-fold> Physics & Movement functions

	/*
	 * Miscellaneous functions
	 */

	void Die(bool drown);
	void Jump();
	void CreateRingLoss();
	void Hurt(int x, bool spike);
	void Deform();
	void GiveRing(int n);
	void GiveLife(int n);
	void CheckDespawn();
	void DoVictory();
	void DoSuperTransform();
    
#ifndef NDEBUG
    void* operator new(size_t const size) {
        for (;;) {
            if (void* const block = Memory::TrackedMalloc("Player", size)) {
                return block;
            }
            if (_callnewh(size) == 0) {
                static const std::bad_alloc nomem;
                _RAISE(nomem);
            }

            // The new handler was successful; try to allocate again...
        }
    }
    
    void* operator new(size_t const size, std::nothrow_t const&) noexcept {
        try {
            return operator new(size);
        } catch (...) {
            return nullptr;
        }
    }
    
    void operator delete(void* const block) noexcept {
        Memory::Free(block);
    }
#endif
};

#endif /* S3_PLAYER_H */
