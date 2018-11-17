#ifndef __GAME_COMMAND_H__
#define __GAME_COMMAND_H__ 

#include "cocos2d.h"
#include <string>
#include <vector>
#include <map>

USING_NS_CC;
using namespace std;

namespace GameObjects {

	struct CommandsElement {
		Sprite* image;
		int ZIndex;
	};

	class Command
	{
		
	public:
		Command();
		Command(string command, map<string, string> opts, vector<string> args);
		~Command();
		string command;
		map<string, string> opts;
		vector<string> args;
		vector<CommandsElement> elements;
	};
}

#endif /*__GAME_COMMAND_H__*/
