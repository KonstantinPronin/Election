#pragma once
#include<vector>
#include"ErrorV.h"
#include<iostream>


class Poll;
class City;
class Error;
class Candidate;

class Elector {
	friend Poll;
	friend Candidate;
	std::string FName;
	std::string SName;
	bool vote;
	std::string CandFName;
	std::string CandSName;
public:
	Elector(std::string str1, std::string str2) {
		FName = str1;
		SName = str2;
		vote = true;
		CandFName = "didn`t";
		CandSName = "vote";
	}
	Elector(Elector* base) {
		FName = base->FName;
		SName = base->SName;
		vote = base->vote;
		CandFName = base->CandFName;
		CandSName = base->CandSName;
	}
	void ShowThis() const {
		std::cout << FName << ' ' << SName << '\n';
	}
	void Vote(std::string str1, std::string str2) {
		if (!vote) throw Error("The elector has already voted\n");
		vote = false;
		CandFName = str1;
		CandSName = str2;
	}
	void Statistics() const {
		if (vote) std::cout << FName << ' ' << SName << ' ' << "Didn`t vote\n";
		else std::cout << FName << ' ' << SName << " voted for " << CandFName << ' ' << CandSName << '\n';
	}

};



class Candidate {
	size_t VotesNum;
	Elector* parent;
public:
	Candidate(Elector* ptr) {
		VotesNum = 0;
		parent = ptr;
	}
	bool compare(std::string str1, std::string str2) {
		if (str1 == parent->FName && str2 == parent->SName) return true;
		else return false;
	}
	size_t GetVotes() { return VotesNum; }
	void AddVote() { VotesNum++; }
	void PrintMe() const {
		std::cout << parent->FName << ' ' << parent->SName << '\n';
	}
};


