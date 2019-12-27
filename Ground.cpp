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
	coord t1;
	t1.x = 50.0;
	t1.y = 30.0;
	t1.z = 0.0;
	coord t2;
	t2.x = 50.0;
	t2.y = 70.0;
	t2.z = 40.0;
	coord t3;
	t3.x = -50.0;
	t3.y = 30.0;
	t3.z = 0.0;
	coord t4;
	t4.x = -50.0;
	t4.y=70.0;
	t4.z=40.0;
	coord t5;
	t5.x=-50.0;
	t5.y=-30.0;
	t5.z=0.0;
	coord t6;
	t6.x=50.0;
	t6.y=-30.0;
	t6.z=0.0;
	coord t7;
	t7.x=-50.0;
	t7.y=-70.0;
	t7.z=40.0;
	coord t8;
	t8.x=50.0;
	t8.y=-70.0;
	t8.z=40.0;
	coord defCoord;
	defCoord.x = 100.0;
	defCoord.y = 100.0;
	defCoord.z = 100.0;

	pointList.push_back(std::make_pair(std::make_pair(t1, t2),defCoord));
	pointList.push_back(std::make_pair(std::make_pair(t2, t3), defCoord));
	pointList.push_back(std::make_pair(std::make_pair(t3, t1), defCoord));

	pointList.push_back(std::make_pair(std::make_pair(t2, t4), defCoord));
	pointList.push_back(std::make_pair(std::make_pair(t4, t3), defCoord));
	pointList.push_back(std::make_pair(std::make_pair(t3, t2), defCoord));

	pointList.push_back(std::make_pair(std::make_pair(t1, t3), defCoord));
	pointList.push_back(std::make_pair(std::make_pair(t3, t5), defCoord));
	pointList.push_back(std::make_pair(std::make_pair(t5, t1), defCoord));

	pointList.push_back(std::make_pair(std::make_pair(t6, t1), defCoord));
	pointList.push_back(std::make_pair(std::make_pair(t1, t5), defCoord));
	pointList.push_back(std::make_pair(std::make_pair(t5, t6), defCoord));

	pointList.push_back(std::make_pair(std::make_pair(t5, t7), defCoord));
	pointList.push_back(std::make_pair(std::make_pair(t7, t6), defCoord));
	pointList.push_back(std::make_pair(std::make_pair(t6, t5), defCoord));

	pointList.push_back(std::make_pair(std::make_pair(t8, t6), defCoord));
	pointList.push_back(std::make_pair(std::make_pair(t6, t7), defCoord));
	pointList.push_back(std::make_pair(std::make_pair(t7, t8), defCoord));

	for (int i = 0; i < pointList.size(); i++) {
		if (i % 3 == 0)
			std::cout << std::endl;
		disp(pointList[i].first.first);
	}
	std::cout << std::endl;
	

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

