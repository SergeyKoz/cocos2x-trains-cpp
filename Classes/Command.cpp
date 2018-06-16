#include "Command.h"

namespace GameObjects {

	Command::Command()
	{	
	}

	Command::Command(string command, map<string, string> opts, vector<string> args)
	{
		Command::command = command;
		Command::opts = opts;
		Command::args = args;
	}

	Command::~Command()
	{
	}
}
