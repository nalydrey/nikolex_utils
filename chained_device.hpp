/*
 * chained_device.hpp
 *
 *  Created on: 6 мая 2026 г.
 *      Author: Oleksiy
 */

#ifndef CHAINED_DEVICE_HPP_
#define CHAINED_DEVICE_HPP_

#include "stdint.h"
#include "queue.hpp"
#include "allocator.hpp"
#include "chain.hpp"
//#include "device_chain.hpp"

namespace nikolex::ChainedDevice::v1 {


	template <typename Dev>
	struct CtxDevice{
		Dev* device;
	};


	template <typename D, typename C, uint8_t chain_size, uint8_t task_size>
	class Device {

	struct Ctx : public CtxDevice<D>, public C {
		using CtxDevice<D>::device;
	};

	public:


		using DeviceChain = Chain<Ctx, task_size>;
		using ChainTask = typename Chain<Ctx, task_size>::Task;

		struct ChainAndTask {
			ChainTask* p_task;
			DeviceChain* p_chain;
		};



		DeviceChain* currentChain;
		Allocator<DeviceChain, chain_size> chainAllocator;
		queue::v1::Queue<DeviceChain*, chain_size> queue;

		bool ready;

		Device():
			currentChain(nullptr),
			ready(true)
		{

		}

		virtual void init() = 0;

		ChainAndTask createChainAndTask(){


			ChainAndTask item;



			DeviceChain* p_chain = chainAllocator.alloc();


			currentChain ?
					*queue.pushFront(p_chain) :
					*queue.pushEnd(p_chain);

			if(currentChain) currentChain = nullptr;



			p_chain->ctx.device = (D*)this;



			ChainTask* p_task = p_chain->taskAllocator.alloc();

			p_chain->taskQueue.pushEnd(p_task);

			item.p_chain = p_chain;
			item.p_task = p_task;

			return item;
		}



		virtual void loop() final {
			if(queue.length() > 0 && currentChain == nullptr){

				currentChain = queue.getFirstItem();
				currentChain->setCompletedCallback([](void* ctx){
					Device* dev = (Device*)ctx;
					if(!dev->currentChain) return;
					dev->queue.pop();
					dev->chainAllocator.remove(dev->currentChain);
					dev->currentChain = nullptr;
				}, this);
			}
			if(!currentChain || !ready || currentChain->blocked) return;

			currentChain->next();
		}

		~Device(){};
	};
}


#endif /* CHAINED_DEVICE_HPP_ */
