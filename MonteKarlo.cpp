#include "MonteKarlo.h"

float distance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

bool isInside(float x, float y, float rounds[3][numberOfRounds]) {
	for (int j = 0; j < numberOfRounds; j++)
	{
		if (distance(x, y, rounds[0][j], rounds[1][j])
			<= rounds[2][j])
			return true;
	}
	return false;
}
float square(float x1, float x2, float y1, float y2) {
	return (distance(x1, 0, x2, 0) * distance(0, y1, 0, y2));
}


float consistentMethod() {
	float area[4] = { 0 };
	float* dotsX = new float[numberOFDots];
	float* dotsY = new float[numberOFDots];
	float rounds[3][numberOfRounds];
	int dotsInside = 0;
	

	//“естовое заполнение дл€ проверки площади
	//X
	rounds[0][0] = 2;
	rounds[0][1] = -3;
	rounds[0][2] = 8;
	//Y
	rounds[1][0] = 4;
	rounds[1][1] = -5;
	rounds[1][2] = -9;
	//R
	rounds[2][0] = 4;
	rounds[2][1] = 5;
	rounds[2][2] = 3;

	area[0] = rounds[0][0] + rounds[2][0]; //max X
	area[1] = rounds[0][0] - rounds[2][0]; //min X
	area[2] = rounds[1][0] + rounds[2][0]; //max Y
	area[3] = rounds[1][0] - rounds[2][0]; //min Y

	//ќпределение границ области постановки точек
	for (int i = 0; i < numberOfRounds; i++)
	{
		if (rounds[0][i] + rounds[2][i] > area[0])
			area[0] = rounds[0][i] + rounds[2][i];
		if (rounds[0][i] - rounds[2][i] < area[1])
			area[1] = rounds[0][i] - rounds[2][i];
		if (rounds[1][i] + rounds[2][i] > area[2])
			area[2] = rounds[1][i] + rounds[2][i];
		if (rounds[1][i] - rounds[2][i] < area[3])
			area[3] = rounds[1][i] - rounds[2][i];
	}
	int j;
	//√енераци€ случайных точек
	for (j = 0; j < numberOFDots; j++) {
		dotsX[j] = (float)(rand() % (int)(area[0] - area[1]) + area[1]);// +(float)(rand() % 100) / 1000.0;
		dotsY[j] = (float)(rand() % (int)(area[2] - area[3]) + area[3]);// +(float)(rand() % 100) / 1000.0;
	}

	int i = 0;
	// определение количества попадающих в круги точек
	for (i = 0; i < numberOFDots; i++)
	{
		if (isInside(dotsX[i], dotsY[i], rounds))
			dotsInside++;
	}
	delete[] dotsX;
	delete[] dotsY;
	// ¬ычисление площади
	return square(area[0], area[1], area[2], area[3]) * dotsInside / numberOFDots;

}


float parallelMethod() {
	float area[4] = { 0 };
	float* dotsX = new float[numberOFDots];
	float* dotsY = new float[numberOFDots];
	float rounds[3][numberOfRounds];
	int dotsInside = 0;


	//“естовое заполнение дл€ проверки площади
	//X
	rounds[0][0] = 2;
	rounds[0][1] = -3;
	rounds[0][2] = 8;
	//Y
	rounds[1][0] = 4;
	rounds[1][1] = -5;
	rounds[1][2] = -9;
	//R
	rounds[2][0] = 4;
	rounds[2][1] = 5;
	rounds[2][2] = 3;



	area[0] = rounds[0][0] + rounds[2][0]; //max X
	area[1] = rounds[0][0] - rounds[2][0]; //min X
	area[2] = rounds[1][0] + rounds[2][0]; //max Y
	area[3] = rounds[1][0] - rounds[2][0]; //min Y

	//ќпределение границ области постановки точек
	for (int i = 0; i < numberOfRounds; i++)
	{
		if (rounds[0][i] + rounds[2][i] > area[0])
			area[0] = rounds[0][i] + rounds[2][i];
		if (rounds[0][i] - rounds[2][i] < area[1])
			area[1] = rounds[0][i] - rounds[2][i];
		if (rounds[1][i] + rounds[2][i] > area[2])
			area[2] = rounds[1][i] + rounds[2][i];
		if (rounds[1][i] - rounds[2][i] < area[3])
			area[3] = rounds[1][i] - rounds[2][i];
	}
	int j;
	//√енераци€ случайных точек
#pragma omp parallel for num_threads(32)
	for (j = 0; j < numberOFDots; j++) {
		dotsX[j] = (float)(rand() % (int)(area[0] - area[1]) + area[1]);// +(float)(rand() % 100) / 1000.0;
		dotsY[j] = (float)(rand() % (int)(area[2] - area[3]) + area[3]);// +(float)(rand() % 100) / 1000.0;
	}

	int i = 0;
	// определение количества попадающих в круги точек
#pragma omp parallel for reduction(+:dotsInside) num_threads(32)//shared(dotsInside)
	for (i = 0; i < numberOFDots; i++)
	{
		if (isInside(dotsX[i], dotsY[i], rounds))
			dotsInside++;
	}
	delete[] dotsX;
	delete[] dotsY;
	// ¬ычисление площади
	return square(area[0], area[1], area[2], area[3]) * dotsInside / numberOFDots;

}

