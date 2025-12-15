#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
	ifstream input("input");
	string operators;
	string line1;
	string line2;
	string line3;
	string line4;
	long long int total{0};
	
	getline(input, line1);
	stringstream line1s(line1);
	getline(input, line2);
	stringstream line2s(line2);
	getline(input, line3);
	stringstream line3s(line3);
	getline(input, line4);
	stringstream line4s(line4);
	getline(input, operators);
	stringstream operatorss(operators);
	
	char operatation{};
	char char1;
	char char2;
	char char3;
	char char4;
	long long currentResult{0};
	char currentOp{};
	while (operatorss >> noskipws >> operatation &&
		line1s >> noskipws >> char1 &&
		line2s >> noskipws >> char2 &&
		line3s >> noskipws >> char3 &&
		line4s >> noskipws >> char4){
		int currentNum{0};
		bool validNum{false};
		if (operatation != ' '){
			total += currentResult;
			currentResult = 0;
			currentOp = operatation;
		}
		// Not being DRY here, no point when It's this few times and never to be expanded
		if (char1 != ' '){
			currentNum = char1 - '0';
			validNum = true;
		}
		if (char2 != ' '){
			currentNum *= 10;
			currentNum += char2 - '0';
			validNum = true;
		}
		if (char3 != ' '){
			currentNum *= 10;
			currentNum += char3 - '0';
			validNum = true;
		}
		if (char4 != ' '){
			currentNum *= 10;
			currentNum += char4 - '0';
			validNum = true;
		}
		if (validNum){
			if (currentOp == '+'){
				currentResult += currentNum;
			}
			else if (currentOp == '*'){
				// Special case for the first number
				if (operatation == '*') currentResult = currentNum;
				else currentResult *= currentNum;
			}
		}


	}
	total += currentResult;
	
	cout << "Total:" << total << endl;
	return 0;
}
