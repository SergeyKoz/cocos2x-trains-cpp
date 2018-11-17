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
		
	public:
		static Cmd *getInstance();

		static void Exec(string cmdline);
		static void Exec(Command *cmd);
		static void Undo(Command *cmd);
		static void Undo();
		static void Redo();
		static void clear();

		Command *decode(string cmdline);
		string encode(Command *cmd);

		vector<Command> history;

		int pointer = 0;

		map<string, CmdFunc> execMethods;
		map<string, CmdFunc> undoMethods;

		void path(map<string, string> opts, vector<string> args);
		void _path(map<string, string> opts, vector<string> args);

		void semaphore(map<string, string> opts, vector<string> args);
		void _semaphore(map<string, string> opts, vector<string> args);

		void train(map<string, string> opts, vector<string> args);
		void _train(map<string, string> opts, vector<string> args);

		void save(map<string, string> opts, vector<string> args);
		void _save(map<string, string> opts, vector<string> args);

		void open(map<string, string> opts, vector<string> args);
		void _open(map<string, string> opts, vector<string> args);

		void railwayStation(map<string, string> opts, vector<string> args);
		void _railwayStation(map<string, string> opts, vector<string> args);
	};
}

#endif /*__GAME_CMD_H__*/
