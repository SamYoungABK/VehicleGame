#pragma once
#include "vehicle.h"

class Airplane :
	public Vehicle
{
public:
	Airplane(double fuelCapacity = 1000, double fuelConsumption = 100) :
		Vehicle(fuelCapacity, fuelConsumption) {}

	VEHICLE_DRIVE_RESULT drive(double distance) override;
};
