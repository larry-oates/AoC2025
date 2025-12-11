#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
	ifstream input("input");
	string operators;
	char operation;
	string operands1;
	int operand1;
	string operands2;
	int operand2;
	string operands3;
	int operand3;
	string operands4;
	int operand4;
	long long int total{0};
	
	getline(input, operands1);
	stringstream operand1s(operands1);
	getline(input, operands2);
	stringstream operand2s(operands2);
	getline(input, operands3);
	stringstream operand3s(operands3);
	getline(input, operands4);
	stringstream operand4s(operands4);
	getline(input, operators);
	stringstream operatorss(operators);

	// This needs to be updated to extract the operands correctly
	while( operand1s >> operand1 && operand2s >> operand2 && operand3s >> operand3 && operand4s >> operand4 && operatorss >> operation ){
		long long unsigned int result{0};
		switch (operation){
			case '+':{
				result = (operand1 + operand2 + operand3 + operand4);
				break;
			}
			case '*':{
				result = operand1;
				result *= operand2;
				result *= operand3;
				result *= operand4;
				break;
			}
			default: cout << "Unknown operation: " << operation << endl;
		}
		cout << result << endl;
		total += result;
	}
	cout << "Total:" << total << endl;
	return 0;
}
