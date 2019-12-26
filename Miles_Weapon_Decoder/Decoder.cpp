//
//  Decoder.cpp
//  Miles_Weapon_Decoder
//
//  Created by Jacob Byerline on 10/18/19.
//  Copyright © 2019 Jacob Byerline. All rights reserved.
//  cssc0927

#include <iostream>
#include "Decoder.hpp"
#include <map>
#include "Queue.hpp"
#define BUFFSIZE 100000

std::string * decode(std::string keyValues[], std::string sampleValues[]) {
    static std::string writeData[BUFFSIZE];
    int totalWeaponCodes = 0;
    
    //Create queue and load sample data into
    Queue inputData;
    for(int i = 0; sampleValues[i].length() != 0; i++){
        inputData.loadValue(stoi(sampleValues[i]));
    }
    
    //Create map<string, string>
    std::map<std::string, std::string> KeyValueMap;
    for (int i = 0; keyValues[i].size() != 0; i = i + 2) {
        KeyValueMap[keyValues[i]] = keyValues[i + 1];
    }

    //Find pattern checker span
    int * first2values = inputData.peek(2);                                     //BROKEN
    int patternCheckerSpan = first2values[1] - first2values[0];                 //BROKEN

    //Initialize potential key array
    std::string potentialKeys[BUFFSIZE];
    int totalPotentialKeys = 0;

    //Find potential weapon code keys
    while (!inputData.isEmpty()) {
        inputData.normalize();
        int * next7values;
        next7values = inputData.peek(7);
        int errors = 0;
        for (int i = 0; i < 7; i++) {
            int value = next7values[i];
            if (value % patternCheckerSpan != 0)
                errors++;
        }
        //Add to potential keys
        if (errors < 2) {
            //Create potential key
            std::string temp = "";
            //if 1 error
            if (errors == 1) {
                for (int i = 0; i < 7; i++) {
                    if (next7values[i] % patternCheckerSpan == 0)
                        temp += std::to_string(next7values[i]);
                }
            }
            //if 0 errors
            else {
                for (int i = 0; i < 6; i++) {
                    temp += std::to_string(next7values[i]);
                }
            }
            //Add to potential key array
            potentialKeys[totalPotentialKeys] = temp;
            totalPotentialKeys++;
        }
        //Dequeue next value
        inputData.nextValue();
    }

    //Check if keys are in map, write to file if true
    for (int i = 0; i < totalPotentialKeys; i++) {
        if ( KeyValueMap.find(potentialKeys[i]) != KeyValueMap.end() ) {
            writeData[totalWeaponCodes] = KeyValueMap[potentialKeys[i]];
            totalWeaponCodes++;
        }
    }
    
    
    return writeData;
}

