#pragma once
#include "vehicle.h"

class Boat :
	public Vehicle
{
public:
	Boat(double fuelCapacity = 40, double fuelConsumption = 5) :
		Vehicle(fuelCapacity, fuelConsumption) {}

	VEHICLE_DRIVE_RESULT drive(double distance) override;
};
