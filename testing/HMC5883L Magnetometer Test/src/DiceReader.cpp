#include "DiceReader.hh"

DiceReader::DiceReader(Adafruit_HMC5883_Unified& magnetometer, float tolerance)
    : mag(magnetometer), tolerance(tolerance) {

    }

bool DiceReader::begin() {
    if (load()) {
        Serial.println("Loaded face signatures from memory.");
        return true;
    } else {
        Serial.println("No face signatures found in memory. Please record them.");
        return false;
    }
}

bool DiceReader::load() {
    
}