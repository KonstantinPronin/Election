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
	bool ElectionStatus;		
	public:
		City():ElectionStatus(0){}
		void CreateElection();
		void CloseElection();
		void AddPoll(size_t num, std::string str);
		Poll* FindPoll(size_t num);
		void DeletePoll(size_t num);
		void ShowPolls() const;
		void ShowAllElectors() const;
};



void City::CreateElection(){
	ElectionStatus = 1;
}

void City::CloseElection(){
	ElectionStatus = 0;
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
	polls.erase(polls.begin() + (FindPoll(num)->ThisPollNum()));
	delete FindPoll(num);
}

void City::ShowPolls() const{
	if (polls.empty()) throw Error("No polls");
	for (int i = 0; i < polls.size(); i++)
		polls[i]->ShowThis();
}

void City::ShowAllElectors() const{
	if (polls.empty()) throw Error("No polls");
	for (int i = 0; i < polls.size(); i++)
		polls[i]->ShowElectors();
}
