#pragma once
#include <string>
#include <random>

using std::string;

class Vehicle
{
public:
	enum class VEHICLE_TYPE
	{
		UNDEFINED,
		CAR,
		BOAT,
		PLANE
	};

	enum class VEHICLE_DRIVE_RESULT
	{
		NOT_ENOUGH_FUEL,
		INVALID_DISTANCE,
		SUCCESS,
	};

protected:

	double m_fuel = 0;
	double m_distanceDriven = 0;
	double m_fuelCapacity = 0;
	double m_fuelConsumption = 0;

public:
	string randomEncounters[3] = {
"",
"",
""
	};

	string m_name = "";

	Vehicle(double fuelCapacity = 0,
		double fuelConsumption = 0) :
		m_fuelCapacity{ fuelCapacity },
		m_fuelConsumption{ fuelConsumption } {}

	void output();
	bool addFuel(int amount);

	virtual VEHICLE_DRIVE_RESULT drive(double distance) = 0;
};
