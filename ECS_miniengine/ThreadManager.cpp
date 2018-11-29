#include "ThreadManager.h"

ThreadManager * ThreadManager::instance = 0;

ThreadManager::ThreadManager()
{
	thPool = new ThreadPool(THREADSNUMBERS);
	
}


ThreadManager::~ThreadManager()
{
	delete instance;
}

ThreadManager * ThreadManager::getInstance()
{
	if (instance == 0)
	{
		instance = new ThreadManager();
	}
	return instance;
}


ThreadPool * ThreadManager::getThreadPool()
{
	return thPool;
}
