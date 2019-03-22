// Object ID: 0xFFFFFFFF
// Object Name: PlayerSpawn.cpp

#include "PlayerSpawn.h"

typedef IMath Math;

void PlayerSpawn::Create() {
    Object::Create();
    if (!LevelScene::Player) {
        Player->G = G;
        Player->App = App;
        Player->Scene = this;
        Player->PlayerID = 0;
        Player->Thremixed = SaveGame::CurrentMode > 0;
        Player->Create();
        Player->Lives = SaveGame::GetLives();
        Players[0] = Player;
        LevelScene::PlayerCount = 1;
        if (SaveGame::CurrentPartnerFlag != 0xFF) {
            Players[1]->G = G;
            Players[1]->App = App;
            Players[1]->Scene = this;
            Players[1]->Sidekick = true;
            Players[1]->PlayerID = 1;
            Players[1]->Thremixed = SaveGame::CurrentMode > 0;
            Players[1]->Create();
            LevelScene::PlayerCount = 2;
        }

        memcpy(LevelScene::Players, Players, sizeof(Players));
    }

    Active = false;
}

