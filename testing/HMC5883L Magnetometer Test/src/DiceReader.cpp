#include "DiceReader.hh"

DiceReader::DiceReader(Adafruit_HMC5883_Unified& magnetometer, float tolerance)
    : mag(magnetometer), tolerance(tolerance) {

    }

bool DiceReader::begin() {
    return load();
}

bool DiceReader::load() {
    prefs.begin("dice_reader", true);
    size_t storedLength = prefs.getBytesLength("calibdata");
    if (storedLength == sizeof(faces)) {
        prefs.getBytes("calibdata", faces, sizeof(faces));
        prefs.end();
        return true;
    }
    prefs.end();
    return false;
}