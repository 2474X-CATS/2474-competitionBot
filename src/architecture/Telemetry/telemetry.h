#ifndef __TELEMETRY_H__ 
#define __TELEMETRY_H__  

#include <map> 
#include <string> 
#include <cstdlib>   
#include <vector>  
#include <iostream> 
#include <stdexcept>
using namespace std; 


typedef enum { 
   INT, 
   DOUBLE, 
   BOOL, 
   STRING
} EntryType;  


typedef struct { 
   string value; 
   EntryType type; 
} EntrySet;


class Telemetry {  
    private: 
      map<string, map<string, EntrySet>> table;
    public:   
      static Telemetry inst;  

      void registerSubtable(string tableKeys, vector<EntrySet> subKeys);   

      template <typename T> 
      void placeValueAt(T val, string directory, string entryKey);  

      template <typename T> 
      T getValueAt(string directory, string entryKey);   
      
};   




#endif