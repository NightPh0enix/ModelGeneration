
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
