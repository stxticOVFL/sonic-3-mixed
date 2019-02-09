#ifndef OBJECTLISTING_H
#define OBJECTLISTING_H

#include "AIZ/Act1TreeBark.h"
#include "AIZ/AirshipBomb.h"
#include "AIZ/AIZBoss.h"
#include "AIZ/AIZMiniboss.h"
#include "AIZ/AIZMinibossBomb.h"
#include "AIZ/AIZMinibossCutscene.h"
#include "AIZ/AIZMinibossFlame.h"
#include "AIZ/Bloominator.h"
#include "AIZ/BloominatorSpore.h"
#include "AIZ/CaterkillerJr.h"
#include "AIZ/CollapsingLogBridge.h"
#include "AIZ/DisappearingFloor.h"
#include "AIZ/Drawbridge.h"
#include "AIZ/FallingLog.h"
#include "AIZ/FlippingBridge.h"
#include "AIZ/ForegroundPlant.h"
#include "AIZ/HollowTree.h"
#include "AIZ/MonkeyDude.h"
#include "AIZ/MonkeyDudeCoconut.h"
#include "AIZ/RhinoBot.h"
#include "AIZ/RideVine.h"
#include "AIZ/RopePeg.h"
#include "AIZ/SpikedLog.h"
#include "AIZ/SwingVine.h"
#include "CNZ/Balloon.h"
#include "CNZ/Batbright.h"
#include "CNZ/BatbrightParts.h"
#include "CNZ/Bouncepad.h"
#include "Common/AnimSprite.h"
#include "Common/AutomaticTunnel.h"
#include "Common/BreakableWall.h"
#include "Common/BubbleAir.h"
#include "Common/Bubbler.h"
#include "Common/Button.h"
#include "Common/CollapsingBridge.h"
#include "Common/CollapsingPlatform.h"
#include "Common/FloatingPlatform.h"
#include "Common/HiddenMonitor.h"
#include "Common/InvisibleDeath.h"
#include "Common/InvisibleSolid.h"
#include "Common/InvisibleSpikes.h"
#include "Common/Monitor.h"
#include "Common/NonAnim.h"
#include "Common/Ridge.h"
#include "Common/RollEnforcer.h"
#include "Common/SpecialRing.h"
#include "Common/Spikes.h"
#include "Common/Spring.h"
#include "Common/StarPost.h"
#include "CommonSpecial/CorkFloor.h"
#include "CommonSpecial/CutsceneKnuckles.h"
#include "CommonSpecial/Door.h"
#include "CommonSpecial/EggCapsule.h"
#include "CommonSpecial/EggCapsuleButton.h"
#include "CommonSpecial/Rock.h"
#include "CommonSpecial/Signpost.h"
#include "CommonSpecial/TensionBridge.h"
#include "CommonSpecial/TensionBridgeChild.h"
#include "HCZ/Blastoid.h"
#include "HCZ/BlastoidShot.h"
#include "HCZ/Block.h"
#include "HCZ/BreakBar.h"
#include "HCZ/Buggernaut.h"
#include "HCZ/Fan.h"
#include "HCZ/HandLauncher.h"
#include "HCZ/HCZConveyorBelt.h"
#include "HCZ/HCZConveyorSpike.h"
#include "HCZ/HCZSlide.h"
#include "HCZ/HCZSnakeBlocks.h"
#include "HCZ/HCZVWaterStream.h"
#include "HCZ/HCZWaterSplash.h"
#include "HCZ/HCZWaterWall.h"
#include "HCZ/HCZ_Miniboss.h"
#include "HCZ/Jawz.h"
#include "HCZ/LargeFan.h"
#include "HCZ/MegaChomper.h"
#include "HCZ/Pointdexter.h"
#include "HCZ/SpinningColumn.h"
#include "HCZ/TurboSpiker.h"
#include "MGZ/MGZDashTrigger.h"
#include "MGZ/MGZHeadTrigger.h"
#include "MGZ/MGZHeadTrigger_Eye.h"
#include "MGZ/MGZQuickMud.h"
#include "MGZ/MGZSwingingPlatform.h"
#include "MGZ/MGZTriggerPlatform.h"


enum {
    Obj_Act1TreeBark = 0x009,
    Obj_AirshipBomb = 0x400,
    Obj_AIZBoss = 0x092,
    Obj_AIZMiniboss = 0x091,
    Obj_AIZMinibossBomb = 0x401,
    Obj_AIZMinibossCutscene = 0x090,
    Obj_AIZMinibossFlame = 0x402,
    Obj_Bloominator = 0x08C,
    Obj_BloominatorSpore = 0x403,
    Obj_CaterkillerJr = 0x08F,
    Obj_CollapsingLogBridge = 0x02C,
    Obj_DisappearingFloor = 0x029,
    Obj_Drawbridge = 0x032,
    Obj_FallingLog = 0x02D,
    Obj_FlippingBridge = 0x02B,
    Obj_ForegroundPlant = 0x035,
    Obj_HollowTree = 0x003,
    Obj_MonkeyDude = 0x08E,
    Obj_MonkeyDudeCoconut = 0x404,
    Obj_RhinoBot = 0x08D,
    Obj_RideVine = 0x006,
    Obj_RopePeg = 0x00A,
    Obj_SpikedLog = 0x02E,
    Obj_SwingVine = 0x00C,
    Obj_Balloon = 0x041,
    Obj_Batbright = 0x0A5,
    Obj_BatbrightParts = 0x405,
    Obj_Bouncepad = 0x04B,
    Obj_AnimSprite = 0x030,
    Obj_AutomaticTunnel = 0x024,
    Obj_BreakableWall = 0x00D,
    Obj_BubbleAir = 0x406,
    Obj_Bubbler = 0x054,
    Obj_Button = 0x033,
    Obj_CollapsingBridge = 0x00F,
    Obj_CollapsingPlatform = 0x004,
    Obj_FloatingPlatform = 0x051,
    Obj_HiddenMonitor = 0x080,
    Obj_InvisibleDeath = 0x06B,
    Obj_InvisibleSolid = 0x028,
    Obj_InvisibleSpikes = 0x06A,
    Obj_Monitor = 0x001,
    Obj_NonAnim = 0x02F,
    Obj_Ridge = 0x00E,
    Obj_RollEnforcer = 0x026,
    Obj_SpecialRing = 0x085,
    Obj_Spikes = 0x008,
    Obj_Spring = 0x007,
    Obj_StarPost = 0x034,
    Obj_CorkFloor = 0x02A,
    Obj_CutsceneKnuckles = 0x082,
    Obj_Door = 0x03C,
    Obj_EggCapsule = 0x081,
    Obj_EggCapsuleButton = 0x407,
    Obj_Rock = 0x005,
    Obj_Signpost = 0x408,
    Obj_TensionBridge = 0x06C,
    Obj_TensionBridgeChild = 0x409,
    Obj_Blastoid = 0x094,
    Obj_BlastoidShot = 0x40A,
    Obj_Block = 0x040,
    Obj_BreakBar = 0x036,
    Obj_Buggernaut = 0x095,
    Obj_Fan = 0x038,
    Obj_HandLauncher = 0x03A,
    Obj_HCZConveyorBelt = 0x03E,
    Obj_HCZConveyorSpike = 0x03F,
    Obj_HCZSlide = 0x069,
    Obj_HCZSnakeBlocks = 0x067,
    Obj_HCZVWaterStream = 0x037,
    Obj_HCZWaterSplash = 0x06D,
    Obj_HCZWaterWall = 0x03B,
    Obj_HCZ_Miniboss = 0x099,
    Obj_Jawz = 0x093,
    Obj_LargeFan = 0x039,
    Obj_MegaChomper = 0x097,
    Obj_Pointdexter = 0x098,
    Obj_SpinningColumn = 0x068,
    Obj_TurboSpiker = 0x096,
    Obj_MGZDashTrigger = 0x059,
    Obj_MGZHeadTrigger = 0x055,
    Obj_MGZHeadTrigger_Eye = 0x40B,
    Obj_MGZQuickMud = 0x04F,
    Obj_MGZSwingingPlatform = 0x053,
    Obj_MGZTriggerPlatform = 0x057,
};

Object* GetNewObjectFromID(int ID);

#endif /* OBJECTLISTING_H */