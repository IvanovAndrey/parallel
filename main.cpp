#include "MonteKarlo.h"
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;
time_point<system_clock> start, stop;

double defaultSquare() {
	float result;
	start = std::chrono::system_clock::now();
	result = consistentMethod();
	stop = std::chrono::system_clock::now();

	return duration_cast<duration<double>>(stop - start).count();
}

double openMPSquare() {
	float result;
	start = std::chrono::system_clock::now();
	result = parallelMethod();
	stop = std::chrono::system_clock::now();
	return duration_cast<duration<double>>(stop - start).count();	
}


int main() {
	srand(time(0));
	vector<double> time(50);

	int size = time.size();
	for (auto i = 0; i < size; i++) {
		time[i] = openMPSquare();
	}

	double avg = 0;
	for (auto& n : time) 
		avg += n;
	avg /= size;


	double d = 0;
	for (auto& n : time) 
	d += pow(avg - n, 2);
	

	d /= size == 1 ? 1 : size - 1;


	double maxError = 2.6778 * pow(d / size, 0.5);
	

	cout << " : m = " << avg << " ms, d = " << d << endl;
	cout << "99% interval: " << avg << " +- " << maxError << " ms" << endl << endl;

}