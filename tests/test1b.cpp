#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "../deep_learning/include/utils.h" // order of declaration is imp
#include "../deep_learning/include/functions.h"

void printOutput(const std::vector<double> &arr){
	for(unsigned i = 0; i < arr.size(); ++i)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}
double f1(const double x){
	return x*x*x;
}
int main(){
	std::vector<double> in1, in2, out;
	std::srand(time(0));
	for( unsigned i = 0; i < 10; ++i){
		in1.push_back(std::rand()%10);
		in2.push_back(std::rand()%10);
	}
	std::cout << "Input1: " << std::endl;
	printOutput(in1);
	std::cout << "Input2: " << std::endl;
	printOutput(in2);

	/* Function::addInputs function */
	out = Functions::addInputs(in1, in2, f1);
	std::cout << "addInputs: Output: " << std::endl;
	printOutput(out);

	/* Function::multipleInputsAddBackward function */
	out.clear();
	out = Functions::multipleInputsAddBackward(in1, in2, f1);
	std::cout << "multipleInputsAddBackward: Output: " << std::endl;
	printOutput(out);

	return 0;
}
