#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "scheduler.h"
#include "ControlBlocks.h"
#include <iostream>

using namespace std;

const string INIT_PID = "init";

void initProcess();

void init();
void createProcess(const string&, int priority);
void destroyProcess(const string&);
void destroyProcessNoScheduler(const string&);
void timeOut();



#endif
