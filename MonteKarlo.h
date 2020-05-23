#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

const int numberOFDots = 3000000;
const int numberOfRounds = 3;
float distance(float x1, float y1, float x2, float y2);
bool isInside(float x, float y, float rounds[3][numberOfRounds]);
float square(float x1, float x2, float y1, float y2);
float consistentMethod();
float parallelMethod();

	//srand(time(0));
