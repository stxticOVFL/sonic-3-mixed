#ifndef S3_OBJECT_H
#define S3_OBJECT_H

#define Scene_AddSelfToRegistry(boots) Scene->Objects##boots[Scene->Object##boots##Count++] = this

class LevelScene;

struct Rect {
    int  Left = 0x0;
    int  Right = 0x0;
    int  Top = 0x0;
    int  Bottom = 0x0;
    Rect() : Left(0), Right(0), Top(0), Bottom(0) {};
    Rect(int l, int r, int t, int b) : Left(l), Right(r), Top(t), Bottom(b) {};
    bool Empty() { return !Left && !Right && !Top && !Bottom; };
    Rect FlipX(bool flipX) { if (!flipX) return Rect(Left, Right, Top, Bottom); Left = -Left; Right = -Right; return Rect(Left, Right, Top, Bottom); };
    Rect FlipY(bool flipY) { if (!flipY) return Rect(Left, Right, Top, Bottom); Top = -Top; Bottom = -Bottom; return Rect(Left, Right, Top, Bottom); };
};

enum class CollideSide {
    NONE = 0,
    LEFT = 1,
    RIGHT = 2,
    SIDES = 3,
    TOP = 4,
    TOP_SIDES = 7,
    BOTTOM = 8,
};
bool operator==(const CollideSide& left, const int& right);
bool operator==(const int& left, const CollideSide& right);
bool operator!=(const CollideSide& left, const int& right);
bool operator!=(const int& left, const CollideSide& right);

class Object {
public:
    IApp* App;
    IGraphics* G;
    LevelScene* Scene;

    ISprite* Sprite = NULL;

    uint32_t InitialX;
    uint32_t InitialY;
    uint32_t* InitialValues;

    int32_t  SubX = 0;
    int32_t  SubY = 0;
    int16_t& X = *((int16_t*)&SubX + 1);
    int16_t& Y = *((int16_t*)&SubY + 1);
    uint16_t ID = 0x0;
    uint8_t  SubType = 0x0;
    bool     FlipX = false;
    bool     FlipY = false;

    int16_t  W = 32;
    int16_t  H = 32;
    int16_t  VisW = 0;
    int16_t  VisH = 0;
    int16_t  XSpeed = 0;
    int16_t  YSpeed = 0;

    int16_t  Gravity = 0;

    int16_t  MaxAccel = 0;
    int16_t  Acceleration = 0;
    int16_t  SwingDirection = 0;
    int16_t  SwingCounter = 0;

    bool     Active = false;
    bool     Priority = false;
    bool     OnScreen = false;
    int      VisualLayer = 0;

    bool     AutoAnimate = false;
    int      CurrentAnimation = -1;
    int      AnimationFrame = -2;
    int      Frame = 0;
    int      Timer = -1;
    int      Rotation = 0;

    bool     Solid = false;
    bool     SolidTop = false;
    bool     SolidCustomized = false;
    Rect     HitboxSolid;

    bool     Pushable = false;
	// bool     Climbable = false;

    bool     BounceOffShield = false;
    bool     NegatedByFireShield = false;
    bool     NegatedByElectricShield = false;
    bool     NegatedByBubbleShield = false;
    int      CollidingWithPlayer = false;
    bool     BeingStoodOn = false;

    CollideSide BreakableByRoll = CollideSide::NONE;
    CollideSide BreakableByJump = CollideSide::NONE;
    CollideSide BreakableByGlide = CollideSide::NONE;
	// CollideSide BreakableBySuper = CollideSide::NONE;
    CollideSide BreakableBySpring = CollideSide::NONE;
    CollideSide BreakableByKnuckles = CollideSide::NONE;

    virtual ~Object() {

    };

    virtual void Create();
    virtual void Update();
    virtual void Render(int CamX, int CamY);

    virtual int  OnTouchHitbox(int) { return 0; };

    virtual int  OnPush(int, int) { return 0; };
    virtual int  OnGrabbed(int) { return 0; };
    virtual int  OnBreakHorizontal(int, int) { return 0; };
    virtual int  OnBreakVertical(int, int) { return 0; };
    virtual int  OnCollisionWithPlayer(int, int, int) { return 0; };
    virtual int  CustomSolidityCheck(int x, int y, int ID, int jumpthrough) { return false; };
    virtual int  OnLeaveScreen() { return 0; };
    virtual void OnSwingFinish() { };
    virtual void OnAnimationFinish();

    void ChangeAnimation(int animationID, int startFrame, bool overrideanyways) {
        if (CurrentAnimation != animationID || overrideanyways)
            Frame = startFrame * 0x100;
        CurrentAnimation = animationID;
    };
    void ChangeAnimation(int animationID, int startFrame) {
        ChangeAnimation(animationID, startFrame, false);
    };
    void ChangeAnimation(int animationID) {
        ChangeAnimation(animationID, 0);
    };

    void Animate();
    void MoveSprite();
    int  Swing_UpAndDown();
};

class Enemy : public Object {
public:
    bool Harmful = true;
    bool Hurting = false;
    bool Invincible = false;
    int  Radius = 1;
    int  HitCount = 1;

    bool Boss = false;

    Rect HitboxEnemy;

    virtual void Create();
    virtual int  OnDeath();
    virtual int  OnHit();
};

class Solid : public Object {
public:
    virtual void Create();
};

#endif /* S3_OBJECT_H */
