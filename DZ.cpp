#include"city.h"
//class City;

int main(){
	
	//while(std::cin){

	try{
	
	City Spb;
	Spb.CreateElection();
	Poll A(1, "south");
//	A.ShowThis();
//	A.ShowElectors();
//	A.AddElector("Ivan", "Ivanov");
//	A.ShowElectors();
	//Elector First(1, "Ivan", "Ivanov");
	//Elector Second(1, "Nik", "Ivanov");
	Spb.ShowPolls();
	//First.ShowThis();
	//City::CreateElection();
	}catch(Error& e){
		std::cout << e.what();
	}
	
	return 0;
}
