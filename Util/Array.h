#ifndef ARRAY_H
#define ARRAY_H

#include <assert.h>

namespace Util{

template<typename T>
class Array{
	public:
		Array() : array(NULL), maxLen(2), len(0){
			array = new T[maxLen];
		}

		Array(const Array<T>& array) : array(NULL), maxLen(array.maxLen), len(array.len){
			this->array = new T[maxLen];
			for(int i = 0; i < len; i++) this->array[i] = array[i];
		}

		~Array(){
			delete array;
			array = NULL;
		}

		inline int length() const{
			return len;
		}

		void append(T item){
			if(len == maxLen) realloc(2*maxLen);
			array[len] = item;
			len++;
		}

		void insert(T item, int position){
			assert(position <= len && position >= 0);
			if(len == maxLen) realloc(2*maxLen);
			for(int i = len-1; i >= position; i--) array[i+1] = array[i];
			array[position] = item;
			len++;
		}

		void remove(int position){
			assert(position < len && position >= 0);
			for(int i = position; i < len-1; i++) array[i] = array[i+1];
			len --;
		}

		inline T operator[](int position) const{
			assert(position < len && position >= 0);
			return array[position];
		}

		inline bool isEmpty() const{
			return len == 0 ? true : false;
		}

	private:
		void realloc(int length){
			assert(length > len);
			maxLen = length;
			T* newArray = new T[length];
			for(int i = 0; i < len; i++) newArray[i] = array[i];
			delete array;
			array = newArray;
		}

	private:
		int maxLen;
		int len;
		T* array;
};

}

#endif
