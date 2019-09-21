#include "scheduler.h"
#include "scheduler.cpp"
#include "ResourceManager.h"
#include "ResourceManager.cpp"
#include "List.h"
#include "List.cpp"
#include "ProcessManager.h"
#include "ProcessManager.cpp"
#include "ControlBlocks.h"
#include "ControlBlocks.cpp"
#include <iostream>
using namespace std;


void processCommand(char* command)
{
	
	if (command[0] == 't' && command[1] == 'o') timeOut();
	else 
	{
		if (command[0] == 'd' && command[1] == 'e')
		{
			string targetPID = "";
			targetPID += command[3];
			destroyProcess(targetPID);
		}
		if (command[0] == 'c' && command[1] == 'r')
		{
			string newPID = "";
			newPID += command[3];
			int priority = command[5] - 48;
			createProcess(newPID, priority);
		}
		if (command[0] == 'r' && command[1] == 'e' && command[2] == 'q')
		{
			string newRID = "";
			newRID += command[4];
			newRID += command[5];
			int units = command[7] - 48;
			request(newRID, units);
		}
		if (command[0] == 'r' && command[1] == 'e' && command[2] == 'l')
		{
			string newRID = "";
			newRID += command[4];
			newRID += command[5];
			int units = command[7] - 48;
			release(newRID, units);
		}

		if (command[0] == 'i' && command[1] == 'n' && command[2] == 'i' && command[3] == 't')
			init();
		if (command == "wait")
			cout <<" here\n";	
	}
	//cout << endl << blockedList << endl;
}

void cleanUp()
{
	for (int i = 0; i < 3; i++)
		readyList[i].destroyPointerInsideNode();
	blockedList.destroyPointerInsideNode();
	destroyedList.destroyPointerInsideNode();
	allRequests.destroyPointerInsideNode();
	allUsedResourceStructs.destroyPointerInsideNode();
	resources.destroyPointerInsideNode();
}
int main()
{
	char myString[1024];
	initResource();
	initProcess();
//	while (1)
//	{
		while(cin.getline(myString, 1024))	
//		if (myString == "EOF") break;
		processCommand(myString);

	cleanUp();
	cout << endl;
//	}
	return 0;
}
