#include"scheduler.h"


PCB* findNextProcess()
{
	PCB* nextProcess;
	if (readyList[PRIORITY_SYSTEM].getNumOfElem() > 0)
		nextProcess = readyList[PRIORITY_SYSTEM].getFirst()->getContent();
	else if (readyList[PRIORITY_USER].getNumOfElem() > 0)
		nextProcess = readyList[PRIORITY_USER].getFirst()->getContent();
	else nextProcess = readyList[PRIORITY_INIT].getFirst()->getContent();
	return nextProcess;
}

void preempt(PCB* &currentProcess, PCB* &newProcess)
{
	currentProcess = newProcess;
	cout << currentProcess->PID << " ";
}

void scheduler()
{
	PCB* nextProcess = findNextProcess();
	if (currentProcess->priority < nextProcess->priority
		|| currentProcess->status.Type != RUNNING
		|| currentProcess == NULL)
		preempt(currentProcess, nextProcess);
}
