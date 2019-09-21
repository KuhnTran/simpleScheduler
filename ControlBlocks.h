#ifndef CONTROLBLOCKS_H
#define CONTROLBLOCKS_H

#include "List.h"
#include "scheduler.h"
#include <string>

using namespace std;

#define BLOCKED 0
#define READY 1
#define RUNNING 2

struct PCB;
struct RCB;

struct UsedResource;
struct RequestingProcess;

struct StatusFields
{
	int Type;
	List<PCB>* list;
};

struct CreationTreeFields
{
	PCB* parent;
	List<PCB> children;
};

struct PCB
{
	PCB();
	PCB(const string&, int);
	friend ostream& operator<<(ostream& o, const PCB& myPCB);

	PCB& operator=(const PCB&);
	bool operator==(const PCB &) const;
	bool operator==(const string&) const;

	string getPID() const;
	
	void setStatus(int newStatus, List<PCB>* newList);
	void addChildren(PCB *newPCB);

	string PID;
	List<UsedResource> otherResources;
	StatusFields status;
	CreationTreeFields creationTree;
	int priority;
};

struct ResourseStatus
{
	int capacity;
	int available;
};

struct RCB
{
	RCB();
	RCB(const string& newRID, int newCapacity);

	bool operator==(const RCB& newRCB) const;
	bool operator==(const string& target) const;
	RCB & operator=(const RCB& newRCB);

	string RID;
	ResourseStatus status;
	List<RequestingProcess> waitingList;
};

struct UsedResource
{
	UsedResource(RCB* newRCB, int newUnits)
	{
		resourceBeingUsed = newRCB;
		units = newUnits;
	}
	
	bool operator==(const string& target) const
	{
		return resourceBeingUsed->RID == target;
	}

	RCB* resourceBeingUsed;
	int units;
};

struct RequestingProcess
{
	bool operator==(const string &targetPID)
	{
		return targetPID == process->PID;
	}

	RequestingProcess(PCB* newProcess, int newUnits)
	{
		process = newProcess;
		units = newUnits;
	}

	PCB* process;
	int units;
};
#endif
