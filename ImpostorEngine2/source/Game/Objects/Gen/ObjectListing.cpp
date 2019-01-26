#include "ObjectListing.h"

Object* GetNewObjectFromID(int ID) {
    switch (ID) {
        case 0x09:
            return new Act1TreeBark();
            break;
        case 0x400:
            return new AirshipBomb();
            break;
        case 0x92:
            return new AIZBoss();
            break;
        case 0x91:
            return new AIZMiniboss();
            break;
        case 0x401:
            return new AIZMinibossBomb();
            break;
        case 0x90:
            return new AIZMinibossCutscene();
            break;
        case 0x402:
            return new AIZMinibossFlame();
            break;
        case 0x8C:
            return new Bloominator();
            break;
        case 0x403:
            return new BloominatorSpore();
            break;
        case 0x8F:
            return new CaterkillerJr();
            break;
        case 0x2C:
            return new CollapsingLogBridge();
            break;
        case 0x29:
            return new DisappearingFloor();
            break;
        case 0x32:
            return new Drawbridge();
            break;
        case 0x2D:
            return new FallingLog();
            break;
        case 0x2B:
            return new FlippingBridge();
            break;
        case 0x35:
            return new ForegroundPlant();
            break;
        case 0x03:
            return new HollowTree();
            break;
        case 0x8E:
            return new MonkeyDude();
            break;
        case 0x404:
            return new MonkeyDudeCoconut();
            break;
        case 0x8D:
            return new RhinoBot();
            break;
        case 0x06:
            return new RideVine();
            break;
        case 0x0A:
            return new RopePeg();
            break;
        case 0x2E:
            return new SpikedLog();
            break;
        case 0x0C:
            return new SwingVine();
            break;
        case 0x41:
            return new Balloon();
            break;
        case 0x30:
            return new AnimSprite();
            break;
        case 0x24:
            return new AutomaticTunnel();
            break;
        case 0x0D:
            return new BreakableWall();
            break;
        case 0x405:
            return new BubbleAir();
            break;
        case 0x54:
            return new Bubbler();
            break;
        case 0x33:
            return new Button();
            break;
        case 0x0F:
            return new CollapsingBridge();
            break;
        case 0x04:
            return new CollapsingPlatform();
            break;
        case 0x51:
            return new FloatingPlatform();
            break;
        case 0x80:
            return new HiddenMonitor();
            break;
        case 0x6B:
            return new InvisibleDeath();
            break;
        case 0x28:
            return new InvisibleSolid();
            break;
        case 0x6A:
            return new InvisibleSpikes();
            break;
        case 0x01:
            return new Monitor();
            break;
        case 0x2F:
            return new NonAnim();
            break;
        case 0x0E:
            return new Ridge();
            break;
        case 0x26:
            return new RollEnforcer();
            break;
        case 0x85:
            return new SpecialRing();
            break;
        case 0x08:
            return new Spikes();
            break;
        case 0x07:
            return new Spring();
            break;
        case 0x34:
            return new StarPost();
            break;
        case 0x2A:
            return new CorkFloor();
            break;
        case 0x82:
            return new CutsceneKnuckles();
            break;
        case 0x3C:
            return new Door();
            break;
        case 0x81:
            return new EggCapsule();
            break;
        case 0x406:
            return new EggCapsuleButton();
            break;
        case 0x05:
            return new Rock();
            break;
        case 0x407:
            return new Signpost();
            break;
        case 0x6C:
            return new TensionBridge();
            break;
        case 0x408:
            return new TensionBridgeChild();
            break;
        case 0x94:
            return new Blastoid();
            break;
        case 0x409:
            return new BlastoidShot();
            break;
        case 0x40:
            return new Block();
            break;
        case 0x36:
            return new BreakBar();
            break;
        case 0x95:
            return new Buggernaut();
            break;
        case 0x38:
            return new Fan();
            break;
        case 0x3A:
            return new HandLauncher();
            break;
        case 0x3E:
            return new HCZConveyorBelt();
            break;
        case 0x3F:
            return new HCZConveyorSpike();
            break;
        case 0x69:
            return new HCZSlide();
            break;
        case 0x67:
            return new HCZSnakeBlocks();
            break;
        case 0x37:
            return new HCZVWaterStream();
            break;
        case 0x6D:
            return new HCZWaterSplash();
            break;
        case 0x3B:
            return new HCZWaterWall();
            break;
        case 0x99:
            return new HCZ_Miniboss();
            break;
        case 0x93:
            return new Jawz();
            break;
        case 0x39:
            return new LargeFan();
            break;
        case 0x97:
            return new MegaChomper();
            break;
        case 0x98:
            return new Pointdexter();
            break;
        case 0x68:
            return new SpinningColumn();
            break;
        case 0x96:
            return new TurboSpiker();
            break;
        case 0x59:
            return new MGZDashTrigger();
            break;
        case 0x55:
            return new MGZHeadTrigger();
            break;
        case 0x40A:
            return new MGZHeadTrigger_Eye();
            break;
        case 0x4F:
            return new MGZQuickMud();
            break;
        case 0x53:
            return new MGZSwingingPlatform();
            break;
        case 0x57:
            return new MGZTriggerPlatform();
            break;

        default:
            break;
    }
    return NULL;
}