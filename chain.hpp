#ifndef NIKOLEX_CHAINHPP_
#define NIKOLEX_CHAINHPP_

#include "queue.hpp"
#include "allocator.hpp"

namespace nikolex {



template <typename C, uint8_t size>
class Chain {

public:

	struct Task {
		void * userData;
		void (* callback)(Chain*);
		void (* exec)(Chain*);
	};



private:

	void (*completed)(void*) = nullptr;
	void* completedCallbackData = nullptr;

	Task* activeTask;


public:
	Allocator<Task, 5> taskAllocator;
	queue::v1::Queue <Task*, 5> taskQueue;
	C ctx;
	bool blocked;
	void* userData;

	Chain():
		completed(nullptr),
		completedCallbackData(nullptr),
		activeTask(nullptr),
		blocked(false)
	{};


	Chain& then(void (* cb)(Chain*), void* userData = nullptr){

		Task* p_task = taskAllocator.alloc();

		Task& task = *taskQueue.pushNext(p_task);


		task.callback = cb;
		task.userData = userData;


		task.exec = [](Chain* chain){
			Task* task = chain->activeTask;
			chain->userData = task->userData;
			task->callback(chain);
			chain->taskAllocator.remove(task);
			chain->next();
		};

		return *this;
	}


	Chain& thenAsync(void (* cb)(Chain*), void* userData = nullptr){

		Task* p_task = taskAllocator.alloc();

		Task& task = *taskQueue.pushNext(p_task);

		task.callback = cb;
		task.userData = userData;

		task.exec = [](Chain* chain){
			Task* task = chain->activeTask;
			chain->blocked = true;
			chain->userData = task->userData;
			task->callback(chain);
		};

		return *this;
	}



	void setCompletedCallback(void (*cb)(void*), void* data = nullptr){
		completed = cb;
		completedCallbackData = data;
	}


	void unblock(){
		blocked = false;
	}


	void next(){
		blocked = false;
		if(!taskQueue.length()){
			if(completed) completed(completedCallbackData);
			return;
		}
		activeTask = taskQueue.pop();

		activeTask->exec(this);
		taskAllocator.remove(activeTask);

	}
};




};



#endif
