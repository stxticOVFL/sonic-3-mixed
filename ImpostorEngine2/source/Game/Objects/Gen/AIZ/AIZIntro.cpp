// Object ID: 0xFFFFFFFF
// Object Name: AIZIntro.cpp

#include "AIZIntro.h"

typedef IMath Math;

void AIZIntro::Create() {
    Object::Create();
    Priority = true;
    InitialCamX = Scene->CameraX;
    InitialCamY = Scene->CameraY;
    Scene->LevelCardHide = true;
    Scene->isCutscene = true;
    SonicAnim = 0;
    SonicFrame = 0;
    SonicX = App->WIDTH / 2 - 4;
    SonicY = App->HEIGHT / 2 - 16;
    IntroPlayersSprite = LevelScene::LoadSpriteFromBin("Players/AIZCutscene.bin", SaveGame::CurrentMode);
    if (IntroPlayersSprite) {
        IntroPlayersSprite->SetTransparentColorIndex(0);
    }

    if (SaveGame::CurrentMode == 0) {
        IntroSprite = Scene->LoadLevelTiles("Classic/Stages/AIZ1/Intro/16x16Tiles.gif");
    }
    else {
        IntroSprite = Scene->LoadLevelTiles("Mixed/Stages/AIZ1/Intro/16x16Tiles.gif");
    }
    IntroSprite->LinkPalette(Scene->TileSprite);
    TileSpriteBackup = Scene->TileSprite;
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
    int LayerForest = Scene->FindLayer("Background (Forest)");
    int LayerFire = Scene->FindLayer("Fire Overlay");
    int LayerBG = Scene->FindLayer("Background (Sea & Sky)");
    if (CutsceneRoutineNumber == 0) {
        SonicFrameTimer++;
        if (SonicFrameTimer > 1) {
            SonicFrame++;
            if (SonicFrame > 1) SonicFrame = 0;

            SonicFrameTimer = 0;
        }

        Scene->Player->Visible = false;
        UpdateTimer++;
        if (UpdateTimer > 180) {
            CutsceneRoutineNumber++;
            UpdateTimer = 0;
            UpdateTimer = SonicY;
        }

        Scene->Player->EZX = Scene->CameraX + App->WIDTH / 2 - 4;
        Scene->Player->EZY = Scene->CameraY + App->HEIGHT / 2 + 32;
    }
    else if (CutsceneRoutineNumber == 1) {
        SonicAnim = 1;
        SonicFrameTimer++;
        SonicX -= 8;
        if (SonicY - 48 < UpdateTimer) {
            SonicY += 4;
        }

        if (SonicFrameTimer > 4) {
            SonicFrame++;
            if (SonicFrame > 4) {
                SonicFrame = 4;
                if (SonicX + 128 < Scene->CameraX && SonicY - 48 <= UpdateTimer) {
					CutsceneRoutineNumber++;
                    SuperSonicMoving++;
                    Scene->Player->EZY = Scene->CameraY + App->HEIGHT / 2 + 32;
                    SonicY = 1;
                }

            }

            SonicFrameTimer = 0;
        }

    }

    if (SuperSonicMoving && CutsceneRoutineNumber > 1) {
        if (Scene->CameraX < InitialCamX + 2900 && !OnBeach) {
            Scene->BackgroundRepeatTileWidth = 32;
            Scene->Player->Visible = true;
        }
        else if (Scene->CameraX >= InitialCamX + 2900 && !OnBeach) {
            Scene->CameraX = InitialCamX + 0x000;
            Scene->BackgroundRepeatTileWidth = 0;
            OnBeach = true;
        }

        if (SonicX >= Scene->CameraX + App->WIDTH / 2 - 4) {
            SonicY = 0;
            Scene->CameraX += 16;
            Scene->Player->EZX = Scene->CameraX + App->WIDTH / 2 - 4;
            Scene->Player->EZY = Scene->CameraY + App->HEIGHT / 2 + 32;
        }
        else {
            if (SonicY > 0) {
                SonicX += 16;
                Scene->Player->EZX = SonicX;
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
            Scene->Player->GroundSpeed = 0x0;
            Scene->Player->XSpeed = 0x0;
            Scene->Player->Rings = 1;
            Scene->Player->Hurt(Scene->Player->EZX + 1, false);
            Scene->Player->Deform();
            Scene->Player->ChangeAnimation(Scene->Player->AnimationMap["Hurt"]);
            CutsceneRoutineNumber = 3;
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
            Cutscene_SonicWaitTimer = 120;
        }

        if (Cutscene_SonicWaitTimer == 0) {
            CutsceneRoutineNumber = 4;
            Scene->Player->ChangeAnimation(Scene->Player->AnimationMap["Idle"]);
            Cutscene_KnucklesBackForth = 60;
            Scene->Player->EZX -= 4;
        }

    }
    else if (CutsceneRoutineNumber == 4) {
        if (Cutscene_KnucklesBackForth == 0) {
            CutsceneRoutineNumber = 5;
            Scene->Player->ChangeAnimation(Scene->Player->AnimationMap["Idle"]);
            Scene->Player->EZX += 4;
            Cutscene_SonicWaitTimer = 120;
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

void AIZIntro::Render(int CamX, int CamY) {
    if (CutsceneRoutineNumber < 2) {
        G->DrawSprite(IntroPlayersSprite, SonicAnim, SonicFrame, SonicX, SonicY, 0, this->FlipX ? IE_FLIPX : IE_NOFLIP);
    }

    }

void AIZIntro::IntroFinish() {
    Scene->HUDVisible = true;
    Scene->Player->Cutscene = false;
    Scene->Player->ControlLocked = false;
    Scene->Act = 1;
    Scene->isCutscene = false;
    SaveGame::SetFlag(1, 0);
}

