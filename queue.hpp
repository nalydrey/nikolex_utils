#ifndef NIKOLEX_QUEUEHPP_
#define NIKOLEX_QUEUEHPP_

#include <stdint.h>

namespace nikolex::queue::v1 {

	template<typename T, uint8_t size>
	class Queue {

		T list[size];

		uint8_t qty;

		int8_t pointer;

	public:
		Queue(): pointer(-1), qty(0){
			for(uint8_t i = 0; i < size; i++){
				list[i] = {};
			}
		}



		T pushEnd(T item) {
			qty++;
			pointer = qty - 1;
			list[pointer] = item;
			return list[pointer];
		}

		T pushNext(T item){
			qty++;
			pointer++;

			for(uint8_t i = qty - 1; i > pointer; i--){
				list[i+1] = list[i];
			}
			list[pointer] = item;
			return list[pointer];
		}


		T pushFront(T item){
			qty++;
			pointer = 0;
			for(uint8_t i = qty - 1; i > 0; i--){
				list[i] = list[i - 1];
			}
			list[pointer] = item;
			return list[0];
		}


		T pop(){
			qty--;
			pointer = -1;
			T firstItem = list[0];
			for(uint8_t i = 0; i < qty; i++){
				list[i] = list[i+1];
			}

			return firstItem;
		}

		T getFirstItem(){
			pointer = 0;
			return list[0];
		}

		uint8_t length(){return qty;}
	};
}
#endif
