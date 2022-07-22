#pragma once
#include "vehicle.h"
#include <vector>

using std::vector;


class VehicleManager
{
public:
	enum class VEHICLE_MANAGER_ERROR
	{
		SUCCESS,
		UNDEFINED_VEHICLE_TYPE,
	};

private:
	vector<Vehicle*> m_vehicleList;

public:
	VEHICLE_MANAGER_ERROR newVehicle(
		Vehicle::VEHICLE_TYPE vehicleType = Vehicle::VEHICLE_TYPE::UNDEFINED,
		double fuelCapacity = 0,
		double fuelConsumption = 0);

	int getVehicleCount();
	Vehicle* getVehicle(int index);
	vector<Vehicle*> getVehicle(string name);

	void listVehicles();
};

