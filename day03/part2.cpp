#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <stdint.h>

using namespace std;
uint_fast64_t getBankJoltage(string bank, int numOfBatteries){
	uint_fast64_t Joltage{};
	string::reverse_iterator previousLargest{bank.rend()};
	for(int batteryMult{1}; batteryMult <= numOfBatteries; batteryMult++ ){
		string::reverse_iterator largestBattery{bank.rbegin() + (numOfBatteries - batteryMult)};
		for (string::reverse_iterator rit {largestBattery}; rit != previousLargest; rit++){
			if (*rit >= *largestBattery) largestBattery = rit;
		}
		previousLargest = largestBattery;
		Joltage += (*largestBattery - '0') * pow(10,numOfBatteries-batteryMult);
	}

	return Joltage;
}

int main (){
	constexpr int numOfBatteries{12};
	ifstream input("input");
	uint_fast64_t totalJoltage{0};
	for (string bank; getline(input, bank);){
		totalJoltage += getBankJoltage(bank, numOfBatteries);
	}
	cout << "Total Joltage: " << totalJoltage << endl;
	return 0;
}

