#include "ObjectListing.h"

Object* GetNewObjectFromID(int ID) {
    switch (ID) {
        case 0x01U:
            return new Monitor();
            break;
        case 0x03U:
            return new HollowTree();
            break;
        case 0x04U:
            return new CollapsingPlatform();
            break;
        case 0x05U:
            return new Rock();
            break;
        case 0x06U:
            return new RideVine();
            break;
        case 0x07U:
            return new Spring();
            break;
        case 0x08U:
            return new Spikes();
            break;
        case 0x09U:
            return new TreeBark();
            break;
        case 0x0AU:
            return new RopePeg();
            break;
        case 0x0CU:
            return new SwingVine();
            break;
        case 0x0DU:
            return new BreakableWall();
            break;
        case 0x0EU:
            return new Ridge();
            break;
        case 0x0FU:
            return new CollapsingBridge();
            break;
        case 0x24U:
            return new AutomaticTunnel();
            break;
        case 0x26U:
            return new RollEnforcer();
            break;
        case 0x28U:
            return new InvisibleBlock();
            break;
        case 0x29U:
            return new DisappearingFloor();
            break;
        case 0x2AU:
            return new CorkFloor();
            break;
        case 0x2BU:
            return new FlippingBridge();
            break;
        case 0x2CU:
            return new CollapsingLogBridge();
            break;
        case 0x2DU:
            return new FallingLog();
            break;
        case 0x2EU:
            return new SpikedLog();
            break;
        case 0x2FU:
            return new NonAnim();
            break;
        case 0x30U:
            return new AnimSprite();
            break;
        case 0x32U:
            return new Drawbridge();
            break;
        case 0x33U:
            return new Button();
            break;
        case 0x34U:
            return new StarPost();
            break;
        case 0x35U:
            return new ForegroundPlant();
            break;
        case 0x36U:
            return new BreakBar();
            break;
        case 0x37U:
            return new HCZVWaterStream();
            break;
        case 0x38U:
            return new Fan();
            break;
        case 0x39U:
            return new LargeFan();
            break;
        case 0x3AU:
            return new HandLauncher();
            break;
        case 0x3BU:
            return new HCZWaterWall();
            break;
        case 0x3CU:
            return new Door();
            break;
        case 0x3EU:
            return new HCZConveyorBelt();
            break;
        case 0x3FU:
            return new HCZConveyorSpike();
            break;
        case 0x40U:
            return new Block();
            break;
        case 0x41U:
            return new Balloon();
            break;
        case 0x46U:
            return new HoverFan();
            break;
        case 0x48U:
            return new VacuumTube();
            break;
        case 0x4BU:
            return new Bouncepad();
            break;
        case 0x4FU:
            return new MGZQuickMud();
            break;
        case 0x51U:
            return new FloatingPlatform();
            break;
        case 0x53U:
            return new MGZSwingingPlatform();
            break;
        case 0x54U:
            return new Bubbler();
            break;
        case 0x55U:
            return new Relief();
            break;
        case 0x57U:
            return new MGZTriggerPlatform();
            break;
        case 0x59U:
            return new MGZDashTrigger();
            break;
        case 0x67U:
            return new HCZSnakeBlocks();
            break;
        case 0x68U:
            return new SpinningColumn();
            break;
        case 0x69U:
            return new HCZSlide();
            break;
        case 0x6AU:
            return new InvisibleSpikes();
            break;
        case 0x6BU:
            return new InvisibleDeath();
            break;
        case 0x6CU:
            return new TensionBridge();
            break;
        case 0x6DU:
            return new HCZWaterSplash();
            break;
        case 0x80U:
            return new HiddenMonitor();
            break;
        case 0x81U:
            return new EggCapsule();
            break;
        case 0x82U:
            return new CutsceneKnuckles();
            break;
        case 0x85U:
            return new SpecialRing();
            break;
        case 0x8CU:
            return new Bloominator();
            break;
        case 0x8DU:
            return new RhinoBot();
            break;
        case 0x8EU:
            return new MonkeyDude();
            break;
        case 0x8FU:
            return new CaterkillerJr();
            break;
        case 0x90U:
            return new AIZMinibossCutscene();
            break;
        case 0x91U:
            return new AIZMiniboss();
            break;
        case 0x92U:
            return new AIZBoss();
            break;
        case 0x93U:
            return new Jawz();
            break;
        case 0x94U:
            return new Blastoid();
            break;
        case 0x95U:
            return new Buggernaut();
            break;
        case 0x96U:
            return new TurboSpiker();
            break;
        case 0x97U:
            return new MegaChomper();
            break;
        case 0x98U:
            return new Pointdexter();
            break;
        case 0x99U:
            return new HCZMiniboss();
            break;
        case 0x9AU:
            return new HCZBoss();
            break;
        case 0x9BU:
            return new BubblesBadnik();
            break;
        case 0x9CU:
            return new Spiker();
            break;
        case 0x9DU:
            return new Mantis();
            break;
        case 0x9EU:
            return new MGZDriller();
            break;
        case 0x9FU:
            return new MGZMiniBoss();
            break;
        case 0xA0U:
            return new DrillerEggman();
            break;
        case 0xA1U:
            return new MGZBoss();
            break;
        case 0xA5U:
            return new Batbright();
            break;
        case 0x400U:
            return new AirshipBomb();
            break;
        case 0x401U:
            return new AIZMinibossBomb();
            break;
        case 0x402U:
            return new AIZMinibossFlame();
            break;
        case 0x403U:
            return new BloominatorSpore();
            break;
        case 0x404U:
            return new MonkeyDudeCoconut();
            break;
        case 0x405U:
            return new BatbrightParts();
            break;
        case 0x406U:
            return new BubbleAir();
            break;
        case 0x407U:
            return new EggCapsuleButton();
            break;
        case 0x408U:
            return new Signpost();
            break;
        case 0x409U:
            return new TensionBridgeChild();
            break;
        case 0x40AU:
            return new ViewCollisionToggler();
            break;
        case 0x40BU:
            return new BlastoidShot();
            break;
        case 0x40CU:
            return new ReliefEye();
            break;
        case 0x40DU:
            return new Platform();
            break;

        default:
            break;
    }
    return NULL;
}

Object* GetNewObjectFromCRC32(uint32_t Hash) {
    switch (Hash) {
        case 0xB3C47F67U:
            return new Monitor();
            break;
        case 0x41FD35EAU:
            return new HollowTree();
            break;
        case 0xFD8527A9U:
            return new CollapsingPlatform();
            break;
        case 0xB63FCB80U:
            return new Rock();
            break;
        case 0xA45C3BD3U:
            return new RideVine();
            break;
        case 0xDD50B0FCU:
            return new Spring();
            break;
        case 0xA0E2B9BAU:
            return new Spikes();
            break;
        case 0x1C11C8EFU:
            return new TreeBark();
            break;
        case 0x1F22E746U:
            return new RopePeg();
            break;
        case 0x854E5A54U:
            return new SwingVine();
            break;
        case 0x683F24E7U:
            return new BreakableWall();
            break;
        case 0x5C472F69U:
            return new Ridge();
            break;
        case 0xD76CA9CFU:
            return new CollapsingBridge();
            break;
        case 0x2384A243U:
            return new AutomaticTunnel();
            break;
        case 0x30FD5555U:
            return new RollEnforcer();
            break;
        case 0x14B30B17U:
            return new InvisibleBlock();
            break;
        case 0x2BB0E102U:
            return new DisappearingFloor();
            break;
        case 0x4EB6BD79U:
            return new CorkFloor();
            break;
        case 0x34040207U:
            return new FlippingBridge();
            break;
        case 0xB5E83566U:
            return new CollapsingLogBridge();
            break;
        case 0xF4D5DE56U:
            return new FallingLog();
            break;
        case 0x363775D2U:
            return new SpikedLog();
            break;
        case 0x2D496EFEU:
            return new NonAnim();
            break;
        case 0x436F8B16U:
            return new AnimSprite();
            break;
        case 0xA430AC35U:
            return new Drawbridge();
            break;
        case 0x8C6808A8U:
            return new Button();
            break;
        case 0x58C873E2U:
            return new StarPost();
            break;
        case 0x5024EE87U:
            return new ForegroundPlant();
            break;
        case 0xB1F0A7DCU:
            return new BreakBar();
            break;
        case 0xBFAD8B0FU:
            return new HCZVWaterStream();
            break;
        case 0xA2FBE7CBU:
            return new Fan();
            break;
        case 0x9008779EU:
            return new LargeFan();
            break;
        case 0x8E5CE4B7U:
            return new HandLauncher();
            break;
        case 0x8C0E6251U:
            return new HCZWaterWall();
            break;
        case 0xB93240FU:
            return new Door();
            break;
        case 0xB9538011U:
            return new HCZConveyorBelt();
            break;
        case 0xA607334FU:
            return new HCZConveyorSpike();
            break;
        case 0x84F84F3BU:
            return new Block();
            break;
        case 0x36EADD72U:
            return new Balloon();
            break;
        case 0x68E27C69U:
            return new HoverFan();
            break;
        case 0x592DBA0EU:
            return new VacuumTube();
            break;
        case 0xC5A3956BU:
            return new Bouncepad();
            break;
        case 0xDC819A61U:
            return new MGZQuickMud();
            break;
        case 0x2DF7EC71U:
            return new FloatingPlatform();
            break;
        case 0xD690B204U:
            return new MGZSwingingPlatform();
            break;
        case 0x1DEA5E31U:
            return new Bubbler();
            break;
        case 0x9A39B25AU:
            return new Relief();
            break;
        case 0xE722BDDCU:
            return new MGZTriggerPlatform();
            break;
        case 0x3ADF0AB6U:
            return new MGZDashTrigger();
            break;
        case 0xED0D528CU:
            return new HCZSnakeBlocks();
            break;
        case 0x29649950U:
            return new SpinningColumn();
            break;
        case 0x5782AB56U:
            return new HCZSlide();
            break;
        case 0x92AA9E1DU:
            return new InvisibleSpikes();
            break;
        case 0x70EF491BU:
            return new InvisibleDeath();
            break;
        case 0x9B8ADC00U:
            return new TensionBridge();
            break;
        case 0x89AE4C47U:
            return new HCZWaterSplash();
            break;
        case 0xA255CEAU:
            return new HiddenMonitor();
            break;
        case 0xA06CE4AU:
            return new EggCapsule();
            break;
        case 0x376AFB5FU:
            return new CutsceneKnuckles();
            break;
        case 0xD06B97DFU:
            return new SpecialRing();
            break;
        case 0xA07A35BBU:
            return new Bloominator();
            break;
        case 0x3F51D31U:
            return new RhinoBot();
            break;
        case 0x72B02A01U:
            return new MonkeyDude();
            break;
        case 0x4B9B3432U:
            return new CaterkillerJr();
            break;
        case 0x38B8F76DU:
            return new AIZMinibossCutscene();
            break;
        case 0x87C53D97U:
            return new AIZMiniboss();
            break;
        case 0x700E41BU:
            return new AIZBoss();
            break;
        case 0x6D126E5DU:
            return new Jawz();
            break;
        case 0x3426B98U:
            return new Blastoid();
            break;
        case 0xF8A3BE39U:
            return new Buggernaut();
            break;
        case 0x3E8719CFU:
            return new TurboSpiker();
            break;
        case 0xBF4B1DA7U:
            return new MegaChomper();
            break;
        case 0xEC9181EBU:
            return new Pointdexter();
            break;
        case 0xEBAA93DBU:
            return new HCZMiniboss();
            break;
        case 0x330382AEU:
            return new HCZBoss();
            break;
        case 0x3DDE24B3U:
            return new BubblesBadnik();
            break;
        case 0xD7E5892CU:
            return new Spiker();
            break;
        case 0xE2A6F79BU:
            return new Mantis();
            break;
        case 0xE1611041U:
            return new MGZDriller();
            break;
        case 0x332430DDU:
            return new MGZMiniBoss();
            break;
        case 0x4839048AU:
            return new DrillerEggman();
            break;
        case 0xFAAAEF1FU:
            return new MGZBoss();
            break;
        case 0xC3D653C4U:
            return new Batbright();
            break;
        case 0xA9B7215FU:
            return new AirshipBomb();
            break;
        case 0xC80C9363U:
            return new AIZMinibossBomb();
            break;
        case 0x801C4523U:
            return new AIZMinibossFlame();
            break;
        case 0x205577C0U:
            return new BloominatorSpore();
            break;
        case 0xA74EABF8U:
            return new MonkeyDudeCoconut();
            break;
        case 0xC25D5CBFU:
            return new BatbrightParts();
            break;
        case 0x6697FD9CU:
            return new BubbleAir();
            break;
        case 0x5C72AD12U:
            return new EggCapsuleButton();
            break;
        case 0x8DBAB84CU:
            return new Signpost();
            break;
        case 0x37C54796U:
            return new TensionBridgeChild();
            break;
        case 0x7D412B08U:
            return new ViewCollisionToggler();
            break;
        case 0x4D41692EU:
            return new BlastoidShot();
            break;
        case 0x5DA9F78DU:
            return new ReliefEye();
            break;
        case 0xA5066DF4U:
            return new Platform();
            break;

        default:
            break;
    }
    return NULL;
}