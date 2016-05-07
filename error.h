#include <string>

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
