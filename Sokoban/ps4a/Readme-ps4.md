# PS4: Sokoban (Part A)

## Contact
Name: Thomas Boyajian
Section: 201
Time to Complete: 4 hours


## Description
Explain what the project does.

### part a

The first part of this project (part a), I built a game/level loader and viewer
using SFML. This program reads in level data from a text file (such as level1.txt)
and displays the game board with walls, floors, boxes, storage locations, and
the player's character. For part A we only worked on building up the UI for the
game and made sure that it could load the levels from the 'sokoban' directory
and output them graphically back to the user.

### part b



### Features
Describe what your major decisions were and why you did things that way.

#### Part a

-A Sokoban class derived from sf::Drawable for rendering

-Level data loading using overloaded stream operators (>> and <<)

-Visual representation of game elements using SFML sprites

-Proper encapsulation using the SB namespace

-Basic game state tracking including:
--Player position tracking via playerLoc()
--Board dimensions via width() and height()
--Placeholder functionality for movePlayer() and isWon()

-Window sizing that adapts to level dimensions (64x64 pixel tiles)

#### Part b

### Memory
Describe how you decided to store the level data including whether you used smart pointers.

### part a

The level data is stored using a one-dimensional vector with row-major ordering for the game grid. This choice was made because:

It's more memory efficient than a vector of vectors
It simplifies iteration over the game board

The sprite textures are loaded once and shared among multiple sprites to optimize memory usage and loading times, as recommended in the assignment specifications.

### part b

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

### part a

The current implementation utilizes the std::transform algorithm with lambda expressions for:

-Converting character representations from the input file to internal game state
-Mapping game state to appropriate sprite selections during rendering

### part b

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

### part a

It took me a while to get the memory under control in this program
and kept loading the textures over and over. I learned how to manage and control
memory much better from this assignment. I also found out it was best to
use switch statements for texture loading. This made it much easier
to read and understand my code, as well as dividing all of the texture
loading for each specific texture to one part which makes it better for
debugging if needed because it would all be in one place. This also made
it easier to modify an individual texture or case without affecting others.

### part b

### Extra Credit
Anything special you did.  This is required to earn bonus points.


## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban

