#pragma once
#include "vehicle.h"
#include "car.h"
#include "boat.h"
#include "airplane.h"
#include "VehicleManager.h"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>



class Game
{
private:
	double m_money = 10000;
	double m_gasPrice = 2.00;

	VehicleManager m_vm;
	void NewVehicleMenu();
	bool SpendMoney(int cost);
	void RenameVehicleMenu();
	Vehicle* SelectVehicle();
	void FuelVehicleMenu();
	void DriveVehicleMenu();
	void RandomizeGasPrice();
	void HandleRandomEncounters(double distance, Vehicle* v);
	void ClearScreen();

public:
	void Loop();

};

