# MultithreadingTask
Multithreading task controller



	auto dis = GContext->taskDispatcher;

	for (int i = 0; i < 1000; i++)
	{
		dis->PushTask(new TestTask(1.f, 0.f, 2.f));
	}



	double dur;
	clock_t start, end;
	start = clock();

	dis->Flush();
	dis->Wait();

	end = clock();
	dur = (double)(end - start);
	printf("Use Time:%f\n", (dur / CLOCKS_PER_SEC));

	Sleep(2000);
	dis->PushTask(new TestTask(1.f, 0.f, 2.f));
	dis->PushTask(new TestTask(1.f, 0.f, 2.f));
	dis->PushTask(new TestTask(1.f, 0.f, 2.f));
	dis->PushTask(new TestTask(1.f, 0.f, 2.f));
	dis->PushTask(new TestTask(1.f, 0.f, 2.f));
	dis->Flush();
	dis->Wait();
