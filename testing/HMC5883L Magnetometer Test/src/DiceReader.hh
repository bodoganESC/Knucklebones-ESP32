#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Preferences.h>

struct FaceSignature {
    float x;
    float y;
    float z;
};

class DiceReader {
    public:
        DiceReader(Adafruit_HMC5883_Unified& magnetometer, float tolerance);

        // Starts the preferences manager and loads saved data.
        void begin();

        // Compares live XYZ to memory. Returns index 1-6, or 0 if no match is found.
        int read(float currentX, float currentY, float currentZ);

        // Pulls data from ESP32 NVS. Returns false if no data is found.
        bool load();

        // Saves the current XYZ values for the specified face.
        void recordFace(int faceIndex, float x, float y, float z);

        void eraseMemory();
        
    private:
        Adafruit_HMC5883_Unified& mag;
        Preferences prefs;
        float tolerance;
        FaceSignature faces[6];

        // Helper function for the public read() method.
        bool isMatch(const FaceSignature& face, float currentX, float currentY, float currentZ);
};