#include"elector&candidate.h"

class Elector;
class City;
class Error;

class Poll{
	size_t number;
	std::string name;
	std::vector<Elector*> elctrs;
	public:
		Poll(size_t num, std::string str):number(num), name(str){}
		void AddElector(std::string str1, std::string str2);
		Elector* FindElector(std::string str1, std::string str2);
		void DeleteElector(std::string str1, std::string str2);
		size_t ThisPollNum() {return number;}
		std::vector<Elector*>& ElectorList(){return elctrs;}
		void ShowThis() const;
		void ShowElectors() const;
		~Poll();
};


void Poll::AddElector(std::string str1, std::string str2){
	Elector* NewEl= new Elector(str1, str2, number);
	elctrs.push_back(NewEl);
}

Elector* Poll::FindElector(std::string str1, std::string str2){
	if (elctrs.empty()) throw Error("No polls");
	for (size_t i = 0; i < elctrs.size(); i++){
		if (elctrs[i]->FName == str1 && elctrs[i]->SName == str2)
			return elctrs[i];
	}
	throw Error("No such elector");	
}


void Poll::DeleteElector(std::string str1, std::string str2){
	if (elctrs.empty()) throw Error("No polls");
	size_t i = 0;
	while(i < elctrs.size() && (elctrs[i]->FName != str1 || elctrs[i]->SName != str2)) i++;
	Elector* ptr = elctrs[i];
	elctrs.erase(elctrs.begin() + i);
	delete ptr;
}

void Poll::ShowThis() const{
	std::cout << number << ' ' << name << '\n';
}

void Poll::ShowElectors() const{
	if (elctrs.size() == 0) throw Error("No Electors");
	for (size_t i = 0; i < elctrs.size(); ++i)
		elctrs[i]->ShowThis();
}

Poll::~Poll(){
	for(size_t i = 0; i < elctrs.size(); i++){
		delete elctrs[i];
	}
	elctrs.clear();
}
