#pragma once
#include "vehicle.h"

class Car :
	public Vehicle
{
public:
	Car(double fuelCapacity = 12, double fuelConsumption = 25.7) :
		Vehicle(fuelCapacity, fuelConsumption) {}
	
	void SetRandomEncounters() override;
};
