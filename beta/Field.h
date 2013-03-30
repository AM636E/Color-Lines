#pragma once
#ifndef FIELD_H
#define FIELD_H

#include <Windows.h>

#include "globals.h"

class Field
{
	Square				field[ NUMSQUARES ][ NUMSQUARES ];
	int					numEmptySquares;

public:
	Field( ): numEmptySquares( NUMSQUARES * NUMSQUARES - CIRCLES_TO_ADD ){ this ->FillWithRandColors( );};

	void				Draw( HDC hDc );

	void				SetColor( int row, int col, COLORREF color ){ field[ row ][ col ].color = color; }
	void				SetIsFilled( int row, int col, bool value ){ field[ row ][ col ].isFilled = value; }
	
	Square				Get( int row, int col )const{ return field[ row ][ col ]; }

	int*				MakeWay( int fromRow, int fromCol, int destRow, int destCol );
	bool				Move( HDC hDc, int fromRow, int fromCol, int destRow, int destCol );

	Coordinate			GetFirstCircle( const Coordinate& startCoordinate, const Direction& direction ) const;
	CircleGroup			GetSameColoredCircles( const Coordinate& startCoordinate )const;
	bool				EraseCircles( const CircleGroup& circleGroup );
	void				FillWithRandColors( );
};

#endif FIELD_H