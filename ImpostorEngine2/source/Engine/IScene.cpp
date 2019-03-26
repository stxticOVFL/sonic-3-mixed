#if INTERFACE
#include <Utils/Standard.h>
#include <Engine/IApp.h>
#include <Engine/IGraphics.h>

class IScene {
public:
    IApp* App = NULL;
    IGraphics* G = NULL;

    int FadeTimer = -1;
    int FadeTimerMax = 1;
    int FadeMax = 0xFF;
    bool FadeIn = false;
};
#endif

#include <Engine/IScene.h>
#include <Engine/Diagnostics/Memory.h>

PUBLIC VIRTUAL IScene::~IScene() {
	Memory::PrintLeak();
}

PUBLIC VIRTUAL void IScene::OnEvent(Uint32 event) {

}

PUBLIC VIRTUAL void IScene::Init() {

}

PUBLIC VIRTUAL void IScene::Update() {

}

PUBLIC VIRTUAL void IScene::Render() {

}

PUBLIC VIRTUAL void IScene::Cleanup() {
	//Memory::PrintLeak();
}

PUBLIC VIRTUAL bool IScene::ExecuteCommand(char* cmd) {
    return false;
}