#include "scheduler.h"
#include "ResourceManager.h"
#include "ControlBlocks.h"
#include "ProcessManager.h"
#include<string>
#include<iostream>
using namespace std;

void initProcess()
{
	PCB* initPCB = new PCB(INIT_PID,PRIORITY_INIT);
	
	readyList[PRIORITY_INIT].insertFront(initPCB);
	currentProcess = initPCB;
	
	scheduler();
}

void init()
{
	currentProcess = readyList[PRIORITY_INIT].getFirst()->getContent();
	destroyProcessNoScheduler(INIT_PID);
	cout << endl;
	initProcess();
}

bool checkForExistence(const string& newPID)
{
	int i =0;
	bool duplicate = blockedList.search(newPID);
	
	if (!duplicate)
		while (i < PRIORITY_LEVELS && !duplicate)
		{
			duplicate = readyList[i].search(newPID);
			++i;
		}
	return duplicate;
}

void createProcess(const string& newPID, int newPriority)
{
	bool duplicate = checkForExistence(newPID);
	if(duplicate || newPriority >= PRIORITY_LEVELS)
	{
		cout << "error ";
	}
	else
	{
		PCB* newProcess = new PCB(newPID,newPriority);
		readyList[newPriority].insertBack(newProcess);
	
		currentProcess->addChildren(newProcess);
		currentProcess->setStatus(READY, readyList);
	}
	scheduler();
}

bool rSearch(PCB* process, const string &targetPID, PCB* &targetPCB)
{
	bool valid = false;
	if (process->creationTree.children.getNumOfElem() != 0)
	{
		valid = process->creationTree.children.search(targetPID, targetPCB);
		Node<PCB>* temp = process->creationTree.children.getFirst();
		while (!valid && temp != NULL)
		{
			valid = rSearch(process->creationTree.children
				.getFirst()->getContent(), targetPID, targetPCB);
			temp = temp->getNext();
		}
	}
	return valid;
}

bool validateDestroyRequest(const string& targetPID, PCB* &targetPCB)
{
	bool valid = false;	
	if (currentProcess->PID == targetPID)
	{
		valid = true;
		targetPCB = currentProcess;
	}
	else
	{	
		if (currentProcess->creationTree.children.getNumOfElem() != 0)
		{
			valid = currentProcess->creationTree.children.search(targetPID, targetPCB);	
			Node<PCB>* temp = currentProcess->creationTree.children.getFirst();
			while (!valid && temp != NULL)
			{
				valid = rSearch(currentProcess->creationTree.children
					.getFirst()->getContent(), targetPID, targetPCB);
				temp = temp->getNext();
			}
		}
	}
	return valid;
}

void destroyChildren(PCB* targetPCB)
{
	Node<PCB>* temp= targetPCB->creationTree.children.getFirst();
	while (temp != NULL)
	{
		destroyProcessNoScheduler(temp->getContent()->PID);
		temp = targetPCB->creationTree.children.getFirst();
	}	
}



void releaseResources(PCB* targetPCB)
{
	Node<UsedResource>* temp = targetPCB->otherResources.getFirst();
	while (temp != NULL)
	{
		temp->getContent()->resourceBeingUsed->status.available += temp->getContent()->units;
		updateWaitlist(temp->getContent()->resourceBeingUsed);
		temp = temp->getNext();
	}	
}



void initiateDestroy(PCB* targetPCB)
{
	if (blockedList.search(targetPCB))
	{
		removeProcessFromWaitingLists(targetPCB);
		blockedList.remove(targetPCB);
	}
	else readyList[targetPCB->priority].remove(targetPCB);
	releaseResources(targetPCB);
	if (targetPCB->creationTree.parent != NULL)
		targetPCB->creationTree.parent->creationTree.children.remove(targetPCB);
	
	destroyedList.insertFront(targetPCB);
}

void destroyProcessNoScheduler(const string& targetPID)
{
	PCB* targetPCB;
	bool valid = validateDestroyRequest(targetPID, targetPCB);
	
	if (!valid) cout << "error ";
	else
	{
		if(targetPCB->creationTree.children.getNumOfElem() != 0)
			destroyChildren(targetPCB);
		initiateDestroy(targetPCB);
	}
}

void destroyProcess(const string& targetPID)
{
	PCB* targetPCB;
	bool valid = validateDestroyRequest(targetPID, targetPCB);
	
	if (!valid) cout << "error ";
	else
	{
		if(targetPCB->creationTree.children.getNumOfElem() != 0)
			destroyChildren(targetPCB);
		initiateDestroy(targetPCB);
		scheduler();
	}
}


void timeOut()
{
	int currentPriority = currentProcess->priority;
	readyList[currentPriority].pushFirstToEnd();
	currentProcess->setStatus(READY, readyList);
	scheduler();
}
