# PS3: N-Body Simulation

## Contact
Name: Tommy Boyajian
Section: 201
Time to Complete: 8 hours give or take


## Description
Explain what the project does.

Part A: This project implements part A of a N-Body simulation, which focuses on 
reading and displaying a static representation of celestial bodies. The program
reads initial positions, velocities, and masses of celestial bodies from a file,
and then displays them in a graphical window without movement. Movement will be
implemented in part b. So for a summary, since this is only part a, this is just
a static representation using information given in text files.

### Features
Describe what your major decisions were and why you did things that way.

-File input/output for universe needed for universe configurations
-SFML graphics which is needed for the display/visual representation
-Scale adjustment to fit different universe sizes in the window
-Background image for extra credit and to add flare to project

I added a background image once again for extra credit. I made sure to make my
thought process clear in the comments of the code and explained my thought
process behind what i created. Scaling was much needed for this assignment
especially for the different files we are working with. This also helped with
positioning bodies within the window.

### Implementation of Features

Universe and CelestialBody Classes:
Implemented Universe class to manage the entire simulation, storing CelestialBody objects in a std::vector.
CelestialBody class represents individual celestial objects, storing their position, velocity, mass, and visual representation.

File Input/Output:
Overloaded >> and << operators for both Universe and CelestialBody classes.
Universe::read method parses the input stream to populate the universe with celestial bodies.
Universe::write method outputs the current state of the universe in the same format as the input.

SFML Graphics Integration:
Both Universe and CelestialBody inherit from sf::Drawable, allowing them to be drawn directly to an SFML window.
CelestialBody::draw method renders the body's sprite.
Universe::draw method handles scaling and positioning of all bodies within the window.

Scaling and Positioning:
Implemented in Universe::draw method.
Calculates a scale factor based on the universe radius and window size.
Transforms each body's position from universe coordinates to window coordinates.

Background Image:
Added setBackground method to Universe class to load and scale a background image.
Background is drawn first in Universe::draw method, ensuring it appears behind celestial bodies.

Error Handling:
Implemented basic error checking for file operations and texture loading.
Uses std::cerr to output error messages when issues occur.

Main Application Loop:
Set up in main.cpp to create a window, read universe data, and continuously render the scene.
Handles window events to allow proper closure of the application.

### Algorithms and Data Structures

Used std::vector to store and manage multiple CelestialBody objects efficiently.
Implemented file I/O operations for reading and writing universe configurations.
Utilized operator overloading for streamlined input/output operations.
Developed a simple scaling algorithm to fit the universe within the display window.
Implemented basic coordinate transformation to convert between universe and window coordinates.

### Memory
Describe how you managed the lifetimes of your objects, including if you used smart pointers.

The project uses stack-allocated objects and a std::vector in the universe class
to store celestialbody objects. This approach provides automatic memory
management without manual allocation/deallocation. SFML Texture and Sprite 
objects are managed within the Celestialbody class

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

The main issue that I ran in with was after implementing the background
image, I had issues making the scaling of the bodies work with the background.
I later found out this was a scaling mistake on my end, but still tricked
me up in the moment.

### Extra Credit
Anything special you did.  This is required to earn bonus points.
If you created your own universe file.  Describe it here and explain why it is interesting.

For the extra credit portion of this assignment, I added my own background jpg
named "image.jpg". In my submission, the "image.jpg" is attached. You can also
see the background image in the screenshot the background working correctly.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Class Notes from Blackboard
SFML Library
