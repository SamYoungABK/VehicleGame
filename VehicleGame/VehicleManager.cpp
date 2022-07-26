#include "VehicleManager.h"
#include "car.h"
#include "boat.h"
#include "airplane.h"
#include <string>

using std::string;


VehicleManager::VEHICLE_MANAGER_ERROR VehicleManager::NewVehicle(
	Vehicle::VEHICLE_TYPE vehicleType,
	double fuelCapacity,
	double fuelConsumption)
{
	if (vehicleType == Vehicle::VEHICLE_TYPE::Undefined)
		return VEHICLE_MANAGER_ERROR::Undefined_Vehicle_Type;

	if (vehicleType == Vehicle::VEHICLE_TYPE::Car)
	{
		Car* carToAdd = new Car();
		carToAdd->m_name = (string)"Car" + (char)('0' + m_vehicleList.size());

		m_vehicleList.push_back(carToAdd);
	}
	else if (vehicleType == Vehicle::VEHICLE_TYPE::Boat)
	{
		Boat* boatToAdd = new Boat();
		boatToAdd->m_name = (string)"Boat" + (char)('0' + m_vehicleList.size());

		m_vehicleList.push_back(boatToAdd);
	}
	else if (vehicleType == Vehicle::VEHICLE_TYPE::Plane)
	{
		Airplane* planeToAdd = new Airplane();
		planeToAdd->m_name = (string)"Airplane" + (char)('0' + m_vehicleList.size());

		m_vehicleList.push_back(planeToAdd);
	}

	return VEHICLE_MANAGER_ERROR::Success;
}

Vehicle* VehicleManager::GetVehicle(int index)
{
	return m_vehicleList[index];
}

int VehicleManager::GetVehicleCount()
{
	return m_vehicleList.size();
}

vector<Vehicle*> VehicleManager::GetVehicle(string name)
{
	vector<Vehicle*> result;

	for (Vehicle* v : m_vehicleList)
	{
		if (v->m_name == name)
			result.push_back(v);
	}

	return result;
}

void VehicleManager::ListVehicles()
{
	if (m_vehicleList.size() == 0)
		return;

	printf("\nVehicle List: \n");
	for (Vehicle* v : m_vehicleList)
	{
		v->Output();
	}
}