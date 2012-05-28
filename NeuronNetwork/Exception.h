#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QtCore/qtconcurrentexception.h>
#include <QString>

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuronNetwork{

enum Errors{
	UnknownError,
	BadAllocation,
	IndexOutOfRange,
	ValueOfParseErrorBadKeyword,
	ValueOfParseErrorIsntDouble,
	ValueOfParseErrorIsntInt,
	ValueOfParseErrorIsntTrFc
};

class Exception : public QtConcurrent::Exception{
	public:
		Exception() : err(UnknownError), message(QString("")){}

		Exception(const Errors err) : err(err), message(QString("")){}

		Exception(const Errors err, const QString message) : err(err), message(message){}

		Exception(Exception* ex) : err(ex->err), message(ex->message){}

		virtual ~Exception() throw(){}

		void raise() const{
			throw *this;
		}

		Exception* clone() const{
			return new Exception(*this);
		}

		const char* what() const throw(){
			return toString().toStdString().c_str();
		}

		QString toString() const{
			switch(err){
				case UnknownError:
					return QString("NeuronNetwork::Exception: unknown error") + message;
				case BadAllocation:
					return QString("NeuronNetwork::Exception: bad memory allocation") + message;
				case IndexOutOfRange:
					return QString("NeuronNetwork::Exception: index out of range") + message;
				case ValueOfParseErrorBadKeyword:
					return QString("NeuronException::Exception: valueOf() parse error, unexpected keyword: ") + message;
				case ValueOfParseErrorIsntDouble:
					return QString("NeuronException::Exception: valueOf() parse error, expected double in: ") + message;
				case ValueOfParseErrorIsntInt:
					return QString("NeuronException::Exception: valueOf() parse error, expected integer in: ") + message;
				case ValueOfParseErrorIsntTrFc:
					return QString("NeuronException::Exception: valueOf() parse error, expected integer between 1 and 4, given: ") + message;
			}
		}

	private:
		Errors err;
		QString message;
};

}

#endif // EXCEPTION_H
