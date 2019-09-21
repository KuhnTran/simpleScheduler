#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "scheduler.h"
#include "ControlBlocks.h"
#include <stdio.h>

const char RESOURCE_LABEL = 'R';

#define NUM_OF_RESOURCE 4
#define RID_LENGTH 2

List<RCB> resources;
List<RequestingProcess> allRequests;
List<UsedResource> allUsedResourceStructs;

void initResource();

void request(const string&, int);

void release(const string&, int);

void updateWaitlist(RCB*);

void removeProcessFromWaitingLists(PCB*);

#endif
