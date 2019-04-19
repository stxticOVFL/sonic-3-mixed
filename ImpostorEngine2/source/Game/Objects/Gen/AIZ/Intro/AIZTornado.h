#ifndef AIZTORNADO_H
#define AIZTORNADO_H

class AIZTornado;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class AIZTornado: public Object {
public:    
    
    int ShadowFrameTimer;
    int PropellorFrameTimer;
    int FlameFrameTimer;
    int ShadowFrame;
    int PropellorFrame;
    int FlameFrame;
    int HeadsFrame;
    int ShadowAnim;
    int PropellorAnim;
    int FlameAnim;
    int HeadsAnim;
    int TornadoAnim;
    ISprite* PlayerSprite;
    int SonicX;
    int SonicY;
    int SonicFrame;
    int SonicFrameTimer;
    int SonicAnim;
    int State;
    int UpdateTimer;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* AIZTORNADO_H */