/*
 * stack.hpp
 *
 *  Created on: Jul 29, 2025
 *      Author: Oleksiy
 */

#ifndef NIKOLEX_UTILS_STACK_HPP_
#define NIKOLEX_UTILS_STACK_HPP_

#include "cstdint"

namespace nikolex {

template<typename T, uint8_t size>
class Stack {
	T list[size];
	int8_t index;
public:
	Stack(){index = -1;}

	T * getCurrentItem(){return &list[index];}
	T * push(const T& item){
		index++;
		list[index] = item;
		return &list[index];
	}

	T * pop(){
		T * lastItem = &list[index];
		index--;
		return lastItem;
	}
};

}




#endif /* NIKOLEX_UTILS_STACK_HPP_ */
