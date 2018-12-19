#ifndef SCENE_Z_MSZ_H
#define SCENE_Z_MSZ_H

#include "Standard.h"
#include "Application.h"
#include "TextureAudio.h"

#include "Engine/ITexture.h"

#include "S3/Player.h"

class Scene_MSZ : public Scene {
public:
    Scene_MSZ(Application* app, int data1, int data2);
    void Update();
    void Render();
    void Free();
};

#endif /* SCENE_Z_MSZ_H */
