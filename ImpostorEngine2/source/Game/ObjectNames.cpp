/* MD5
converted to C++ class by Frank Thilo (thilo@unix-ag.org)
for bzflag (http://www.bzflag.org)

based on:

md5.h and md5.c
reference implemantion of RFC 1321

Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.

*/

/* interface header */
#include <Game/ObjectNames.h>

/* system implementation headers */
#include <cstdio>


// Constants for MD5Transform routine.
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

///////////////////////////////////////////////

// F, G, H and I are basic MD5 functions.
inline MD5::uint4 MD5::F(uint4 x, uint4 y, uint4 z) {
	return (x & y) | (~x & z);
}

inline MD5::uint4 MD5::G(uint4 x, uint4 y, uint4 z) {
	return (x & z) | (y & ~z);
}

inline MD5::uint4 MD5::H(uint4 x, uint4 y, uint4 z) {
	return x ^ y^z;
}

inline MD5::uint4 MD5::I(uint4 x, uint4 y, uint4 z) {
	return y ^ (x | ~z);
}

// rotate_left rotates x left n bits.
inline MD5::uint4 MD5::rotate_left(uint4 x, int n) {
	return (x << n) | (x >> (32 - n));
}

// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.
inline void MD5::FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + F(b, c, d) + x + ac, s) + b;
}

inline void MD5::GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + G(b, c, d) + x + ac, s) + b;
}

inline void MD5::HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + H(b, c, d) + x + ac, s) + b;
}

inline void MD5::II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + I(b, c, d) + x + ac, s) + b;
}

//////////////////////////////////////////////

// default ctor, just initailize
MD5::MD5() {
	init();
}

//////////////////////////////////////////////

// nifty shortcut ctor, compute MD5 for string and finalize it right away
MD5::MD5(const std::string &text) {
	init();
	update(text.c_str(), (unsigned int)text.length());
	finalize();
}

//////////////////////////////

void MD5::init() {
	finalized = false;

	count[0] = 0;
	count[1] = 0;

	// load magic initialization constants.
	state[0] = 0x67452301;
	state[1] = 0xefcdab89;
	state[2] = 0x98badcfe;
	state[3] = 0x10325476;
}

//////////////////////////////

// decodes input (unsigned char) into output (uint4). Assumes len is a multiple of 4.
void MD5::decode(uint4 output[], const uint1 input[], size_type len) {
	for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((uint4)input[j]) | (((uint4)input[j + 1]) << 8) |
		(((uint4)input[j + 2]) << 16) | (((uint4)input[j + 3]) << 24);
}

//////////////////////////////

// encodes input (uint4) into output (unsigned char). Assumes len is
// a multiple of 4.
void MD5::encode(uint1 output[], const uint4 input[], size_type len) {
	for (size_type i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = input[i] & 0xff;
		output[j + 1] = (input[i] >> 8) & 0xff;
		output[j + 2] = (input[i] >> 16) & 0xff;
		output[j + 3] = (input[i] >> 24) & 0xff;
	}
}

//////////////////////////////

// apply MD5 algo on a block
void MD5::transform(const uint1 block[blocksize]) {
	uint4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
	decode(x, block, blocksize);

	/* Round 1 */
	FF(a, b, c, d, x[0], S11, 0xd76aa478); /* 1 */
	FF(d, a, b, c, x[1], S12, 0xe8c7b756); /* 2 */
	FF(c, d, a, b, x[2], S13, 0x242070db); /* 3 */
	FF(b, c, d, a, x[3], S14, 0xc1bdceee); /* 4 */
	FF(a, b, c, d, x[4], S11, 0xf57c0faf); /* 5 */
	FF(d, a, b, c, x[5], S12, 0x4787c62a); /* 6 */
	FF(c, d, a, b, x[6], S13, 0xa8304613); /* 7 */
	FF(b, c, d, a, x[7], S14, 0xfd469501); /* 8 */
	FF(a, b, c, d, x[8], S11, 0x698098d8); /* 9 */
	FF(d, a, b, c, x[9], S12, 0x8b44f7af); /* 10 */
	FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
	FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
	FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
	FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
	FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
	FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

											/* Round 2 */
	GG(a, b, c, d, x[1], S21, 0xf61e2562); /* 17 */
	GG(d, a, b, c, x[6], S22, 0xc040b340); /* 18 */
	GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
	GG(b, c, d, a, x[0], S24, 0xe9b6c7aa); /* 20 */
	GG(a, b, c, d, x[5], S21, 0xd62f105d); /* 21 */
	GG(d, a, b, c, x[10], S22, 0x2441453); /* 22 */
	GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
	GG(b, c, d, a, x[4], S24, 0xe7d3fbc8); /* 24 */
	GG(a, b, c, d, x[9], S21, 0x21e1cde6); /* 25 */
	GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
	GG(c, d, a, b, x[3], S23, 0xf4d50d87); /* 27 */
	GG(b, c, d, a, x[8], S24, 0x455a14ed); /* 28 */
	GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
	GG(d, a, b, c, x[2], S22, 0xfcefa3f8); /* 30 */
	GG(c, d, a, b, x[7], S23, 0x676f02d9); /* 31 */
	GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

											/* Round 3 */
	HH(a, b, c, d, x[5], S31, 0xfffa3942); /* 33 */
	HH(d, a, b, c, x[8], S32, 0x8771f681); /* 34 */
	HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
	HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
	HH(a, b, c, d, x[1], S31, 0xa4beea44); /* 37 */
	HH(d, a, b, c, x[4], S32, 0x4bdecfa9); /* 38 */
	HH(c, d, a, b, x[7], S33, 0xf6bb4b60); /* 39 */
	HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
	HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
	HH(d, a, b, c, x[0], S32, 0xeaa127fa); /* 42 */
	HH(c, d, a, b, x[3], S33, 0xd4ef3085); /* 43 */
	HH(b, c, d, a, x[6], S34, 0x4881d05); /* 44 */
	HH(a, b, c, d, x[9], S31, 0xd9d4d039); /* 45 */
	HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
	HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
	HH(b, c, d, a, x[2], S34, 0xc4ac5665); /* 48 */

										   /* Round 4 */
	II(a, b, c, d, x[0], S41, 0xf4292244); /* 49 */
	II(d, a, b, c, x[7], S42, 0x432aff97); /* 50 */
	II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
	II(b, c, d, a, x[5], S44, 0xfc93a039); /* 52 */
	II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
	II(d, a, b, c, x[3], S42, 0x8f0ccc92); /* 54 */
	II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
	II(b, c, d, a, x[1], S44, 0x85845dd1); /* 56 */
	II(a, b, c, d, x[8], S41, 0x6fa87e4f); /* 57 */
	II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
	II(c, d, a, b, x[6], S43, 0xa3014314); /* 59 */
	II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
	II(a, b, c, d, x[4], S41, 0xf7537e82); /* 61 */
	II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
	II(c, d, a, b, x[2], S43, 0x2ad7d2bb); /* 63 */
	II(b, c, d, a, x[9], S44, 0xeb86d391); /* 64 */

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	// Zeroize sensitive information.
	memset(x, 0, sizeof x);
}

//////////////////////////////

// MD5 block update operation. Continues an MD5 message-digest
// operation, processing another message block
void MD5::update(const unsigned char input[], size_type length) {
	// compute number of bytes mod 64
	size_type index = count[0] / 8 % blocksize;

	// Update number of bits
	if ((count[0] += (length << 3)) < (length << 3))
		count[1]++;
	count[1] += (length >> 29);

	// number of bytes we need to fill in buffer
	size_type firstpart = 64 - index;

	size_type i;

	// transform as many times as possible.
	if (length >= firstpart) {
		// fill buffer first, transform
		memcpy(&buffer[index], input, firstpart);
		transform(buffer);

		// transform chunks of blocksize (64 bytes)
		for (i = firstpart; i + blocksize <= length; i += blocksize)
			transform(&input[i]);

		index = 0;
	}
	else
		i = 0;

	// buffer remaining input
	memcpy(&buffer[index], &input[i], length - i);
}

//////////////////////////////

// for convenience provide a verson with signed char
void MD5::update(const char input[], size_type length) {
	update((const unsigned char*)input, length);
}

//////////////////////////////

// MD5 finalization. Ends an MD5 message-digest operation, writing the
// the message digest and zeroizing the context.
MD5& MD5::finalize() {
	static unsigned char padding[64] = {
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	if (!finalized) {
		// Save number of bits
		unsigned char bits[8];
		encode(bits, count, 8);

		// pad out to 56 mod 64.
		size_type index = count[0] / 8 % 64;
		size_type padLen = (index < 56) ? (56 - index) : (120 - index);
		update(padding, padLen);

		// Append length (before padding)
		update(bits, 8);

		// Store state in digest
		encode(digest, state, 16);

		// Zeroize sensitive information.
		memset(buffer, 0, sizeof buffer);
		memset(count, 0, sizeof count);

		finalized = true;
	}

	return *this;
}

//////////////////////////////

// return hex representation of digest as string
std::string MD5::getdigest() const {
	if (!finalized)
		return "";

	char buf[17];
	for (int i = 0; i < 16; i++)
		buf[i] = digest[i];
	buf[16] = 0;

	return std::string(buf);
}

// return hex representation of digest as string
std::string MD5::hexdigest() const {
	if (!finalized)
		return "";

	char buf[33];
	for (int i = 0; i < 16; i++)
		sprintf(buf + i * 2, "%02x", digest[i]);
	buf[32] = 0;

	return std::string(buf);
}

//////////////////////////////

std::ostream& operator<<(std::ostream& out, MD5 md5) {
	return out << md5.hexdigest();
}

//////////////////////////////

std::string MD5I(const std::string str) {
	MD5 md5 = MD5(str);

	return md5.hexdigest();
}

const char* ObjectNameList[554] = {
	"Acetone",
	"ActClear",
	"AIZEggRobo",
	"AIZKingClaw",
	"AIZSetup",
	"AIZTornado",
	"AIZTornadoPath",
	"AmoebaDroid",
	"AnimalHBH",
	"Animals",
	"Announcer",
	"APICallback",
	"Aquis",
	"Armadiloid",
	"BadnikHelpers",
	"Ball",
	"BallCannon",
	"BallHog",
	"BarStool",
	"Batbot",
	"Batbrain",
	"Beanstalk",
	"BGSwitch",
	"BigSqueeze",
	"BladePole",
	"Blank Object",
	"Blaster",
	"Blastoid",
	"Bomb",
	"BouncePlant",
	"BoundsMarker",
	"BreakableWall",
	"BreakBar",
	"Bridge",
	"BSS_Collectable",
	"BSS_Collected",
	"BSS_Horizon",
	"BSS_HUD",
	"BSS_Message",
	"BSS_Palette",
	"BSS_Player",
	"BSS_Setup",
	"Bubbler",
	"BuckwildBall",
	"Buggernaut",
	"Bumpalo",
	"Bungee",
	"BurningLog",
	"Button",
	"ButtonDoor",
	"BuzzBomber",
	"BuzzSaw",
	"CableWarp",
	"Cactula",
	"Camera",
	"Canista",
	"Caterkiller",
	"CaterkillerJr",
	"ChaosEmerald",
	"CheckerBall",
	"ChemBubble",
	"ChemicalBall",
	"ChemicalPool",
	"Chopper",
	"CircleBumper",
	"Clapperboard",
	"Clucker",
	"CollapsingPlatform",
	"CollapsingSand",
	"ColorHelpers",
	"Competition",
	"CompetitionSession",
	"Constellation",
	"ContinuePlayer",
	"ContinueSetup",
	"ConveyorBelt",
	"ConveyorPlatform",
	"ConveyorWheel",
	"CorkscrewPath",
	"COverlay",
	"CPZ1Intro",
	"CPZ2Outro",
	"CPZBoss",
	"CPZSetup",
	"CPZShutter",
	"Crabmeat",
	"Crane",
	"CrashTest",
	"Crate",
	"CreditsSetup",
	"CrimsonEye",
	"Current",
	"CutsceneHBH",
	"CutsceneRules",
	"CutsceneSeq",
	"Cylinder",
	"DAControl",
	"Dango",
	"DASetup",
	"DashLift",
	"DBTower",
	"DCEvent",
	"DDWrecker",
	"Debris",
	"DebugMode",
	"Decoration",
	"DemoMenu",
	"DERobot",
	"DirectorChair",
	"DiveEggman",
	"DNARiser",
	"DoorTrigger",
	"Dragonfly",
	"DrawHelpers",
	"Drillerdroid",
	"DrillerdroidO",
	"Dust",
	"E3MenuSetup",
	"EggJanken",
	"EggJankenPart",
	"EggLoco",
	"Eggman",
	"EggPistonsMKII",
	"EggPrison",
	"EggTower",
	"EggTV",
	"ElectroMagnet",
	"ERZGunner",
	"ERZKing",
	"ERZMystic",
	"ERZOutro",
	"ERZRider",
	"ERZSetup",
	"ERZShinobi",
	"ERZStart",
	"EscapeCar",
	"Explosion",
	"Fan",
	"FarPlane",
	"FBZ1Outro",
	"FBZFan",
	"FBZMissile",
	"FBZSetup",
	"FBZSinkTrash",
	"FBZStorm",
	"FBZTrash",
	"FilmProjector",
	"FilmReel",
	"Fireball",
	"Fireflies",
	"Firework",
	"Fireworm",
	"FlameSpring",
	"Flamethrower",
	"FlasherMKII",
	"FlingRamp",
	"Flipper",
	"FlowerPod",
	"FoldingPlatform",
	"ForceSpin",
	"ForceUnstick",
	"FrostThrower",
	"Funnel",
	"FXExpandRing",
	"FXFade",
	"FXRuby",
	"FXSpinRay",
	"FXTrail",
	"Gachapandora",
	"GameOver",
	"GameProgress",
	"GasPlatform",
	"GenericTrigger",
	"GHZ2Outro",
	"GHZCutsceneK",
	"GHZCutsceneST",
	"GHZSetup",
	"GiantPistol",
	"Gondola",
	"Grabber",
	"GreenScreen",
	"GymBar",
	"HandLauncher",
	"HangConveyor",
	"HangPoint",
	"Hatch",
	"Hatterkiller",
	"HCZ1Intro",
	"HCZOneWayDoor",
	"HCZSetup",
	"HCZSpikeBall",
	"HeavyGunner",
	"HeavyKing",
	"HeavyMystic",
	"HeavyRider",
	"HeavyShinobi",
	"HiLoSign",
	"Honkytonk",
	"Hotaru",
	"HotaruHiWatt",
	"HotaruMKII",
	"HPZEmerald",
	"HUD",
	"Ice",
	"IceBomba",
	"IceSpring",
	"ImageTrail",
	"Ink",
	"InkWipe",
	"InvincibleStars",
	"InvisibleBlock",
	"ItemBox",
	"Iwamodoki",
	"JacobsLadder",
	"Jawz",
	"Jellygnite",
	"JuggleSaw",
	"JunctionWheel",
	"Kabasira",
	"Kanabun",
	"KingAttack",
	"KingClaw",
	"KleptoMobile",
	"LargeGear",
	"Launcher",
	"LaunchSpring",
	"LaundroMobile",
	"LavaFall",
	"LavaGeyser",
	"LEDPanel",
	"Letterboard",
	"LevelSelect",
	"LightBarrier",
	"LightBulb",
	"Localization",
	"LocoSmoke",
	"LogHelpers",
	"LogoSetup",
	"LottoBall",
	"LottoMachine",
	"LoveTester",
	"LRZ1Outro",
	"LRZ1Setup",
	"LRZ2Setup",
	"LRZ3Cutscene",
	"LRZ3OutroK",
	"LRZ3Setup",
	"LRZConvControl",
	"LRZConvDropper",
	"LRZConveyor",
	"LRZConvItem",
	"LRZConvSwitch",
	"LRZFireball",
	"LRZRockPile",
	"LRZSpikeBall",
	"LRZSpiral",
	"MagnetSphere",
	"MagPlatform",
	"MagSpikeBall",
	"MathHelpers",
	"MatryoshkaBom",
	"MechaBu",
	"MegaChopper",
	"MegaOctus",
	"MenuParam",
	"MenuSetup",
	"MetalArm",
	"MetalSonic",
	"MeterDroid",
	"MicDrop",
	"Mine",
	"MMZSetup",
	"MMZWheel",
	"MonarchBG",
	"MonkeyDude",
	"Motobug",
	"MSFactory",
	"MSHologram",
	"MSOrb",
	"MSPanel",
	"MSZ1KIntro",
	"MSZ2Cutscene",
	"MSZCutsceneK",
	"MSZCutsceneST",
	"MSZSetup",
	"MSZSpotlight",
	"Music",
	"Newspaper",
	"Newtron",
	"Octus",
	"OneWayDoor",
	"OOZ1Outro",
	"OOZFlames",
	"OOZSetup",
	"Options",
	"Orbinaut",
	"OrbitSpike",
	"PaintingEyes",
	"PaperRoller",
	"ParallaxSprite",
	"ParticleHelpers",
	"PathInverter",
	"PauseMenu",
	"Pendulum",
	"PetalPile",
	"PhantomEgg",
	"PhantomGunner",
	"PhantomHand",
	"PhantomKing",
	"PhantomMissile",
	"PhantomMystic",
	"PhantomRider",
	"PhantomRuby",
	"PhantomShield",
	"PhantomShinobi",
	"PimPom",
	"Pinata",
	"Piston",
	"PKingAttack",
	"PlaneSeeSaw",
	"PlaneSwitch",
	"Platform",
	"PlatformControl",
	"PlatformNode",
	"Player",
	"PlayerHelpers",
	"PlayerProbe",
	"PohBee",
	"Pointdexter",
	"PopcornKernel",
	"PopcornMachine",
	"PopOut",
	"Press",
	"PrintBlock",
	"Projectile",
	"Propeller",
	"PropellerShaft",
	"PSZ1Setup",
	"PSZ2Intro",
	"PSZ2Outro",
	"PSZ2Setup",
	"PSZDoor",
	"PSZEggman",
	"PSZLauncher",
	"PullChain",
	"PullSwitch",
	"PushSpring",
	"PuyoAI",
	"PuyoAttack",
	"PuyoBean",
	"PuyoGame",
	"PuyoIndicator",
	"PuyoLabel",
	"PuyoLevelSelect",
	"PuyoMatch",
	"PuyoScore",
	"Rattlekiller",
	"Reagent",
	"Redz",
	"Rexon",
	"Ring",
	"RingField",
	"RisingLava",
	"RockDrill",
	"RockemSockem",
	"RollerMKII",
	"RotatingSpikes",
	"RotatingStair",
	"RPlaneShifter",
	"RTeleporter",
	"RubyPortal",
	"SaveGame",
	"Scarab",
	"ScoreBonus",
	"ScrewMobile",
	"SDashWheel",
	"SeeSaw",
	"SeltzerBottle",
	"SeltzerWater",
	"SentryBug",
	"Shield",
	"Shiversaw",
	"ShopWindow",
	"Shuriken",
	"Shutterbug",
	"SideBarrel",
	"SignPost",
	"SilverSonic",
	"SizeLaser",
	"SkyTeleporter",
	"Smog",
	"Snowflakes",
	"Sol",
	"Soundboard",
	"SP500",
	"SP500MkII",
	"SparkRail",
	"Spear",
	"SpearBlock",
	"SpecialClear",
	"SpecialRing",
	"SpeedBooster",
	"SpeedGate",
	"SpiderMobile",
	"SpikeCorridor",
	"SpikeCrusher",
	"SpikeFlail",
	"SpikeLog",
	"Spikes",
	"SpinBooster",
	"Spiny",
	"SpiralPlatform",
	"Splats",
	"Spring",
	"Springboard",
	"SPZ1Intro",
	"SPZ1Setup",
	"SPZ2Outro",
	"SPZ2Setup",
	"SSZ1Intro",
	"SSZ1Outro",
	"SSZ1Setup",
	"SSZ2Setup",
	"SSZ3Cutscene",
	"SSZSpikeBall",
	"SSZSpotlight",
	"Staircase",
	"Stalactite",
	"StarPost",
	"Stegway",
	"StickyPlatform",
	"SuperSparkle",
	"Sweep",
	"SwingRope",
	"SwitchDoor",
	"Syringe",
	"TAEmerald",
	"TargetBumper",
	"Technosqueek",
	"TeeterTotter",
	"TetherBall",
	"ThanksSetup",
	"ThoughtBubble",
	"TilePlatform",
	"TimeAttackData",
	"TimeAttackGate",
	"TimePost",
	"TimeTravelSetup",
	"TippingPlatform",
	"Title3DSprite",
	"TitleBG",
	"TitleCard",
	"TitleLogo",
	"TitleSetup",
	"TitleSonic",
	"TMZ1Outro",
	"TMZ1Setup",
	"TMZ2Outro",
	"TMZ2Setup",
	"TMZ3Setup",
	"TMZAlert",
	"TMZBarrier",
	"TMZCable",
	"TMZFlames",
	"Tornado",
	"TornadoPath",
	"Toxomister",
	"TransportTube",
	"TryAgain",
	"TTCutscene",
	"TubeSpring",
	"Tubinaut",
	"Tuesday",
	"Turbine",
	"TurboSpiker",
	"TurboTurtle",
	"Turntable",
	"TurretSwitch",
	"TVFlyingBattery",
	"TVPole",
	"TVVan",
	"TwistedTubes",
	"TwistingDoor",
	"TwistingSlide",
	"UberCaterkiller",
	"UFO_Camera",
	"UFO_Circuit",
	"UFO_Decoration",
	"UFO_Dust",
	"UFO_HUD",
	"UFO_ItemBox",
	"UFO_Message",
	"UFO_Plasma",
	"UFO_Player",
	"UFO_Ring",
	"UFO_Setup",
	"UFO_Shadow",
	"UFO_SpeedLines",
	"UFO_Sphere",
	"UFO_Springboard",
	"UFO_Water",
	"UIBackground",
	"UIButton",
	"UIButtonLabel",
	"UIButtonPrompt",
	"UICharButton",
	"UIChoice",
	"UIControl",
	"UICreditsText",
	"UIDialog",
	"UIHeading",
	"UIInfoLabel",
	"UIKeyBinder",
	"UILeaderboard",
	"UIMedallionPanel",
	"UIModeButton",
	"UIOptionPanel",
	"UIPicture",
	"UIResPicker",
	"UISaveSlot",
	"UISlider",
	"UISubHeading",
	"UITAZoneModule",
	"UIText",
	"UITransition",
	"UIUsernamePopup",
	"UIVideo",
	"UIVsCharSelector",
	"UIVsResults",
	"UIVsRoundPicker",
	"UIVsScoreboard",
	"UIVsZoneButton",
	"UIWaitSpinner",
	"UIWidgets",
	"UIWinSize",
	"UncurlPlant",
	"Valve",
	"VanishPlatform",
	"Vultron",
	"WalkerLegs",
	"WallBumper",
	"WallCrawl",
	"WarpDoor",
	"Water",
	"WaterGush",
	"WeatherMobile",
	"WeatherTV",
	"Whirlpool",
	"Wisp",
	"WoodChipper",
	"Woodrow",
	"YoyoPulley",
	"ZipLine",
	"Zone",
};

const char* ObjectNames(int n) {
	return ObjectNameList[n];
}

std::vector<std::string> ObjectNamesList;

void SetObjectName(std::string name) {
	ObjectNamesList.push_back(name);
}

const char* GetObjectName(int n) {
	return ObjectNamesList[n].c_str();
}

void clearObjectNames()
{
	ObjectNamesList.clear();
}

int GetObjectNamesSize()
{
	return ObjectNamesList.size();
}

static uint32_t crc32_t[256] = {
	0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
	0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
	0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
	0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
	0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,
	0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
	0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
	0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
	0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,
	0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,
	0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,
	0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
	0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,
	0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
	0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,
	0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
	0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,
	0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
	0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,
	0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
	0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
	0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,
	0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,
	0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
	0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,
	0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,
	0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,
	0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
	0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,
	0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,
	0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,
	0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
	0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,
	0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,
	0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
	0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
	0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,
	0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,
	0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,
	0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
	0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,
	0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
	0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,
	0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
	0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,
	0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,
	0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,
	0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
	0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
	0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,
	0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,
	0x2d02ef8dL
};

uint32_t crc32(char* c, uint32_t len) {
	uint32_t crc32val = 0;
	uint8_t* s = (uint8_t*)c;
	for (uint32_t i = 0; i < len; i++) {
		if (c[i] == '\r') continue;
		if (!c[i]) break;
		crc32val = crc32_t[(crc32val ^ s[i]) & 0xFF] ^ (crc32val >> 8);
	}
	return crc32val;
}