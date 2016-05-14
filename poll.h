#pragma once
#include"ElectorV.h"

class Elector;
class City;
class Error;

class Poll {
	size_t number;
	std::string name;
	std::vector<Elector*> elctrs;
public:
	Poll(size_t num, std::string str) :number(num), name(str) {}
	void AddElector(std::string str1, std::string str2);
	Elector* FindElector(std::string str1, std::string str2);
	void DeleteElector(std::string str1, std::string str2);
	size_t ThisPollNum() { return number; }
	std::vector<Elector*>& ElectorList() { return elctrs; }
	std::vector<Elector*> CopyElectorList() { return elctrs; }
	void ShowThis() const;
	void ShowElectors() const;
	void Statistics() const;
	~Poll();
};



void Poll::AddElector(std::string str1, std::string str2) {
	Elector* NewEl = new Elector(str1, str2);
	elctrs.push_back(NewEl);
}

Elector* Poll::FindElector(std::string str1, std::string str2) {
	if (elctrs.empty()) throw Error("No electors\n");
	for (size_t i = 0; i < elctrs.size(); i++) {
		if (elctrs[i]->FName == str1 && elctrs[i]->SName == str2)
			return elctrs[i];
	}
	throw Error("No such elector\n");
}


void Poll::DeleteElector(std::string str1, std::string str2) {
	if (elctrs.empty()) throw Error("No electors\n");
	size_t i = 0;
	while (i < elctrs.size() && (elctrs[i]->FName != str1 || elctrs[i]->SName != str2)) i++;
	Elector* ptr = elctrs[i];
	elctrs.erase(elctrs.begin() + i);
	delete ptr;
}

void Poll::ShowThis() const {
	std::cout << number << ' ' << name << '\n';
}

void Poll::ShowElectors() const {
	std::cout << number << ' ' << name << ":\n";
	if (elctrs.empty()) std::cout << "Electors list is empty\n";
	for (size_t i = 0; i < elctrs.size(); ++i)
		elctrs[i]->ShowThis();
}

void Poll::Statistics() const {
	for (size_t i = 0; i < elctrs.size(); i++)
		elctrs[i]->Statistics();
}

Poll::~Poll() {
	for (size_t i = 0; i < elctrs.size(); i++) {
		delete elctrs[i];
	}
	elctrs.clear();
}
