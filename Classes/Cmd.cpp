#include "Cmd.h"
#include <functional>
//#include "cocos2d.h"
//USING_NS_CC;
#include "cocos2d/external/json/rapidjson.h"  
#include "cocos2d/external/json/document.h"
#include "Field.h"
#include "Helper.h"
#include "MenuLayer.h"

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

		undoMethods["path"] = &Cmd::_path;
		undoMethods["semaphore"] = &Cmd::_semaphore;
	}
	
	Cmd::~Cmd()
	{
	}

	void Cmd::Exec(string cmdline)
	{
		CCLOG("> %s", cmdline);

		Cmd *inst = Cmd::getInstance();

		Command *cmd = inst->ParseCmd(cmdline);
		inst->history.insert(inst->history.end(), *cmd);
		inst->pointer++;
		(*(MenuLayer*)Field::getInstance()->menuLayer).UndoButton->enable(true);
	
		CmdFunc execMethod = inst->execMethods[cmd->command];
		(inst->*execMethod)(cmd->opts, cmd->args);
	}

	void Cmd::Undo(Command *cmd)
	{
		CCLOG("< %s", cmd->command);
		
		Cmd *inst = Cmd::getInstance();	

		//Command *cmd = inst->ParseCmd(cmdline);
		//inst->history.insert(inst->history.end(), *cmd);
		inst->pointer--;

		CmdFunc execMethod = inst->undoMethods[cmd->command];
		(inst->*execMethod)(cmd->opts, cmd->args);
	}

	void Cmd::Undo()
	{
		Cmd *inst = Cmd::getInstance();
		//inst->pointer--;
		//Command cmd = inst->history[inst->pointer - 1];
		Cmd::Undo(&inst->history[inst->pointer - 1]);

		MenuLayer *menu = (MenuLayer*)Field::getInstance()->menuLayer;
		if (inst->pointer == 0) {
			menu->UndoButton->enable(false);
		}
		if (inst->pointer == inst->history.size() - 1) {
			menu->RedoButton->enable(true);
		}
	}

	void Cmd::Redo()
	{
		Cmd *inst = Cmd::getInstance();
		//inst->pointer++;
		Cmd::Exec(inst->history[inst->pointer + 1].command);

		MenuLayer *menu = (MenuLayer*)Field::getInstance()->menuLayer;
		if (inst->pointer == 1) {
			menu->UndoButton->enable(true);
		}

		if (inst->pointer == inst->history.size()) {
			menu->RedoButton->enable(false);
		}
	}

	void Cmd::clear()
	{
		//Field *Game = Field::getInstance();
		//MenuLayer *menu = (MenuLayer*)Game->menuLayer;

		MenuLayer *menu = (MenuLayer*)Field::getInstance()->menuLayer;
		menu->UndoButton->enable(false);
		menu->RedoButton->enable(false);
		
		Cmd *inst = Cmd::getInstance();

		/*std::vector<Command> history = inst->history;
		
		for (std::vector<Command>::iterator i = history.begin(); i != history.end(); ++i) {
			//Cmd *inst = Cmd::getInstance();
			delete (*i);
		}*/
		inst->history.clear();
		inst->pointer = 0;
		
		CCLOG("= clear");
	}
	
	Command *Cmd::ParseCmd(string cmdline)
	{
		vector<string> args;
		map<string, string> opts;

		vector<string> items = Helper::split(cmdline, ' ');
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
		}

		if (opts["remove"] == "") {

		}

	}

	void Cmd::semaphore(map<string, string> opts, vector<string> args) {
		if (opts["add"] == "") {
			rapidjson::Document jsonDoc;
			jsonDoc.Parse<kParseDefaultFlags>(opts["cell"].c_str());
			Field::getInstance()->cells[jsonDoc["x"].GetInt()][jsonDoc["y"].GetInt()].SetSemaphore(std::stoi(opts["point"]));
		}

		if (opts["remove"] == "") {

		}
	}

	//undo methods
	void Cmd::_path(map<string, string> opts, vector<string> args) {
		if (opts["add"] == "") {
			Field *Game = Field::getInstance();
			rapidjson::Document jsonDoc;
			if (opts["path"] != "") {
				jsonDoc.Parse<kParseDefaultFlags>(opts["path"].c_str());

				for (SizeType i = 0; i < jsonDoc.Size(); i++) {
					Game->cells[jsonDoc[i]["from"]["x"].GetInt()][jsonDoc[i]["from"]["y"].GetInt()].Disconnect(&Game->cells[jsonDoc[i]["to"]["x"].GetInt()][jsonDoc[i]["to"]["y"].GetInt()], jsonDoc[i]["point"].GetInt());
				}
			}

			if (opts["switch"] != "") {
				jsonDoc.Parse<kParseDefaultFlags>(opts["switch"].c_str());

				for (SizeType i = 0; i < jsonDoc.Size(); i++) {
					Game->cells[jsonDoc[i]["cell"]["x"].GetInt()][jsonDoc[i]["cell"]["y"].GetInt()].RemoveSwitch(jsonDoc[i]["point"].GetInt());
				}
			}
		}

		if (opts["remove"] == "") {

		}
	}

	void Cmd::_semaphore(map<string, string> opts, vector<string> args) {
		if (opts["add"] == "") {
			rapidjson::Document jsonDoc;
			jsonDoc.Parse<kParseDefaultFlags>(opts["cell"].c_str());
			Field::getInstance()->cells[jsonDoc["x"].GetInt()][jsonDoc["y"].GetInt()].RemoveSemaphore(std::stoi(opts["point"]));
		}

		if (opts["remove"] == "") {

		}
	}

}
