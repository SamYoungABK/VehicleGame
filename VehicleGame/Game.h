#pragma once
#include "vehicle.h"
#include "car.h"
#include "boat.h"
#include "airplane.h"
#include "VehicleManager.h"

#include <iostream>
#include <string>



class Game
{
private:
	double m_money = 10000;
	double m_gasPrice = 2.00;

	VehicleManager m_vm;
	void newVehicleMenu();
	bool spendMoney(int cost);
	void renameVehicleMenu();
	Vehicle* selectVehicle();
	void fuelVehicleMenu();
	void driveVehicleMenu();
	void randomizeGasPrice();
	void handleRandomEncounters(double distance, Vehicle* v);

public:
	void loop();

};

