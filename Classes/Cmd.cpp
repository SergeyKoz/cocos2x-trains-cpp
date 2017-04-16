#include "Cmd.h"
#include <functional>
//#include "cocos2d.h"
//USING_NS_CC;
#include "cocos2d/external/json/rapidjson.h"  
#include "cocos2d/external/json/document.h"
#include "Field.h"

using namespace rapidjson;

namespace GameObjects {

	Cmd *Cmd::p_instance = 0;

	Cmd *Cmd::getInstance() {
		if (p_instance == 0) {
			p_instance = new Cmd;
		}
		return p_instance;
	}

	Cmd::Cmd()
	{
		execMethods["path"] = &Cmd::path;
		execMethods["semaphore"] = &Cmd::semaphore;
	}
	
	Cmd::~Cmd()
	{
	}

	void Cmd::Exec(string cmdline)
	{
		Cmd *inst = Cmd::getInstance();
		
		CCLOG("> %s", cmdline);
		
		Command *cmd = inst->ParseCmd(cmdline);
		inst->history.insert(inst->history.end(), *cmd);

		CmdFunc execMethod = inst->execMethods[cmd->command];
		(inst->*execMethod)(cmd->opts, cmd->args);
	}

	Command *Cmd::ParseCmd(string cmdline)
	{
		vector<string> args;
		map<string, string> opts;

		vector<string> items = split(cmdline, ' ');
		string command = items[0];
		int pos;
		string caption, value;
		for (int c = 1; c < items.size(); c++){
			if (items[c] != ""){
				if (items[c].substr(0, 2) == "--"){
					pos = items[c].find("=");
					if (pos != string::npos) {
						caption = items[c].substr(2, pos - 2);
						value = items[c].substr(pos + 1);
						if (caption != ""){
							opts.insert(pair<string, string>(caption, value));
						}
					}else{
						caption = items[c].substr(2);
						if (caption != ""){
							opts.insert(pair<string, string>(caption, ""));
						}

					}
				}
				else {
					args.insert(args.end(), items[c]);
				}
			}
		}

		return new Command(command, opts, args);
	}

	vector<string> &Cmd::split(const string &s, char delim, vector<string> &elems) {
		stringstream ss(s);
		string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}
	
	vector<string> Cmd::split(const string &s, char delim) {
		std::vector<string> elems;
		split(s, delim, elems);
		return elems;
	}

	//execution methods
	void Cmd::path(map<string, string> opts, vector<string> args){
		if (opts["add"] == "") {			
			Field *Game = Field::getInstance();
			rapidjson::Document jsonDoc;
			if (opts["path"] != "") {
				jsonDoc.Parse<kParseDefaultFlags>(opts["path"].c_str());

				for (SizeType i = 0; i < jsonDoc.Size(); i++){
					Game->cells[jsonDoc[i]["from"]["x"].GetInt()][jsonDoc[i]["from"]["y"].GetInt()].Connect(&Game->cells[jsonDoc[i]["to"]["x"].GetInt()][jsonDoc[i]["to"]["y"].GetInt()], jsonDoc[i]["point"].GetInt());
				}
			}

			if (opts["switch"] != "") {
				jsonDoc.Parse<kParseDefaultFlags>(opts["switch"].c_str());

				for (SizeType i = 0; i < jsonDoc.Size(); i++) {
					Game->cells[jsonDoc[i]["cell"]["x"].GetInt()][jsonDoc[i]["cell"]["y"].GetInt()].SetSwitch(jsonDoc[i]["point"].GetInt());
				}
			}

			/*
			local i
			for c = 1, #Path do
				i=Path[c]
				Game:getCell(i.from.x, i.from.y):Connect(Game:getCell(i.to.x, i.to.y), i.point)
			end
			if opts.switch~=nil then        
				local Switch=json.decode(opts.switch)
				for c = 1, #Switch do
					i=Switch[c]
					Game:getCell(i.cell.x, i.cell.y):SetSwitch(i.point)
				end 
			end
			*/
		}

		if (opts["remove"] == "") {

		}

	}

	void Cmd::semaphore(map<string, string> opts, vector<string> args) {
		if (opts["add"] == "") {
			Field *Game = Field::getInstance();
			rapidjson::Document jsonDoc;		
		}

		if (opts["remove"] == "") {

		}
	}
	
}
