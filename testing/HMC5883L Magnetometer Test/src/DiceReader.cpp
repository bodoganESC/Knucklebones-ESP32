#include "DiceReader.hh"

DiceReader::DiceReader(Adafruit_HMC5883_Unified& magnetometer, uint8_t slotId, float m_tolerance)
    : mag(magnetometer), id(slotId), tolerance(m_tolerance) {
        snprintf(nvsKey, sizeof(nvsKey), "slot_%u", id);
    }

bool DiceReader::begin() {
    if (!isValidId()) return false;
    return load();
}

bool DiceReader::load() {
    if (!isValidId()) return false;
    prefs.begin(NVS_NAMESPACE, true);
    size_t storedLength = prefs.getBytesLength(nvsKey);
    if (storedLength == sizeof(faces)) {
        prefs.getBytes(nvsKey, faces, sizeof(faces));
        prefs.end();
        return true;
    }
    prefs.end();
    return false;
}

int DiceReader::read(float currentX, float currentY, float currentZ) const {
    int bestFace = 0;
    float bestDistance = tolerance * tolerance;

    for (uint8_t i = 0; i < NUM_FACES; i++) {
        float dx = currentX - faces[i].x;
        float dy = currentY - faces[i].y;
        float dz = currentZ - faces[i].z;

        float distSqr = (dx * dx) + (dy * dy) + (dz * dz);

        if (distSqr < (bestDistance)) {
            bestDistance = distSqr;
            bestFace = i + 1;
        }
    }
    return bestFace;
}

bool DiceReader::recordFace(uint8_t faceNumber, float x, float y, float z) {
    if (faceNumber < 1 || faceNumber > 6) return false;
    faces[faceNumber-1] = {x, y, z};
    return saveToNVS();
}

bool DiceReader::recordAllFaces(const FaceSignature newFaces[6]) {
    memcpy(faces, newFaces, sizeof(faces));
    return saveToNVS();
}

bool DiceReader::eraseMemory() {
    if (!isValidId() || !prefs.begin(NVS_NAMESPACE, false)) {
        return false;
    }
    bool removed = prefs.remove(nvsKey);
    prefs.end();
    return removed;
}

bool DiceReader::isValidId() const {
    return (id >= 1 && id <= MAX_SLOTS);
}

bool DiceReader::saveToNVS()
{
    if (!isValidId()) {
        return false;
    }
    if (!prefs.begin(NVS_NAMESPACE, false)) {
        return false; // Failed to start preferences
    }
    size_t written = prefs.putBytes(nvsKey, faces, sizeof(faces));
    prefs.end();

    return (written == sizeof(faces));    
}