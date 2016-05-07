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
		City(){
			EllectionStatus = 0;
		}
		void CreateEll(){
			EllectionStatus = 1;
		}
		void ShowPolls(){
			if (polls.size() == 0) throw Error("No polls");
			for (int i = 0; i < polls.size(); i++)
				polls[i]->ShowThis();
		}
		void ShowAllElectors(){
			if (polls.size() == 0) throw Error("No polls");
			for (int i = 0; i < polls.size(); i++)
				polls[i]->ShowElectors();
		}
};
std::vector<Poll*> City::polls;
std::vector<Candidate*> City::cands;



class Poll{
	int number;
	std::string name;
	std::vector<Elector*> elctrs;
	public:
		Poll(int num, std::string str){
			number = num;
			name = str;
			City::polls.push_back(this);
		}	 
		void AddElector(Elector* elc){
			elctrs.push_back(elc);
		}
		void DeleteElector(const Elector& elc){
			int i = 0;
			
		}
		int ThisPollNum(){
			return number;
		}
		void Showthis(){
			std::cout << number << ' ' << name << '\n';
		}
		void ShowElectors(){
			if (elctrs.size() == 0) throw Error("No Electors");
			for (size_t i = 0; i < elctrs.size(); ++i)
				elctrs[i]->ShowThis();
		}
};

class Candidate{
	size_t VotesNum;
	public:
		Candidate(){
			VotesNum = 0;
		}
		void AddToCandidate(){
			City::cands.push_back(this);		
		}
};

class Elector:public Candidate{
	//friend Poll;
	int PollNumber;
	std::string FName;
	std::string SName;
	//bool status;
	bool vote;
	public:
		Elector(int poll, std::string str1, std::string str2){
			PollNumber = poll;
			FName = str1;
			SName = str2;
			vote = true;
			FindPoll(PollNumber)->AddElector(this);
			Candidate();
		}
		
		int GetPollNum(){
			return PollNumber;
		}
		
		Poll* FindPoll(int num){
			int i = 0;
 			while (i < City::polls.size() && City::polls[i]->ThisPollNum() != num) i++;
 			if (i == City::polls.size()) throw Error("No Such Poll");
			return City::polls[i]; 	
		}
		
		void ShowThis(){
			std::cout << FName << ' ' << SName << '\n';
		}
		
		~Elector(){
			FindPoll(PollNumber)->DeleteElector(*this); 
		}
};



//
//class Candidate:private Elector{
//	int VotesNum;
//	public:
//		Candidate(const Elector& basis){
//			VotesNum = 0;
//			//Elector A(basis); 
//		}
//};



int main(){
	City Moscow();
	Poll A(1, "South");
	Elector First(1, "Ivan", "Ivanov");
	Elector Second(1, "Nik", "Ivanov");
	
	return 0;
}
