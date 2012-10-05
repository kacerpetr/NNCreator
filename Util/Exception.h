#ifndef EXCEPTION_H
#define EXCEPTION_H

/*
 * This file is part of neuron network implementation.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2012 Petr Kacer (kacerpetr@gmail.com)
 */

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
