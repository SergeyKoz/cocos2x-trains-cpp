#ifndef __GAME_COMMAND_H__
#define __GAME_COMMAND_H__ 

#include <string>
#include <vector>
#include <map>
using namespace std;

namespace GameObjects {

	class Command
	{
		
	public:
		Command(string command, map<string, string> opts, vector<string> args);
		~Command();
		string command;
		map<string, string> opts;
		vector<string> args;
	};
}

#endif /*__GAME_COMMAND_H__*/
