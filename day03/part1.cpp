#include <fstream>
#include <iostream>
using namespace std;

int getBankJoltage(string_view bank){
	int tens{};
	int digit{};

	for(char i: bank){
		int num{i-'0'};
		if (digit > tens){
			tens = digit;
			digit = num;
			continue;
		}
		if(num > digit) {
			digit = num;
		}
	}
	return tens * 10 + digit;
}

int main (){
	ifstream input("input");
	int totalJoltage{0};
	for (string bank; getline(input, bank);){
		totalJoltage += getBankJoltage(bank);
	}
	cout << "Total Joltage: " << totalJoltage << endl;
	return 0;
}

