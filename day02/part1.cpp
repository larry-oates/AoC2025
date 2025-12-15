#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;		

template <class T>
int numDigits(T number)
{
    int digits = 0;
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

long long unsigned int invalidIDs (long long unsigned int min, long long unsigned int max) {
	long long int total{0};
	int mostDigits{numDigits(max)};
	int leastDigits{numDigits(min)};

	if (min > max) cerr << "Min larger than Max!" << endl;

	cout << "Range: " << min << "-" << max << endl;
	cout << (static_cast<long long int>(pow(10,(leastDigits/2)-1))) << "-" << pow(10,(mostDigits/2))-1 << endl;
	for (int patten{(static_cast<int>(pow(10,(leastDigits/2)-1)))}; patten < pow(10,(mostDigits/2)); patten++) {
		long long unsigned int id {(patten * static_cast<long long unsigned int>(pow(10, numDigits(patten)))) + patten};
		cout << id << endl;
		if (id >= min && id <= max){
			total += id;
			cout << "Found ID:" << id << endl;
		}
	}
	cout << "Total: " << total << endl;
	return total;
}

int main  () {
	ifstream input("input");

	long unsigned int min {};
	long unsigned int max {};
	char range{};
	char delimiter {};
	long long unsigned int total{0};

	while ((input >> min >> range >> max >> delimiter) && range == '-' && delimiter == ',') {
		total += invalidIDs(min, max);
	}
	cout << "Total of invalid IDs: " << total <<endl;
	return 0;
}
