#include "Vehicle.h"

void Vehicle::Output()
{
	double fuelPercentage =
		m_fuelCapacity != 0 ? m_fuel / m_fuelCapacity * 100 : 0;

	printf("\n-------------------------------------\n");
	printf("Name: %s\n", m_name.c_str());
	printf("Distance traveled: %g miles\n", m_distanceDriven);
	printf("Fuel Efficiency: %g miles/g\n", m_fuelConsumption);
	printf("Fuel: %g gal/%g gal   %g%% full\n", m_fuel, m_fuelCapacity, fuelPercentage);
	printf("-------------------------------------\n\n");
}

Vehicle::VEHICLE_DRIVE_RESULT Vehicle::Drive(double distance)
{
	if (distance < 0)
		return VEHICLE_DRIVE_RESULT::Negative_Distance;

	if (NotEnoughFuel(distance))
		return VEHICLE_DRIVE_RESULT::Not_Enough_Fuel;

	// convert m_fuelConsumption from miles/gal to gallons/mi
	double gallonsPerMile = 1 / m_fuelConsumption;

	m_fuel -= distance * gallonsPerMile;
	m_distanceDriven += distance;

	return VEHICLE_DRIVE_RESULT::Success;
}

bool Vehicle::NotEnoughFuel(double distance)
{
	return (distance * 1 / m_fuelConsumption) > m_fuel;
}

bool Vehicle::AddFuel(int amount)
{
	if ((m_fuel + amount) > m_fuelCapacity)
		return false;

	m_fuel += amount;

	return true;
}