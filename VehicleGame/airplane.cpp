#include "Airplane.h"

Vehicle::VEHICLE_DRIVE_RESULT Airplane::drive(double distance)
{
	randomEncounters[0] = "A friendly bird flies by your window while you're flying and gives you some money!";
	randomEncounters[1] = "There's some money in the clouds! You don't question how that's possible.";
	randomEncounters[2] = "You find some money under your seat cushion!";

	if (distance < 0)
		return VEHICLE_DRIVE_RESULT::INVALID_DISTANCE;

	if ((distance * 1 / m_fuelConsumption) > m_fuel)
		return VEHICLE_DRIVE_RESULT::NOT_ENOUGH_FUEL;

	m_fuel -= distance * 1 / m_fuelConsumption;
	m_distanceDriven += distance;

	return VEHICLE_DRIVE_RESULT::SUCCESS;
}