#include "ResourceManager.h"
#include "scheduler.h"
#include "ControlBlocks.h"

void initResource()
{
	int n;
	char RIDbuffer[3];
	for (int i = 0; i < NUM_OF_RESOURCE; ++i)
	{
		n = sprintf(RIDbuffer, "%c%d", RESOURCE_LABEL, i + 1);
		RCB* newRCB = new RCB(RIDbuffer, i+1);
		resources.insertBack(newRCB);
	}
}

void block_WaitlistProcess(RCB* RCBRequested, int unit, PCB* process)
{
	int currentPriority = process->priority;
	
	process->setStatus(BLOCKED,&blockedList);
	readyList[currentPriority].remove(process);
	blockedList.insertFront(process);
	RequestingProcess* newHolder = 
		new RequestingProcess(process, unit);
	
	RCBRequested->waitingList.insertBack(newHolder);
	allRequests.insertFront(newHolder);
}

bool noError = true;
void handleRequest(RCB* RCBRequested, int units, PCB* process, bool isReleasing)
{
	if (RCBRequested->status.capacity < units || units <= 0)
	{
		cout << "error ";
		noError = false;
	}
	else
	{
		if (RCBRequested->status.available >= units && (RCBRequested->waitingList.getNumOfElem() == 0 || isReleasing))
		{
			UsedResource* newUsedResource = 
				new UsedResource(RCBRequested, units);
			RCBRequested->status.available -= units;
			process->otherResources
				.insertBack(newUsedResource);
		
			allUsedResourceStructs.insertFront(newUsedResource);
		}
		else block_WaitlistProcess(RCBRequested, units, process);
	}
}

void handleProcessAlreadyHoldsRes(RCB* RCBRequested, int units, PCB* process, bool isReleasing)
{
	UsedResource* resultHolder;
	
	if (process->otherResources
			.search(RCBRequested->RID, resultHolder))
	{
		if (resultHolder->units + units > RCBRequested->status.capacity || units <= 0)
		{
			cout << "error ";
			noError = false;
		}
		else
		{
			if (RCBRequested->status.available >= units && (RCBRequested->waitingList.getNumOfElem() == 0 ||isReleasing))
			{
				resultHolder->units += units;
				RCBRequested->status.available -= units;
			}
			else block_WaitlistProcess(RCBRequested, units, process);
		}
	}
}

bool processIsHoldingTheResource(const string &requestRID, PCB* process)
{
	return process->otherResources.search(requestRID);
}

void handleRequestCases(const string &requestRID, PCB* process, RCB* resource, int requestUnits, bool isReleasing)
{
	if (processIsHoldingTheResource(requestRID, process))
		handleProcessAlreadyHoldsRes(resource, requestUnits, process, isReleasing);
	else handleRequest(resource, requestUnits, process, isReleasing);
}

void request(const string& requestRID, int requestUnits)
{
	RCB* resultRCB;
	bool existRCB = resources.search(requestRID, resultRCB);
	if (existRCB)
	{
		handleRequestCases(requestRID,currentProcess, resultRCB, requestUnits, false);
		if (noError) 
			scheduler();
		noError = true;
	}
	else cout << "error ";
}

void releaseTheUnits(UsedResource* resHolder, int resUnits)
{
	resHolder->resourceBeingUsed->status.available += resUnits;
	resHolder->units -= resUnits;
}

void releaseRCBCompletely(PCB* process, UsedResource* resHolder, int resUnits)
{
	resHolder->resourceBeingUsed->status.available += resUnits;
	process->otherResources.remove(resHolder);
}

void updateWaitlist(RCB* freeRCB)
{
	while(freeRCB->waitingList.getNumOfElem() != 0 
			&& freeRCB->waitingList.getFirst()->getContent()
				->units <= freeRCB->status.available)
	{
		PCB* freeProcess = freeRCB->waitingList.getFirst()
			->getContent()->process;
		int requestingUnits = freeRCB->waitingList.getFirst()
			->getContent()->units;
		int freeProcessPriority = freeProcess->priority;
		//Remove PCB from RCB's waitlist & reset status:
		freeRCB->waitingList.remove(freeRCB->waitingList.getFirst()
			->getContent());
		freeProcess->setStatus(READY,readyList);

		//Give the resource to the process:	
		handleRequestCases(freeRCB->RID, freeProcess, 
			freeRCB, requestingUnits, true);
		
		//InsertPCB into readyList, remove from blockList:
		readyList[freeProcessPriority].insertBack(freeProcess);
		blockedList.remove(freeProcess);
	}

}

void release(const string &releaseRID, int releaseUnits)
{
	UsedResource* resultHolder;
	if (processIsHoldingTheResource(releaseRID, currentProcess))
	{
		currentProcess->otherResources.search(releaseRID, resultHolder);
		if (resultHolder->units < releaseUnits)
			cout << "error ";
		else
		{
			RCB* RCBBeingProcessed = resultHolder->resourceBeingUsed;
			
			if (resultHolder->units == releaseUnits)
				releaseRCBCompletely(currentProcess, resultHolder,releaseUnits);
			else releaseTheUnits(resultHolder,releaseUnits);
			
			updateWaitlist(RCBBeingProcessed);
			scheduler();
		}
	}
	else cout << "error ";
}

RCB* hasInWaitlist(PCB* target, RequestingProcess* &resultHolder)
{
	bool found = false;
	Node<RCB>* temp = resources.getFirst();
	RCB* resultRCB;
	
	while (!found && temp != NULL)
	{
		found = temp->getContent()->waitingList.search(target->PID, resultHolder);
		if (found) resultRCB = temp->getContent();
		else temp = temp->getNext();
	}
	if (!found) return (RCB*)-1;
	else return resultRCB;
}

void removeProcessFromWaitingLists(PCB* targetPCB)
{
	RequestingProcess* resultHolder;
	RCB* RCBContainingPCB = hasInWaitlist(targetPCB, resultHolder);
	RCBContainingPCB->waitingList.remove(resultHolder);
}
