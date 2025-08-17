#include "telemetry.h"
#include <sstream>
#include <string>
#include <stdexcept>

Telemetry Telemetry::inst;

void Telemetry::registerSubtable(string tableKey, vector<EntrySet> subKeys)
{
    for (EntrySet key : subKeys)
    {
        table[tableKey][key.value] = (EntrySet){"None", key.type};
    }
};

template <typename T>
void placeValueAt(T val, string directory, string entryKey)
{
    __throw_logic_error("Val type must be an int, double, bool, or a string");
    return;
};

template <>
void Telemetry::placeValueAt<string>(string val, string directory, string entryKey)
{
    if (table.at(directory).at(entryKey).type == EntryType::STRING)
    {
        table[directory][entryKey].value = val;
    }
    else
    {
        __throw_logic_error("Placement value must be the same type as the registered type / Table value must exist");
    }
};
template <>
void Telemetry::placeValueAt<int>(int val, string directory, string entryKey)
{
    if (table.at(directory).at(entryKey).type == EntryType::INT)
    {
        ostringstream strVal;
        strVal << val;
        table[directory][entryKey].value = strVal.str();
    }
    else
    {
        __throw_logic_error("Placement value must be the same type as the registered type / Table value must exist");
    }
};

template <>
void Telemetry::placeValueAt<double>(double val, string directory, string entryKey)
{
    if (table.at(directory).at(entryKey).type == EntryType::DOUBLE)
    {
        ostringstream strVal;
        strVal << val;
        table[directory][entryKey].value = strVal.str();
    }
    else
    {
        __throw_logic_error("Placement value must be the same type as the registered type / Table value must exist");
    }
};

template <>
void Telemetry::placeValueAt<bool>(bool val, string directory, string entryKey)
{
    if (table.at(directory).at(entryKey).type == EntryType::BOOL)
    {
        ostringstream strVal;
        strVal << val;
        table[directory][entryKey].value = strVal.str();
    }
    else
    {
        __throw_logic_error("Placement value must be the same type as the registered type / Table value must exist");
    }
};

//------------------
template <typename T>
T getValueAt(string directory, string entryKey)
{
    __throw_logic_error("Type must be int, double, bool, or string");
    return T{};
};

template <>
string Telemetry::getValueAt<string>(string directory, string entryKey)
{
    if (table.at(directory).at(entryKey).type == EntryType::STRING)
    { 
        if (table.at(directory).at(entryKey).value == "None")
           return "None";
        return table[directory][entryKey].value;
    }
    else
    {
        __throw_logic_error("Template type must match registered type for this table entry");
    }
};

template <>
int Telemetry::getValueAt<int>(string directory, string entryKey)
{
    if (table.at(directory).at(entryKey).type == EntryType::INT)
    { 
        if (table.at(directory).at(entryKey).value == "None")
           return 0;
        
        stringstream strVal(table[directory][entryKey].value);
        int val;
        strVal >> val;
        return val;
    }
    else
    {
        __throw_logic_error("Template type must match registered type for this table entry");
    }
};

template <>
double Telemetry::getValueAt<double>(string directory, string entryKey)
{
    if (table.at(directory).at(entryKey).type == EntryType::DOUBLE)
    { 
        if (table.at(directory).at(entryKey).value == "None")
           return 0.0;
        stringstream strVal(table[directory][entryKey].value);
        double val;
        strVal >> val;
        return val;
    }
    else
    {
        __throw_logic_error("Template type must match registered type for this table entry");
    }
};

template <>
bool Telemetry::getValueAt<bool>(std::string directory, std::string entryKey)
{
    if (table.at(directory).at(entryKey).type == EntryType::BOOL)
    { 
        if (table.at(directory).at(entryKey).value == "None")
           return false;
        return table[directory][entryKey].value == "1";
    }
    else
    {
        __throw_logic_error("Template type must match registered type for this table entry");
        return false;
    }
};