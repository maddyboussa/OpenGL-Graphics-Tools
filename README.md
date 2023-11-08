# Open GL Graphics Tools

## Polygon Creation Tool
Polygon Creation Tool utilizes OpenGL and the graphics pipeline to create a C++ application that allows users to draw and render polygons onto the screen.

To create this tool, I implemented a PolyObject class that stores vertex data and includes draw functionality based on said vertices. It also required in-depth understanding of OpenGL's callback function, and how vertex data is handled by both the CPU and GPU.

## Particle System
I developed a particle system simulator using C++ and OpenGL to dynamically create and render particles to the screen in a performance efficient way.

In order to do so, I implemented a Particle System class that handles the vertex data including velocity, position, and alpha over lifetime. Particle vertex data is sent to the GPU using vertex array drawing methods in order to reduce the processing power required to simulate many objects. A camera class is also created to allow users alter the view angle of the particle system and visualize the coordinate system, as well as handling the projection of 3D objects onto a 2D viewing plane.

## MORE COMING SOON
