// Object ID: 0x03
// Object Name: HollowTree.cpp

#include "HollowTree.h"

typedef IMath Math;

void HollowTree::Create() {
    Object::Create();
    Active = true;
    Priority = false;
    DoDeform = true;
    W = 0xD0;
    H = 0x168;
    Status = 0;
    for (int i = 0; i < 8; i++)
PlayerStorage[i] = 0;

    Timer = 0;
    VisualLayer = 1;
}

void HollowTree::Update() {
    for (int i = 0; i < Scene->PlayerCount; i++)
{
        if (Scene->Players[i]->Action == ActionType::Dead) continue;

        CheckPlayer(i);
    }
    if (Status == 0) {
        if (Timer != 0) {
            Timer--;
            if (Timer == 0) {
                Scene->CameraMinX = 0x1300;
                Scene->CameraMaxX = 0x4000;
            }
            else {
                if (Scene->CameraMinX != 0x1300) {
                    if (Scene->Player->EZX >= 0x2D00) {
                        Scene->CameraMinX = 0x1300;
                    }
                    else {
                        Scene->CameraMinX -= 4;
                    }
                }

                if (Scene->CameraMaxX != 0x4000) {
                    if (Scene->Player->EZX < 0x2D00) {
                        Scene->CameraMaxX = 0x4000;
                    }
                    else {
                        Scene->CameraMaxX += 4;
                    }
                }

            }
        }

    }

    Object::Update();
}

void HollowTree::CheckPlayer(int id) {
    int d0;
    IPlayer* Player = Scene->Players[id];
    if (((Status >> id) & 1) == 0) {
        if (Player->Ground) {
            d0 = Player->EZX + 0x10 - X;
            if (d0 >= 0) {
                if (d0 < 0x40) {
                    d0 = Player->EZY - Y;
                    if (d0 >= -0x5A) {
                        if (d0 <= 0xA0) {
                            if (Player->XSpeed >= 0x600) {
                                if (Player->ObjectControlled == 0) {
                                    Status |= (1 << id);
                                    PlayerStorage[id] = 0;
                                    Player->ObjectControlled |= (1 << 6);
                                    Player->ObjectControlled |= (1 << 1);
                                    Player->Action = ActionType::Corkscrew;
                                    if (id == 0) {
                                        Scene->LevelTriggerFlag |= 1 << 0;
                                    }

                                    Timer = 0x3C;
                                }

                            }

                        }

                    }

                }

            }

        }

    }
    else {
        if (id == 0) {
            if (Scene->CameraMinX < X - App->WIDTH / 2) {
                if (Scene->CameraMinX < Scene->CameraX) Scene->CameraMinX = Scene->CameraX;

                Scene->CameraMinX += 4;
            }
            else {
                Scene->CameraMinX = X - App->WIDTH / 2;
            }
            if (Scene->CameraMaxX > X - App->WIDTH / 2) {
                if (Scene->CameraMaxX > Scene->CameraX) Scene->CameraMaxX = Scene->CameraX;

                Scene->CameraMaxX -= 4;
            }
            else {
                Scene->CameraMaxX = X - App->WIDTH / 2;
            }
        }

        d0 = Math::abs(Player->GroundSpeed);
        if (d0 >= 0x600) {
            if (Player->Ground || true) {
                d0 = Player->EZY - Y + 0x90;
                if (d0 > 0) {
                    if (d0 > 0x130) {
                        AIZTree_FallOff(id);
                        return;
                    }
                    else {
                        AIZTree_SetPlayerPos(id);
                    }
                }
                else {
                    AIZTree_FallOff(id);
                    return;
                }
            }
            else {
                if (Player->EZX < 0x2C99) {
                    Player->EZX = 0x2C99;
                    Player->XSpeed = 0x400;
                }

                if (Player->EZX >= 0x2D66) {
                    Player->EZX = 0x2D66;
                    Player->XSpeed = -0x400;
                }

                AIZTree_FallOff(id);
                return;
            }
        }
        else {
            if ((PlayerStorage[id] >> 16) < 0x400) {
                AIZTree_SetPlayerPos(id);
                AIZTree_FallOff(id);
                return;
            }
            else {
                AIZTree_FallOff(id);
                return;
            }
        }
    }
}

void HollowTree::AIZTree_FallOff(int id) {
    IPlayer* Player = Scene->Players[id];
    Player->Ground = false;
    Player->Action = ActionType::Normal;
    Status &= (1 << id) ^ 0xFF;
    Player->ObjectControlled = 0;
    Player->XSpeed >>= 2;
    Player->YSpeed >>= 1;
    Player->H = Player->OrigH;
}

void HollowTree::AIZTree_SetPlayerPos(int id) {
    int d0;
    int d2;
    int d3;
    IPlayer* Player = Scene->Players[id];
    if (((Status >> id) & 1) != 0) {
        d0 = Player->GroundSpeed;
        d0 <<= 8;
        Player->DoCollision = false;
        PlayerStorage[id] += d0;
        if (PlayerStorage[id] >= 0) {
            if ((PlayerStorage[id] >> 16) >= 0x400) {
                Scene->CameraMinX = 0x1300;
                Scene->CameraMaxX = 0x4000;
            }

            d2 = Player->EZX;
            d0 = (PlayerStorage[id] >> 16);
            d0 >>= 1;
            Player->GrabSwingValue = (d0 & 0xFF);
            d0 = Math::sinHex(d0) * -0x70;
            d3 = Math::sign(d0);
            d0 >>= 16;
            d0 += X;
            Player->EZX = d0;
            d0 -= d2;
            d0 <<= 8;
            Player->XSpeed = Math::abs(d0) * d3;
            d2 = Player->EZY;
            d0 = (PlayerStorage[id] >> 16);
            d0 >>= 2;
            d0 = -d0;
            d0 += 0x90;
            d0 += Y;
            Player->EZY = d0;
            Player->H = 32;
            d0 = int(d0) - int(d2);
            d0 <<= 8;
            Player->YSpeed = -0x100;
            d0 = 0;
            d0 = (PlayerStorage[id] >> 16);
            d0 >>= 1;
            d0 /= 0xB;
            d0 = Player->EZY - Y + 0x90;
            if (d0 <= 0) {
                AIZTree_FallOff(id);
                Player->Ground = true;
                Player->GroundSpeed = 0x400;
                Player->EZY = Y - 124 - Player->H / 2;
            }

        }
        else {
            AIZTree_FallOff(id);
        }
    }

}

