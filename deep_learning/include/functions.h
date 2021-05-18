#include <cmath>
#include <vector>
#include <cassert>

namespace Functions{
	double identity( double input){
		return input;
	}

	std::vector<double> square(const std::vector<double> &values){
		/* Square each element in the input array */
		std::vector<double> res;
		for(unsigned i = 0; i < values.size(); ++i)
			res.push_back(pow(values[i],2));
		return res;
	}

	double square_1( const double value){
		/* squares a number*/
		return pow(value,2);
	}

	std::vector<double> leakyRelu(const std::vector<double> & values){
		/* Apply leaky relu function to each element in the vector array */
		std::vector<double> res;
		for(unsigned i = 0; i < values.size(); ++i)
			res.push_back( fmax(0.2*values[i], values[i]) );
		return res;
	}

	double leakyRelu_1(const double value){
		/* Apply the leaky relu function on a number */
		return fmax(0.2*value, value);
	}

	std::vector<double> sigmoid( const std::vector<double> &values){
		/* Apply the sigmoid function to each element in the input vector array */
		std::vector<double> res;
		for(unsigned i = 0; i < values.size(); ++i)
			res.push_back( 1/(1+exp(-values[i])) );
		return res;
	}

	double sigmoid_1( const double value){
		/* Apply the sigmoid function to a number*/
			return 1/(1+exp(-value));
	}

	std::vector<double> addInputs( const std::vector<double> &x1, const std::vector<double> &x2, double(*f) (double)){
		/* function with multiple inputs and addition, forward pass: */
		assert(x1.size() == x2.size());
		std::vector<double> y;
		for(unsigned i = 0; i < x1.size(); ++i)
			y.push_back( f(x1[i] + x2[i]) );	
		return y;
	}

	std::vector<double> multipleInputsAddBackward(const std::vector<double> &x1,
			const std::vector<double> &x2,
			double(*f) (double)){
		/* computes the derivative of a simple function wrt to both inputs */
		std::vector<double> a = Functions::addInputs(x1, x2, Functions::identity);
		std::vector<double> dsda = Utils::derivative(a, f);
		//double dadx = 1, dady = 1;
		return  dsda;

	}
}
