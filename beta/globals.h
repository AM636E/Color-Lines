#pragma once

const int SQUARE_SIZE = 50;//px

const int NUMSQUARES = 9;
const int CIRCLES_TO_ADD = 3;

enum Color
{
	RED		= 0x000000FF,
	GREEN	= 0x0000FF00,
	BLUE	= 0x00FF0000,	
	YELLOW	= 0x0000FFFF,
	AQUA	= 0x00FFFF00,
	BLACK	= 0x00000000
};

struct Square
{
	COLORREF color;
	bool	 isFilled;

	Square( ): color( RGB( 1, 1, 12 ) ), isFilled( 0 ){};
};

struct Coordinate
{
	int row, col;

	Coordinate( ): row( 0 ), col ( 0 ) {};
}static changes[ 4 ];

struct Direction
{
	int	plusToRow, plusToCol;

	Direction( ): plusToRow( 0 ), plusToCol( 0 ){};
	Direction( int plusToRow, int plusToCol ):
	plusToRow( plusToRow ), plusToCol( plusToCol )
	{};
};

struct CircleGroup
{
	Coordinate 	firstCircle;			// coordinates of first circle
	Direction	moveDir;	// direction to move on group
	int			countOfCircles;
	bool		isErase;
};
