// Object ID: 0xFFFFFFFF
// Object Name: Music.cpp

#include "Music.h"

typedef IMath Math;

void Music::Create() {
    Object::Create();
    AttributeBuffer = GetAttribute("trackFile");
    trackFile = AttributeBuffer.ValString;
    AttributeBuffer = GetAttribute("soundtestTitle");
    soundtestName = AttributeBuffer.ValString;
    AttributeBuffer = GetAttribute("trackID");
    trackID = AttributeBuffer.ValVar;
    AttributeBuffer = GetAttribute("trackLoop");
    trackLoop = AttributeBuffer.ValUint32;
    playOnLoad = false;
    AttributeBuffer = GetAttribute("playOnLoad");
    playOnLoad = AttributeBuffer.ValBool;
    loopTrack = false;
    if (trackLoop > 0) {
        loopTrack = true;
    }

    if (playOnLoad) {
        /*Sound::SoundBank[trackID]->Load(trackFile, true);
        Sound::Audio->LoopPoint[trackID] = trackLoop;
        Sound::Audio->Loop[trackID] = false;
        App->Audio->PushMusicAt(Sound::SoundBank[trackID], 0, loopTrack, trackLoop);*/
    }

}

