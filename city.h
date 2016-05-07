#include"poll.h"

class Poll;
class Candidate;
class Elector;
class Error;


class City{
	friend Poll;
	friend Candidate;
	friend Elector;
	std::vector<Poll*> polls;	
	std::vector<Candidate*> cands;
	int ElectionStatus;		
	public:
		City():ElectionStatus(-1){}
		//Методы, связанные с выборами
		void CreateElection();
		void FinishElection();
		void CloseElection();
		//Методы, связанные с участками
		void AddPoll(size_t num, std::string str);
		Poll* FindPoll(size_t num);
		void DeletePoll(size_t num);
		void ShowPolls() const;
		void ShowElectorsFromPoll(size_t PollNum);
		void Merge(size_t FirstId, size_t SecondId);
		//Методы, связанные с избирателями
		void AddElector(size_t PollNum, std::string str1, std::string str2);
		void DeleteElector(size_t PollNum, std::string str1, std::string str2);
		void ShowAllElectors() const;
};



void City::CreateElection(){
	ElectionStatus = 0;
}

void City::FinishElection(){
	ElectionStatus = 1;
}

void City::CloseElection(){
	ElectionStatus = -1;
}

void City::AddPoll(size_t num, std::string str){
	Poll* NewPoll = new Poll(num, str);
	polls.push_back(NewPoll);
}

Poll* City::FindPoll(size_t num){
	if (polls.empty()) throw Error("No polls");
		for (size_t i = 0; i < polls.size(); i++){
			if(polls[i]->ThisPollNum() == num) return polls[i];
		}
		throw Error("No such poll");	
}

void City::DeletePoll(size_t num){
	delete FindPoll(num);
	polls.erase(polls.begin() + num - 1);
}

void City::Merge(size_t FirstId, size_t SecondId){
	Poll* fptr = FindPoll(FirstId);
	Poll* sptr = FindPoll(SecondId);
	for (size_t i = 0; i < sptr->ElectorList().size(); i++)
		fptr->ElectorList().push_back(sptr->ElectorList()[i]);	
	DeletePoll(SecondId);					
}

void City::AddElector(size_t PollNum, std::string str1, std::string str2){
	FindPoll(PollNum)->AddElector(str1, str2);
}

void City::DeleteElector(size_t PollNum, std::string str1, std::string str2){
	FindPoll(PollNum)->DeleteElector(str1, str2);
}

void City::ShowPolls() const{
	if (polls.empty()) throw Error("No polls");
	for (int i = 0; i < polls.size(); i++)
		polls[i]->ShowThis();
}

void City::ShowElectorsFromPoll(size_t PollNum){
	FindPoll(PollNum)->ShowElectors();
}

void City::ShowAllElectors() const{
	if (polls.empty()) throw Error("No polls");
	for (int i = 0; i < polls.size(); i++)
		polls[i]->ShowElectors();
}
