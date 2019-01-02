struct AnimFrame {
    int X;
    int Y;
    int W;
    int H;
    int OffX;
    int OffY;
    int SheetNumber;
    int Duration;
    uint BufferID;
};

struct Animation {
    char* Name;
    int FrameCount;
    int AnimationSpeed;
    int FrameToLoop;
    int Flags;
    AnimFrame Frames;
};
