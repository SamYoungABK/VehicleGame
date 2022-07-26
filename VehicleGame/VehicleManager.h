#pragma once
#include "vehicle.h"
#include <vector>
#include <string>

using std::vector;
using std::string;


class VehicleManager
{
public:
	enum class VEHICLE_MANAGER_ERROR
	{
		Success,
		Undefined_Vehicle_Type,
	};

private:
	vector<Vehicle*> m_vehicleList;
	string GetDefaultName(string VehicleName);

public:
	VEHICLE_MANAGER_ERROR NewVehicle(
		Vehicle::VEHICLE_TYPE vehicleType = Vehicle::VEHICLE_TYPE::Undefined,
		double fuelCapacity = 0,
		double fuelConsumption = 0);

	int GetVehicleCount();
	Vehicle* GetVehicle(int index);
	vector<Vehicle*> GetVehicle(string name);

	void ListVehicles();
};

