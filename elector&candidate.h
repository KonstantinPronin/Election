#include<vector>
#include"error.h"
#include<iostream>


class Poll;
class City;
class Error;
class Candidate;

class Elector{
	friend Poll;
	friend Candidate;
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
		}
		Elector(Elector* base){
			PollNumber = base->PollNumber;
			FName = base->FName; 
			SName = base->SName;
			vote = base->vote;
		}		
		void ShowThis() const{
			std::cout << FName << ' ' << SName << '\n';
		}
		
};



class Candidate{
	size_t VotesNum;
	Elector* parent;
	public:
		Candidate(Elector* ptr){
			VotesNum = 0;
			parent = ptr;
		}
		bool compare(std::string str1, std::string str2){
			if (str1 == parent->FName && str2 == parent->SName) return true;
				else return false;
		}
		size_t GetVotes(){return VotesNum;}
		void PrintMe(){
			std::cout << parent->FName << ' ' << parent->SName << '\n';
		}
};


