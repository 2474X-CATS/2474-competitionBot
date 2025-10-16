#ifndef __MIRROR_H__
#define __MIRROR_H__

#include <vector>
#include <cstdio>
#include <string>

using namespace std;

extern bool STARTING_FROM_ORIGIN; 

typedef enum
{
    REFLECT,
    ABSORB,
    OPAQUE
} MirrorMode;

typedef struct
{
    int axises[4];
    bool buttons[12];
} FrameData;

extern FrameData defaultFrame;

string getStringFromFrame(FrameData data);
FrameData getFrameFromString(string str);

class AbsorbtiveMirror
{

private:
    static int AUTONFRAMES;
    static int SKILLFRAMES;
    int maximumFrames;
    int writtenFrames = 0;
    FILE *writeStream;

public:
    void captureFrame(int axises[4], bool buttons[12]);

    int getWrittenFrames();

    bool isFull();

    AbsorbtiveMirror(string filename);
    ~AbsorbtiveMirror();
};

class ReflectiveMirror
{

private:
    FILE *readStream;

public:
    FrameData getNextFrame();
    bool isDone();
    ReflectiveMirror(string filename);
    ~ReflectiveMirror();
};

#endif