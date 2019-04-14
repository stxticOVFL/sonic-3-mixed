#ifndef STANDARDLIBS_H
#define STANDARDLIBS_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>

#include <unordered_map>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>

#ifdef MSVC
    #define IFILE(name) ("source/Resources/" name)
#elif NX
    #define IFILE(name) ("Resources/" name)
#elif IOS
    #define IFILE(name) name
#elif ANDROID
    #define IFILE(name) name
#elif MACOSX
    #define IFILE(name) ("source/Resources/" name)
#endif

#ifdef ANDROID
    #include <android/log.h>
#endif

enum {
    IE_NOFLIP = 0,
    IE_FLIPX = 1,
    IE_FLIPY = 2,

    IE_FILTER_BLACKWHITE = 1,
    IE_FILTER_INVERT = 2,
    IE_FILTER_FADEABLE = 4,
};

enum class Platforms {
    Default,
    Windows,
    MacOSX,
    Linux,
    Ubuntu,
    Switch,
    iOS,
    Android,
	PlayStation4,
	XboxOne,
	Vita,
};

void Discord_UpdatePresence(const char* header, const char* state, const char* imgkey, bool time);
void Discord_UpdatePresence(const char* header, const char* state, const char* imgkey);

using namespace std;

typedef std::string string;

#endif // STANDARDLIBS_H
