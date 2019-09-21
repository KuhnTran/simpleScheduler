#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "ControlBlocks.h"
#include "List.h"
#include<string>

//Define the priority levels
#define PRIORITY_SYSTEM 2
#define PRIORITY_USER 1
#define PRIORITY_INIT 0

#define PRIORITY_LEVELS 3

List<PCB> readyList[PRIORITY_LEVELS];
List<PCB> blockedList;
List<PCB> destroyedList;

PCB* currentProcess;

void initProcessLists();

PCB* findNextProcess();
void preempt(Node<PCB>* &, Node<PCB>* &);
void scheduler();

#endif
