// Object ID: 0xFFFFFFFF
// Object Name: AIZIntro.cpp

#include "AIZIntro.h"

typedef IMath Math;

void AIZIntro::Create() {
    Object::Create();
    Priority = true;
    Scene->TileSprite->SetTransparentColorIndex(48);
    InitialCamX = Scene->CameraX;
    InitialCamY = Scene->CameraY;
    Scene->LevelCardHide = true;
    Scene->isCutscene = true;
    if (SaveGame::CurrentMode == 0) {
        IntroSprite = Scene->LoadLevelTiles("Classic/Stages/AIZ1/Intro/16x16Tiles.gif");
    }
    else {
        IntroSprite = Scene->LoadLevelTiles("Mixed/Stages/AIZ1/Intro/16x16Tiles.gif");
    }
    TileSpriteBackup = Scene->TileSprite;
    IntroSprite->SetTransparentColorIndex(0);
    Scene->HUDVisible = false;
    Scene->LevelCardTimer = 0.0;
    Scene->LevelCardHide = true;
    Scene->FadeAction = 0;
    Scene->FadeTimerMax = 90;
    Scene->FadeMax = 0x140;
    if (Scene->Player) {
        if (Scene->Player->Character == CharacterType::Knuckles) {
            CutSceneKnux = true;
        }
        else {
            CutSceneKnux = false;
            OnBeach = false;
            SuperSonicMoving = false;
            CutsceneRoutineNumber = 0x00;
            Cutscene_SonicWaitTimer = -1;
            Cutscene_KnucklesBackForth = -1;
            Scene->Player->Cutscene = true;
            Scene->Player->ControlLocked = true;
            Scene->Player->ChangeAnimation(Scene->Player->AnimationMap["S_Run"]);
            Scene->AddNewObject(Obj_AIZTornado);
            Scene->PlayMusicObj();
        }
    }

}

void AIZIntro::Update() {
    if (CutSceneKnux) {
        KnuxCutscene();
    }
    else {
        SonicCutscene();
    }
    Object::Update();
}

void AIZIntro::SonicCutscene() {
    int LayerBG = Scene->FindLayer("Background");
    int LayerFG = Scene->FindLayer("FG High");
    if (CutsceneRoutineNumber == 0) {
        Scene->BackgroundRepeatTileWidth = 16;
        Scene->Data->Layers[LayerFG].Visible = false;
        SonicFrameTimer++;
        if (SonicFrameTimer > 1) {
            SonicFrame++;
            if (SonicFrame > 1) SonicFrame = 0;

            SonicFrameTimer = 0;
        }

        Scene->Player->Visible = false;
        UpdateTimer++;
        if (UpdateTimer > 260) {
            CutsceneRoutineNumber++;
            UpdateTimer = 0;
            UpdateTimer = TornadoY;
        }

        Scene->Player->EZX = Scene->CameraX + App->WIDTH / 2 - 4;
        Scene->Player->EZY = Scene->CameraY + App->HEIGHT / 2 + 32;
    }
    else if (CutsceneRoutineNumber == 1) {
        SonicFrameTimer++;
        TornadoX -= 8;
        if (TornadoY - 48 < UpdateTimer) {
            TornadoY += 4;
        }

        if (SonicFrameTimer > 4) {
            SonicFrame++;
            if (SonicFrame > 4) {
                SonicFrame = 4;
                if (TornadoX + 128 < Scene->CameraX && TornadoY - 48 <= UpdateTimer) {
                    CutsceneRoutineNumber++;
                    SuperSonicMoving++;
                    Scene->RoutineNumber = 1;
                    Scene->Player->EZY = Scene->CameraY + App->HEIGHT / 2 + 32;
                    TornadoY = 1;
                }

            }

            SonicFrameTimer = 0;
        }

    }

    if (SuperSonicMoving && CutsceneRoutineNumber == 2) {
        if (Scene->CameraX < InitialCamX + 3000 && !OnBeach) {
            Scene->BackgroundRepeatTileWidth = 32;
        }
        else if (Scene->CameraX >= InitialCamX + 3000 && !OnBeach) {
            Scene->CameraX = InitialCamX + 0x000;
            Scene->BackgroundRepeatTileWidth = 0;
            OnBeach = true;
            Scene->Data->Layers[LayerFG].Visible = true;
        }

        if (TornadoX >= Scene->CameraX + App->WIDTH / 2 - 4) {
            TornadoY = 0;
            Scene->CameraX += 16;
            Scene->Player->EZX = Scene->CameraX + App->WIDTH / 2 - 4;
            Scene->Player->EZY = Scene->CameraY + App->HEIGHT / 2 + 32;
        }
        else {
            if (TornadoY > 0) {
                TornadoX += 16;
                Scene->Player->EZX = TornadoX;
                Scene->Player->EZY = Scene->CameraY + App->HEIGHT / 2 + 32;
            }
            else {
                Scene->CameraX += 16;
                Scene->Player->EZX = Scene->CameraX + App->WIDTH / 2 - 4;
                Scene->Player->EZY = Scene->CameraY + App->HEIGHT / 2 + 32;
            }
        }
        Scene->Player->GroundSpeed = 0xC00;
        Scene->Player->Ground = true;
        if (Scene->CameraX >= InitialCamX + 5024 && OnBeach) {
            Scene->CameraX = InitialCamX + 5024;
            SuperSonicMoving = false;
            Scene->Player->Visible = true;
            Scene->Player->GroundSpeed = 0x0;
            Scene->Player->XSpeed = 0x0;
            Scene->Player->Rings = 1;
            Scene->Player->Hurt(Scene->Player->EZX + 1, false);
            Scene->Player->Deform();
            Scene->Player->ChangeAnimation(Scene->Player->AnimationMap["Hurt"]);
            Scene->RoutineNumber = 2;
            CutsceneRoutineNumber = 3;
            Scene->AddNewObject(Obj_AIZIntroKnux, InitialCamX + 5313, Scene->Player->Y);
            Knux = Scene->ObjectCount - 1;
        }

    }

    int MaxY = 0x400 - 8;
    Scene->CameraY = MaxY - App->HEIGHT / 2;
    if (Scene->Player->EZY > 0x480) {
        Scene->Player->EZY = 0x480;
    }

    if (Scene->LevelCardTimer >= 1.5) {
        Scene->LevelCardTimer = 5.0;
    }

    if (Scene->LevelCardTimer >= 5.0) {
        Scene->LevelCardHide = false;
    }

    if (CutsceneRoutineNumber == 3) {
        if (Scene->Player->Ground && Cutscene_SonicWaitTimer < 0) {
            Scene->Player->Action = ActionType::Normal;
            Scene->Player->ChangeAnimation(Scene->Player->AnimationMap["Idle"]);
            Cutscene_SonicWaitTimer = 30;
            Scene->SetObjectSubType(Knux, 1);
        }

        if (Cutscene_SonicWaitTimer == 0) {
            CutsceneRoutineNumber = 4;
            Scene->Player->ChangeAnimation(Scene->Player->AnimationMap["Idle"]);
            Cutscene_KnucklesBackForth = 112;
            Scene->SetObjectSubType(Knux, 60);
        }

    }
    else if (CutsceneRoutineNumber == 4) {
        if (Cutscene_KnucklesBackForth == 0) {
            CutsceneRoutineNumber = 5;
            Scene->Player->ChangeAnimation(Scene->Player->AnimationMap["Idle"]);
            Cutscene_SonicWaitTimer = 60;
        }

    }
    else if (CutsceneRoutineNumber == 5) {
        if (Cutscene_SonicWaitTimer == 0) {
            Scene->Player->Cutscene = false;
            Scene->Player->ControlLocked = false;
            Scene->Player->Rings = 0;
            Scene->LevelCardTimer = 0.0;
            Scene->LevelCardHide = true;
            Scene->HUDVisible = true;
            Timer = 0;
            Scene->Frame--;
            Scene->isCutscene = false;
            SaveGame::SetFlag(1, 0);
            Scene->TileSprite = TileSpriteBackup;
            Scene->LoadNextAct = true;
        }

    }

    if (Cutscene_SonicWaitTimer > 0) Cutscene_SonicWaitTimer--;

    if (Cutscene_KnucklesBackForth > 0) Cutscene_KnucklesBackForth--;

}

void AIZIntro::KnuxCutscene() {
}

void AIZIntro::IntroFinish() {
    Scene->HUDVisible = true;
    Scene->Player->Cutscene = false;
    Scene->Player->ControlLocked = false;
    Scene->Act = 1;
    Scene->isCutscene = false;
    SaveGame::SetFlag(1, 0);
}

