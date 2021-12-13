// deletes an EXACT line 
//Assume the following contents in a file 
//Hello, how are you 
//You wanna play? 

// This script will only remove whole sentences like "You wanna play?" but cannot remove strings in the middle of the sentence like "wanna play?"

#include <iostream>
#include <fstream> // the class declarations for file stream objects
#include <vector>
#include <math.h>
#include <string>

void eraseFileLine(std::string path, std::string eraseLine) 
{
    std::string line;
    std::ifstream fin;
    
    fin.open(path);
    // contents of path must be copied to a temp file then
    // renamed back to the path file
    std::ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line)) 
    {
        // write all lines to temp other than the line marked for erasing
        if (line != eraseLine)
        {
            temp << line << std::endl;
        }        
    }

    temp.close();
    fin.close();

    // required conversion for remove and rename functions
    const char * p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}


int main (void)
{
    eraseFileLine("strng.txt","M140 S55.00");
    eraseFileLine("strng.txt","M104 T0 S205.00");
    eraseFileLine("strng.txt","M109 T0 S205.00");
    eraseFileLine("strng.txt","M190 S55.00");
    eraseFileLine("strng.txt","G28");
    eraseFileLine("strng.txt","M106 S0");
    eraseFileLine("strng.txt","M140 S55");
    eraseFileLine("strng.txt","M140 S45");

    return 0;
}
