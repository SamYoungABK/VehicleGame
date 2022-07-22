#include "Vehicle.h"

void Vehicle::output()
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

bool Vehicle::addFuel(int amount)
{
	if ((m_fuel + amount) > m_fuelCapacity)
		return false;

	m_fuel += amount;

	return true;
}