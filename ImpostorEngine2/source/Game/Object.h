#ifndef S3_OBJECT_H
#define S3_OBJECT_H

#define Scene_AddSelfToRegistry(boots) Scene->Objects##boots[Scene->Object##boots##Count++] = this

class LevelScene;

enum class CollideSide {
    NONE = 0,
    LEFT = 1,
    RIGHT = 2,
    SIDES = 3,
    TOP = 4,
    TOP_SIDES = 7,
    BOTTOM = 8,
};

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
    int16_t  W = 32;
    int16_t  H = 32;
    int16_t  VisW = 0;
    int16_t  VisH = 0;
    int16_t  XSpeed = 0;
    int16_t  YSpeed = 0;

    uint16_t ID;
    uint8_t  SubType;
    bool     Active;
    bool     Priority;
    bool     OnScreen = false;
    int      VisualLayer = 0;

    bool FlipX;
    bool FlipY;

    int  Frame = 0;
    int  CurrentAnimation = 0;
    int  Timer = -1;
    int  Rotation = 0;

    bool Solid = false;
    bool SolidTop = false;
    bool SolidCustomized = false;

    bool Pushable = false;
    bool CollidingWithPlayer = false;
    bool BeingStoodOn = false;

    CollideSide BreakableByRoll = CollideSide::NONE;
    CollideSide BreakableByJump = CollideSide::NONE;
    CollideSide BreakableByGlide = CollideSide::NONE;
    CollideSide BreakableBySpring = CollideSide::NONE;
    CollideSide BreakableByKnuckles = CollideSide::NONE;

    bool BounceOffShield = false;
    bool NegatedByFireShield = false;
    bool NegatedByElectricShield = false;
    bool NegatedByBubbleShield = false;

    void* MyVars[25];

    virtual ~Object() {

    };

    virtual void Create() {
        X = InitialX;
        Y = InitialY;
        VisW = W;
        VisH = H;
    };
    virtual void Update() { };
    virtual void Render(int CamX, int CamY) { };

    virtual int  OnTouchHitbox(int) { return 0; };

    virtual int  OnPush(int, int) { return 0; };
    virtual int  OnGrabbed(int) { return 0; };
    virtual int  OnBreakHorizontal(int, int) { return 0; };
    virtual int  OnBreakVertical(int, int) { return 0; };
    virtual int  OnCollisionWithPlayer(int, int, int) { return 0; };
    virtual int  CustomSolidityCheck(int x, int y, int ID, int jumpthrough) { return false; };
    virtual int  OnLeaveScreen() { return 0; };

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
};

class Enemy : public Object {
public:
    bool Harmful = true;
    bool Hurting = false;
    bool Invincible = false;
    int  Radius = 1;
    int  HitCount = 1;

    bool Boss = false;

    virtual int OnDeath();
    virtual int OnHit() {
        HitCount--;
        if (HitCount <= 0)
            return OnDeath();
        return 0;
    };
    virtual int  OnCollisionWithPlayer(int, int, int) { return 0; };
};

#endif /* S3_OBJECT_H */
