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
		Airplane
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
	string m_randomEncounters[3] = {
"",
"",
""
	};

	string m_name = "";

	Vehicle(double fuelCapacity = 0,
		double fuelConsumption = 0) :
		m_fuelCapacity(fuelCapacity),
		m_fuelConsumption(fuelConsumption) {};

	void Output();
	bool AddFuel(int amount);
	VEHICLE_DRIVE_RESULT Drive(double distance);
	virtual void SetRandomEncounters() = 0;

private:
	bool IsTooMuchFuel(int amount);
	bool NotEnoughFuel(double distance);
	float CalculateFuelPercentage();
};
