#include"poll.h"
#include<map>

class Poll;
class Candidate;
class Elector;
class Error;

typedef std::map<size_t, Candidate*>::iterator m_iter;
typedef std::map<size_t, Candidate*>::const_iterator const_m_iter;


class City{
	friend Poll;
	friend Candidate;
	friend Elector;
	std::vector<Poll*> polls;	
	std::map<size_t, Candidate*> cands;
	int ElectionStatus;		
	public:
		City():ElectionStatus(-1){}
		//Методы, связанные с выборами
		void CreateElection();
		void StartElection();
		void FinishElection();
		void CloseElection();
		void Statistics(size_t PollNum);
		void AllStatistics();
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
		void Vote(size_t PollNum, std::string fname, std::string sname, std::string candfname, std::string candsname);
		//Методы, связанные с кандидатами
		void AddCandidate(size_t Pollnum, std::string fname, std::string sname);
		size_t FindCandidate(std::string fname, std::string sname);
		void DelCandidate(std::string fname, std::string sname);
		void ShowCandidates() const;
		void SelectWinner();
		~City();
};



void City::CreateElection(){
	if(ElectionStatus != -1) throw Error("Elections have already been created\n");
	ElectionStatus = 0;
	std::cout << "Elections have been created\n";
}

void City::StartElection(){
	if(ElectionStatus != 0) throw Error("Elections have already been started\n");
	ElectionStatus = 2;
	std::cout << "Elections have been started\n";
}

void City::FinishElection(){
	if(ElectionStatus != 2) throw Error("Elections have already been finished\n");
	ElectionStatus = 1;
	SelectWinner();
}

void City::CloseElection(){
	if(ElectionStatus == -1) throw Error("Elections have already been closed\n");
	ElectionStatus = -1;
	for (m_iter it = cands.begin(); it != cands.end(); ++it)
		delete it->second;
	cands.clear();
	std::cout << "Elections have been closed\n";	
}

void City::AddPoll(size_t num, std::string str){
	if (ElectionStatus == 2) throw Error("Elections have already been started\n");
	Poll* NewPoll = new Poll(num, str);
	polls.push_back(NewPoll);
} 

Poll* City::FindPoll(size_t num){
	if (polls.empty()) throw Error("No polls\n");
	for (size_t i = 0; i < polls.size(); i++){
		if(polls[i]->ThisPollNum() == num) return polls[i];
	}
	throw Error("No such poll\n");	
}

void City::DeletePoll(size_t num){
	if (ElectionStatus == 2) throw Error("Elections have already been started\n");
	delete FindPoll(num);
	polls.erase(polls.begin() + num - 1);
}

void City::Merge(size_t FirstId, size_t SecondId){
	if (ElectionStatus == 2) throw Error("Elections have already been started\n");
	Poll* fptr = FindPoll(FirstId);
	Poll* sptr = FindPoll(SecondId);
	for (size_t i = 0; i < sptr->ElectorList().size(); i++){
		Elector* ForChange = new Elector(sptr->CopyElectorList()[i]);
		fptr->ElectorList().push_back(ForChange);		
	}
	DeletePoll(SecondId);					
}

void City::Vote(size_t PollNum, std::string fname, std::string sname, std::string candfname, std::string candsname){
	if (ElectionStatus != 2) throw Error("Elections have not been started\n");
	if (fname == candfname && sname == candsname) throw Error("Candidate cann`t vote for himself\n");
	FindPoll(PollNum)->FindElector(fname, sname)->Vote(candfname, candsname);
	cands.find(FindCandidate(candfname, candsname))->second->AddVote();
}

void City::Statistics(size_t PollNum){
	if (ElectionStatus != 1) throw Error("Elections have not been finished\n");
	FindPoll(PollNum)->Statistics();
}

void City::AllStatistics(){
	if (ElectionStatus != 1) throw Error("Elections have not been finished\n");
	for (size_t i = 0; i < polls.size(); i++)
		polls[i]->Statistics();
}

void City::AddElector(size_t PollNum, std::string str1, std::string str2){
	if (ElectionStatus == 2) throw Error("Elections have already been started\n");
	FindPoll(PollNum)->AddElector(str1, str2);
}

void City::DeleteElector(size_t PollNum, std::string str1, std::string str2){
	if (ElectionStatus == 2) throw Error("Elections have already been started\n");
	FindPoll(PollNum)->DeleteElector(str1, str2);
}

void City::ShowPolls() const{
	if (polls.empty()) throw Error("No polls\n");
	std::cout << "Polls:\n";
	for (int i = 0; i < polls.size(); i++)
		polls[i]->ShowThis();
}

void City::ShowElectorsFromPoll(size_t PollNum){
	FindPoll(PollNum)->ShowElectors();
}

void City::ShowAllElectors() const{
	if (polls.empty()) throw Error("No polls\n");
	for (int i = 0; i < polls.size(); i++)
		polls[i]->ShowElectors();
}

void City::AddCandidate(size_t PollNum, std::string fname, std::string sname){
	if (ElectionStatus) throw Error("Election hasn`t been created or has already started\n");
	Candidate* NewCand = new Candidate(FindPoll(PollNum)->FindElector(fname, sname));	
	cands.insert(std::pair<size_t, Candidate*>(cands.size(), NewCand));
}

size_t City::FindCandidate(std::string fname, std::string sname){
	if (cands.empty()) throw Error("No candidates\n");
	for (m_iter it = cands.begin(); it != cands.end(); ++it){
		if (it->second->compare(fname, sname)) return it->first;
	}
	throw Error("No such Candidate\n");
}

void City::DelCandidate(std::string fname, std::string sname){
	if (ElectionStatus) throw Error("Election hasn`t been created or has already started\n");
	m_iter it = cands.find(FindCandidate(fname, sname));
	delete (it->second);
	cands.erase(it); 
}

void City::ShowCandidates() const{
	std::cout << "Candidates:\n";
	for (const_m_iter it = cands.begin(); it != cands.end(); ++it)
		it->second->PrintMe();
}

void City::SelectWinner(){
	if (ElectionStatus != 1) throw Error("Election hasn`t been fifnished\n");
	m_iter max = cands.begin();
	for (m_iter it = cands.begin(); it != cands.end(); ++it)
		if (max->second->GetVotes() < it->second->GetVotes()) max = it;
	std::cout << "Winner:\n";  
	max->second->PrintMe();	
}

City::~City(){
	CloseElection();
	for(size_t i = 0; i < polls.size(); i++) delete polls[i];
	polls.clear();
}
