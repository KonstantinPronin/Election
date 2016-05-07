#include<vector>
#include"error.h"
#include<iostream>


class Poll;
class City;
class Error;

class Candidate{
	size_t VotesNum;
	public:
		Candidate(){
			VotesNum = 0;
		}
};

class Elector:public Candidate{
	friend Poll;
	size_t PollNumber;
	std::string FName;
	std::string SName;
	bool vote;
	public:
		Elector(std::string str1, std::string str2, size_t num){
			PollNumber = num;
			FName = str1;
			SName = str2;
			vote = true;
			Candidate();
		}
		
//		int GetPollNum(){
//			return PollNumber;
//		}
		
//		Poll* FindPoll(int num){
//			int i = 0;
// 			while (i < City::polls.size() && City::polls[i]->ThisPollNum() != num) i++;
// 			if (i == City::polls.size()) throw Error("No Such Poll");
//			return City::polls[i]; 	
//		}
		
		void const ShowThis(){
			std::cout << FName << ' ' << SName << '\n';
		}
		
};

