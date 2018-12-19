#include "Player.h"
#include <time.h>
#include <Engine/IResources.h>
#include <Engine/IGraphics.h>

/* SONIC ANIMATIONS
"Idle" (index: 0)
 - Animation Speed: 0
 - [0]
"Bored 1" (index: 1)
 - Animation Speed: 2
 - [1, 11]
"Bored 2" (index: 12)
 - Animation Speed: 2
 - [12, 79]
"Look Up" (index: 80)
 - Animation Speed: 128
 - [80, 87]
"Crouch" (index: 88)
 - Animation Speed: 128
 - [88, 93]
"Walk" (index: 94)
 - Animation Speed: 64
 - [94, 105]
"Air Walk" (index: 106)
 - Animation Speed: 64
 - [106, 117]
"Jog" (index: 118)
 - Animation Speed: 96
 - [118, 127]
"Run" (index: 128)
 - Animation Speed: 128
 - [128, 136]
"Dash" (index: 137)
 - Animation Speed: 256
 - [137, 141]
"Jump" (index: 142)
 - Animation Speed: 60
 - [142, 157]
"Spring Twirl" (index: 158)
 - Animation Speed: 128
 - [158, 167]
"Spring Diagonal" (index: 168)
 - Animation Speed: 128
 - [168, 169]
"Skid" (index: 170)
 - Animation Speed: 128
 - [170, 182]
"Skid Turn" (index: 183)
 - Animation Speed: 128
 - [183, 186]
"Spindash" (index: 187)
 - Animation Speed: 1
 - [187, 202]
"Dropdash" (index: 203)
 - Animation Speed: 256
 - [203, 218]
"Push" (index: 219)
 - Animation Speed: 1
 - [219, 228]
"Hurt" (index: 229)
 - Animation Speed: 1
 - [229, 233]
"Die" (index: 234)
 - Animation Speed: 0
 - [234]
"Drown" (index: 235)
 - Animation Speed: 0
 - [235]
"Balance 1" (index: 236)
 - Animation Speed: 1
 - [236, 243]
"Balance 2" (index: 244)
 - Animation Speed: 1
 - [244, 251]
"Spring CS" (index: 252)
 - Animation Speed: 128
 - [252, 275]
"Stand CS" (index: 276)
 - Animation Speed: 128
 - [276, 299]
"Fan" (index: 300)
 - Animation Speed: 80
 - [300, 309]
"Victory" (index: 310)
 - Animation Speed: 1
 - [310, 327]
"Outta Here" (index: 328)
 - Animation Speed: 1
 - [328, 342]
"Hang" (index: 343)
 - Animation Speed: 1
 - [343, 350]
"Hang Move" (index: 351)
 - Animation Speed: 1
 - [351, 362]
"Pole Swing V" (index: 363)
 - Animation Speed: 256
 - [363, 374]
"Pole Swing H" (index: 375)
 - Animation Speed: 256
 - [375, 386]
"Shaft Swing" (index: 387)
 - Animation Speed: 256
 - [387, 398]
"Turntable" (index: 399)
 - Animation Speed: 1
 - [399, 410]
"Twister" (index: 411)
 - Animation Speed: 0
 - [411, 434]
"Spiral Run" (index: 435)
 - Animation Speed: 1
 - [435, 458]
"Stick" (index: 459)
 - Animation Speed: 1
 - [459, 464]
"Pulley Hold" (index: 465)
 - Animation Speed: 1
 - [465, 470]
"Shimmy Idle" (index: 471)
 - Animation Speed: 0
 - [471]
"Shimmy Move" (index: 472)
 - Animation Speed: 1
 - [472, 477]
"Bubble" (index: 478)
 - Animation Speed: 1
 - [478, 482]
"Breathe" (index: 483)
 - Animation Speed: 1
 - [483, 489]
"Ride" (index: 490)
 - Animation Speed: 1
 - [490, 491]
"Cling" (index: 492)
 - Animation Speed: 1
 - [492, 495]
"Bungee" (index: 496)
 - Animation Speed: 1
 - [496, 501]
"TwistRun" (index: 502)
 - Animation Speed: 1
 - [502, 513]
"Transform" (index: 514)
 - Animation Speed: 1
 - [514, 542]
"Fly" (index: 543)
 - Animation Speed: 0
 - [543, 546]
"Fly Tired" (index: 547)
 - Animation Speed: 0
 - []
"Fly Lift" (index: 547)
 - Animation Speed: 0
 - []
"Fly Lift Tired" (index: 547)
 - Animation Speed: 0
 - []
"Swim" (index: 547)
 - Animation Speed: 0
 - []
"Swim Tired" (index: 547)
 - Animation Speed: 0
 - []
//*/

/* KNUCKLES ANIMATIONS
"Idle" (index: 0)
 - Animation Speed: 0
 - [0]
"Bored 1" (index: 1)
 - Animation Speed: 1
 - [1, 70]
"Bored 2" (index: 71)
 - Animation Speed: 2
 - [71]
"Look Up" (index: 72)
 - Animation Speed: 128
 - [72, 79]
"Crouch" (index: 80)
 - Animation Speed: 128
 - [80, 85]
"Walk" (index: 86)
 - Animation Speed: 64
 - [86, 97]
"Air Walk" (index: 98)
 - Animation Speed: 64
 - [98, 109]
"Jog" (index: 110)
 - Animation Speed: 96
 - [110, 119]
"Run" (index: 120)
 - Animation Speed: 128
 - [120, 128]
"Dash" (index: 129)
 - Animation Speed: 256
 - [129, 133]
"Jump" (index: 134)
 - Animation Speed: 60
 - [134, 149]
"Spring Twirl" (index: 150)
 - Animation Speed: 128
 - [150, 159]
"Spring Diagonal" (index: 160)
 - Animation Speed: 128
 - [160, 161]
"Skid" (index: 162)
 - Animation Speed: 128
 - [162, 166]
"Skid Turn" (index: 167)
 - Animation Speed: 128
 - [167, 170]
"Spindash" (index: 171)
 - Animation Speed: 1
 - [171, 186]
"Ledge Pullup" (index: 187)
 - Animation Speed: 1
 - [187, 195]
"Push" (index: 196)
 - Animation Speed: 1
 - [196, 205]
"Hurt" (index: 206)
 - Animation Speed: 1
 - [206, 210]
"Die" (index: 211)
 - Animation Speed: 0
 - [211]
"Drown" (index: 212)
 - Animation Speed: 0
 - [212]
"Balance 1" (index: 213)
 - Animation Speed: 1
 - [213, 218]
"Balance 2" (index: 219)
 - Animation Speed: 1
 - [219, 224]
"Spring CS" (index: 225)
 - Animation Speed: 128
 - [225, 248]
"Stand CS" (index: 249)
 - Animation Speed: 128
 - [249, 272]
"Fan" (index: 273)
 - Animation Speed: 80
 - [273, 282]
"Victory" (index: 283)
 - Animation Speed: 1
 - [283, 305]
"Outta Here" (index: 306)
 - Animation Speed: 1
 - [306, 320]
"Hang" (index: 321)
 - Animation Speed: 1
 - [321, 328]
"Hang Move" (index: 329)
 - Animation Speed: 1
 - [329, 340]
"Pole Swing V" (index: 341)
 - Animation Speed: 256
 - [341, 352]
"Pole Swing H" (index: 353)
 - Animation Speed: 256
 - [353, 364]
"Shaft Swing" (index: 365)
 - Animation Speed: 256
 - [365, 376]
"Turntable" (index: 377)
 - Animation Speed: 1
 - [377, 388]
"Twister" (index: 389)
 - Animation Speed: 0
 - [389, 412]
"Spiral Run" (index: 413)
 - Animation Speed: 1
 - [413, 436]
"Stick" (index: 437)
 - Animation Speed: 1
 - [437, 442]
"Pulley Hold" (index: 443)
 - Animation Speed: 1
 - [443, 448]
"Shimmy Idle" (index: 449)
 - Animation Speed: 0
 - [449]
"Shimmy Move" (index: 450)
 - Animation Speed: 1
 - [450, 455]
"Bubble" (index: 456)
 - Animation Speed: 1
 - [456, 460]
"Breathe" (index: 461)
 - Animation Speed: 1
 - [461, 467]
"Ride" (index: 468)
 - Animation Speed: 1
 - [468, 469]
"Cling" (index: 470)
 - Animation Speed: 1
 - [470, 473]
"Bungee" (index: 474)
 - Animation Speed: 1
 - [474, 479]
"TwistRun" (index: 480)
 - Animation Speed: 1
 - [480, 491]
"Transform" (index: 492)
 - Animation Speed: 1
 - [492, 520]
"Glide" (index: 521)
 - Animation Speed: 1
 - [521, 529]
"Glide Drop" (index: 530)
 - Animation Speed: 1
 - [530, 534]
"Glide Land" (index: 535)
 - Animation Speed: 1
 - [535, 537]
"Glide Slide" (index: 538)
 - Animation Speed: 1
 - [538, 544]
"Climb Idle" (index: 545)
 - Animation Speed: 1
 - [545, 548]
"Climb Up" (index: 549)
 - Animation Speed: 1
 - [549, 556]
"Climb Down" (index: 557)
 - Animation Speed: 1
 - [557, 558]
//*/

/* SONIC ANIMATIONS
int sonicPoses[2 * 40] = {
    142, 142, // Standing
    0, 7, // Walking
    8, 11, // Running
    12, 23, // Air Flipping
    24, 35, // Air Flipping (Standing)
    36, 47, // Running in Cylinder
    48, 54, // Spinning Standing
    55, 60, // Swinging around a vertical bar
    61, 61, // YEAH!
    62, 67, // Swinging around a horizontal bar
    68, 82, // Running up a Cylinder
    83, 83, // Hanging on Swing bar
    84, 89, // Monkey Bars (Moving)
    91, 95, // Spindash
    97, 97, // Hurt
    98, 98, // Spring
    99, 99, // Hugging Wall
    100, 103, // Monkey Bars (Standing)
    104, 105, // Conveyor (Moving)
    106, 110, // Rolling
    111, 112, // Crouch
    113, 116, // Skidding
    120, 122, // Tipping
    117, 119, // Tipping Further
    123, 125, // Dead
    126, 127, // Hanging on to vertical bar
    128, 128, // Bubble Get
    129, 135, // Level Complete
    136, 137, // Hanging on to horizontal bar
    138, 141, // Pushing
    142, 150, // Waiting
    151, 152, // Looking up
    153, 155, // Whistling
    156, 163, // Air Spinning
    164, 165, // Begin Super
    166, 167, // Loop  Super
};
//*/

/* TAILS ANIMATIONS
int tailsPoses[2 * 44] = {
    129, 129, // Standing
    0, 7, // Walking
    151, 152, // Running
    12, 23, // Air Flipping
    24, 35, // Air Flipping (Standing)
    36, 47, // Running in Cylinder
    48, 54, // Spinning Standing
    55, 60, // Swinging around a vertical bar
    61, 61, // YEAH!
    62, 67, // Swinging around a horizontal bar
    68, 82, // Running up a Cylinder
    83, 83, // Hanging on Swing bar
    84, 89, // Monkey Bars (Moving)
    90, 92, // Spindash
    93, 94, // Hurt
    95, 96, // Spring
    97, 97, // Hugging Wall
    100, 103, // Monkey Bars (Standing)
    104, 105, // Conveyor (Moving)
    106, 108, // Rolling
    109, 109, // Crouch
    98, 99, // Skidding
    110, 111, // Tipping
    110, 111, // Tipping Further
    112, 112, // Dead
    113, 114, // Hanging on to vertical bar
    115, 115, // Bubble Get
    121, 122, // Level Complete
    123, 124, // Hanging on to horizontal bar
    125, 128, // Pushing
    129, 136, // Waiting
    137, 144, // Looking up
    153, 155, // Whistling
    137, 144, // Air Spinning
    164, 165, // Begin Super
    166, 167, // Loop  Super
    116, 116, // Flying (Downwards)
    117, 117, // Flying (Upwards)
    118, 120, // Flying (Tired)
    145, 149, // Swimming
    155, 156, // Swimming (Tored)
};
//*/

IPlayer::IPlayer() {
    X = 512;
    Y = 64;
    W = 22;
    H = 40;
    DropDashEnabled = true;
}

int  IPlayer::Create() {
    for (int a = 0; a < 360; a++) {
        this->Sin[a] = std::sin(toRadians(a));
        this->Cos[a] = std::cos(toRadians(a));
    }
    DropDashEnabled = true;

    Lives = 0;

    // Flags:
    // 0x00 - None (Animation Controlled By Code)
    // 0x01 - Animation Loops
    // 0x04 - Animation Stops

    if (Character == CharacterType::Knuckles) {
        Sprites[0] = SpriteLoader_LoadGIF(IResources::Load("Player/Knux1.gif")->RW);
        Sprites[1] = SpriteLoader_LoadGIF(IResources::Load("Player/Knux2.gif")->RW);
        Sprites[2] = SpriteLoader_LoadGIF(IResources::Load("Player/Knux3.gif")->RW);
        Sprites[3] = SpriteLoader_LoadGIF(IResources::Load("Player/KnuxCutsceneCPZ.gif")->RW);

        SDL_RWops* SpriteFile = IResources::Load("Player/Knux.bin")->RW;
        skipBytes(SpriteFile, 0x8);
    	int sheets = readByte(SpriteFile);
    	for (int i = 0; i < sheets; i++)
    		free(readRSDKString(SpriteFile));

    	sheets = readByte(SpriteFile);
    	for (int i = 0; i < sheets; i++)
    		free(readRSDKString(SpriteFile));

    	int count = readUShort(SpriteFile);
        Animations = (Animation*)malloc(sizeof(Animation) * count);
        for (int a = 0; a < count; a++) {
            Animations[a].Name = readRSDKString(SpriteFile);
            Animations[a].FrameCount = readUShort(SpriteFile);
            Animations[a].AnimationSpeed = readUShort(SpriteFile);
            Animations[a].FrameToLoop = readByte(SpriteFile);
            Animations[a].Flags = readByte(SpriteFile);
            AnimationMap.emplace(string(Animations[a].Name), a);
            printf("\"%s\" (%d) (Flags: %02X, FtL: %d)\n", Animations[a].Name, a, Animations[a].Flags, Animations[a].FrameToLoop);
            Animations[a].Frames = (AnimFrame*)malloc(sizeof(AnimFrame) * Animations[a].FrameCount);
            for (int i = 0; i < Animations[a].FrameCount; i++) {
                Animations[a].Frames[i].SheetNumber = readByte(SpriteFile);
                Animations[a].Frames[i].Duration = readUShort(SpriteFile);
                skipBytes(SpriteFile, 2);
                Animations[a].Frames[i].X = readUShort(SpriteFile);
                Animations[a].Frames[i].Y = readUShort(SpriteFile);
                Animations[a].Frames[i].W = readUShort(SpriteFile);
                Animations[a].Frames[i].H = readUShort(SpriteFile);
                Animations[a].Frames[i].OffX = readShort(SpriteFile);
                Animations[a].Frames[i].OffY = readShort(SpriteFile);
                skipBytes(SpriteFile, 16);
            }
        }
        SDL_RWclose(SpriteFile);
	}
	return 1;
}

void IPlayer::ChangeAnimation(int animationID) {
    ChangeAnimation(animationID, 0);
}
void IPlayer::ChangeAnimation(int animationID, int startFrame) {
    if (CurrentAnimation != animationID)
        CurrentFrame = startFrame * 0x100;
    CurrentAnimation = animationID;
    AnimationDone = 0;
}
void IPlayer::ChangeAnimation2(int animationID) {
    ChangeAnimation2(animationID, 0);
}
void IPlayer::ChangeAnimation2(int animationID, int startFrame) {
    CurrentFrame = startFrame * 0x100;
    CurrentAnimation = animationID;
    AnimationDone = 0;
}

int  IPlayer::Update() {
    StepBegin();
    Step();
    StepEnd();

    if (Action == ActionType::Jumping || Action == ActionType::Rolling || Action == ActionType::Glide || Action == ActionType::GlideFall || Action == ActionType::Fly) {
        H = 30;
    }
    else {
        H = 40;
    }
    if (ForceRoll)
		H = 28;
	return 1;
}
void IPlayer::LateUpdate() {
    //DisplayAngle = toRadians(Angle);
    DisplayFlip = Flip;

    if (Ground) {
        //SlowRotationReset = false;
    }

    float OffX = (Action == ActionType::Rolling ? 5 : 0) * this->Sin[Angle];
    float OffY = (Action == ActionType::Rolling ? 5 : 0) * this->Cos[Angle];

    OffX += DisplayFlip * (Action == ActionType::Push ? 2 : 0);

    // Sonic 3 Animations
    if (!Scene->ManiacMode) {
        if (Character == CharacterType::Sonic || Character == CharacterType::Knuckles) {
            if (Action == ActionType::Normal) {
                if (abs(Speed) > 0) {
                    if (abs(Speed) >= 6)
                        AnimSet(8, 11, fmax(8 - (int)abs(Speed), 1), false);
                    else
                        AnimSet(0, 7, fmax(8 - (int)abs(Speed), 1), false);
                }
                else {
                    AnimSet(142, 142, 2, true);
                }
            }
            else if (Action == ActionType::LookUp) {
                AnimSet(151, 152, 2, true);
            }
            else if (Action == ActionType::Push) {
                AnimSet(138, 141, 32, false);
            }
            else if (Action == ActionType::Hurt) {
                AnimSet(97, 97, 4, true);
            }
            else if (Action == ActionType::Peril) {
                AnimSet(97, 97, 4, true);
            }
            else if (Action == ActionType::Dead) {
                if (Underwater)
                    AnimSet(123, 123, 4, true);
                else
                    AnimSet(123, 123, 4, true);
            }
            else if (Action == ActionType::Rolling) {
                AnimSet(106, 110, fmax(5 - (int)abs(Speed), 1), false);
            }
            else if (Action == ActionType::Skid) {
                AnimSet(113, 116, 2, true);
            }
            else if (Action == ActionType::Jumping) {
                AnimSet(106, 110, fmax(4 - (int)abs(GroundSpeed), 1), false);
            }
            else if (Action == ActionType::CrouchDown) {
                AnimSet(111, 112, 4, true);
            }
            else if (Action == ActionType::Spindash) {
                AnimSet(91, 95, 4, false);
            }
            else if (Action == ActionType::Spring) {
                AnimSet(12, 23, 4, false);
            }
            else if (Action == ActionType::Grab) {
                AnimSet(101, 101, 8, false);
            }
            else if (Action == ActionType::Twirl) {
                AnimSet(12, 23, 4, false);
            }
            // Special States
            else if (Action == ActionType::Glide) {
                AnimSet(156, 156, 1, true);
            }
            else if (Action == ActionType::GlideFall) {
                AnimSet(106, 110, fmax(5 - (int)abs(Speed), 1), false);
            }
            else if (Action == ActionType::Climb) {
                AnimSet(103, 103, 1, true);
            }
            else if (Action == ActionType::ClimbRise) {
                AnimSet(187, 195, 3, true);
            }
        }
    }
    // Mania Animations
    else {
        if (Character == CharacterType::Sonic) {
            if (Action == ActionType::Normal) {
                if (abs(Speed) > 0) {
                    if (abs(Speed) >= 12)
                        AnimSet(138, 141, 1, false);
                    else if (abs(Speed) >= 8)
                        AnimSet(129, 136, 2, false);
                    else if (abs(Speed) >= 4)
                        AnimSet(129, 136, 3, false);
                    else
                        AnimSet(94, 105, 4, false);
                }
                else {
                    AnimSet(0, 0, 2, false);
                }
            }
            else if (Action == ActionType::LookUp) {
                AnimSet(80, 85, 2, true);
            }
            else if (Action == ActionType::Push) {
                AnimSet(219, 228, 4, false);
            }
            else if (Action == ActionType::Hurt) {
                AnimSet(229, 233, 4, true);
            }
            else if (Action == ActionType::Peril) {
                AnimSet(232, 233, 4, false);
            }
            else if (Action == ActionType::Dead) {
                if (Underwater)
                    AnimSet(235, 235, 4, true);
                else
                    AnimSet(234, 234, 4, true);
            }
            else if (Action == ActionType::Rolling) {
                AnimSet(142, 157, fmax(5 - (int)abs(Speed), 1), false);
            }
            else if (Action == ActionType::Skid) {
                AnimSet(170, 182, 2, true);
            }
            else if (Action == ActionType::Jumping) {
                if (DropDashRev >= 21 / 2) {
                    AnimSet(203, 218, 1, false);
                }
                else {
                    AnimSet(142, 157, fmax(5 - (int)abs(GroundSpeed), 1), false);
                }
            }
            else if (Action == ActionType::CrouchDown) {
                AnimSet(88, 92, 2, true);
            }
            else if (Action == ActionType::Spindash) {
                AnimSet(188, 202, 2, false);
            }
            else if (Action == ActionType::Spring) {
                AnimSet(158, 167, 4, false);
                DisplayFlip = 1;
            }
            else if (Action == ActionType::Grab) {
                AnimSet(343, 350, 8, false);
            }
            else if (Action == ActionType::Twirl) {
                AnimSet(252, 275, 4, false);
            }
        }
        else if (Character == CharacterType::Tails) {
            if (Action == ActionType::Normal) {
                if (abs(Speed) > 0) {
                    if (abs(Speed) >= 7)
                        AnimSet(107, 108, 1, false);
                    else if (abs(Speed) >= 5)
                        AnimSet(98, 104, 2, false);
                    else if (abs(Speed) >= 4)
                        AnimSet(86, 94, 3, false);
                    else
                        AnimSet(62, 73, 4, false);
                }
                else {
                    AnimSet(0, 0, 2, false);
                }

                OffX = 4 * this->Sin[Angle];
                OffY = 4 * this->Cos[Angle];
            }
            else if (Action == ActionType::Rolling) {
                AnimSet(110, 115, fmax(5 - (int)abs(Speed), 1), false);
                OffX = 7 * this->Sin[Angle];
                OffY = 7 * this->Cos[Angle];
            }
            else if (Action == ActionType::Skid) {
                AnimSet(128, 138, 2, true);
                OffY = 4;
            }
            else if (Action == ActionType::Jumping) {
                AnimSet(110, 115, fmax(2 - (int)abs(GroundSpeed), 1), false);
            }
            else if (Action == ActionType::CrouchDown) {
                AnimSet(56, 60, 2, true);
                OffX = 4 * this->Sin[Angle];
                OffY = 4 * this->Cos[Angle];
            }
            else if (Action == ActionType::Spindash) {
                AnimSet(143, 158, 2, false);
                OffX = 4 * this->Sin[Angle];
                OffY = 4 * this->Cos[Angle];
            }
            // Special States
            else if (Action == ActionType::Fly) {
                if (FlyTimer > 0) {
                    AnimSet(474, 477, 2, false);
                }
                else {
                    AnimSet(478, 485, 3, false);
                }
            }
        }
        else if (Character == CharacterType::Knuckles) {
            if (Action == ActionType::Normal) {
                if (abs(Speed) > 0) {
                    if (abs(Speed) >= 10)
                        ChangeAnimation(AnimationMap["Dash"]);
                    else if (abs(Speed) >= 7)
                        ChangeAnimation(AnimationMap["Run"]);
                    else if (abs(Speed) >= 6)
                        ChangeAnimation(AnimationMap["Jog"]);
                    else if (!Ground)
                        ChangeAnimation(AnimationMap["Air Walk"]);
                    else
                        ChangeAnimation(AnimationMap["Walk"]);
                }
                else {
                    ChangeAnimation(AnimationMap["Idle"]);
                }
            }
            else if (Action == ActionType::LookUp) {
                ChangeAnimation(AnimationMap["Look Up"]);
                if (CurrentFrame >= 3 * 0x100)
                    CurrentFrame = 3 * 0x100;
            }
            else if (Action == ActionType::Push) {
                ChangeAnimation(AnimationMap["Push"]);
            }
            else if (Action == ActionType::Hurt) {
                ChangeAnimation(AnimationMap["Hurt"]);
            }
            else if (Action == ActionType::Peril) {
                ChangeAnimation(AnimationMap["Hurt"], 0x100);
            }
            else if (Action == ActionType::Dead) {
                if (Underwater)
                    ChangeAnimation(AnimationMap["Drown"]);
                else
                    ChangeAnimation(AnimationMap["Die"]);
            }
            else if (Action == ActionType::Rolling) {
                //AnimSet(134, 149, fmax(5 - (int)abs(Speed), 1), false);
                ChangeAnimation(AnimationMap["Jump"]);
            }
            else if (Action == ActionType::Skid) {
                if (abs(Speed) < 3)
                    ChangeAnimation(AnimationMap["Skid Turn"]);
                else
                    ChangeAnimation(AnimationMap["Skid"]);
            }
            else if (Action == ActionType::Jumping) {
                //AnimSet(134, 149, fmax(4 - (int)abs(GroundSpeed), 1), false);
                ChangeAnimation(AnimationMap["Jump"]);
            }
            else if (Action == ActionType::CrouchDown) {
                ChangeAnimation(AnimationMap["Crouch"]);
                if (CurrentFrame >= 4 * 0x100)
                    CurrentFrame = 4 * 0x100;
            }
            else if (Action == ActionType::Spindash) {
                ChangeAnimation(AnimationMap["Spindash"]);
            }
            else if (Action == ActionType::Spring) {
                ChangeAnimation(AnimationMap["Spring Twirl"]);
                DisplayFlip = 1;
            }
            else if (Action == ActionType::Grab) {
                ChangeAnimation(AnimationMap["Hang"]);
            }
            else if (Action == ActionType::Twirl) {
                ChangeAnimation(AnimationMap["Spring CS"]);
            }
            else if (Action == ActionType::Fan) {
                //ChangeAnimation(AnimationMap["Fan"]);
                ChangeAnimation(AnimationMap["Spring CS"]);
            }
            else if (Action == ActionType::InStream) {
                ChangeAnimation(AnimationMap["Fan"]);
            }
            // Special States
            else if (Action == ActionType::Glide) {
                if (GlideTurnSpeed == 0) {
                    //AnimSet(527, 529, fmax(12 - (int)abs(Speed), 1), false);
                    ChangeAnimation(AnimationMap["Glide"], 0x400);
                    GlideTurnFlag = false;
                }
                else {
                    TurnValue = 5;
                    if (!GlideTurnFlag && (this->Cos[GlideTurnCos] * Flip) >= 0.9f) {
                        TurnValue = 5;
                    }
                    else if (!GlideTurnFlag && (this->Cos[GlideTurnCos] * Flip) >= 0.7f && (this->Cos[GlideTurnCos] * Flip) < 0.9f) {
                        TurnValue = 4;
                    }
                    else if (!GlideTurnFlag && (this->Cos[GlideTurnCos] * Flip) >= 0.6f && (this->Cos[GlideTurnCos] * Flip) < 0.7f) {
                        TurnValue = 3;
                    }
                    else if (!GlideTurnFlag && (this->Cos[GlideTurnCos] * Flip) >= 0.4f && (this->Cos[GlideTurnCos] * Flip) < 0.6f) {
                        TurnValue = 2;
                    }
                    else if (!GlideTurnFlag && (this->Cos[GlideTurnCos] * Flip) >= 0.2f && (this->Cos[GlideTurnCos] * Flip) < 0.4f) {
                        TurnValue = 1;
                    }
                    else if (!GlideTurnFlag && (this->Cos[GlideTurnCos] * Flip) >= 0.0f && (this->Cos[GlideTurnCos] * Flip) < 0.2f) {
                        TurnValue = 0;
                    }
                    else if (!GlideTurnFlag) {
                        GlideTurnFlag = true;
                        Flip *= -1;
                    }
                    else if (GlideTurnFlag && (this->Cos[GlideTurnCos] * -Flip) >= -1.0f && (this->Cos[GlideTurnCos] * -Flip) < -0.5f) {
                        TurnValue = 5;
                    }

                    if (TurnValue == 5) {
                        ChangeAnimation(AnimationMap["Glide"], 0x400);
                    }
                    else if (TurnValue == 4) {
                        ChangeAnimation2(AnimationMap["Glide"], 0x300);
                    }
                    else if (TurnValue == 3) {
                        ChangeAnimation2(AnimationMap["Glide"], 0x200);
                        if (!GlideTurnFlag)
                            DisplayFlip = -Flip;
                    }
                    else if (TurnValue == 2) {
                        ChangeAnimation2(AnimationMap["Glide"], 0x200);
                        //if (!GlideTurnFlag)
                            //DisplayFlip = -Flip;
                    }
                    else if (TurnValue == 1) {
                        ChangeAnimation2(AnimationMap["Glide"], 0x100);
                        //if (!GlideTurnFlag)
                            //DisplayFlip = -Flip;
                    }
                    else if (TurnValue == 0) {
                        ChangeAnimation2(AnimationMap["Glide"], 0x000);
                        if (!GlideTurnFlag)
                            DisplayFlip = -Flip;
                    }
                    ChangeAnimation2(AnimationMap["Glide"], 0x000);
                    AnimSet(521 + TurnValue, 521 + TurnValue, 1, true);
                }
            }
            else if (Action == ActionType::GlideFall) {
                ChangeAnimation(AnimationMap["Glide Drop"]);
            }
            else if (Action == ActionType::GlideFallLand) {
                ChangeAnimation(AnimationMap["Glide Land"]);
            }
            else if (Action == ActionType::GlideSlide) {
                ChangeAnimation(AnimationMap["Glide Slide"]);
            }
            else if (Action == ActionType::Climb) {
                if (InputUp) {
                    ChangeAnimation(AnimationMap["Climb Up"]);
                }
                else if (InputDown) {
                    ChangeAnimation(AnimationMap["Climb Down"]);
                }
                else {
                    ChangeAnimation(AnimationMap["Climb Idle"]);
                }
            }
            else if (Action == ActionType::ClimbRise) {
                ChangeAnimation(AnimationMap["Ledge Pullup"]);
            }
        }
    }



    AnimExecute();


	Animation animation = Animations[CurrentAnimation];

	if (CurrentFrame / 0x100 >= animation.FrameCount - 1) {
		if (false)
			CurrentFrame = animation.FrameCount * 0x100 - 0x100;
		else
			CurrentFrame = animation.FrameToLoop * 0x100;

        AnimationDone = 1;
	}

    if (animation.AnimationSpeed > 2)
        CurrentFrame += animation.AnimationSpeed;
    else if (animation.Frames[CurrentFrame / 0x100].Duration != 0)
        CurrentFrame += 0x100 / animation.Frames[CurrentFrame / 0x100].Duration;

    //DisplayAngle += AngleDifference((int)DisplayAngle, Angle) / 3.f;

    /*
    if (InputLeft)
        Frame--;
    if (InputRight)
        Frame++;

    if (Frame < 0)
        Frame = 0;
    //*/




    if (Action == ActionType::Climb || Action == ActionType::ClimbRise) {
        OffX += Flip * 2;
        if (Flip < 0)
            OffX++;
    }

    if (Action == ActionType::Glide)
        OffY += 4;
    if (Action == ActionType::Rolling) {
        CameraX = OffX;
        CameraY = -OffY;
    }
    if (Action == ActionType::CrouchDown || Action == ActionType::Spindash) {
        DisplayAngle = 0;
    }
    if (Action == ActionType::Fan || Action == ActionType::Twirl) {
        DisplayFlip = 1;
    }

    //CameraX += (OffX * 0 - CameraX) / 3.f;
    //CameraY += (OffY * 0 - CameraY) / 3.f;

    if (Action == ActionType::CrouchDown) {
        if (CameraLookTimer >= 60) {
            CameraY = fmin(CameraY + 2, 88.f);
        }
        else {
            if (CameraY < 0)
                CameraY = fmin(CameraY + 2, 0.f);
            if (CameraY > 0)
                CameraY = fmax(CameraY - 2, 0.f);
        }
    }
    else if (Action == ActionType::LookUp) {
        if (CameraLookTimer >= 60) {
            CameraY = fmax(CameraY - 2, -104.f);
        }
        else {
            if (CameraY < 0)
                CameraY = fmin(CameraY + 2, 0.f);
            if (CameraY > 0)
                CameraY = fmax(CameraY - 2, 0.f);
        }
    }
    else {
        if (CameraLookTimer >= 60) {
            if (CameraY < 0)
                CameraY = fmin(CameraY + 2, 0.f);
            else if (CameraY > 0)
                CameraY = fmax(CameraY - 2, 0.f);
            else
                CameraLookTimer = 0;
        }
        else {
            CameraY = 0;
        }
    }

    if (Action == ActionType::ClimbRise) {
        if ((int)Frame == 0) {
            OffX = Flip * 3;
            OffY = 15;
        }
        else if ((int)Frame == 1) {
            OffX = Flip * 2;
            OffY = 15;
        }
        else if ((int)Frame == 2) {
            OffX = Flip * 7;
            OffY = 7;
        }
        else if ((int)Frame == 3) {
            OffX = Flip * 12;
            OffY = -1;
        }
        else if ((int)Frame == 4) {
            OffX = Flip * 17;
            OffY = -8;
        }
        else if ((int)Frame == 5) {
            OffX = Flip * 22;
            OffY = -11;
        }
        else if ((int)Frame >= 6 && (int)Frame <= 8) {
            OffX = Flip * 22;
            OffY = -15;
        }
        //251 is the new Y begin animation

        //CameraX += (36 - CameraX) / 3.f;
        //CameraY += (0 - CameraY) / 3.f;
    }

    if (X < 10) {
        X = 10;
        Speed = 0;
        if (Ground)
            Action = ActionType::Normal;
    }

    /*
    if (Scene->CameraLocked) {
        if (X < Scene->CameraX + 10) {
            X = Scene->CameraX + 10;
            Speed = 0;
            if (Ground)
                Action = ActionType::Normal;
        }
        if (X > Scene->CameraX + App->WIDTH - 10) {
            X = Scene->CameraX + App->WIDTH - 10;
            Speed = 0;
            if (Ground)
                Action = ActionType::Normal;
        }
    }
    //*/

    DisplayX = (int)X + (int)OffX;
    DisplayY = (int)Y + (int)OffY;

    if (Action == ActionType::Rolling || Action == ActionType::CrouchDown || Action == ActionType::Spindash) {
        DisplayAngle = 0;
    }
    else if ((Angle < 40 || Angle > 360 - 40) && Ground) {
        DisplayAngle += AngleDifference(DisplayAngle, 0) / 4.f;
    }
    else {
        if (!Ground && Action == ActionType::Normal)
            DisplayAngle += AngleDifference(DisplayAngle, Angle) / 8.f;
        else
            DisplayAngle += AngleDifference(DisplayAngle, Angle) / 2.f;
    }
}
int  IPlayer::Render(int CamX, int CamY) {
    // Mania
    if (Invincibility != InvincibilityType::Temporary || InvincibilityTimer % 6 < 3) {
        Animation animation = Animations[CurrentAnimation];
        AnimFrame currentFrame = animation.Frames[CurrentFrame / 0x100];
        G->DrawSprite(Sprites[currentFrame.SheetNumber],
            currentFrame.X,
            currentFrame.Y,
            currentFrame.W,
            currentFrame.H, (int)DisplayX - CamX, (int)DisplayY - CamY, (int)DisplayAngle, DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX,
            currentFrame.OffX,
            currentFrame.OffY);
    }

    /*
    float OffZ = 0.0f;

    if (Action == ActionType::Dead)
        OffZ = 1.0f;

    if (Invincibility != InvincibilityType::Temporary || InvincibilityTimer % 6 < 3) {
        G->Scale(DisplayFlip, 1.f);
        if (Scene->ManiacMode) {
            if (Palette1 == NULL) {
                G->PaletteShift(-1);
            }
            else {
                G->PaletteShift(0);
                G->SetNextSpriteDrawPalette(Palette1, Palette2);
            }
        }
        else {
            G->PaletteShift(0);
        }

        float FinalAngle = DisplayAngle;
        FinalAngle = toRadians(round(toDegrees(FinalAngle) / 45.f) * 45);
        if (ObjectControlled != 0)
            FinalAngle = DisplayAngle;

        G->DrawSprite(Sprite, (int)DisplayX - CamX, (int)DisplayY - CamY, ForegroundLayer * -0.1f - 0.05f - VisualLayer * 1.1f - OffZ, FinalAngle, (int)Frame + AnimationStart, IE::CenterAlign | IE::MiddleAlign);

        if (Scene->ManiacMode)
            G->SetNextSpriteDrawPalette(NULL, NULL);

        G->PaletteShift(0);
        if (Action == ActionType::Spindash)
            G->DrawSprite(SpriteDashDust, (int)DisplayX - CamX, (int)DisplayY - CamY, ForegroundLayer * -0.1f - 0.05f - VisualLayer * 1.1f - OffZ + 0.01f, (Scene->frameAnim / 2) % 7, IE::CenterAlign | IE::MiddleAlign);

        if (WaterRunning)
            G->DrawSprite(SpriteWaterRun, (int)DisplayX - CamX - DisplayFlip * 24, (int)Y - CamY + 12, ForegroundLayer * -0.1f - 0.05f - VisualLayer * 1.1f - OffZ + 0.01f, (Scene->frameAnim / 4) % 5, IE::CenterAlign | IE::MiddleAlign);

        G->Scale(1.f, 1.f);

        G->SetNextSpriteDrawPalette(NULL, NULL);
    }
    if (Action != ActionType::Dead && !SuperForm) {
        G->PaletteShift(0);
        if (Invincibility != InvincibilityType::Full) {
            int bubbleShieldAnim[55] = {
                1,   0,   9,   0,   9,   0,   9,   1,  0xA,   1,  0xA,   1,  0xA,   2,   9,   2,   9,   2,   9,   3,
                0xA,   3,  0xA,   3,  0xA,   4,   9,   4,   9,   4,   9,   5,  0xA,   5,  0xA,   5,  0xA,   6,   9,   6,
                9,   6,   9,   7,  0xA,   7,  0xA,   7,  0xA,   8,   9,   8,   9,   8,   9,
            };
            int electricShieldAnim1[43] = {
                1,   0,   0,   1,   1,   2,   2,   3,   3,   4,   4,   5,   5,   6,   6,   7,   7,   8,   8,   9,
        		0xA,  0xB, 0x16, 0x16, 0x15, 0x15, 0x14, 0x14, 0x13, 0x13, 0x12, 0x12,
        		0x11, 0x11,	0x10, 0x10,  0xF,	0xF,  0xE,  0xE,	9,  0xA,	 0xB
            };
            if (Shield == ShieldType::Fire) {
                int fa = Scene->frameAnim / 2;
                int fcount = (Scene->frameAnim + (fa % 2) * 32) % 64;
                int fr = fcount / 4;

                int ffiv = fr % 16;
                if (ffiv >= 8) {
                    ffiv += 8;
                }

                if (ShieldAction) {
                    fcount %= 16 * 2;
                    fr = fcount / 2;

                    ffiv = fr % 16;
                    ffiv = ffiv % 8 + 8;
                    G->Scale(DisplayFlip, 1.0f);
                }

                float dZ = 0;
                if (ffiv >= 16) {
                    dZ = 0.1f;
                }

                G->DrawSprite(SpriteShieldFire, (int)DisplayX - CamX, (int)DisplayY - CamY, ForegroundLayer * -0.1f - 0.05f - VisualLayer * 1.1f - OffZ - 0.01f + dZ, 0, ffiv, IE::CenterAlign | IE::MiddleAlign);
                G->Scale(1.f, 1.f);
            }
            else if (Shield == ShieldType::Electric) {
                int fcount = Scene->frameAnim;
                fcount %= 43 * 2;
                int fr = electricShieldAnim1[fcount / 2] % 12;
                G->DrawSprite(SpriteShieldElectric, (int)DisplayX - CamX, (int)DisplayY - CamY, ForegroundLayer * -0.1f - 0.05f - VisualLayer * 1.1f - OffZ - 0.01f, 0, fr, IE::CenterAlign | IE::MiddleAlign);
            }
            else if (Shield == ShieldType::Bubble) {
                int fcount = Scene->frameAnim;
                fcount %= 55 * 2;
                int fr = bubbleShieldAnim[fcount / 2];
                if (!ShieldAction) {
                    G->DrawSprite(SpriteShieldBubble, (int)DisplayX - CamX, (int)DisplayY - CamY, ForegroundLayer * -0.1f - 0.05f - VisualLayer * 1.1f - OffZ - 0.01f, 0, fr, IE::CenterAlign | IE::MiddleAlign);
                }
                else {
                    if (Gravity < 9)
                        G->DrawSprite(SpriteShieldBubble, (int)DisplayX - CamX, (int)DisplayY - CamY, ForegroundLayer * -0.1f - 0.05f - VisualLayer * 1.1f - OffZ - 0.01f, 0, 10, IE::CenterAlign | IE::MiddleAlign);
                    else
                        G->DrawSprite(SpriteShieldBubble, (int)DisplayX - CamX, (int)DisplayY - CamY, ForegroundLayer * -0.1f - 0.05f - VisualLayer * 1.1f - OffZ - 0.01f, 0, 11, IE::CenterAlign | IE::MiddleAlign);
                }
            }
            else if (Shield == ShieldType::Instashield) {
                G->DrawSprite(SpriteShieldInsta, (int)DisplayX - CamX, (int)DisplayY - CamY, ForegroundLayer * -0.1f - 0.05f - VisualLayer * 1.1f - OffZ - 0.01f, 0, ShieldAnimation, IE::CenterAlign | IE::MiddleAlign);
            }
        }
    }

    if (Scene->ShowHitboxes) {
        G->PaletteShift(-1);
        G->DrawRectangle((int)(round(X) - CamX - W / 2.f), (int)(round(Y) - CamY - H / 2.f), ForegroundLayer * -0.1f - 0.05f - VisualLayer * 1.1f - OffZ - 0.1f, W, H, IColor(1, 1, 1, 0.5f));
    }
    //*/
	return 1;
}

void IPlayer::AnimSet(int Start, int End, int Speed, bool Stop) {
    AnimationEnd = End;
    AnimationStop = Stop;
    AnimationStart = Start;
    AnimationSpeed = Speed;

}
void IPlayer::AnimExecute() {
    int animFrameCount = AnimationEnd - AnimationStart + 1;
    // reset if animation change
    if (Frame < 0 || Frame >= animFrameCount) {
        //fcountOffset = fcount;
    }


    if (Frame < 0) {
        Frame = 0;
    }
    if (Frame >= animFrameCount) {
        if (AnimationStop) {
            Frame = 0;
        }
        else {
            Frame = animFrameCount - 1;
        }
    }

    if (AnimationStop) {
        if (AnimationSpeed > 0)
            Frame = fmin(Frame + 1.f / AnimationSpeed, (float)animFrameCount - 1);
        else
            Frame = 0;//fmax(frm + speedAu, 0);
    }
    else {
        if (AnimationSpeed != 0)
            Frame = fmod(Frame + 1.f / AnimationSpeed + animFrameCount, animFrameCount);
        else
            Frame = 0;
    }
}

void IPlayer::Deform() {
    SuperForm = false;

    SuperFormAnim = SuperFormAnimType::Deforming;
    SuperFormAnimTimer = 40;
    SuperFormAnimTimerMax = 40;
}

void IPlayer::StepBegin() {
    //XPrevious = X;
    //YPrevious = Y;
    LastSpeed = Speed;

    if (CameraLag && CameraLockTimer > 0) {
        CameraLockTimer--;
    }

    // Input Management
    Landed = false;
    if (Action == ActionType::Dead || !SuperEnabled) {
        if (SuperForm) {
            Deform();
        }
    }
    if (Action == ActionType::Dead) {
        //App->Stack->Remove("Drowning");
        return;
    }
    if (Ground) {
        EnemyCombo = 0;
        SpringFlip = 0;
        LastGrab = NULL;
        //SlowRotationReset = false;
        StoredRotation = DisplayAngle;
    }

    // Timers
    if (Invincibility != InvincibilityType::None) {
        if (Invincibility == InvincibilityType::Full) {
            UnderwaterTimer = 1800;
            if (InvincibilityTimer % 8 == 0 && !SuperForm) {
                //InvAngle = WrapAngle(InvAngle + 45);
                //float X = this->Cos[InvAngle]*16;
                //float Y = this->Sin[InvAngle]*16;
                //instance_create(X+X, Y+Y, objInvSparkle)
                //instance_create(X-X, Y-Y, objInvSparkle)
            }
        }

        if (InvincibilityTimer == 0) {
            if (Invincibility == InvincibilityType::Full) {
                //App->Stack->Remove("Invincibility");
            }
            Invincibility = InvincibilityType::None;
        }
        InvincibilityTimer -= 1;
    }
    if (SpeedSneakersActive) {
        if (SpeedSneakersTimer == 0) {
            //App->Stack->Remove("Speed Shoes");
            SpeedSneakersActive = false;
        }
        SpeedSneakersTimer -= 1;
    }
    if (SuperForm) {
        if (SuperFormTimer % 60 == 0) {
            /*
            sc->rings -= 1;
            if (sc->rings == 0) {
                Deform();
            }
            */
        }
        SuperFormTimer = (SuperFormTimer + 1) % 60;
    }
    if (ShieldUsable == false && Action != ActionType::Jumping) {
        ShieldUsable = true;
        ShieldAction = false;
    }

    // Underwater
    if (Action == ActionType::Pipe) {
        Underwater = false;
    }
    if (Underwater) {
        if (Shield == ShieldType::Bubble)
            UnderwaterTimer = 1800;

        if (UnderwaterTimer == 660) {
            //App->Stack->Push("Drowning", Scene->aud_BGM_Drowning, 11, 0, 0, false, true);
        }
        else if (UnderwaterTimer > 660) {
            //App->Stack->Remove("Drowning");
        }

        //if (UnderwaterTimer == 1500 || UnderwaterTimer == 1200 || UnderwaterTimer == 900)
            //Scene->aud[0xA9]->Play(3);

        if (UnderwaterTimer == 0) {
            //Scene->aud_C_Drown->Play(3); // $AudioPlay(aud_C_Drown, 3);
            Die();
        }
        UnderwaterTimer--;
    }
    else {
        UnderwaterTimer = 1800;
        //App->Stack->Remove("Drowning");
    }

    // Physics Values
    // On Land

    if (!Ground) {
        AccelRate = 0.0546875f;
    }
    else
        AccelRate = 0.046875f;

    if (!Underwater) {
        if (Action != ActionType::Fly)
            GravityRate = 0.21875f;
        if (Action == ActionType::Hurt)
            GravityRate = 0.1875f;

        JumpRelease = JumpReleaseValue;

        if (!SuperForm || SpeedSneakersActive) {
            JumpHeight = JumpValue;
            SkidRate = 0.5f;
        }

        if (!SpeedSneakersActive) {
            if (!SuperForm) {
                Acceleration = AccelRate;
                if (Action != ActionType::Fly)
                    TopSpeed = 6.0f;
                RollingFriction = 0.0234375f;
            }
            else {
                // Super Form values
                JumpHeight = -8.0f;
                SkidRate = 1.0f;
                if (Action != ActionType::Fly)
                    TopSpeed = 10.0f;
                RollingFriction = 0.0234375f;
                Acceleration = AccelRate * 4.0f;
            }
        }
        else {
            Acceleration = AccelRate * 2.0f;
            if (Action != ActionType::Fly)
                TopSpeed = 12.0f;
            RollingFriction = 0.046875f;
        }
    }
    // Underwater
    else {
        JumpHeight = JumpValueWater;
        JumpRelease = JumpReleaseValueWater;

        if (Action != ActionType::Fly)
            GravityRate = 0.0625f;
        if (Action == ActionType::Hurt)
            GravityRate = 0.0425f;

        if (Shield == ShieldType::Fire || Shield == ShieldType::Electric)
            Shield = ShieldType::None;

        if (!SuperForm) {
            if (Action != ActionType::Fly)
                TopSpeed = 3.0f;

            Acceleration = AccelRate / 2.0f;
            RollingFriction = 0.01171875f;
            SkidRate = 0.25f;
        }
        else {
            if (Action != ActionType::Fly)
                TopSpeed = 5.0f;

            Acceleration = AccelRate * 2.0f;
            RollingFriction = 0.0234375f;
            SkidRate = 0.5f;
        }
    }

    if (!Ground && Action != ActionType::Fly) {
        Acceleration *= 2.0f;
    }

    if (SuperFlight && SuperForm) {
        GravityRate = 0;
        JumpHeight = 0;
        if (InputUp) {
            Gravity -= Acceleration * SpeedMultiplier / 2.0f;
        }
        else if (InputDown) {
            Gravity += Acceleration * SpeedMultiplier / 2.0f;
        }
        else if (InputLeft || InputRight) {

        }
        else {
            Speed -= fmin(abs(Speed), Acceleration * SpeedMultiplier / 6.0f) * signum(Speed);
            Gravity -= fmin(abs(Gravity), Acceleration * SpeedMultiplier / 6.0f) * signum(Gravity);
        }
        Ground = false;
    }

    if (CollisionSquish()) {
        Die();
    }
}
void IPlayer::Step() {
    if (Action == ActionType::Dead) {
        return;
    }

    if (Ground && (abs(this->Sin[Angle]) > 0.5f || InputRight || InputLeft) &&
        Action != ActionType::Rolling &&
        Action != ActionType::Pipe &&
        Action != ActionType::CrouchDown &&
        Action != ActionType::Spindash &&
        Action != ActionType::LookUp)
        Speed -= (0.125f * this->Sin[Angle]) / SpeedMultiplier;

    if (abs(Speed) < 2.0f && Shield == ShieldType::Fire && ShieldAction)
        ShieldAction = false;

    if (ForceRoll)
        Action = ActionType::Rolling;

    if (Action == ActionType::Rolling || Action == ActionType::Slide) {
        if (signum(Speed) == signum(this->Sin[Angle])) {
            Speed -= (0.078125f * this->Sin[Angle]) / SpeedMultiplier;
        }
        else {
            Speed -= (0.3125f * this->Sin[Angle]) / SpeedMultiplier;
        }
    }

    // -- Accelerate when holding InputLeft/InputRight keys, and decelerate when hold neither. --
    if (InputAlarm <= 0 &&
       (!ShieldAction || Shield == ShieldType::Bubble) &&
       (Action == ActionType::Normal ||
       (Action == ActionType::Corkscrew/* && Animation != "Rolling"*/) ||
       (Action == ActionType::Jumping && (JumpVariable >= 0 || !RollJumpLock)) ||
        Action == ActionType::Spring ||
        Action == ActionType::Fan ||
        Action == ActionType::Fly ||
        Action == ActionType::GlideFall ||
        Action == ActionType::Peril) && ObjectControlled == 0) {
        if (InputLeft && Speed > -TopSpeed)
            Speed = fmax(Speed - Acceleration * SpeedMultiplier, -TopSpeed);
        else if (InputRight && Speed < TopSpeed)
            Speed = fmin(Speed + Acceleration * SpeedMultiplier,  TopSpeed);

        if (!InputRight && !InputLeft &&
            Speed != 0 &&
           (Ground || Action == ActionType::Corkscrew) &&
            ObjectControlled == 0 &&
           (!SuperForm || (SuperForm && !SuperFlight)))
            Speed -= fmin(abs(Speed), AccelRate * SpeedMultiplier) * signum(Speed);

    }

    // -- Handle Input Alarm.
    if (InputAlarm > 0 && (Ground || InputAlarm < 30)) {
        InputAlarm -= 1;
    }

    // Object Control
    if (ObjectControlled % 4 == 0) {
        FlagsAllowXMovement = true;
        FlagsAllowYMovement = true;
    }
    else if (ObjectControlled % 4 == 1) {
        FlagsAllowXMovement = false;
        FlagsAllowYMovement = false;
    }
    else if (ObjectControlled % 4 == 2) {
        FlagsAllowXMovement = false;
        FlagsAllowYMovement = true;
    }
    else if (ObjectControlled % 4 == 3) {
        FlagsAllowXMovement = true;
        FlagsAllowYMovement = false;
    }

    // Movement
    if (Action == ActionType::Dead) {
        return;
    }
    if (FlagsAllowXMovement) {
        //HandleBreakableTerrain();
        WallCollision();
        SpeedMovement();
    }
    if (FlagsAllowYMovement) {
        //HandleBreakableTerrain();
        if (!Ground) {
            if (Gravity < 0.0f && Gravity > -4.0f)
                Speed -= (Speed / 0.125f) / 256.0f;

            GravityMovement();

            if (!Ground &&
                Action != ActionType::Glide &&
                Action != ActionType::Climb &&
                Action != ActionType::ClimbRise &&
                Action != ActionType::Transform &&
                Action != ActionType::Grab &&
                Action != ActionType::Quicksand)
            Gravity += GravityRate * SpeedMultiplier;
        }
    }

    // Object Handle
    if (FlagsAllowObjectHandle) {
        //HandleObjects();
        //HandleBreakableTerrain();
        HandleSprings();
        /*HandleRings();

        HandleBumpers();
        HandleBalloons();
        HandleDashers();
        HandleSpikes();
        HandleEnemies();
        HandleMonitors();
        HandlePipes();
        HandleCheckpoint();
        HandleBubbles();
        HandleHarmful();
        HandleCollapsingPlatforms();
        HandleSignpost();
        HandleChaosEmeralds();
        HandleGrabPoles();
        HandleCorkews();
        HandleQuicksand();
        HandleLayers();
        HandleConveyers();
        HandleMisc();
        HandleCutscenes();*/
    }

    // Actions
    HandleAction();

    // Jumping out of Object Control
    if (ObjectControlled > 0 && ObjectControlled < 4 && InputJump) {
        ObjectControlled = 0;
        if (Action == ActionType::Grab) {
            int An = Angle;
            Jump();
            Speed   =  std::cos(toRadians(An)) * GroundSpeed;
            Gravity = -std::sin(toRadians(An)) * GroundSpeed;
        }
        else {
            Jump();
            Gravity = -3;
        }
    }

    // Misc
    /*if Sonic falls past ground bounds,
        Dead(sndPlayerDead);
    if (Action != ActionFly &&(audio_is_playing(sndFly) || audio_is_playing(sndFlyFall))) {
        audio_stop_sound(sndFly);
        audio_stop_sound(sndFlyFall);
    }*/
    if (Action != ActionType::Fly) {
        FlyTimer = 480;
        FlyFlag = 0;
    }
    if (Shield == ShieldType::Instashield && ShieldAnimation >= 7) {
        Shield = ShieldType::None;
        ShieldAnimation = 0;
    }

    if (Shield == ShieldType::Instashield && ((!SuperForm && Invincibility == InvincibilityType::None && Action != ActionType::Transform))) {
        ShieldAnimation++;
    }

    // Speed Caps
    if (SpeedCap == SpeedCapType::S1) {
        if (Action != ActionType::Rolling &&
            (Action != ActionType::Jumping || JumpVariable > 0) && InputAlarm <= 0) {
            if (InputRight)
                Speed = fmin(Speed, TopSpeed);
            if (InputLeft)
                Speed = fmax(Speed, -TopSpeed);
        }
    }
    else if (SpeedCap == SpeedCapType::SCD) {
        if (!Ground && (Action != ActionType::Jumping || JumpVariable > 0) && InputAlarm <= 0) {
            if (InputRight)
                Speed = fmin(Speed, TopSpeed);
            if (InputLeft)
                Speed = fmax(Speed, -TopSpeed);
        }
    }
}
void IPlayer::StepEnd() {
    if (Action == ActionType::Dead) {
        Gravity += 0.21875f;
        Y += Gravity;
        return;
    }

    // Reset Drop Dash Charge if not jumping
    if (Action != ActionType::Jumping) {
        DropDashRev = 0;
    }

    if (ObjectControlled > 0)
        return;

    if ((Speed <= 0 || !Ground) && InputLeft && InputAlarm <= 0 &&
        (Action == ActionType::Normal ||
        Action == ActionType::Spring ||
        Action == ActionType::Fan ||
        Action == ActionType::Fly ||
        Action == ActionType::Jumping ||
        Action == ActionType::Quicksand ||
        Action == ActionType::Peril))
        Flip = -1;
    if ((Speed >= 0 || !Ground) && InputRight && InputAlarm <= 0 &&
        (Action == ActionType::Normal ||
        Action == ActionType::Spring ||
        Action == ActionType::Fan ||
        Action == ActionType::Fly ||
        Action == ActionType::Jumping ||
        Action == ActionType::Quicksand ||
        Action == ActionType::Peril))
        Flip = 1;

    if (Speed * this->Cos[AngleMode * 90] < -6 && InputLeft) {
        //camShiftX += (-80.0f - camShiftX) / 20.0f;
    }
    else if (Speed * this->Cos[AngleMode * 90] > 6 && InputRight) {
        //camShiftX += (80.0f - camShiftX) / 20.0f;
    }
    else if (AngleMode == 0 && ObjectControlled == 0) {
        //camShiftX += (0.0f - camShiftX) / 20.0f;
    }
    if (Action == ActionType::Spindash) {
        //camShiftX += (80.0f * Flip - camShiftX) / 20.0f;
    }

    if (CameraLockTimer == 0) {
        if (Action == ActionType::CrouchDown) {
            CameraLookTimer += 1;
        }
        else if (Action == ActionType::LookUp) {
            CameraLookTimer += 1;
        }
    }

    if (Ground)
        GroundSpeed = Speed;

    /*
    if (WaterRunning && Scene->frameAnim % 16 == 0) {
        Scene->aud[0xDB]->Play(3);
    }
    //*/
}

void IPlayer::Vibrate(int controller, double strength, int milliseconds) {

}

int  IPlayer::SpecialModulo(int a, int b) {
    return a - (a / b) * b;
}
int  IPlayer::AngleDifference(int a, int b) {
    //return SpecialModulo(b - a + 180, 360) - 180;
    a = b - a;
    if (a > 180) a -= 360;
    if (a < -180) a += 360;
    return a;
}

bool IPlayer::CollisionSensor360(int obj, int len, int A, int no360) {
    int InitAngle = wrapAngle(Angle);
    bool AB = no360 >= 0;
    if (no360 == 2)
        InitAngle = wrapAngle(AngleMode * 90);
    if (no360 < 0) {
        no360 = abs(A);
        InitAngle = wrapAngle(AngleMode * 90 + 180);
    }
    int X2 = X - 9 * this->Cos[InitAngle];
    int Y2 = Y + 9 * this->Sin[InitAngle];
    if (A == 1) {
        X2 = X;
        Y2 = Y;
    }
    else if (A == 2) {
        X2 = X + 9 * this->Cos[InitAngle];
        Y2 = Y - 9 * this->Sin[InitAngle];
    }

    int Height = 0;

    if (AngleMode == 0 && (Angle < 7 || Angle > 353) && no360 == 0)
        Height = GroundSensorHeightMin;
    else
        Height = GroundSensorHeight;

    if (no360 >= 1)
        Height = GroundSensorHeight;

    int ang = 0;
    for (int i = 0; i < Height + len; i++) {
        if (AB) {
            CheckJumpThrough = true;
        }
        bool Object = CollisionCheckLine((int)X2, (int)Y2, (int)X2, (int)Y2, &ang);
        if (AB) {
            CheckJumpThrough = false;
        }

        if (Object && no360 == 0) {
            return true;
        }
        else if (Object && no360 > 0) {
            return true;
        }
        else {
            if (no360 == 2) {
                X2 += (int)this->Sin[InitAngle];
                Y2 += (int)this->Cos[InitAngle];
            }
            else {
                X2 += this->Sin[InitAngle];
                Y2 += this->Cos[InitAngle];
            }
        }
    }
    return false;
}
bool IPlayer::CollisionASensor(int obj, int len) { return CollisionSensor360(obj, len, 0, 2); }
bool IPlayer::CollisionBSensor(int obj, int len) { return CollisionSensor360(obj, len, 2, 2); }
bool IPlayer::CollisionASensor360(int obj, int len) { return CollisionSensor360(obj, len, 0, 2); }
bool IPlayer::CollisionBSensor360(int obj, int len) { return CollisionSensor360(obj, len, 2, 2); }
bool IPlayer::CollisionMSensor360(int obj, int len) { return CollisionSensor360(obj, len, 1, 0); }

bool IPlayer::CollisionLeftSensor(int obj) {
    int InitAngle = wrapAngle(AngleMode * 90);

    int X1 = X + 4 * this->Sin[InitAngle];
    int Y1 = Y + 4 * this->Cos[InitAngle];

    int X2 = X1 - 14 * this->Cos[InitAngle];
    int Y2 = Y1 + 14 * this->Sin[InitAngle];

    int ang = 0;
    bool Object = CollisionCheckLine(X1, Y1, X2, Y2, &ang);

    if (Object)
        return true;

    return false;
}
bool IPlayer::CollisionRightSensor(int obj) {
    int InitAngle = wrapAngle(AngleMode * 90); // Round angle to nearest 10.

    int X1 = X + 4 * this->Sin[InitAngle];
    int Y1 = Y + 4 * this->Cos[InitAngle];

    int X2 = X1 + 13 * this->Cos[InitAngle];
    int Y2 = Y1 - 13 * this->Sin[InitAngle];

    int ang = 0;
    return CollisionCheckLine(X1, Y1, X2, Y2, &ang);
}

bool IPlayer::CollisionCSensor(int obj, int len) { return CollisionSensor360(obj, len, 0, -2); }
bool IPlayer::CollisionDSensor(int obj, int len) { return CollisionSensor360(obj, len, 2, -2); }

bool IPlayer::CollisionSquish() {
    int outAngle = 0;
    Object *Object1, *Object2;
    bool Object1Col, Object2Col;

    LastObject = NULL;
    Object1Col = CollisionCheckLine((int)X - 9, (int)Y - H / 2 + 5, (int)X + 9, (int)Y - H / 2 + 5, &outAngle);
    Object1 = LastObject;

    LastObject = NULL;
    Object2Col = CollisionCheckLine((int)X - 9, (int)Y + H / 2 - 1, (int)X + 9, (int)Y + H / 2 - 1, &outAngle);
    Object2 = LastObject;

    if (Object1Col && Ground && AngleMode == 0) {
        if (Object1 != NULL) {
            return true;
        }
    }
    return false;
}

bool IPlayer::CollisionCheckLine(float xr, float yr, float x2, float y2, int* angleOut) {
    float X2 = round(xr);
    float Y2 = round(yr);
    float X3 = round(x2);
    float Y3 = round(y2);
    //if (loop)
        //Y2 = fmod((Y2 + sc->levelH * 128), (sc->levelH * 128));

    float angle = 0;
    float len = 0;

    len = std::sqrt((Y2 - Y3) * (Y2 - Y3) + (X3 - X2) * (X3 - X2));

    if (len > 0) {
        angle = std::atan2(Y2 - Y3, X3 - X2);
    }
    else
        angle = 0;

    angle = wrapAngleRad(angle);

    for (int n = 0; n <= len; n++) {
        /*
        if (Ground && abs(Speed) > 7 && Angle == 0 && Y2 >= sc->waterLevel && !Underwater && Y < sc->waterLevel && (sc->act & 0xF0) == 0x20) {
            WaterRun = true;
            return bool { true, -1, true, 0, 0, 0, 0, 0 };
        }
        */

        #if 0
        for (unsigned int o = 0; o < sc->objects_count && objChek; o++) {
            if (sc->objects[o] != NULL) {
                bool noException = true;
                if (sc->objects[o]->data1 == 0x69 && (sc->objects[o]->data2 & 0xF0) == 0x00 && (sc->objects[o]->data2 & 0x0F) > 0x00) {
                    noException = false;
                }

                /*if (!(sc->objects[o]->X - sc->cameraX[app->CurrentViewport] >= 0 &&
                      sc->objects[o]->Y - sc->cameraY[app->CurrentViewport] >= 0 &&
                      sc->objects[o]->X - sc->cameraX[app->CurrentViewport] < app->renderWidth &&
                      sc->objects[o]->Y - sc->cameraY[app->CurrentViewport] < app->gameHeight) && noException) continue;*/

                if (X2 >= sc->objects[o]->X - sc->objects[o]->w / 2.f &&
                    Y2 >= sc->objects[o]->Y - sc->objects[o]->h / 2.f &&
                    X2 < sc->objects[o]->X + sc->objects[o]->w / 2.f &&
                    Y2 < sc->objects[o]->Y + sc->objects[o]->h / 2.f && sc->objects[o]->active && noException) {
                    if (sc->objects[o]->data1 == 0x01) {
                        if ((Action == ActionType::Jumping && Gravity > 0 && !Ground) || Action == ActionType::Rolling || sc->objects[o]->data2 == 0x0A)
                            continue;
                        else {
                            return bool { true, -1, false, 0, 0, 0, 0, scrWrapAngle(AngleMode * 90), o };
                        }
                    }
                    else if (sc->objects[o]->solid) {
                        if ((sc->objects[o]->data1 == 0x0F ||
                             sc->objects[o]->data1 == 0x51 ||
                             sc->objects[o]->data1 == 0x11 ||
                             sc->objects[o]->data1 == 0x43 ||
                             sc->objects[o]->data1 == 0x51 ||
                             sc->objects[o]->data1 == 0x6C ||
                             sc->objects[o]->data1 == 0x71 ||
                             sc->objects[o]->data1 == 0xAF ||
                             sc->objects[o]->data1 == 0xB0 ||
                             sc->objects[o]->data1 == 0xB3) && Ground)
                            sc->objects[o]->doThing();
                        standSpdX = sc->objects[o]->standSpdX;
                        //standSpdY = sc->objects[o]->standSpdY;
                        return bool { true, -1, false, (int)sc->objects[o]->Speed, 0, 0, 0, scrWrapAngle(AngleMode * 90), o };
                    }
                    else if (sc->objects[o]->solidTop && Gravity >= 0 && AngleMode == 0 && Y + 12 <= sc->objects[o]->Y + sc->objects[o]->h / 2.f) {
                        if ((sc->objects[o]->data1 == 0x0F ||
                             sc->objects[o]->data1 == 0x51 ||
                             sc->objects[o]->data1 == 0x11 ||
                             sc->objects[o]->data1 == 0x43 ||
                             sc->objects[o]->data1 == 0x51 ||
                             sc->objects[o]->data1 == 0x6C ||
                             sc->objects[o]->data1 == 0x71 ||
                             sc->objects[o]->data1 == 0xAF ||
                             sc->objects[o]->data1 == 0xB0 ||
                             sc->objects[o]->data1 == 0xB3) && Ground)
                            sc->objects[o]->doThing();
                        standSpdX = sc->objects[o]->standSpdX;
                        //standSpdY = sc->objects[o]->standSpdY;
                        return bool { true, -1, true, 0, 0, 0, 0, scrWrapAngle(AngleMode * 90), o };
                    }
                    else
                        continue;
                }
            }
        }
        #endif

        int ang = 0;
        if (angleOut == NULL)
            angleOut = &ang;
        if (CollisionAt != NULL) {
            if (CollisionAt(X2, Y2, angleOut)) {
                if (*angleOut == 0)
                    *angleOut = AngleMode * 90;
                return true;
            }
        }
        else {
            if (Scene->CollisionAt(X2, Y2, angleOut)) {
                if (*angleOut == 0)
                    *angleOut = AngleMode * 90;
                return true;
            }
        }

        X2 += this->Cos[(int)wrapAngle(toDegrees(angle))];
        Y2 -= this->Sin[(int)wrapAngle(toDegrees(angle))];

        //if (loop)
            //Y2 = fmod((Y2 + sc->levelH * 128), (sc->levelH * 128));
    }
    return false;
}

int  IPlayer::CheckAngle() {
    if (TerrainAngle >= 0) {
        return TerrainAngle;
    }
    return Angle;
}
void IPlayer::CheckGroundLevel() {
    if (Action == ActionType::ClimbRise) return;

    int InitAngle = wrapAngle(AngleMode * 90);

    float LeftX2   = (int)(X) - (9 * this->Cos[InitAngle]);
    float LeftY2   = (int)(Y) + (9 * this->Sin[InitAngle]);
    float LeftX    = (int)(X) + (20 * this->Sin[InitAngle]);
    float LeftY    = (int)(Y) + (20 * this->Cos[InitAngle]);
    int   LeftAngle = -1;
    //float LeftX2OG = LeftX2;
    //float LeftY2OG = LeftY2;

    float RightX2  = (int)(X) + (9 * this->Cos[InitAngle]);
    float RightY2  = (int)(Y) - (9 * this->Sin[InitAngle]);
    float RightX   = (int)(X) + (20 * this->Sin[InitAngle]);
    float RightY   = (int)(Y) + (20 * this->Cos[InitAngle]);
    int   RightAngle = -1;
    //float RightX2OG = RightX2;
    //float RightY2OG = RightY2;

    float MiddleX2 = (int)(X);
    float MiddleY2 = (int)(Y);
    float MiddleX  = (int)(X) + (20 * this->Sin[InitAngle]);
    float MiddleY  = (int)(Y) + (20 * this->Cos[InitAngle]);
    int   MiddleAngle = -1;
    //float MiddleX2OG = MiddleX2;
    //float MiddleY2OG = MiddleY2;

    int Add = 0;
    if (AngleMode != 0)
        Add = 0;

    LastObject = NULL;

    //if (AngleMode == 0)
    CheckJumpThrough = true;

    bool TerrainLeft = false;
    for (int i = 0; i < GroundSensorHeight + Add; i++) {
        TerrainLeft = CollisionCheckLine((int)LeftX2, (int)LeftY2, (int)LeftX2, (int)LeftY2, &LeftAngle);
        if (TerrainLeft) {
            LeftX = LeftX2;
            LeftY = LeftY2;
            break;
        }
        else {
            LeftX2 += (int)this->Sin[InitAngle];
            LeftY2 += (int)this->Cos[InitAngle];
        }
    }

    bool TerrainRight = false;
    for (int i = 0; i < GroundSensorHeight + Add; i++) {
        TerrainRight = CollisionCheckLine((int)RightX2, (int)RightY2, (int)RightX2, (int)RightY2, &RightAngle);
        if (TerrainRight) {
            RightX = RightX2;
            RightY = RightY2;
            break;
        }
        else {
            RightX2 += (int)this->Sin[InitAngle];
            RightY2 += (int)this->Cos[InitAngle];
        }
    }

    bool TerrainMiddle = false;
    for (int i = 0; i < GroundSensorHeight; i++) {
        TerrainMiddle = CollisionCheckLine((int)MiddleX2, (int)MiddleY2, (int)MiddleX2, (int)MiddleY2, &MiddleAngle);
        if (TerrainMiddle) {
            bool TerrainMiddle2 = CollisionCheckLine(
                (int)MiddleX2 - (int)this->Sin[InitAngle],
                (int)MiddleY2 - (int)this->Cos[InitAngle],
                (int)MiddleX2 - (int)this->Sin[InitAngle],
                (int)MiddleY2 - (int)this->Cos[InitAngle], &MiddleAngle);
            if (TerrainMiddle2) {
                MiddleX2 = (int)X + 20 * (int)this->Sin[InitAngle];
                MiddleY2 = (int)Y + 20 * (int)this->Cos[InitAngle];
                break;
            }
        }
        if (TerrainMiddle) {
            MiddleX = MiddleX2;
            MiddleY = MiddleY2;
            break;
        }
        else{
            MiddleX2 += (int)this->Sin[InitAngle];
            MiddleY2 += (int)this->Cos[InitAngle];
        }
    }

    //if (AngleMode == 0)
    CheckJumpThrough = false;

    if (AngleMode == 0) {
        if ((false) && TerrainMiddle && (MiddleY < LeftY && MiddleY < RightY)) {
            TerrainAngle = MiddleAngle;
        }
        else if (RightY < LeftY && TerrainRight/* || (TerrainLeft.Active && X > TerrainLeft.bbox_right)) &&(X >= TerrainRight.bbox_left)*/) {
            TerrainAngle = RightAngle;
        }
        else if (LeftY < RightY && TerrainLeft /* || (TerrainRight.Active && X < TerrainRight.bbox_left)) && X <= TerrainLeft.bbox_right*/) {
            TerrainAngle = LeftAngle;
        }
        else {
            if (TerrainMiddle)
                TerrainAngle = MiddleAngle;
            else if (TerrainRight)
                TerrainAngle = RightAngle;
            else if (TerrainLeft)
                TerrainAngle = LeftAngle;
        }

        if (TerrainLeft && TerrainRight && TerrainMiddle && abs(AngleDifference(MiddleAngle, Angle)) < 60) {
            Y = fmin(LeftY, fmin(RightY, MiddleY)) - 20 /* H / 2 */;
            TerrainAngle = MiddleAngle;

            if (LastObject != NULL) {
                X += LastObject->Speed;
            }
        }
        else if (!TerrainLeft && (TerrainMiddle || abs((RightY - 20) - (int)Y) <= 0 || TerrainRight) && abs(AngleDifference(RightAngle, Angle)) < 60) {
            Y = RightY - 20 /* H / 2 */;
            TerrainAngle = RightAngle;

            if (LastObject != NULL) {
                X += LastObject->Speed;
            }
        }
        else if (!TerrainRight && (TerrainMiddle || abs((LeftY - 20) - (int)Y) <= 0 || TerrainLeft) && abs(AngleDifference(LeftAngle, Angle)) < 60) {
            Y = LeftY - 20 /* H / 2 */;
            TerrainAngle = LeftAngle;

            if (LastObject != NULL) {
                X += LastObject->Speed;
            }
        }
    }
    else if (AngleMode == 1) {
        if (/* DISABLES CODE */ (false) && TerrainMiddle && (MiddleX == LeftX && MiddleX == RightX)) {
            TerrainAngle = MiddleAngle;
        }
        else if (RightX < LeftX/* ||(TerrainLeft.Active && Y < TerrainLeft.bbox_top))&& Y <= TerrainRight.bbox_bottom*/) {
            TerrainAngle = RightAngle;
        }
        else if (LeftX < RightX/* ||(TerrainRight.Active && Y > TerrainRight.bbox_bottom)) && (Y >= TerrainLeft.bbox_top)*/) {
            TerrainAngle = LeftAngle;
        }
        else {
            if (TerrainMiddle)
                TerrainAngle = MiddleAngle;
            else if (TerrainRight)
                TerrainAngle = RightAngle;
            else if (TerrainLeft)
                TerrainAngle = LeftAngle;
        }

        if (TerrainRight && TerrainLeft && TerrainMiddle) {
            X = fmin(LeftX, fmin(RightX, MiddleX)) - 20 /* H / 2 */;
            TerrainAngle = MiddleAngle;
        }
        else if (!TerrainLeft && (TerrainMiddle || abs((RightX - 20) - (int)X) <= 0 || TerrainRight)) {
            X = RightX - 20 /* H / 2 */;
            TerrainAngle = RightAngle;
        }
        else if (!TerrainRight && (TerrainMiddle || abs((LeftX - 20) - (int)X) <= 0 || TerrainLeft)) {
            X = LeftX - 20 /* H / 2 */;
            TerrainAngle = LeftAngle;
        }

    }
    else if (AngleMode == 2) {
        if ((false) && TerrainMiddle && (MiddleY > LeftY && MiddleY > RightY)) {
            TerrainAngle = MiddleAngle;
        }
        else if (RightY > LeftY) { //TerrainRight.Active && (RightY > LeftY ||(TerrainLeft.Active && X < TerrainLeft.bbox_left))&& X <= TerrainRight.bbox_right) {
            TerrainAngle = RightAngle;
        }
        else if (LeftY > RightY) { //TerrainLeft.Active && (LeftY > RightY ||(TerrainRight.Active && X > TerrainRight.bbox_right)) &&  X >= TerrainLeft.bbox_left) {
            TerrainAngle = LeftAngle;
        }
        else {
            if (TerrainMiddle)
                TerrainAngle = MiddleAngle;
            else if (TerrainRight)
                TerrainAngle = RightAngle;
            else if (TerrainLeft)
                TerrainAngle = LeftAngle;
        }
        if (TerrainRight && TerrainLeft && TerrainMiddle && abs(AngleDifference(MiddleAngle, Angle)) < 30) {
            Y = fmax(LeftY, fmax(RightY, MiddleY)) + 20 /* H / 2 */;
            TerrainAngle = MiddleAngle;
        }
        else if (!TerrainLeft && (TerrainMiddle || abs((RightY + 20) - (int)Y) <= 0) && abs(AngleDifference(RightAngle, Angle)) < 30) {
            Y = RightY + 20 /* H / 2 */;
            TerrainAngle = RightAngle;
        }
        else if (!TerrainRight && (TerrainMiddle || abs((LeftY + 20) - (int)Y) <= 0) && abs(AngleDifference(LeftAngle, Angle)) < 30) {
            Y = LeftY + 20 /* H / 2 */;
            TerrainAngle = LeftAngle;
        }
    }
    else if (AngleMode == 3) {
        if ((false) && TerrainMiddle && (MiddleX == LeftX && MiddleX == RightX)) {
            TerrainAngle = MiddleAngle;
        }
        else if (RightX > LeftX) { //TerrainRight.Active && (RightX > LeftX ||(TerrainLeft.Active && Y > TerrainLeft.bbox_bottom))&& Y >= TerrainRight.bbox_top) {
            TerrainAngle = RightAngle;
        }
        else if (LeftX > RightX) { //TerrainLeft.Active && (LeftX > RightX ||(TerrainRight.Active && Y < TerrainRight.bbox_top)) && Y <= TerrainLeft.bbox_bottom) {
            TerrainAngle = LeftAngle;
        }
        else {
            if (TerrainMiddle)
                TerrainAngle = MiddleAngle;
            else if (TerrainRight)
                TerrainAngle = RightAngle;
            else if (TerrainLeft)
                TerrainAngle = LeftAngle;
        }
        if (TerrainRight && TerrainLeft && TerrainMiddle) {
            X = fmax(LeftX, fmax(RightX, MiddleX)) + 20 /* H / 2 */;
            TerrainAngle = MiddleAngle;
        }
        else if (!TerrainLeft && (TerrainMiddle || abs((RightX + 20) - (int)X) <= 0 || TerrainRight)) {
            X = RightX + 20 /* H / 2 */;
            TerrainAngle = RightAngle;
        }
        else if (!TerrainRight && (TerrainMiddle || abs((LeftX + 20) - (int)X) <= 0 || TerrainLeft)) {
            X = LeftX + 20 /* H / 2 */;
            TerrainAngle = LeftAngle;
        }
    }
}

bool IPlayer::PushPlayerX_Id(int obj) {
    if (Action == ActionType::ClimbRise) return false;

    int InitAngle = wrapAngle(Angle);

    int hei = 8;

    float X_s = X + hei * round(this->Sin[InitAngle]);
    float Y_s = Y + hei * round(this->Cos[InitAngle]);

    int len = W / 2 - 1;

    float X2 = X_s + len * round(this->Cos[InitAngle]);
    float Y2 = Y_s - len * round(this->Sin[InitAngle]);

    bool Object = false;
    int outAngle = 0;

    bool Collided = false;

    for (int i = 0; i < 12 && Ground; i++) {
        Object = CollisionCheckLine(X_s, Y_s, X2, Y2, &outAngle);
        if (Object && Speed >= 0) {
            X -= round(this->Cos[InitAngle]);
            Y += round(this->Sin[InitAngle]);

            Collided = true;

            // recalculate X Y
            X_s = X + hei * round(this->Sin[InitAngle]);
            Y_s = Y + hei * round(this->Cos[InitAngle]);
            X2 = X_s + len * round(this->Cos[InitAngle]);
            Y2 = Y_s - len * round(this->Sin[InitAngle]);
        }
        else
            break;
    }

    len = W / 2;

    X_s = X + hei * (int)this->Sin[InitAngle];
    Y_s = Y + hei * (int)this->Cos[InitAngle];

    X2 = X_s - len * round(this->Cos[InitAngle]);
    Y2 = Y_s + len * round(this->Sin[InitAngle]);

    for (int i = 0; i < 12 && Ground; i++) {
        Object = CollisionCheckLine(X_s, Y_s, X2, Y2, &outAngle);
        if (Object && Speed <= 0) {
            X += round(this->Cos[InitAngle]);
            Y -= round(this->Sin[InitAngle]);

            Collided = true;

            X_s = X + hei * round(this->Sin[InitAngle]);
            Y_s = Y + hei * round(this->Cos[InitAngle]);
            X2 = X_s - len * round(this->Cos[InitAngle]);
            Y2 = Y_s + len * round(this->Sin[InitAngle]);
        }
        else
            break;
    }

    if (!Ground) {
        hei = -3;

        len = 11;

        X_s = (int)X + hei * (int)this->Sin[InitAngle];
        Y_s = (int)Y + hei * (int)this->Cos[InitAngle];

        X2 = X_s + len * (int)this->Cos[InitAngle];
        Y2 = Y_s - len * (int)this->Sin[InitAngle];

        bool Object = false;

        for (int i = 0; i < 12; i++) {
            Object = CollisionCheckLine(X_s, Y_s, X2, Y2, &outAngle);
            if (Object && Speed >= 0) {
                X -= this->Cos[InitAngle];
                Y += this->Sin[InitAngle];

                Collided = true;

                X_s = (int)X + hei * (int)this->Sin[InitAngle];
                Y_s = (int)Y + hei * (int)this->Cos[InitAngle];
                X2 = X_s + len * this->Cos[InitAngle];
                Y2 = Y_s - len * this->Sin[InitAngle];
            }
            else
                break;
        }

        X_s = (int)X + hei * (int)this->Sin[InitAngle];
        Y_s = (int)Y + hei * (int)this->Cos[InitAngle];
        X2 = X_s - len * (int)this->Cos[InitAngle];
        Y2 = Y_s + len * (int)this->Sin[InitAngle];

        for (int i = 0; i < 12; i++) {
            Object = CollisionCheckLine(X_s, Y_s, X2, Y2, &outAngle);
            if (Object && Speed <= 0) {
                X += this->Cos[InitAngle];
                Y -= this->Sin[InitAngle];

                Collided = true;

                X_s = (int)X + hei * (int)this->Sin[InitAngle];
                Y_s = (int)Y + hei * (int)this->Cos[InitAngle];
                X2 = X_s - len * this->Cos[InitAngle];
                Y2 = Y_s + len * this->Sin[InitAngle];
            }
            else
                break;
        }
    }

    return Collided;
}
bool IPlayer::PushPlayerX() {
    return PushPlayerX_Id(-1);
}
void IPlayer::PushPlayerY() {
    if (Action == ActionType::ClimbRise) return;

    int InitAngle = wrapAngle(AngleMode * 90);

    int pushOutNess = 128;
    for (int i = 0; i < pushOutNess; i++) {
        if (CollisionASensor(0, -16) && !CollisionCSensor(0, 0)) {
            X -= (int)this->Sin[InitAngle];
            Y -= (int)this->Cos[InitAngle];
        }
        else
            break;
    }
    for (int i = 0; i < pushOutNess; i++) {
        if (CollisionBSensor(0, -16) && !CollisionDSensor(0, 0)) {
            X -= (int)this->Sin[InitAngle];
            Y -= (int)this->Cos[InitAngle];
        }
        else
            break;
    }
}
void IPlayer::PushPlayerYLand() {
    if (Action == ActionType::ClimbRise) return;

    if (Ground && Landed == false)
        return;

    int InitAngle = wrapAngle(AngleMode * 90);

    for (int i = 0; i < 160; i++) {
        if (CollisionASensor(0, -17)/* && CollisionCSensor(0, 0) == false*/) {
            X -= this->Sin[InitAngle];
            Y -= this->Cos[InitAngle];
        }
        else
            break;
    }
    for (int i = 0; i < 160; i++) {
        if (CollisionBSensor(0, -17)/* && CollisionDSensor(0, 0) == false*/) {
            X -= this->Sin[InitAngle];
            Y -= this->Cos[InitAngle];
        }
        else
            break;
    }
}
void IPlayer::PushPlayerYDown() {
    if (Action == ActionType::ClimbRise) return;

    for (int i = 0; i < 40; i++) {
        bool Object = CollisionCheckLine(X - 9, Y - 9, X - 9, Y - 9, NULL);
        if (Object) {
            //X -= dsin(InitAngle);
            Gravity = 0;
            Y += 1;
        }
        Object = CollisionCheckLine(X + 9, Y - 9, X + 9, Y - 9, NULL);
        if (Object) {
            //X -= dsin(InitAngle);
            Gravity = 0;
            Y += 1;
        }
        else {
            return;
        }
    }
}

void IPlayer::WallCollision() {
    if (Action == ActionType::ClimbRise) return;

    bool Collide;
    float X1, Y1, X2, Y2;
    int outAngle = 0;
    int InitAngle = wrapAngle(AngleMode * 90);

    int len = W / 2 + 1;

    int hei = 8;

    X1 = X + hei * this->Sin[InitAngle];
    Y1 = Y + hei * this->Cos[InitAngle];
    X2 = X1 + len * this->Cos[InitAngle];
    Y2 = Y1 - len * this->Sin[InitAngle];
    Collide = CollisionCheckLine(X1, Y1, (int)X2, Y2, &outAngle);
    if (Collide && Speed >= 0) {
        PushPlayerX_Id(Collide);
        Speed = 0;
    }

    X1 = X + hei * this->Sin[InitAngle];
    Y1 = Y + hei * this->Cos[InitAngle];
    X2 = X1 - len * this->Cos[InitAngle];
    Y2 = Y1 + len * this->Sin[InitAngle];
    Collide = CollisionCheckLine(X1, Y1, X2, Y2, &outAngle);
    if (Collide && Speed <= 0) {
        PushPlayerX_Id(Collide);
        Speed = 0;
    }


    // Check forehead if not rolling
    if (Action != ActionType::Rolling && AngleMode == 0) {
        hei = -H / 2 + 3;
        X1 = X + hei * this->Sin[InitAngle];
        Y1 = Y + hei * this->Cos[InitAngle];
        X2 = X1 + len * this->Cos[InitAngle];
        Y2 = Y1 - len * this->Sin[InitAngle];
        Collide = CollisionCheckLine(X1, Y1, (int)X2, Y2, &outAngle);
        if (Collide && Speed >= 0) {
            PushPlayerX_Id(Collide);
            Speed = 0;
        }

        X1 = X + hei * this->Sin[InitAngle];
        Y1 = Y + hei * this->Cos[InitAngle];
        X2 = X1 - len * this->Cos[InitAngle];
        Y2 = Y1 + len * this->Sin[InitAngle];
        Collide = CollisionCheckLine(X1, Y1, (int)X2, Y2, &outAngle);
        if (Collide && Speed <= 0) {
            PushPlayerX_Id(Collide);
            Speed = 0;
        }
    }


    if (!Ground) {
        X1 = (int)X - 7 * this->Sin[InitAngle];
        Y1 = (int)Y - 7 * this->Cos[InitAngle];

        X2 = X1 + len * this->Cos[InitAngle];
        Y2 = Y1 - len * this->Sin[InitAngle];
        Collide = CollisionCheckLine(X1, Y1, X2, Y2, &outAngle);
        if (Collide && Speed >= 0) {
            PushPlayerX_Id(Collide);
            Speed = 0;
        }

        X1 = (int)X - 7 * this->Sin[InitAngle];
        Y1 = (int)Y - 7 * this->Cos[InitAngle];

        X2 = X1 - len * this->Cos[InitAngle];
        Y2 = Y1 + len * this->Sin[InitAngle];
        Collide = CollisionCheckLine(X1, Y1, X2, Y2, &outAngle);
        if (Collide && Speed <= 0) {
            PushPlayerX_Id(Collide);
            Speed = 0;
            //app->print(0, "Speeeeeed %f", Speed);
        }
    }
}
void IPlayer::SpeedMovement() {
    if (Action == ActionType::ClimbRise) return;

    float SpeedSplit = 1;
    float SpeedValue = 0;

    //PushPlayerX_Id(-1);
    //PushPlayerY();

    Speed = clamp(Speed, -128.0f, 128.0f);
    SpeedSplitAmount = 8;

    SpeedSplit = std::floor(fmax(abs((Speed * SpeedMultiplier) / SpeedSplitAmount), 1.0f));

    if (SpeedSplit > 0)
        SpeedValue = (Speed * SpeedMultiplier) / SpeedSplit;
    else
        SpeedValue = 0;

    float SpeedMax = abs(Speed) * SpeedMultiplier;

	for (int i = 0; i < std::ceil(SpeedSplit); i++) {
		if (Speed == 0)
            SpeedValue = 0;

        SpeedValue = fmin(SpeedMax, abs(SpeedValue)) * signum(SpeedValue);
        SpeedMax -= SpeedValue;

        //if (HandleBreakableTerrain())
        //    break;

        int TempAngle = Angle;

        X += SpeedValue * this->Cos[Angle];
        Y -= SpeedValue * this->Sin[Angle];

        HandlePathSwitchers();
        HandleMonitors();
        if (HandleSprings()) {
            X -= SpeedValue * this->Cos[TempAngle];
            Y += SpeedValue * this->Sin[TempAngle];
            break;
        }

        if (CollisionPushMode == 0) {
            PushPlayerX_Id(-1);
            PushPlayerY();
        }
        else {
            //PushPlayerSafe();
        }

        if (Ground) {
            AngleLast2 = Angle;

            CheckGroundLevel();
            PushPlayerY();

            AngleLast = Angle;

            Angle = CheckAngle();

            // >  315 normally
            // >= 312 AIZ

            if ((Angle >= 312 || Angle < 45) && AngleMode != 0 && abs(AngleDifference(AngleLast2, Angle)) < 40) {
                AngleModeLast = AngleMode;
                AngleMode = 0;

                if (!Angle360Detection &&
                    AngleModeLast != 0 &&
                    (!CollisionASensor(-1, 0) || !CollisionBSensor(-1, 0)))
                    AngleMode = AngleModeLast;
                else if (!AngleBothSensors ||
                    abs(AngleDifference(AngleMode * 90, Angle)) > 10 ||
                    (CollisionASensor360(-1, 0) && CollisionBSensor360(-1, 0)))
                    Angle = CheckAngle();

                PushPlayerY();
            }
            else if ((Angle > 45 && Angle < 135) && AngleMode != 1 && abs(AngleDifference(AngleLast2, Angle)) < 40) {
                AngleModeLast = AngleMode;
                AngleMode = 1;

                /*if (!Angle360Detection && (!CollisionASensor(-1, 0)) && AngleModeLast != 1) {
                    AngleMode = AngleModeLast;
                    Angle = AngleLast;
                }
                else */if (Speed < 0 && AngleMode == 0 && AngleModeSwitchMode == 1) {
                    X -= 12;
                    X = std::floor(X);
                }
                else if ((Speed > 0 || AngleMode != 0 || AngleModeSwitchMode == 1 || (AngleLast < 45 && AngleLast > 0))) {
                    X += 1;
                    AngleMode = 1;
                    if (!AngleBothSensors || abs(AngleDifference(AngleMode * 90, Angle)) > 10 ||
                    (CollisionASensor360(-1, 0) && CollisionBSensor360(-1, 0)))
                        Angle = CheckAngle();
                }
                else {
                    AngleMode = AngleModeLast;
                    Angle = AngleLast;
                }

                PushPlayerY();
            }
            else if ((Angle > 135 && Angle < 225) && AngleMode != 2 && abs(AngleDifference(AngleLast2, Angle)) < 40) {
                AngleModeLast = AngleMode;
                AngleMode = 2;

                /*if (!Angle360Detection && AngleModeLast != 2 &&
                    (!CollisionASensor(-1, 0) || !CollisionBSensor(-1, 0))) {
                    AngleMode = AngleModeLast;

                    Y += 1;
                }
                else */if (!AngleBothSensors ||
                    abs(AngleDifference(AngleMode * 90, Angle)) > 10 ||
                    (CollisionASensor360(-1, 0) && CollisionBSensor360(-1, 0))) {
                    Angle = CheckAngle();
                }

                PushPlayerY();
            }
            else if ((Angle > 225 && Angle < 315) && AngleMode != 3 && abs(AngleDifference(AngleLast2, Angle)) < 40) {
                AngleModeLast = AngleMode;
                AngleMode = 3;

                /*if (!Angle360Detection && AngleModeLast != 3 &&
                    (!CollisionASensor(-1, 0) || !CollisionBSensor(-1, 0)))
                    AngleMode = AngleModeLast;
                else */if (Speed > 0 && AngleMode == 0 && AngleModeSwitchMode == 0) {
                    X += 12;
                    X = std::ceil(X);
                    Y += 12;
                }
                else if (Speed < 0 || AngleMode != 0 || AngleModeSwitchMode == 1 || ((AngleLast > 315 && AngleLast < 360))) {
                    AngleMode = 3;
                    if (!AngleBothSensors ||
                        abs(AngleDifference(AngleMode * 90, Angle)) > 10 ||
                        (CollisionASensor360(-1, 0) && CollisionBSensor360(-1, 0)))
                        Angle = CheckAngle();
                }
                else
                    AngleMode = AngleModeLast;

                PushPlayerY();
            }
        }

        WallCollision();

        int GoAroundCircleAddition = 0;
        if (ForceRoll)
            GoAroundCircleAddition = 16;
        if (Ground && !ForceRoll && (!CollisionASensor(-1, GoAroundCircleAddition) && !CollisionBSensor(-1, GoAroundCircleAddition))) {
            //if (TerrainAngle >= 0 && (AngleMode == 1 || AngleMode == 3))
            //    Angle = wrapAngle(TerrainAngle);

            //app->print(0, "No ground detected, falling off. Angle: %d, AngleMode: %d", (int)Angle, AngleMode);
            Gravity = -Speed * this->Sin[Angle];
            Speed = Speed * this->Cos[Angle];
            if (Action == ActionType::Rolling) {
                X += (5 * this->Sin[AngleMode * 90]);
                Y += (5 * this->Cos[AngleMode * 90]);
            }
            Angle = 0;
            AngleMode = 0;
            Ground = false;
       }
    }

    if ((Angle >= 45 && Angle <= 315) && abs(Speed) < 2.5f && !ForceRoll) {
        if (Angle < 90 || Angle > 270) {
            InputAlarm  = 30;
        }
        else {
            Gravity = -this->Sin[Angle] * Speed;
            Speed = this->Cos[Angle] * Speed;
            Ground = false;
            if (Action == ActionType::Rolling) {
                X += (5 * this->Sin[Angle]);
                Y += (5 * this->Cos[Angle]);
                CameraX = -5 * this->Sin[Angle];
                //CameraY = 0;
            }

            SlowRotationReset = true;
            DisplayAngle = toRadians(Angle);
            StoredRotation = DisplayAngle;

            Angle = 0;
            AngleMode = 0;
            InputAlarm = 30;
        }
    }
}
void IPlayer::GravityMovement() {

    //Gravity = round(Gravity * 16) / 16;
    //Gravity += standSpdY;
    //standSpdY = 0;

    float GravitySplit = 1.0f;
    float GravityValue = 0.0f;
    //bool Object;
    //bool Object2;
    //bool Object3;
    if (Ground)
        return;

    float split = 2.0f;
    //if (app->platform == Application::P_Vita) {
        //split = 12.0f;
    //}

    Gravity = clamp(Gravity, -GravityMaxFull, GravityMaxFull);
    GravitySplit = std::floor(fmax(abs((Gravity * SpeedMultiplier)) / split, 1.0f));

    if (GravitySplit > 0)
        GravityValue = (Gravity * SpeedMultiplier) / (GravitySplit);
    else
        GravityValue = 0;
    float GravityMax = Gravity * SpeedMultiplier;

    int Length = 0;

    for (int i = 0; i < std::ceil(GravitySplit); i++) {
        if (GravityMax == 0 && Gravity != 0)
            break;

        GravityValue = fmin(abs(GravityMax), abs(GravityValue)) * signum(GravityValue);
        GravityMax = fmax(abs(GravityMax) - abs(GravityValue), 0.0f) * signum(GravityValue);

        Y += GravityValue;
        HandleMonitors();
        HandleSprings();

        if (Action == ActionType::InStreamPipe) continue;

        if (Action != ActionType::InStreamPipe) {
            //HandleBreakableTerrain();
            //WallCollision();

            PushPlayerX_Id(-1);
            PushPlayerYDown();
        }


        if (Action == ActionType::Jumping || Action == ActionType::Rolling)
            Length = 16;
        else
            Length = 20;

        bool Object = CollisionCheckLine(X - 9, Y - Length, X - 9, Y, NULL);
        bool Object2 = false;
        bool Object3 = false;
        if (!Object)
            Object2 = CollisionCheckLine(X + 9, Y - Length, X + 9, Y, NULL);
        if (!Object2)
            Object3 = CollisionCheckLine(X, Y - Length, X, Y, NULL);

        if (Gravity >= 0 &&
            (CollisionASensor(-1, -16) || CollisionBSensor(-1, -16)) &&
            !Object && !Object2 && !Object3) {
            if (ShieldAction && Shield == ShieldType::Bubble) {
                Gravity = -7.5f;
                Ground = false;
                ShieldAction = false;
                ShieldUsable = true;
                //Vibrate(0, 0.5, 250);
                PushPlayerY();
                return;
            }
            else {
                //ResetTrail();
                PushPlayerYLand();
                Ground = true;
                EnemyCombo = 0;
                Landed = true;
                Angle = 0;
                ShieldAction = false;
                AngleMode = 0;
                CheckGroundLevel();
                PushPlayerX();

                ShieldUsable = true;

                Angle = CheckAngle();
                if (!ForceRoll) {
                    if ((Angle > 315 || Angle < 45))
                        AngleMode = 0;
                    else if ((Angle > 45 && Angle < 135))
                        AngleMode = 1;
                    else if ((Angle > 135 && Angle < 225))
                        AngleMode = 2;
                    else if ((Angle > 225 && Angle < 315))
                        AngleMode = 3;
                }

                if (abs(Speed) <= abs(Gravity) && Angle >= 22.5f && Angle <= 337.5f/* && TerrainId.object_index != objObjectSeesaw*/) {
                    Speed = -Gravity * signum(this->Sin[Angle]);
                    if (Angle < 45 || Angle > 315)
                        Speed *= 0.5f;
                    /*else if (TerrainId.object_index == objObjectSeesaw)
                        Angle = 0;*/
                }
                if (ObjectControlled == 0 && abs(Speed) > 0.5f && InputDown && Ground &&
                    (/*!RollMoveLock || */(!InputLeft && !InputRight)) &&
                    (Action == ActionType::Normal || Action == ActionType::Jumping)) {
                    //ResetTrail();
                    //audio_play_sound(sndPlayerRoll, 1, false);
                    Action = ActionType::Rolling;
                }
                if (Action == ActionType::Hurt) {
                    Invincibility = InvincibilityType::Temporary;
                    InvincibilityTimer = 120;
                    Action = ActionType::Normal;
                    Speed = 0;
                }
                if (Action == ActionType::Twirl) {
                    Action = ActionType::Normal;
                }
                if (Action == ActionType::Peril) {
                    Action = ActionType::Normal;
                }

                Gravity = 0;
                GravityMax = 0;

                return;
            }
        }

        if ((Object || Object2 || Object3) && !ForceRoll) {
            float Y_s = Y;
            AngleMode = 2;

            if (Gravity < -0.5f) {
                Angle = 180;
                Ground = true;
                Landed = true;
                CheckGroundLevel();
                PushPlayerX_Id(-1);
                PushPlayerY();
                Angle = CheckAngle();

                if ((
                    (Angle > 90 && Angle <= 135) ||
                    (Angle >= 225 && Angle < 270)) &&
                    Gravity < -1.5f &&
                    (Action == ActionType::Normal ||
                    Action == ActionType::Jumping ||
                    Action == ActionType::Spring ||
                    Action == ActionType::Fan ||
                    Action == ActionType::Rolling)) {
                    //ResetTrail();
                    if ((Angle > 45 && Angle < 135))
                        AngleMode = 1;
                    else if ((Angle > 135 && Angle < 225))
                        AngleMode = 2;
                    else if ((Angle > 225 && Angle < 315))
                        AngleMode = 3;

                    Ground = true;
                    Speed = -Gravity * signum(this->Sin[Angle]);

                    Gravity = 0;
                    EnemyCombo = 0;

                    GravityMax = 0;

                    if (InputDown && (Action == ActionType::Normal || Action == ActionType::Jumping)) {
                        //ResetTrail();
                        //Scene->aud_Roll->Play(1); // $AudioPlay(aud_Roll, 1);
                        Action = ActionType::Rolling;
                    }
                    return;
                }
                else {
                    if (Gravity < 0)
                        Gravity = 0;

                    TerrainAngle = -1;
                    Ground = false;
                    Angle = 0;
                    Landed = false;
                    AngleMode = 0;

                    PushPlayerX_Id(-1);

                    Y = Y_s;
                    PushPlayerYDown();

                    TerrainAngle = -1;
                    GravityMax = 0;
                    return;
                }
            }
            else {
                if (Gravity < 0)
                    Gravity = 0;

                TerrainAngle = -1;
                Ground = false;
                Angle = 0;
                Landed = false;
                AngleMode = 0;

                PushPlayerX_Id(-1);
                PushPlayerYDown();
                TerrainAngle = -1;
                GravityMax = 0;
                return;
            }
        }

        //HandleSprings();
        //HandleMonitors();
    }
}

void IPlayer::HandleAction() {
    switch (Action) {
        case ActionType::Normal:
            ActionNormal();
            break;
        case ActionType::LookUp:
            ActionLookUp();
            break;
        case ActionType::Skid:
            ActionSkid();
            break;
        case ActionType::Jumping:
            ActionJumping();
            break;
        case ActionType::Push:
            ActionPush();
            break;
        case ActionType::Rolling:
            ActionRolling();
            break;
        case ActionType::CrouchDown:
            ActionCrouchDown();
            break;
        case ActionType::Spindash:
            ActionSpindash();
            break;
        case ActionType::Spring:
        case ActionType::Fan:
            ActionSpring();
            break;
        case ActionType::Slide:
            ActionSlide();
            break;

        case ActionType::Fly:
            ActionFly();
            break;

        case ActionType::Grab:
            ActionGrab();
            break;

        case ActionType::ObjectGrab:
            //ActionObjectGrab();
            break;

        case ActionType::Glide:
            ActionGlide();
            break;
        case ActionType::GlideFall:
            ActionGlideFall();
            break;
        case ActionType::GlideFallLand:
            ActionGlideFallLand();
            break;
        case ActionType::GlideSlide:
            ActionGlideSlide();
            break;
        case ActionType::Climb:
            ActionClimb();
            break;
        case ActionType::ClimbRise:
            ActionClimbRise();
            break;

        case ActionType::InStream:
            ActionInStream();
            break;
        case ActionType::InStreamGrab:
            ActionInStreamGrab();
            break;
        case ActionType::InStreamPipe:
            ActionInStreamPipe();
            break;

        case ActionType::Respawn:
            ActionRespawn();
            break;


        default:
            ActionNormal();
            break;
    }
}

void IPlayer::ActionNormal() {
    if (InputJump && Ground) {
        Jump();
    }

    bool Sonic3RollReq = true;
    bool RollMoveLock = false;

    if (ObjectControlled > 0) return;

    // Pushing
    if (Ground &&
        Speed == 0 &&
        AngleMode == 0 &&
        (CollisionRightSensor(42069) && InputRight))
        Action = ActionType::Push;
    else if (Ground &&
        Speed == 0 &&
        AngleMode == 0 &&
        (CollisionLeftSensor(42069) && InputLeft))
        Action = ActionType::Push;
    // Skidding
    else if (Ground && AngleMode == 0 && InputAlarm <= 0 && ((Speed >= 4.5f && InputLeft) || (Speed <= -4.5f && InputRight))) {
        Action = ActionType::Skid;
        //Scene->aud_Skid->Play(0); // $AudioPlay(aud_Skid, 0);
    }
    // Turning around
    else if (Ground && InputAlarm <= 0 && ((Speed < 0 && InputRight) || (Speed > 0 && InputLeft))) {
        Speed = fmax(abs(Speed) - SkidRate, 0.0f) * signum(Speed);
    }
    // Jumping
    else if (InputJump && Ground) {
        Jump();
    }
    // Crouching
    else if (abs(Speed) <= (Sonic3RollReq ? 1.03125f : 0.53125f) && InputDown && Ground) {
        Speed = 0;
        CameraLookTimer = 0;
        Action = ActionType::CrouchDown;
    }
    // Looking up
    else if (Speed == 0 && InputUp && Ground) {
        CameraLookTimer = 0;
        Action = ActionType::LookUp;

    }
    // Rolling
    else if (abs(Speed) > (Sonic3RollReq ? 1.03125f : 0.53125f) && InputDown && Ground && (!RollMoveLock || (!InputRight && !InputLeft))) {
        //Scene->aud_Roll->Play(1); // $AudioPlay(aud_Roll, 1);
        Action = ActionType::Rolling;
    }
}
void IPlayer::ActionLookUp() {
    if (!InputUp)
        Action = ActionType::Normal;

    if (InputJump && Ground)
        Jump();
}
void IPlayer::ActionPush() {
    if (
        (Flip == 1.0f && (!InputRight || !CollisionRightSensor(42069))) ||
        (Flip == -1.0f && (!InputLeft || !CollisionLeftSensor(42069))) ||
        !Ground) {
        Action = ActionType::Normal;
        return;
    }
    else if (InputJump && Ground) {
        Jump();
        return;
    }
    else {
        /*
        for (int o = 0; o < Scene->ObjectSolidCount; o++) {
            Object* obj = (ISpring*)Scene->ObjectsSolid[o];
            if (obj != NULL) {
                if (obj->Active && obj->Pushable) {
                    if (obj->X + obj->W / 2 >= X + 14 * fmin(Flip, 0.0f) &&
                        obj->Y + obj->H / 2 >= Y + 10 &&
                        obj->X - obj->W / 2 <  X + 14 * fmax(Flip, 0.0f) &&
                        obj->Y - obj->H / 2 <  Y + 10) {
                        if (obj->OnPush(PlayerID, Flip)) {
                            X      += Flip * 0.25f;
                            obj->X = X + Flip * (obj->W / 2 + 13);
                            return;
                        }
                    }
                }
            }
        }
        //*/
    }
    if (Ground)
        Speed = 0;
}
void IPlayer::ActionRolling() {
    if (ObjectControlled > 0) return;

    if (Speed > 0)
        Speed = fmax(0.0f, Speed - (AccelRate / 2.0f));
    else if (Speed < 0)
        Speed = fmin(0.0f, Speed + (AccelRate / 2.0f));

    if (/*CharacterId != consCharacterTails && */!ForceRoll && InputAlarm <= 0) {
        if (InputLeft && Speed > 0)
           Speed = fmax(0.0f, Speed - 0.125f);
        if (InputRight && Speed < 0)
           Speed = fmin(0.0f, Speed + 0.125f);
    }
    else if (InputAlarm <= 0) {
        if (InputLeft && Speed > 0)
           Speed = fmax(0.0f, Speed - (SkidRate / 4.0f));
        if (InputRight && Speed < 0)
           Speed = fmin(0.0f, Speed + (SkidRate / 4.0f));
    }
    if (!Ground && !ForceRoll) {
        Action = ActionType::Jumping;
        JumpAnimSpeed = 1.0f / fmax((5.0f - abs(Speed)), 1.0f);
        JumpVariable = false;
    }
    if (InputJump && Ground && !ForceRoll) {
        Jump();
        JumpVariable = -1;
    }
    //HandleMonitors();
    if (Speed == 0 && Ground) {
        if (!ForceRoll)
            Action = ActionType::Normal;
        else {
            //Scene->aud_Roll->Play(1); // $AudioPlay(aud_Roll, 1);
            Speed = 4.0f;
        }
    }
    if (RollSpeedCap)
        Speed = fmin(abs(Speed), 32.0f) * signum(Speed);
}
void IPlayer::ActionSkid() {
    bool CreateParticles = false;
    if (Speed > 0 && InputLeft) {
        Speed = fmax(Speed - SkidRate, 0.0f);

        /*
        if (Scene->frameAnim % 5 == 0) {
            CreateParticles = true;
        }
        //*/
    }
    else if (Speed < 0 && InputRight) {
        Speed = fmin(Speed + SkidRate, 0.0f);

        /*
        if (Scene->frameAnim % 5 == 0) {
            CreateParticles = true;
        }
        //*/
    }
    else if (Speed != 0)
        Speed -= fmin(abs(Speed), Acceleration) * signum(Speed);

    if (CreateParticles) {
        /*
        IEnemyExplosion* obj = new IEnemyExplosion();
        obj->X = X;
        obj->Y = Y + 13;
        obj->G = G;
        obj->App = App;
        obj->Scene = Scene;
        Scene->Particles[Scene->ParticleCount] = obj;
        Scene->ParticleCount = (Scene->ParticleCount + 1) % 50;
        obj->Create();
        obj->Sprite = App->Sprites["FX (Skid Dust)"];
        obj->Frame = 0;
        obj->Speed = 4;
        Vibrate(0, 0.25, 50);
        //*/
    }

    if ((InputLeft && Speed < 0) || (InputRight && Speed > 0) || Speed == 0 || (!InputLeft && !InputRight)) {
        Action = ActionType::Normal;
    }
    else if (InputJump && Ground) {
        Jump();
    }
}
void IPlayer::ActionJumping() {
    if (!InputJumpHold && Gravity < JumpRelease && JumpVariable == 1)
        Gravity = JumpRelease;

    //HandleMonitors();
    if (Ground) {
        ShieldUsable = true;
        ShieldAction = false;
        if (DropDashRev >= 21 && InputJumpHold && Character == CharacterType::Sonic) {
            //Scene->aud_Roll->Play(1); // $AudioPlay(aud_Roll, 1);
            Action = ActionType::Rolling;

            int DropDashSpeed = 8;
            int MaxSpeed = 12;

            if (SuperForm) {
                DropDashSpeed = 12;
                MaxSpeed = 13;
            }

            Speed = Flip * DropDashSpeed + GroundSpeed / 4;
            if (CheckAngle() != 0) {
                Speed += GroundSpeed / 4;
            }
            else {
                /*
                IEnemyExplosion* obj = new IEnemyExplosion();
                obj->X = X;
                obj->Y = Y;
                obj->G = G;
                obj->App = App;
                obj->Scene = Scene;
                Scene->Particles[Scene->ParticleCount] = obj;
                Scene->ParticleCount = (Scene->ParticleCount + 1) % 50;
                obj->Create();
                obj->Sprite = SpriteDashDust;
                obj->Frame = 0;
                obj->Speed = 4;
                obj->FlipX = Speed < 0;
                Vibrate(0, 0.25, 50);
                //*/
            }
            if (abs(Speed) > MaxSpeed)
                Speed = signum(Speed) * MaxSpeed;

            if (CameraLag) {
                CameraLockTimer = 16;
            }


        }
        else {
            Action = ActionType::Normal;
        }
        DropDashRev = 0;
    }
    else if (InputJump && JumpVariable != 0 && ShieldUsable && Shield != ShieldType::Instashield && Character == CharacterType::Sonic && (!SuperForm || DropDashEnabled)) {
        ShieldAnimation = 0;
        switch (Shield) {
            case ShieldType::None:
                if (DropDashEnabled) {
                    if (JumpVariable < 0)
                        JumpVariable = 0;

                    if (DropDashRev == 0)
                        DropDashRev = 1;
                    //Scene->aud_SpinRev->Play(1); // $AudioPlay(aud_SpinRev, 1);
                }
                else if (!SuperForm) {
                    //Scene->aud[0x42]->Play(1); // $AudioPlay(aud[0x42], 1);
                    if (JumpVariable < 0)
                        JumpVariable = 0;

                    Shield = ShieldType::Instashield;
                }
                break;
            case ShieldType::Bubble:
                if (!SuperForm) {
                    ShieldAction = true;
                    Speed = 0.0f;
                    Gravity = 8.0f;
                    //Scene->aud[0x44]->Play(1); // $AudioPlay(aud[0x44], 1);
                }
                break;
            case ShieldType::Electric:
                if (!SuperForm) {
                    Gravity = -5.5f;
                    JumpVariable = 0;
                    //Vibrate(0, 0.5, 250);
                    /*
                    for (int j = 0; j < 4; j++) {
                        IEnemyExplosion* obj = new IEnemyExplosion();
                        obj->X = X;
                        obj->Y = Y - 10;
                        obj->G = G;
                        obj->App = App;
                        obj->Scene = Scene;
                        Scene->Particles[Scene->ParticleCount] = obj;
                        Scene->ParticleCount = (Scene->ParticleCount + 1) % 50;
                        obj->Create();
                        obj->Sprite = App->Sprites["Shield (Invincibility)"];
                        obj->Frame = 5;
                        obj->Speed = 4;
                        Vibrate(0, 0.25, 50);

                        int xs = (j % 2) * 4 - 2;
                        int ys = (j / 2) * 4 - 2;
                        obj->HSpeed = xs;
                        obj->Gravity = ys;
                        obj->CanFall = true;
                    }
                    //*/

                    //Scene->aud[0x45]->Play(1); // $AudioPlay(aud[0x45], 1);
                    break;
                }
            case ShieldType::Fire:
                if (!SuperForm) {
                    ShieldAction = true;
                    Speed = 8.0f * Flip;
                    Gravity = 0.0f;
                    //Vibrate(0, 0.5, 250);
                    //Scene->aud[0x43]->Play(1); // $AudioPlay(aud[0x43], 1);

                    if (CameraLag) {
                        CameraLockTimer = 16;
                    }
                }
                break;
			default:
				break;
        }
        ShieldUsable = false;
    }
    else if (InputJump && JumpVariable != 0 && Character == CharacterType::Tails && Action != ActionType::Rolling) {
        Action = ActionType::Fly;
        FlyFlag = 1;
        if (!Underwater) {
            //audio_play_sound(sndFly, 1, true);
        }
        InputJump = false;
    }
    else if (InputJump && JumpVariable != 0 && Character == CharacterType::Knuckles) {
        Action = ActionType::Glide;
        if (Gravity < 0)
            Gravity = 0;
        Speed = fmax(4.0f, abs(Speed) * 0.75f) * Flip;
        GlideTurnSpeed = 0;
    }
    else if (InputJump && InputUp && HyperForm && ShieldUsable) {
        if (InputUp) {
            Speed = 0.0f;
            Gravity = -8.0f;
        }
        else {
            Speed = 8.0f * Flip;
            Gravity = 0;
        }
        ShieldUsable = false;
        JumpVariable = 0;
        if (CameraLag) {
            CameraLockTimer = 16;
        }
        //audio_play_sound(sndPlayerSpindash, 1, false);
    }
    if ((InputJump && false && !SuperForm && !Ground /*&& sc->rings >= 50 && global.ChaosEmeralds == 127 && && CharacterId == consCharacterSonic */ && SuperEnabled /* && !sc->levelComplete */)) {
        Speed = 0;
        Gravity = 0;
        //Action      = ActionType::Transform;
        SuperForm = true;
        SuperFlight = false;
        //formingType = 1;
        //formingTimer = 4 * 10;
        Shield = ShieldType::None;
        //sc->aud[0x9F]->Play(2);
        //audio_pause_sound(global.CurrentSong);
        //audio_play_sound(sndSuperSonic, 1, true);
        //global.CurrentSong = sndSuperSonic;
    }

    if (DropDashEnabled && Character == CharacterType::Sonic && InputJumpHold && DropDashRev > 0) {
        DropDashRev++;
    }
}
void IPlayer::ActionCrouchDown() {
    if (!InputDown)
        Action = ActionType::Normal;

    if (InputJump && Spindash != SpindashType::None) {
        SpindashRev = 0;
        //SpindashFrame = global.Frame;
        if (Spindash == SpindashType::Standard) {
            //Scene->aud_SpinRev->Play(1); // $AudioPlay(aud_SpinRev, 1);
        }
        else if (Spindash == SpindashType::SCD) {
            //audio_stop_sound(sndPeelout);
            //audio_play_sound(sndPeelout, 1, false);
        }
        Action = ActionType::Spindash;
    }
    else if (InputJump && Ground)
        Jump();
}
void IPlayer::ActionSpindash() {
    if (false) { // Delay) {
        /*SpindashRev = SpindashRev;
        Flip   = global.Player[0].Flip;
        if (global.Player[0].Action != ActionSpindash) {
            Speed = (SpindashMin+SpindashRev)*Flip;
            audio_play_sound(sndPlayerSpindash, 1, false);
            scrPlayerResetTrail();
            Action = ActionRolling;
            scrPlayerHandleMonitors();
        }
        exit;*/
    }

    if (Spindash == SpindashType::Standard) {
        if (InputJump) {
            SpindashRev = fmin(SpindashRev + SpindashRevAmount, SpindashMax - 8.0f);
            //Scene->aud_SpinRev->Play(1); // $AudioPlay(aud_SpinRev, 1);
            Frame = 0;

            //Vibrate(0, 0.25, 150);
        }
        SpindashRev -= (SpindashRev / 0.125f) / 256.0f;

        /*S3Object::Terrain _ObjectHandle = collision_line_terrain(x, y + 10, x + (12 * flip), y + 10);
        if (_ObjectHandle.Active && PlayerID == 0) {
            if (sc->objects[_ObjectHandle.ObjectID] != NULL) {
                if (sc->objects[_ObjectHandle.ObjectID]->Pushable) {
                    x += flip * 0.25f;
                    sc->objects[_ObjectHandle.ObjectID]->x += flip * 0.25f;
                }
            }
        }*/

        if (!InputDown) {
            Speed = (((SpindashMin + SpindashRev)) + (3.0f * (SuperForm ? 1 : 0))) * Flip;
            //scrPlayerResetTrail();
            //Scene->aud_Roll->Play(1); // $AudioPlay(aud_Roll, 1);
            Action = ActionType::Rolling;
            SpindashRev = 0;

            if (CameraLag) {
                CameraLockTimer = 16;
            }

            //HandleMonitors();
        }
    }
    else if (Spindash == SpindashType::SCD && !InputDown) {
        /*if (Frame >= SpindashFrame + 45) {
            Speed = 12 * Flip;
            //audio_play_sound(sndPlayerSpindash, 1, false);
            //scrPlayerResetTrail();
            Action = ActionType::Rolling;
            //scrPlayerHandleMonitors();
        }
        else {
            Action = ActionType::Normal;
        }*/
    }
}
void IPlayer::ActionSpring() {
    if (Ground) {
        Action = ActionType::Normal;
        //Fan = false;
    }
    /*else if (InputJump && !Ground && UseCurlButton && !Fan && Action == ActionType::Spring) {
        Action = ActionType::Jumping;
        JumpAnimSpeed  = 1.0f / fmax((5.0f - abs(Speed)), 1.0f);
        //audio_play_sound(sndShieldInstashield, 1, false);
        JumpVariable = 0;
    }*/
    else if (/* !Fan && */Gravity > 0 && Action == ActionType::Spring) {
        Action = ActionType::Normal;
        if (SpringFlip > 0) {
            SpringFlip--;
        }
    }
}
void IPlayer::ActionSlide() {
    if (!Ground)
        Action = ActionType::Normal;
    else if (InputJump)
        Jump();

    if (signum(Speed) != 0)
        Flip = signum(Speed);
}
void IPlayer::ActionGrab() {

}
void IPlayer::ActionFly() {
    FlyTimer -= 1;
    GravityRate = 0;

    InputAlarm = 0;

    if (FlyTimer == 0 && !Underwater) {
        //audio_stop_sound(sndFly);
        //audio_play_sound(sndFlyFall, 1, true);
    }
    if (Gravity <= -1)
        FlyFlag = 1;

    if (FlyFlag > 1) {
        Gravity -= 0.125f;
        FlyFlag++;
        if (FlyFlag == 32)
            FlyFlag = 1;
    }
    else {
       if (FlyTimer > 0 && Gravity > -1 && InputJump)
           FlyFlag = 2;
       Gravity += 0.03125f;
    }

    TopSpeed = 6.f / (Underwater ? 2 : 1);

    if (Ground) {
        FlyTimer = 480;
        FlyFlag = 0;
        Action = ActionType::Normal;
    }
}
void IPlayer::ActionInStream() {
}
void IPlayer::ActionInStreamPipe() {
}
void IPlayer::ActionInStreamGrab() {
}
void IPlayer::ActionRespawn() {
}
void IPlayer::ActionGlide() {
    if (Gravity > 0.5f) {
        Gravity = fmax(0.5f, Gravity - 0.125f);
    }
    if (Gravity < 0.5f) {
        Gravity = fmin(0.5f, Gravity + 0.125f);
    }

    if (GlideTurnSpeed == 0)
        Speed += 0.015625f * Flip;

    if (Flip > 0 && InputLeftPress && GlideTurnSpeed == 0) {
        GlideTurnSpeed = fmax(abs(Speed), 4.0f);
        GlideTurnCos = 0;
        GlideTurnFlag = false;
    }
    else if (InputRightPress && GlideTurnSpeed != 0 && GlideTurnCos < 180) {
        GlideTurnCos = 360 - GlideTurnCos;
        GlideTurnFlag = false;
    }
    else if (Flip < 0 && InputRightPress && GlideTurnSpeed == 0) {
        GlideTurnSpeed = fmax(abs(Speed), 4.0f);
        GlideTurnCos = 180;
        GlideTurnFlag = false;
    }
    else if (InputLeftPress && GlideTurnSpeed != 0 && GlideTurnCos > 180) {
        GlideTurnCos = 360 - GlideTurnCos;
        GlideTurnFlag = false;
    }
    if (GlideTurnSpeed != 0) {
        GlideTurnCos = (int)(wrapAngle(GlideTurnCos + 2.8125f));
        Speed = GlideTurnSpeed * this->Cos[GlideTurnCos];

        if (GlideTurnCos == 0) {
            GlideTurnSpeed = 0;
        }
        else if (GlideTurnCos == 180) {
            GlideTurnSpeed = 0;
        }
    }
    else {
        GlideTurnFlag = false;
    }
    if (!InputJumpHold) {
        //Speed *= 0.5;
        Action = ActionType::GlideFall;
    }

    if (CollisionRightSensor(42069) && Speed > 0 && !CollisionBSensor(-1, -16)) {
        Action = ActionType::Climb;
        //audio_play_sound(sndClimb, 1, false);

        /*
        if (SuperForm)
            Scene->aud[0x49]->Play(1);
        else
            Scene->aud[0x4A]->Play(1);
        //*/

        Speed = 0;
        Gravity = 0;

        int ang = 0;
        if (!CollisionCheckLine((int)X, Y + 4, (int)X + (12 * Flip), Y + 4, &ang)) {
            X = (int)X + Flip;
        }
    }
    else if (CollisionLeftSensor(42069) && Speed < 0 && !CollisionASensor(-1, -16)) {
        Action = ActionType::Climb;
        //audio_play_sound(sndClimb, 1, false);

        /*
        if (SuperForm)
            Scene->aud[0x49]->Play(1);
        else
            Scene->aud[0x4A]->Play(1);
        //*/

        Speed = 0;
        Gravity = 0;

        int ang = 0;
        if (!CollisionCheckLine((int)X, Y + 4, (int)X + (12 * Flip), Y + 4, &ang)) {
            X = (int)X + Flip;
        }
    }


    if (Ground && AngleMode == 0) {
        Action = ActionType::GlideSlide;
        //Action = ActionType::Normal;
    }
    else if (Ground) {
        Action = ActionType::Normal;
    }
}
void IPlayer::ActionGlideFall() {
    if (Ground) {
        //audio_play_sound(sndGlideLand, 1, false);
        //Scene->aud[0x56]->Play(3);
        //Speed *= 0.75;
        Speed = 0;
        Action = ActionType::GlideFallLand;
        GenericTimer = 16;
    }
}
void IPlayer::ActionGlideFallLand() {
    if (GenericTimer > 0) {
        GenericTimer--;
    }
    else {
        Action = ActionType::Normal;
        GenericTimer = -1;
    }
}
void IPlayer::ActionGlideSlide() {
    if (Speed > 0)
        Speed = fmax(Speed - 0.125f, 0.0f);
    else if (Speed < 0)
        Speed = fmin(Speed + 0.125f, 0.0f);

    if ((Speed == 0 || !InputJumpHold)) {
        Speed = 0;
    }
    if (Speed == 0) {
        Action = ActionType::Normal;
    }

    //if (global.Frame mod 5 == 0){
        //instance_create(x, y+13, objSkidDust);
        //audio_play_sound(sndGlideSlide, 1, false);
    //}
}

void IPlayer::ActionClimb() {
    int ang = 0;
    InputAlarm = 0;
    if (!CollisionCheckLine((int)X, Y + 4, (int)X + (12 * Flip), Y + 4, &ang)) {
        X = (int)X + Flip;
    }

    if (InputUp/* && scrPlayerCollisionCSensor(10, objParentTerrain) == false && scrPlayerCollisionDSensor(10, objParentTerrain) == false*/) {
        Y = (int)Y;
        Gravity = -1;
    }
    else if (InputDown) {
        Y = (int)Y;
        Gravity = 2;
    }
    else {
        Gravity = 0;
    }

    if (InputJump) {
        Gravity = -4;
        Speed = -Flip * 4;
        Ground = false;
        JumpVariable = true;
        Action = ActionType::Jumping;
        //scrPlayerResetTrail();

        //audio_play_sound(sndPlayerJump, 1, false);

        Angle = 0;
        TerrainAngle = 0;
        AngleMode = 0;
    }
    if (Ground)
        Action = ActionType::Normal;

    if (!CollisionCheckLine(X, (int)Y + 4, X + (13 * Flip), (int)Y + 4, &ang)) {
        Action = ActionType::GlideFall;
		ChangeAnimation(AnimationMap["Glide Drop"], 2);
    }

    if (!CollisionRightSensor(-1) && Flip == 1) {
        if (!CollisionCheckLine(X, (int)Y - 5, X + 13, (int)Y - 5, &ang)) {
            Action = ActionType::ClimbRise;
            Ground = true;
            Frame = 0;
        }
        else {
            Action = ActionType::GlideFall;
        }
    }
    else if (!CollisionLeftSensor(-1) && Flip == -1) {
        if (!CollisionCheckLine(X, Y - 5, X - 13, Y - 5, &ang)) {
            Action = ActionType::ClimbRise;
            Ground = true;
            Speed = 0;
            Gravity = 0;

            X += Flip * 20;
            Y = (int)Y - 32;
        }
        else {
            Action = ActionType::GlideFall;
        }
    }
}
void IPlayer::ActionClimbRise() {
    Speed = 0;
    Gravity = 0;

    if (AnimationDone > 0) {
        Action = ActionType::Normal;
        Ground = true;
        CameraX = 0;
    }
}

void IPlayer::HandleMonitors() {
    //*
    #if 0
    for (unsigned int o = 0; o < (unsigned int)Scene->ObjectBreakableCount; o++) {
        Object* obj = Scene->ObjectsBreakable[o];
        if (obj != NULL) {
            if (obj->Active) {
                if (obj->X + obj->W / 2 >= X - W / 2 - 1 &&
                    obj->Y + obj->H / 2 >= Y - H / 2 - 1 &&
                    obj->X - obj->W / 2 <  X + W / 2 + 1 &&
                    obj->Y - obj->H / 2 <  Y + H / 2 + 1) {

                    int hitFrom = 0;
                    float wy = (W + obj->W) * (Y - obj->Y);
                    float hx = (H + obj->H) * (X - obj->X);

                    if (wy > hx)
                        if (wy > -hx)
                            hitFrom = 3;
                        else
                            hitFrom = 2;
                    else
                        if (wy > -hx)
                            hitFrom = 0;
                        else
                            hitFrom = 1;

                    if (obj->BreakableByRoll && Action == ActionType::Rolling)
                        obj->OnBreakHorizontal(PlayerID, hitFrom);
                    if (obj->BreakableByJump && Action == ActionType::Jumping && ((hitFrom == 1 && Gravity > 0) || (hitFrom == 3 && Gravity < 0)))
                        obj->OnBreakVertical(PlayerID, hitFrom);
                    if (obj->BreakableByKnuckles && Character == CharacterType::Knuckles)
                        obj->OnBreakHorizontal(PlayerID, hitFrom);
                }
            }
        }
    }
    #endif

    for (int o = 0; o < Scene->ObjectBreakableCount; o++) {
        Object* obj = Scene->ObjectsBreakable[o];
        if (obj != NULL) {
            if (obj->Active) {
                if (obj->X + obj->W / 2 >= X - W / 2 - 2 &&
                    obj->Y + obj->H / 2 + 2 >= Y - H / 2 - 2 &&
                    obj->X - obj->W / 2 <  X + W / 2 + 2 &&
                    obj->Y - obj->H / 2 - 2 <  Y + H / 2 + 2) {

                    int hitFrom = 0;
                    float wy = (W + obj->W) * (Y - obj->Y);
                    float hx = (H + obj->H) * (X - obj->X);

                    if (wy > hx)
                        if (wy > -hx)
                            hitFrom = 3;
                        else
                            hitFrom = 2;
                    else
                        if (wy > -hx)
                            hitFrom = 0;
                        else
                            hitFrom = 1;

                    if (obj->BreakableByRoll && Action == ActionType::Rolling) {
                        if (obj->OnBreakHorizontal(PlayerID, hitFrom))
                            X -= std::ceil(abs(Speed));
                    }
                    else if (obj->BreakableByGlide && Action == ActionType::Glide) {
                        Gravity = -Gravity;
                        obj->OnBreakVertical(PlayerID, hitFrom);
                    }
                    else if (obj->BreakableByJump && Action == ActionType::Jumping && ((hitFrom == 0 && Speed < -0.5f) || (hitFrom == 2 && Speed > 0.5f) || (hitFrom == 1 && Gravity > 0) || (hitFrom == 3 && Gravity < 0))) {
                        if (hitFrom != 3) { // add "|| Settings_SonicKnucklesMonitorBehavior"
                            if (obj->OnBreakVertical(PlayerID, hitFrom) == 1)
                                Gravity = -Gravity;
                        }
                        else {
                            obj->Gravity = -3;
                            Gravity = 1;
                        }
                    }
                    else if (obj->BreakableByKnuckles && Character == CharacterType::Knuckles && ((hitFrom == 0 && Speed < -0.125f) || (hitFrom == 2 && Speed > 0.125f))) {
                        X -= std::ceil(abs(Speed));
                        obj->OnBreakHorizontal(PlayerID, hitFrom);
                    }
                }
            }
        }
    }
    //*/
}
bool IPlayer::HandleSprings() {
    ///*
    for (int o = 0; o < Scene->ObjectSpringCount; o++) {
        Object* obj = Scene->ObjectsSpring[o];
        if (obj != NULL) {
            if (obj->Active) {
                int si = abs(this->Sin[obj->Rotation]);
                int co = abs(this->Cos[obj->Rotation]);
                if (obj->X + obj->W / 2 + si * 3 - co * 6 >= X - W / 2 - 8 &&
                    obj->Y + obj->H / 2 + co * 3          >= Y - H / 2 &&
                    obj->X - obj->W / 2 - si * 3 + co * 6 <  X + W / 2 + 8 &&
                    obj->Y - obj->H / 2 - co * 3          <  Y + H / 2) {

                    float wy = (W + obj->W) * (Y - obj->Y);
                    float hx = (H + obj->H) * (X - obj->X);

                    int hitFrom = 0;

                    if (wy > hx)
                        if (wy > -hx)
                            hitFrom = 3;
                        else
                            hitFrom = 2;
                    else
                        if (wy > -hx)
                            hitFrom = 0;
                        else
                            hitFrom = 1;

                    bool Hurt = Action == ActionType::Hurt;
                    if (obj->OnCollisionWithPlayer(PlayerID, hitFrom, 1)) {
                        if (Hurt) {
                            Invincibility = InvincibilityType::Temporary;
                            InvincibilityTimer = 120;
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
    //*/
}
void IPlayer::HandleEnemies() {

}
void IPlayer::HandlePathSwitchers() {
    for (int i = 0; i < Scene->PlaneSwitchCount; i++) {
        int W = 16 * Scene->PlaneSwitchers[i].Size + 16;
        int H = 16 * Scene->PlaneSwitchers[i].Size + 16;
        if (Scene->PlaneSwitchers[i].Angle == 0) {
            W = 0;
        }
        else {
            H = 0;
        }
        if (X + 7 >= Scene->PlaneSwitchers[i].X - W / 2 &&
            X - 7 <  Scene->PlaneSwitchers[i].X + W / 2 &&
            Y + 11 >= Scene->PlaneSwitchers[i].Y - H / 2 &&
            Y - 11 <  Scene->PlaneSwitchers[i].Y + H / 2) {
            if (Scene->PlaneSwitchers[i].OnPath) {
                if (Ground) {
                    if (Speed * Cos[(int)Scene->PlaneSwitchers[i].Angle % 360] < 0) {
                        Layer = (Scene->PlaneSwitchers[i].Flags >> 3) & 1;
                        VisualLayer = (Scene->PlaneSwitchers[i].Flags >> 2) & 1;
                    }
                    else {
                        Layer = (Scene->PlaneSwitchers[i].Flags >> 1) & 1;
                        VisualLayer = (Scene->PlaneSwitchers[i].Flags >> 0) & 1;
                    }
                }
            }
            else {
                if (Scene->PlaneSwitchers[i].Angle == 0) {
                    if (Speed * Cos[(int)Scene->PlaneSwitchers[i].Angle % 360] > 0) {
                        Layer = (Scene->PlaneSwitchers[i].Flags >> 3) & 1;
                        VisualLayer = (Scene->PlaneSwitchers[i].Flags >> 2) & 1;
                    }
                    else {
                        Layer = (Scene->PlaneSwitchers[i].Flags >> 1) & 1;
                        VisualLayer = (Scene->PlaneSwitchers[i].Flags >> 0) & 1;
                    }
                }
                else {
                    if (Gravity * Sin[(int)Scene->PlaneSwitchers[i].Angle % 360] > 0) {
                        Layer = (Scene->PlaneSwitchers[i].Flags >> 3) & 1;
                        VisualLayer = (Scene->PlaneSwitchers[i].Flags >> 2) & 1;
                    }
                    else {
                        Layer = (Scene->PlaneSwitchers[i].Flags >> 1) & 1;
                        VisualLayer = (Scene->PlaneSwitchers[i].Flags >> 0) & 1;
                    }
                }
            }
        }
    }

    /*
    for (int o = 0; o < Scene->ObjectPathSwitcherCount; o++) {
        Object* obj = Scene->ObjectsPathSwitcher[o];
        if (obj != NULL) {
            if (X + W / 2 >= obj->X - obj->W / 2.f &&
                Y + H / 2 >= obj->Y - obj->H / 2.f &&
                X - W / 2 <  obj->X + obj->W / 2.f &&
                Y - H / 2 <  obj->Y + obj->H / 2.f) {
                int groundOnly = (obj->SubType >> 7) & 0x01;
                int orientation = (obj->SubType >> 2) & 0x01;

                int leftUpPath = (obj->SubType >> 4) & 0x01;
                int leftUpPriority = (obj->SubType >> 6) & 0x01; //1 is high, 0 is low
                int rightDownPath = (obj->SubType >> 3) & 0x01;
                int rightDownPriority = (obj->SubType >> 5) & 0x01;

                if (groundOnly == 1 && !Ground)
                    break;

                if ((Gravity > 0 && orientation == 1) || (Speed * this->Sin[AngleMode * 90] < 0 && orientation == 1) || (Speed * this->Cos[AngleMode * 90] > 0 && orientation == 0)) {
                    Layer = rightDownPath;
                    VisualLayer = rightDownPriority;
                }
                if ((Gravity < 0 && orientation == 1) || (Speed * this->Sin[AngleMode * 90] > 0 && orientation == 1) || (Speed * this->Cos[AngleMode * 90] < 0 && orientation == 0)) {
                    Layer = leftUpPath;
                    VisualLayer = leftUpPriority;
                }
                break;
            }
        }
    }
    //*/
}

void IPlayer::Jump() {
    ///*
    float GSpeed = Speed;
    GroundSpeed = Speed;
    Speed =    (this->Cos[Angle] * GSpeed) + (this->Sin[Angle] * (JumpHeight + (Character == CharacterType::Knuckles ? 0.5f : 0.0f)));
    Gravity = -(this->Sin[Angle] * GSpeed) + (this->Cos[Angle] * (JumpHeight + (Character == CharacterType::Knuckles ? 0.5f : 0.0f)));
    Ground = false;
    JumpVariable = 1;
    Action = ActionType::Jumping;

    //Scene->aud_Jump->Play(1); // $AudioPlay(aud_Jump, 1);

    DropDashRev = 0;
    Angle = 0;
    TerrainAngle = -1;
    AngleMode = 0;
    InputAlarm = 0;
    JumpAnimSpeed = 1.0f / fmax((5.0f - abs(Speed)), 1.0f);
    //*/
}
void IPlayer::Hurt(int x, bool spike) {
    ///*
    if (Action == ActionType::Hurt || Shield == ShieldType::Instashield || Action == ActionType::Dead || Invincibility != InvincibilityType::None || SuperForm || Action == ActionType::Transform)
        return;

    Vibrate(0, 0.75, 450);
    ObjectControlled = 0;

    if (Shield == ShieldType::None) {
        if (Rings > 0) {
            Action = ActionType::Hurt;
            //if (CollisionCSensor(-1, 6) == false && CollisionDSensor(-1, 6) == false)
                Gravity = -4;
            //else
            //    Gravity = 0;
            Ground = false;
            Speed = 2 * signum(X - x);
            if (Speed == 0) Speed = -2;
            if (Underwater) {
                Gravity /= 2;
                Speed /= 2;
            }

            CreateRingLoss();
            /*
            if (!spike)
                Scene->aud_Spiked->Play(1); // aud_Spiked $AudioPlay(aud_RingLoss, 1);
            else
                Scene->aud_Spiked->Play(1);
            //*/
        }
        else {
            Die();
            //Scene->aud_Die->Play(1); // $AudioPlay(aud_Die, 1);
        }
    }
    else if (Invincibility == InvincibilityType::None) {
        Shield = ShieldType::None;
        Action = ActionType::Hurt;
        /*
        if (!spike)
            Scene->aud_Spiked->Play(1); // $AudioPlay(aud_Death, 1);
        else
            Scene->aud_Spiked->Play(1);
        //*/
        Gravity = -4;
        Ground = false;
        Speed = 2 * signum(X - x);
        if (Speed == 0) Speed = -2;
        if (Underwater) {
            Gravity /= 2;
            Speed /= 2;
        }
    }
    //*/
}
void IPlayer::Die() {
    /*
    if (Action == ActionType::Dead)
        return;

    Action    = ActionType::Dead;
    Speed     = 0;
    Angle     = 0;
    AngleMode = 0;
    Gravity   = -7;

    Scene->aud_Die->Play(1);

    //if (!Controllable) return;

    Scene->lives--;
    //*/
}
void IPlayer::CreateRingLoss() {
    /*
    //if (!Controllable) return;

    int RingTotal = fmin((int)Rings, 32);
    float RingAngle = 101.25f;
    float RingSpeed = 4;

    Scene->aud_C_RingLoss->Play(3);

    while (RingTotal > 0) {
        IRing* ring = new IRing();
        ring->X = X - 8;
        ring->Y = Y - 16;
        ring->Lifespan = 256;
        ring->Sprite = App->Sprites["Ring"];

        ring->Gravity = -std::sin(toRadians(round(RingAngle))) * RingSpeed;
        ring->Speed   =  std::cos(toRadians(round(RingAngle))) * RingSpeed;
        ring->CanFall = true;
        ring->NonCollect = 64;

        ring->G = G;
        ring->App = App;
        ring->Scene = Scene;

        if (RingTotal % 2 != 0) {
            RingAngle += 22.5f;
            ring->Speed *= -1.f;
        }
        RingTotal -= 1;
        if (RingTotal == 16) {
            RingSpeed = 2;
            RingAngle = 101.25f;
        }

        Scene->Objects[Scene->ObjectCount++] = ring;

        ring->Create();
        ring->Priority = true;
    }
    Rings = 0;

    HyperRings = false;
    //*/
    Rings = 0;
}
