#ifndef SCENE_MAINMENU_H
#define SCENE_MAINMENU_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL

class ISprite;
class ISprite;
class ISprite;
class ISprite;

#include <Engine/IScene.h>
#include <Engine/ISprite.h>

class Scene_MainMenu : public IScene {
public:
	int selected = 0;
	int ran = 0;
	ISprite* MenuSprite = NULL;
	ISprite* SphereSprite = NULL;
	ISprite* SuperButtonsSprite = NULL;
	ISprite* TextSprite = NULL;

	Scene_MainMenu(IApp* app, IGraphics* g);
	void Init();
	void Update();
	void Render();
};

#endif /* SCENE_MAINMENU_H */
