#ifndef MONITOR_H
#define MONITOR_H

class Monitor;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Monitor: public Object {
public:    
    enum ItemTypes {
        TYPE_SUPER = 6,
        TYPE_RINGS = 0,
        TYPE_SPEED_SHOES = 4,
        TYPE_SHIELD_BUBBLE = 1,
        TYPE_1UP = 7,
        TYPE_SHIELD_FIRE = 2,
        TYPE_SHIELD_LIGHTNING = 3,
        TYPE_INVINCIBILITY = 5,
        TYPE_BROKEN = 8,
        TYPE_STATIC = 9,
        TYPE_HYPER_RING = 10,
        TYPE_ROBOTNIK = 11,
    };
    
    int SubY;
    bool CanFall;
    double GhostY;
    int SubTypeFrame;
    int PlayerAggressor;
    
    void Create();
    void UpdateSubType();
    uint8_t GetSubTypeMax();
    void Update();
    void Render(int CamX, int CamY);
    int OnBreakHorizontal(int PlayerID, int HitFrom);
    int OnBreakVertical(int PlayerID, int HitFrom);
};

#endif /* MONITOR_H */
