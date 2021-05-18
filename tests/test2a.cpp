#include "../deep_learning/include/matrix.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

int main(){
	std::srand(time(0));
	std::cout << "Matrix Tests" << std::endl;	
	Matrix matA(3,5);	
	Matrix matB(3,5);	
	Matrix matC(5,3);

	matA.print();
	std::cout << std::endl;
	matA.set(1,1,5);
	matA.set(1,4,10);
	matA.set(2,4,-1);
	matA.print();
	std::cout << std::endl;
	std::cout << "The value at (1,4) = " << matA(1,4) << std::endl;

	std::cout << std::endl;
	matA.T();
	matA.print();

	std::cout << std::endl;
	matA.transpose();
	matA.print();

	for( unsigned i = 0; i < matA.getRows(); ++i)
		for( unsigned j = 0; j < matA.getCols(); ++j){
			matA.set(i,j, std::rand()%5);	
			matB.set(i,j, std::rand()%5);	
		}
	std::cout << "MatA: " << std::endl;
	matA.print();
	std::cout << "MatB: " << std::endl;
	matB.print();

	std::cout << "MatA + MatB: " << std::endl;
	(matA+matB).print();

	std::cout << "MatA - MatB: " << std::endl;
	(matA - matB).print();

	std::cout << "MatA * MatB.T(): " << std::endl;
	(matA*matB.T()).print();
	matB.T();

	std::cout << "MatA * 5: " << std::endl;
	(matA*5).print();

	std::cout << "MatA / 5: " << std::endl;
	(matA/5).print();

	return 0;
}
