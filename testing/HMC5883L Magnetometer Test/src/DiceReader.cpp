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

bool DiceReader::recordFace(int faceIndex, float x, float y, float z) {
    if (faceIndex < 1 || faceIndex > 6) {
        return false; // Invalid face index
    }
    faces[faceIndex - 1] = {x, y, z};
    prefs.begin("dice_reader", false);
    prefs.putBytes("calibdata", faces, sizeof(faces));
    prefs.end();
    return true;
}

bool DiceReader::recordAllFaces(const FaceSignature newFaces[6]) {
    memcpy(faces, newFaces, sizeof(faces));

    if (!prefs.begin("dice_reader", false)) {
        return false; // Failed to start preferences
    }

    size_t written = prefs.putBytes("calibdata", faces, sizeof(faces));
    prefs.end();

    return (written == sizeof(faces));
}