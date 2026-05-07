#ifndef NIKOLEX_ALLOCATORHPP_
#define NIKOLEX_ALLOCATORHPP_

#include <stdint.h>

namespace nikolex {

template <typename T, uint8_t size>
class Allocator {

	T container[size];
	bool ReadyToAllocateList[size];

public:
	Allocator(){
		for (uint8_t i = 0; i < size; i++) {
			ReadyToAllocateList[i] = true;
		}
		for (uint8_t i = 0; i < size; i++) {
			container[i] = {};
		}
	};


	T* alloc(){
		for(uint8_t i=0; i < size; i++){
			if(ReadyToAllocateList[i]){
				ReadyToAllocateList[i] = false;
				return &container[i];
			}
		}
		return nullptr;
	}


	bool remove(T* pointer){
		for (uint8_t i = 0; i < size; i++) {
			if(&container[i] == pointer){
				container[i] = {};
				ReadyToAllocateList[i] = true;
				return true;
			}
		}
		return false;
	}

};



}




#endif
