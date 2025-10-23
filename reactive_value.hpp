/*
 * reactive_value.hpp
 *
 *  Created on: Oct 23, 2025
 *      Author: Oleksiy
 */

#ifndef REACTIVE_VALUE_HPP_
#define REACTIVE_VALUE_HPP_



#include <cstdint>



namespace nikolex {

class ReactiveValue{

private:
	uint32_t value;
	uint32_t prevValue;

	void(* onChangeCallback)(uint32_t, void*) = nullptr;
	void(* onReadCallback)(uint32_t, void*) = nullptr;

	void* onChangeCtx = nullptr;
	void* onReadCtx = nullptr;

public:

	void setValue(uint32_t val){
		value = val;
		if(onReadCallback) onReadCallback(value, onReadCtx);
		if(prevValue != value){
			prevValue = value;
			if(onChangeCallback) onChangeCallback(value, onChangeCtx);
		}
	}

	void onChange(void(* callback)(uint32_t val, void*), void* ctx = nullptr){
		onChangeCallback = callback;
		onChangeCtx = ctx;
	}

	void onRead(void(* callback)(uint32_t val, void*), void* ctx = nullptr){
		onReadCallback = callback;
		onReadCtx = ctx;
	}

	uint32_t getValue(){
		return value;
	}

	 ~ReactiveValue(){}
};

}


#endif /* REACTIVE_VALUE_HPP_ */
