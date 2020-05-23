#include "MonteKarlo.h"
#include <chrono>
using namespace std;
using namespace std::chrono;
std::chrono::time_point<std::chrono::system_clock> start, stop;

void defaultSquare() {
	float result;
	start = std::chrono::system_clock::now();
	result = consistentMethod();
	stop = std::chrono::system_clock::now();

	cout<<"Default Time: "<< duration_cast<duration<double>>(stop - start).count()<<endl;
	cout<<"Default Square: "<<result<<endl;
}

void openMPSquare() {
	float result;
	start = std::chrono::system_clock::now();
	result = parallelMethod();
	stop = std::chrono::system_clock::now();

	cout << "OpenMP Time: " << duration_cast<duration<double>>(stop - start).count() << endl;
	cout << "OpenMP Square: " << result << endl;
}


int main() {
	float result1, result2;
	srand(time(0));

	defaultSquare();
	openMPSquare();
}