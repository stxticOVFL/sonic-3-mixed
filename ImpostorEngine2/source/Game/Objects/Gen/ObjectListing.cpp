#include "ObjectListing.h"

Object* GetNewObjectFromID(int ID) {
    switch (ID) {
        case 0x01:
            return new Monitor();
            break;
        case 0x03:
            return new HollowTree();
            break;
        case 0x04:
            return new CollapsingPlatform();
            break;
        case 0x05:
            return new Rock();
            break;
        case 0x06:
            return new RideVine();
            break;
        case 0x07:
            return new Spring();
            break;
        case 0x08:
            return new Spikes();
            break;
        case 0x09:
            return new AIZTreeBark();
            break;
        case 0x0A:
            return new RopePeg();
            break;
        case 0x0C:
            return new SwingVine();
            break;
        case 0x0D:
            return new BreakableWall();
            break;
        case 0x0E:
            return new Ridge();
            break;
        case 0x0F:
            return new CollapsingBridge();
            break;
        case 0x24:
            return new AutomaticTunnel();
            break;
        case 0x26:
            return new RollEnforcer();
            break;
        case 0x28:
            return new InvisibleSolid();
            break;
        case 0x29:
            return new DisappearingFloor();
            break;
        case 0x2A:
            return new CorkFloor();
            break;
        case 0x2B:
            return new FlippingBridge();
            break;
        case 0x2C:
            return new CollapsingLogBridge();
            break;
        case 0x2D:
            return new FallingLog();
            break;
        case 0x2E:
            return new SpikedLog();
            break;
        case 0x2F:
            return new NonAnim();
            break;
        case 0x30:
            return new AnimSprite();
            break;
        case 0x32:
            return new Drawbridge();
            break;
        case 0x33:
            return new Button();
            break;
        case 0x34:
            return new StarPost();
            break;
        case 0x35:
            return new ForegroundPlant();
            break;
        case 0x36:
            return new BreakBar();
            break;
        case 0x37:
            return new HCZVWaterStream();
            break;
        case 0x38:
            return new Fan();
            break;
        case 0x39:
            return new LargeFan();
            break;
        case 0x3A:
            return new HandLauncher();
            break;
        case 0x3B:
            return new HCZWaterWall();
            break;
        case 0x3C:
            return new Door();
            break;
        case 0x3E:
            return new HCZConveyorBelt();
            break;
        case 0x3F:
            return new HCZConveyorSpike();
            break;
        case 0x40:
            return new Block();
            break;
        case 0x41:
            return new Balloon();
            break;
        case 0x48:
            return new VacuumTube();
            break;
        case 0x4B:
            return new Bouncepad();
            break;
        case 0x4F:
            return new MGZQuickMud();
            break;
        case 0x51:
            return new FloatingPlatform();
            break;
        case 0x53:
            return new MGZSwingingPlatform();
            break;
        case 0x54:
            return new Bubbler();
            break;
        case 0x55:
            return new MGZHeadTrigger();
            break;
        case 0x57:
            return new MGZTriggerPlatform();
            break;
        case 0x59:
            return new MGZDashTrigger();
            break;
        case 0x67:
            return new HCZSnakeBlocks();
            break;
        case 0x68:
            return new SpinningColumn();
            break;
        case 0x69:
            return new HCZSlide();
            break;
        case 0x6A:
            return new InvisibleSpikes();
            break;
        case 0x6B:
            return new InvisibleDeath();
            break;
        case 0x6C:
            return new TensionBridge();
            break;
        case 0x6D:
            return new HCZWaterSplash();
            break;
        case 0x80:
            return new HiddenMonitor();
            break;
        case 0x81:
            return new EggCapsule();
            break;
        case 0x82:
            return new CutsceneKnuckles();
            break;
        case 0x85:
            return new SpecialRing();
            break;
        case 0x8C:
            return new Bloominator();
            break;
        case 0x8D:
            return new RhinoBot();
            break;
        case 0x8E:
            return new MonkeyDude();
            break;
        case 0x8F:
            return new CaterkillerJr();
            break;
        case 0x90:
            return new AIZMinibossCutscene();
            break;
        case 0x91:
            return new AIZMiniboss();
            break;
        case 0x92:
            return new AIZBoss();
            break;
        case 0x93:
            return new Jawz();
            break;
        case 0x94:
            return new Blastoid();
            break;
        case 0x95:
            return new Buggernaut();
            break;
        case 0x96:
            return new TurboSpiker();
            break;
        case 0x97:
            return new MegaChomper();
            break;
        case 0x98:
            return new Pointdexter();
            break;
        case 0x99:
            return new HCZ_Miniboss();
            break;
        case 0xA5:
            return new Batbright();
            break;
        case 0x400:
            return new AirshipBomb();
            break;
        case 0x401:
            return new AIZMinibossBomb();
            break;
        case 0x402:
            return new AIZMinibossFlame();
            break;
        case 0x403:
            return new BloominatorSpore();
            break;
        case 0x404:
            return new MonkeyDudeCoconut();
            break;
        case 0x405:
            return new BatbrightParts();
            break;
        case 0x406:
            return new BubbleAir();
            break;
        case 0x407:
            return new EggCapsuleButton();
            break;
        case 0x408:
            return new Signpost();
            break;
        case 0x409:
            return new TensionBridgeChild();
            break;
        case 0x40A:
            return new BlastoidShot();
            break;
        case 0x40B:
            return new MGZHeadTrigger_Eye();
            break;

        default:
            break;
    }
    return NULL;
}

Object* GetNewObjectFromCRC32(uint32_t Hash) {
    switch (Hash) {
        case 0xB3C47F67:
            return new Monitor();
            break;
        case 0x41FD35EA:
            return new HollowTree();
            break;
        case 0xFD8527A9:
            return new CollapsingPlatform();
            break;
        case 0xB63FCB80:
            return new Rock();
            break;
        case 0xA45C3BD3:
            return new RideVine();
            break;
        case 0xDD50B0FC:
            return new Spring();
            break;
        case 0xA0E2B9BA:
            return new Spikes();
            break;
        case 0x8E04E942:
            return new AIZTreeBark();
            break;
        case 0x1F22E746:
            return new RopePeg();
            break;
        case 0x854E5A54:
            return new SwingVine();
            break;
        case 0x683F24E7:
            return new BreakableWall();
            break;
        case 0x5C472F69:
            return new Ridge();
            break;
        case 0xD76CA9CF:
            return new CollapsingBridge();
            break;
        case 0x2384A243:
            return new AutomaticTunnel();
            break;
        case 0x30FD5555:
            return new RollEnforcer();
            break;
        case 0x33905189:
            return new InvisibleSolid();
            break;
        case 0x2BB0E102:
            return new DisappearingFloor();
            break;
        case 0x4EB6BD79:
            return new CorkFloor();
            break;
        case 0x34040207:
            return new FlippingBridge();
            break;
        case 0xB5E83566:
            return new CollapsingLogBridge();
            break;
        case 0xF4D5DE56:
            return new FallingLog();
            break;
        case 0x363775D2:
            return new SpikedLog();
            break;
        case 0x2D496EFE:
            return new NonAnim();
            break;
        case 0x436F8B16:
            return new AnimSprite();
            break;
        case 0xA430AC35:
            return new Drawbridge();
            break;
        case 0x8C6808A8:
            return new Button();
            break;
        case 0x58C873E2:
            return new StarPost();
            break;
        case 0x5024EE87:
            return new ForegroundPlant();
            break;
        case 0xB1F0A7DC:
            return new BreakBar();
            break;
        case 0xBFAD8B0F:
            return new HCZVWaterStream();
            break;
        case 0xA2FBE7CB:
            return new Fan();
            break;
        case 0x9008779E:
            return new LargeFan();
            break;
        case 0x8E5CE4B7:
            return new HandLauncher();
            break;
        case 0x8C0E6251:
            return new HCZWaterWall();
            break;
        case 0xB93240F:
            return new Door();
            break;
        case 0xB9538011:
            return new HCZConveyorBelt();
            break;
        case 0xA607334F:
            return new HCZConveyorSpike();
            break;
        case 0x84F84F3B:
            return new Block();
            break;
        case 0x36EADD72:
            return new Balloon();
            break;
        case 0x592DBA0E:
            return new VacuumTube();
            break;
        case 0xC5A3956B:
            return new Bouncepad();
            break;
        case 0xDC819A61:
            return new MGZQuickMud();
            break;
        case 0x2DF7EC71:
            return new FloatingPlatform();
            break;
        case 0xD690B204:
            return new MGZSwingingPlatform();
            break;
        case 0x1DEA5E31:
            return new Bubbler();
            break;
        case 0xECB747B3:
            return new MGZHeadTrigger();
            break;
        case 0xE722BDDC:
            return new MGZTriggerPlatform();
            break;
        case 0x3ADF0AB6:
            return new MGZDashTrigger();
            break;
        case 0xED0D528C:
            return new HCZSnakeBlocks();
            break;
        case 0x29649950:
            return new SpinningColumn();
            break;
        case 0x5782AB56:
            return new HCZSlide();
            break;
        case 0x92AA9E1D:
            return new InvisibleSpikes();
            break;
        case 0x70EF491B:
            return new InvisibleDeath();
            break;
        case 0x9B8ADC00:
            return new TensionBridge();
            break;
        case 0x89AE4C47:
            return new HCZWaterSplash();
            break;
        case 0xA255CEA:
            return new HiddenMonitor();
            break;
        case 0xA06CE4A:
            return new EggCapsule();
            break;
        case 0x376AFB5F:
            return new CutsceneKnuckles();
            break;
        case 0xD06B97DF:
            return new SpecialRing();
            break;
        case 0xA07A35BB:
            return new Bloominator();
            break;
        case 0x3F51D31:
            return new RhinoBot();
            break;
        case 0x72B02A01:
            return new MonkeyDude();
            break;
        case 0x4B9B3432:
            return new CaterkillerJr();
            break;
        case 0x38B8F76D:
            return new AIZMinibossCutscene();
            break;
        case 0x87C53D97:
            return new AIZMiniboss();
            break;
        case 0x700E41B:
            return new AIZBoss();
            break;
        case 0x6D126E5D:
            return new Jawz();
            break;
        case 0x3426B98:
            return new Blastoid();
            break;
        case 0xF8A3BE39:
            return new Buggernaut();
            break;
        case 0x3E8719CF:
            return new TurboSpiker();
            break;
        case 0xBF4B1DA7:
            return new MegaChomper();
            break;
        case 0xEC9181EB:
            return new Pointdexter();
            break;
        case 0x6FC83AFC:
            return new HCZ_Miniboss();
            break;
        case 0xC3D653C4:
            return new Batbright();
            break;
        case 0xA9B7215F:
            return new AirshipBomb();
            break;
        case 0xC80C9363:
            return new AIZMinibossBomb();
            break;
        case 0x801C4523:
            return new AIZMinibossFlame();
            break;
        case 0x205577C0:
            return new BloominatorSpore();
            break;
        case 0xA74EABF8:
            return new MonkeyDudeCoconut();
            break;
        case 0xC25D5CBF:
            return new BatbrightParts();
            break;
        case 0x6697FD9C:
            return new BubbleAir();
            break;
        case 0x5C72AD12:
            return new EggCapsuleButton();
            break;
        case 0x8DBAB84C:
            return new Signpost();
            break;
        case 0x37C54796:
            return new TensionBridgeChild();
            break;
        case 0x4D41692E:
            return new BlastoidShot();
            break;
        case 0x5E30EBAA:
            return new MGZHeadTrigger_Eye();
            break;

        default:
            break;
    }
    return NULL;
}