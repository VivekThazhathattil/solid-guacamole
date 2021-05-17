#include <cmath>
#include<vector>

namespace Functions{
	std::vector<double> square(const std::vector<double> &values){
		/* Square each element in the input array */
		std::vector<double> res;
		for(unsigned i = 0; i < values.size(); ++i)
			res.push_back(pow(values[i],2));
		return res;
	}

	std::vector<double> leakyRelu(const std::vector<double> & values){
		/* Apply leaky relu function to each element in the vector array */
		std::vector<double> res;
		for(unsigned i = 0; i < values.size(); ++i)
			res.push_back( fmax(0.2*values[i], values[i]) );
		return res;
	}

	std::vector<double> sigmoid( const std::vector<double> &values){
		/* Apply the sigmoid function to each element in the input vector array */
		std::vector<double> res;
		for(unsigned i = 0; i < values.size(); ++i)
			res.push_back( 1/(1+exp(-values[i])) );
		return res;
	}

	double sigmoid( const double value){
		/* Apply the sigmoid function to a number*/
			return 1/(1+exp(-value));
	}

	double square( const double value){
		/* squares a number*/
		return pow(value,2);
	}
}

namespace Utils{
	std::vector<double> derivative(
			const std::vector<double> & values, // input values
			double  (*f)(double), // function whose derivative we need
			const double delta = 0.001 // the delta step required to calculate the derivative
			){
		/* Evaluates the derivative of a function at every element in the input vector array */
		std::vector<double> res;
		for(unsigned i = 0; i < values.size(); ++i)
			res.push_back( ( (*f)(values[i] + delta) - (*f)(values[i] - delta) )/(2*delta) );
		return res;
	}

	std::vector<double> chain( 
			const std::vector<double> & values, // input values
			std::vector<double (*)(double)> vectorOfFunctions // vector of function pointers
			){
		/* Pass the input values through the chain of functions 
		 * The vector function pointer array is in sequential order of applying the function to the input */
		std::vector<double> res;
		for(unsigned i = 0; i < values.size(); ++i){
			double temp = values[i];
			for(unsigned j = 0; j < vectorOfFunctions.size(); ++j){
				temp = vectorOfFunctions[j](temp);
			}
			res.push_back(temp);
		}
		return res;
	}

	std::vector<double> chainDeriv2(
			std::vector<double> values, // note: here values are not called by reference and hence subject to change
			double (*f1)(double),
			double (*f2)(double)
			){
		/* Use the chain rule to compute the derivative of two nested functions f1 and f2. */
		std::vector<double> res, df1dx, df2du, f1_of_x;
		for(unsigned i = 0; i < values.size(); ++i)
			f1_of_x.push_back( (*f1)(values[i]) );
		df1dx = Utils::derivative(values, (*f1));
		df2du = Utils::derivative(f1_of_x, (*f2));
		for(unsigned i = 0; i < values.size(); ++i)
			res.push_back(df1dx[i] * df2du[i]);
		return res;
	}
}
