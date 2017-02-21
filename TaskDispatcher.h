#pragma once
#include "../base/baseinc.h"

struct Task
{
	virtual ~Task() {}
	virtual void Execute() = 0;
};


class WorkThread;
class TaskDispatcher
{
public:
	TaskDispatcher() : workThreadNum(7/* Cpu 核心数*/){};
	~TaskDispatcher() {};

	std::stack<Task*> taskStack;
	std::vector<WorkThread*> workThreadPool;
	int workThreadNum;

	void PushTask(Task* task);
	Task* RequestTask();
	void Flush();
	void Wait();


	void Init();
	void Free();
};

class WorkThread
{
public:
	WorkThread(TaskDispatcher* inDispatcher) : dispatcher(inDispatcher) {}
	~WorkThread() {}

	TaskDispatcher* dispatcher;
	std::thread* _thread;
	bool exitThread;

	void Stop()
	{
		exitThread = true;
	}

	void Start()
	{
		exitThread = false;
		_thread = new std::thread(&WorkThread::Working, this);
		_thread->detach();

	}

	std::mutex finish_mux;
	std::condition_variable finish_cv;

	std::mutex wait_mux;
	std::condition_variable wait_cv;

	//实际在工作线程中运行的函数
	// 当被标志开始工作之前都会一直等待，直到被标志开始工作，
	// 工作完成后，切换完成工作的状态
	bool doworking = false;
	void Working()
	{
		while (!exitThread)//线程循环
		{
			std::unique_lock <std::mutex> lck_w(wait_mux);
			wait_cv.wait(lck_w);

			while (true)//任务循环
			{

				Task* task = dispatcher->RequestTask();
				if (!task)
				{
					//跳出任务循环
					break;
				}

				task->Execute();
				delete task;
				task = nullptr;
			}

			doworking = false;
			std::unique_lock <std::mutex> lck_f(finish_mux);
			finish_cv.notify_all();
		}

	}
};


struct TestTask : public Task
{
	TestTask(double inI, double inJ, double inK) : i(inI), j(inJ), k(inK) {}
	~TestTask() {}
	virtual void Execute() override;

	double i;
	double j;
	double k;

};

