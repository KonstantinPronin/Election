#include"poll.h"
#include<map>

class Poll;
class Candidate;
class Elector;
class Error;

typedef std::map<size_t, Candidate*>::iterator m_iter;

class City{
	friend Poll;
	friend Candidate;
	friend Elector;
	std::vector<Poll*> polls;	
	std::map<size_t, Candidate*> cands;
	int ElectionStatus;		
	public:
		City():ElectionStatus(-1){}
		//Ìåòîäû, ñâÿçàííûå ñ âûáîðàìè
		void CreateElection();
		void StartElection();
		void FinishElection();
		void CloseElection();
		//Ìåòîäû, ñâÿçàííûå ñ ó÷àñòêàìè
		void AddPoll(size_t num, std::string str);
		Poll* FindPoll(size_t num);
		void DeletePoll(size_t num);
		void ShowPolls() const;
		void ShowElectorsFromPoll(size_t PollNum);
		void Merge(size_t FirstId, size_t SecondId);
		//Ìåòîäû, ñâÿçàííûå ñ èçáèðàòåëÿìè
		void AddElector(size_t PollNum, std::string str1, std::string str2);
		void DeleteElector(size_t PollNum, std::string str1, std::string str2);
		void ShowAllElectors() const;
		//Ìåòîäû, ñâÿçàííûå ñ êàíäèäàòàìè
		void AddCandidate(size_t Pollnum, std::string fname, std::string sname);
		size_t FindCandidate(std::string fname, std::string sname);
		void DelCandidate(std::string fname, std::string sname);
		void SelectWinner();
};



void City::CreateElection(){
	if(ElectionStatus == 0) throw Error("Elections have already been created");
	ElectionStatus = 0;
}

void City::StartElection(){
	if(ElectionStatus == 2) throw Error("Elections have already been started");
	ElectionStatus = 2;
}

void City::FinishElection(){
	if(ElectionStatus == 1) throw Error("Elections have already been finished");
	ElectionStatus = 1;
	SelectWinner();
}

void City::CloseElection(){
	if(ElectionStatus == -1) throw Error("Elections have already been closed");
	ElectionStatus = -1;
	for (m_iter it = cands.begin(); it != cands.end(); ++it)
		delete it->second;
	cands.clear();	
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
	for (size_t i = 0; i < sptr->ElectorList().size(); i++){
		Elector* ForChange = new Elector(sptr->CopyElectorList()[i]);
		fptr->ElectorList().push_back(ForChange);		
	}
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

void City::AddCandidate(size_t PollNum, std::string fname, std::string sname){
	if (ElectionStatus) throw Error("Election hasn`t been created or has already started");
	Candidate* NewCand = new Candidate(FindPoll(PollNum)->FindElector(fname, sname));	
	cands.insert(std::pair<size_t, Candidate*>(cands.size(), NewCand));
}

size_t City::FindCandidate(std::string fname, std::string sname){
	if (cands.empty()) throw Error("No candidates");
	for (m_iter it = cands.begin(); it != cands.end(); ++it){
		if (it->second->compare(fname, sname)) return it->first;
	}
	throw Error("No such Candidate");
}

void City::DelCandidate(std::string fname, std::string sname){
	if (ElectionStatus) throw Error("Election hasn`t been created or has already started");
	m_iter it = cands.find(FindCandidate(fname, sname));
	delete (it->second);
	cands.erase(it); 
}

void City::SelectWinner(){
	m_iter max = cands.begin();
	for (m_iter it = cands.begin(); it != cands.end(); ++it)
		if (max->second->GetVotes() < it->second->GetVotes()) max = it;
	max->second->PrintMe();	
}
