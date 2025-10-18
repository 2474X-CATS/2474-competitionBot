#ifndef __TELEMETRY_H__
#define __TELEMETRY_H__
/*
  Logs values on a seperate thread for easy access

  Ex:
    *Making a subtable to store entries about your intake*
    First make the subtable...
    "Telemetry::inst.registerSubtable(
      "intake", // subtable name
      {
        (EntrySet){"is_spinning_in", EntryType::BOOL}, <- Declares that there is going to be an entry called "is_spinning_in" that is a boolean (true/false)
        (EntrySet){"motor_voltage", EntryType::DOUBLE}
      }
    )"
                                         (double)
    from there you can update values...     |
                                            V
    "Telemetry::inst.placeValueAt<double>( 30, "intake", "motor_voltage");""

    and you can get values

    double intake_voltage = Telemetry::inst.getValueAt<double>("intake","motor_voltage");
    cout << intake_voltage;
         |
         V
    |stdout: 30|

*/
#include <map>
#include <vector>

using namespace std;

typedef enum
{
  INT,
  DOUBLE,
  BOOL,
  STRING
} EntryType;

struct EntrySet
{
  string value;
  EntryType type;
};

class Telemetry
{
private:
  map<string, map<string, struct EntrySet>> table; //A table of every subtable possible

public:
  static Telemetry inst; //Only need one telemetry class

  void registerSubtable(string tableKeys, vector<struct EntrySet> subKeys); //Create a new subtable with a key, entry names, and types for those entry names using EntryType
                                                                            //Would make like (EntrySet){entry_key, EntryType::type}
  template <typename T>
  void placeValueAt(T val, string directory, string entryKey); // Place a appropriately typed value at a certain subtable:key entry

  template <typename T>
  T getValueAt(string directory, string entryKey); // Retrieve a appropriately typed value from a certain subtable:key entry
};

#endif