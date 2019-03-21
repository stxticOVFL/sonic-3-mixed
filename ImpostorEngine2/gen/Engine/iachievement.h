#ifndef IACHIEVEMENT_H
#define IACHIEVEMENT_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

class IApp;
class IGraphics;
class IAchievement;

#include <Utils/Standard.h>
#include <Engine/IApp.h>
#include <Engine/IGraphics.h>

constexpr auto TOTAL_ACHIEVEMENT_COUNT = (0x40);

class IAchievement {
public:
	struct Achievement {
		char Name[0x40];
		bool Achieved = false;
		bool Hidden = false;
		bool Initialised = false;
		//ISprite Icon;
	};
	Achievement AchievementList[TOTAL_ACHIEVEMENT_COUNT];
	uint8_t AchievementCount = 0;
	bool AchievementGet = false;
	int GotAchievement = 0;
	void CreateAchievement(char* name);
	void CreateAchievement(char* name, int ID);
	void SetAchievement(int AchievementID, bool State);
	void OnAchievementGet(int AchievementID);
	IAchievement();
	IAchievement(IApp* app);
	IApp* App = NULL;
	IGraphics* G = NULL;
};


#endif /* IACHIEVEMENT_H */
