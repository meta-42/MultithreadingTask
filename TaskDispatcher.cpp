#include "TaskDispatcher.h"


void TaskDispatcher::PushTask(Task* task)
{
	taskStack.push(task);
}

std::mutex glock_RequestTask;
Task* TaskDispatcher::RequestTask()
{
	Task* task = nullptr;

	glock_RequestTask.lock();
	if (!taskStack.empty())
	{
		task = taskStack.top();
		taskStack.pop();
	}
	glock_RequestTask.unlock();

	return task;
}

//主线程通知所有工作线程，开始Flush任务
void TaskDispatcher::Flush()
{
	std::vector<WorkThread*>::iterator it = workThreadPool.begin();
	for (; it != workThreadPool.end(); ++it)
	{
		std::unique_lock <std::mutex> lck((*it)->wait_mux);
		(*it)->wait_cv.notify_all();
		(*it)->doworking = true;
	}

}

//主线程等待所有工作线程Flush所有任务
void TaskDispatcher::Wait()
{
	std::vector<WorkThread*>::iterator it = workThreadPool.begin();
	for (; it != workThreadPool.end(); ++it)
	{
		std::unique_lock <std::mutex> lck((*it)->finish_mux);
		if ((*it)->doworking == true)
		{
			(*it)->finish_cv.wait(lck);

		}
	}
	//std::cout << "所有任务执行完毕" << std::endl;
}

void TaskDispatcher::Init()
{
	//将所有工作线程启动起来
	for (int i = 0; i < workThreadNum; ++i)
	{
		workThreadPool.push_back(new WorkThread(this));
	}

	std::vector<WorkThread*>::iterator it = workThreadPool.begin();
	for (; it != workThreadPool.end(); ++it)
	{
		(*it)->Start();
	}
}

void TaskDispatcher::Free()
{
	std::vector<WorkThread*>::iterator it = workThreadPool.begin();
	for (; it != workThreadPool.end(); ++it)
	{
		(*it)->Stop();
		delete (*it);
	}
}


void TestTask::Execute()
{

	int count = 0;
	while (count < 1000)
	{
		i = i + j + k;

		count++;
	}

	double num = i;

	printf("[thread:%d] > num: %f\n", std::this_thread::get_id(), num);

}
