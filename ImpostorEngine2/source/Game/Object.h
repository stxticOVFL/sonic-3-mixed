#ifndef S3_OBJECT_H
#define S3_OBJECT_H

#define Scene_AddSelfToRegistry(boots) Scene->Objects##boots[Scene->Object##boots##Count++] = this

#ifndef CONSTRUCTER
#define CONSTRUCTER
#endif

class LevelScene;
class IPlayer;

struct Rect {
    int  Left = 0x0;
    int  Right = 0x0;
    int  Top = 0x0;
    int  Bottom = 0x0;
    Rect() : Left(0), Right(0), Top(0), Bottom(0) {};
    Rect(int l, int r, int t, int b) : Left(l), Right(r), Top(t), Bottom(b) {};
    bool Empty() { return !Left && !Right && !Top && !Bottom; };
    Rect FlipX(bool flipX) { if (!flipX) return Rect(Left, Right, Top, Bottom); Left = -Left; Right = -Right; return Rect(Left, Right, Top, Bottom); };
    Rect FlipY(bool flipY) { if (!flipY) return Rect(Left, Right, Top, Bottom); Top = -Top; Bottom = -Bottom; return Rect(Left, Right, Top, Bottom); };
};

enum class CollideSide {
    NONE = 0,
    LEFT = 1,
    RIGHT = 2,
    SIDES = 3,
    TOP = 4,
    TOP_SIDES = 7,
    BOTTOM = 8,
};

namespace ThremixedIDS {
	enum ObjectNameToIdThremixed {
		Ring,
		Monitor,
		PathSwap,
		CollapsingPlatform,
		Spring,
		Spikes,
		BreakableWall,
		Ridge,
		CollapsingBridge,
		ContactFirceFallAnimator,
		AutomaticTunnel,
		RollEnforcer,
		LavaCollisionMarker,
		InvisibleBarrier,
		CorkFloor,
		StillSprite,
		AnimatedStillSprite,
		Button,
		StarPost,
		BreakableBar,
		Door,
		RetractingSpring,
		FloatingPlatform,
		Bubbler,
		InvisibleHurtBlockHorizontal,
		InvisibleHurtBlockVertical,
		TensionBridge,
		WaterDrop,
		HiddenMonitor,
		EggCapsule,
		CutsceneKnuckles,
		CutsceneButton,
		SpriteMasker,
		Tulipon,
		RhinoBot,
		MonkeyDude,
		CaterKillerJr,
		Jawz,
		Blastoid,
		Buggernaut,
		TurboSpiker,
		MegaChomper,
		Poindexter,
		BubblesBadnik,
		Spiker,
		Mantis,
		Clamer,
		Batbright,
		Blaster,
		TechnoSqueek,
		Penguinator,
		StarPointer,
		SnaleBlaster,
		Ribot,
		Orbinaut,
		Corkey,
		Flybot767,
		GumballItem,
		MagneticOrb,
		TiltingBridge,
		ElectricInvisibleBlock,
		FlamingInvisibleBlock,
		Madmole,
		Mushmeanie,
		Dragonfly,
		Butterdroid,
		Cluckoid,
		Skorp,
		Sandworm,
		Rockn,
		Fireworm,
		Toxomister,
		EggRobo,
		Spikebonker,
		Chainspike,
		ContactLevelChanger,

		P2RotateObject,

		RetractingSpring2P,
		Item2P,
		GoalMarker2P,

		AIZ_HollowTree,
		AIZ_LRZ_EMZ_Rock,
		AIZ_RideVine,
		AIZ_SwingVine,
		AIZ_DisappearingFloor,
		AIZ_FlippingBridge,
		AIZ_CollapsingLogBridge,
		AIZ_FallingLog,
		AIZ_SpikedLog,
		AIZ_DrawBridge,
		AIZ_ForegroundPlant,
		AIZ_CutsceneSonic,
		AIZ_Miniboss_Cutscene,
		AIZ_Miniboss,
		AIZ_EndBoss,
		AIZ1_TreeBark,
		AIZ1_RopePeg,

		HCZ_VWaterStream,
		HCZ_CGZ_Fan,
		HCZ_LargeFan,
		HCZ_HandLauncher,
		HCZ_WaterWall,
		HCZ_ConveyorBelt,
		HCZ_ConveyorSpike,
		HCZ_Block,
		HCZ_SnakeBlocks,
		HCZ_SpinningColumn,
		HCZ_Slide,
		HCZ_WaterSplash,
		HCZ_Miniboss,
		HCZ_EndBoss,

		MGZ_LBZSmashingPillar,
		MGZ_QuickMud,
		MGZ_RunAroundPole,
		MGZ_SwingingPlatform,
		MGZ_HeadTrigger,
		MGZ_MovingSpikePlatform,
		MGZ_TriggerPlatform,
		MGZ_SwingingSpikeBall,
		MGZ_DashTrigger,
		MGZ_Pulley,
		MGZ_TopPlatform,
		MGZ_TopLauncher,
		MGZ_CutsceneMiniBoss,
		MGZ_CTwistVine,
		MGZ_MiniBoss,
		MGZ_Boss,
		MGZ_KnucklesBoss,
		MGZ2_DrillingEggman,

		CNZ_Balloon,
		CNZ_Cannon,
		CNZ_RisingPlatform,
		CNZ_TrapDoor,
		CNZ_LightBulb,
		CNZ_HoverFan,
		CNZ_RotatingBarrels,
		CNZ_VacuumTubes,
		CNZ_RotatingWheel,
		CNZ_Bumper,
		CNZ_BouncepadSprings,
		CNZ_Corkscrew,
		CNZ_BarberPoleSprite,
		CNZ_RotatingMesh,
		CNZ_BreakableWaterRisingFloor,
		CNZ_LightSwitch,
		CNZ_Blastoid,
		CNZ_Miniboss,
		CNZ_EndBoss,

		ICZ_CrushingColumn,
		ICZ_PathFollowPlatform,
		ICZ_BreakableWall,
		ICZ_Freezer,
		ICZ_SegmentColumn,
		ICZ_SwingingPlatform,
		ICZ_Stalagtite,
		ICZ_IceCube,
		ICZ_IceSpikes,
		ICZ_HarmfulIce,
		ICZ_SnowPile,
		ICZ_TensionPlatform,
		ICZ_RightTrampolineSupport,
		ICZ_Miniboss,
		ICZ_EndBoss,

		MHZ_PulleyLift,
		MHZ_CurledVine,
		MHZ_StickyVine,
		MHZ_SwingBarHorizontal,
		MHZ_SwingBarVertical,
		MHZ_SwingVine,
		MHZ_MushroomPlatform,
		MHZ_MushroomParachute,
		MHZ_MushroomCatapult,
		MHZ_MushroomCap,
		MHZ_WindTunnel,
		MHZ_ChopTree,
		MHZ_ForceCrouch,
		MHZ_KnucklesButton,
		MHZ_Miniboss,
		MHZ_EndBoss,

		FBZ_RotatingMesh,
		FBZ_TwistingCylinders,
		FBZ_FloatingPlatform,
		FBZ_ChainLink,
		FBZ_MagneticSpikeBall,
		FBZ_MagneticPlatform,
		FBZ_SnakePlatform,
		FBZ_BentPipe,
		FBZ_RotatingPlatform,
		FBZ_DEZPlayerLauncher,
		FBZ_DisappearingPlatform,
		FBZ_ScrewDoor,
		FBZ_FanPole,
		FBZ_Propeller,
		FBZ_Piston,
		FBZ_PlatformBlocks,
		FBZ_MissileLauncher,
		FBZ_ExitDoor,
		FBZ_EggPrison,
		FBZ_SpringPlunger,
		FBZ_WallMissile,
		FBZ_Mine,
		FBZ_Elevator,
		FBZ_TrapSpring,
		FBZ_Flamethrower,
		FBZ_SpiderCrane,
		FBZ_MagneticPendulum,
		FBZ_Laser_Boss,
		FBZ_EndBoss,
		FBZ1_Boss,
		FBZ2_CutsceneObjects,

		LRZ_TubeElevator,
		LRZ_MovingPlatform,
		LRZ_FlagPlatform, // Unused
		LRZ_Door,
		LRZ_BigDoor,
		LRZ_ExplodingTrigger,
		LRZ_TriggerBridge,
		LRZ_PlayerLauncher,
		LRZ_FlameThrower,
		LRZ_RideGrapple,
		LRZ_CupElevator,
		LRZ_CupElevatorPole,
		LRZ_PipePlug,
		LRZ_HangPlatform,
		LRZ_FireballLauncher,
		LRZ_ButtonHorizontal,
		LRZ_ShootingTrigger,
		LRZ_DashElevator,
		LRZ_LavaFall,
		LRZ_SwingingSpikeBall,
		LRZ_SmashingSpikePlatform,
		LRZ_SpikeBall,
		LRZ_SpikeBallLauncher,
		LRZ_OrbitingSpikeBallHorizontal,
		LRZ_OrbitingSpikeBallVertical,
		LRZ_SolidMovingPlatforms,
		LRZ_SolidRock,
		LRZ_SpinLauncher,
		LRZ_LoweringGrapple,
		LRZ_GateLaser,
		LRZ_Siren,
		LRZ_ChainedPlatforms,
		LRZ_FallingSpike,
		LRZ_SinkingRock,
		LRZ_ExplodingRock,
		LRZ_RockCrusher,
		LRZ_TorpedoLauncher,
		LRZ_RotatingCylinders,
		LRZ_VerticalCylinder,
		LRZ_CollapsingBridge,
		LRZ_TurbineSprites,
		LRZ_TwirlTunnel,
		LRZ_KnucklesEndHelper,
		LRZ_Miniboss,
		LRZ_FinalBoss1,
		LRZ_FinalBoss2,
		LRZ_EndBoss,
		LRZ1_Eggman,
		LRZ1_MiniBoss,
		LRZ1_KnucklesMiniBossBox,
		LRZ2_EggMobile,
		LRZ2_TallBoss,
		LRZ3_Platforms,

		SOZ_SandFalls,
		SOZ_SpawningSandBlocks,
		SOZ_DoubleLoopPathSwapper,
		SOZ_SpringLoopPathSwapper,
		SOZ_PushableRock,
		SOZ_SpringVine,
		SOZ_RisingSandWall,
		SOZ_LightSwitch,
		SOZ_FloatingPillar,
		SOZ_SwingingPlatform,
		SOZ_BreakableSandRock,
		SOZ_PushSwitch,
		SOZ_Door,
		SOZ_SandCork,
		SOZ_RapelWire,
		SOZ_SolidSprites,
		SOZ_Ghosts,
		SOZ_Miniboss,
		SOZ_EndBoss,
		SOZ2_GhostCapsuleLoader,
		SOZ2_GhostCapsule,

		HPZ_MasterEmerald,
		HPZ_MidwayPalleteChanger,
		HPZ_SuperEmeralds,
		HPZ_SpecialStageCreater,

		SSZ_RetractingSpring,
		SSZ_SwingingCarrier,
		SSZ_RotatingPlatform,
		SSZ_RetractingBridge,
		SSZ_HPZTeleporter,
		SSZ_ElevatorBar,
		SSZ_CollapsingBridgeDiagonal,
		SSZ_CollapsingBridge,
		SSZ_BouncyCloud,
		SSZ_CollapsingColumn,
		SSZ_FloatingPlatform,
		SSZ_KnucklesButton,
		SSZ_EggRobo,
		SSZ_GHZBoss,
		SSZ_MTZBoss,
		SSZ_MechaSonicBoss,

		DEZ_FloatingPlatform,
		DEZ_HangCarrier,
		DEZ_TorpedoLauncher,
		DEZ_LiftPad,
		DEZ_Staircase,
		DEZ_ConveyorBelt,
		DEZ_Lightning,
		DEZ_ConveyorPad,
		DEZ_EnergyBridge,
		DEZ_CurvedEnergyBridge,
		DEZ_TunnelLauncher,
		DEZ_GravitySwitch,
		DEZ_ReverseGravityTunnel,
		DEZ_TwirlTunnel,
		DEZ_GravityReverser,
		DEZ_TunnelJunction,
		DEZ_RetractingSpring,
		DEZ_HoverMachine,
		DEZ_SpecialEngineController,
		DEZ_BumperWall,
		DEZ_GravityPuzzle,
		DEZ_Miniboss,
		DEZ_EndBoss,
		DeathEgg_LaunchTowers,

		DDZ_BossShip,
		DDZ_Asteroid,
		DDZ_Missile,

		CGZ_TriangularSprings,
		CGZ_BladePlatform,

		BPZ_ElephantBlock,
		BPZ_Balloon,

		DPZ_DisolvingSandBar,
		DPZ_Button,

		EMZ_Dripper,

		SS_EntryRing,
		SS_GumballLevel,
		SS_GumballSideSpring,

		Pachinko_TriangleBumper,
		Pachinko_Flipper,
		Pachinko_EnergyTrap,
		Pachinko_InvisibleUnknown,
		Pachinko_Platform,
		Pachinko_ItemOrb,
	};
};

bool operator==(const CollideSide& left, const int& right);
bool operator==(const int& left, const CollideSide& right);
bool operator!=(const CollideSide& left, const int& right);
bool operator!=(const int& left, const CollideSide& right);

class Object;

class Object {
public:
    IApp* App;
    IGraphics* G;
    LevelScene* Scene;

    ISprite* Sprite = NULL;
    
    void *Parent = NULL;

    uint32_t  InitialX;
    uint32_t  InitialY;
    uint32_t* InitialValues;
	int*      Attributes = NULL;

    int32_t  SubX = 0;
    int32_t  SubY = 0;
    int16_t& X = *((int16_t*)&SubX + 1);
    int16_t& Y = *((int16_t*)&SubY + 1);
    uint16_t ID = 0x0;
    uint8_t  SubType = 0x0;
    bool     FlipX = false;
    bool     FlipY = false;
    bool     DoDeform = false;
    
    bool     isDebugModeObject = false;
    bool     isHeldDebugObject = false;

    int16_t  W = 32;
    int16_t  H = 32;
    int16_t  VisW = 0;
    int16_t  VisH = 0;
    int16_t  XSpeed = 0;
    int16_t  YSpeed = 0;

    int16_t  Gravity = 0;

    int16_t  MaxAccel = 0;
    int16_t  Acceleration = 0;
    int16_t  SwingDirection = 0;
    int16_t  SwingCounter = 0;

    bool     Active = false;
    bool     Priority = false;
    bool     OnScreen = false;
	bool     DrawCollisions = false;
    bool     CleanupInactiveObject = false;
    bool     IsFloatingPlatform = false;
	bool     Visible = true;
    int      VisualLayer = 0;
    uint32_t DrawCollisionsColor = 0x49ED80; // Green
    uint32_t DrawNoCollisionsColor = 0xCC53D1; // Violet?
    
    size_t   BinIndex = 0xFFFFFFFF;

    bool     AutoAnimate = false;
    int      CurrentAnimation = -1;
    int      AnimationFrame = -2;
    int      Frame = 0;
    int      Timer = -1;
    int      Rotation = 0;

    bool     Solid = false;
    bool     SolidTop = false;
    bool     SolidCustomized = false;
    Rect     HitboxSolid;
	
    bool     Pushable = false;
	int      PushMaxLeft = 0;
	int      PushMaxRight = 0;
	CollideSide PushableSide = CollideSide::SIDES;
	// bool     Climbable = false;

    bool     BounceOffShield = false;
    bool     NegatedByFireShield = false;
    bool     NegatedByElectricShield = false;
    bool     NegatedByBubbleShield = false;
    int      CollidingWithPlayer = false;
    bool     BeingStoodOn = false;

    CollideSide BreakableByRoll = CollideSide::NONE;
    CollideSide BreakableByJump = CollideSide::NONE;
    CollideSide BreakableByGlide = CollideSide::NONE;
	CollideSide BreakableBySuper = CollideSide::NONE;
    CollideSide BreakableBySpring = CollideSide::NONE;
    CollideSide BreakableByKnuckles = CollideSide::NONE;
    CollideSide BreakableByMighty = CollideSide::NONE;

    virtual ~Object() {

    };

    virtual void Create();
    virtual void Update();
	virtual void UpdateSubType();
    virtual uint8_t GetSubTypeIncrement();
	virtual uint8_t GetSubTypeMax();
    virtual void Render(int CamX, int CamY);

	virtual void DebugCreate();

    virtual int  OnTouchHitbox(int) { return 0; };

	virtual void OnPush(int PlayerID, int HitFrom);
    virtual int  OnGrabbed(int) { return 0; };
    virtual int  OnBreakHorizontal(int, int) { return 0; };
    virtual int  OnBreakVertical(int, int) { return 0; };
    virtual int  OnCollisionWithPlayer(int, int, int) { return 0; };
    virtual int  CustomSolidityCheck(int x, int y, int ID, int jumpthrough) { return false; };
    virtual int  OnLeaveScreen();
    virtual void OnSwingFinish() { };
    virtual void OnAnimationFinish();
    virtual void MoveSprite();
    virtual void MoveWithParent();
    
    virtual Object* GetObjectParent();
    virtual bool IsParentFloatingPlatform();

    void ChangeAnimation(int animationID, int startFrame, bool overrideanyways) {
        if (CurrentAnimation != animationID || overrideanyways)
            Frame = startFrame * 0x100;
        CurrentAnimation = animationID;
    };
    void ChangeAnimation(int animationID, int startFrame) {
        ChangeAnimation(animationID, startFrame, false);
    };
    void ChangeAnimation(int animationID) {
        ChangeAnimation(animationID, 0);
    };

    void Animate();
	void AnimationProgress(int16_t animationData[]);
	int16_t DelayedAnimationProgress(int16_t animationData[]);
	int16_t DelayedAnimationProgress(int16_t animationData[], ISprite::Animation Animation);
    int Swing_UpAndDown();
};

class Enemy : public Object {
public:
    bool Harmful = true;
    bool Hurting = false;
    bool Invincible = false;
	bool IsBodyExtension = false;
    int  Radius = 1;
    int  HitCount = 1;

    bool Boss = false;

    Rect HitboxEnemy;
    
    IPlayer *ClosetPlayer = 0;
    bool PlayerRelativeXDirection = 0;
    bool PlayerRelativeYDirection = 0;
    int16_t PlayerXDistance = 0;
    int16_t PlayerYDistance = 0;

    virtual void Create();
    virtual void CheckDistanceToPlayers();
    virtual void MoveTowardsTargetPosition(IPlayer *Player, int16_t maxSpeed, int16_t speed);
    virtual int  OnDeath();
    virtual int  OnHit();
    virtual Enemy* GetEnemyParent();
};

class Solid : public Object {
public:
    virtual void Create();
};

#include <Game/SaveGame.h>

#endif /* S3_OBJECT_H */
