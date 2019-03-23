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
        TYPE_ROBOTNIK = 2,
        TYPE_STATIC = 0,
        TYPE_SHIELD_FIRE = 5,
        TYPE_1UP = 1,
        TYPE_RINGS = 3,
        TYPE_SHIELD_BUBBLE = 7,
        TYPE_SPEED_SHOES = 4,
        TYPE_SHIELD_LIGHTNING = 6,
        TYPE_SHIELD = 13,
        TYPE_INVINCIBILITY = 8,
        TYPE_SUPER = 9,
        TYPE_BROKEN = 10,
        TYPE_HYPER = 11,
        TYPE_HYPER_RING = 12,
        END_LIST_DONT_MOVE = 14,
    };
    
    int SubY;
    bool CanFall;
    double GhostY;
    int SubTypeFrame;
    int PlayerAggressor;
    IPlayer* Player;
    int MonitorType;
    
    CONSTRUCTER Monitor();
    void Create();
    void UpdateSubType();
    uint8_t GetSubTypeMax();
    void Update();
    void Render(int CamX, int CamY);
    int OnBreakHorizontal(int PlayerID, int HitFrom);
    int OnBreakVertical(int PlayerID, int HitFrom);
};

#endif /* MONITOR_H */
