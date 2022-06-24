#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include "Train.h"

using namespace std;

vector<Train> Trains;
map<int, int> TrainIDmap;
int TrainQuantity = 0;

vector<TrainWorker> TrainWorkers;
map<int, int> WorkerIDmap;
int WorkersQuantity = 0;

bool FuncForWorkersSortion(TrainWorker w1, TrainWorker w2)
{
	return w1.TrainID < w2.TrainID;
}

bool FuncForTrainIDmapSortion(pair<int, int> p1, pair<int, int> p2)
{
	return p1.second < p2.second;
}

void TrainFileOutput()
{
	ofstream out;
	out.open("D:\\BD\\Lab1BD\\T.txt");
	out << "TrainID  TrainType  Available  FirstWorkerNumber  WorkersQuantity" << endl;
	for (int i = 0; i < TrainQuantity; i++)
	{
		Train tr = Trains[i];
		out << tr.TrainID << "         " << tr.TrainType << "           1" << "          " << tr.FirstWorkerNumber << "           " << tr.WorkersQuantity << endl;
	}
	out.close();
} 


void WorkersFileOutput()
{
	ofstream out;
	out.open("D:\\BD\\Lab1BD\\W.txt");
	out << "WorkerID  Name  Surname TrainID" << endl;
	for (int i = 0; i < WorkersQuantity; i++)
	{
		TrainWorker w = TrainWorkers[i];
		out << w.WorkerID << "         " << w.Name << "           " << w.Surname << "           " << w.TrainID << endl;
	}
	out.close();
}


void TrainIndexFileOutput()
{
	ofstream out;
	out.open("D:\\BD\\Lab1BD\\T_ind.txt");
	out << "TrainID   Number" << endl;

	vector<pair<int, int>> v;
	for (auto x : TrainIDmap)
	{
		v.push_back(make_pair(x.first, x.second));
	}

	sort(v.begin(), v.end(), FuncForTrainIDmapSortion);

	for (int i = 0; i < v.size(); i++)
		out << v[i].first << "        " << v[i].second << endl;

	out.close();
}

void InsertMaster(int TrainID, string TrainType)
{
	if (!TrainIDmap.count(TrainID))
	{
		Trains.push_back({ TrainID, TrainType, -1, 0 });
		TrainQuantity++;
		TrainIDmap[TrainID] = TrainQuantity - 1;

		ofstream out;
		out.open("D:\\BD\\Lab1BD\\T.txt", std::ios::app);
		out << TrainID << "         " << TrainType << "           1" << "         -1         0" << endl;
		out.close();

		out.open("D:\\BD\\Lab1BD\\T_ind.txt", std::ios::app);
		out << TrainID << "          " << TrainQuantity - 1 << endl;
		out.close();
	}
	else
		cout << "Train is available in database \n";
}


void GetMaster(int TrainID)
{
	auto copyTrainIDmap = TrainIDmap;
	if (copyTrainIDmap.count(TrainID))
	{
		Train tr = Trains[TrainIDmap[TrainID]];
		cout << "TrainID : " << tr.TrainID << " TrainType : " << tr.TrainType << " WorkersQuantity : " << tr.WorkersQuantity << endl;
	}
	else
		cout << "No train \n";
}


void GetSlave(int WorkerID)
{
	auto copyWorkersIDmap = WorkerIDmap;
	if (copyWorkersIDmap.count(WorkerID))
	{
		TrainWorker w = TrainWorkers[WorkerIDmap[WorkerID]];
		cout << "WorkerID : " << w.WorkerID << " Name : " << w.Name << " Surname : " << w.Surname << " TrainID : " << w.TrainID << endl;
	}
	else
		cout << "No worker \n";
}


void InsertSlave(int TrainID, int WorkerID, string Name, string Surname)
{
	auto copyTrainIDmap = TrainIDmap;
	if (copyTrainIDmap.count(TrainID))
	{
		if (!WorkerIDmap.count(WorkerID))
		{
			TrainWorkers.push_back({ WorkerID, Name, Surname, TrainID });
			WorkersQuantity++;
			Trains[TrainIDmap[TrainID]].WorkersQuantity ++;
			sort(TrainWorkers.begin(), TrainWorkers.end(), FuncForWorkersSortion);

			int CurrentTrainID = TrainWorkers[0].TrainID;
			Trains[TrainIDmap[CurrentTrainID]].FirstWorkerNumber = 0;
			for (int i = 0; i < WorkersQuantity; i++)
			{
				WorkerIDmap[TrainWorkers[i].WorkerID] = i;
				if (TrainWorkers[i].TrainID != CurrentTrainID)
				{
					CurrentTrainID = TrainWorkers[i].TrainID;
					Trains[TrainIDmap[CurrentTrainID]].FirstWorkerNumber = i;
				}
			}

			TrainFileOutput();
			WorkersFileOutput();
		}
		else
			cout << "WorkerID is available in database \n";
	}
	else
		cout << "No train \n";
}


void DeleteSlave(int WorkerID)
{
	auto copyWorkerIDmap = WorkerIDmap;
	if (copyWorkerIDmap.count(WorkerID))
	{
		int DeleteNumber = WorkerIDmap[WorkerID];
		Trains[TrainIDmap[TrainWorkers[DeleteNumber].TrainID]].WorkersQuantity -= 1;
		Trains[TrainIDmap[TrainWorkers[DeleteNumber].TrainID]].FirstWorkerNumber = -1;

		TrainWorkers[DeleteNumber] = TrainWorkers[WorkersQuantity - 1];
		TrainWorkers.erase(TrainWorkers.begin() + WorkersQuantity - 1);
		WorkersQuantity--;
		WorkerIDmap.erase(WorkerID);

		sort(TrainWorkers.begin(), TrainWorkers.end(), FuncForWorkersSortion);

		if (WorkersQuantity > 0)
		{
			int CurrentTrainID = TrainWorkers[0].TrainID;
			Trains[TrainIDmap[CurrentTrainID]].FirstWorkerNumber = 0;
			for (int i = 0; i < WorkersQuantity; i++)
			{
				WorkerIDmap[TrainWorkers[i].WorkerID] = i;
				if (TrainWorkers[i].TrainID != CurrentTrainID)
				{
					CurrentTrainID = TrainWorkers[i].TrainID;
					Trains[TrainIDmap[CurrentTrainID]].FirstWorkerNumber = i;
				}
			}
		}
	}

	else
		cout << "No worker" << endl;
}


void DeleteMaster(int TrainID)
{
	auto copyTrainIDmap = TrainIDmap;
	if (copyTrainIDmap.count(TrainID))
	{
		int DeleteNumber = TrainIDmap[TrainID];

		int FirstWorkerNumber = Trains[DeleteNumber].FirstWorkerNumber;
		int ThisWorkersQuantity = Trains[DeleteNumber].WorkersQuantity;
		int LastWorkerNumber = FirstWorkerNumber + ThisWorkersQuantity - 1;
		if (FirstWorkerNumber != -1)
		{
			set<int> IDOfWorkersForDelete;
			for (int i = FirstWorkerNumber; i <= LastWorkerNumber; i++)
				IDOfWorkersForDelete.insert(TrainWorkers[i].WorkerID);

			for (auto workerID : IDOfWorkersForDelete)
				DeleteSlave(workerID);
		}

		Trains[DeleteNumber] = Trains[TrainQuantity - 1];
		TrainIDmap[Trains[DeleteNumber].TrainID] = DeleteNumber;
		Trains.erase(Trains.begin() + TrainQuantity - 1);
		TrainQuantity--;
		TrainIDmap.erase(TrainID);

		TrainFileOutput();
		WorkersFileOutput();
		TrainIndexFileOutput();
	}
	else
		cout << "No train" << endl;
}


void UpdateMaster(int TrainID, string TrainType)
{
	auto copyTrainIDmap = TrainIDmap;
	if (copyTrainIDmap.count(TrainID))
	{
		Trains[TrainIDmap[TrainID]].TrainType = TrainType;
		TrainFileOutput();
	}
	else
		cout << "No train" << endl;
}

void UpdateSlave(int WorkerID, string Name, string SurName, int TrainID)
{
	auto copyWorkersIDmap = WorkerIDmap;
	auto copyTrainsIDmap = TrainIDmap;
	if (copyWorkersIDmap.count(WorkerID) && copyTrainsIDmap.count(TrainID))
	{
		TrainWorkers[WorkerIDmap[WorkerID]].Name = Name;
		TrainWorkers[WorkerIDmap[WorkerID]].Surname = SurName;

		if (TrainID != TrainWorkers[WorkerIDmap[WorkerID]].TrainID)
		{
			Trains[TrainIDmap[TrainID]].WorkersQuantity++;
			Trains[TrainIDmap[TrainWorkers[WorkerIDmap[WorkerID]].TrainID]].WorkersQuantity--;
			Trains[TrainIDmap[TrainWorkers[WorkerIDmap[WorkerID]].TrainID]].FirstWorkerNumber = -1;
			TrainWorkers[WorkerIDmap[WorkerID]].TrainID = TrainID;

			sort(TrainWorkers.begin(), TrainWorkers.end(), FuncForWorkersSortion);

			int CurrentTrainID = TrainWorkers[0].TrainID;
			Trains[TrainIDmap[CurrentTrainID]].FirstWorkerNumber = 0;
			for (int i = 0; i < WorkersQuantity; i++)
			{
				WorkerIDmap[TrainWorkers[i].WorkerID] = i;
				if (TrainWorkers[i].TrainID != CurrentTrainID)
				{
					CurrentTrainID = TrainWorkers[i].TrainID;
					Trains[TrainIDmap[CurrentTrainID]].FirstWorkerNumber = i;
				}
			}
		}

		TrainFileOutput();
		WorkersFileOutput();
	}
	else
		cout << "TrainID or WorkerID is not correct" << endl;
}

void MasterUtilite()
{
	cout << "TrainID  TrainType  Available  FirstWorkerNumber  WorkersQuantity" << endl;
	for (int i = 0; i < TrainQuantity; i++)
	{
		Train tr = Trains[i];
		cout << tr.TrainID << "         " << tr.TrainType << "           1" << "          " << tr.FirstWorkerNumber << "           " << tr.WorkersQuantity << endl;
	}
}

void SlaveUtilite()
{
	cout << "WorkerID  Name  Surname TrainID" << endl;
	for (int i = 0; i < WorkersQuantity; i++)
	{
		TrainWorker w = TrainWorkers[i];
		cout << w.WorkerID << "         " << w.Name << "           " << w.Surname << "           " << w.TrainID << endl;
	}
}

int main()
{
	ofstream out;
	out.open("D:\\BD\\Lab1BD\\T.txt");
	out << "TrainID  TrainType  Available  FirstWorkerNumber  WorkersQuantity" << endl;
	out.close();

	out.open("D:\\BD\\Lab1BD\\W.txt");
	out << "WorkerID  Name  Surname TrainID" << endl;
	out.close();

	out.open("D:\\BD\\Lab1BD\\T_ind.txt");
	out << "";
	out.close();

	ifstream in;
	in.open("D:\\BD\\Lab1BD\\Input.txt");

	while (true)
	{
		string command;
		cout << "Input a command \n";
		in >> command;

		if (command == "insert-m")
		{
			int trID;
			string trType;
			in >> trID >> trType;
			InsertMaster(trID, trType);
		}

		if (command == "get-m")
		{
			int TrainID;
			in >> TrainID;
			GetMaster(TrainID);
		}

		if (command == "insert-s")
		{
			int TrainID, WorkerID;
			string Name, Surname;
			in >> TrainID >> WorkerID >> Name >> Surname;
			InsertSlave(TrainID, WorkerID, Name, Surname);
		}

		if (command == "get-s")
		{
			int WorkerID;
			in >> WorkerID;
			GetSlave(WorkerID);
		}

		if (command == "del-s")
		{
			int WorkerID;
			in >> WorkerID;
			DeleteSlave(WorkerID);
			TrainFileOutput();
			WorkersFileOutput();
		}

		if (command == "del-m")
		{
			int TrainID;
			in >> TrainID;
			DeleteMaster(TrainID);
		}

		if (command == "update-m")
		{
			int TrainID;
			string TrainType;
			in >> TrainID >> TrainType;
			UpdateMaster(TrainID, TrainType);
		}

		if (command == "update-s")
		{
			int WorkerID, TrainID;
			string Name, SurName;
			in >> WorkerID >> Name >> SurName >> TrainID;
			UpdateSlave(WorkerID, Name, SurName, TrainID);
		}

		if (command == "ut-m")
		{
			MasterUtilite();
		}

		if (command == "ut-s")
		{
			SlaveUtilite();
		}

		if (command == "calc-m")
		{
			cout << "TrainsQuantity : " << TrainQuantity << endl;
		}

		if (command == "calc-s")
		{
			cout << "WorkersQuantity : " << WorkersQuantity << endl;
			for (int i = 0; i < TrainQuantity; i++)
				cout << "TrainID " << Trains[i].TrainID << " WorkersQuantity "<< Trains[i].WorkersQuantity << endl;
		}

		if (command == "stop")
			return 0;
	}
	
	in.close();
}






















// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
