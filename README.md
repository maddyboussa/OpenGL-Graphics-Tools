# Open GL Graphics Tools

## Polygon Creation Tool
Polygon Creation Tool utilizes OpenGL and the graphics pipeline to create a C++ application that allows users to draw and render polygons onto the screen.

To create this tool, I implemented a PolyObject class that stores vertex data and includes draw functionality based on said vertices. It also required in-depth understanding of OpenGL's callback function, and how vertex data is handled by both the CPU and GPU.

## Particle System
I developed a particle system simulator using C++ and OpenGL to dynamically create and render particles to the screen in a performance efficient way.

In order to do so, I implemented a Particle System class that handles the vertex data including velocity, position, and alpha over lifetime. Particle vertex data is sent to the GPU using vertex array drawing methods in order to reduce the processing power required to simulate many objects. A camera class is also created to allow users to alter the view angle of the particle system and visualize the coordinate system, as well as handling the projection of 3D objects onto a 2D viewing plane.

## Skeleton Rig

The skeleton rig tool allows users to visualize and manipulate the joints of an animtion rig skeleton.

Utilizing transformation matrices and hierarchies in C++ and OpenGL, the skeleton rig has 16 rotatable joints that can be maneuvered into a variety of custom poses. Intuitive user controls were implemented to allow users to traverse the joints and transform the position of the specific limbs and joints in a realistic manner. A text file can be found within the project directory outlining the specific user controls. This project required in-depth knowledge of OpenGL's pushMatrix() and popMatrix functions, and a solid understanding of how object transformations and rendering are processed under the hood.

## MORE COMING SOON
