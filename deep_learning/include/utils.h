#include <cmath>
#include <vector>
#include <cassert>

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
			const std::vector<double> &values, // input values
			std::vector<double (*)(double)> funcs // vector of function pointers
			){
		/* Pass the input values through the chain of functions 
		 * The vector function pointer array is in sequential order of applying the function to the input */
		std::vector<double> res;
		for(unsigned i = 0; i < values.size(); ++i){
			double temp = values[i];
			for(unsigned j = 0; j < funcs.size(); ++j){
				temp = funcs[j](temp);
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
	
	std::vector<double> chainDerivN(
			const std::vector<double> &x,
			std::vector< double (*)(double)> funcs
			){
		std::vector<double> f1_of_x, f2_of_x, df3du, df2du, df1dx, res;
		for(unsigned i = 0; i < x.size(); ++i){
			f1_of_x.push_back(funcs[0](x[i]));
			f2_of_x.push_back(funcs[1](f1_of_x[i]));
		}
		df3du = Utils::derivative(f2_of_x, funcs[2]);
		df2du = Utils::derivative(f1_of_x, funcs[1]);
		df1dx = Utils::derivative(x, funcs[0]);
		for(unsigned i = 0; i < x.size(); ++i)
			res.push_back( df3du[i] * df2du[i] * df1dx[i] );
		return res;
	}

}
