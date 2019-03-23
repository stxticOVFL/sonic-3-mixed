// Object ID: 0xFFFFFFFF
// Object Name: PlayerSpawn.cpp

#include "PlayerSpawn.h"

typedef IMath Math;

void PlayerSpawn::Create() {
    Object::Create();
    SpawnPlayer = 0;
    SpawnAsSidekick = false;
    SpawnPlayerID = 0;
    Scene->SpawnPlayer(SpawnPlayer, SpawnAsSidekick);
    Active = false;
}

