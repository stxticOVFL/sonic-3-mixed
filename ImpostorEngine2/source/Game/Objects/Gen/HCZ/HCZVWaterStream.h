#ifndef HCZVWATERSTREAM_H
#define HCZVWATERSTREAM_H

class HCZVWaterStream;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class HCZVWaterStream: public Object {
public:    
    
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* HCZVWATERSTREAM_H */
