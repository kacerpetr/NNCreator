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

#include <QtCore/qtconcurrentexception.h>
#include <QString>

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuronNetwork{

/**
 * Error types.
 */
enum Error{
	UnknownError,
	BadAllocation,
	NeuronParseError,
	LayerParseError
};

/**
 * Exception class.
 */
class Exception : public QtConcurrent::Exception{
	public:
		Exception() : err(UnknownError), message(QString("")){}
		Exception(const Error err) : err(err), message(QString("")){}
		Exception(const Error err, const QString message) : err(err), message(message){}
		Exception(Exception* ex) : err(ex->err), message(ex->message){}
		virtual ~Exception() throw(){}

		void raise() const{throw *this;}
		Exception* clone() const{return new Exception(*this);}
		const char* what() const throw(){return toString().toStdString().c_str();}

		QString toString() const{
			switch(err){
				case UnknownError:
					return QString("NeuronNetwork::Exception: unknown error ") + message;
				case BadAllocation:
					return QString("NeuronNetwork::Exception: bad memory allocation ") + message;
				case NeuronParseError:
					return QString("NeuronNetwork::Exception: neuron parse error ") + message;
				case LayerParseError:
					return QString("NeuronNetwork::Exception: layer parse error ") + message;
			}
			return QString();
		}

	private:
		Error err;
		QString message;
};

}

#endif // EXCEPTION_H
