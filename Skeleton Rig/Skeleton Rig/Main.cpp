
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <math.h>
using namespace std;


#define MAX_NUM_JOINTS 16

int win_width = 600, win_height = 600;
float canvas_width = 20.0f;
float canvas_height = 20.0f;

float colors[3 * MAX_NUM_JOINTS];
float translations[2 * MAX_NUM_JOINTS];
float rotations[MAX_NUM_JOINTS];

int activeID = 6; // start activeID at the lower torso (has an id of 6)
float activeRotateX;
float activeRotateY;


void init(void)
{
    for (int i = 0; i < MAX_NUM_JOINTS; i++) {
        colors[i * 3 + 0] = 0.0f; // red
        colors[i * 3 + 1] = 0.0f; // green
        colors[i * 3 + 2] = 0.0f; // blue

        translations[i * 2 + 0] = 0.0f; // x
        translations[i * 2 + 1] = 0.0f; // y

        rotations[i] = 0.0f;
    }
}

// draws a rectangle based on a given x and y coordinate of the center, and values given for width and height
void drawRect(float x, float y, float width, float height, const float* c)
{
    glColor3fv(c);
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - (width / 2), y - (height / 2));   // top left
    glVertex2f(x + (width / 2), y - (height / 2));   // top right
    glVertex2f(x + (width / 2), y + (height / 2));   // bottom right
    glVertex2f(x - (width / 2), y + (height / 2));   // bottom left
    glVertex2f(x - (width / 2), y - (height / 2));   // connect to top left
    glEnd();
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // stores the index of current joint
    // joint ids are assigned with 0 being the bottom of the rig and 15 being the head
    // the torso is given a jid of 6 as it resides in the middle of the figure
    // jids are assigned this way so users can intuitively traverse the joints up and down
    int jid;

    // _____ lower body _____

    // lower torso
    jid = 6;

    // rotate around origin
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);

    glPushMatrix();
    glPushMatrix();

    drawRect(0, 0, 3, 2, colors + jid * 3);

    // _____ left leg _____

    // left thigh
    jid = 5;

    // declare rotate point
    activeRotateX = -1;
    activeRotateY = -2 + (2 / 2);

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    drawRect(-1, -2, 1, 2, colors + jid * 3);

    // left leg
    jid = 4;

    // declare rotate point
    activeRotateX = -1;
    activeRotateY = -4 + (2 / 2);

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    drawRect(-1, -4, 1, 2, colors + jid * 3);

    // left foot
    jid = 3;

    // declare rotate point
    activeRotateX = -1.5 + (2 / 2);
    activeRotateY = -5.5 + (1 / 2);

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    drawRect(-1.5, -5.5, 2, 1, colors + jid * 3);

    // _____ right leg _____

    glPopMatrix();

    // right thigh
    jid = 2;

    // declare rotate point
    activeRotateX = 1 + (1 / 2);
    activeRotateY = -2 + (2 / 2);

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    drawRect(1, -2, 1, 2, colors + jid * 3);

    // right leg
    jid = 1;

    // declare rotate point
    activeRotateX = 1 + (1 / 2);
    activeRotateY = -4 + (2 / 2);

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    drawRect(1, -4, 1, 2, colors + jid * 3);

    // right foot
    jid = 0;

    // declare rotate point
    activeRotateX = 1.5 - (2 / 2);
    activeRotateY = -5.5 + (1 / 2);

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    drawRect(1.5, -5.5, 2, 1, colors + jid * 3);

    // _____ upper torso _____

    glPopMatrix();

    // upper torso
    jid = 7;

    // declare rotate point
    activeRotateX = 0;
    activeRotateY = 2.5 - (3 / 2);

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    glPushMatrix();
    glPushMatrix();

    drawRect(0, 2.5, 3.5, 3, colors + jid * 3);

    // _____ left arm _____

    // left arm
    jid = 8;

    // declare rotate point
    activeRotateX = -2.75 + (2 / 2);
    activeRotateY = 3.5;

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    drawRect(-2.75, 3.5, 2, 1, colors + jid * 3);

    // left forearm
    jid = 9;

    // declare rotate point
    activeRotateX = -4.75 + (2 / 2);
    activeRotateY = 3.5;

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    drawRect(-4.75, 3.5, 2, 1, colors + jid * 3);

    // left hand
    jid = 10;

    // declare rotate point
    activeRotateX = -6.25 + (1 / 1.75);
    activeRotateY = 3.5;

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    drawRect(-6.25, 3.5, 1, 1, colors + jid * 3);

    // _____ right arm _____

    glPopMatrix();

    // right arm
    jid = 11;

    // declare rotate point
    activeRotateX = 2.75 - (2 / 2);
    activeRotateY = 3.5;

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    drawRect(2.75, 3.5, 2, 1, colors + jid * 3);

    // right forearm
    jid = 12;

    // declare rotate point
    activeRotateX = 4.75 - (2 / 2);
    activeRotateY = 3.5;

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    drawRect(4.75, 3.5, 2, 1, colors + jid * 3);

    // right hand
    jid = 13;

    // declare rotate point
    activeRotateX = 6.25 - (1 / 1.75);
    activeRotateY = 3.5;

    glTranslatef(activeRotateX, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-activeRotateX, -activeRotateY, 0);

    drawRect(6.25, 3.5, 1, 1, colors + jid * 3);

    // _____ head _____

    glPopMatrix();

    // neck
    jid = 14;

    // declare rotate point
    activeRotateX = 0;
    activeRotateY = 4.5 - (1 / 1.75);

    glTranslatef(0, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-0, -activeRotateY, 0);

    drawRect(0, 4.5, 1, 1, colors + jid * 3);

    // head
    jid = 15;

    // declare rotate point
    activeRotateX = 0;
    activeRotateY = 6.15 - (2.25 / 2);

    glTranslatef(0, activeRotateY, 0);
    glRotatef(rotations[jid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-0, -activeRotateY, 0);

    drawRect(0, 6.15, 2.25, 2.25, colors + jid * 3);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    win_width = w;
    win_height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-canvas_width / 2.0f, canvas_width / 2.0f, -canvas_height / 2.0f, canvas_height / 2.0f);
    glViewport(0, 0, (GLsizei)win_width, (GLsizei)win_height);

    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) // 'esc' key
        exit(0);

    // rotate based on keyboard press
    // if a key is pressed, increment rotation by 1
    if (key == 97 || key == 65)
    {
        rotations[activeID] += 2;
    }
    // if d key is pressed, decrement rotation by 1
    if (key == 100 || key == 68)
    {
        rotations[activeID] -= 2;
    }

    // select id based on keyboard press
    // w key - increment selection
    if (key == 119 || key == 87)
    {
        // cap id number at max of 15 (since there are 16 joints)
        if (activeID++ > 14)
        {
            activeID = 15;
        }
    }
    // s key - decrement selection
    if (key == 115 || key == 83)
    {
        // ensure id is never less than 0
        if (activeID-- < 1)
        {
            activeID = 0;
        }
    }

    // change color to red to indicate current selection
    for (unsigned int i = 0; i <= 15; i++)
    {
        if (i == activeID)
        {
            colors[i * 3 + 0] = 1.0f;   // change r value to red
        }
        else
        {
            colors[i * 3 + 0] = 0.0f;
        }
    }

    glutPostRedisplay();
}


int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("2D Transformation Tree");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;

}