#pragma once
#include <string>
#include <random>

using std::string;

class Vehicle
{
public:
	enum class VEHICLE_TYPE
	{
		Undefined,
		Car,
		Boat,
		Plane
	};

	enum class VEHICLE_DRIVE_RESULT
	{
		Not_Enough_Fuel,
		Negative_Distance,
		Success,
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

	bool NotEnoughFuel(double distance);
	VEHICLE_DRIVE_RESULT Drive(double distance);
	virtual void SetRandomEncounters() = 0;
};
