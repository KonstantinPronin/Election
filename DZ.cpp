#include<iostream>
#include<string>
#include<vector>

class City;
class Poll;
class Elector;
class Candidate;

class Error{
	std::string inf;
	
	public: 
		Error(std::string str){
	 		inf = str;
		}		
		std::string what(){
			return inf;
		} 
};

class City{
	friend Poll;
	friend Candidate;
	friend Elector;
	static std::vector<Poll*> polls;
	static std::vector<Candidate*> cands;
	bool EllectionStatus;		
	public:
		
};


class Poll{
	int number;
	std::vector<Elector*> elctrs;
	public:
		Poll(int num){
			number = num;
		}	 
		void AddElector(Elector* elc){
			elctrs.push_back(elc);
		}
		void DeleteElector(const Elector& elc){
			elctrs.erase(elctrs.begin() + elc.GetPollNum);
		}
		int ThisPollNum(){
			return this->number;
		}
};

class Elector{
	friend Poll;
	int PollNumber;
	std::string FName;
	std::string SName;
	bool status;
	public:
		Elector(int poll, std::string str1, std::string str2, bool flag){
			PollNumber = poll;
			FName = str1;
			SName = str2;
			status = flag;
			FindPoll(PollNumber)->AddElector(this);
		}
		Elector(const Elector& One){
			
		}
		
		int GetPollNum(){
			return PollNumber;
		}
		
		void AddToCandidate(){
			status = 1;	
		}
		
		Poll* FindPoll(int num){
 			int i = 0;
 			while (i < City::polls.size() && City::polls[i]->ThisPollNum() != num) i++;
 			if (i == City::polls.size()) throw Error("No Such Poll");
			return City::polls[i]; 	
//			auto it = polls.begin();
//			while (it < polls.end() && it -> ThisPollNum() != num) ++it;
//			if (it == polls.end()) throw Error("No Such Poll");
//			return it;
		}
};


class Candidate:private Elector{
	int VotesNum;
	public:
		Candidate(const Elector& basis){
			VotesNum = 0;
			//Elector A(basis); 
		}
};



int main(){
	
	return 0;
}
