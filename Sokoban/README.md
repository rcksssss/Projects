# PS4: Sokoban (Part B)

## Contact
Name: Thomas Boyajian
Section: 201
Time to Complete: 6-8 hours


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

The second part of this project (part b), I added all the gameplay mechanics to make Sokoban fully playable. The program now handles player movement using WASD/arrow keys, allows pushing boxes into storage locations, and implements complete win condition checking. I implemented reset functionality with the 'R' key and an undo system with the 'Z' key. When a player wins, the game displays "You Win!" in the center of the screen and plays a victory sound.

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

-Complete movement system with collision detection and box pushing

-Win condition checking and victory display
Basic game mechanics including:

--Player movement using WASD/arrow keys
--Box pushing mechanics
--Storage spot detection
--Win state tracking via isWon()


Undo/Reset functionality:

-R key for level reset
-Z key for undo moves
-State tracking for proper restoration


-Victory feedback with centered text and sound

### Memory
Describe how you decided to store the level data including whether you used smart pointers.

### part a

The level data is stored using a one-dimensional vector with row-major ordering for the game grid. This choice was made because:

It's more memory efficient than a vector of vectors
It simplifies iteration over the game board

The sprite textures are loaded once and shared among multiple sprites to optimize memory usage and loading times, as recommended in the assignment specifications.

### part b

The gameplay mechanics required additional state tracking beyond the basic level data. This was managed by:

-Using the existing 2D vector for grid representation

-Adding an undo stack to store previous game states

-Maintaining initial grid state for reset functionality

-Creating a simple GameState structure to bundle related state data

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

### part a

The current implementation utilizes the std::transform algorithm with lambda expressions for:

-Converting character representations from the input file to internal game state
-Mapping game state to appropriate sprite selections during rendering

### part b

The part B implementation utilizes std::count_if with lambda expressions for:

-Counting boxes on storage locations for win condition

-Tracking total boxes and storage spots
Verifying game state through standard algorithms

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

Initially, I had trouble with the win condition where it would trigger prematurely before all boxes were properly placed. I also struggled with getting the victory text to display in the exact center of the screen. The undo system required careful consideration to ensure all game states were properly tracked and restored. Through this part of the project, I learned better state management and how to properly implement game mechanics while maintaining clean, maintainable code.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

I added a victory sound effect for completing a level
I also added a full undo system that can undo multiple moves

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
Font: https://github.com/liberationfonts/liberation-fonts/releases
Victory .wav Sound: https://pixabay.com/sound-effects/search/victory/
