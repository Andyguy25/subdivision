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
#include <time.h>
#include <stdlib.h>

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


void
Ground::Draw(void)
{
    glPushMatrix();
    glCallList(display_list);
    glPopMatrix();
}

bool
Ground::isEqualNoZ(coord first, coord second) {
	if (first.x == second.x && first.y == second.y) {
		return true;
	}
	else
		return false;
}

void
Ground::disp(std::pair<std::pair<coord, coord>, coord> coor) {
	std::cout << "startX: " << coor.first.first.x << "  ";
	std::cout << "startY: " << coor.first.first.y << "  ";
	std::cout << "startZ: " << coor.first.first.z << "  \t";
	std::cout << "   ";
	std::cout << "endX: " << coor.first.second.x << "  ";
	std::cout << "endY: " << coor.first.second.y << "  ";
	std::cout << "endZ: " << coor.first.second.z << "  \t";
	std::cout << "   ";
	std::cout << "midX: " << coor.second.x << "  ";
	std::cout << "midY: " << coor.second.y << "  ";
	std::cout << "midZ: " << coor.second.z << "\n";
}

void
Ground::midCalc(std::vector<std::pair<std::pair<coord, coord>, coord>>& pointList) {
	
	coord defCoord;
	defCoord.x = 100.0;
	defCoord.y = 100.0;
	defCoord.z = 100.0;

	for (int i = 0; i < pointList.size(); i += 3) {

		//maximum random value
		double randMin = -5.0;
		//minimum random value
		double randMax = 5.0;
		srand(time(NULL));
		double r1 = randMin + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (randMax - randMin)));
		double r2 = randMin + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (randMax - randMin)));
		double r3 = randMin + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (randMax - randMin)));

		pointList[i].second = averageCoord(pointList[i].first.first, pointList[i].first.second);
		pointList[i + 1].second = averageCoord(pointList[i + 1].first.first, pointList[i + 1].first.second);
		pointList[i + 2].second = averageCoord(pointList[i + 2].first.first, pointList[i + 2].first.second);

		//before randomizing z value, check if you've done it before so edges dont have gaps
		if (!checkFinal(finalList, pointList[i].second))
			pointList[i].second.z += r1;

		if (!checkFinal(finalList, pointList[i + 1].second))
			pointList[i + 1].second.z += r2;

		if (!checkFinal(finalList, pointList[i + 2].second))
			pointList[i + 2].second.z += r3;

		//////////////////////////////////////////////////add to finalList in specific counterclockwise order
		finalList.push_back(std::make_pair(std::make_pair(pointList[i].first.first, pointList[i].second), defCoord));
		finalList.push_back(std::make_pair(std::make_pair(pointList[i].second, pointList[i+2].second), defCoord));
		finalList.push_back(std::make_pair(std::make_pair(pointList[i+2].second, pointList[i].first.first), defCoord));

		finalList.push_back(std::make_pair(std::make_pair(pointList[i+1].first.first, pointList[i+1].second), defCoord));
		finalList.push_back(std::make_pair(std::make_pair(pointList[i + 1].second, pointList[i].second), defCoord));
		finalList.push_back(std::make_pair(std::make_pair(pointList[i].second, pointList[i + 1].first.first), defCoord));

		finalList.push_back(std::make_pair(std::make_pair(pointList[i+2].first.first, pointList[i+2].second), defCoord));
		finalList.push_back(std::make_pair(std::make_pair(pointList[i + 2].second, pointList[i + 1].second), defCoord));
		finalList.push_back(std::make_pair(std::make_pair(pointList[i + 1].second, pointList[i + 2].first.first), defCoord));

		finalList.push_back(std::make_pair(std::make_pair(pointList[i].second, pointList[i+1].second), defCoord));
		finalList.push_back(std::make_pair(std::make_pair(pointList[i+1].second, pointList[i + 2].second), defCoord));
		finalList.push_back(std::make_pair(std::make_pair(pointList[i+2].second, pointList[i].second), defCoord));
	}
	pointList.swap(finalList);
	finalList.clear();
}

coord
Ground::averageCoord(coord start, coord end) {
	coord middle;
	middle.x = (start.x + end.x) / 2;
	middle.y = (start.y + end.y) / 2;
	middle.z = (start.z + end.z) / 2;
	return middle;
}

//only need z value, check if new middle vertex is in finalList, if it is, return z value
bool
Ground::checkFinal(std::vector<std::pair<std::pair<coord, coord>, coord>>& finalList, coord& coordToCheck) {
	for (int i = 0; i < finalList.size(); i++) {
		if (isEqualNoZ(coordToCheck, finalList[i].first.first)) {
			coordToCheck.z = finalList[i].first.first.z;
			return true;
		}
	}
	return false;
}

void
Ground::subdivide() {
	std::cout << "Rendering...\n";
	midCalc(pointList);
	vectToVert(pointList);
	std::cout << "Rendered\n";
}

void
Ground::vectToVert(std::vector<std::pair<std::pair<coord, coord>, coord>>& pointList) {

	glDeleteLists(display_list, 1);

	display_list = glGenLists(1);
	glNewList(display_list, GL_COMPILE);
	glColor3f(1.0, 1.0, 0.5);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < pointList.size(); i+=3) {

		coord vectU;
		vectU.x = pointList[i + 1].first.first.x - pointList[i].first.first.x;
		vectU.y = pointList[i + 1].first.first.y - pointList[i].first.first.y;
		vectU.z = pointList[i + 1].first.first.z - pointList[i].first.first.z;

		coord vectV;
		vectV.x = pointList[i + 2].first.first.x - pointList[i].first.first.x;
		vectV.y = pointList[i + 2].first.first.y - pointList[i].first.first.y;
		vectV.z = pointList[i + 2].first.first.z - pointList[i].first.first.z;

		coord surfNorm;
		surfNorm.x = (vectU.y * vectV.z) - (vectU.z * vectV.y);
		surfNorm.y = (vectU.z * vectV.x) - (vectU.x * vectV.z);
		surfNorm.z = (vectU.x * vectV.y) - (vectU.y * vectV.x);
		
		glNormal3f(surfNorm.x, surfNorm.y, surfNorm.z);
		glVertex3f(pointList[i].first.first.x, pointList[i].first.first.y, pointList[i].first.first.z);
		glVertex3f(pointList[i+1].first.first.x, pointList[i + 1].first.first.y, pointList[i + 1].first.first.z);
		glVertex3f(pointList[i + 2].first.first.x, pointList[i + 2].first.first.y, pointList[i + 2].first.first.z);
	}
	

	glEnd();
	glEndList();
}