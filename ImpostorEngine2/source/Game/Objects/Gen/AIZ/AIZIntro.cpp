// Object ID: 0xFFFFFFFF
// Object Name: AIZIntro.cpp

#include "AIZIntro.h"

typedef IMath Math;

void AIZIntro::Create() {
    Object::Create();
    Scene->HUDVisible = false;
    Scene->LevelCardTimer = 0.0;
    Scene->LevelCardHide = true;
    Scene->FadeAction = 0;
    Scene->FadeTimerMax = 90;
    Scene->FadeMax = 0x140;
    OnBeach = false;
    SuperSonicMoving = true;
    CutsceneRoutineNumber = 0x00;
    Cutscene_SonicWaitTimer = -1;
    Cutscene_KnucklesBackForth = -1;
    Scene->Player->Cutscene = true;
    Scene->Player->ControlLocked = true;
    if (Scene->Player) {
        if (Scene->Player->Character != CharacterType::Knuckles) {
            CutSceneKnux = true;
        }
        else {
            CutSceneKnux = false;
            Scene->TileSprite = IntroSprite;
        }
    }

    IntroFinish();
}

void AIZIntro::Update() {
    Object::Update();
}

void AIZIntro::IntroFinish() {
    Scene->TileSprite = TileSpriteBackup;
    Scene->HUDVisible = true;
    Scene->Player->Cutscene = false;
    Scene->Player->ControlLocked = false;
}

