/*
 * Ground.h: Header file for a class that draws the ground.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#ifndef _GROUND_H_
#define _GROUND_H_

#include <Fl/gl.h>
#include <utility> 
#include <vector>
#include <iostream>
#include <tuple>

struct coord {
	double x;
	double y;
	double z;

};

class Ground {
  private:
    GLubyte display_list;   // The display list that does all the work.
    bool    initialized;    // Whether or not we have been initialised.

  public:
    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Ground(void) { display_list = 0; initialized = false; };

    // Destructor. Frees the display lists and texture object.
    ~Ground(void);

    // Initializer. Creates the display list.
    bool    Initialize(void);

    // Does the drawing.
    void    Draw(void);
	
	std::vector<coord> pointList;
	std::vector<coord> finalList;
	std::vector<coord> searchList[101][101];


	bool isEqualNoZ(coord first, coord second);

	void disp(std::pair<std::pair<coord, coord>, coord>);

	void midCalc(std::vector<coord>& pointList);
	coord averageCoord(coord, coord);
	
	bool checkFinal(std::vector<coord> searchList[101][101], coord& coordToCheck);

	void insertSearchList(std::vector<coord> searchList[101][101], coord& coordToCheck);

	void subdivide();

	void vectToVert(std::vector<coord>& pointList);
	int cycleNum;
	double sizeReducer;
	double constSize = 0.5;
};


#endif
