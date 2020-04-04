#include "Cmd.h"
#include <functional>
//#include "cocos2d.h"
//USING_NS_CC;
#include "json/rapidjson.h"  
#include "json/document.h"
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
		execMethods["save"] = &Cmd::save;
		execMethods["open"] = &Cmd::open;
		execMethods["train"] = &Cmd::train;
		execMethods["station"] = &Cmd::railwayStation;

		undoMethods["path"] = &Cmd::_path;
		undoMethods["semaphore"] = &Cmd::_semaphore;
		undoMethods["train"] = &Cmd::_train;
		undoMethods["save"] = &Cmd::_save;
		undoMethods["open"] = &Cmd::_open;
		undoMethods["station"] = &Cmd::_railwayStation;
	}
	
	Cmd::~Cmd()
	{
	}

	void Cmd::Exec(string cmdline)
	{
		CCLOG("> %s", cmdline);

		Cmd *inst = Cmd::getInstance();

		Command *cmd = inst->decode(cmdline);
		if (inst->history.size() > inst->pointer) {
			inst->history.resize(inst->pointer);
		}
		inst->history.insert(inst->history.end(), *cmd);

		inst->pointer++;
		(*(MenuLayer*)Field::getInstance()->menuLayer).UndoButton->enable(true);
	
		CmdFunc execMethod = inst->execMethods[cmd->command];
		(inst->*execMethod)(cmd->opts, cmd->args);
	}

	void Cmd::Exec(Command *cmd)
	{
		CCLOG("> %s", cmd->command);

		Cmd *inst = Cmd::getInstance();
		CmdFunc execMethod = inst->execMethods[cmd->command];
		(inst->*execMethod)(cmd->opts, cmd->args);
	}

	void Cmd::Undo(Command *cmd)
	{
		CCLOG("< %s", cmd->command);
		
		Cmd *inst = Cmd::getInstance();
		inst->pointer--;
		CmdFunc execMethod = inst->undoMethods[cmd->command];
		(inst->*execMethod)(cmd->opts, cmd->args);
	}

	void Cmd::Undo()
	{
		Cmd *inst = Cmd::getInstance();
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
		inst->pointer++;
		Cmd::Exec(&(inst->history[inst->pointer - 1]));

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
		MenuLayer *menu = (MenuLayer*)Field::getInstance()->menuLayer;
		menu->UndoButton->enable(false);
		menu->RedoButton->enable(false);
		
		Cmd *inst = Cmd::getInstance();
		std::vector<Command> history = inst->history;		
		for (std::vector<Command>::iterator i = history.begin(); i != history.end(); ++i) {
			i->elements.clear();
		}

		inst->history.clear();
		inst->pointer = 0;		
		CCLOG("= clear");
	}
	
	Command *Cmd::decode(string cmdline)
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

	string Cmd::encode(Command *cmd)
	{
		string cmdline = cmd->command;
		string opts = "";
		for (std::map<string, string>::iterator i = cmd->opts.begin(); i != cmd->opts.end(); ++i) {
			opts += " --" + i->first + (i->second != "" ? "=" + i->second : "");
		}
		string args = "";
		for (int i = 0; i < cmd->args.size(); i++) {
			args += " " + cmd->args[i];
		}
		return cmdline + opts + args;
	}

	//execution methods
	void Cmd::path(map<string, string> opts, vector<string> args){
		if (opts["add"] == "") {			
			Field *Game = Field::getInstance();
			rapidjson::Document jsonDoc;
			if (opts["path"] != "") {
				jsonDoc.Parse<kParseDefaultFlags>(opts["path"].c_str());

				for (SizeType i = 0; i < jsonDoc.Size(); i++) {
					if (jsonDoc[i].HasMember("cell")) {
						Game->cells[jsonDoc[i]["cell"]["x"].GetInt()][jsonDoc[i]["cell"]["y"].GetInt()].Connect(Elements::getTrackElement(jsonDoc[i]["element"].GetString()), jsonDoc[i]["point"].GetInt());
					}					
				}
			}

			if (opts["switch"] != "") {
				jsonDoc.Parse<kParseDefaultFlags>(opts["switch"].c_str());

				for (SizeType i = 0; i < jsonDoc.Size(); i++) {
					Game->cells[jsonDoc[i]["cell"]["x"].GetInt()][jsonDoc[i]["cell"]["y"].GetInt()].SetSwitch(jsonDoc[i]["point"].GetInt());
					if (jsonDoc[i].HasMember("position")) {
						string position = jsonDoc[i]["position"].GetString();
						SwitchPosition pos = Elements::getSwitchPosition(position);
						Game->cells[jsonDoc[i]["cell"]["x"].GetInt()][jsonDoc[i]["cell"]["y"].GetInt()].switches[jsonDoc[i]["point"].GetInt()]->setPosition(pos);
					}
				}
			}		
		}

		if (opts["remove"] == "") {

		}
	}

	void Cmd::train(map<string, string> opts, vector<string> args) {
		if (opts["add"] == "") {
			Field *game = Field::getInstance();
			rapidjson::Document jsonDoc;

			jsonDoc.Parse<kParseDefaultFlags>(opts["position"].c_str());
			int indent = jsonDoc["indent"].GetInt();
			int point = jsonDoc["point"].GetInt();
			int x = jsonDoc["cell"]["x"].GetInt();
			int y = jsonDoc["cell"]["y"].GetInt();
			TrackElement element = Elements::getTrackElement(jsonDoc["element"].GetString());
			TrainDirection direction = Elements::getDirection(opts["direction"]);

			Train train;
			train.id = std::stoi(opts["id"]);
			train.direction = direction;
			CarElement car;
			for (int i = 0; i < args.size(); i++) {
				car = Elements::getCarElement(args[i]);
				train.AddCar(car);
			}

			train.SetPosition({ &game->cells[x][y], point, indent, element });
			game->addTrain(train);
		}
	}

	void Cmd::semaphore(map<string, string> opts, vector<string> args)
	{
		if (opts["add"] == "") {
			rapidjson::Document jsonDoc;
			jsonDoc.Parse<kParseDefaultFlags>(opts["cell"].c_str());
			Field::getInstance()->cells[jsonDoc["x"].GetInt()][jsonDoc["y"].GetInt()].SetSemaphore(std::stoi(opts["point"]));
			Semaphore *semaphore = Field::getInstance()->cells[jsonDoc["x"].GetInt()][jsonDoc["y"].GetInt()].semaphores[std::stoi(opts["point"])];
			if (opts["position"] != "") {				
				SemaphorePosition pos = Elements::getSemaphorePosition(opts["position"]);
				semaphore->setPosition(pos);
			}

			if (opts["program"] != "") {				
				string data = "{\"data\":" + opts["program"] + "}";
				rapidjson::Document jsonDocProgram;
				jsonDocProgram.Parse<kParseDefaultFlags>(data.c_str());
				int program[24][12];
				for (SizeType h = 0; h < jsonDocProgram["data"].Size(); h++) {
					for (SizeType m = 0; m < jsonDocProgram["data"][h].Size(); m++) {
						program[h][m] = jsonDocProgram["data"][h][m].GetInt();
					}
				}
				semaphore->setProgram(program);
			}
		}

		if (opts["remove"] == "") {
			
		}
	}

	void Cmd::save(map<string, string> opts, vector<string> args)
	{
		string name = args[0];
		FileUtils *utils = FileUtils::getInstance();
		string path = utils->getWritablePath() + name + "/";
		utils->setWritablePath(path);
		if (!utils->isDirectoryExist(path)) {
			utils->createDirectory(path);
		}
		history.pop_back();
		pointer--;
		Field::getInstance()->save(name);
	}

	void Cmd::open(map<string, string> opts, vector<string> args)
	{
		string name = args[0];
		FileUtils *utils = FileUtils::getInstance();
		string path = utils->getWritablePath() + name + "/";
		utils->setWritablePath(path);
		if (utils->isDirectoryExist(path)) {
			Field::getInstance()->open(name);
			Cmd::clear();
		}		
	}

	void Cmd::railwayStation(map<string, string> opts, vector<string> args)
	{
		if (opts["add"] == "") {
			Field *game = Field::getInstance();
			rapidjson::Document jsonDoc;
			jsonDoc.Parse<kParseDefaultFlags>(opts["cell"].c_str());
			int x = jsonDoc["x"].GetInt();
			int y = jsonDoc["y"].GetInt();
			string id = opts["id"];
			int angle = 0;
			if (opts["angle"] != "") {
				int _angle = std::stoi(opts["angle"]);
				if (_angle == 0 || _angle == 90 || _angle == 180 || _angle == 270) {
					angle = _angle;
				}
			}

			RailwayStation station;
			station.id = std::stoi(opts["id"]);			
			//station.angle = angle;
			station.setPosition({ x, y }, angle);
			game->addRailwayStation(station);
		}
	}

	//undo methods
	void Cmd::_path(map<string, string> opts, vector<string> args) {
		if (opts["add"] == "") {
			Field *Game = Field::getInstance();
			rapidjson::Document jsonDoc;

			if (opts["switch"] != "") {
				jsonDoc.Parse<kParseDefaultFlags>(opts["switch"].c_str());
				for (int i = jsonDoc.Size() - 1; i >= 0; i--) {
					Game->cells[jsonDoc[i]["cell"]["x"].GetInt()][jsonDoc[i]["cell"]["y"].GetInt()].RemoveSwitch(jsonDoc[i]["point"].GetInt());
				}
			}

			if (opts["path"] != "") {
				jsonDoc.Parse<kParseDefaultFlags>(opts["path"].c_str());
				for (int i = jsonDoc.Size() - 1; i >= 0; i--) {
					if (jsonDoc[i].HasMember("cell")) {
						Game->cells[jsonDoc[i]["cell"]["x"].GetInt()][jsonDoc[i]["cell"]["y"].GetInt()].Disconnect(Elements::getTrackElement(jsonDoc[i]["element"].GetString()), jsonDoc[i]["point"].GetInt());
					}

					/*if (jsonDoc[i].HasMember("from")) {
						Game->cells[jsonDoc[i]["from"]["x"].GetInt()][jsonDoc[i]["from"]["y"].GetInt()].Disconnect(&Game->cells[jsonDoc[i]["to"]["x"].GetInt()][jsonDoc[i]["to"]["y"].GetInt()], jsonDoc[i]["point"].GetInt());
					}*/
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

	void Cmd::_train(map<string, string> opts, vector<string> args)
	{
		if (opts["add"] == "") {
			Field::getInstance()->removeTrain();
		}
	}

	void Cmd::_save(map<string, string> opts, vector<string> args)
	{
	}

	void Cmd::_open(map<string, string> opts, vector<string> args)
	{
	}

	void Cmd::_railwayStation(map<string, string> opts, vector<string> args)
	{
		if (opts["add"] == "") {			
			Field::getInstance()->removeRailwayStation();
		}
	}
}
