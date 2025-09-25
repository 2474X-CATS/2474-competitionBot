#include <string>
#include "mirror.h"
#include <sstream>

/*
string getStringFromFrame(FrameData frame){
  string result;
  string currentToken;
  for (int i = 0; i < 4; i ++){
     result += frame.axises[i] + ",";
  }
  for (int i = 0; i < 12; i ++){
     result += frame.buttons[i] + ",";
  }
  return result;
};
*/

string getStringFromData(int axises[4], bool buttons[12])
{
   string result;
   for (int i = 0; i < 4; i++)
   { 
      ostringstream additive; 
      additive << axises[i] << ",";
      result += additive.str();
   }
   for (int i = 0; i < 12; i++)
   {
      ostringstream additive; 
      additive << buttons[i] << ",";
      result += additive.str();
   }
   return result;
}

FrameData getFrameFromString(string str)
{
   FrameData data;
   int tokensPassed = 0;
   int endingIndex = 0;
   int startingIndex = 0;
   while (tokensPassed < 16)
   {
      if (str[endingIndex] == ',')
      {
         stringstream strVal(str.substr(startingIndex, endingIndex - startingIndex));
         if (tokensPassed <= 4)
         {
            strVal >> data.axises[tokensPassed];
         }
         else if (tokensPassed <= 16)
         {
            strVal >> data.buttons[tokensPassed - 4];
         }
         startingIndex = endingIndex + 1;
         tokensPassed += 1;
      }
      endingIndex += 1;
   }
   return data;
};

FrameData getFrameFromData(int axises[4], bool buttons[12])
{
   FrameData frame;
   for (int i = 0; i < 4; i++)
   {
      frame.axises[i] = axises[i];
   }
   for (int i = 0; i < 12; i++)
   {
      frame.buttons[i] = buttons[i];
   }
   return frame;
};

ReflectiveMirror::ReflectiveMirror(string filename)
    : readStream(ifstream(filename)), currentFrame(0)
{
   string line;
   while (getline(readStream, line))
   {
      frames.push_back(getFrameFromString(line));
      numFrames += 1;
   }
   readStream.close();
};

FrameData ReflectiveMirror::getNextFrame()
{
   FrameData result;
   if (isDone())
      result = defaultFrame;
   else
      result = frames[currentFrame];
   currentFrame += 1;
   return result;
};

bool ReflectiveMirror::isDone()
{
   return currentFrame >= numFrames;
}

//-----------------------------------------------

int AbsorbtiveMirror::AUTONFRAMES = 15 * 50;
int AbsorbtiveMirror::SKILLFRAMES = 60 * 50;

AbsorbtiveMirror::AbsorbtiveMirror(string filename)
    : writeStream(ofstream(filename))
{
   string fileSuffix = filename.substr(filename.length() - 3);
   if (fileSuffix == "auto")
      maximumFrames = AbsorbtiveMirror::AUTONFRAMES;
   if (fileSuffix == "skil")
      maximumFrames = AbsorbtiveMirror::SKILLFRAMES;
};

void AbsorbtiveMirror::captureFrame(int axises[4], bool buttons[12])
{
   if (!isFull())
   {
      writeStream << getStringFromData(axises, buttons) << endl;
      writtenFrames += 1;
   }
};

bool AbsorbtiveMirror::isFull()
{
   return writtenFrames >= maximumFrames;
};

AbsorbtiveMirror::~AbsorbtiveMirror()
{
   writeStream.close();
}

FrameData defaultFrame = getFrameFromData(
    new int[4]{0, 0, 0, 0},
    new bool[12]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
