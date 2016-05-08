#include"city.h"
//class City;

int main(){
	
	//while(std::cin){
	City Spb;
	try{
	
	
	Spb.CreateElection();

	Spb.AddPoll(1, "South");
	Spb.AddPoll(2, "North");
	Spb.AddPoll(3, "East");

	Spb.AddElector(2, "Ivan", "Ivanov");
 	Spb.AddElector(1, "Misha", "Artemov");
	Spb.AddElector(3, "Max", "Tiger");
	Spb.AddElector(3, "Lena", "Kolina");
	
	Spb.ShowPolls();
	Spb.ShowAllElectors();

	Spb.Merge(1, 2);
	Spb.ShowPolls();
	Spb.ShowElectorsFromPoll(3);

	Spb.AddCandidate(1, "Ivan", "Ivanov");
	Spb.AddCandidate(3, "Lena", "Kolina");
	Spb.DelCandidate("Lena", "Kolina");
	Spb.AddCandidate(3, "Max", "Tiger");
	Spb.ShowCandidates();

	Spb.StartElection();
	Spb.Vote(1, "Misha", "Artemov", "Max", "Tiger");
	//Spb.Vote(1, "Ivan", "Ivanov", "Ivan", "Ivanov");
	Spb.Vote(3, "Lena", "Kolina", "Max", "Tiger");
	Spb.Vote(3, "Max", "Tiger", "Ivan", "Ivanov");
	
	Spb.FinishElection();
	//Spb.Statistics(1);
	Spb.AllStatistics();
	
	
//	Spb.CloseElection();
//	Spb.CreateElection();
//	Spb.AddCandidate(3, "Lena", "Kolina");
//	Spb.ShowPolls();
//	Spb.ShowAllElectors();
	
	}catch(Error& e){
		std::cout << e.what();
	}
	
	return 0;
}
