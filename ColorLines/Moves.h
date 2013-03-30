#pragma once
#ifndef MOVES_H
#define MOVES_H

#include "Field.h"

int** FormLabirintFromField(
	const Field& field 
	);

bool FindWay( 
	int **labirint,
	int startRow,
	int startCol,
	int destRow,
	int destCol
	);

int* GenerateWayToDest(
	const Field& field,
	int startRow,
	int startCol,
	int destRow,
	int destCol
	);

int* GenerateWay(
	const Field& field,
	const Square& from,
	const Square& to
	);

void writeArray(
	int **arr
	);

bool IsInRect( const POINT& point, const RECT &rect );

#endif MOVES_H

