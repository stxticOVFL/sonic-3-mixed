#ifndef OBJECTLISTING_H
#define OBJECTLISTING_H

#include "Common/Ring.h"			// 2EA61FD6
#include "Common/Monitor.h"			// BDE7E33A
#include "AIZ/HollowTree.h"			// 1E5BFA5F
#include "Common/CollapsingPlatform.h"			// 95087B30
#include "CommonSpecial/Rock.h"			// FE0305DD
#include "AIZ/RideVine.h"			// 7F20AD1D
#include "Common/Spring.h"			// 2802B89E
#include "Common/Spikes.h"			// 44BC7B0E
#include "AIZ/TreeBark.h"			// 590E62AF
#include "AIZ/RopePeg.h"			// 7FB64D3A
#include "AIZ/SwingVine.h"			// D691E4F3
#include "Common/BreakableWall.h"			// 60436E3A
#include "Common/Ridge.h"			// EC54C850
#include "Common/CollapsingBridge.h"			// 18C4AE0D
#include "Common/AutomaticTunnel.h"			// C286FB4D
#include "Common/RollEnforcer.h"			// 624D9DA4
#include "Common/InvisibleBlock.h"			// B4878D6A
#include "AIZ/DisappearingFloor.h"			// 16A80CA8
#include "CommonSpecial/CorkFloor.h"			// 4A50924F
#include "AIZ/FlippingBridge.h"			// B48623A
#include "AIZ/CollapsingLogBridge.h"			// C558537E
#include "AIZ/FallingLog.h"			// BFF26300
#include "AIZ/SpikedLog.h"			// 22DC09C3
#include "Common/NonAnim.h"			// 10F942A2
#include "Common/AnimSprite.h"			// 9B4046EC
#include "AIZ/Drawbridge.h"			// 5465065D
#include "Common/Button.h"			// F72B92E4
#include "Common/StarPost.h"			// C8B337E6
#include "AIZ/ForegroundPlant.h"			// 9D88FCCE
#include "HCZ/BreakBar.h"			// EFFDFB55
#include "HCZ/HCZVWaterStream.h"			// D396DEF2
#include "HCZ/Fan.h"			// 7849B3C1
#include "HCZ/LargeFan.h"			// 35EA70E0
#include "HCZ/HandLauncher.h"			// E6E16DBC
#include "HCZ/HCZWaterWall.h"			// EC4012B6
#include "CommonSpecial/Door.h"			// 81EC1830
#include "HCZ/HCZConveyorBelt.h"			// 98E1D2FF
#include "HCZ/HCZConveyorSpike.h"			// D719B2D
#include "HCZ/Block.h"			// 58F95E1C
#include "CNZ/Balloon.h"			// 65BE2A3A
#include "CNZ/CNZLightBulb.h"			// A17F0176
#include "CNZ/HoverFan.h"			// 7C977754
#include "CNZ/VacuumTube.h"			// 177568D6
#include "CNZ/Bumper.h"			// 9DD277AF
#include "CNZ/Bouncepad.h"			// 3B4DCB47
#include "MGZ/MGZQuickMud.h"			// 43F8965E
#include "Common/FloatingPlatform.h"			// C3C9288B
#include "MGZ/MGZSmashingPillar.h"			// 6B9FADA2
#include "MGZ/MGZSwingingPlatform.h"			// 3B006393
#include "Common/Bubbler.h"			// 8E41B4A6
#include "MGZ/Relief.h"			// FC346615
#include "MGZ/MGZTriggerPlatform.h"			// 5809E61C
#include "MGZ/MGZDashTrigger.h"			// FF451B7
#include "MGZ/TopPlatform.h"			// C2A459B3
#include "HCZ/HCZSnakeBlocks.h"			// 1DBC27C1
#include "HCZ/SpinningColumn.h"			// 7DC95D09
#include "HCZ/HCZSlide.h"			// BECC7360
#include "Common/InvisibleSpikes.h"			// E40C8E50
#include "Common/InvisibleDeath.h"			// A0BE8640
#include "CommonSpecial/TensionBridge.h"			// 5F02A27F
#include "HCZ/HCZWaterSplash.h"			// AFDD0C56
#include "Common/HiddenMonitor.h"			// 8616E0BD
#include "CommonSpecial/EggCapsule.h"			// 973691D6
#include "CommonSpecial/CutsceneKnuckles.h"			// 2822B56D
#include "Common/SpecialRing.h"			// ABC2C658
#include "AIZ/Bloominator.h"			// 9B85E709
#include "AIZ/RhinoBot.h"			// 4374E9C7
#include "AIZ/MonkeyDude.h"			// B7C95057
#include "AIZ/CaterkillerJr.h"			// 3F487ED4
#include "AIZ/FireBreathCutscene.h"			// 842C5D59
#include "AIZ/FireBreath.h"			// CDF582CA
#include "AIZ/FlameMobile.h"			// 7893A0E1
#include "HCZ/Jawz.h"			// 2160C123
#include "HCZ/Blastoid.h"			// CD00547A
#include "HCZ/Buggernaut.h"			// 78C3EB13
#include "HCZ/TurboSpiker.h"			// 8E6F27CF
#include "HCZ/MegaChomper.h"			// C50988CE
#include "HCZ/Pointdexter.h"			// F365CCC4
#include "HCZ/BigShaker.h"			// 92C9F0D4
#include "HCZ/ScrewMobile.h"			// 1EF84BB7
#include "MGZ/BubblesBadnik.h"			// A8CF1ABB
#include "MGZ/Spiker.h"			// DF9FA830
#include "MGZ/Mantis.h"			// 2C7E197C
#include "MGZ/MGZDriller.h"			// CCA7D752
#include "MGZ/TunnelBot.h"			// 403E6CD3
#include "MGZ/DrillerEggman.h"			// 88549378
#include "MGZ/DrillMobile.h"			// EFAD5D3C
#include "CNZ/Batbright.h"			// 9D8C15CA
#include "ICZ/StarPointer.h"			// 804AD12D
#include "ICZ/CrushingColumn.h"			// A5F30B34
#include "ICZ/Freezer.h"			// DE608819
#include "ICZ/SegmentedColumn.h"			// 5EE8DBE4
#include "ICZ/SwingingPlatform.h"			// 3200872E
#include "ICZ/Stalagtite.h"			// C73D2821
#include "ICZ/IceCube.h"			// E855624C
#include "ICZ/HarmfulIce.h"			// 8BC9A52C
#include "ICZ/SnowPile.h"			// CF9FDC21
#include "LBZ/Orbinaut.h"			// 75BEA9FB
#include "AIZ/AirshipBomb.h"			// 8E8C37A1
#include "AIZ/BloominatorSpore.h"			// BF8DF98A
#include "AIZ/FireBreathBomb.h"			// A1BB73AA
#include "AIZ/FireBreathFlame.h"			// CE81DA7E
#include "AIZ/MonkeyDudeCoconut.h"			// 5C688649
#include "CNZ/BatbrightParts.h"			// D5ADBFDB
#include "Common/BlankObject.h"			// 8D487F51
#include "Common/BubbleAir.h"			// 11DAFFC3
#include "Common/PlaneSwitcher.h"			// 7573BB38
#include "Common/PlatformOutliner.h"			// 5DFC3336
#include "Common/PlayerSpawn.h"			// EACB9471
#include "Common/WarpStars.h"			// 7E49DBD3
#include "CommonSpecial/EggCapsuleButton.h"			// A0128E04
#include "CommonSpecial/Signpost.h"			// 6A8C340C
#include "CommonSpecial/TensionBridgeChild.h"			// 8ED6F84C
#include "CommonSpecial/ViewCollisionToggler.h"			// 27340CB0
#include "GHZ/Motobug.h"			// 219C1E61
#include "GHZ/MotobugSmoke.h"			// 5B38E7A8
#include "HCZ/BlastoidShot.h"			// 3692A9F5
#include "HCZ/DepthCharge.h"			// B708D750
#include "HCZ/TurboSpikerSpike.h"			// 77A23BDE
#include "ICZ/SegmentedColumnStub.h"			// 91BDF05
#include "ICZ/StarPointerOrbs.h"			// 802D069A
#include "ICZ/SwingingPlatformTrigger.h"			// 7A5BA50E
#include "MGZ/ReliefEye.h"			// BBCA6AC5
#include "Test/Platform.h"			// C4B304CC


enum {
    Obj_Ring = 0x000,
    Obj_Monitor = 0x001,
    Obj_HollowTree = 0x003,
    Obj_CollapsingPlatform = 0x004,
    Obj_Rock = 0x005,
    Obj_RideVine = 0x006,
    Obj_Spring = 0x007,
    Obj_Spikes = 0x008,
    Obj_TreeBark = 0x009,
    Obj_RopePeg = 0x00A,
    Obj_SwingVine = 0x00C,
    Obj_BreakableWall = 0x00D,
    Obj_Ridge = 0x00E,
    Obj_CollapsingBridge = 0x00F,
    Obj_AutomaticTunnel = 0x024,
    Obj_RollEnforcer = 0x026,
    Obj_InvisibleBlock = 0x028,
    Obj_DisappearingFloor = 0x029,
    Obj_CorkFloor = 0x02A,
    Obj_FlippingBridge = 0x02B,
    Obj_CollapsingLogBridge = 0x02C,
    Obj_FallingLog = 0x02D,
    Obj_SpikedLog = 0x02E,
    Obj_NonAnim = 0x02F,
    Obj_AnimSprite = 0x030,
    Obj_Drawbridge = 0x032,
    Obj_Button = 0x033,
    Obj_StarPost = 0x034,
    Obj_ForegroundPlant = 0x035,
    Obj_BreakBar = 0x036,
    Obj_HCZVWaterStream = 0x037,
    Obj_Fan = 0x038,
    Obj_LargeFan = 0x039,
    Obj_HandLauncher = 0x03A,
    Obj_HCZWaterWall = 0x03B,
    Obj_Door = 0x03C,
    Obj_HCZConveyorBelt = 0x03E,
    Obj_HCZConveyorSpike = 0x03F,
    Obj_Block = 0x040,
    Obj_Balloon = 0x041,
    Obj_CNZLightBulb = 0x045,
    Obj_HoverFan = 0x046,
    Obj_VacuumTube = 0x048,
    Obj_Bumper = 0x04A,
    Obj_Bouncepad = 0x04B,
    Obj_MGZQuickMud = 0x04F,
    Obj_FloatingPlatform = 0x051,
    Obj_MGZSmashingPillar = 0x052,
    Obj_MGZSwingingPlatform = 0x053,
    Obj_Bubbler = 0x054,
    Obj_Relief = 0x055,
    Obj_MGZTriggerPlatform = 0x057,
    Obj_MGZDashTrigger = 0x059,
    Obj_TopPlatform = 0x05B,
    Obj_HCZSnakeBlocks = 0x067,
    Obj_SpinningColumn = 0x068,
    Obj_HCZSlide = 0x069,
    Obj_InvisibleSpikes = 0x06A,
    Obj_InvisibleDeath = 0x06B,
    Obj_TensionBridge = 0x06C,
    Obj_HCZWaterSplash = 0x06D,
    Obj_HiddenMonitor = 0x080,
    Obj_EggCapsule = 0x081,
    Obj_CutsceneKnuckles = 0x082,
    Obj_SpecialRing = 0x085,
    Obj_Bloominator = 0x08C,
    Obj_RhinoBot = 0x08D,
    Obj_MonkeyDude = 0x08E,
    Obj_CaterkillerJr = 0x08F,
    Obj_FireBreathCutscene = 0x090,
    Obj_FireBreath = 0x091,
    Obj_FlameMobile = 0x092,
    Obj_Jawz = 0x093,
    Obj_Blastoid = 0x094,
    Obj_Buggernaut = 0x095,
    Obj_TurboSpiker = 0x096,
    Obj_MegaChomper = 0x097,
    Obj_Pointdexter = 0x098,
    Obj_BigShaker = 0x099,
    Obj_ScrewMobile = 0x09A,
    Obj_BubblesBadnik = 0x09B,
    Obj_Spiker = 0x09C,
    Obj_Mantis = 0x09D,
    Obj_MGZDriller = 0x09E,
    Obj_TunnelBot = 0x09F,
    Obj_DrillerEggman = 0x0A0,
    Obj_DrillMobile = 0x0A1,
    Obj_Batbright = 0x0A5,
    Obj_StarPointer = 0x0AE,
    Obj_CrushingColumn = 0x0AF,
    Obj_Freezer = 0x0B2,
    Obj_SegmentedColumn = 0x0B3,
    Obj_SwingingPlatform = 0x0B4,
    Obj_Stalagtite = 0x0B5,
    Obj_IceCube = 0x0B6,
    Obj_HarmfulIce = 0x0B8,
    Obj_SnowPile = 0x0B9,
    Obj_Orbinaut = 0x0C0,
    Obj_AirshipBomb = 0x400,
    Obj_BloominatorSpore = 0x401,
    Obj_FireBreathBomb = 0x402,
    Obj_FireBreathFlame = 0x403,
    Obj_MonkeyDudeCoconut = 0x404,
    Obj_BatbrightParts = 0x405,
    Obj_BlankObject = 0x406,
    Obj_BubbleAir = 0x407,
    Obj_PlaneSwitcher = 0x408,
    Obj_PlatformOutliner = 0x409,
    Obj_PlayerSpawn = 0x40A,
    Obj_WarpStars = 0x40B,
    Obj_EggCapsuleButton = 0x40C,
    Obj_Signpost = 0x40D,
    Obj_TensionBridgeChild = 0x40E,
    Obj_ViewCollisionToggler = 0x40F,
    Obj_Motobug = 0x410,
    Obj_MotobugSmoke = 0x411,
    Obj_BlastoidShot = 0x412,
    Obj_DepthCharge = 0x413,
    Obj_TurboSpikerSpike = 0x414,
    Obj_SegmentedColumnStub = 0x415,
    Obj_StarPointerOrbs = 0x416,
    Obj_SwingingPlatformTrigger = 0x417,
    Obj_ReliefEye = 0x418,
    Obj_Platform = 0x419,
};

Object* GetNewObjectFromID(int ID);
Object* GetNewObjectFromCRC32(uint32_t Hash);

#endif /* OBJECTLISTING_H */