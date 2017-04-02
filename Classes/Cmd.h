#ifndef __GAME_CMD_H__
#define __GAME_CMD_H__

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "Command.h"
using namespace std;

namespace GameObjects {

	class Cmd
	{
		typedef void (Cmd::*CmdFunc)(map<string, string>, vector<string>);

	protected:
		Cmd();
		Cmd(const Cmd&);
		Cmd &operator=(Cmd&);
		~Cmd();
	private:
		static Cmd *p_instance;

		vector<string> &split(const string &s, char delim, vector<string> &elems);
		vector<string> split(const string &s, char delim);
		
	public:
		static Cmd *getInstance();
		static void Exec(string cmdline);
		Command *ParseCmd(string cmdline);

		vector<Command> history;

		map<string, CmdFunc> execMethods;

		void path(map<string, string> opts, vector<string> args);
		void semaphore(map<string, string> opts, vector<string> args);

	};
}

#endif /*__GAME_CMD_H__*/
