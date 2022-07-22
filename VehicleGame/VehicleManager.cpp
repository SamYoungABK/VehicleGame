#include "VehicleManager.h"
#include "car.h"
#include "boat.h"
#include "airplane.h"
#include <string>

using std::string;


VehicleManager::VEHICLE_MANAGER_ERROR VehicleManager::newVehicle(
	Vehicle::VEHICLE_TYPE vehicleType,
	double fuelCapacity,
	double fuelConsumption)
{
	if (vehicleType == Vehicle::VEHICLE_TYPE::UNDEFINED)
		return VEHICLE_MANAGER_ERROR::UNDEFINED_VEHICLE_TYPE;

	if (vehicleType == Vehicle::VEHICLE_TYPE::CAR)
	{
		Car* carToAdd = new Car();
		carToAdd->m_name = (string)"Car" + (char)('0' + m_vehicleList.size());

		m_vehicleList.push_back(carToAdd);
	}
	else if (vehicleType == Vehicle::VEHICLE_TYPE::BOAT)
	{
		Boat* boatToAdd = new Boat();
		boatToAdd->m_name = (string)"Boat" + (char)('0' + m_vehicleList.size());

		m_vehicleList.push_back(boatToAdd);
	}
	else if (vehicleType == Vehicle::VEHICLE_TYPE::PLANE)
	{
		Airplane* planeToAdd = new Airplane();
		planeToAdd->m_name = (string)"Airplane" + (char)('0' + m_vehicleList.size());

		m_vehicleList.push_back(planeToAdd);
	}

	return VEHICLE_MANAGER_ERROR::SUCCESS;
}

Vehicle* VehicleManager::getVehicle(int index)
{
	return m_vehicleList[index];
}

int VehicleManager::getVehicleCount()
{
	return m_vehicleList.size();
}

vector<Vehicle*> VehicleManager::getVehicle(string name)
{
	vector<Vehicle*> result;

	for (Vehicle* v : m_vehicleList)
	{
		if (v->m_name == name)
			result.push_back(v);
	}

	return result;
}

void VehicleManager::listVehicles()
{
	if (m_vehicleList.size() == 0)
		return;

	printf("\nVehicle List: \n");
	for (Vehicle* v : m_vehicleList)
	{
		v->output();
	}
}