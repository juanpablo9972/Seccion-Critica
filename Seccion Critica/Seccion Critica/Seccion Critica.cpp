Main()
{

	// flags to indicate if each thread is in 
	// its critial section or not. 
	boolean thread1 = false;
	boolean thread2 = false;

	startThreads();
}

Thread1()
{

	do {

		// entry section 
		// wait until thread2 is in its critical section 
		while (thread2 == true)
			;

		// indicate thread1 entering its critical section 
		thread1 = true;

		// critical section 

		// exit section 
		// indicate thread1 exiting its critical section 
		thread1 = false;

		// remainder section 

	} while (completed == false)
}

Thread2()
{

	do {

		// entry section 
		// wait until thread1 is in its critical section 
		while (thread1 == true)
			;

		// indicate thread2 entering its critical section 
		thread2 = true;

		// critical section 

		// exit section 
		// indicate thread2 exiting its critical section 
		thread2 = false;

		// remainder section 

	} while (completed == false)
}