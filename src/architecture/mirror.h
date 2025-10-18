#ifndef __MIRROR_H__
#define __MIRROR_H__

#include <vector>
#include <cstdio>
#include <string>

using namespace std;

typedef enum
{
    REFLECT, //Projecting a file to the telemetry table
    ABSORB,  //Making a file from the telemetry table
    OPAQUE   //Nothing
} MirrorMode;

typedef struct
{
    int axises[4];
    bool buttons[12];
} FrameData; //Stores a single frame of input [axises: int[4], buttons: bool[12]]

FrameData getFrameFromString(string str);


class AbsorbtiveMirror
{

private:
    static int AUTONFRAMES;
    static int SKILLFRAMES;
    int maximumFrames;
    int writtenFrames = 0;
    FILE *writeStream; 
    bool isFlipped;

public:
    void captureFrame(int axises[4], bool buttons[12]);

    int getWrittenFrames();

    bool isFull();

    AbsorbtiveMirror(string filename, bool isFlipped);
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