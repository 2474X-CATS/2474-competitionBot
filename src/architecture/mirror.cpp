#include <sstream>
#include "mirror.h"

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
bool STARTING_FROM_ORIGIN = true; // Will control whether the x values for the axises are flipped (starting on the right side)

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
/*
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
            int val;
            strVal >> val;
            data.buttons[tokensPassed - 4] = (val == 1);
         }
         startingIndex = endingIndex + 1;
         tokensPassed += 1;
      }
      endingIndex += 1;
   }
   return data;
};
*/
FrameData getFrameFromString(string str)
{
   FrameData data{};
   std::stringstream ss(str);
   std::string token;
   int i = 0;

   while (std::getline(ss, token, ',') && i < 16)
   {
      if (token.empty())
         continue; // skip trailing empty field from last comma
      int val = 0;
      std::stringstream(token) >> val;
      if (i < 4)
      { 
           data.axises[i] = (i == 0 || i == 3) && (!STARTING_FROM_ORIGIN) ? -val : val; //val <- replace with this if you get wonky values
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

AbsorbtiveMirror::AbsorbtiveMirror(string filename)
    : writeStream(fopen(filename.c_str(), "w"))
{
   string fileSuffix = filename.substr(filename.length() - 4);
   if (fileSuffix == "auto")
      maximumFrames = AbsorbtiveMirror::AUTONFRAMES;
   if (fileSuffix == "skil")
      maximumFrames = AbsorbtiveMirror::SKILLFRAMES;
};

void AbsorbtiveMirror::captureFrame(int axises[4], bool buttons[12])
{
   if (!isFull())
   {
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
