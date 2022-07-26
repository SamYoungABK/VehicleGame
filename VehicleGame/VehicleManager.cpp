#include "VehicleManager.h"
#include "car.h"
#include "boat.h"
#include "airplane.h"
#include <string>

using std::string;


string VehicleManager::GetDefaultName(string vehicleName)
{
	char number = '0' + m_vehicleList.size();

	return vehicleName + number;
}

VehicleManager::VEHICLE_MANAGER_ERROR VehicleManager::NewVehicle(
	Vehicle::VEHICLE_TYPE vehicleType,
	double fuelCapacity,
	double fuelConsumption)
{
	if (vehicleType == Vehicle::VEHICLE_TYPE::Undefined)
		return VEHICLE_MANAGER_ERROR::Undefined_Vehicle_Type;

	Vehicle* vehicleToAdd;

	switch (vehicleType) {
	case Vehicle::VEHICLE_TYPE::Car:
		vehicleToAdd = new Car();
		vehicleToAdd->m_name = GetDefaultName("Car");
		break;
	case Vehicle::VEHICLE_TYPE::Boat:
		vehicleToAdd = new Boat();
		vehicleToAdd->m_name = GetDefaultName("Car");
		break;
	case Vehicle::VEHICLE_TYPE::Airplane:
		vehicleToAdd = new Airplane();
		vehicleToAdd->m_name = GetDefaultName("Car");
		break;
	}

	m_vehicleList.push_back(vehicleToAdd);

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
		if (v->m_name == name) result.push_back(v);

	return result;
}

void VehicleManager::ListVehicles()
{
	if (m_vehicleList.size() == 0) return;

	printf("\nVehicle List: \n");
	for (Vehicle* v : m_vehicleList) v->Output();
}