#include "Car.h"
#include <iostream>

using std::cout;

Vehicle::VEHICLE_DRIVE_RESULT Car::drive(double distance)
{
	randomEncounters[0] = "You find some money along the side of the road on your trip!";
	randomEncounters[1] = "Some money falls out of the sky while you're driving!";
	randomEncounters[2] = "A friendly dog shows up while you're on your trip and gives you some money!";

	if (distance < 0)
		return VEHICLE_DRIVE_RESULT::INVALID_DISTANCE;

	if ((distance * 1 / m_fuelConsumption) > m_fuel)
		return VEHICLE_DRIVE_RESULT::NOT_ENOUGH_FUEL;

	m_fuel -= distance * 1 / m_fuelConsumption;
	m_distanceDriven += distance;

	return VEHICLE_DRIVE_RESULT::SUCCESS;
}