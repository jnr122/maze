# Graphics-with-Shapes

Note to Windows users: remember to copy freeglut.dll from the cmake-build-debug folder of Graphics-Starter to the cmake-build-debug folder here.

1. Read through Button.h and Button.cpp. 
2. Implement the two methods in Button.cpp that have TODO comments.
3. Read through graphics_starter.cpp. Notice the global Quad and Button objects at the top of the file, and notice where they are used throughout the file.
4. Run the program. It should have a button labeled "Spawn" that produces confetti.
5. Use an enum to get three screens:
    * A start screen that displays a message. It should not be a button, it should be a string you print. Look at the Button draw method for an example of how to do this. Pressing the ```s``` key should move you to the second screen.
    * The second screen will be the given confetti-spawning program.
    * Once 100 confetti have been spawned, go to an end screen that prints a message of your choice.
6. Make the button move with the arrow keys. You will need to add at least one method to the Button class to accomplish this.

## Extra time? Extra credit!
Create a vector of Quads to make a running background:
* Each Quad should be a different height but have the same bottom edge. They should not overlap.
* All Quads should move smoothly to the left at the same rate. Hint: use a timer for this.
* Once a Quad goes completely off the left side of the screen, move it just to the right of the screen (so that it can pass across the screen again).
* Make multiple rows of these, where each row has a different color, height range, and rate of movement. The ones closer to you (drawn on top) should be shortest and move fastest.
