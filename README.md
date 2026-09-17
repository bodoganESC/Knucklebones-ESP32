# Knucklebones-ESP32
This repository is to document my try at making the physical version of the Cult of The Lamb game, Knucklebones, closer to its' digital counterpart.

GOAL:
Have a fully playable board of Knucklebones, complete with displays for showing score and LEDs for confirming the winner.

Current stage:
Drafting of project.

<h5>How the game works</h5>

Knucklebones is a turn based dice game that takes place on two opposing matrices, which are the "playing field".
Score is dictated by the number on the dice face.
On a turn, you must roll the dice and then place it in one of the three columns of your matrix. Your score is the sum-total of all dice faces on your board.
When you have multiple dice of the same value in the same column, your score for those dice gets a multiplier.
For instance: if you have two fours in the same column, your score for those will be (4+4)*2 = 16.
However, if you place a dice with the same face as the opponents', in the same column, all of their dice in that column with that value get removed.
The game ends when one of the two matrices gets filled up completely.

Score is then calculated and the winner is decided.

<h5>How this project makes this different</h5>

In the game your score is automatically calculated dynamically, as opposed to real life where you have to do the math on the fly.
I really like the idea of having a screen that shows you exactly how much score you have, so you don't have to explain
the premise of the game to someone. This way they could pick it up on the fly, with errors when placing incorrectly and
hints to how the game works and who the winner was on a game.

This could be done with a camera that tracks dice faces, sure. However, this would make this otherwise very portable game totally impractical
to take with you. Hence why I decided to make it using magnets and the hall effect.

Using 3D magnetometers and dice with magnets inside, I should be able to track the dice face purely by the XYZ values of the magnetic fields,
allowing me to relay that data to an ESP32 that can make those calculations and display everything via displays and LEDs.
