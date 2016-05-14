// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <sstream>
#include "CityV.h"

std::vector<std::string> Separator(std::string command);
void CommandSwitch(std::vector<std::string> command, City& Spb);

int main() {
	City Spb;
	//std::fstream file;	
	while (true) {
		std::string command;

		try {
			std::cout << ">";
			getline(std::cin, command);
			CommandSwitch(Separator(command), Spb);
			std::cout << "\n";
		}
		catch (Error& e) {
			std::cout << e.what();
		}
	}

	return 0;
}

std::vector<std::string> Separator(std::string command) {
	std::vector<std::string> result;
	std::stringstream strm(command);
	std::string word;

	while (getline(strm, word, ' ')) {
		result.push_back(word);
	}

	return result;
}


void CommandSwitch(std::vector<std::string> command, City& Spb) {
	if (command.size() == 1) {
		if (command[0] == "CreateElection") Spb.CreateElection();
		else if (command[0] == "StartElection") Spb.StartElection();
		else if (command[0] == "FinishElection") Spb.FinishElection();
		else if (command[0] == "CloseElection") Spb.CloseElection();
		else if (command[0] == "Statistics") Spb.AllStatistics();
		else if (command[0] == "ShowPolls") Spb.ShowPolls();
		else if (command[0] == "ShowElectors") Spb.ShowAllElectors();
		else if (command[0] == "ShowCandidates") Spb.ShowCandidates();
		else if (command[0] == "SelectWinner") Spb.SelectWinner();
		else if (command[0] == "Vote") {
			size_t PollNum;
			std::string str;
			std::cout << "Enter the poll number: ";
			std::cin >> PollNum;
			std::cout << "Enter in this format: Elector -> Candidate\n";
			std::cin.ignore();
			getline(std::cin, str);
			std::vector<std::string> data = Separator(str);
			if (data[2] != "->" || data.size() != 5) throw Error("Wrong format");
			Spb.Vote(PollNum, data[0], data[1], data[3], data[4]);
		}
		else throw Error("Wrong Format!\n");
	}
	else if (command.size() == 3) {
		if (command[0] == "ShowElectors" && command[1] == "->") Spb.ShowElectorsFromPoll(stoi(command[2], nullptr));
		else if (command[0] == "DeletePoll" && command[1] == "->") Spb.DeletePoll(stoi(command[2], nullptr));
		else if (command[0] == "Statistics" && command[1] == "->") Spb.Statistics(stoi(command[2], nullptr));
		else if (command[0] == "AddPoll") Spb.AddPoll(stoi(command[1], nullptr), command[2]);
		else if (command[0] == "DeleteCandidate") Spb.DelCandidate(command[1], command[2]);
		else throw Error("Wrong Format!\n");
	}
	else if (command.size() == 4) {
		if (command[0] == "AddCandidate") Spb.AddCandidate(stoi(command[1], nullptr), command[2], command[3]);
		else if (command[0] == "Merge" && command[2] == "<->") Spb.Merge(stoi(command[1], nullptr), stoi(command[3], nullptr));
		else if (command[0] == "AddElector") Spb.AddElector(stoi(command[1], nullptr), command[2], command[3]);
		else if (command[0] == "DeleteElector") Spb.DeleteElector(stoi(command[1], nullptr), command[2], command[3]);
		else throw Error("Wrong Format!\n");
	}
	else throw Error("Wrong Format!\n");
}
