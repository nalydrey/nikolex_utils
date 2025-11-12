/*
 * queue.h
 *
 *  Created on: Nov 11, 2025
 *      Author: Oleksiy
 */

#pragma once

#include "cstdint"


namespace nikolex {

template<typename T, uint8_t size>
class Queue {

	T itemList[size];
	int8_t pointer;
	uint8_t qty;

public:

	Queue() : pointer(-1), qty(0){

	}

	bool isEmpty(){ return qty == 0;}
	bool isFull(){return qty == size;}


	void push(T* item){
		if(isFull()) return;
		pointer++;
		qty++;
		itemList[pointer] = *item;
	}

	T* getNext(){
		if((pointer + 1) < size){
			return &itemList[pointer + 1];
		}
		return nullptr;
	}

	T* getFirst(){
		if(isEmpty()) return nullptr;
		return &itemList[0];
	}

	T* createNext(){
		if((pointer + 1) < size){
			pointer++;
			qty++;
			return &itemList[pointer];
		}
		return nullptr;
	}

	void deleteFirst(){
		if(isEmpty()) return;

		for(uint8_t i = 1; i <= qty; i++){
			itemList[i-1] = itemList[i];
		}

		qty--;
		pointer--;
	}

};

}  // namespace nikolex
