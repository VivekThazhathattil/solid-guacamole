#include <iostream>
#include <vector>
#include "../deep_learning/include/functions.h"
#include <fstream>

void printOutput(const std::vector<double> &arr){
	for(unsigned i = 0; i < arr.size(); ++i)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}
/***************************************/
/* Test function for derivative */

double testFunc(const double val){
	return (val - 2.0)*(val - 2.0);
}
/***************************************/
/* Test functions for chain */
double f1 ( const double val){
	return (val+1)/2;
}
double f2 ( const double val){
	return val*val*val;
}
double f3 ( const double val){
	return (val-11);
}
double f4 ( const double val){
	return (val+3)*(val+3);
}
/***************************************/
int main(){
	std::vector<double> in = {-2.0, -1.0, 3.0, 4.0};
	std::vector<double> out;

	/* prints input */
	std::cout << "Input: " << std::endl;
	printOutput(in);

	/* test for Functions::square function */
	out = Functions::square(in);	
	std::cout << "Test: Functions::square" << std::endl;
	printOutput(out);

	/* test for Functions::leakyRelu function */
	out.clear();
	out = Functions::leakyRelu(in);
	std::cout << "Test: Functions::leakyRelu" << std::endl;
	printOutput(out);

	/* test for Utils::derivative function */
	out.clear();
	out = Utils::derivative(in, testFunc, 0.001);
	std::cout << "Test: Utils::derivative" << std::endl;
	printOutput(out);	

	/* test for Utils::chain function */
	out.clear();
	std::vector<double (*)(double)> functions;
	functions.push_back(f1);
	functions.push_back(f2);
	functions.push_back(f3);
	functions.push_back(f4);
	out = Utils::chain(in, functions);
	std::cout << "Test: Utils::chain" << std::endl;
	printOutput(out);	

	/* test for Utils::chainDeriv2 function */
	out.clear();
	out = Utils::chainDeriv2(in, f1, f2);
	std::cout << "Test: Utils::chainDeriv2" << std::endl;
	printOutput(out);

	/* for verifying plots of chain derivative expression -> save to file*/
	std::ofstream saveFile;
	saveFile.open("../data/saveData.txt");
	if(!saveFile.is_open()){
		std::cerr << "File open error!" << std::endl;
		exit(1);
	}	

	std::vector<double> x;
	for( float i = -3; i <= 3; i+=0.01){
		x.push_back(i);
	}

	std::vector<double> y1, y2, y3, y4;
	functions.clear();
	functions.push_back(Functions::sigmoid);
	functions.push_back(Functions::square);
	y1 = Utils::chain(x, functions);
	y2 = Utils::chainDeriv2(x, Functions::sigmoid, Functions::square);

	functions.clear();
	functions.push_back(Functions::square);
	functions.push_back(Functions::sigmoid);
	y3 = Utils::chain(x, functions);
	y4 = Utils::chainDeriv2(x, Functions::square, Functions::sigmoid);

	for( unsigned i = 0; i < x.size(); ++i)
		saveFile << x[i] << "\t" << y1[i] << "\t" << y2[i] << "\t" << y3[i] << "\t" << y4[i] << std::endl;
	saveFile.close();	
	return 0;
}
