/*
 * Ground.cpp: A class for drawing the ground.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */
//testcomment

#include "Ground.h"
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>


// Destructor
Ground::~Ground(void)
{
    if ( initialized )
    {
	glDeleteLists(display_list, 1);
    }
}


// Initializer. Returns false if something went wrong, like not being able to
// load the texture.
bool
Ground::Initialize(void)
{
	//test adding points to vector

	//pointList.push_back()

	////////////////////////////done test

    display_list = glGenLists(1);
    glNewList(display_list, GL_COMPILE);
	glColor3f(1.0, 1.0, 0.5);

	glBegin(GL_TRIANGLES);
		
		glNormal3f(0.0, -0.5, 1.0);
		glVertex3f(50.0, 30.0, 0.0);
		glVertex3f(50.0, 70.0, 40.0);
		glVertex3f(-50.0, 30.0, 0.0);

		glNormal3f(0.0, -0.5, 1.0);
		glVertex3f(50.0, 70.0, 40.0);
		glVertex3f(-50.0, 70.0, 40.0);
		glVertex3f(-50.0, 30.0, 0.0);

		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(50.0, 30.0, 0.0);
		glVertex3f(-50.0, 30.0, 0.0);
		glVertex3f(-50.0, -30.0, 0.0);

		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(50.0, -30.0, 0.0);
		glVertex3f(50.0, 30.0, 0.0);
		glVertex3f(-50.0, -30.0, 0.0);

		glNormal3f(0.0, 0.5, 1.0);
		glVertex3f(-50.0, -30.0, 0.0);
		glVertex3f(-50.0, -70.0, 40.0);
		glVertex3f(50.0, -30.0, 0.0);

		glNormal3f(0.0, 0.5, 1.0);
		glVertex3f(50.0, -70.0, 40.0);
		glVertex3f(50.0, -30.0, 0.0);
		glVertex3f(-50.0, -70.0, 40.0);
		

	glEnd();
    glEndList();

    initialized = true;

    return true;
}


// Draw just calls the display list we set up earlier.
void
Ground::Draw(void)
{
    glPushMatrix();
    glCallList(display_list);
    glPopMatrix();
}

