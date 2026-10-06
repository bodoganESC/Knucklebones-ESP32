#include "DiceReader.hh"

DiceReader::DiceReader(Adafruit_HMC5883_Unified& magnetometer, float tolerance)
    : mag(magnetometer), tolerance(tolerance) {
        
    }