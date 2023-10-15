#include "PolyObject.h"
#include <GL/freeglut.h>
#include <iostream>

// constructor
PolyObject::PolyObject()
{
}

// destructor
PolyObject::~PolyObject()
{
}

// adds new vertex to the end of the vector (list)
void PolyObject::addVertex(vec2 p_vert)
{
	vertices.push_back(p_vert);
}

// sets current polygon color to a new color
void PolyObject::setColor(vec3 p_color)
{
	color = p_color;
}

// returns the number of vertices of the polygon
unsigned int PolyObject::getVertNum()
{
	return vertices.size();
}

// draw completed polygon
void PolyObject::draw()
{
	// establish drawing color and point size
	glColor3f(color[0], color[1], color[2]);
	glPointSize(10.0f);

	// determine drawing mode based on number of vertices
	switch (getVertNum())
	{
	case 1:
		// if polygon contains one vertex, draw a point
		glBegin(GL_POINTS);
		glVertex2fv(vec2ToGLFloat(vertices[0]));
		glEnd();
		break;

	case 2:
		// if polygon contains two vertices, draw a line
		glBegin(GL_LINES);
		glVertex2fv(vec2ToGLFloat(vertices[0]));
		glVertex2fv(vec2ToGLFloat(vertices[1]));
		glEnd();
		break;

	default:
		// if polygon contains 3 or more vertices, draw a polygon
		glBegin(GL_POLYGON);
		for (unsigned int i = 0; i < getVertNum(); i++)
		{
			glVertex2fv(vec2ToGLFloat(vertices[i]));
		}
		glEnd();
		break;
	}
}

// draw polygon mid-creation
void PolyObject::draw(float* p_mousePos)
{
	// establish drawing color and point size
	glColor3f(color[0], color[1], color[2]);
	glPointSize(10.0f);

	// determine drawing mode based on number of vertices
	switch (getVertNum())
	{
	case 1:
		// if polygon contains one vertex, draw a line from vertex to mouse position
		glBegin(GL_LINES);
		glVertex2fv(vec2ToGLFloat(vertices[0]));
		glVertex2fv(p_mousePos);
		glEnd();
		break;

	default:
		// if polygon contains 2 or more vertices, draw vertices and mouse position
		glBegin(GL_POLYGON);
		for (unsigned int i = 0; i < getVertNum(); i++)
		{
			glVertex2fv(vec2ToGLFloat(vertices[i]));
		}
		glVertex2fv(p_mousePos);
		glEnd();
		break;
	}
}

// convert from vec2 to an array
float* PolyObject::vec2ToGLFloat(vec2 vectorToConvert)
{
	// establish array to store coordinates
	float v[2];

	// parse data from vector to new array
	v[0] = vectorToConvert[0];
	v[1] = vectorToConvert[1];

	return v;
}
