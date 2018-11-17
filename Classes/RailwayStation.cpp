#include "RailwayStation.h"
#include "Field.h"
#include "Cmd.h"

namespace GameObjects {
	
	RailwayStation::RailwayStation()
	{
		Field *Game = Field::getInstance();
		int d = 10 * Game->scale;

		if (Game->constuctionMode != ConstructionMode::ConstructOpen) {
			this->resource = Elements::GetObjectElement(ObjectsElement::RailwayStaton);
			Game->mapLayer->addChild(this->resource, ZIndexBuildings);
			Cmd *inst = Cmd::getInstance();
			inst->history[inst->pointer - 1].elements.push_back({ this->resource , ZIndexBackgroundBuildings });
		}
	}

	RailwayStation::~RailwayStation()
	{
	}

	void RailwayStation::setPosition(MapPoint position, int angle)
	{
		Field *Game = Field::getInstance();
		int d = 10 * Game->scale;

		this->position = position;
		this->angle = angle;

		if (this->angle == 0) {
			if (Game->constuctionMode != ConstructionMode::ConstructOpen) {
				this->resource->setPosition(this->position.x * d + 2.0 * d, this->position.y * d + 5.0 * d);
				this->resource->setRotation(180);
			}
			for (int i = 0; i < 10; i++) {
				Game->cells[position.x + 4][position.y + i].Connect(TrackElement::Vertical, 2);
				Game->cells[position.x + 5][position.y + i].Connect(TrackElement::Vertical, 2);
			}
			Game->cells[position.x + 4][position.y].SetSemaphore(2);			
			Game->cells[position.x + 5][position.y].SetSemaphore(2);
			Game->cells[position.x + 4][position.y + 10].SetSemaphore(6);
			Game->cells[position.x + 5][position.y + 10].SetSemaphore(6);

			for (int x = 4; x < 6; x++) {
				for (int y = 0; y < 10; y++) {
					Game->cells[position.x + x][position.y + y].accessParam = Game->cells[position.x + x][position.y + y].accessParam | 0b10;
					//debug
					//Cell cl = Game->cells[position.x + x][position.y + y];
					//cl.writeDebugNode(cl.x, cl.y, cl.access, cl.accessParam, Color4F::GREEN);
				}
			}

			for (int x = -1; x < 5; x++) {
				for (int y = 2; y < 8; y++) {
					Game->cells[position.x + x][position.y + y].accessParam = Game->cells[position.x + x][position.y + y].accessParam | 0b10;
					//debug
					//Cell cl = Game->cells[position.x + x][position.y + y];
					//cl.writeDebugNode(cl.x, cl.y, cl.access, cl.accessParam, Color4F::GREEN);
				}
			}
		}

		if (this->angle == 90) {
			if (Game->constuctionMode != ConstructionMode::ConstructOpen) {
				this->resource->setPosition(this->position.x * d + 5.0 * d, this->position.y * d + 3.0 * d);
				this->resource->setRotation(90);
			}

			for (int i = 0; i < 10; i++) {
				Game->cells[position.x + i][position.y + 5].Connect(TrackElement::Horizontal, 0);
				Game->cells[position.x + i][position.y + 6].Connect(TrackElement::Horizontal, 0);
			}
			Game->cells[position.x][position.y + 5].SetSemaphore(0);
			Game->cells[position.x][position.y + 6].SetSemaphore(0);
			Game->cells[position.x + 10][position.y + 5].SetSemaphore(4);
			Game->cells[position.x + 10][position.y + 6].SetSemaphore(4);
			
			for (int x = 0; x < 10; x++) {
				for (int y = 5; y < 7; y++) {
					Game->cells[position.x + x][position.y + y].accessParam = Game->cells[position.x + x][position.y + y].accessParam | 0b10;
					//debug
					//Cell cl = Game->cells[position.x + x][position.y + y];
					//cl.writeDebugNode(cl.x, cl.y, cl.access, cl.accessParam, Color4F::GREEN);
				}
			}

			for (int x = 2; x < 8; x++) {
				for (int y = 0; y < 5; y++) {
					Game->cells[position.x + x][position.y + y].accessParam = Game->cells[position.x + x][position.y + y].accessParam | 0b10;
					//debug
					//Cell cl = Game->cells[position.x + x][position.y + y];
					//cl.writeDebugNode(cl.x, cl.y, cl.access, cl.accessParam, Color4F::GREEN);
				}
			}
		}

		if (this->angle == 180) {
			if (Game->constuctionMode != ConstructionMode::ConstructOpen) {
				this->resource->setPosition(this->position.x * d + 3.0 * d, this->position.y * d + 5.0 * d);
			}
			for (int i = 0; i < 10; i++) {				
				Game->cells[position.x][position.y + i].Connect(TrackElement::Vertical, 2);
				Game->cells[position.x + 1][position.y + i].Connect(TrackElement::Vertical, 2);
			}
			Game->cells[position.x][position.y].SetSemaphore(2);
			Game->cells[position.x + 1][position.y].SetSemaphore(2);
			Game->cells[position.x][position.y + 10].SetSemaphore(6);
			Game->cells[position.x + 1][position.y + 10].SetSemaphore(6);

			for (int x = 0; x < 2; x++) {
				for (int y = 0; y < 10; y++) {
					Game->cells[position.x + x][position.y + y].accessParam = Game->cells[position.x + x][position.y + y].accessParam | 0b10;
					//debug
					//Cell cl = Game->cells[position.x + x][position.y + y];
					//cl.writeDebugNode(cl.x, cl.y, cl.access, cl.accessParam, Color4F::GREEN);
				}
			}

			for (int x = 2; x < 7; x++) {
				for (int y = 2; y < 8; y++) {
					Game->cells[position.x + x][position.y + y].accessParam = Game->cells[position.x + x][position.y + y].accessParam | 0b10;
					//debug
					//Cell cl = Game->cells[position.x + x][position.y + y];
					//cl.writeDebugNode(cl.x, cl.y, cl.access, cl.accessParam, Color4F::GREEN);
				}
			}
		}

		if (this->angle == 270) {
			if (Game->constuctionMode != ConstructionMode::ConstructOpen) {
				this->resource->setPosition(this->position.x * d + 5.0 * d, this->position.y * d + 4.0 * d);
				this->resource->setRotation(270);
			}
			for (int i = 0; i < 10; i++) {
				Game->cells[position.x + i][position.y + 1].Connect(TrackElement::Horizontal, 0);
				Game->cells[position.x + i][position.y + 2].Connect(TrackElement::Horizontal, 0);
			}
			Game->cells[position.x][position.y + 1].SetSemaphore(0);
			Game->cells[position.x][position.y + 2].SetSemaphore(0);
			Game->cells[position.x + 10][position.y + 1].SetSemaphore(4);
			Game->cells[position.x + 10][position.y + 2].SetSemaphore(4);

			for (int x = 0; x < 10; x++) {
				for (int y = 1; y < 3; y++) {
					Game->cells[position.x + x][position.y + y].accessParam = Game->cells[position.x + x][position.y + y].accessParam | 0b10;
					//debug
					//Cell cl = Game->cells[position.x + x][position.y + y];
					//cl.writeDebugNode(cl.x, cl.y, cl.access, cl.accessParam, Color4F::GREEN);
				}
			}

			for (int x = 2; x < 8; x++) {
				for (int y = 3; y < 7; y++) {
					Game->cells[position.x + x][position.y + y].accessParam = Game->cells[position.x + x][position.y + y].accessParam | 0b10;
					//debug
					//Cell cl = Game->cells[position.x + x][position.y + y];
					//cl.writeDebugNode(cl.x, cl.y, cl.access, cl.accessParam, Color4F::GREEN);
				}
			}
		}
	}

	void RailwayStation::remove()
	{
		Field *Game = Field::getInstance();
		Game->mapLayer->removeChild(this->resource);
				
		if (this->angle == 0) {			
			for (int i = 0; i < 10; i++) {
				Game->cells[position.x + 4][position.y + i].Disconnect(TrackElement::Vertical, 2);
				Game->cells[position.x + 5][position.y + i].Disconnect(TrackElement::Vertical, 2);
			}
			Game->cells[position.x + 4][position.y].RemoveSemaphore(2);
			Game->cells[position.x + 5][position.y].RemoveSemaphore(2);
			Game->cells[position.x + 4][position.y + 10].RemoveSemaphore(6);
			Game->cells[position.x + 5][position.y + 10].RemoveSemaphore(6);
		}

		if (this->angle == 90) {
			for (int i = 0; i < 10; i++) {
				Game->cells[position.x + i][position.y + 5].Disconnect(TrackElement::Horizontal, 0);
				Game->cells[position.x + i][position.y + 6].Disconnect(TrackElement::Horizontal, 0);
			}
			Game->cells[position.x][position.y + 5].RemoveSemaphore(0);
			Game->cells[position.x][position.y + 6].RemoveSemaphore(0);
			Game->cells[position.x + 10][position.y + 5].RemoveSemaphore(4);
			Game->cells[position.x + 10][position.y + 6].RemoveSemaphore(4);
		}

		if (this->angle == 180) {
			for (int i = 0; i < 10; i++) {
				Game->cells[position.x][position.y + i].Disconnect(TrackElement::Vertical, 2);
				Game->cells[position.x + 1][position.y + i].Disconnect(TrackElement::Vertical, 2);
			}
			Game->cells[position.x][position.y].RemoveSemaphore(2);
			Game->cells[position.x + 1][position.y].RemoveSemaphore(2);
			Game->cells[position.x][position.y + 10].RemoveSemaphore(6);
			Game->cells[position.x + 1][position.y + 10].RemoveSemaphore(6);
		}

		if (this->angle == 270) {
			for (int i = 0; i < 10; i++) {
				Game->cells[position.x + i][position.y + 1].Disconnect(TrackElement::Horizontal, 0);
				Game->cells[position.x + i][position.y + 2].Disconnect(TrackElement::Horizontal, 0);
			}
			Game->cells[position.x][position.y + 1].RemoveSemaphore(0);
			Game->cells[position.x][position.y + 2].RemoveSemaphore(0);
			Game->cells[position.x + 10][position.y + 1].RemoveSemaphore(4);
			Game->cells[position.x + 10][position.y + 2].RemoveSemaphore(4);
		}
	}
}
