# Knucklebones-ESP32

This repository documents my attempt at making a physical version of the *Cult of the Lamb* mini-game, Knucklebones, that plays just like its digital counterpart.

**GOAL:** 
Have a fully playable, self-contained board of Knucklebones, complete with displays for showing the score dynamically and WS2812B LEDs for confirming placements and the winner.

**Current stage:** 
Drafting the project and building the first single-sensor breadboard prototype.

---

## How the game works

Knucklebones is a turn-based dice game that takes place on two opposing 3x3 matrices, which act as the "playing field."

* The score is dictated by the number on the die face.
* On a turn, you roll a die and place it in one of the three columns of your matrix. Your score is the sum-total of all dice faces on your board.
* When you have multiple dice of the same value in the same column, your score for those dice gets a multiplier. For instance: if you have two 4s in the same column, your score for those will be `(4+4) * 2 = 16`.
* If you place a die with the same face as the opponent's in the corresponding column, all of their dice in that column with that value get removed.

The game ends when one of the two matrices gets filled up completely. The final score is then calculated, and the winner is decided.

---

## How this project makes this different

In the video game, your score is automatically calculated dynamically, as opposed to a real-life physical version where you have to do the math on the fly. 

I really like the idea of having a screen that shows you exactly what your score is, so you don't have to explain the complex math premise to a new player. This way, they can pick it up on the fly, with the board flashing errors when placing incorrectly, giving hints on how the game works, and automatically declaring the winner.

**The Hardware Approach:**
This could be done with a camera that tracks dice faces, sure. However, an overhead camera rig would make this otherwise very portable game totally impractical to take with you. Hence why I decided to make it using magnets and 3D magnetometers instead.

By putting neodymium magnets inside the dice and placing a GY-271 (QMC5883L) 3-axis magnetometer under each board slot, I can track the die face purely by reading the X, Y, and Z values of the magnetic fields. That data is relayed via I2C to an ESP32 microcontroller, which handles the game logic, does the math, and drives the LCD displays and LEDs.

---

## Technical Stack & Hardware
* **Microcontroller:** ESP32 (Handles game state, rules, and I2C communication)
* **Sensors:** GY-271 3-axis Magnetometers (One under each slot to read the magnetic vector)
* **Visuals:** WS2812B Addressable LEDs (For slot status and animations) - not set in stone
* **Displays:** I2C LCD/OLED screens (For column multipliers and total score)

## Project Roadmap
- [x] Draft project rules, hardware stack, and README
- [ ] Build single-sensor breadboard prototype
- [ ] Map the X, Y, Z magnetic values to the 6 dice faces
- [ ] Program a single-slot LED visual reaction
- [ ] Expand the I2C bus to handle multiple sensors
