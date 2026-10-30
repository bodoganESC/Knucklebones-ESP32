#include "DiceReader.hh"

DiceReader::DiceReader(Adafruit_HMC5883_Unified& magnetometer, uint8_t slotId, float m_tolerance)
    : mag(magnetometer), tolerance(m_tolerance) {

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

bool DiceReader::recordFace(uint8_t faceNumber, float x, float y, float z) {
    if (faceNumber < 1 || faceNumber > 6) {
        return false; // Invalid face index
    }
    faces[faceNumber - 1] = {x, y, z};
    prefs.begin("dice_reader", false);
    prefs.putBytes("calibdata", faces, sizeof(faces));
    prefs.end();
    return true;
}

bool DiceReader::recordAllFaces(const FaceSignature newFaces[6]) {
    memcpy(faces, newFaces, sizeof(faces));
    return saveToNVS();
}

bool DiceReader::saveToNVS() {
    if (!prefs.begin("dice_reader", false)) {
        return false; // Failed to start preferences
    }
    size_t written = prefs.putBytes("calibdata", faces, sizeof(faces));
    prefs.end();

    return (written == sizeof(faces));    
}