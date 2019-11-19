#include "pch.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5
#define LEFT (i-1)%N
#define RIGHT (i+1)%N 
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define TRUE 1
#define FALSE 0
HANDLE mutex, semaphilo[N];
int state[N];

/*-----------------------------------*/
void test(int i)
{
	if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
	{
		state[i] = EATING;
		ReleaseSemaphore(semaphilo[i], 1, NULL);
	}
}
void take_forks(int i)
{

	WaitForSingleObject(mutex, INFINITE);
	state[i] = HUNGRY;
	test(i);
	ReleaseSemaphore(mutex, 1, NULL);
	WaitForSingleObject(semaphilo[i], INFINITE);
	printf("\n Toma tenedores : %d", i);
}
void put_forks(int i)
{
	WaitForSingleObject(mutex, INFINITE);
	state[i] = THINKING;
	printf("\n Deja Tenedores : %d", i);
	test(LEFT);
	test(RIGHT);
	ReleaseSemaphore(mutex, 1, NULL);
}
void think(int i)
{
	int z = 0;
	printf("\n Pensando : %d", i);
	z = 2;
	Sleep(z);
}
void eat(int i)
{
	int z = 0;
	printf("\n Comiendo : %d", i);
	z = rand();
	Sleep(z);
}

DWORD WINAPI philo(int *i)
{
	while (TRUE)
	{
		think(*i);
		take_forks(*i);
		eat(*i);
		put_forks(*i);
	}
	return 0;
}

/*-----------------------------------*/
DWORD main(void)
{
	HANDLE Hilo[5];
	DWORD HiloID;
	int fil1 = 1;
	int fil2 = 2;
	int fil3 = 3;
	int fil4 = 4;
	int fil5 = 5;
	srand((unsigned)time(NULL));
	mutex = CreateSemaphore(NULL, 1, 10, (LPCWSTR)"Semaforo");
	semaphilo[1] = CreateSemaphore(NULL, 0, 1, (LPCWSTR)"Sema1");
	semaphilo[2] = CreateSemaphore(NULL, 0, 1, (LPCWSTR)"Sema2");
	semaphilo[3] = CreateSemaphore(NULL, 0, 1, (LPCWSTR)"Sema3");
	semaphilo[4] = CreateSemaphore(NULL, 0, 1, (LPCWSTR)"Sema4");
	semaphilo[5] = CreateSemaphore(NULL, 0, 1, (LPCWSTR)"Sema5");

	Hilo[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)philo, &fil1, 0, &HiloID);
	Hilo[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)philo, &fil2, 0, &HiloID);
	Hilo[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)philo, &fil3, 0, &HiloID);
	Hilo[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)philo, &fil4, 0, &HiloID);
	Hilo[4] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)philo, &fil5, 0, &HiloID);
	WaitForMultipleObjects(5, Hilo, 1, INFINITE);
	CloseHandle(Hilo[0]);
	CloseHandle(Hilo[1]);
	CloseHandle(Hilo[2]);
	CloseHandle(Hilo[3]);
	CloseHandle(Hilo[4]);
	CloseHandle(mutex);
	return 0;
}
/*mutex = CreateSemaphore(NULL, 1, 10, (LPCWSTR)"Semaforo");
	Hilo[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)philo1, &fil1, 0, &HiloID);
	Hilo[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)philo2, &fil2, 0, &HiloID);
	Hilo[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)philo3, &fil3, 0, &HiloID);
	Hilo[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)philo4, &fil4, 0, &HiloID);
	Hilo[4] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)philo5, &fil5, 0, &HiloID);*/