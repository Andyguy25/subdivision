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
	t1.x = 0.0;
	t1.y = 50.0;
	t1.z = 0.0;
	coord t2;
	t2.x = -50.0;
	t2.y = 30.0;
	t2.z = 0.0;
	coord t3;
	t3.x = -50.0;
	t3.y = -30.0;
	t3.z = 0.0;
	coord t4;
	t4.x = 0.0;
	t4.y = -50.0;
	t4.z = 0.0;
	coord t5;
	t5.x = 50.0;
	t5.y = -30.0;
	t5.z = 0.0;
	coord t6;
	t6.x = 50.0;
	t6.y = 30.0;
	t6.z = 0.0;
	coord t7;
	t7.x = 0.0;
	t7.y = 0.0;
	t7.z = 50.0;
	
	pointList.push_back(t1);
	pointList.push_back(t2);
	pointList.push_back(t7);

	pointList.push_back(t2);
	pointList.push_back(t3);
	pointList.push_back(t7);

	pointList.push_back(t3);
	pointList.push_back(t4);
	pointList.push_back(t7);

	pointList.push_back(t4);
	pointList.push_back(t5);
	pointList.push_back(t7);

	pointList.push_back(t5);
	pointList.push_back(t6);
	pointList.push_back(t7);

	pointList.push_back(t6);
	pointList.push_back(t1);
	pointList.push_back(t7);

	vectToVert(pointList);

	cycleNum = 0;
	sizeReducer = 1;
	srand(time(NULL));

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
Ground::midCalc(std::vector<coord>& pointList) {
	
	for (int i = 0; i < pointList.size(); i += 3) {
		coord firstMid;
		coord secondMid;
		coord thirdMid;

		//maximum random value
		double randMin = -13.0;
		//minimum random value
		double randMax = 13.0;

		randMin = randMin * sizeReducer;
		randMax = randMax * sizeReducer;
		
		double r1 = randMin + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (randMax - randMin)));
		double r2 = randMin + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (randMax - randMin)));
		double r3 = randMin + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (randMax - randMin)));

		firstMid = averageCoord(pointList[i], pointList[i+1]);
		secondMid = averageCoord(pointList[i + 1], pointList[i + 2]);
		thirdMid = averageCoord(pointList[i + 2], pointList[i]);

		//before randomizing z value, check if you've done it before so edges dont have gaps

		bool check1 = false;
		bool check2 = false;
		bool check3 = false;

		if (!checkFinal(searchList, firstMid)) {
			firstMid.z += r1;
			check1 = true;
		}

		if (!checkFinal(searchList, secondMid)) {
			secondMid.z += r2;
			check2 = true;
		}

		if (!checkFinal(searchList, thirdMid)) {
			thirdMid.z += r3;
			check3 = true;
		}
			
		//add to finalList in specific counterclockwise order
		finalList.push_back(pointList[i]);
		finalList.push_back(firstMid);
		finalList.push_back(thirdMid);

		finalList.push_back(pointList[i+1]);
		finalList.push_back(secondMid);
		finalList.push_back(firstMid);

		finalList.push_back(pointList[i+2]);
		finalList.push_back(thirdMid);
		finalList.push_back(secondMid);

		finalList.push_back(firstMid);
		finalList.push_back(secondMid);
		finalList.push_back(thirdMid);


		int indx1 = floor(firstMid.x)+50;
		int indy1 = floor(firstMid.y)+50;
		int indx2 = floor(secondMid.x)+50;
		int indy2 = floor(secondMid.y)+50;
		int indx3 = floor(thirdMid.x)+50;
		int indy3 = floor(thirdMid.y)+50;

		if (check1)
			insertSearchList(searchList, firstMid);
			//searchList[indx1][indy1].push_back(firstMid);
		if (check2)
			insertSearchList(searchList, secondMid);
			//searchList[indx2][indy2].push_back(secondMid);
		if (check3)
			insertSearchList(searchList, thirdMid);
			//searchList[indx3][indy3].push_back(thirdMid);
		
	}
	std::cout << " sizeReduced: " << sizeReducer;
	sizeReducer = (constSize * sizeReducer);

	pointList.swap(finalList);
	finalList.clear();
	//clear searchList
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			searchList[i][j].clear();
		}
	}
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
Ground::checkFinal(std::vector<coord> searchList[101][101], coord& coordToCheck) {
	
	int indx = floor(coordToCheck.x) + 50;
	int indy = floor(coordToCheck.y) + 50;
	if (searchList[indx][indy].size() > 0) {

		int minx = -1;
		int maxx = searchList[indx][indy].size();

		int midInd = floor((minx + maxx) / 2);
		double midx = searchList[indx][indy][midInd].x;

		while (((minx + 1) < maxx)) {

			if (coordToCheck.x < midx) {
				maxx = midInd;
			}

			else if (coordToCheck.x >= midx) {
				if (isEqualNoZ(coordToCheck, searchList[indx][indy][midx])) {
					coordToCheck.z = searchList[indx][indy][midx].z;
					return true;
				}
				minx = midInd;
			}
			midInd = floor((minx + maxx) / 2);
			midx = searchList[indx][indy][midInd].x;
		}
		return false;
	}
	return false;
	/*int indx = floor(coordToCheck.x)+50;
	int indy = floor(coordToCheck.y)+50;
	for (int i = 0; searchList[indx][indy].size() > i; i++) {
		if (isEqualNoZ(coordToCheck, searchList[indx][indy][i])) {
			coordToCheck.z = searchList[indx][indy][i].z;
			return true;
		}
	}
	
	return false;*/
}

void 
Ground::insertSearchList(std::vector<coord> searchList[101][101], coord& coordToCheck) {
	int indx = floor(coordToCheck.x) + 50;
	int indy = floor(coordToCheck.y) + 50;
	if (searchList[indx][indy].size()) {
		//min and max are supposed to be one lower and one higher so all numbers get checked
		int minx = -1;
		int maxx = searchList[indx][indy].size();

		int midInd = floor((minx + maxx) / 2);
		double midx = searchList[indx][indy][midInd].x;

		while (((minx + 1) < maxx)) {

			if (coordToCheck.x < midx) {
				maxx = midInd;
			}

			else if (coordToCheck.x > midx) {
				minx = midInd;
			}
			midInd = floor((minx + maxx) / 2);
			midx = searchList[indx][indy][midInd].x;
		}
		auto insertHere = searchList[indx][indy].begin() + minx;
		searchList[indx][indy].insert(insertHere, 1, coordToCheck);
	}
}

void
Ground::subdivide() {
	std::cout << "Cycle " << cycleNum+1 << " Rendering...   ";
	midCalc(pointList);
	vectToVert(pointList);
	cycleNum++;
	std::cout << " Rendered\n";
}

void
Ground::vectToVert(std::vector<coord>& pointList) {

	display_list = glGenLists(1);
	glNewList(display_list, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	int temp = 0;
	for (int i = 0; i < pointList.size(); i+=3) {
		temp++;
		coord vectU;
		vectU.x = pointList[i + 1].x - pointList[i].x;
		vectU.y = pointList[i + 1].y - pointList[i].y;
		vectU.z = pointList[i + 1].z - pointList[i].z;

		coord vectV;
		vectV.x = pointList[i + 2].x - pointList[i].x;
		vectV.y = pointList[i + 2].y - pointList[i].y;
		vectV.z = pointList[i + 2].z - pointList[i].z;

		coord surfNorm;
		surfNorm.x = (vectU.y * vectV.z) - (vectU.z * vectV.y);
		surfNorm.y = (vectU.z * vectV.x) - (vectU.x * vectV.z);
		surfNorm.z = (vectU.x * vectV.y) - (vectU.y * vectV.x);
		
		glNormal3f(surfNorm.x, surfNorm.y, surfNorm.z);
		
		int colorDeciderNum = rand() % 100;
		int gsThresh; //grass to stone threshold
		int ssThresh; //stone to snow threshold
		double colorPoint = pointList[i].z;
		
		//add noise to change the z level being compared between
		double minLineNoise = -4;
		double maxLineNoise = 4;
		double zNoise = minLineNoise + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (maxLineNoise - minLineNoise)));
		colorPoint += zNoise;

		if (colorPoint >= 40) {
			//supposed to be out of bounds so it has to be snow
			gsThresh = -1;
			ssThresh = -1;
		}
		else if (colorPoint >= 30 && colorPoint < 40) {
			gsThresh = -1;
			ssThresh = 30;
		}
		else if (colorPoint >= 20 && colorPoint < 30) {
			gsThresh = 15;
			ssThresh = 85;
		}
		else if (colorPoint >= 10 && colorPoint < 20) {
			gsThresh = 75;
			ssThresh = 101;
		}
		else if (colorPoint < 10) {
			//supposed to be out of bounds so it has to be grass
			gsThresh = 101;
			ssThresh = 101;
		}

		if (colorDeciderNum >= ssThresh) {
			glColor3f(1.0, 1.0, 1.0);
		}
		else if (colorDeciderNum >= gsThresh && colorDeciderNum < ssThresh) {
			glColor3f(0.5, 0.5, 0.5);
		}
		else if(colorDeciderNum < gsThresh){
			glColor3f(0.0, 0.35, 0.1);
		}


		glVertex3f(pointList[i].x, pointList[i].y, pointList[i].z);
		glVertex3f(pointList[i+1].x, pointList[i + 1].y, pointList[i + 1].z);
		glVertex3f(pointList[i + 2].x, pointList[i + 2].y, pointList[i + 2].z);
	}
	std::cout << "  " << temp << std::endl;

	glEnd();
	glEndList();
}