#include <Game/Player.h>
#include <Engine/IResources.h>
#include <Engine/IGraphics.h>

#include <Game/Explosion.h>
#include <Game/BubbleCountdown.h>

// Find:    #([A-f0-9]+) ([A-f0-9]+) ([A-f0-9]+) ([A-f0-9]+)
// Replace: 0x$3$2$1,

Uint32 SonicPaletteNormal[6] = {
	// Just blue
	0x00000080,
	0x000038C0,
	0x000068F0,
	0x001888F0,
	0x0030A0F0,
	0x0068D0F0,
};
Uint32 SonicPaletteSuper[6] = {
	// Just gold
	0x00F0C000,
	0x00F0D028,
	0x00F0E040,
	0x00F0E860,
	0x00F0E898,
	0x00F0E8D0,
};
Uint32 SonicPaletteSuperPulse[6] = {
	0x00F0D898,
	0x00F0E0B0,
	0x00F0E8C0,
	0x00F0F0D8,
	0x00F0F0F0,
	0x00F0F0F8,
};

Uint32 TailsPaletteNormal[6] = {
	0x800801,
	0xB01801,
	0xD05001,
	0xE07808,
	0xE89008,
	0xF0A801,
};
Uint32 TailsPaletteSuper[6] = {
	0xF03830,
	0xF06848,
	0xF09860,
	0xF0B868,
	0xF0C870,
	0xF0D870,
};
Uint32 TailsPaletteSuperPulse[6] = {
	0x800801,
	0xB01801,
	0xD05001,
	0xE07808,
	0xE89008,
	0xF0A801,
};

Uint32 KnuxPaletteNormal[6] = {
	0x580818,
	0x980130,
	0xD00840,
	0xE82858,
	0xF06080,
	0xF08088,
};
Uint32 KnuxPaletteSuper[6] = {
	0xF05878,
	0xF06090,
	0xF080A0,
	0xF098B0,
	0xF0B0C8,
	0xF0C0C8,
};
Uint32 KnuxPaletteSuperPulse[6] = {
	0x580818,
	0x980130,
	0xD00840,
	0xE82858,
	0xF06080,
	0xF08088,
};

Uint32 SonicPaletteNormalHCZ[6] = {
	0x200888,
	0x3020C8,
	0x3840F0,
	0x4070F0,
	0x4098F0,
	0x40C0F0,
};
Uint32 SonicPaletteSuperHCZ[6] = {
	0x88C880,
	0x68E090,
	0x50F098,
	0x68F0C0,
	0x78F0C8,
	0xA0F0D8,
};
Uint32 SonicPaletteSuperPulseHCZ[6] = {
	0x60E898,
	0x48F0A0,
	0x58F0B0,
	0x68F0C0,
	0x90F0D0,
	0xA0F0D8,
};

Uint32 TailsPaletteNormalHCZ[6] = {
	0x880808,
	0xA03810,
	0xA05848,
	0xB07058,
	0xC08068,
	0xC89078,
};
Uint32 TailsPaletteSuperHCZ[6] = {
	0xCC6161,
	0xDC8462,
	0xD5978A,
	0xDEA893,
	0xE6B09D,
	0xEABAA7,
};
Uint32 TailsPaletteSuperPulseHCZ[6] = {
	0x880808,
	0xA03810,
	0xA05848,
	0xB07058,
	0xC08068,
	0xC89078,
};

Uint32 KnuxPaletteNormalHCZ[6] = {
	0x181050,
	0x301090,
	0x5018A8,
	0x8828C0,
	0xA048C0,
	0xB868C8,
};
Uint32 KnuxPaletteSuperHCZ[6] = {
	0x746DA3,
	0x7F65D0,
	0x9768E0,
	0xC070EF,
	0xD086EB,
	0xDE9CED,
};
Uint32 KnuxPaletteSuperPulseHCZ[6] = {
	0x181050,
	0x301090,
	0x5018A8,
	0x8828C0,
	0xA048C0,
	0xB868C8,
};

IPlayer::IPlayer() {
    X = 512;
    Y = 64;
    W = 22;
    H = 40;
    OrigH = H;
    DropDashEnabled = true;

	ModeSin[0] = 0;
	ModeSin[1] = 1;
	ModeSin[2] = 0;
	ModeSin[3] = -1;

	ModeCos[0] = 1;
	ModeCos[1] = 0;
	ModeCos[2] = -1;
	ModeCos[3] = 0;

    memset(Sprites, 0, sizeof(Sprites));
}

void IPlayer::Create() {
    InputLockLeftRight = false;
    Ground = false;
    WaitTimer = -1;
    Action = ActionType::Normal;

	InputUp = false;
	InputDown = false;
	InputLeft = false;
	InputRight = false;
	InputJump = false;
	InputJumpHold = false;
	InputLeftPress = false;
	InputRightPress = false;

    Hidden = false;

    ShieldAnimation = 0;
    ShieldUsable = true;
    ShieldAction = false;
    Shield = ShieldType::None;

    FlyFlag = 0;
    FlyTimer = 480;
    FlyTimerMax = 480;

    SuperForm = false;
    SuperFormAnim = SuperFormAnimType::None;
    Layer = 0;
    VisualLayer = 0;
    Angle = 0;
    AngleMode = 0;
    DisplayAngle = 0;
    Cutscene = false;
    RingLifeValue = 100;
    HyperRings = false;
    GroundSpeed = 0;
    XSpeed = 0;
    YSpeed = 0;
    Flip = 1;
    DisplayFlip = 1;
    CameraX = 0;
    CameraY = 0;
    InputAlarm = 0;
    Layer = 0;
    VisualLayer = 0;
    EnemyCombo = 0;

    ForceRoll = false;
    CameraLookTimer = 0;
    CameraLockTimer = 0;
    GenericTimer = -1;
    ObjectControlled = 0;
    RingAlarm = 0;

    Underwater = false;
    UnderwaterTimer = 1800;

    InvincibilityTimer = 0;
    Invincibility = InvincibilityType::None;

    SpeedSneakersTimer = 0;
    SpeedSneakersActive = false;


    if (Sprites[0]) { // prevent re-loading sprites on restart
        goto PlayerSetPalettes;
    }

    //Character = CharacterType::Knuckles;

    for (int a = 0; a < 256; a++) {
        this->Sin[a] = -std::sin(a * M_PI / 128);
        this->Cos[a] =  std::cos(a * M_PI / 128);
    }
    Lives = 0;

    // Flags:
    // 0x00 - None (Animation Controlled By Code)
    // 0x01 - Animation Loops
    // 0x04 - Animation Stops

    if (Character == CharacterType::Sonic) {
        H = 40;
        OrigH = H;
        Sprites[0] = new ISprite("Player/Sonic1.gif", App);
        Sprites[1] = new ISprite("Player/Sonic2.gif", App);
        Sprites[2] = new ISprite("Player/Sonic3.gif", App);
        Sprites[3] = new ISprite("Player/Sonic4.gif", App);
        Sprites[4] = new ISprite("Player/SonicCutsceneCPZ.gif", App);

        Sprites[0]->LoadAnimation("Player/Sonic.bin");

        int i = 0;
        for (; i < Sprites[0]->AnimCount; i++) {
            AnimationMap.emplace(string(Sprites[0]->Animations[i].Name), i);
        }

        Sprites[0]->LoadAnimation("Player/SuperSonic.bin");
        for (; i < Sprites[0]->AnimCount; i++) {
            AnimationMap.emplace("S_" + string(Sprites[0]->Animations[i].Name), i);
        }

        Sprites[1]->LinkAnimation(Sprites[0]->Animations);
        Sprites[2]->LinkAnimation(Sprites[0]->Animations);
        Sprites[3]->LinkAnimation(Sprites[0]->Animations);
        Sprites[4]->LinkAnimation(Sprites[0]->Animations);
	}
    else if (Character == CharacterType::Tails) {
        H = 32;
        OrigH = H;

        Sprites[0] = new ISprite("Player/Tails1.gif", App);
        Sprites[1] = new ISprite("Player/Tails2.gif", App);
        Sprites[2] = new ISprite("Player/Tails3.gif", App);
        Sprites[3] = new ISprite("Player/TailsCutsceneCPZ.gif", App);

        Sprites[0]->LoadAnimation("Player/Tails.bin");
        Sprites[0]->LoadAnimation("Player/TailSprite.bin");
        Sprites[1]->LinkAnimation(Sprites[0]->Animations);
        Sprites[2]->LinkAnimation(Sprites[0]->Animations);
        Sprites[3]->LinkAnimation(Sprites[0]->Animations);

        for (int i = 0; i < Sprites[0]->AnimCount; i++) {
            AnimationMap.emplace(string(Sprites[0]->Animations[i].Name), i);
        }
	}
    else if (Character == CharacterType::Knuckles) {
        H = 40;
        OrigH = H;
        if (Scene->KnuxSprite[0]) {
            for (int i = 0; i < 5; i++) {
                Sprites[i] = Scene->KnuxSprite[i];
            }
        }
        else {
            Sprites[0] = new ISprite("Player/Knux1.gif", App);
            Sprites[1] = new ISprite("Player/Knux2.gif", App);
            Sprites[2] = new ISprite("Player/Knux3.gif", App);
            Sprites[3] = new ISprite("Player/KnuxCutsceneAIZ.gif", App);
            Sprites[4] = new ISprite("Player/KnuxCutsceneHPZ.gif", App);

            Sprites[0]->LoadAnimation("Player/Knux.bin");
            Sprites[1]->LinkAnimation(Sprites[0]->Animations);
            Sprites[2]->LinkAnimation(Sprites[0]->Animations);
            Sprites[3]->LinkAnimation(Sprites[0]->Animations);
            Sprites[4]->LinkAnimation(Sprites[0]->Animations);
        }

        for (int i = 0; i < Sprites[0]->AnimCount; i++) {
            AnimationMap.emplace(string(Sprites[0]->Animations[i].Name), i);
        }
	}
    else if (Character == CharacterType::Ray) {
        Sprites[0] = new ISprite("Player/Ray1.gif", App);
        Sprites[1] = new ISprite("Player/Ray2.gif", App);
        Sprites[2] = new ISprite("Player/Ray3.gif", App);
        Sprites[3] = new ISprite("Player/RayCutsceneCPZ.gif", App);

        Sprites[0]->LoadAnimation("Player/Ray.bin");
        Sprites[1]->LinkAnimation(Sprites[0]->Animations);
        Sprites[2]->LinkAnimation(Sprites[0]->Animations);
        Sprites[3]->LinkAnimation(Sprites[0]->Animations);

        for (int i = 0; i < Sprites[0]->AnimCount; i++) {
            AnimationMap.emplace(string(Sprites[0]->Animations[i].Name), i);
        }
	}

    SpriteDashDust = Scene->ExplosionSprite;

    SpriteShields = new ISprite("Sprites/Global/ShieldsOld.gif", App);
    SpriteShields->LoadAnimation("Sprites/Global/ShieldsOld.bin");

    SpriteShields2 = new ISprite("Sprites/Global/Shields.gif", App);
    SpriteShields2->LoadAnimation("Sprites/Global/Invincible.bin");

    for (int i = 0; i < 8; i++) {
        if (!Sprites[i]) break;

        memcpy(Sprites[i]->PaletteAlt, Sprites[i]->Palette, 256 * 4);
		Sprites[i]->UpdatePalette();
    }

    // Set Palettes
    PlayerSetPalettes:
    int palWhere;
    Uint32 *palNormal, *palNormalHCZ;

    if (Character == CharacterType::Sonic) {
        palWhere = 0x40;
        palNormal = SonicPaletteNormal;
        palNormalHCZ = SonicPaletteNormalHCZ;
    }
    else if (Character == CharacterType::Tails) {
        palWhere = 0x46;
        palNormal = TailsPaletteNormal;
        palNormalHCZ = TailsPaletteNormalHCZ;
    }
    else if (Character == CharacterType::Knuckles) {
        palWhere = 0x50;
        palNormal = KnuxPaletteNormal;
        palNormalHCZ = KnuxPaletteNormalHCZ;
    }
    else {
        // Default to Sonic
        palWhere = 0x40;
        palNormal = SonicPaletteNormal;
        palNormalHCZ = SonicPaletteNormalHCZ;
    }

    for (int i = 0; i < 8; i++) {
        if (!Sprites[i]) break;

        memcpy(Sprites[i]->Palette + palWhere, palNormal, 6 * 4);
        memcpy(Sprites[i]->PaletteAlt + palWhere, palNormalHCZ, 6 * 4);
        Sprites[i]->Paletted = 2;
		Sprites[i]->UpdatePalette();
    }
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
    CurrentFrame = startFrame << 8;
    CurrentAnimation = animationID;
    AnimationDone = 0;
}

/*

The Doomsday (original):
Super Sonic has no acceleration, when UDLR is pressed, (middle step)
Sonic's speed is set to 0x300

When jump is pressed, speed is set to 0x900 (end step)

Speed decrements by 0x40 per begin step

when hit by asteroid, speed goes to -0xC0, then
after a frame, -0x80

*/

void IPlayer::Update() {
    if (Action == ActionType::Transform)
        return;

    int16_t acc = 0xC;
    int16_t dec = 0x80;
    int16_t frc = 0xC;
    int16_t top = 0x600;
    int16_t slp = 0x20;
    int16_t slprollup = 0x14;
    int16_t slprolldown = 0x50;
    int16_t fall = 0x280;
    int16_t grv = 0x38;
    int16_t air = 0x18;
    int16_t rel = -0x400;

    if (Sidekick) {
        IPlayer* player = Scene->Player;
        PlayerStatus status = player->PlayerStatusTable[(player->PlayerStatusTableIndex + 0x20 - 0x10) & 0x1F];

        if (!PanicSpindashing) {
            InputUp = status.InputUp;
            InputDown = status.InputDown;
            InputLeft = status.InputLeft;
            InputRight = status.InputRight;
            InputJump = false;
            InputJumpHold = status.InputJumpHold;
            if (Ground || InputUp || Character == CharacterType::Tails) {
                InputJump = status.InputJump;
            }

            if (!InputJump) {
                if (player->Ground && player->EZY < EZY - 0x10 && player->YSpeed >= 0x0) {
                    if ((abs(GroundSpeed) <= 0x100 || Angle == 0) && InputAlarm > 0) {
                        InputDown = true;
                        PanicSpindashing = true;
                        GroundSpeed = 0;
                    }
                    else if (InputAlarm == 0) {
                        if (Ground && !(Scene->Frame & 0x1F))
                            InputJump = true;
                        InputJumpHold = true;
                    }
                }
            }

            if (Action == ActionType::Respawn) {
                VisualLayer = 1;

                if (player->EZX < EZX - 0x10)
                    EZX -= 2;
                if (player->EZX > EZX + 0x10)
                    EZX += 2;

                if (EZY < player->EZY)
                    EZY += 1;
                else
                    Action = ActionType::Normal;
                return;
            }
            else {
                VisualLayer = player->VisualLayer;

                if (Action != ActionType::Fly) {
                    if (player->EZX < EZX - 0x10)
                        InputLeft = true;
                    if (player->EZX > EZX + 0x10)
                        InputRight = true;
                }
                else {
                    if (player->EZX < EZX - 0x02)
                        InputLeft = true;
                    if (player->EZX > EZX + 0x02)
                        InputRight = true;
                }
            }
        }
        else {
            InputDown = true;
            InputJump = false;
            if (((Scene->Frame >> 3) & 1) && Action == ActionType::CrouchDown)
                InputJump = true;

            if (!(Scene->Frame & 0x3F)) {
                InputJump = false;
                InputDown = false;
                PanicSpindashing = false;
            }
        }
    }

    OnScreen = false;
    if (EZX + W / 2 >= Scene->CameraX &&
        EZY + H / 2 >= Scene->CameraY &&
        EZX - W / 2 <  Scene->CameraX + App->WIDTH &&
        EZY - H / 2 <  Scene->CameraY + App->HEIGHT) {
        OnScreen = true;
    }

    CheckDespawn();

    if (Action == ActionType::Dead) {
        YSpeed += grv;
        Y += YSpeed << 8;
        return;
    }

    bool isHurt = Action == ActionType::Hurt;
    if (isHurt) {
        grv = 0x30;
        if (Underwater)
            grv /= 2;
    }

    if (Angle < 0)
        Angle += 0x100;
    Angle &= 0xFF;

    // Underwater checker
    if ((Y >> 16) > Scene->WaterLevel) {
        if (!Underwater && Action != ActionType::Respawn) {
            XSpeed >>= 1;
            if (Action != ActionType::Spring)
                YSpeed >>= 2;

            if (Shield == ShieldType::Fire)
                Shield = ShieldType::None;

            if (Shield == ShieldType::Electric) {
                Shield = ShieldType::None;
            }

            if (YSpeed != 0 && Action != ActionType::InStream && Action != ActionType::InStreamGrab) {
                Explosion* watersplash;
                watersplash = new Explosion();
                watersplash->G = G;
                watersplash->App = App;
                watersplash->CurrentAnimation = 1;
                watersplash->FlipX = false;
                watersplash->Active = true;
                watersplash->Sprite = Scene->WaterSprite;
                watersplash->X = EZX;
                watersplash->Y = Scene->WaterLevel;
                Scene->Explosions.push_back(watersplash);
                Sound::Play(Sound::SFX_SPLASH);
            }
        }
        Underwater = true;
    }
    else {
        if (Underwater && Action != ActionType::Respawn) {
            if (YSpeed >= -0x400 && ObjectControlled == 0 && Action != ActionType::Hurt)
                YSpeed <<= 1;

            if (YSpeed < -0x1000)
                YSpeed = -0x1000;

            App->Audio->RemoveMusic(Sound::SoundBank[0xFD]);

            if (YSpeed != 0) {
                Explosion* watersplash;
                watersplash = new Explosion();
                watersplash->G = G;
                watersplash->App = App;
                watersplash->CurrentAnimation = 1;
                watersplash->FlipX = false;
                watersplash->Active = true;
                watersplash->Sprite = Scene->WaterSprite;
                watersplash->X = EZX;
                watersplash->Y = Scene->WaterLevel;
                Scene->Explosions.push_back(watersplash);
                Sound::Play(Sound::SFX_SPLASH);
            }
        }
        Underwater = false;
    }

    string superflag;
    if (SuperForm && Character == CharacterType::Sonic)
        superflag = "S_";

    if (Underwater) {
        acc = 0x6;
        dec = 0x40;
        frc = 0x6;
        top = 0x300;
        slp = 0x20;
        slprollup = 0x14;
        slprolldown = 0x50;
        fall = 0x280;
        grv = 0x10;
        air = 0xC;
        rel = -0x200;

        SpeedSneakersActive = false;
    }

    if (SpeedSneakersActive) {
        acc *= 2;
        top *= 2;
        air *= 2;
        frc *= 2;
    }

    if (SuperForm) {
        acc = 0x30;
        dec = 0x100;
        frc = 0xC;
        top = 0xA00;
        air = 0x60;

        if (SpeedSneakersActive) {
            top = 0xC00;
        }

        if (Character != CharacterType::Sonic) {
            top -= 0x200;
            air /= 2;
        }

        if (Underwater) {
            top /= 2;
            acc /= 2;
            air /= 2;
        }
    }

    H = OrigH;

    if (Action == ActionType::Fan) {
        Ground = false;
        grv = 0;
        JumpVariable = 1;
    }
    else if (Action == ActionType::Glide) {
        int Flip = IMath::sign(DisplayFlip);
        grv = 0x0;
        H = 32;

        if (YSpeed < 0x80) YSpeed += 0x20;
        if (YSpeed > 0x80) YSpeed -= 0x20;

        if (SuperForm) {
            if (XSpeed < 0)
                XSpeed -= 0xC;
            else
                XSpeed += 0xC;
        }
        else {
            if (XSpeed < 0)
                XSpeed -= 0x4;
            else
                XSpeed += 0x4;
        }

        if (Flip > 0) {
            if (XSpeed < 0)
                XSpeed = 0;
        }
        else {
            if (XSpeed > 0)
                XSpeed = 0;
        }

        if (Scene->CollisionAtClimbable(EZX + 12 * IMath::sign(XSpeed), EZY - 10, NULL, XSpeed < 0 ? 3 : 1, this)) {
            if (SuperForm && IMath::abs(XSpeed) >= 0x480) {
                // Sound::Play(0x49);
                // Scene->ShakeTimer = 14;
            }
            else {
                Sound::Play(Sound::SFX_GRAB);
            }

            DisplayFlip = IMath::sign(XSpeed);
            XSpeed = 0;
            Action = ActionType::Climb;

            // To make sure Knuckles is properly on the wall
            while (Scene->CollisionAtClimbable(EZX + 10 * DisplayFlip, EZY - 10, NULL, DisplayFlip < 0 ? 3 : 1, this))
                EZX -= DisplayFlip;
            while (!Scene->CollisionAtClimbable(EZX + 10 * DisplayFlip, EZY - 10, NULL, DisplayFlip < 0 ? 3 : 1, this))
                EZX += DisplayFlip;
        }

        if (!InputJumpHold) {
            Action = ActionType::GlideFall;
            XSpeed /= 4;
            grv = 0x38;
        }
    }
    else if (Action == ActionType::GlideSlide) {
        frc = 0x20;
        H = 32;

        InputAlarm = 3;

        if (!InputJumpHold) {
            GroundSpeed = 0;
        }
        if (GroundSpeed == 0) {
            H = OrigH;

            while (Scene->CollisionAt(EZX, EZY + H / 2 - 1, NULL, 0, this))
                EZY--;
        }

        if (!Ground) {
            Action = ActionType::GlideFall;
            grv = 0x38;
        }
    }
    else if (Action == ActionType::Climb) {
        int Flip = IMath::sign(DisplayFlip);
        grv = 0;
        air = 0;
        YSpeed = 0;
        XSpeed = 0;
        if (!SuperForm) {
            if (InputUp) {
                YSpeed = -0x100;
            }
            else if (InputDown) {
                YSpeed = 0x100;
            }
        }
        else {
            if (InputUp) {
                YSpeed = -0x200;
            }
            else if (InputDown) {
                YSpeed = 0x200;
            }
        }

        if (!Scene->CollisionAtClimbable(EZX + 10 * Flip, EZY - 10, NULL, Flip < 0 ? 3 : 1, this)) {
            if (YSpeed >= 0) {
                Action = ActionType::GlideFall;
                ChangeAnimation(AnimationMap["Glide Drop"], 2);
            }
            else {
                Action = ActionType::ClimbRise;
                StoredX = EZX;
                StoredY = EZY;
            }
        }

        if (InputJump) {
            Jump();
            XSpeed = Flip * -0x400;
            YSpeed = -0x400;
            InputJump = false;
        }
    }
    else if (Action == ActionType::ClimbRise) {
        grv = 0;
        air = 0;
        XSpeed = 0;
        YSpeed = 0;
    }
    else if (Action == ActionType::RayGlide) {
        // sub_4CD660

        if (Angle == 1) { // Is Facing Up
            if (GlideTurnCos < 0x70)
                GlideTurnCos += 8;
        }
        else {
            if (GlideTurnCos > 0x10)
                GlideTurnCos -= 8;
        }

        if (GlideSpeedStore != 0) {
            YSpeed += GlideSpeedStore >> (2 - Underwater);
            if (YSpeed < GlideSpeedStore) {
                YSpeed = GlideSpeedStore;
                GlideSpeedStore = 0;
            }
        }
        else {
            YSpeed += 0x38 * GlideTurnCos >> 9;
        }

        if (YSpeed < -0x600)
            YSpeed = -0x600;

        if (Angle == 1) {
            grv = 0;
            air = 0;
            int tempYSpeed = YSpeed;
            if (tempYSpeed > 0x100)
                YSpeed = tempYSpeed - (tempYSpeed >> 2);
        }

        int storedYSpeed = YSpeed;
        if (storedYSpeed <= 0) {
            MaxGlideSpeed -= (22 * (0x50 - GlideTurnCos)) >> 6;
            if (MaxGlideSpeed < 0x400)
                MaxGlideSpeed = 0x400;
        }
        else if (storedYSpeed > MaxGlideSpeed) {
            MaxGlideSpeed = storedYSpeed - (storedYSpeed >> 6);
        }

        if (XSpeed) {
            int v23 = 0x50 - GlideTurnCos;
            if (DisplayFlip < 0) {
                XSpeed -= (0x16 * v23 >> Underwater) >> 6;
                if (XSpeed > -0x100)
                    XSpeed = -0x100;

                int signedMaxGlideSpeed = -MaxGlideSpeed;
                if (XSpeed < signedMaxGlideSpeed)
                    XSpeed = signedMaxGlideSpeed;
            }
            else {
                XSpeed += (0x16 * v23 >> Underwater) >> 6;
                if (XSpeed < 0x100)
                    XSpeed = 0x100;

                int signedMaxGlideSpeed = MaxGlideSpeed;
                if (XSpeed > signedMaxGlideSpeed)
                    XSpeed = signedMaxGlideSpeed;
            }
        }

        int v7 = 0; // 1A8
        if (v7) {
            // 1A8
        }
        else {
            bool did = true;
            if (DisplayFlip < 0) {
                if (!InputRight || GlideTurnCos != 0x10) {
                    if (InputLeft && GlideTurnCos == 0x70 && Angle == 1) {
                        GlideSpeedStore = 0;
                        Angle = 0;
                        ChangeAnimation(AnimationMap["Ray Fly Down"], 0);
                    }
                    did = false;
                }
            }
            else if (!InputLeft || GlideTurnCos != 0x10) {
                if (InputRight && GlideTurnCos == 0x70 && Angle == 1) {
                    GlideSpeedStore = 0;
                    Angle = 0;
                    ChangeAnimation(AnimationMap["Ray Fly Down"], 0);
                }
                did = false;
            }

            if (did && !Angle) {
                bool ySpeedGreaterThan = YSpeed > 0x280 && false;
                bool ySpeedEquals = YSpeed == 0x280;
                bool ySpeedLessThan = YSpeed < 0x280;

                Angle = 1;

                if (!((ySpeedLessThan != ySpeedGreaterThan) || ySpeedEquals)
                    || RayBoostCount == 0x100
                    || (Underwater && YSpeed > 0x180)) {
                    int v10 = XSpeed;
                    int v11 = v10;
                    ySpeedLessThan = v10 < 0;
                    if (v10 < 0) {
                        v11 = -v10;
                        ySpeedLessThan = v10 < 0;
                    }

                    int v13 = XSpeed;
                    if (ySpeedLessThan) {
                        v13 = -v10;
                        if (v10 < 0)
                            v10 = -v10;
                    }

                    int v15 = -(RayBoostCount * ((v11 >> 1) + (v13 >> 2) + (v10 >> 4)) >> 8);
                    GlideSpeedStore = v15;
                    if (Underwater)
                        GlideSpeedStore = (v15 >> 1) + (v15 >> 3);
                    if (RayBoostCount > 0x10)
                        RayBoostCount = RayBoostCount - 0x20;
                    if (GlideSpeedStore < -0x600)
                        GlideSpeedStore = -0x600;
                }
                ChangeAnimation(AnimationMap["Ray Fly Up"], 0);
            }
        }

        if (!InputJumpHold || XSpeed == 0 || EZY < Scene->CameraY) {
            Action = ActionType::Jumping;
			JumpVariable = 0;
        }
    }
    else if (Action == ActionType::Fly) {
        if (YSpeed < -0x100)
            FlyFlag = 0x8;

        if (InputJump && FlyTimer > 0) {
            FlyFlag = -0x20;
        }

        if (!Underwater && !(Scene->Frame & 0xF)) {
            if (FlyTimer > 0)
                Sound::Play(Sound::SFX_TAILS_FLY);
            else
                Sound::Play(Sound::SFX_TAILS_TIRED);
        }

        grv = FlyFlag;

        if (FlyTimer > 0)
            FlyTimer--;
    }
	else if (Action == ActionType::Spring) {
		H = 32;
	}
	else if (Action == ActionType::Jumping) {
		H = 32;
	}

    if (Action == ActionType::Slide) {
        if (!(Scene->Frame & 0x1F))
            Sound::Play(Sound::SFX_SLIDE);
    }

    bool IUp = InputUp;
    bool IDown = InputDown;
    bool IJump = InputJump;
    bool ILeft = InputLeft;
    bool IRight = InputRight;
    bool IJumpHold = InputJumpHold;

    if (ObjectControlled != 0 || ForceRoll || isHurt || ControlLocked) {
        InputUp = false;
        InputDown = false;
        InputLeft = false;
        InputRight = false;

        if ((ObjectControlled >> 7 & 1) == 1) {
            InputJump = false;
            InputJumpHold = false;
        }
    }

    if (InputLockLeftRight) {
        InputUp = false;
        InputDown = false;
        InputJump = false;
        InputJumpHold = false;
    }

    if (ObjectControlled == 0) {
        DoCollision = true;
    }

	if (Action == ActionType::Grab) {
		DoCollision = false;
	}

    if (Action == ActionType::InStream) {
        if (InputUp)
            YSpeed = -0x120;
        if (InputDown)
            YSpeed = 0xC0;
    }
    if (Action == ActionType::InStreamGrab) {
        grv = 0;
        YSpeed = 0;
        XSpeed = 0;
        if (InputUp)
            YSpeed = -0x100;
        if (InputDown)
            YSpeed = 0x100;
    }

    if (ForceRoll) {
        Action = ActionType::Rolling;
        if (abs(GroundSpeed) < 1) {
            GroundSpeed = 0x580;
        }
    }

    if (InputUp || InputDown || InputLeft || InputRight || InputJump ) {
        if (Action == ActionType::CancelableAnim)
            Action = ActionType::Normal;
    }

    if (InputUp || InputDown || InputLeft || InputRight || InputJump || InputJumpHold || !Ground || XSpeed != 0) {
        WaitTimer = 180;

        //if (Ground) {
            if (Action == ActionType::Bored1)
                Action = ActionType::Normal;
        //}
    }

    bool doRollFriction =
        Action == ActionType::Rolling ||
        Action == ActionType::Slide;

    if (!doRollFriction) {
        GroundSpeed -= slp * Sin[Angle];
    }
    else {
        if (IMath::sign(GroundSpeed) == IMath::sign(Sin[Angle]))
            GroundSpeed -= slprollup * Sin[Angle];
        else
            GroundSpeed -= slprolldown * Sin[Angle];
    }

    bool doLeftRight =
        Action != ActionType::InStreamGrab &&
        Action != ActionType::CrouchDown &&
        Action != ActionType::Spindash &&
        Action != ActionType::LookUp &&
        Action != ActionType::RayGlide &&
        Action != ActionType::Glide &&
        Action != ActionType::GlideFallLand &&
        Action != ActionType::Climb &&
        Action != ActionType::ClimbRise &&
        Action != ActionType::Slide;

    if (Action == ActionType::Corkscrew)
        frc = 0x6;

    if (Action == ActionType::Skid) {
        if (DisplayFlip > 0) {
            if (GroundSpeed <= 0) {
                Action = ActionType::CancelableAnim;
                ChangeAnimation(AnimationMap[superflag + "Skid Turn"]);
            }
        }
        else {
            if (GroundSpeed >= 0) {
                Action = ActionType::CancelableAnim;
                ChangeAnimation(AnimationMap[superflag + "Skid Turn"]);
            }
        }
        if ((!InputLeft && GroundSpeed > 0) || (!InputRight && GroundSpeed < 0)) {
            Action = ActionType::Normal;
            ChangeAnimation(AnimationMap[superflag + "Walk"]);
        }
    }

    if (doLeftRight && InputLeft && InputAlarm == 0) {
        if (Action == ActionType::Rolling) {
            if (GroundSpeed > 0) {
                GroundSpeed -= 0x20;
            }
        }
        else {
            if (GroundSpeed >= 0x480 && Action != ActionType::Skid && Ground) {
                Action = ActionType::Skid;
                DisplayFlip = 1;
                Sound::Play(Sound::SFX_SKID);
            }
            else if (Action != ActionType::Skid)
                DisplayFlip = -1;

            if (Ground) {
                if (GroundSpeed > 0) {
                    GroundSpeed -= dec;
                }
                else if (GroundSpeed > -top) {
                    GroundSpeed -= acc;
                }
            }
            else {
                if (XSpeed > -top)
                    XSpeed -= air;
            }
        }
    }
    else if (doLeftRight && InputRight && InputAlarm == 0) {
        if (Action == ActionType::Rolling) {
            if (GroundSpeed < 0) {
                GroundSpeed += 0x20;
            }
        }
        else {
            if (GroundSpeed <= -0x480 && Action != ActionType::Skid && Ground) {
                Action = ActionType::Skid;
                DisplayFlip = -1;
                Sound::Play(Sound::SFX_SKID);
            }
            else if (Action != ActionType::Skid)
                DisplayFlip = 1;

            if (Ground) {
                if (GroundSpeed < 0) {
                    GroundSpeed += dec;
                }
                else if (GroundSpeed < top) {
                    GroundSpeed += acc;
                }
            }
            else {
                if (XSpeed < top)
                    XSpeed += air;
            }
        }
    }
    else {
        if (!doRollFriction)
            GroundSpeed -= min((int16_t)abs(GroundSpeed), frc) * IMath::sign(GroundSpeed);
    }
    if (doRollFriction)
        GroundSpeed -= min(abs(GroundSpeed), frc / 2) * IMath::sign(GroundSpeed);

    // Flip player when hitting left/right
    if (doLeftRight && InputAlarm == 0) {
        if (InputLeft) {
            if (Action != ActionType::Skid && Action != ActionType::Rolling)
                DisplayFlip = -1;
        }
        else if (InputRight) {
            if (Action != ActionType::Skid && Action != ActionType::Rolling)
                DisplayFlip = 1;
        }
    }

    if (Action == ActionType::Normal) {
        if (GroundSpeed == 0 && InputUp && Ground) {
            CameraLookTimer = 0;
            Action = ActionType::LookUp;
        }
    }

    if (Action == ActionType::CrouchDown) {
        if (!InputDown) {
            Action = ActionType::CancelableAnim;
        }
    }
    if (Action == ActionType::LookUp) {
        if (!InputUp)
            Action = ActionType::CancelableAnim;
    }

    if (Action == ActionType::Rolling) {
        if (!ManiaPhysics && abs(GroundSpeed) < 0x80)
            Action = ActionType::Normal;
        else if (ManiaPhysics && GroundSpeed == 0x00)
            Action = ActionType::Normal;
    }

    // int AngleMode0_Min = 0x20;

    if (InputAlarm > 0)
        InputAlarm--;

    int16_t X = this->X >> 16;
    int16_t Y = this->Y >> 16;

    WallLeft = false;
    WallRight = false;
    LastObject = NULL;

    HandleMonitors(); // handle breakable objects before collision, so that solids dont override breakability

	int SensorEFWidth = 10;
	bool AngelIslandTriLoopFlag = false;

	if (Scene->ZoneID == 1 && Scene->Act == 1 && AngleMode == 1 &&
		EZX > 0x2B40 && EZX < 0x2B54 &&
		EZY > 0x388 && EZY < 0x3F0) {
		AngelIslandTriLoopFlag = true;
		AngleIslandFlag = true;
		EZX = 0x2B60 - H / 2;
	}

	if (AngleIslandFlag && (EZY < 0x35B || GroundSpeed < 0 || YSpeed > 0 || !Ground)) {
		AngleIslandFlag = false;
		AngelIslandTriLoopFlag = false;
	}

	if (AngelIslandTriLoopFlag)
		SensorEFWidth = -1;

    if (Ground) {
        XSpeed = GroundSpeed * Cos[Angle];
        YSpeed = GroundSpeed * -Sin[Angle];

        ///*
        int angleOut;
        int SensorEFPos = Y;
        if (Angle == 0)
            SensorEFPos = Y + 8;
        if (DisplayAngle == 0 && AngleMode == 0)
            SensorEFPos = Y + 8;

        if (AngleMode != 0 && AngleMode != 2) {
            //SensorEFPos -= Y - X;
        }

        // Check Sensor E
        SensorE = -1;
        for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
            if (Scene->CollisionAt(X - (1 + x), SensorEFPos, &angleOut, (AngleMode + 3) & 3, this)) {
                if (angleOut == 0)
                    angleOut = AngleMode * 0x40;
                SensorE = x;
                break;
            }
        }
        if (SensorE <= SensorEFWidth && SensorE >= 0 && GroundSpeed * ModeCos[AngleMode] < 0 && (AngleMode == 0 || AngleMode == 2)) {
            this->X = ((X - 1 + (SensorEFWidth + 1 - SensorE)) << 16);
            X = this->X >> 16;
            WallLeft = true;
            GroundSpeed = 0;
            XSpeed = 0;
        }

        // Check Sensor F
        SensorF = -1;
        for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
            if (Scene->CollisionAt(X + (1 + x), SensorEFPos, &angleOut, (AngleMode + 1) & 3, this)) {
                if (angleOut == 0)
                    angleOut = AngleMode * 0x40;
                SensorF = x;
                break;
            }
        }
        if (SensorF <= SensorEFWidth && SensorF >= 0 && GroundSpeed * ModeCos[AngleMode] > 0 && (AngleMode == 0 || AngleMode == 2)) {
            this->X = ((X + 1 - (SensorEFWidth + 1 - SensorF)) << 16);
            X = this->X >> 16;
            WallRight = true;
            GroundSpeed = 0;
            XSpeed = 0;
        }
        //*/

        if (abs(GroundSpeed) < 0x280 && AngleMode != 0) {
            if (Action == ActionType::Rolling) {
                this->X += (int)(this->Sin[Angle] * (H / 2 - 16)) << 16;
                this->Y += (int)(this->Cos[Angle] * (H / 2 - 16)) << 16;
            }

            if (Angle <= 0xC0 && Angle >= 0x40) {
                if (Action == ActionType::Rolling)
                    Action = ActionType::Jumping;
                Ground = false;
                GroundSpeed = 0;
                Angle = 0;
                AngleMode = 0;
            }
            InputAlarm = 30;
        }
    }
    else {
        int angleOut;
        int SensorEFPos = Y;

        // Check Sensor E
        SensorE = -1;
        for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
            if (Scene->CollisionAt(X - 1 - x, SensorEFPos, &angleOut, (AngleMode + 3) & 3, this)) {
                if (angleOut == 0)
                    angleOut = AngleMode * 0x40;
                SensorE = x;
                break;
            }
        }
        if (SensorE <= SensorEFWidth && SensorE >= 0 && XSpeed < 0) {
            this->X = ((X - 1 + (SensorEFWidth + 1 - SensorE)) << 16);
            X = this->X >> 16;
            XSpeed = 0;
        }

        // Check Sensor F
        SensorF = -1;
        for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
            if (Scene->CollisionAt(X + 1 + x, SensorEFPos, &angleOut, (AngleMode + 3) & 3, this)) {
                if (angleOut == 0)
                    angleOut = AngleMode * 0x40;
                SensorF = x;
                break;
            }
        }
        if (SensorF <= SensorEFWidth && SensorF >= 0 && XSpeed > 0) {
            this->X = ((X + 1 - (SensorEFWidth + 1 - SensorF)) << 16);
            X = this->X >> 16;
            XSpeed = 0;
        }

        if (Action != ActionType::InStream) {
            YSpeed += grv;
            if (YSpeed > 0x1000) YSpeed = 0x1000;

            if (YSpeed < 0x0 && YSpeed > -0x400) {
                XSpeed -= XSpeed / 0x20;
            }
        }
    }

    this->X += XSpeed << 8;
    this->Y += YSpeed << 8;
    if (Action == ActionType::InStream) {
        this->X += XSpeed << 8;
        this->Y += YSpeed << 8;
    }

    X = this->X >> 16;
    Y = this->Y >> 16;

    int angleOut;
    // int SensorEFWidth = 10;
    int SensorEFPos = Y;
    if (Angle == 0)
        SensorEFPos = Y + 8;
    if (DisplayAngle == 0 && AngleMode == 0)
        SensorEFPos = Y + 8;
    if (!Ground)
        SensorEFPos = Y;

    if (AngleMode != 0 && AngleMode != 2) {
        SensorEFPos -= Y - X;
    }

    bool extraCheck = false;

    // Check Sensor E
    CheckSensorE:
    SensorE = -1;
    if (AngleMode == 0 || AngleMode == 2) {
        for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
            if (Scene->CollisionAt(X - x, SensorEFPos, &angleOut, (AngleMode + 3) & 3, this)) {
                if (angleOut == 0)
                    angleOut = AngleMode * 0x40;
                SensorE = x;
                break;
            }
        }
        if (SensorE < 11 && SensorE >= 0 && XSpeed < 0 && ((DisplayAngle == 0 && AngleMode == 0) || Action == ActionType::InStream || !Ground || (Angle == 0) || (AngleMode == 2))) {
            this->X = (X + (11 - SensorE)) << 16;
            if (Action == ActionType::InStream)
                this->X -= (XSpeed << 9);
            X = this->X >> 16;
            if (SensorE == 0)
                goto CheckSensorE;
        }
    }
    else {
        for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
            if (Scene->CollisionAt(SensorEFPos, Y - x, &angleOut, (AngleMode + 3) & 3, this)) {
                if (angleOut == 0)
                    angleOut = AngleMode * 0x40;
                SensorE = x;
                break;
            }
        }
        if (SensorE < 11 && SensorE >= 0 && YSpeed < 0) {
            this->Y = (Y + (11 - SensorE)) << 16;
            Y = this->Y >> 16;
            if (AngleMode == 1)
                GroundSpeed = 0;
            if (SensorE == 0)
                goto CheckSensorE;
        }
    }

    // Check Sensor F
    CheckSensorF:
    SensorF = -1;
    if (AngleMode == 0 || AngleMode == 2) {
        for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
            if (Scene->CollisionAt(X + x, SensorEFPos, &angleOut, (AngleMode + 1) & 3, this)) {
                if (angleOut == 0)
                    angleOut = AngleMode * 0x40;
                SensorF = x;
                break;
            }
        }
        if (SensorF < 11 && SensorF >= 0 && XSpeed > 0 && ((DisplayAngle == 0 && AngleMode == 0) || Action == ActionType::InStream || !Ground || (Angle == 0) || (AngleMode == 2))) {
            this->X = (X - (11 - SensorF)) << 16;
            if (Action == ActionType::InStream)
                this->X -= (XSpeed << 9);
            X = this->X >> 16;
            if (SensorF == 0)
                goto CheckSensorF;
        }
    }
    else {
        for (int x = 0; x <= SensorEFWidth && DoCollision; x++) {
            if (Scene->CollisionAt(SensorEFPos, Y + x, &angleOut, (AngleMode + 1) & 3, this)) {
                if (angleOut == 0)
                    angleOut = AngleMode * 0x40;
                SensorF = x;
                break;
            }
        }
        if (SensorF < 11 && SensorF >= 0 && YSpeed > 0) {
            this->Y = (Y - (11 - SensorF)) << 16;
            Y = this->Y >> 16;
            if (AngleMode == 3)
                GroundSpeed = 0;
            if (SensorF == 0)
                goto CheckSensorF;
        }
    }

    if (Action == ActionType::InStream && SensorEFPos == Y) {
        SensorEFPos = Y - 8;
        goto CheckSensorE;
    }

    int SensorLength = H / 2;
    if (Ground) {
        SensorLength += 16;
    }

    if ((Action != ActionType::Jumping || YSpeed < 0) && ShieldAction) {
        ShieldAction = false;
    }

    int SensorABCDWidth = 9;
    if (Action == ActionType::Jumping ||
        Action == ActionType::Rolling ||
        Action == ActionType::Spring)
        SensorABCDWidth = 7;

    HandleSprings();

    CheckSensorsAB:
    // Check Sensor A
    SensorA = -1;
    int SensorA_Angle = -1;
	Object* lastObj = NULL;
    for (int y = 0; y <= SensorLength && DoCollision; y++) {
        if (Scene->CollisionAt(
            X - SensorABCDWidth * ModeCos[AngleMode] + y * ModeSin[AngleMode],
            Y + SensorABCDWidth * ModeSin[AngleMode] + y * ModeCos[AngleMode], &SensorA_Angle, AngleMode, this)) {
            if (!SensorA_Angle)
                SensorA_Angle = ((4 - AngleMode) & 0x3) * 0x40;
            SensorA = y;
            break;
        }
    }
    if (SensorA == 0) SensorA = -1;

	if (LastObject)
		lastObj = LastObject;

    // Check Sensor B
    SensorB = -1;
    int SensorB_Angle = -1;
    for (int y = 0; y <= SensorLength && DoCollision; y++) {
        if (Scene->CollisionAt(
            X + SensorABCDWidth * ModeCos[AngleMode] + y * ModeSin[AngleMode],
            Y - SensorABCDWidth * ModeSin[AngleMode] + y * ModeCos[AngleMode], &SensorB_Angle, AngleMode, this)) {
            if (!SensorB_Angle)
                SensorB_Angle = ((4 - AngleMode) & 0x3) * 0x40;
            SensorB = y;
            break;
        }
    }
    if (SensorB == 0) SensorB = -1;

	if (!LastObject)
		LastObject = lastObj;

    // Handle falling and ground reacquisition
    if (Ground) {
		if (AngleIslandFlag && SensorEFWidth == -1 && AngelIslandTriLoopFlag) {
			Angle = 0xC0;
			AngleMode = 1;
			Ground = true;
			EZX = 0x2B60 - H / 2;
			goto SkipRepositioning;
		}

        if (SensorA == -1 && SensorB == -1) {
            XSpeed = GroundSpeed * Cos[Angle];
            YSpeed = GroundSpeed * -Sin[Angle];

            Ground = false;
            if (Action == ActionType::Rolling) {
                JumpVariable = 2;
                Action = ActionType::Jumping;
                this->X += (int)(this->Sin[Angle] * (H / 2 - 16)) << 16;
                this->Y += (int)(this->Cos[Angle] * (H / 2 - 16)) << 16;
            }
            Angle = 0;
            AngleMode = 0;
            ShieldUsable = false;

            if (Action == ActionType::Skid) {
                Action = ActionType::Normal;
                ChangeAnimation(AnimationMap[superflag + "Air Walk"]);
            }
        }

        int ang = 0;
        int value = 0xFF;
        if (SensorA == -1 && SensorB != -1) {
            value = SensorB;
            ang = SensorB_Angle;
        }
        else if (SensorA != -1 && SensorB == -1) {
            value = SensorA;
            ang = SensorA_Angle;
        }
        else if (SensorA != -1 && SensorB != -1) {
            if (SensorA < SensorB) {
                value = SensorA;
                ang = SensorA_Angle;
            }
            else {
                value = SensorB;
                ang = SensorB_Angle;
            }
        }
        if (value != 0xFF) {
            if (LastObject && !extraCheck) {
                this->X += (LastObject->XSpeed) << 8;
                if (LastObject->XSpeed != 0) {
                    if (XSpeed == 0) {
                        if (LastObject->XSpeed < 0)
                            XSpeed = -1;
                        else
                            XSpeed = 1;
                    }
                    extraCheck = true;
                    goto CheckSensorE;
                }
            }

            if (true) {
                if (AngleMode == 0)
                    this->Y = (Y + value - H / 2) << 16;
                else if (AngleMode == 1)
					this->X = (X + value - H / 2) << 16;
                else if (AngleMode == 2)
                    this->Y = (Y - value + H / 2) << 16;
                else if (AngleMode == 3)
                    this->X = (X - value + H / 2) << 16;

                if (GroundSpeed != 0)
                    Angle = ang;
            }
        }

        if (AngleMode == 0) {
            if (Angle < 0xE0 && Angle > 0x80) // to prevent bug
                AngleMode = 1;
            else if (Angle > 0x20 && Angle < 0x80)
                AngleMode = 3;
        }
        else if (AngleMode == 1) {
            if (Angle < 0xA0)
                AngleMode = 2;
            else if (Angle > 0xDC && GroundSpeed < 0)
                AngleMode = 0;
        }
        else if (AngleMode == 2) {
            if (Angle < 0x60)
                AngleMode = 3;
            else if (Angle > 0xA0)
                AngleMode = 1;
        }
        else if (AngleMode == 3) {
            if (Angle < 0x24 && GroundSpeed > 0)           // TODO: fix
                AngleMode = 0;
            else if (Angle > 0x60)
                AngleMode = 2;
        }

        // make sure when exporting/porting S3 levels that angles like FC don't get put on the sides
        // only ones above 45 degrees!

        if (!extraCheck) {
            extraCheck = true;
            //goto CheckSensorsAB;
        }
    }
    else {
        int hH = this->H / 2;
        bool Landed = false;
        if (SensorA == -1 && SensorB != -1) {
            if (this->Y > (Y + SensorB - hH) << 16) {
                if (Action == ActionType::InStream || YSpeed > 0) {
                    this->Y = (Y + SensorB - hH) << 16;
                    Angle = SensorB_Angle;
                    Landed = true;
                }
            }
        }
        else if (SensorA != -1 && SensorB == -1) {
            if (this->Y > (Y + SensorA - hH) << 16) {
                if (Action == ActionType::InStream || YSpeed > 0) {
                    this->Y = (Y + SensorA - hH) << 16;
                    Angle = SensorA_Angle;
                    Landed = true;
                }
            }
        }
        else if (SensorA != -1 && SensorB != -1) {
            if (SensorA < SensorB) {
                if (this->Y > (Y + SensorA - hH) << 16) {
                    if (Action == ActionType::InStream || YSpeed > 0) {
                        this->Y = (Y + SensorA - hH) << 16;
                        Angle = SensorA_Angle;
                        Landed = true;
                    }
                }
            }
            else {
                if (this->Y > (Y + SensorB - hH) << 16) {
                    if (Action == ActionType::InStream || YSpeed > 0) {
                        this->Y = (Y + SensorB - hH) << 16;
                        Angle = SensorB_Angle;
                        Landed = true;
                    }
                }
            }
        }

        if (Landed) {
            JumpVariable = 0;
            EnemyCombo = 0;
        }

        if ((SensorA == 0 || SensorB == 0) && Landed) {
            goto CheckSensorsAB;
        }
        if (Action == ActionType::InStream || Action == ActionType::InStreamGrab)
            Angle = 0;

        if (DropDashRev > 0 && InputJumpHold) {
            DropDashRev++;
        }
        if (DropDashRev > 0 && !InputJumpHold) {
            DropDashRev = 0;
        }
        if (DropDashRev == 21) {
            Sound::Play(Sound::SFX_DROPDASHREADY);
        }

        if (Landed && Action != ActionType::InStream && Action != ActionType::InStreamGrab) {
            if (Shield == ShieldType::Bubble && ShieldAction) {
                Ground = false;
                ShieldUsable = true;
                ShieldAction = false;
                if (Underwater)
                    YSpeed = -0x400;
                else
                    YSpeed = -0x780;
                JumpVariable = 1;
            }
            else if (Action == ActionType::GlideFall) {
                XSpeed = 0;
                GroundSpeed = 0;
                if (InputDown) {
                    Action = ActionType::CrouchDown;
                }
                else {
                    Action = ActionType::GlideFallLand;
                }
                Ground = true;
            }
            else if (Action == ActionType::Victory) {
                XSpeed = 0;
                GroundSpeed = 0;
                Ground = true;
            }
            else {
                if (Angle >= 0xF0 && Angle <= 0xFF)
                    GroundSpeed = XSpeed;
                else if (Angle >= 0x00 && Angle <= 0x0F)
                    GroundSpeed = XSpeed;
                else if (abs(XSpeed) > YSpeed) {
                    GroundSpeed = XSpeed;
                }
                else {
                    if (Angle >= 0xE0 && Angle <= 0xEF)
                        GroundSpeed = YSpeed / 2 * -(int)IMath::sign(Sin[Angle]);
                    else if (Angle >= 0x10 && Angle <= 0x1F)
                        GroundSpeed = YSpeed / 2 * -(int)IMath::sign(Sin[Angle]);

                    else if (Angle >= 0xC0 && Angle <= 0xDF)
                        GroundSpeed = YSpeed * -(int)IMath::sign(Sin[Angle]);
                    else if (Angle >= 0x20 && Angle <= 0x3F)
                        GroundSpeed = YSpeed * -(int)IMath::sign(Sin[Angle]);
                }


                Ground = true;
                ShieldUsable = true;
                YSpeed = 0;
				EZY -= (OrigH - H) / 2; H = OrigH;

                if (Action == ActionType::Peril) {
                    Action = ActionType::Normal;
                }
                else if (Action == ActionType::Slide) {
                    Action = ActionType::Normal;
                }
                else if (Action == ActionType::Glide) {
                    Action = ActionType::GlideSlide;
                }
                else if (Action == ActionType::Hurt) {
                    Invincibility = InvincibilityType::Temporary;
                    InvincibilityTimer = 120;
                    Action = ActionType::Normal;
                    GroundSpeed = 0;
                    XSpeed = 0;
                    isHurt = false;
                }
                else {
                    if (DropDashRev >= 21 && Action == ActionType::Jumping) {
                        Sound::Play(Sound::SFX_DROPDASH);

                        Explosion* dropdashdust;
                        dropdashdust = new Explosion();
                        dropdashdust->G = G;
                        dropdashdust->App = App;
                        dropdashdust->CurrentAnimation = 2;
                        dropdashdust->FlipX = DisplayFlip < 0;
                        dropdashdust->Active = true;
                        dropdashdust->Sprite = Scene->ExplosionSprite;
                        dropdashdust->X = X;
                        dropdashdust->Y = Y + H / 2;
                        Scene->Explosions.push_back(dropdashdust);

                        CameraLockTimer = 8;

                        Action = ActionType::Rolling;

                        int dashspeed = 0x800;
                        int maxspeed = 0xC00;

                        if (InputRight)
                            DisplayFlip = 1;
                        if (InputLeft)
                            DisplayFlip = -1;

                        if (SuperForm) {
                            dashspeed = 0xC00;
                            maxspeed = 0xD00;

                            Scene->ShakeTimer = 20;
                        }
                        else {
                            dashspeed = 0x800;
                            maxspeed = 0xC00;
                        }

                        if (DisplayFlip < 0) {
                            if (XSpeed <= 0) {
                                GroundSpeed = max(-maxspeed, (GroundSpeed >> 2) - dashspeed);
                                goto LABEL_25;
                            }
                            if (Angle != 0) {
                                GroundSpeed = (GroundSpeed >> 1) - dashspeed;
                                goto LABEL_25;
                            }
                            dashspeed = -dashspeed;
                        }
                        else {
                            if (XSpeed >= 0) {
                                GroundSpeed = min(maxspeed, dashspeed + (GroundSpeed >> 2));
                                goto LABEL_25;
                            }
                            if (Angle != 0) {
                                GroundSpeed = dashspeed + (GroundSpeed >> 1);
                                goto LABEL_25;
                            }
                        }
                        GroundSpeed = dashspeed;
                        LABEL_25:
                        DropDashRev = 0;
                    }
                    else if ((ObjectControlled & 1) == 0) {
                        Action = ActionType::Normal;
						EZY -= (OrigH - H) / 2; H = OrigH;
					}
                }

                DropDashRev = 0;
            }
        }

        // Check Sensor C
        SensorC = -1;
        int SensorC_Angle;
        for (int y = 0; y <= SensorLength && DoCollision; y++) {
            if (Scene->CollisionAt(
                X - SensorABCDWidth * ModeCos[AngleMode] - y * ModeSin[AngleMode],
                Y - SensorABCDWidth * ModeSin[AngleMode] - y * ModeCos[AngleMode], &SensorC_Angle, (AngleMode + 2) & 0x3, this)) {
                SensorC = y;
                break;
            }
        }

        // Check Sensor D
        SensorD = -1;
        int SensorD_Angle;
        for (int y = 0; y <= SensorLength && DoCollision; y++) {
            if (Scene->CollisionAt(
                X + SensorABCDWidth * ModeCos[AngleMode] - y * ModeSin[AngleMode],
                Y + SensorABCDWidth * ModeSin[AngleMode] - y * ModeCos[AngleMode], &SensorD_Angle, (AngleMode + 2) & 0x3, this)) {
                SensorD = y;
                break;
            }
        }

        int value = 0xFF;
        int ang = 40;
        if (SensorC == -1 && SensorD != -1) {
            value = SensorD;
            ang = SensorD_Angle;
        }
        else if (SensorC != -1 && SensorD == -1) {
            value = SensorC;
            ang = SensorC_Angle;
        }
        else if (SensorC != -1 && SensorD != -1) {
            if (SensorC < SensorD) {
                value = SensorC;
                ang = SensorC_Angle;
            }
            else {
                value = SensorD;
                ang = SensorD_Angle;
            }
        }

        if (value != 0xFF) {
            if (YSpeed < 0) {
                if (Action != ActionType::InStream) {
                    if (ang >= 0xA0 && ang <= 0xBF) {
                        Angle = ang;
                        AngleMode = 1;
                        GroundSpeed = YSpeed * -(int)IMath::sign(Sin[Angle]);
                        Ground = true;
                        ShieldUsable = true;
                        Action = ActionType::Normal;
						EZY += (OrigH - H) / 2; H = OrigH;
                        DisplayAngle = Angle << 8;
                    }
                    else if (ang >= 0x40 && ang <= 0x5F) {
                        Angle = ang;
                        AngleMode = 3;
                        GroundSpeed = YSpeed * -(int)IMath::sign(Sin[Angle]);
                        Ground = true;
                        ShieldUsable = true;
                        Action = ActionType::Normal;
						EZY += (OrigH - H) / 2; H = OrigH;
                        DisplayAngle = Angle << 8;
                    }
                    else {
                        YSpeed = 0;
                    }
                }
                else {
                    if (ang >= 0xA0 && ang <= 0xBF) {
                        this->X -= 2 << 16;
                    }
                    else if (ang >= 0x40 && ang <= 0x5F) {
                        this->X += 2 << 16;
                    }
                    else {
                        YSpeed = 0;
                    }
                }
                FlyFlag = 0x8;
                this->Y = (Y - value + H / 2) << 16;
            }
        }
    }

	SkipRepositioning:

    if (Action == ActionType::Victory) {
        Angle = 0;
        AngleMode = 0;
    }

    if (InputDown && Ground && Action != ActionType::Slide) {
        if (ManiaPhysics) {
            if (Action == ActionType::Normal) {
                if (GroundSpeed == 0 && abs((int8_t)Angle) < 0x10) {
                    Action = ActionType::CrouchDown;
                }
                else if (abs(GroundSpeed) >= 0x90) {
                    Action = ActionType::Rolling;
                    Sound::Play(Sound::SFX_ROLL);
                }
            }
        }
        else {
            if (Action == ActionType::Normal) {
                if (abs(GroundSpeed) > 0x108) {
                    Action = ActionType::Rolling;
                    Sound::Play(Sound::SFX_ROLL);
                }
                else {
                    Action = ActionType::CrouchDown;
                }
            }
            else {
                if (abs(GroundSpeed) > 0x88) {
                    if (Action != ActionType::Rolling)
                        Sound::Play(Sound::SFX_ROLL);
                    Action = ActionType::Rolling;
                }
            }
        }
    }

    if (Ground) {
        JumpVariable = 0;
    }

    // Double-jumps, etc...
    if (InputJump) {
        if (Action == ActionType::Normal ||
            Action == ActionType::Rolling ||
            Action == ActionType::LookUp ||
            Action == ActionType::Skid ||
            Action == ActionType::Spinning ||
            Action == ActionType::Slide) {
            if (Ground || (ObjectControlled <= 0x7F && ObjectControlled > 0x00)) {
                if (ObjectControlled <= 0x7F && ObjectControlled > 0x00) {
                    ObjectControlled = 0;
                    GroundSpeed >>= 1;
                    EZY -= 4;
                }

                Jump();
            }
        }
        else if (Action == ActionType::CrouchDown) {
            Action = ActionType::Spindash;
            SpindashRev = 0x200;
            Vibrate(VibrationType::SpindashRev);
            Sound::Play(Sound::SFX_SPINDASHREV);
        }
        else if (Action == ActionType::Spindash) {
            Vibrate(VibrationType::SpindashRev);
            SpindashRev += 0x200;
            if (SpindashRev > 0x800)
                SpindashRev = 0x800;
            ChangeAnimation2(AnimationMap[superflag + "Spindash"]);
            Sound::Play(Sound::SFX_SPINDASHREV);
        }
        else if (Action == ActionType::Jumping && JumpVariable == 1) {
            if (HyperForm) {
                if (ShieldUsable && Character == CharacterType::Sonic) {
                    if (InputUp) {
                        YSpeed = -0x800;
                    }
                    else if (InputDown) {
                        // Do nothing.
                        if (true) {
                            if (DropDashRev == 0)
                                DropDashRev = 1;
                        }
                    }
                    else {
                        XSpeed = 0x800 * DisplayFlip;
                        YSpeed = 0;
                        CameraLockTimer = 16;
                    }
                    ShieldUsable = false;
                }
            }
            else if (Character == CharacterType::Sonic) {
                /*
                if no shield,
                    then instashield
                */
                if (ShieldUsable) {
                    if ((SuperForm || HyperForm || Shield == ShieldType::None)) {
                        if (!InputUp) {
                            if (DropDashRev == 0)
                                DropDashRev = 1;
                        }
                        else if (!SuperForm && !HyperForm) {
                            if (Rings >= 50 && !Scene->StopTimer) {
                                Action = ActionType::Transform;
                                SuperFormAnim = SuperFormAnimType::Transforming;
                                SuperFormTimer = 0;

                                Sound::Play(Sound::SFX_TRANSFORM);
                            }
                        }
                        ShieldUsable = false;
                    }
                    else if (Shield == ShieldType::Fire) {
                        XSpeed = 0x800 * DisplayFlip;
                        YSpeed = 0;
                        CameraLockTimer = 16;
                        Sound::Play(Sound::SFX_SHIELD_FIRE_DASH);
                    }
                    else if (Shield == ShieldType::Bubble) {
                        XSpeed = 0;
                        YSpeed = 0x800;
                        ShieldAction = true;
                        Sound::Play(Sound::SFX_SHIELD_BUBBLE_BOUNCE);
                    }
                    else if (Shield == ShieldType::Electric) {
                        YSpeed = -0x580;
                        Sound::Play(Sound::SFX_SHIELD_ELECTRIC_JUMP);
                    }
                    else if (Shield == ShieldType::Basic) {
                        // Do nothing.
                    }

                    ShieldUsable = false;
                }
            }
            else if (Character == CharacterType::Tails) {
                if (!InputUp) {
                    Action = ActionType::Fly;
                    FlyFlag = 0x8;
                    FlyTimer = FlyTimerMax;
                }
                else if (!SuperForm && !HyperForm) {
                    if (Rings >= 50 && !Scene->StopTimer) {
                        Action = ActionType::Transform;
                        SuperFormAnim = SuperFormAnimType::Transforming;
                        SuperFormTimer = 0;

                        Sound::Play(Sound::SFX_TRANSFORM);
                    }
                }
            }
            else if (Character == CharacterType::Knuckles) {
                if (!InputUp) {
                    Action = ActionType::Glide;
                    XSpeed = DisplayFlip * 0x400;
                    if (YSpeed < 0)
                        YSpeed = 0;
                }
                else if (!SuperForm && !HyperForm) {
                    if (Rings >= 50 && !Scene->StopTimer) {
                        Action = ActionType::Transform;
                        SuperFormAnim = SuperFormAnimType::Transforming;
                        SuperFormTimer = 0;

                        Sound::Play(Sound::SFX_TRANSFORM);
                    }
                }
            }
            else if (Character == CharacterType::Ray) {
                // sub_4C8DF0
				if (JumpVariable == 1) {
					Action = ActionType::RayGlide;

					int adjustedXSpeed = XSpeed - (XSpeed / 8);
					XSpeed = adjustedXSpeed;

					int maxx = 0x300;
					if (Underwater)
						maxx = 0x180;

					if (DisplayFlip < 0) {
						if (XSpeed > -maxx)
							XSpeed = -maxx;
					}
					else {
						if (XSpeed < maxx)
							XSpeed = maxx;
					}

					if ((DisplayFlip < 0 || !InputRight) && (DisplayFlip > 0 || !InputLeft)) {
						ChangeAnimation(AnimationMap["Ray Fly Up"], 3);

						Angle = 1; // Facing Up

						bool goingLeft = (XSpeed >> 1) < 0;
						XSpeed >>= 1;

						int v8 = XSpeed;
						int v9 = XSpeed;
						if (goingLeft)
							v9 = -v9;
						int v10 = XSpeed;

						if (v8 < 0) {
							v10 = -v8;
							if (v8 < 0)
								v8 = -v8;
						}
						int v11 = -((v9 >> 1) + (v10 >> 2) + (v8 >> 4)) >> Underwater;
						if (v11 > 0x400)
							v11 = 0x400;

						GlideSpeedStore = v11;
					}
					else {
						ChangeAnimation(AnimationMap["Ray Fly Down"], 3);
						Angle = 0; // Facing Down
						GlideSpeedStore = 0;
					}

					YSpeed >>= 1;
					GlideTurnCos = 0x40;
					MaxGlideSpeed = abs(XSpeed);
					RayBoostCount = 0x100;
				}
            }
        }
    }

    if (Action == ActionType::Spindash) {
        GroundSpeed = 0;
        if (!InputDown) {
            Action = ActionType::Rolling;
            GroundSpeed = DisplayFlip * (SpindashRev / 2 + 0x800);
            CameraLockTimer = 16;

            Sound::Play(Sound::SFX_SPINDASH);
        }
        SpindashRev -= SpindashRev / 0x20;
    }

    if (Action == ActionType::Jumping && !InputJumpHold && YSpeed < rel && JumpVariable == 1)
        YSpeed = rel;

    if (Action == ActionType::Spring && YSpeed >= 0) {
        Action = ActionType::Normal;
        ChangeAnimation(AnimationMap[superflag + "Air Walk"]);
    }

    if (Action == ActionType::Skid || Action == ActionType::GlideSlide) {
        if (!Ground && Action == ActionType::Skid) {
            Action = ActionType::Normal;
        }
        else {
            if (Scene->Frame % 5 == 0 && GroundSpeed != 0 && Ground) {
                Explosion* skiddust;
                skiddust = new Explosion();
                skiddust->G = G;
                skiddust->App = App;
                skiddust->FlipX = false;
                skiddust->CurrentAnimation = 0;
                skiddust->Active = true;
                skiddust->Sprite = Scene->ExplosionSprite;
                skiddust->X = X;
                skiddust->Y = Y + H / 2 - 4;
                Scene->Explosions.push_back(skiddust);
            }
        }
    }

    HandlePathSwitchers();

    if (Action == ActionType::Fan)
        Action = ActionType::Normal;

    if (isHurt) {
        if (Action != ActionType::Hurt) {
            Invincibility = InvincibilityType::Temporary;
            InvincibilityTimer = 120;
            if (Ground)
                GroundSpeed = 0;
        }
    }

    if (CameraLockTimer > 0)
        CameraLockTimer--;

    if (InvincibilityTimer > 0)
        InvincibilityTimer--;
    else {
        if (Invincibility == InvincibilityType::Full)
            App->Audio->RemoveMusic(Sound::SoundBank[0xFF]);
        Invincibility = InvincibilityType::None;
    }

    if (SpeedSneakersTimer > 0)
        SpeedSneakersTimer--;
    else if (SpeedSneakersActive) {
        SpeedSneakersActive = false;
        App->Audio->RemoveMusic(Sound::SoundBank[0xFE]);
    }

    if (WaitTimer > 0)
        WaitTimer--;

    if (WaitTimer == 0) {
        WaitTimer = -1;

        if (Action == ActionType::Normal) {
            Action = ActionType::Bored1;
        }
    }

    if (RingAlarm > 0)
        RingAlarm--;

    if (Rings > 0) {
        if (SuperForm && Scene->Frame % 60 == 0)
            Rings--;
    }
    else {
        Deform();
    }

    if ((WallLeft && InputLeft) || (WallRight && InputRight)) {
        //if ((Scene->Frame & 0xF) == 0)
            //Sound::Play(Sound::SFX_PUSHING);
    }
    if (WaterRunning && (Scene->Frame & 0xF) == 0) {
        Sound::Play(Sound::SFX_WATERRUN);
    }

    // Beeps
    if (UnderwaterTimer == 1440 ||
        UnderwaterTimer == 1140 ||
        UnderwaterTimer == 840) {
        Sound::Play(Sound::SFX_UNDERWATER_BEEP); // , 1);
    }
	if (UnderwaterTimer == 750 && !Sidekick) {
		App->Audio->PushMusic(Sound::SoundBank[0xFD], false, 0);
    }
    if (UnderwaterTimer == 12 * 60 ||
        UnderwaterTimer == 10 * 60 ||
        UnderwaterTimer == 8 * 60 ||
        UnderwaterTimer == 6 * 60 ||
        UnderwaterTimer == 4 * 60 ||
        UnderwaterTimer == 2 * 60) {
        int number = (UnderwaterTimer / 120) - 1;
        BubbleCountdown* countdown = new BubbleCountdown();
        countdown->G = G;
        countdown->App = App;
        countdown->Scene = Scene;
        countdown->Number = number;
        countdown->FlipX = false;
        countdown->FlipY = false;
        countdown->Active = true;
        countdown->VisualLayer = 1;
        countdown->Sprite = Scene->WaterSprite;
        countdown->X = EZX - Scene->CameraX + 20;
        countdown->Y = EZY - Scene->CameraY - 20;
        Scene->Explosions.push_back(countdown);
    }

    if (Underwater && Shield != ShieldType::Bubble) {
        if (UnderwaterTimer > 0)
            UnderwaterTimer--;
        else
            Die(true);
    }
    else {
        UnderwaterTimer = 1800;
    }

    if (GrabTimer > 0)
        GrabTimer--;

    InputUp = IUp;
    InputDown = IDown;
    InputJump = IJump;
    InputLeft = ILeft;
    InputRight = IRight;
    InputJumpHold = IJumpHold;

	if (Scene->StopTimer && (SuperForm || HyperForm)) {
		Deform();
	}
	if (AngleIslandFlag) {
		EZX = 0x2B60 - H / 2;
		AngleMode = 1;
		Angle = 0xC0;
	}
}
void IPlayer::LateUpdate() {
	AnimationSpeedMult = 0x100;

    if (!Cutscene) {
        string superflag;
        if (SuperForm && Character == CharacterType::Sonic)
            superflag = "S_";

        if (Ground) {
            if (Action == ActionType::Rolling) {
                if (abs(GroundSpeed) < 0x500)
                    AnimationSpeedMult = abs(GroundSpeed);
                else
                    AnimationSpeedMult = 0x500;

                if (AnimationSpeedMult < 0x100)
                    AnimationSpeedMult = 0x100;

                ChangeAnimation(AnimationMap[superflag + "Jump"]);
            }
            else if (Action == ActionType::Victory) {
                ChangeAnimation(AnimationMap[superflag + "Victory"]);
            }
            else if (Action == ActionType::GlideSlide) {
                ChangeAnimation(AnimationMap["Glide Slide"], 0);
            }
            else if (Action == ActionType::GlideFallLand) {
                ChangeAnimation(AnimationMap["Glide Land"]);
            }
            else if (Action == ActionType::CrouchDown) {
                ChangeAnimation(AnimationMap[superflag + "Crouch"]);
                if (CurrentFrame >= 0x400)
                    CurrentFrame = 0x400;
            }
			else if (Action == ActionType::Spindash) {
				AnimationSpeedMult = 0x100;

                ChangeAnimation(AnimationMap[superflag + "Spindash"]);
            }
            else if (Action == ActionType::Skid) {
                ChangeAnimation(AnimationMap[superflag + "Skid"]);
            }
            else if (Action == ActionType::Bored1) {
				ChangeAnimation(AnimationMap[superflag + "Bored 1"]);
            }
            else if (Action == ActionType::LookUp) {
                ChangeAnimation(AnimationMap[superflag + "Look Up"]);
                if (CurrentFrame >= 0x400 && Character == CharacterType::Sonic)
                    CurrentFrame = 0x400;
                else if (CurrentFrame >= 0x500)
                    CurrentFrame = 0x500;
            }
            else if ((WallLeft && InputLeft) || (WallRight && InputRight)) {
                ChangeAnimation(AnimationMap[superflag + "Push"]);
            }
            else if (Action != ActionType::CancelableAnim) {
				if (abs(GroundSpeed) == 0x0 && (Angle <= 0x10 || Angle >= 0xF0)) {
                    bool below = !Scene->CollisionAt(EZX, EZY + H / 2 + 2, NULL, 0, this);
                    bool infront = (DisplayFlip > 0 && SensorB == -1) || (DisplayFlip < 0 && SensorA == -1);
                    bool behind = (DisplayFlip > 0 && SensorA == -1) || (DisplayFlip < 0 && SensorB == -1);

                    below &= Angle == 0;
                    infront &= Angle == 0;
                    behind &= Angle == 0;

					AnimationSpeedMult = 0x100;
                    if (below && infront) {
		                ChangeAnimation(AnimationMap[superflag + "Balance 1"]);
                        WaitTimer = 180;
                    }
                    else if (below && behind) {
		                ChangeAnimation(AnimationMap[superflag + "Balance 2"]);
                        WaitTimer = 180;
                    }
                    else
                        ChangeAnimation(AnimationMap[superflag + "Idle"]);
                }
                else if (abs(GroundSpeed) < 0x400) {
					AnimationSpeedMult = 0x200 * abs(GroundSpeed) / 0x400;
					if (AnimationSpeedMult < 0x100)
						AnimationSpeedMult = 0x100;

                    ChangeAnimation(AnimationMap[superflag + "Walk"]);
                }
                else if (abs(GroundSpeed) < 0x600) {
                    AnimationSpeedMult = 0x200 * abs(GroundSpeed) / 0x600;

                    ChangeAnimation(AnimationMap[superflag + "Jog"]);
                }
                else if (abs(GroundSpeed) < 0xC00) {
                    AnimationSpeedMult = 0x200 * abs(GroundSpeed) / 0xC00;

                    ChangeAnimation(AnimationMap[superflag + "Run"], 0x100);
                }
                else {
                    ChangeAnimation(AnimationMap[superflag + "Dash"]);
                }
            }
        }
        else {
            if (Action == ActionType::Fan)
                ChangeAnimation(AnimationMap[superflag + "Spring CS"]);
            else if (Action == ActionType::Jumping && DropDashRev > 20)
                ChangeAnimation(AnimationMap[superflag + "Dropdash"]);
            else if (Action == ActionType::Jumping) {
                if (abs(GroundSpeed) < 0x500)
                    AnimationSpeedMult = abs(GroundSpeed);
                else
                    AnimationSpeedMult = 0x500;

                if (AnimationSpeedMult < 0x100)
                    AnimationSpeedMult = 0x100;

                ChangeAnimation(AnimationMap[superflag + "Jump"]);
            }
            else if (Action == ActionType::Spring) {
                if (ManiaPhysics)
                    ChangeAnimation(AnimationMap[superflag + "Spring Twirl"]);
                else
                    ChangeAnimation(AnimationMap[superflag + "Spring Diagonal"]);
            }
            else if (Action == ActionType::Transform) {
                ChangeAnimation(AnimationMap["Transform"]);
            }
            //else if (Action == ActionType::Normal && !ObjectControlled)
                //ChangeAnimation(AnimationMap[superflag + "Air Walk"]);
        }

        // Overriding animations
        if (Action == ActionType::Peril) {
            if (AnimationMap["Flume"])
                ChangeAnimation(AnimationMap[superflag + "Flume"]);
            else
                ChangeAnimation(AnimationMap[superflag + "Hurt"], 0x300);
        }
        else if (Action == ActionType::Slide) {
            if (AnimationMap["Flume"])
                ChangeAnimation(AnimationMap[superflag + "Flume"]);
            else
                ChangeAnimation(AnimationMap[superflag + "Hurt"], 0x300);
        }
        else if (Action == ActionType::Hurt) {
            ChangeAnimation(AnimationMap[superflag + "Hurt"]);
        }
        else if (Action == ActionType::InStream) {
            ChangeAnimation(AnimationMap[superflag + "Fan"]);
            DisplayFlip = 1;
        }
        else if (Action == ActionType::InStreamGrab) {
            ChangeAnimation(AnimationMap[superflag + "Cling"]);
            DisplayFlip = 1;
        }
        else if (Action == ActionType::Glide) {
            ChangeAnimation(AnimationMap["Glide"], 0x500);
            //if (CurrentFrame >= 0x400)
                //CurrentFrame = 0x400;
        }
        else if (Action == ActionType::GlideFall) {
            ChangeAnimation(AnimationMap["Glide Drop"]);
        }
        else if (Action == ActionType::Climb) {
            if (YSpeed == 0)
                ChangeAnimation(AnimationMap["Climb Idle"]);
            else if (YSpeed < 0)
                ChangeAnimation(AnimationMap["Climb Up"]);
            else
                ChangeAnimation(AnimationMap["Climb Down"]);
        }
        else if (Action == ActionType::ClimbRise) {
            ChangeAnimation(AnimationMap["Ledge Pullup"]);
        }
        else if (Action == ActionType::Dead) {
            if (Underwater)
                ChangeAnimation(AnimationMap[superflag + "Drown"]);
            else
                ChangeAnimation(AnimationMap[superflag + "Die"]);
        }
        else if (Action == ActionType::Grab) {
            ChangeAnimation(AnimationMap[superflag + "Hang"]);
        }
        else if (Action == ActionType::Conveyor) {
            if (abs(XSpeed) == 0x200) {
                ChangeAnimation(AnimationMap[superflag + "Shimmy Idle"]);
            }
            else if (abs(XSpeed) > 0x200) {
                ChangeAnimation(AnimationMap[superflag + "Shimmy Move"]);
                DisplayFlip = 1 * IMath::sign(XSpeed);
            }
            else {
                ChangeAnimation(AnimationMap[superflag + "Shimmy Move"]);
                DisplayFlip = -1 * IMath::sign(XSpeed);
            }
        }
        else if (Action == ActionType::Spinning) {
            ChangeAnimation2(AnimationMap[superflag + "Twister"], (Scene->Frame >> 2) % 24);
        }
        else if (Action == ActionType::Fly) {
            if (Underwater) {
                if (FlyTimer > 0)
                    ChangeAnimation(AnimationMap["Swim"]);
                else
                    ChangeAnimation(AnimationMap["Swim Tired"]);
            }
            else {
                if (FlyTimer > 0)
                    ChangeAnimation(AnimationMap["Fly"]);
                else
                    ChangeAnimation(AnimationMap["Fly Tired"]);
            }
        }
        else if (Action == ActionType::Respawn) {
            if (Character == CharacterType::Tails)
                ChangeAnimation(AnimationMap["Fly"]);
            else if (Character == CharacterType::Knuckles)
				ChangeAnimation(AnimationMap["Glide"]);
			else if (Character == CharacterType::Ray)
				ChangeAnimation(AnimationMap["Ray Fly Up"]);
            else
                ChangeAnimation(47);
        }
    }

	ISprite::Animation animation = Sprites[0]->Animations[CurrentAnimation];

	/*
	if (animation.AnimationSpeed > 2)
		CurrentFrame += (animation.AnimationSpeed * AnimationSpeedMult) >> 8;
	else if (animation.Frames[CurrentFrame / 0x100].Duration != 0)
		CurrentFrame += ((0x100 * animation.AnimationSpeed * AnimationSpeedMult) >> 8) / animation.Frames[CurrentFrame / 0x100].Duration;
    else if (Action == ActionType::Transform)
        CurrentFrame += 0x100;
	*/

	if (animation.AnimationSpeed > 0 && animation.Frames[CurrentFrame / 0x100].Duration != 0) {
		CurrentFrame += ((0x100 * animation.AnimationSpeed * AnimationSpeedMult) >> 8) / animation.Frames[CurrentFrame / 0x100].Duration;
	}
	else if (Action == ActionType::Transform)
		CurrentFrame += 0x100;

    if (Action == ActionType::ClimbRise) {
        int offsetsX[7] = { 0x00, 0x00,  0x05,  0x0A,  0x0F,  0x14,  0x14 };
        int offsetsY[7] = { 0x01, 0x01, -0x07, -0x0F, -0x11, -0x1F, -0x1D };

        int reindex = (CurrentFrame) >> 8;
        if (reindex < 7) {
            X = 0;
            Y = 0;
            EZX = StoredX + offsetsX[reindex] * DisplayFlip;
            EZY = StoredY + offsetsY[reindex];
        }
        if (reindex == 8)
            Action = ActionType::Normal;
    }
    else if (Action == ActionType::GlideSlide) {
        if (GroundSpeed != 0) {
            if ((CurrentFrame >> 8) >= 3)
                CurrentFrame = 0x200;
        }
        else {
            if ((CurrentFrame >> 8) >= animation.FrameCount - 1) {
                CurrentFrame = (animation.FrameCount - 1) << 8;
                Action = ActionType::Normal;
            }
        }
    }

	if (CurrentFrame >= animation.FrameCount * 0x100) {
		// Actions that cancel after animation is finished

		AnimationDone = 1;

		bool loop = true;

		if (Action == ActionType::CancelableAnim)
			Action = ActionType::Normal;
		else if (Action == ActionType::Bored1) {
            Action = ActionType::Normal;

            WaitTimer = 180;
		}
        else if (Action == ActionType::GlideFallLand) {
            loop = false;
            Action = ActionType::Normal;
            ChangeAnimation(AnimationMap["Idle"]);
        }
        else if (Action == ActionType::ClimbRise) {
            loop = false;
            Action = ActionType::Normal;
            CurrentFrame = animation.FrameCount * 0x100 - 0x100;
        }

        if (Action == ActionType::Transform) {
            SuperForm = true;
            Action = ActionType::Normal;
            SuperFormAnim = SuperFormAnimType::Super;
            XSpeed = 0;
            YSpeed = 0;
            ChangeAnimation(AnimationMap["Jump"]);

            loop = false;
            CurrentFrame = 0;
        }

		if (loop) {
			if (false)
				CurrentFrame = animation.FrameCount * 0x100 - 0x100;
			else
				CurrentFrame = animation.FrameToLoop * 0x100;
		}
	}



    if (Shield != ShieldType::None) {
        ISprite::Animation ani = SpriteShields2->Animations[0];

        if (Shield == ShieldType::Fire)
            ani = SpriteShields->Animations[2];
        else if (Shield == ShieldType::Electric)
            ani = SpriteShields->Animations[3];
        else if (Shield == ShieldType::Bubble)
            ani = SpriteShields->Animations[1];
        else if (Shield == ShieldType::Basic)
            ani = SpriteShields->Animations[0];

    	if (ShieldFrame / 0x100 >= ani.FrameCount - 1) {
            ShieldFrame = ani.FrameToLoop * 0x100;
    	}

        if (ani.AnimationSpeed > 2)
            ShieldFrame += ani.AnimationSpeed;
        else if (ani.Frames[ShieldFrame / 0x100].Duration != 0)
            ShieldFrame += 0x100 / ani.Frames[ShieldFrame / 0x100].Duration;
    }

    if (Action == ActionType::Spindash) {
        ISprite::Animation ani = SpriteDashDust->Animations[1];

    	if (DashFrame / 0x100 >= ani.FrameCount - 1) {
            DashFrame = ani.FrameToLoop * 0x100;
    	}

        if (ani.AnimationSpeed > 2)
            DashFrame += ani.AnimationSpeed;
        else if (ani.Frames[DashFrame / 0x100].Duration != 0)
            DashFrame += 0x100 / ani.Frames[DashFrame / 0x100].Duration;
    }

    DisplayX = X >> 16;
    DisplayY = Y >> 16;

    int palWhere;
    Uint32 *palSuper, *palNormal, *palSuperHCZ, *palNormalHCZ, *palSuperPulse, *palSuperPulseHCZ;

    if (Character == CharacterType::Sonic) {
        palWhere = 0x40;
        palSuper = SonicPaletteSuper;
        palNormal = SonicPaletteNormal;
        palSuperHCZ = SonicPaletteSuperHCZ;
        palNormalHCZ = SonicPaletteNormalHCZ;
        palSuperPulse = SonicPaletteSuperPulse;
        palSuperPulseHCZ = SonicPaletteSuperPulseHCZ;
    }
    else if (Character == CharacterType::Tails) {
        palWhere = 0x46;
        palSuper = TailsPaletteSuper;
        palNormal = TailsPaletteNormal;
        palSuperHCZ = TailsPaletteSuperHCZ;
        palNormalHCZ = TailsPaletteNormalHCZ;
        palSuperPulse = TailsPaletteSuperPulse;
        palSuperPulseHCZ = TailsPaletteSuperPulseHCZ;
    }
    else if (Character == CharacterType::Knuckles) {
        palWhere = 0x50;
        palSuper = KnuxPaletteSuper;
        palNormal = KnuxPaletteNormal;
        palSuperHCZ = KnuxPaletteSuperHCZ;
        palNormalHCZ = KnuxPaletteNormalHCZ;
        palSuperPulse = KnuxPaletteSuperPulse;
        palSuperPulseHCZ = KnuxPaletteSuperPulseHCZ;
    }
    else {
        // Default to Sonic
        palWhere = 0x40;
        palSuper = SonicPaletteSuper;
        palNormal = SonicPaletteNormal;
        palSuperHCZ = SonicPaletteSuperHCZ;
        palNormalHCZ = SonicPaletteNormalHCZ;
        palSuperPulse = SonicPaletteSuperPulse;
        palSuperPulseHCZ = SonicPaletteSuperPulseHCZ;
    }


    if (SuperFormAnim == SuperFormAnimType::Super) {
        double superblend = Cos[(Scene->Frame << 1) & 0xFF] / 2.0 + 0.5;
        for (int i = 0; i < 4; i++) {
            for (int p = 0; p < 6; p++) {
                Sprites[i]->Palette[palWhere + p] = G->ColorBlend(palSuper[p], palSuperPulse[p], superblend);

                Sprites[i]->PaletteAlt[palWhere + p] = G->ColorBlend(palSuperHCZ[p], palSuperPulseHCZ[p], superblend);
            }
			Sprites[i]->UpdatePalette();
        }
    }
    else if (SuperFormAnim == SuperFormAnimType::Transforming) {
        if (SuperFormTimer < 40)
            SuperFormTimer++;

        double superblend = SuperFormTimer / 40.0;
        for (int i = 0; i < 4; i++) {
            for (int p = 0; p < 6; p++) {
                Sprites[i]->Palette[palWhere + p] = G->ColorBlend(palNormal[p], palSuper[p], superblend);

                Sprites[i]->PaletteAlt[palWhere + p] = G->ColorBlend(palNormalHCZ[p], palSuperHCZ[p], superblend);
            }
			Sprites[i]->UpdatePalette();
        }
    }
    else if (SuperFormAnim == SuperFormAnimType::Deforming) {
        if (SuperFormTimer < 20)
            SuperFormTimer++;

        double superblend = SuperFormTimer / 20.0;
        for (int i = 0; i < 4; i++) {
            for (int p = 0; p < 6; p++) {
                Sprites[i]->Palette[palWhere + p] = G->ColorBlend(palSuper[p], palNormal[p], superblend);

                Sprites[i]->PaletteAlt[palWhere + p] = G->ColorBlend(palSuperHCZ[p], palNormalHCZ[p], superblend);
            }
			Sprites[i]->UpdatePalette();
        }
    }
    else {
        for (int i = 0; i < 8; i++) {
            if (!Sprites[i]) break;

            memcpy(Sprites[i]->Palette + palWhere, palNormal, 6 * 4);
            memcpy(Sprites[i]->PaletteAlt + palWhere, palNormalHCZ, 6 * 4);
			Sprites[i]->UpdatePalette();
        }
    }

    // Ease rotation
    int8_t shortestrot;
    int8_t FinalAngle = 0;
    if (abs((int8_t)Angle) >= 0x1C) {
        FinalAngle = (int8_t)Angle;
    }
    shortestrot = (FinalAngle - ((uint16_t)DisplayAngle >> 8)) & 0xFF;
    if (DisplayAngle == 0 && shortestrot < 0) {
        DisplayAngle = -1;
        shortestrot = -1;
    }
    if (shortestrot < 0) {
        if (Ground)
            DisplayAngle -= 0x600;
        else
            DisplayAngle -= 0x400;

        DisplayAngle &= 0xFFFF;

        if (DisplayAngle < FinalAngle * 0x100)
            DisplayAngle = FinalAngle * 0x100;
    }
    else if (shortestrot > 0) {
        if (Ground)
            DisplayAngle += 0x600;
        else
            DisplayAngle += 0x400;

        DisplayAngle &= 0xFFFF;

        if ((DisplayAngle >> 8) > FinalAngle)
            DisplayAngle = FinalAngle << 8;
    }


    // For animations that don't rotate, set DisplayAngle to 0
    bool noRotate =
		Action != ActionType::Normal &&
		Action != ActionType::Grab;
    if (noRotate)
        DisplayAngle = 0;

    CameraX = 0;
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
    else if (Action == ActionType::Rolling) {
        CameraX = (int)(this->Sin[Angle] * (H / 2 - 16));
        CameraY = (int)(this->Cos[Angle] * (H / 2 - 16));
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

    if (CameraLockTimer == 0) {
        if (Action == ActionType::CrouchDown) {
            CameraLookTimer += 1;
        }
        else if (Action == ActionType::LookUp) {
            CameraLookTimer += 1;
        }
    }

    PlayerStatus status;
    status.X = EZX;
    status.Y = EZY;
    status.InputUp = InputUp;
    status.InputDown = InputDown;
    status.InputLeft = InputLeft;
    status.InputLeftPress = InputLeftPress;
    status.InputRight = InputRight;
    status.InputRightPress = InputRightPress;
    status.InputJump = InputJump;
    status.InputJumpHold = InputJumpHold;
    status.Action = Action;
    status.XSpeed = XSpeed;
    status.YSpeed = YSpeed;
    PlayerStatusTable[PlayerStatusTableIndex] = status;
    PlayerStatusTableIndex = (PlayerStatusTableIndex + 1) & 0x1F;
}
void IPlayer::Render(int CamX, int CamY) {
    if (Hidden) return;

    // Invincibility stars:
    // 2 per sonic status position
    // 3 status positions + current pos to revolve around
    ISprite::Animation animation2 = Sprites[0]->Animations[CurrentAnimation];
    ISprite::AnimFrame currentFrame2 = animation2.Frames[CurrentFrame / 0x100];
    int myOffX = 0;
    int myOffY = currentFrame2.OffY + H / 2;
    if (Action != ActionType::Conveyor)
        myOffY = 0;

    if (Action == ActionType::Rolling) {
        myOffX += (int)(this->Sin[Angle] * (H / 2 - 16));
        myOffY += (int)(this->Cos[Angle] * (H / 2 - 16));
    }

    // Draw water running waves
    if (WaterRunning) {
        G->DrawModeOverlay = true;
        G->DrawSprite(Scene->SpriteMapIDs[0x33], 17, (Scene->Frame >> 1) % Scene->SpriteMapIDs[0x33]->Animations[17].FrameCount, EZX - CamX, EZY + H / 2 - CamY, 0, XSpeed > 0 ? IE_NOFLIP : IE_FLIPX);
        G->DrawModeOverlay = false;
    }

    // Draw shields (Above player)
    if (!SuperForm && !HyperForm && Invincibility != InvincibilityType::Full) {
        if (Shield == ShieldType::Fire && ((ShieldFrame >> 8) & 1)) {
            G->DrawSprite(SpriteShields, 2, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_NOFLIP);
        }
        else if (Shield == ShieldType::Electric && (Scene->Frame & 1)) {
			G->DrawSprite(SpriteShields, 3, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_NOFLIP);
        }
        else if (Shield == ShieldType::Bubble && !((ShieldFrame / 0x100) & 1) && !(Scene->Frame & 1)) {
			if (ShieldAction)
				G->DrawSprite(SpriteShields, 4, 2, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_FLIPY);
			else
				G->DrawSprite(SpriteShields, 1, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_FLIPY);
        }
        else if (Shield == ShieldType::Basic && !(Scene->Frame & 1)) {
			G->DrawSprite(SpriteShields, 0, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, !(Scene->Frame & 1) ? IE_FLIPX : IE_NOFLIP);
        }
    }

    // Draw Player
    if (Invincibility != InvincibilityType::Temporary ||
        InvincibilityTimer % 6 < 3 ||
        Action == ActionType::Transform) {
        int FinalAngle = DisplayAngle >> 8;

        int x = 0;
        int y = 0;
        if (Action == ActionType::Rolling) {
            x = (int)(this->Sin[Angle] * (H / 2 - 16));
            y = (int)(this->Cos[Angle] * (H / 2 - 16));
        }

        /*
        "Player/TailSprite.bin"
        "Tails 0" (55) (Flags: 04, FtL: 0, Spd: 64, Frames: 10)
        "Tails 1" (56) (Flags: 01, FtL: 0, Spd: 64, Frames: 6)
        "Tails 2" (57) (Flags: 00, FtL: 0, Spd: 128, Frames: 6)
        "Tails 3" (58) (Flags: 00, FtL: 0, Spd: 64, Frames: 6)
        "Tails 4" (59) (Flags: 00, FtL: 0, Spd: 64, Frames: 6)
        "Tails 5" (60) (Flags: 01, FtL: 0, Spd: 32, Frames: 6)
        "Tails 6" (61) (Flags: 01, FtL: 0, Spd: 64, Frames: 10)
        */
		// Draw Tails' tails
        int Ani = 0;
        int Ang = 0;
        int Fli = 0;
        int Fra = 0;
        if (Character == CharacterType::Tails) {
            if (CurrentAnimation <= 3) {
                Ani = 55;
                Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
                Fra = (Scene->Frame >> 2) % 10;
            }
            else if (CurrentAnimation == 4) {
                Ani = 61;
                Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
                Fra = (Scene->Frame >> 2) % 10;
                Ang = FinalAngle;
            }
			else if (CurrentAnimation >= 5 && CurrentAnimation <= 9) {
				// Do nothing, as these tails are in-sprite.
				Ani = 0;
			}
			else if (CurrentAnimation == 10) {
                Ani = 56;
                Ang = IMath::atanHex(XSpeed, -YSpeed);
                Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPY;
                Fra = ((Scene->Frame >> 2) * IMath::clamp(abs(GroundSpeed) >> 7, 1, 8)) % 6;
            }
			else if (CurrentAnimation >= 11 && CurrentAnimation <= 12) {
				// Do nothing, as these tails are in-sprite.
				Ani = 0;
			}
			else if (CurrentAnimation >= 13 && CurrentAnimation <= 14) {
                Ani = 57;
                Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
                Fra = (Scene->Frame >> 2) % 6;
                Ang = FinalAngle;
            }
            else if (CurrentAnimation == 15) {
                Ani = 55;
                Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
                Fra = (Scene->Frame >> 1) % 10;
            }
			else if (CurrentAnimation == 16) {
				// Tails does not have a drop dash, but just in case...
                Ani = 56;
                Ang = IMath::atanHex(XSpeed, -YSpeed);
                Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPY;
                Fra = ((Scene->Frame >> 2) * IMath::clamp(abs(GroundSpeed) >> 7, 1, 8)) % 6;
            }
			else if (CurrentAnimation == 17) {
				// Pushing
				Ani = 55;
				Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
				Fra = (Scene->Frame >> 2) % 10;
			}
			else if (CurrentAnimation >= 18 && CurrentAnimation <= 27) {
				// Do nothing, as these tails are in-sprite.
				Ani = 0;
			}
			else if (CurrentAnimation == 28) {
				Ani = 58;
				Fli = DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX;
				Fra = (Scene->Frame >> 2) % 6;
				Ang = FinalAngle;
			}
			else if (CurrentAnimation >= AnimationMap["Fly"]) {
				Ani = 0;
			}

            if (Ani > 0)
                G->DrawSprite(Sprites[0], Ani, Fra, EZX + x - CamX, EZY + y - CamY, Ang, Fli);
        }

        ISprite::Animation animation = Sprites[0]->Animations[CurrentAnimation];
        ISprite::AnimFrame currentFrame = animation.Frames[CurrentFrame / 0x100];

        if (SuperForm || HyperForm || SpeedSneakersActive) {
            for (int i = -5 - 8; i <= -5; i += 4) {
                G->DrawAlpha = 0xFF + i * 0xC;
                PlayerStatus status = PlayerStatusTable[(PlayerStatusTableIndex + 0x20 + i) & 0x1F];
                int status_Y = status.Y;
                if (Ground && Angle == 0)
                    status_Y = EZY;

                if (Character == CharacterType::Tails) {
                    if (Action == ActionType::Jumping || Action == ActionType::Rolling) {
                        Ang = IMath::atanHex(status.XSpeed, -status.YSpeed);
                    }

                    if (Ani > 0)
                        G->DrawSprite(Sprites[0], Ani, Fra, status.X + x - CamX, status_Y + y - CamY, Ang, Fli);
                }

				G->DrawSprite(Sprites[currentFrame.SheetNumber], CurrentAnimation, CurrentFrame >> 8, status.X + x - CamX, status_Y + y - CamY, FinalAngle, DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX);
            }
        }

        G->DrawAlpha = 0xFF;

        G->DrawSprite(Sprites[currentFrame.SheetNumber], CurrentAnimation, CurrentFrame >> 8, EZX + x - CamX, EZY + y - CamY, FinalAngle, DisplayFlip > 0 ? IE_NOFLIP : IE_FLIPX);
    }

    // Draw spindash dust
    if (Action == ActionType::Spindash)
        G->DrawSprite(SpriteDashDust, 1, DashFrame >> 8, EZX - CamX, EZY + H / 2 - CamY, 0, (DisplayFlip < 0) ? IE_FLIPX : IE_NOFLIP);

    // Draw shields (Above player)
    if (!SuperForm && !HyperForm && Invincibility != InvincibilityType::Full) {
        if (Shield == ShieldType::Fire && !((ShieldFrame >> 8) & 1)) {
            G->DrawSprite(SpriteShields, 2, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_NOFLIP);
        }
        else if (Shield == ShieldType::Electric && !(Scene->Frame & 1)) {
            G->DrawSprite(SpriteShields, 3, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_NOFLIP);
        }
        else if (Shield == ShieldType::Bubble && (((ShieldFrame / 0x100) & 1) || (Scene->Frame & 1))) {
			if (ShieldAction)
				G->DrawSprite(SpriteShields, 4, 2, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_FLIPY);
			else
				G->DrawSprite(SpriteShields, 1, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, IE_FLIPY);
        }
        else if (Shield == ShieldType::Basic && (Scene->Frame & 1)) {
            G->DrawSprite(SpriteShields, 0, ShieldFrame >> 8, EZX + myOffX - CamX, EZY + myOffY - CamY, 0, !(Scene->Frame & 1) ? IE_FLIPX : IE_NOFLIP);
        }
    }

    // Draw Invincibility stars
    if (Invincibility == InvincibilityType::Full) {
        int star = 0;
        G->DrawModeOverlay = true;
        for (int i = -5 - 8; i <= -1; i += 4) {
            G->DrawAlpha = 0xFF + i * 0x8;
            PlayerStatus status = PlayerStatusTable[(PlayerStatusTableIndex + 0x20 + i) & 0x1F];
            ISprite::Animation animation = SpriteShields2->Animations[star];
            // ISprite::AnimFrame currentFrame = animation.Frames[Scene->Frame % animation.FrameCount];

            int x, y, ang;
            ang = (((Scene->Frame + star) % 16) * 0x2FE / 16 + (Scene->Frame << 2)) & 0xFF;
            x = (int)(this->Cos[ang] * 16);
            y = (int)(this->Sin[ang] * 16);

			G->DrawSprite(SpriteShields2, star, Scene->Frame % animation.FrameCount,
				status.X - x - CamX,
                status.Y + y - CamY,
                0, IE_NOFLIP);

            G->DrawSprite(SpriteShields2, star, Scene->Frame % animation.FrameCount,
				status.X + x - CamX,
                status.Y - y - CamY,
                0, IE_NOFLIP);

            star++;
        }
        G->DrawModeOverlay = false;
        G->DrawAlpha = 0xFF;
    }
}

void IPlayer::Jump() {
    for (int x = -9; x <= 9 && AngleMode == 0 && Action != ActionType::Climb; x++) {
        if (Scene->CollisionAt((X >> 16) + x, (Y >> 16) - 25, NULL, 2, this)) {
            return;
        }
    }

    int16_t jmp = 0x680;
    if (Character == CharacterType::Knuckles)
        jmp = 0x600;
    else if (Character == CharacterType::Ray)
        jmp = 0x6B8;

    if (Underwater)
        jmp -= 0x300;

    if (Character == CharacterType::Sonic && SuperForm) {
        jmp = 0x800;
        if (Underwater)
            jmp = 0x380;
    }

    XSpeed -= jmp * Sin[Angle];
    YSpeed -= jmp * Cos[Angle];

    Ground = false;
    Angle = 0;
    AngleMode = 0;
    ShieldUsable = true;

	AngleIslandFlag = false;

    JumpVariable = 1;

    Action = ActionType::Jumping;
    Sound::Play(Sound::SFX_JUMP);
}
void IPlayer::Hurt(int x, bool spike) {
    if (Action == ActionType::Hurt ||
        Shield == ShieldType::Instashield ||
        Action == ActionType::Dead ||
        Invincibility != InvincibilityType::None ||
        SuperForm ||
        Action == ActionType::Transform)
        return;

    ObjectControlled = 0;
    DisplayAngle = 0;
    Angle = 0;

    if (Shield == ShieldType::None) {
        Vibrate(VibrationType::DamageSmall);
        if (Rings > 0 || Sidekick) {
            Action = ActionType::Hurt;
            //if (CollisionCSensor(-1, 6) == false && CollisionDSensor(-1, 6) == false)
                YSpeed = -0x400;
            //else
            //    YSpeed = 0;
            Ground = false;
            XSpeed = 0x200 * IMath::sign(EZX - x);
            if (XSpeed == 0) XSpeed = -0x200;
            if (Underwater) {
                XSpeed >>= 1;
                YSpeed >>= 1;
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
            Die(false);
            //Scene->aud_Die->Play(1); // $AudioPlay(aud_Die, 1);
        }
    }
    else if (Invincibility == InvincibilityType::None) {
        Shield = ShieldType::None;
        Action = ActionType::Hurt;
        Vibrate(VibrationType::DamageLarge);

        Sound::Play(Sound::SFX_SPIKE_DEATH);

        YSpeed = -0x400;
        Ground = false;
        XSpeed = 0x200 * IMath::sign(EZX - x);
        if (XSpeed == 0) XSpeed = -0x200;
        if (Underwater) {
            XSpeed >>= 1;
            YSpeed >>= 1;
        }
    }
}
void IPlayer::Die(bool drown) {
    Action = ActionType::Dead;
    XSpeed = 0;
    Angle = 0;
    AngleMode = 0;
    DisplayAngle = 0;
    if (drown) {
        YSpeed = 0;
        Sound::Play(Sound::SFX_DROWN);
		if (!Sidekick)
			App->Audio->ClearMusic();
        UnderwaterTimer = 1800;
    }
    else {
        YSpeed = -0x700;
        Sound::Play(Sound::SFX_DEATH);
    }
    Lives--;
    VisualLayer = 1;
    Invincibility = InvincibilityType::None;
}
void IPlayer::CreateRingLoss() {
    if (Cutscene) return;
    if (Sidekick) return;

    int t = 0;
    int angle = 72;
    bool n = false;
    int spd = 0x400;

    if (Rings > 32)
        Rings = 32;

    RingAlarm = 64;

    while (t < Rings) {
        int xspd = (int)(spd * Cos[angle & 0xFF]);
        int yspd = (int)(spd * Sin[angle & 0xFF]);
        if (n) {
            xspd = -xspd;
            angle += 0x10;
        }
        Scene->AddActiveRing(EZX, EZY, xspd, yspd, -1);

        n = !n;
        t++;

        if (t == 16) {
            spd = 0x200;
            angle = 72;
        }
    }

    Sound::Play(Sound::SFX_RINGLOSS);

    Rings = 0;
}
void IPlayer::Vibrate(VibrationType v) {
    double strengths[7] = {
        0.0,
        0.35,
        0.75,
        0.35,
        0.75,
        0.15,
        0.85,
    };
    int durations[7] = {
        0,
        200,
        200,
        650,
        650,
        150,
        350,
    };
    App->Input->Vibrate(0, strengths[(int)v], durations[(int)v]);
}

void IPlayer::Deform() {
    if (!SuperForm) return;

    SuperForm = false;
    SuperFormTimer = 0;
    SuperFormAnim = SuperFormAnimType::Deforming;
    InvincibilityTimer = 0;
    Invincibility = InvincibilityType::None;
}
void IPlayer::CheckDespawn() {
    if (!Sidekick) return;
    if (Action == ActionType::Respawn) return;

    if (OnScreen) {
        RespawnTimer = 0;
    }
    else {
        RespawnTimer++;
        if (RespawnTimer >= 0x12C) {
            Action = ActionType::Respawn;
            RespawnTimer = 0;
            EZX = Scene->Player->EZX;
            if (Scene->CameraY - 0x60 > 0)
                EZY = Scene->CameraY - 0x60;
            else
                EZY = 0;
        }
    }
}

void IPlayer::GiveRing(int n) {
    if (Sidekick)
        Scene->Player->Rings += n;
    else
        Rings += n;

    if (Rings >= RingLifeValue) {
        RingLifeValue += 100;
        GiveLife(1);
    }
}
void IPlayer::GiveLife(int n) {
    Sound::Audio->PushMusic(Sound::SoundBank[0xFB], false, 0);

    if (Sidekick)
        Scene->Player->Lives += n;
    else
        Lives += n;
}

void IPlayer::HandlePathSwitchers() {
    int16_t X = this->X >> 16;
    int16_t Y = this->Y >> 16;

    int sz_l = XSpeed >> 8;
    int sz_r = XSpeed >> 8;

    if (sz_l > 0)
        sz_l = 0;
    if (sz_r > 0)
        sz_r = 0;

    for (int i = 0; i < Scene->PlaneSwitchCount; i++) {
        int W = 8 * Scene->PlaneSwitchers[i].Size;
        int H = 8 * Scene->PlaneSwitchers[i].Size;
        int rnd = (Scene->PlaneSwitchers[i].Angle & 0xC0);
        if (rnd == 0x00 ||
            rnd == 0x80) {
            W = 0;
        }
        else {
            H = 0;
        }

        if (rnd != Scene->PlaneSwitchers[i].Angle)
            continue; // just don't even deal with angles like these tbh

        if (X + 10 + sz_l >= Scene->PlaneSwitchers[i].X - W &&
            X - 10 + sz_r <  Scene->PlaneSwitchers[i].X + W &&
            Y + 10 + 00 >= Scene->PlaneSwitchers[i].Y - H &&
            Y - 10 - 00 <  Scene->PlaneSwitchers[i].Y + H) {

            if (Scene->PlaneSwitchers[i].OnPath) {
                if (Ground) {
                    float dot = 0;
                    dot += XSpeed * Cos[Scene->PlaneSwitchers[i].Angle] * abs(XSpeed);
                    dot += YSpeed * Sin[Scene->PlaneSwitchers[i].Angle] * abs(YSpeed);

                    if (dot > 0) {
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
                float dot = 0;
                dot += XSpeed * Cos[Scene->PlaneSwitchers[i].Angle] * abs(XSpeed);
                dot += YSpeed * Sin[Scene->PlaneSwitchers[i].Angle] * abs(YSpeed);

                if (dot > 0) {
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
void IPlayer::HandleMonitors() {
    ISprite::Animation animation2 = Sprites[0]->Animations[CurrentAnimation];
    ISprite::AnimFrame currentFrame2 = animation2.Frames[CurrentFrame / 0x100];
    int myOffY = currentFrame2.OffY + H / 2;
    if (Action != ActionType::Conveyor)
        myOffY = 0;

    for (int o = 0; o < Scene->RingPropCount; o++) {
        LevelScene::ObjectProp obj = Scene->RingProps[o];
        bool Collided = (
            (int)obj.X + 8 >=  (X >> 16) - W / 2 + (XSpeed >> 8) &&
            (int)obj.Y + 8 >=  (Y >> 16) - H / 2 + (YSpeed >> 8) + myOffY &&
            (int)obj.X - 8 <   (X >> 16) + W / 2 + (XSpeed >> 8) &&
            (int)obj.Y - 8 <   (Y >> 16) + H / 2 + (YSpeed >> 8) + myOffY
        );

        if (Shield == ShieldType::Electric) {
            int diffX = (int)obj.X - (int)(X >> 16);
            int diffY = (int)obj.Y - (int)(Y >> 16);

            if (diffX * diffX + diffY * diffY < 0x1000 && obj.ID) { // radius of 64, then squared
                Scene->AddActiveRing(obj.X, obj.Y, 0, 0, PlayerID);
                Scene->RingProps[o].ID = 0;
            }
        }

        if (Collided && obj.ID) {
            Scene->RingProps[o].ID = 0;
            GiveRing(1);
            Sound::Play(Sound::SFX_RING);

            int rx[3] = { -4, 1, 4 };
            int ry[3] = { 1, -2, 3 };
            for (int i = 0; i < 3; i++) {
                Explosion* ringsparkle;
                ringsparkle = new Explosion();
                ringsparkle->G = G;
                ringsparkle->App = App;
                ringsparkle->CurrentAnimation = 9;
                ringsparkle->FlipX = false;
                ringsparkle->Active = true;
                ringsparkle->Sprite = Scene->ItemsSprite;
                ringsparkle->X = obj.X + rx[i];
                ringsparkle->Y = obj.Y + ry[i];
                Scene->Explosions.push_back(ringsparkle);
            }
        }
    }

    for (int o = 0; o < Scene->ObjectEnemiesCount; o++) {
        Enemy* obj = Scene->ObjectsEnemies[o];
        if (obj != NULL) {
            if (obj->Active && obj->HitCount > 0) {
                bool Collided = false;
                if (obj->Radius > 1) {
                    int DeltaX = (int)obj->X - max(EZX - (int)W / 2, min((int)obj->X, EZX + (int)W / 2));
                    int DeltaY = (int)obj->Y - max(EZY - (int)H / 2, min((int)obj->Y, EZY + (int)H / 2));
                    Collided = (DeltaX * DeltaX + DeltaY * DeltaY) < (obj->Radius * obj->Radius);
                }
                else {
                    Collided =
                        (int)obj->X + obj->W / 2 >= EZX - (int)W / 2 &&
                        (int)obj->Y + obj->H / 2 >= EZY - (int)H / 2 &&
                        (int)obj->X - obj->W / 2 <  EZX + (int)W / 2 &&
                        (int)obj->Y - obj->H / 2 <  EZY + (int)H / 2;
                }

                if (Collided) {
                    int hitFrom = 0;
                    float wy = (W + obj->W) * ((Y >> 16) - obj->Y);
                    float hx = (H + obj->H) * ((int)(X >> 16) - (int)obj->X);

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

                    bool IsAttacking = false;
					bool IsAttackingAbsolute = false;
					IsAttacking |= SuperForm;
					IsAttacking |= HyperForm;
					IsAttacking |= Shield == ShieldType::Instashield;
					IsAttacking |= Invincibility == InvincibilityType::Full;
					IsAttackingAbsolute = IsAttacking;

                    if ((obj->X < EZX && DisplayFlip < 0) ||
                        (obj->X > EZX && DisplayFlip > 0))
                        IsAttacking |= Action == ActionType::Glide;
                    if (obj->Y < EZY)
                        IsAttacking |= Action == ActionType::Fly;
                    IsAttacking |= Action == ActionType::Jumping;
                    IsAttacking |= Action == ActionType::Rolling;

                    if (IsAttacking) {
                        if (obj->Invincible) {
                            if (obj->Harmful) {
                                Hurt(obj->X, false);
                                goto FinishBadnikBounce;
                            }
                            else
                                continue;
                        }
						else if (obj->Hurting && !IsAttackingAbsolute) {
                            Hurt(obj->X, false);
                            goto FinishBadnikBounce;
                        }
                        else if (obj->Hurting) {
                            obj->OnHit();
                            goto DoBadnikBounce;
                        }
                        else {
                            obj->OnHit();
                            goto DoBadnikBounce;
                        }
                    }
                    else if (obj->Harmful) {
                        Hurt(obj->X, false);
                        goto FinishBadnikBounce;
                    }
                    else {
                        continue;
                    }

                    DoBadnikBounce:
                    if (obj->Boss) {
                        if (IsAttacking) {
                            Sound::Play(Sound::SFX_BOSSHIT);
                            Vibrate(VibrationType::ImpactLarge);
                            if (Ground) {
                                GroundSpeed = -GroundSpeed;
                            }
                            else {
                                XSpeed = -XSpeed;
                                YSpeed = -YSpeed;
                            }
                        }
                    }
                    else {
                        if (EnemyCombo == 0) {
                            Scene->Score += 100;
                        }
                        else if (EnemyCombo == 1) {
                            Scene->Score += 200;
                        }
                        else if (EnemyCombo == 2) {
                            Scene->Score += 500;
                        }
                        else if (EnemyCombo == 15) {
                            Scene->Score += 10000;
                        }
                        else {
                            Scene->Score += 1000;
                        }
                        Scene->AddScoreGhost(EnemyCombo, obj->X, obj->Y);
                        if (EnemyCombo < 15)
                            EnemyCombo++;
                        Vibrate(VibrationType::ImpactLarge);
                        if (EZY < obj->Y && YSpeed > 0) {
                            YSpeed = -YSpeed;
                        }
                        else {
                            if (YSpeed < 0)
                                YSpeed += 0x100;
                            else
                                YSpeed -= 0x100;
                        }
                    }
                    FinishBadnikBounce:
                    YSpeed += 0;
                }
            }
        }
    }

    if (Sidekick) return;

    for (int o = 0; o < Scene->ObjectBreakableCount; o++) {
        Object* obj = Scene->ObjectsBreakable[o];
        if (obj != NULL) {
            if (obj->Active) {
                if ((int)obj->X + obj->W / 2     >=  (X >> 16) - (int)W / 2 + (XSpeed >> 8) - 2 &&
                    (int)obj->Y + obj->H / 2 + 2 >=  (Y >> 16) - (int)H / 2 &&
                    (int)obj->X - obj->W / 2     <   (X >> 16) + (int)W / 2 + (XSpeed >> 8) + 2 &&
                    (int)obj->Y - obj->H / 2 - 2 <   (Y >> 16) + (int)H / 2 + (YSpeed >> 8)) {
                    int hitFrom = 0;
                    float wy = (W + obj->W) * (int(Y >> 16) - int(obj->Y));
                    float hx = (H + obj->H) * (int(X >> 16) - int(obj->X));

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
						if (hitFrom == 1 || hitFrom == 3) continue;

                        if (obj->OnBreakHorizontal(PlayerID, hitFrom)) {
                            Action = ActionType::Normal;
                            Vibrate(VibrationType::ImpactSmall);
                        }
                        else {
                            X -= abs(GroundSpeed) << 8;
                            Vibrate(VibrationType::ImpactSmall);
                        }
                    }
                    else if (obj->BreakableByGlide && Action == ActionType::Glide) {
                        if (YSpeed > 0x600)
                            Vibrate(VibrationType::ImpactLarge);
                        else
                            Vibrate(VibrationType::ImpactSmall);

                        if (hitFrom == 0 || hitFrom == 2) {
                            obj->OnBreakHorizontal(PlayerID, hitFrom);
                        }
                        else {
                            if (EZY < obj->Y)
                                YSpeed = -YSpeed;

                            obj->OnBreakVertical(PlayerID, hitFrom);
                        }
                    }
                    else if (obj->BreakableByJump && Action == ActionType::Jumping && ((hitFrom == 0 && XSpeed < -0x80) || (hitFrom == 2 && XSpeed > 0x80) || (hitFrom == 1 && YSpeed > 0) || (hitFrom == 3 && YSpeed < 0))) {
                        if (EZY < obj->Y + 8) { // add "|| Settings_SonicKnucklesMonitorBehavior"
                            if (obj->OnBreakVertical(PlayerID, hitFrom) == 1) {
                                if (YSpeed > 0x600)
                                    Vibrate(VibrationType::ImpactLarge);
                                else
                                    Vibrate(VibrationType::ImpactSmall);

                                YSpeed = -YSpeed;
                            }
                        }
                        else if (hitFrom == 3) {
                            obj->YSpeed = -0x300;
                            YSpeed = 0x100;
                            Vibrate(VibrationType::SpindashRev);
                        }
                    }
                    else if (obj->BreakableByKnuckles && Character == CharacterType::Knuckles && ((hitFrom == 0 && XSpeed < -0x20) || (hitFrom == 2 && XSpeed > 0x20))) {
                        X -= abs(GroundSpeed) << 8;
                        obj->OnBreakHorizontal(PlayerID, hitFrom);
                    }
                }
            }
        }
    }
}
bool IPlayer::HandleSprings() {
    ///*
    for (int o = 0; o < Scene->ObjectSpringCount; o++) {
        Object* obj = Scene->ObjectsSpring[o];
        if (obj != NULL) {
            if (obj->Active) {
                int si = abs(this->Sin[obj->Rotation * 64 / 90]);
                int co = abs(this->Cos[obj->Rotation * 64 / 90]);
                if (obj->X + obj->W / 2 + si * 3 - co * 6 >= ((X + (XSpeed << 8)) >> 16) - W / 2 - 8 &&
                    obj->Y + obj->H / 2 + co * 3          >= (Y >> 16) - H / 2 &&
                    obj->X - obj->W / 2 - si * 3 + co * 6 <  ((X + (XSpeed << 8)) >> 16) + W / 2 + 8 &&
                    obj->Y - obj->H / 2 - co * 3          <  (Y >> 16) + H / 2) {

                    float wy = (W + obj->W) * ((Y >> 16) - obj->Y);
                    float hx = (H + obj->H) * ((int)(X >> 16) - (int)obj->X);

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

                    if (obj->OnCollisionWithPlayer(PlayerID, hitFrom, 1)) {
                        /*if (Action == ActionType::Hurt) {
                            Invincibility = InvincibilityType::Temporary;
                            InvincibilityTimer = 120;
                        }*/
                        return true;
                    }
                }
            }
        }
    }
    return false;
    //*/
}

void IPlayer::DoVictory() {
    bool DoJump = false;
    if (Ground && Action != ActionType::Victory && DoJump) {
        if (Underwater) {
            YSpeed = -0x100;
            XSpeed = 0x80;
        }
        else {
            YSpeed = -0x200;
            XSpeed = 0x100;
        }
        Ground = false;
    }
    Action = ActionType::Victory;
    ChangeAnimation(AnimationMap["Victory"]);
}
