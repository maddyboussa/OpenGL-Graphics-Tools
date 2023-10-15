
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <vector>
#include "PolyObject.h"

using namespace std;

float canvasSize[] = { 10.0f, 10.0f };
int rasterSize[] = { 800, 600 };
float mousePos[2];

// vector to store completed polygons
vector<PolyObject> completedPolygons;

// stores in-progress polygon
PolyObject activePoly;

void init(void)
{
    // initialize mouse position
    mousePos[0] = mousePos[1] = 0.0f;

    // instantiate initial polygon
    activePoly = PolyObject();
}

void display(void)
{
    // clear canvas
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // draw active polygon
    activePoly.draw(mousePos);

    // draw completed polygons
    for (unsigned int i = 0; i < completedPolygons.size(); i++)
    {
        completedPolygons[i].draw();
    }

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    rasterSize[0] = w;
    rasterSize[1] = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, canvasSize[0], 0.0, canvasSize[1]);
    glViewport(0, 0, rasterSize[0], rasterSize[1]);

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    // alter number of vertices depending on mouse clicks
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        // get canvas mouse position based on os position
        mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
        mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

        // on mouse click,
        // add new vertex to the polygon at mouse position
        activePoly.addVertex(vec2(mousePos[0], mousePos[1]));

        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    // mouse events are handled by OS, eventually. When using mouse in the raster window, it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
    mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
    mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;

        // pressing enter will finish the polygon
    case 13:
        // when polygon finished, add it to the completed list
        PolyObject tempPoly = activePoly;

        completedPolygons.push_back(tempPoly);

        // instantiate a new polygon to be active
        PolyObject newPoly;
        activePoly = newPoly;

        break;
    }
}

void menu(int value)
{
    // menu states
    switch (value)
    {
    case 0: // clear
        // clear vector of completed polygons
        completedPolygons.clear();
        glutPostRedisplay();
        break;

    case 1: //exit
        exit(0);

        // change colors
    case 2: // red
        activePoly.setColor(vec3(1, 0, 0));
        glutPostRedisplay();
        break;

    case 3: // green
        activePoly.setColor(vec3(0.451, 0.89, 0.455));
        glutPostRedisplay();
        break;

    case 4: // blue
        activePoly.setColor(vec3(0.451, 0.514, 0.89));
        glutPostRedisplay();
        break;

    case 5: // purple
        activePoly.setColor(vec3(0.463, 0.008, 0.639));
        glutPostRedisplay();
        break;

    case 6: // yellow
        activePoly.setColor(vec3(0.973, 1, 0));
        glutPostRedisplay();
        break;

    case 7: // black
        activePoly.setColor(vec3(0, 0, 0));
        glutPostRedisplay();
        break;

    default:
        break;
    }
}

// creates interactable menu on right click
void createMenu()
{
    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Blue", 4);
    glutAddMenuEntry("Purple", 5);
    glutAddMenuEntry("Yellow", 6);
    glutAddMenuEntry("Black", 7);

    glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 0);
    glutAddSubMenu("Colors", colorMenu);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(rasterSize[0], rasterSize[1]);
    glutCreateWindow("Mouse Event - draw some polygons");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    createMenu();
    glutMainLoop();
    return 0;


}