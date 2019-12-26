//
//  main.cpp
//  Miles_Weapon_Decoder
//
//  Created by Jacob Byerline on 10/13/19.
//  Copyright © 2019 Jacob Byerline. All rights reserved.
//  cssc0927

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <map>
#include "Queue.hpp"
#include "Decoder.hpp"

#define BUFFSIZE 100000

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc == 3){
        string value;
        string key;
        string keyValues[BUFFSIZE];
        string sampleValue;
        string sampleValues[BUFFSIZE];
        int index = 0;
        int lineCounter = 0;
        
        ifstream MilesCodeFile (argv[1], ifstream::in);    //Read key and value pairings for weapon codes
        for (int i = 0; MilesCodeFile.good(); i++) {
            // first 6 values are concatenated and then added to string array (key)
            getline ( MilesCodeFile, value, ',' );
            if (lineCounter < 6) {
                lineCounter++;
                key = key + value;
            }
            // 7th value is added as the 2nd element in the string array (value)
            else {
                //remove '\n' from keys
                if (index != 0) {
                    key.erase(0, 2);
                }
                keyValues[index] = key;
                keyValues[index + 1] = value;
                index = index + 2;
                lineCounter = 0;
                key = "";
            }
        }
        //Read data input
        ifstream SampleDataFile (argv[2],ifstream::in);
        for (int i = 0; SampleDataFile.good(); i++)
        {
           // Gets sample data and adds it to sample value string array
           getline ( SampleDataFile, sampleValue, ',' );
           sampleValues[i] = sampleValue;
        }
        
        //Decode input data
        ofstream OutFile;
        OutFile.open("OutFile.csv");
        cout << "test1";
        string * weaponCodes = decode(keyValues, sampleValues);
        
        cout << "test2";
        
        for(int i = 0; weaponCodes[i].length() != 0; i++) {

            weaponCodes[i].erase(std::remove(weaponCodes[i].begin(), weaponCodes[i].end(), '\n'), weaponCodes[i].end());
            weaponCodes[i].erase(std::remove(weaponCodes[i].begin(), weaponCodes[i].end(), '\r'), weaponCodes[i].end());

            OutFile << weaponCodes[i] << ",";

        }
        OutFile.close();
        
        return 0;
    }
    else{
        
        int count = 0;
        while(argv[++count] != NULL){
            cout << "argv[" << count << "] = "  << argv[count] << endl;
        }
        cout <<  "argc = " << argc << endl;
        printf ("Error opening file or insufficient arguments\n");
        exit (EXIT_FAILURE);
    }
}
