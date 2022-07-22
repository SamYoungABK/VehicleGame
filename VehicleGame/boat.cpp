#include "Boat.h"
#include <iostream>

using std::cout;

Vehicle::VEHICLE_DRIVE_RESULT Boat::drive(double distance)
{
	randomEncounters[0] = "A fish jumps out of the water and gives you some undersea treasure!";
	randomEncounters[1] = "Some money falls out of the sky and lands on your boat!";
	randomEncounters[2] = "A cute baby duck has found it's way onto your boat! It gives you some money!";



	if (distance < 0)
		return VEHICLE_DRIVE_RESULT::INVALID_DISTANCE;

	if ((distance * 1 / m_fuelConsumption) > m_fuel)
		return VEHICLE_DRIVE_RESULT::NOT_ENOUGH_FUEL;

	m_fuel -= distance * 1 / m_fuelConsumption;
	m_distanceDriven += distance;

	return VEHICLE_DRIVE_RESULT::SUCCESS;
}