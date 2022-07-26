#include "Vehicle.h"

void Vehicle::Output()
{
	float fuelPercentage = CalculateFuelPercentage();

	printf("\n-------------------------------------\n");
	printf("Name: %s\n", m_name.c_str());
	printf("Distance traveled: %g miles\n", m_distanceDriven);
	printf("Fuel Efficiency: %g miles/gal\n", m_fuelConsumption);
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
	double fuelConsumed = distance * gallonsPerMile;

	m_fuel -= fuelConsumed;
	m_distanceDriven += distance;

	return VEHICLE_DRIVE_RESULT::Success;
}

bool Vehicle::NotEnoughFuel(double distance)
{
	return (distance * 1 / m_fuelConsumption) > m_fuel;
}

float Vehicle::CalculateFuelPercentage()
{
	if (m_fuelCapacity == 0 || m_fuel == 0) return 0.00;

	float fuelPercentage = m_fuel / m_fuelCapacity * 100;

	return fuelPercentage;
}

bool Vehicle::IsTooMuchFuel(int amount)
{
	return (m_fuel + amount) > m_fuelCapacity;
}


bool Vehicle::AddFuel(int amount)
{
	if (IsTooMuchFuel(amount)) return false;

	m_fuel += amount;

	return true;
}

