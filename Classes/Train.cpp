#include "Train.h"
#include "Car.h"
#include "Path.h"

namespace GameObjects {

	Train::Train()
	{
	}

	Train::~Train()
	{
	}

	void Train::AddCar(Car *car)
	{
		this->cars.insert(cars.end(), *car);
	}

	void Train::Init()
	{
		/*
		if self.Cars ~= nil and self.SpeedProgram.MaxSpeed > 0 and self.Cars[1].Move == nil then    
        local i           
        for i = 1, self.SpeedProgram.Length do
            self.SpeedProgram.Speeds[i] = {}
        end
        self.SpeedProgram.Pointer = 1 
        self.SpeedProgram.Speeds[self.SpeedProgram.Pointer].Speed = 0            
        self:SpeedProgramReset()        
        self:GetMove(self:GetSpeed())
    end

		*/
	}

	void Train::Move()
	{
		TrackPosition pos = Path::GetPosition(this->position, -5);
		this->position = pos;
		for (int i = 0; i < cars.size(); i++) {
			pos = cars[i].SetPosition(pos);
		}
	}

	void Train::SetPosition(TrackPosition position)
	{
		this->position = position;
		TrackPosition pos = position;
		for (int i = 0; i < cars.size(); i++) {
			pos = cars[i].SetPosition(pos);
			cars[i].resource->setVisible(true);
		}
	}
	
	void Train::GetMove(int move)
	{
	}

	void Train::RunMove()
	{
	}

	int Train::GetSpeed()
	{
		return 0;
	}

	void Train::SpeedProgramReset()
	{
	}
}
