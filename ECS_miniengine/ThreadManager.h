#pragma once
#include "ThreadPool.h"
#include "ManagerConstants.h"
class ThreadManager
{
private:
	static ThreadManager * instance;
	ThreadPool * thPool;
	ThreadManager();
	~ThreadManager();
public:
	static ThreadManager* getInstance();
	ThreadPool * getThreadPool();
};

