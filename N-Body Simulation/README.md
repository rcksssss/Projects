# PS3: N-Body Simulation Part B

## Contact
Name: Tommy Boyajian
Section: 201
Time to Complete: 8 hours for part A, 5 more hours for part B

### Functionality

Fully Works


## Description
Explain what the project does.

### Part A

Part A: This project implements part A of a N-Body simulation, which focuses on 
reading and displaying a static representation of celestial bodies. The program
reads initial positions, velocities, and masses of celestial bodies from a file,
and then displays them in a graphical window without movement. Movement will be
implemented in part b. So for a summary, since this is only part a, this is just
a static representation using information given in text files.

### Part B

This project extends Part A by implementing the physics simulation and animation of the N-Body system. It simulates the motion of celestial bodies over time using Newton's laws of motion and gravitation. The program now accepts command-line arguments for total simulation time and time step, animates the movement of bodies, and outputs the final state of the universe.

### Features
Describe what your major decisions were and why you did things that way.

### Part A

-File input/output for universe needed for universe configurations
-SFML graphics which is needed for the display/visual representation
-Scale adjustment to fit different universe sizes in the window
-Background image for extra credit and to add flare to project

I added a background image once again for extra credit. I made sure to make my
thought process clear in the comments of the code and explained my thought
process behind what i created. Scaling was much needed for this assignment
especially for the different files we are working with. This also helped with
positioning bodies within the window.

### Part B

-Implementation of physics simulation using the leapfrog method

-Command-line argument parsing for simulation time and time step

-Real-time animation of celestial bodies

Force calculation between bodies using Newton's law of universal gravitation

-Velocity and position updates based on calculated forces

-Use of smart pointers for memory management of CelestialBody objects

-Real time elapsed time display in the top-left of the display window

### Implementation of Features

### Part A

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

### Part B

Physics Simulation:
Implemented the step method in the Universe class to simulate the motion of bodies over time.
Used the leapfrog method for numerical integration of equations of motion.
Calculated pairwise forces between bodies using Newton's law of universal gravitation.

Command-line Arguments:
Modified main.cpp to accept total simulation time (T) and time step (Δt) as command-line arguments.
Implemented error checking for correct number and type of arguments.

Animation:
Updated the main loop to call Universe::step and redraw the window at each time step.
Implemented smooth animation of celestial bodies' movements.

Force Calculation:
Added methods in Universe class to calculate net forces on each body.
Implemented acceleration calculation based on net forces.

Velocity and Position Updates:
Extended CelestialBody class with methods to update velocity and position based on calculated accelerations and time step.

Smart Pointer Usage:
Replaced raw pointers with std::unique_ptr for managing CelestialBody objects in the Universe class.

Output:
Added functionality to output the final state of the universe after the simulation ends. Also showed elapsed time in the top-left of the output window.

### Algorithms and Data Structures

### Part A

Used std::vector to store and manage multiple CelestialBody objects efficiently.

Implemented file I/O operations for reading and writing universe configurations.

Utilized operator overloading for streamlined input/output operations.

Developed a simple scaling algorithm to fit the universe within the display window.

Implemented basic coordinate transformation to convert between universe and window coordinates.

### Part B

Used nested loops for calculating pairwise forces between all bodies.

### Memory

## Part A

Describe how you managed the lifetimes of your objects, including if you used smart pointers.

The project uses stack-allocated objects and a std::vector in the universe class
to store celestialbody objects. This approach provides automatic memory
management without manual allocation/deallocation. SFML Texture and Sprite 
objects are managed within the Celestialbody class

### Part B

In addition to the memory management from Part A, we now use std::unique_ptr to manage the lifetimes of CelestialBody objects in the Universe class. This ensures that the CelestialBody objects are automatically deallocated when the Universe object is destroyed or when bodies are removed from the simulation. The use of smart pointers helps prevent memory leaks and provides better exception safety.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

## Part A

The main issue that I ran in with was after implementing the background
image, I had issues making the scaling of the bodies work with the background.
I later found out this was a scaling mistake on my end, but still tricked
me up in the moment.

### Part B

One challenge was ensuring the physics calculations were accurate, especially when dealing with very large or very small numbers. I learned the importance of using appropriate data types (e.g., double instead of float) for precise calculations.

Another challenge was keeping the texture of the sprites loaded between different simulation. I had gotten stuck on this for quite some time during this project and had to even debug and load simple white circles for the sprites in the simulation to make sure that its just a texture loading bug and not a simulation bug. Even though this error was annoying and tricked me up, it actually helped me become better at finding out where the bugs comes from and how to debug certain situations differently.

one last challneging part was completing the second extra-credit section for this assignment (showing the elapsed time). This was difficult due to never working with importing my own fonts before and it was difficult to figure out for me at the start. One i got it working, it was very easy to mess around with and change which was nice and it reminded me a lot of HTML5 which was funny.

### Extra Credit
Anything special you did.  This is required to earn bonus points.
If you created your own universe file.  Describe it here and explain why it is interesting.

### Part A

For the extra credit portion of this assignment, I added my own background jpg
named "image.jpg". In my submission, the "image.jpg" is attached. You can also
see the background image in the screenshot the background working correctly.

### Part B

I implemented a feature to display the elapsed simulation time on the main screen. This helps users track the progress of the simulation and provides a better understanding of the timescale involved. For this feature I also found a open-sourced font as stated in the Acknowledgements below. I used the font "LiberationMono-Regular" for the elapsed time. The time display is updated in real-time within the step() method of the Universe class.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Class Notes from Blackboard
SFML Library
Background image from google
Font from "https://github.com/liberationfonts/liberation-fonts/releases"
