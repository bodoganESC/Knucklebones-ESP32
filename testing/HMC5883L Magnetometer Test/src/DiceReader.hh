#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Preferences.h>
#include <stdint.h>

struct FaceSignature {
    float x;
    float y;
    float z;
};

class DiceReader {
public:
    static constexpr uint8_t NUM_FACES = 6;
    static constexpr uint8_t MAX_SLOTS = 18;
    DiceReader(Adafruit_HMC5883_Unified& magnetometer, uint8_t slotId, float m_tolerance);

    // Starts the preferences manager and loads saved data. 
    // Returns true if data was successfully loaded, false otherwise.
    bool begin();

    // Pulls data from ESP32 NVS. Returns false if no data is found.
    bool load();

    // Compares live XYZ to memory. Returns index 1-6, or 0 if no match is found.
    int read(float currentX, float currentY, float currentZ) const;

    // Saves the current XYZ values for the specified face.
    bool recordFace(uint8_t faceNumber, float x, float y, float z);

    // Saves all six face signatures at once. Returns false if any of the face signatures are invalid.
    bool recordAllFaces(const FaceSignature newFaces[6]);

    void eraseMemory();

    uint8_t getSlotId() const { return id; }

private:
    static constexpr const char* NVS_NAMESPACE = "dice_reader";

    Adafruit_HMC5883_Unified& mag;
    Preferences prefs;
    uint8_t id;
    float tolerance;
    FaceSignature faces[6];
    char nvsKey[12];

    // Private helpers for validation and DRY NVS operations
    bool isValidId() const;
    bool isMatch(const FaceSignature& face, float currentX, float currentY, float currentZ) const;
    bool saveToNVS();
};