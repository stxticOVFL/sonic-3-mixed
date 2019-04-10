#ifndef VWATERSTREAM_H
#define VWATERSTREAM_H

class VWaterStream;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class VWaterStream: public Object {
public:    
    
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* VWATERSTREAM_H */
