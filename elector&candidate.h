//#pragma once
//#include<string>
#include<vector>
#include"error.h"
#include<iostream>
//#include"city.h"
//#include"poll.h"

class Poll;
class City;
class Error;

class Candidate{
	size_t VotesNum;
	public:
		Candidate(){
			VotesNum = 0;
		}
//		void AddToCandidate(){
//			City::cands.push_back(this);		
//		}
};

class Elector:public Candidate{
	friend Poll;
	//int PollNumber;
	std::string FName;
	std::string SName;
	//bool status;
	bool vote;
	public:
		Elector(std::string str1, std::string str2){
			//PollNumber = poll;
			FName = str1;
			SName = str2;
			vote = true;
			Candidate();
			//std::cout << "Ok";
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
		
//		~Elector(){
//			FindPoll(PollNumber)->DeleteElector(*this); 
//		}
};


