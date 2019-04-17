// Object ID: 0xFFFFFFFF
// Object Name: AIZIntro.cpp

#include "AIZIntro.h"

typedef IMath Math;

void AIZIntro::Create() {
    Object::Create();
    Priority = true;
    Scene->Act = 0;
    Scene->isCutscene = true;
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
            Scene->TileSprite = IntroSprite;
            OnBeach = false;
            SuperSonicMoving = true;
            CutsceneRoutineNumber = 0x00;
            Cutscene_SonicWaitTimer = -1;
            Cutscene_KnucklesBackForth = -1;
            Scene->Player->Cutscene = true;
            Scene->Player->ControlLocked = true;
            Scene->Player->ChangeAnimation(Scene->Player->AnimationMap["S_Run"]);
        }
    }

}

void AIZIntro::SubUpdate() {
}

void AIZIntro::IntroFinish() {
    Scene->HUDVisible = true;
    Scene->Player->Cutscene = false;
    Scene->Player->ControlLocked = false;
    Scene->Act = 0;
    Scene->isCutscene = false;
    Scene->TileSprite = TileSpriteBackup;
    SaveGame::SetFlag(1, 0);
}

