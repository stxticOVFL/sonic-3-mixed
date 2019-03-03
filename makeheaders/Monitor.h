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
        TYPE_HYPER_RING = 11
        TYPE_SHIELD_FIRE = 5
        TYPE_SHIELD_LIGHTNING = 6
        TYPE_BROKEN = 10
        TYPE_INVINCIBILITY = 8
        TYPE_SUPER = 9
        TYPE_SHIELD_BUBBLE = 7
        TYPE_ROBOTNIK = 2
        TYPE_SPEED_SHOES = 4
        TYPE_RINGS = 3
        TYPE_1UP = 1
        TYPE_STATIC = 0
    };
    
    int SubY;
    bool CanFall;
    double GhostY;
    int SubTypeFrame;
    int PlayerAggressor;
    
    void Create();
    void Update();
    void Render(int CamX, int CamY);
    int OnBreakHorizontal(int PlayerID, int HitFrom);
    int OnBreakVertical(int PlayerID, int HitFrom);
};

#endif /* MONITOR_H */
