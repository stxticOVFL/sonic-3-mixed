#ifndef IACHIEVEMENT_H
#define IACHIEVEMENT_H

#define PUBLIC
#define PRIVATE
#define PROTECTED
#define STATIC
#define VIRTUAL
#define CONSTRUCTER

#include <Utils/Standard.h>
#include <Utils/StandardSDL2.h>
#include <Engine/IApp.h>
#include <Engine/ISprite.h>

class IAchievement {
public:
    struct Achievement {
    char Name[0x40];
    bool Achieved;
	bool Hidden;
	//ISprite Icon;
    }; 
    Achievement AchievementList[0x40];
    uint8_t AchievementCount = 0;
    void CreateAchievement(char* name);
    void CreateAchievement(char* name, int ID);
    void SetAchievement(int AchievementID, bool State);
    void OnAchievementGet(int AchievementID);
	IAchievement();
};

#endif /* IACHIEVEMENT_H */
