#include "scheduler.h"
#include "ControlBlocks.h"

PCB::PCB()
{
	PID = "N/A";
	status.Type = -1;
	creationTree.parent = NULL;
	priority = -1;
}

PCB::PCB(const string& newPID, int newPriority)
{
    PID = newPID;
    status.Type = READY;
    creationTree.parent = currentProcess;
    priority = newPriority;
}

ostream& operator<<(ostream& o, const PCB& myPCB)
{
	o << myPCB.PID << " " << myPCB.priority;
	return o;	
}	

PCB& PCB::operator=(const PCB& newPCB) 
{
	if (&newPCB != this)
	{	
		PID = newPCB.PID;
		otherResources = newPCB.otherResources;
		status.Type = newPCB.status.Type;
		status.list = newPCB.status.list;
		creationTree.parent = newPCB.creationTree.parent;
		creationTree.children = newPCB.creationTree.children;
		priority = newPCB.priority;
	}
	else cout << "Trying to assing to self PCB" << endl;
	return *this;
}

bool PCB::operator==(const PCB &newPCB) const
{
	return (PID == newPCB.PID);
}

bool PCB::operator==(const string &target) const
{
	return PID == target;
}

void PCB::setStatus(int newStatus, List<PCB>* newList)
{
	status.Type = newStatus;
	status.list = newList;
}

void PCB::addChildren(PCB *newPCB)
{
	creationTree.children.insertBack(newPCB);
}

RCB::RCB()
{
	RID = "N/A";
	status.capacity = 0;
	status.available = 0;
}

RCB::RCB(const string &newRID, int newCapacity)
{
	RID = newRID;
	status.capacity = newCapacity;
	status.available = newCapacity;
}

bool RCB::operator==(const RCB& newRCB) const
{
	return RID == newRCB.RID;
}
	
bool RCB::operator==(const string &target) const
{
	return RID == target;
}

RCB & RCB::operator=(const RCB& newRCB)
{
	if (&newRCB != this)
	{
		RID = newRCB.RID;
		status.capacity = newRCB.status.capacity;
		status.available = newRCB.status.available;
		waitingList = newRCB.waitingList;
	}
	else cout << "Trying to self assignment RCB";
	return *this;
}
