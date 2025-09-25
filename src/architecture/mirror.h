#ifndef __MIRROR_H__
#define __MIRROR_H__

#include <vector>
#include <fstream>

using namespace std;

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
FrameData getFrameFromData(int axises[4], bool buttons[12]);

class AbsorbtiveMirror
{

private:
    static int AUTONFRAMES;
    static int SKILLFRAMES;

    int maximumFrames;
    int writtenFrames = 0;
    ofstream writeStream;

public:
    void captureFrame(int axises[4], bool buttons[12]);

    bool isFull();

    AbsorbtiveMirror(string filename);
    ~AbsorbtiveMirror();
};

class ReflectiveMirror
{

private:
    vector<FrameData> frames;
    int numFrames = 0;
    ifstream readStream;
    int currentFrame;

public:
    FrameData getNextFrame();
    bool isDone();
    ReflectiveMirror(string filename);
};

#endif