#pragma once
#include <string>

using namespace std;

class Train
{
  public :
    int TrainID;
	string TrainType;
	int FirstWorkerNumber;
	int WorkersQuantity;
};

class TrainWorker
{
   public :
	   int WorkerID;
	   string Name;
	   string Surname;
	   int TrainID;
};

