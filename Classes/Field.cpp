#include "Cell.h"
#include "Field.h"
#include "Cmd.h"
#include "MapLayer.h"

namespace GameObjects {

	Field *Field::p_instance = 0;

	Field *Field::getInstance() {
		if (p_instance == 0) {
			p_instance = new Field;
		}
		return p_instance;
	}

	Field::Field()
	{	
		for (int x = 0; x < SizeX; x++) {
			for (int y = 0; y < SizeY; y++) {
				cells[x][y].x = x;
				cells[x][y].y = y;				
			}
		}
	}

	Field::~Field()
	{
	}

	void Field::addTrain(Train train)
	{
		this->trains.push_back(train);		
	}

	void Field::removeTrain()
	{		
		this->trains.back().remove();
		this->trains.pop_back();
	}

	void Field::addRailwayStation(RailwayStation station)
	{
		this->stations.push_back(station);
	}

	void Field::removeRailwayStation()
	{
		this->stations.back().remove();
		this->stations.pop_back();
	}

	void Field::save(string name)
	{
		ValueMap settings;

		FileUtils *utils = FileUtils::getInstance();
		string path = utils->getWritablePath();
		
		int blocks = 0;
		if (utils->isFileExist(path + "settings.dat")) {
			settings = utils->getValueMapFromFile(path + "settings.dat");
			blocks = settings["blocks"].asInt();
		} 
		
		Cmd *inst = Cmd::getInstance();

		int c = 0, i = 0;
		int blockSize = 100 * 1024;
		while (i < inst->pointer) {
			string content = "";
			while (content.size() < blockSize && i < inst->pointer) {
				content += (content.size() == 0 ? "" : "\n") + inst->encode(&inst->history[i]);
				i++;
			}
			utils->writeStringToFile(content, path + "commands_" + std::to_string(blocks) + ".dat");
			blocks++;
		}

		settings["blocks"] = blocks;
		utils->writeValueMapToFile(settings, path + "settings.set");

		//save backround
		MapLayer *map = (MapLayer*)(mapLayer);
		map->renderMap();
	}

	void Field::open(string name)
	{
		constuctionMode = ConstructOpen;
		MapLayer *map = (MapLayer*)(mapLayer);
		map->showMap();

		FileUtils *utils = FileUtils::getInstance();
		string path = utils->getWritablePath();

		ValueMap settings = utils->getValueMapFromFile(path + "settings.set");
		int blocks = settings["blocks"].asInt();

		for (int i = 0; i < blocks; i++) {
			string commands = utils->getStringFromFile(path + "commands_" + std::to_string(i) + ".dat");
			vector<string> items = Helper::split(commands, '\n');
			vector<string>::iterator c;
			for (c = items.begin(); c != items.end(); ++c) {
				Cmd::Exec(*c);
			}			
		}
		constuctionMode = ConstructNone;
	}
}
