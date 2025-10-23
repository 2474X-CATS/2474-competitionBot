#include <sstream>
#include "mirror.h"


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
   FrameData data{};
   std::stringstream ss(str);
   std::string token;
   int i = 0;

   while (std::getline(ss, token, ',') && i < 16)
   {
      if (token.empty())
         continue; 
      int val = 0;
      std::stringstream(token) >> val;
      if (i < 4)
      { 
           data.axises[i] = val;
      }
      else
      {
         data.buttons[i - 4] = (val == 1);
      }
      i++;
   }

   return data;
}

ReflectiveMirror::ReflectiveMirror(string filename)
    : readStream(fopen(filename.c_str(), "r")) {

      };

std::string getLine(FILE *file)
{
   std::string line;
   int c;
   while ((c = fgetc(file)) != EOF)
   {
      if (c == '\n')
         break;
      line.push_back(static_cast<char>(c));
   }
   return line;
}

FrameData ReflectiveMirror::getNextFrame()
{
   FrameData result{};
   if (!isDone())
   {
      result = getFrameFromString(getLine(readStream));
   }
   return result;
};

bool ReflectiveMirror::isDone()
{
   return feof(readStream);
}

ReflectiveMirror::~ReflectiveMirror()
{
   if (readStream)
      fclose(readStream);
}

//-----------------------------------------------

int AbsorbtiveMirror::AUTONFRAMES = 15 * 50;
int AbsorbtiveMirror::SKILLFRAMES = 60 * 50;

AbsorbtiveMirror::AbsorbtiveMirror(string filename, bool isFlipped) : isFlipped(isFlipped)
{ 
   /* 
   input: awp_23.auto, true 
   output: opening a write stream to autos/awp_23_FLIPPED.auto 

   input awp_23.skills, false 
   output: opening a write stream to skills/awp_23.skil
   */
   
   string fileSuffix = filename.substr(filename.length() - 4); 
   string fileBody = filename.substr(0, filename.length() - 5); 
   string directory;  

   string fullFileName;

   if (fileSuffix == "auto"){
      maximumFrames = AbsorbtiveMirror::AUTONFRAMES; 
      directory = "autos";  
   }
   if (fileSuffix == "skil"){
      maximumFrames = AbsorbtiveMirror::SKILLFRAMES;   
      directory = "skills";
   } 

   fullFileName = directory + "/" + fileBody + (isFlipped ? "_FLIPPED" : "") + "." + fileSuffix; 
   writeStream = fopen(fullFileName.c_str(), "w"); 
}; 


void AbsorbtiveMirror::captureFrame(int axises[4], bool buttons[12])
{
   if (!isFull())
   { 
      if (isFlipped){
         axises[3] *= -1; //Only flip horizontal component for driving  
         bool temp = buttons[0];  // On one side there is a mid goal
         buttons[0] = buttons[1]; // on the other a low goal and they are symmetrical relative to the center of the field
         buttons[1] = temp;       // by switching the buttons for the mid and low scoring functions the robot can adapt to different goals 
      }
      fprintf(writeStream, "%s\n", getStringFromData(axises, buttons).c_str());
      writtenFrames += 1;
   }
};

int AbsorbtiveMirror::getWrittenFrames()
{
   return writtenFrames;
}

bool AbsorbtiveMirror::isFull()
{
   return writtenFrames >= maximumFrames;
};

AbsorbtiveMirror::~AbsorbtiveMirror()
{
   fclose(writeStream);
}
