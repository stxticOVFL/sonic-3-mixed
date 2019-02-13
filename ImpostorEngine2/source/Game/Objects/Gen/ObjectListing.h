#ifndef OBJECTLISTING_H
#define OBJECTLISTING_H

#include "Common/Monitor.h"
#include "AIZ/HollowTree.h"
#include "Common/CollapsingPlatform.h"
#include "CommonSpecial/Rock.h"
#include "AIZ/RideVine.h"
#include "Common/Spring.h"
#include "Common/Spikes.h"
#include "AIZ/AIZTreeBark.h"
#include "AIZ/RopePeg.h"
#include "AIZ/SwingVine.h"
#include "Common/BreakableWall.h"
#include "Common/Ridge.h"
#include "Common/CollapsingBridge.h"
#include "Common/AutomaticTunnel.h"
#include "Common/RollEnforcer.h"
#include "Common/InvisibleSolid.h"
#include "AIZ/DisappearingFloor.h"
#include "CommonSpecial/CorkFloor.h"
#include "AIZ/FlippingBridge.h"
#include "AIZ/CollapsingLogBridge.h"
#include "AIZ/FallingLog.h"
#include "AIZ/SpikedLog.h"
#include "Common/NonAnim.h"
#include "Common/AnimSprite.h"
#include "AIZ/Drawbridge.h"
#include "Common/Button.h"
#include "Common/StarPost.h"
#include "AIZ/ForegroundPlant.h"
#include "HCZ/BreakBar.h"
#include "HCZ/HCZVWaterStream.h"
#include "HCZ/Fan.h"
#include "HCZ/LargeFan.h"
#include "HCZ/HandLauncher.h"
#include "HCZ/HCZWaterWall.h"
#include "CommonSpecial/Door.h"
#include "HCZ/HCZConveyorBelt.h"
#include "HCZ/HCZConveyorSpike.h"
#include "HCZ/Block.h"
#include "CNZ/Balloon.h"
#include "CNZ/VacuumTube.h"
#include "CNZ/Bouncepad.h"
#include "MGZ/MGZQuickMud.h"
#include "Common/FloatingPlatform.h"
#include "MGZ/MGZSwingingPlatform.h"
#include "Common/Bubbler.h"
#include "MGZ/MGZHeadTrigger.h"
#include "MGZ/MGZTriggerPlatform.h"
#include "MGZ/MGZDashTrigger.h"
#include "HCZ/HCZSnakeBlocks.h"
#include "HCZ/SpinningColumn.h"
#include "HCZ/HCZSlide.h"
#include "Common/InvisibleSpikes.h"
#include "Common/InvisibleDeath.h"
#include "CommonSpecial/TensionBridge.h"
#include "HCZ/HCZWaterSplash.h"
#include "Common/HiddenMonitor.h"
#include "CommonSpecial/EggCapsule.h"
#include "CommonSpecial/CutsceneKnuckles.h"
#include "Common/SpecialRing.h"
#include "AIZ/Bloominator.h"
#include "AIZ/RhinoBot.h"
#include "AIZ/MonkeyDude.h"
#include "AIZ/CaterkillerJr.h"
#include "AIZ/AIZMinibossCutscene.h"
#include "AIZ/AIZMiniboss.h"
#include "AIZ/AIZBoss.h"
#include "HCZ/Jawz.h"
#include "HCZ/Blastoid.h"
#include "HCZ/Buggernaut.h"
#include "HCZ/TurboSpiker.h"
#include "HCZ/MegaChomper.h"
#include "HCZ/Pointdexter.h"
#include "HCZ/HCZ_Miniboss.h"
#include "CNZ/Batbright.h"
#include "AIZ/AirshipBomb.h"
#include "AIZ/AIZMinibossBomb.h"
#include "AIZ/AIZMinibossFlame.h"
#include "AIZ/BloominatorSpore.h"
#include "AIZ/MonkeyDudeCoconut.h"
#include "CNZ/BatbrightParts.h"
#include "Common/BubbleAir.h"
#include "CommonSpecial/EggCapsuleButton.h"
#include "CommonSpecial/Signpost.h"
#include "CommonSpecial/TensionBridgeChild.h"
#include "HCZ/BlastoidShot.h"
#include "MGZ/MGZHeadTrigger_Eye.h"


enum {
    Obj_Monitor = 0x001,
    Obj_HollowTree = 0x003,
    Obj_CollapsingPlatform = 0x004,
    Obj_Rock = 0x005,
    Obj_RideVine = 0x006,
    Obj_Spring = 0x007,
    Obj_Spikes = 0x008,
    Obj_AIZTreeBark = 0x009,
    Obj_RopePeg = 0x00A,
    Obj_SwingVine = 0x00C,
    Obj_BreakableWall = 0x00D,
    Obj_Ridge = 0x00E,
    Obj_CollapsingBridge = 0x00F,
    Obj_AutomaticTunnel = 0x024,
    Obj_RollEnforcer = 0x026,
    Obj_InvisibleSolid = 0x028,
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
    Obj_VacuumTube = 0x048,
    Obj_Bouncepad = 0x04B,
    Obj_MGZQuickMud = 0x04F,
    Obj_FloatingPlatform = 0x051,
    Obj_MGZSwingingPlatform = 0x053,
    Obj_Bubbler = 0x054,
    Obj_MGZHeadTrigger = 0x055,
    Obj_MGZTriggerPlatform = 0x057,
    Obj_MGZDashTrigger = 0x059,
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
    Obj_AIZMinibossCutscene = 0x090,
    Obj_AIZMiniboss = 0x091,
    Obj_AIZBoss = 0x092,
    Obj_Jawz = 0x093,
    Obj_Blastoid = 0x094,
    Obj_Buggernaut = 0x095,
    Obj_TurboSpiker = 0x096,
    Obj_MegaChomper = 0x097,
    Obj_Pointdexter = 0x098,
    Obj_HCZ_Miniboss = 0x099,
    Obj_Batbright = 0x0A5,
    Obj_AirshipBomb = 0x400,
    Obj_AIZMinibossBomb = 0x401,
    Obj_AIZMinibossFlame = 0x402,
    Obj_BloominatorSpore = 0x403,
    Obj_MonkeyDudeCoconut = 0x404,
    Obj_BatbrightParts = 0x405,
    Obj_BubbleAir = 0x406,
    Obj_EggCapsuleButton = 0x407,
    Obj_Signpost = 0x408,
    Obj_TensionBridgeChild = 0x409,
    Obj_BlastoidShot = 0x40A,
    Obj_MGZHeadTrigger_Eye = 0x40B,
};

Object* GetNewObjectFromID(int ID);
Object* GetNewObjectFromCRC32(uint32_t Hash);

#endif /* OBJECTLISTING_H */