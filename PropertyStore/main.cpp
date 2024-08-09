#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;


// This will act as database it is nested map
map<string, map<string ,string>> database;

// Filename of persistent storage
string filename = "database.txt";

/* The setValue function stores property values indexed by section name and property name within that section.
 * A single section can have multiple property names within it and multiple sections may contain properties of the same name without conflict.
 * A section will not contain another section (no nesting of sections)
 * Section names, property names, and property values are all strings
 * A default value is supplied for properties if one isn't given.
 * All property values are immediately saved to persistent storage when assigned a new value.
 * Persistent storage is in a human-readable tab separated format
 */


void setValue(string& sectionName, string& propertyName, string  propertyValue = "$10,000,000") {
    map<string, string> property;
    property[propertyName] = propertyValue;
    database.insert({sectionName,property});

    ofstream file(filename);
    if(file.is_open()){
        file << "Section Name\t" << "Property Name\t" << "Property Value\t" <<endl;
        for(const auto& section : database){
            for(const auto& prop : section.second) {
                file << section.first << "\t\t" << prop.first << "\t\t" << prop.second <<endl;
            }
        }
        file.close();
        cout << "Data saved to file: " << filename << endl;
    }
    else{
        cerr<< "Unable to open file for writing" << endl;
    }

}

/* The getValue function extracts and displays property values from the database map.
 */
void getValue(string& sectionName, string& propertyName) {
    auto it  = database.find(sectionName);
    if (it != database.end()) {
        map property = it->second;
        auto ind = property.find(propertyName);
        if (ind != property.end()) {
            const string& propertyValue = ind->second;
            std::cout << "Property found in Section: " << it->first << ", Property Name: " << ind->first << ", Value: " << ind->second <<std::endl;
        }
    }
    else {
        std::cout << "Property not found" << std::endl;
    }

}
int main()
{
    //testing some values.
    string sN = "District 10";
    string pN = "St Barts";
    string pV = "20,000,000";
    setValue(sN, pN );
    getValue(sN, pN);
    return 0;
}
