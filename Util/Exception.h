#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <exception>
#include <string>

namespace Util{

/**
 * Error types.
 */
enum Error{
	UnknownError,
	BadAllocation,
	NeuronParseError,
	NeuralNetworkParseError
};

/**
 * Exception class.
 */
class Exception : public std::exception{
	public:
		Exception() : err(UnknownError), message(std::string("")){}
		Exception(const Error err) : err(err), message(std::string("")){}
		Exception(const Error err, const std::string message) : err(err), message(message){}
		Exception(Exception* ex) : err(ex->err), message(ex->message){}
		virtual ~Exception() throw(){}

		void raise() const{throw *this;}
		Exception* clone() const{return new Exception(*this);}
		const char* what() const throw(){return toString().c_str();}

		std::string toString() const{
			std::string message = (this->message.empty() ? "" : " ("+this->message+")");
			switch(err){
				case UnknownError:
					return std::string("Unknown error") + message;
				case BadAllocation:
					return std::string("Bad memory allocation") + message;
				case NeuronParseError:
					return std::string("Neuron parse error") + message;
				case NeuralNetworkParseError:
					return std::string("Neural network parse error") + message;
			}
			return std::string();
		}

	private:
		Error err;
		std::string message;
};

}

#endif // EXCEPTION_H
