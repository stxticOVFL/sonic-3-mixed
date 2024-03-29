#include "ObjectListing.h"

Object* GetNewObjectFromID(int ID) {
    switch (ID) {
        case 0x00U:
            return new Ring();
            break;
        case 0x01U:
            return new ItemBox();
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
            return new InvisibleBlockH();
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
            return new NonAnimSprite();
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
            return new BreakableBar();
            break;
        case 0x37U:
            return new VWaterStream();
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
            return new WaterWall();
            break;
        case 0x3CU:
            return new Door();
            break;
        case 0x3EU:
            return new ConveyorBelt();
            break;
        case 0x3FU:
            return new ConveyorSpike();
            break;
        case 0x40U:
            return new Block();
            break;
        case 0x41U:
            return new Balloon();
            break;
        case 0x45U:
            return new CNZLightBulb();
            break;
        case 0x46U:
            return new HoverFan();
            break;
        case 0x47U:
            return new CNZRotatingBarrel();
            break;
        case 0x48U:
            return new VacuumTube();
            break;
        case 0x4AU:
            return new Bumper();
            break;
        case 0x4BU:
            return new Bouncepad();
            break;
        case 0x4FU:
            return new QuickMud();
            break;
        case 0x51U:
            return new FloatingPlatform();
            break;
        case 0x52U:
            return new SmashingPillar();
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
            return new TriggerPlatform();
            break;
        case 0x59U:
            return new DashTrigger();
            break;
        case 0x5BU:
            return new TopPlatform();
            break;
        case 0x67U:
            return new SnakeBlocks();
            break;
        case 0x68U:
            return new SpinningColumn();
            break;
        case 0x69U:
            return new Slide();
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
            return new WaterSplash();
            break;
        case 0x6EU:
            return new WaterDrop();
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
            return new FireBreathCutscene();
            break;
        case 0x91U:
            return new FireBreath();
            break;
        case 0x92U:
            return new FlameMobile();
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
            return new BigShaker();
            break;
        case 0x9AU:
            return new ScrewMobile();
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
            return new TunnelBotCutscene();
            break;
        case 0x9FU:
            return new TunnelBot();
            break;
        case 0xA0U:
            return new DrillerEggman();
            break;
        case 0xA1U:
            return new DrillMobile();
            break;
        case 0xA5U:
            return new Batbright();
            break;
        case 0xAEU:
            return new StarPointer();
            break;
        case 0xAFU:
            return new CrushingColumn();
            break;
        case 0xB2U:
            return new Freezer();
            break;
        case 0xB3U:
            return new SegmentedColumn();
            break;
        case 0xB4U:
            return new ICZSwingingPlatform();
            break;
        case 0xB5U:
            return new Stalagtite();
            break;
        case 0xB6U:
            return new IceCube();
            break;
        case 0xB8U:
            return new HarmfulIce();
            break;
        case 0xB9U:
            return new SnowPile();
            break;
        case 0xC0U:
            return new Orbinaut();
            break;
        case 0x400U:
            return new AirshipBomb();
            break;
        case 0x401U:
            return new AIZControl();
            break;
        case 0x402U:
            return new BloominatorSpore();
            break;
        case 0x403U:
            return new FireBreathBomb();
            break;
        case 0x404U:
            return new FireBreathFlame();
            break;
        case 0x405U:
            return new AIZIntro();
            break;
        case 0x406U:
            return new AIZIntroKnux();
            break;
        case 0x407U:
            return new AIZIntroSplash();
            break;
        case 0x408U:
            return new AIZTornado();
            break;
        case 0x409U:
            return new MonkeyDudeCoconut();
            break;
        case 0x40AU:
            return new BatbrightParts();
            break;
        case 0x40BU:
            return new BlankObject();
            break;
        case 0x40CU:
            return new BoundsMarker();
            break;
        case 0x40DU:
            return new BubbleAir();
            break;
        case 0x40EU:
            return new HUD();
            break;
        case 0x40FU:
            return new InvisibleBlockV();
            break;
        case 0x410U:
            return new Music();
            break;
        case 0x411U:
            return new PauseMenu();
            break;
        case 0x412U:
            return new PlaneSwitcher();
            break;
        case 0x413U:
            return new PlatformOutliner();
            break;
        case 0x414U:
            return new PlayerSpawn();
            break;
        case 0x415U:
            return new TitleCard();
            break;
        case 0x416U:
            return new WarpStars();
            break;
        case 0x417U:
            return new EggCapsuleButton();
            break;
        case 0x418U:
            return new Signpost();
            break;
        case 0x419U:
            return new TensionBridgeChild();
            break;
        case 0x41AU:
            return new ViewCollisionToggler();
            break;
        case 0x41BU:
            return new Motobug();
            break;
        case 0x41CU:
            return new MotobugSmoke();
            break;
        case 0x41DU:
            return new BlastoidShot();
            break;
        case 0x41EU:
            return new DepthCharge();
            break;
        case 0x41FU:
            return new TurboSpikerSpike();
            break;
        case 0x420U:
            return new SegmentedColumnStub();
            break;
        case 0x421U:
            return new StarPointerOrbs();
            break;
        case 0x422U:
            return new SwingingPlatformTrigger();
            break;
        case 0x423U:
            return new ReliefEye();
            break;
        case 0x424U:
            return new Platform();
            break;

        default:
            break;
    }
    return NULL;
}

Object* GetNewObjectFromCRC32(uint32_t Hash) {
    switch (Hash) {
        case 0x2EA61FD6U:
            return new Ring();
            break;
        case 0xD028F874U:
            return new ItemBox();
            break;
        case 0x1E5BFA5FU:
            return new HollowTree();
            break;
        case 0x95087B30U:
            return new CollapsingPlatform();
            break;
        case 0xFE0305DDU:
            return new Rock();
            break;
        case 0x7F20AD1DU:
            return new RideVine();
            break;
        case 0x2802B89EU:
            return new Spring();
            break;
        case 0x44BC7B0EU:
            return new Spikes();
            break;
        case 0x590E62AFU:
            return new TreeBark();
            break;
        case 0x7FB64D3AU:
            return new RopePeg();
            break;
        case 0xD691E4F3U:
            return new SwingVine();
            break;
        case 0x60436E3AU:
            return new BreakableWall();
            break;
        case 0xEC54C850U:
            return new Ridge();
            break;
        case 0x18C4AE0DU:
            return new CollapsingBridge();
            break;
        case 0xC286FB4DU:
            return new AutomaticTunnel();
            break;
        case 0x624D9DA4U:
            return new RollEnforcer();
            break;
        case 0xBF7B0AFDU:
            return new InvisibleBlockH();
            break;
        case 0x16A80CA8U:
            return new DisappearingFloor();
            break;
        case 0x4A50924FU:
            return new CorkFloor();
            break;
        case 0xB48623AU:
            return new FlippingBridge();
            break;
        case 0xC558537EU:
            return new CollapsingLogBridge();
            break;
        case 0xBFF26300U:
            return new FallingLog();
            break;
        case 0x22DC09C3U:
            return new SpikedLog();
            break;
        case 0x71F5C3A7U:
            return new NonAnimSprite();
            break;
        case 0x9B4046ECU:
            return new AnimSprite();
            break;
        case 0x5465065DU:
            return new Drawbridge();
            break;
        case 0xF72B92E4U:
            return new Button();
            break;
        case 0xC8B337E6U:
            return new StarPost();
            break;
        case 0x9D88FCCEU:
            return new ForegroundPlant();
            break;
        case 0xE0D9B634U:
            return new BreakableBar();
            break;
        case 0xD746F4D5U:
            return new VWaterStream();
            break;
        case 0x7849B3C1U:
            return new Fan();
            break;
        case 0x35EA70E0U:
            return new LargeFan();
            break;
        case 0xE6E16DBCU:
            return new HandLauncher();
            break;
        case 0x3B839BD2U:
            return new WaterWall();
            break;
        case 0x81EC1830U:
            return new Door();
            break;
        case 0x57260ED0U:
            return new ConveyorBelt();
            break;
        case 0x3CD6B406U:
            return new ConveyorSpike();
            break;
        case 0x58F95E1CU:
            return new Block();
            break;
        case 0x65BE2A3AU:
            return new Balloon();
            break;
        case 0xA17F0176U:
            return new CNZLightBulb();
            break;
        case 0x7C977754U:
            return new HoverFan();
            break;
        case 0x3F2CD13FU:
            return new CNZRotatingBarrel();
            break;
        case 0x177568D6U:
            return new VacuumTube();
            break;
        case 0x9DD277AFU:
            return new Bumper();
            break;
        case 0x3B4DCB47U:
            return new Bouncepad();
            break;
        case 0x8942D1CCU:
            return new QuickMud();
            break;
        case 0xC3C9288BU:
            return new FloatingPlatform();
            break;
        case 0xABC86E5CU:
            return new SmashingPillar();
            break;
        case 0x3B006393U:
            return new MGZSwingingPlatform();
            break;
        case 0x8E41B4A6U:
            return new Bubbler();
            break;
        case 0xFC346615U:
            return new Relief();
            break;
        case 0x8D951E1DU:
            return new TriggerPlatform();
            break;
        case 0x1E4996EFU:
            return new DashTrigger();
            break;
        case 0xC2A459B3U:
            return new TopPlatform();
            break;
        case 0xCFEF501BU:
            return new SnakeBlocks();
            break;
        case 0x7DC95D09U:
            return new SpinningColumn();
            break;
        case 0x1D05F53U:
            return new Slide();
            break;
        case 0xE40C8E50U:
            return new InvisibleSpikes();
            break;
        case 0xA0BE8640U:
            return new InvisibleDeath();
            break;
        case 0x5F02A27FU:
            return new TensionBridge();
            break;
        case 0x9095B5CCU:
            return new WaterSplash();
            break;
        case 0xBE0BDD3CU:
            return new WaterDrop();
            break;
        case 0x8616E0BDU:
            return new HiddenMonitor();
            break;
        case 0x973691D6U:
            return new EggCapsule();
            break;
        case 0x2822B56DU:
            return new CutsceneKnuckles();
            break;
        case 0xABC2C658U:
            return new SpecialRing();
            break;
        case 0x9B85E709U:
            return new Bloominator();
            break;
        case 0x4374E9C7U:
            return new RhinoBot();
            break;
        case 0xB7C95057U:
            return new MonkeyDude();
            break;
        case 0x3F487ED4U:
            return new CaterkillerJr();
            break;
        case 0x842C5D59U:
            return new FireBreathCutscene();
            break;
        case 0xCDF582CAU:
            return new FireBreath();
            break;
        case 0x7893A0E1U:
            return new FlameMobile();
            break;
        case 0x2160C123U:
            return new Jawz();
            break;
        case 0xCD00547AU:
            return new Blastoid();
            break;
        case 0x78C3EB13U:
            return new Buggernaut();
            break;
        case 0x8E6F27CFU:
            return new TurboSpiker();
            break;
        case 0xC50988CEU:
            return new MegaChomper();
            break;
        case 0xF365CCC4U:
            return new Pointdexter();
            break;
        case 0x92C9F0D4U:
            return new BigShaker();
            break;
        case 0x1EF84BB7U:
            return new ScrewMobile();
            break;
        case 0xA8CF1ABBU:
            return new BubblesBadnik();
            break;
        case 0xDF9FA830U:
            return new Spiker();
            break;
        case 0x2C7E197CU:
            return new Mantis();
            break;
        case 0x8AB74B2DU:
            return new TunnelBotCutscene();
            break;
        case 0x403E6CD3U:
            return new TunnelBot();
            break;
        case 0x88549378U:
            return new DrillerEggman();
            break;
        case 0xEFAD5D3CU:
            return new DrillMobile();
            break;
        case 0x9D8C15CAU:
            return new Batbright();
            break;
        case 0x804AD12DU:
            return new StarPointer();
            break;
        case 0xA5F30B34U:
            return new CrushingColumn();
            break;
        case 0xDE608819U:
            return new Freezer();
            break;
        case 0x5EE8DBE4U:
            return new SegmentedColumn();
            break;
        case 0xEA181B0BU:
            return new ICZSwingingPlatform();
            break;
        case 0xC73D2821U:
            return new Stalagtite();
            break;
        case 0xE855624CU:
            return new IceCube();
            break;
        case 0x8BC9A52CU:
            return new HarmfulIce();
            break;
        case 0xCF9FDC21U:
            return new SnowPile();
            break;
        case 0x75BEA9FBU:
            return new Orbinaut();
            break;
        case 0x8E8C37A1U:
            return new AirshipBomb();
            break;
        case 0x46F4A841U:
            return new AIZControl();
            break;
        case 0xBF8DF98AU:
            return new BloominatorSpore();
            break;
        case 0xA1BB73AAU:
            return new FireBreathBomb();
            break;
        case 0xCE81DA7EU:
            return new FireBreathFlame();
            break;
        case 0x7B6FD60BU:
            return new AIZIntro();
            break;
        case 0x3B52D08U:
            return new AIZIntroKnux();
            break;
        case 0x6FC38B24U:
            return new AIZIntroSplash();
            break;
        case 0xA257AE9AU:
            return new AIZTornado();
            break;
        case 0x5C688649U:
            return new MonkeyDudeCoconut();
            break;
        case 0xD5ADBFDBU:
            return new BatbrightParts();
            break;
        case 0x8D487F51U:
            return new BlankObject();
            break;
        case 0xE572007EU:
            return new BoundsMarker();
            break;
        case 0x11DAFFC3U:
            return new BubbleAir();
            break;
        case 0x200B8155U:
            return new HUD();
            break;
        case 0x76DDB5BU:
            return new InvisibleBlockV();
            break;
        case 0xE3B8D32U:
            return new Music();
            break;
        case 0xA55958B7U:
            return new PauseMenu();
            break;
        case 0x7573BB38U:
            return new PlaneSwitcher();
            break;
        case 0x5DFC3336U:
            return new PlatformOutliner();
            break;
        case 0xEACB9471U:
            return new PlayerSpawn();
            break;
        case 0xFAEE228AU:
            return new TitleCard();
            break;
        case 0x7E49DBD3U:
            return new WarpStars();
            break;
        case 0xA0128E04U:
            return new EggCapsuleButton();
            break;
        case 0x6A8C340CU:
            return new Signpost();
            break;
        case 0x8ED6F84CU:
            return new TensionBridgeChild();
            break;
        case 0x27340CB0U:
            return new ViewCollisionToggler();
            break;
        case 0x219C1E61U:
            return new Motobug();
            break;
        case 0x5B38E7A8U:
            return new MotobugSmoke();
            break;
        case 0x3692A9F5U:
            return new BlastoidShot();
            break;
        case 0xB708D750U:
            return new DepthCharge();
            break;
        case 0x77A23BDEU:
            return new TurboSpikerSpike();
            break;
        case 0x91BDF05U:
            return new SegmentedColumnStub();
            break;
        case 0x802D069AU:
            return new StarPointerOrbs();
            break;
        case 0x7A5BA50EU:
            return new SwingingPlatformTrigger();
            break;
        case 0xBBCA6AC5U:
            return new ReliefEye();
            break;
        case 0xC4B304CCU:
            return new Platform();
            break;

        default:
            break;
    }
    return NULL;
}

int GetObjectIDFromName(const char* ObjName) {
            if (!strcmp(ObjName, "Ring")) {
            return 0x0U;
        }

        if (!strcmp(ObjName, "ItemBox")) {
            return 0x1U;
        }

        if (!strcmp(ObjName, "HollowTree")) {
            return 0x3U;
        }

        if (!strcmp(ObjName, "CollapsingPlatform")) {
            return 0x4U;
        }

        if (!strcmp(ObjName, "Rock")) {
            return 0x5U;
        }

        if (!strcmp(ObjName, "RideVine")) {
            return 0x6U;
        }

        if (!strcmp(ObjName, "Spring")) {
            return 0x7U;
        }

        if (!strcmp(ObjName, "Spikes")) {
            return 0x8U;
        }

        if (!strcmp(ObjName, "TreeBark")) {
            return 0x9U;
        }

        if (!strcmp(ObjName, "RopePeg")) {
            return 0xAU;
        }

        if (!strcmp(ObjName, "SwingVine")) {
            return 0xCU;
        }

        if (!strcmp(ObjName, "BreakableWall")) {
            return 0xDU;
        }

        if (!strcmp(ObjName, "Ridge")) {
            return 0xEU;
        }

        if (!strcmp(ObjName, "CollapsingBridge")) {
            return 0xFU;
        }

        if (!strcmp(ObjName, "AutomaticTunnel")) {
            return 0x24U;
        }

        if (!strcmp(ObjName, "RollEnforcer")) {
            return 0x26U;
        }

        if (!strcmp(ObjName, "InvisibleBlockH")) {
            return 0x28U;
        }

        if (!strcmp(ObjName, "DisappearingFloor")) {
            return 0x29U;
        }

        if (!strcmp(ObjName, "CorkFloor")) {
            return 0x2AU;
        }

        if (!strcmp(ObjName, "FlippingBridge")) {
            return 0x2BU;
        }

        if (!strcmp(ObjName, "CollapsingLogBridge")) {
            return 0x2CU;
        }

        if (!strcmp(ObjName, "FallingLog")) {
            return 0x2DU;
        }

        if (!strcmp(ObjName, "SpikedLog")) {
            return 0x2EU;
        }

        if (!strcmp(ObjName, "NonAnimSprite")) {
            return 0x2FU;
        }

        if (!strcmp(ObjName, "AnimSprite")) {
            return 0x30U;
        }

        if (!strcmp(ObjName, "Drawbridge")) {
            return 0x32U;
        }

        if (!strcmp(ObjName, "Button")) {
            return 0x33U;
        }

        if (!strcmp(ObjName, "StarPost")) {
            return 0x34U;
        }

        if (!strcmp(ObjName, "ForegroundPlant")) {
            return 0x35U;
        }

        if (!strcmp(ObjName, "BreakableBar")) {
            return 0x36U;
        }

        if (!strcmp(ObjName, "VWaterStream")) {
            return 0x37U;
        }

        if (!strcmp(ObjName, "Fan")) {
            return 0x38U;
        }

        if (!strcmp(ObjName, "LargeFan")) {
            return 0x39U;
        }

        if (!strcmp(ObjName, "HandLauncher")) {
            return 0x3AU;
        }

        if (!strcmp(ObjName, "WaterWall")) {
            return 0x3BU;
        }

        if (!strcmp(ObjName, "Door")) {
            return 0x3CU;
        }

        if (!strcmp(ObjName, "ConveyorBelt")) {
            return 0x3EU;
        }

        if (!strcmp(ObjName, "ConveyorSpike")) {
            return 0x3FU;
        }

        if (!strcmp(ObjName, "Block")) {
            return 0x40U;
        }

        if (!strcmp(ObjName, "Balloon")) {
            return 0x41U;
        }

        if (!strcmp(ObjName, "CNZLightBulb")) {
            return 0x45U;
        }

        if (!strcmp(ObjName, "HoverFan")) {
            return 0x46U;
        }

        if (!strcmp(ObjName, "CNZRotatingBarrel")) {
            return 0x47U;
        }

        if (!strcmp(ObjName, "VacuumTube")) {
            return 0x48U;
        }

        if (!strcmp(ObjName, "Bumper")) {
            return 0x4AU;
        }

        if (!strcmp(ObjName, "Bouncepad")) {
            return 0x4BU;
        }

        if (!strcmp(ObjName, "QuickMud")) {
            return 0x4FU;
        }

        if (!strcmp(ObjName, "FloatingPlatform")) {
            return 0x51U;
        }

        if (!strcmp(ObjName, "SmashingPillar")) {
            return 0x52U;
        }

        if (!strcmp(ObjName, "MGZSwingingPlatform")) {
            return 0x53U;
        }

        if (!strcmp(ObjName, "Bubbler")) {
            return 0x54U;
        }

        if (!strcmp(ObjName, "Relief")) {
            return 0x55U;
        }

        if (!strcmp(ObjName, "TriggerPlatform")) {
            return 0x57U;
        }

        if (!strcmp(ObjName, "DashTrigger")) {
            return 0x59U;
        }

        if (!strcmp(ObjName, "TopPlatform")) {
            return 0x5BU;
        }

        if (!strcmp(ObjName, "SnakeBlocks")) {
            return 0x67U;
        }

        if (!strcmp(ObjName, "SpinningColumn")) {
            return 0x68U;
        }

        if (!strcmp(ObjName, "Slide")) {
            return 0x69U;
        }

        if (!strcmp(ObjName, "InvisibleSpikes")) {
            return 0x6AU;
        }

        if (!strcmp(ObjName, "InvisibleDeath")) {
            return 0x6BU;
        }

        if (!strcmp(ObjName, "TensionBridge")) {
            return 0x6CU;
        }

        if (!strcmp(ObjName, "WaterSplash")) {
            return 0x6DU;
        }

        if (!strcmp(ObjName, "WaterDrop")) {
            return 0x6EU;
        }

        if (!strcmp(ObjName, "HiddenMonitor")) {
            return 0x80U;
        }

        if (!strcmp(ObjName, "EggCapsule")) {
            return 0x81U;
        }

        if (!strcmp(ObjName, "CutsceneKnuckles")) {
            return 0x82U;
        }

        if (!strcmp(ObjName, "SpecialRing")) {
            return 0x85U;
        }

        if (!strcmp(ObjName, "Bloominator")) {
            return 0x8CU;
        }

        if (!strcmp(ObjName, "RhinoBot")) {
            return 0x8DU;
        }

        if (!strcmp(ObjName, "MonkeyDude")) {
            return 0x8EU;
        }

        if (!strcmp(ObjName, "CaterkillerJr")) {
            return 0x8FU;
        }

        if (!strcmp(ObjName, "FireBreathCutscene")) {
            return 0x90U;
        }

        if (!strcmp(ObjName, "FireBreath")) {
            return 0x91U;
        }

        if (!strcmp(ObjName, "FlameMobile")) {
            return 0x92U;
        }

        if (!strcmp(ObjName, "Jawz")) {
            return 0x93U;
        }

        if (!strcmp(ObjName, "Blastoid")) {
            return 0x94U;
        }

        if (!strcmp(ObjName, "Buggernaut")) {
            return 0x95U;
        }

        if (!strcmp(ObjName, "TurboSpiker")) {
            return 0x96U;
        }

        if (!strcmp(ObjName, "MegaChomper")) {
            return 0x97U;
        }

        if (!strcmp(ObjName, "Pointdexter")) {
            return 0x98U;
        }

        if (!strcmp(ObjName, "BigShaker")) {
            return 0x99U;
        }

        if (!strcmp(ObjName, "ScrewMobile")) {
            return 0x9AU;
        }

        if (!strcmp(ObjName, "BubblesBadnik")) {
            return 0x9BU;
        }

        if (!strcmp(ObjName, "Spiker")) {
            return 0x9CU;
        }

        if (!strcmp(ObjName, "Mantis")) {
            return 0x9DU;
        }

        if (!strcmp(ObjName, "TunnelBotCutscene")) {
            return 0x9EU;
        }

        if (!strcmp(ObjName, "TunnelBot")) {
            return 0x9FU;
        }

        if (!strcmp(ObjName, "DrillerEggman")) {
            return 0xA0U;
        }

        if (!strcmp(ObjName, "DrillMobile")) {
            return 0xA1U;
        }

        if (!strcmp(ObjName, "Batbright")) {
            return 0xA5U;
        }

        if (!strcmp(ObjName, "StarPointer")) {
            return 0xAEU;
        }

        if (!strcmp(ObjName, "CrushingColumn")) {
            return 0xAFU;
        }

        if (!strcmp(ObjName, "Freezer")) {
            return 0xB2U;
        }

        if (!strcmp(ObjName, "SegmentedColumn")) {
            return 0xB3U;
        }

        if (!strcmp(ObjName, "ICZSwingingPlatform")) {
            return 0xB4U;
        }

        if (!strcmp(ObjName, "Stalagtite")) {
            return 0xB5U;
        }

        if (!strcmp(ObjName, "IceCube")) {
            return 0xB6U;
        }

        if (!strcmp(ObjName, "HarmfulIce")) {
            return 0xB8U;
        }

        if (!strcmp(ObjName, "SnowPile")) {
            return 0xB9U;
        }

        if (!strcmp(ObjName, "Orbinaut")) {
            return 0xC0U;
        }

        if (!strcmp(ObjName, "AirshipBomb")) {
            return 0x400U;
        }

        if (!strcmp(ObjName, "AIZControl")) {
            return 0x401U;
        }

        if (!strcmp(ObjName, "BloominatorSpore")) {
            return 0x402U;
        }

        if (!strcmp(ObjName, "FireBreathBomb")) {
            return 0x403U;
        }

        if (!strcmp(ObjName, "FireBreathFlame")) {
            return 0x404U;
        }

        if (!strcmp(ObjName, "AIZIntro")) {
            return 0x405U;
        }

        if (!strcmp(ObjName, "AIZIntroKnux")) {
            return 0x406U;
        }

        if (!strcmp(ObjName, "AIZIntroSplash")) {
            return 0x407U;
        }

        if (!strcmp(ObjName, "AIZTornado")) {
            return 0x408U;
        }

        if (!strcmp(ObjName, "MonkeyDudeCoconut")) {
            return 0x409U;
        }

        if (!strcmp(ObjName, "BatbrightParts")) {
            return 0x40AU;
        }

        if (!strcmp(ObjName, "BlankObject")) {
            return 0x40BU;
        }

        if (!strcmp(ObjName, "BoundsMarker")) {
            return 0x40CU;
        }

        if (!strcmp(ObjName, "BubbleAir")) {
            return 0x40DU;
        }

        if (!strcmp(ObjName, "HUD")) {
            return 0x40EU;
        }

        if (!strcmp(ObjName, "InvisibleBlockV")) {
            return 0x40FU;
        }

        if (!strcmp(ObjName, "Music")) {
            return 0x410U;
        }

        if (!strcmp(ObjName, "PauseMenu")) {
            return 0x411U;
        }

        if (!strcmp(ObjName, "PlaneSwitcher")) {
            return 0x412U;
        }

        if (!strcmp(ObjName, "PlatformOutliner")) {
            return 0x413U;
        }

        if (!strcmp(ObjName, "PlayerSpawn")) {
            return 0x414U;
        }

        if (!strcmp(ObjName, "TitleCard")) {
            return 0x415U;
        }

        if (!strcmp(ObjName, "WarpStars")) {
            return 0x416U;
        }

        if (!strcmp(ObjName, "EggCapsuleButton")) {
            return 0x417U;
        }

        if (!strcmp(ObjName, "Signpost")) {
            return 0x418U;
        }

        if (!strcmp(ObjName, "TensionBridgeChild")) {
            return 0x419U;
        }

        if (!strcmp(ObjName, "ViewCollisionToggler")) {
            return 0x41AU;
        }

        if (!strcmp(ObjName, "Motobug")) {
            return 0x41BU;
        }

        if (!strcmp(ObjName, "MotobugSmoke")) {
            return 0x41CU;
        }

        if (!strcmp(ObjName, "BlastoidShot")) {
            return 0x41DU;
        }

        if (!strcmp(ObjName, "DepthCharge")) {
            return 0x41EU;
        }

        if (!strcmp(ObjName, "TurboSpikerSpike")) {
            return 0x41FU;
        }

        if (!strcmp(ObjName, "SegmentedColumnStub")) {
            return 0x420U;
        }

        if (!strcmp(ObjName, "StarPointerOrbs")) {
            return 0x421U;
        }

        if (!strcmp(ObjName, "SwingingPlatformTrigger")) {
            return 0x422U;
        }

        if (!strcmp(ObjName, "ReliefEye")) {
            return 0x423U;
        }

        if (!strcmp(ObjName, "Platform")) {
            return 0x424U;
        }


		IApp::Print(1,"Object wasn't found!");
	return 0x40BU; //Return the BlankObject ID, since the requested one wasn't found
        
}