#ifndef __GAME_COMMAND_H__
#define __GAME_COMMAND_H__ 

#include "cocos2d.h"
#include <string>
#include <vector>
#include <map>

USING_NS_CC;
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
		vector<Sprite*> elements;
	};
}

#endif /*__GAME_COMMAND_H__*/
