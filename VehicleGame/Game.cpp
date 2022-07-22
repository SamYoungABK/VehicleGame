#include "Game.h"
#include <iostream>
#include <random>
#include <ctime>
#include <string>

using std::string;

void Game::loop()
{
	bool running = true;
	char userInput;

	while (running)
	{
		printf("\n---------------------------------------------------\n");
		printf("\nMoney: $%4.2f\n", m_money);
		printf("\nFuel Price: $%4.2f/gal\n", m_gasPrice);
		printf("\n---------------------------------------------------\n");
		m_vm.listVehicles();
		printf("\nOptions:\n");
		printf("  1. Purchase Vehicle\n");
		printf("  2. Rename Vehicle\n");
		printf("  3. Purchase Fuel For Vehicle\n");
		printf("  4. Drive Vehicle\n");
		printf("(1,2,3,4): ");
		std::cin >> userInput;
		switch (userInput) {
		case '1':
			newVehicleMenu();
			break;
		case '2':
			renameVehicleMenu();
			break;
		case '3':
			fuelVehicleMenu();
			break;
		case '4':
			driveVehicleMenu();
			break;
		default:
			printf("Invalid option.\n");
		}
	}
}

void Game::renameVehicleMenu()
{
	if (m_vm.getVehicleCount() <= 0)
	{
		printf("\nERROR: Can't rename vehicles that haven't been created yet!\n");
		return;
	}

	Vehicle* selectedVehicle = selectVehicle();
	if (selectedVehicle == nullptr) return;

	printf("What would you like to rename the vehicle to?\n");
	printf("(string): ");
	string newName;
	string oldName = selectedVehicle->m_name;
	std::cin >> newName;
	selectedVehicle->m_name = newName;

	printf("Renamed %s to %s.\n", oldName.c_str(), newName.c_str());
	return;
}

Vehicle* Game::selectVehicle()
{
	int vehicleIndex;
	printf("\n\nType the position of Vehicle in the list:\n");
	m_vm.listVehicles();
	printf("(0-%d): ", m_vm.getVehicleCount() - 1);

	std::cin >> vehicleIndex;

	if (vehicleIndex < 0 || vehicleIndex >= m_vm.getVehicleCount())
	{
		printf("\nERROR: Vehicle index out of range.\n");
		return nullptr;
	}

	printf("Selected: \n");
	m_vm.getVehicle(vehicleIndex)->output();
	return m_vm.getVehicle(vehicleIndex);
}

void Game::newVehicleMenu()
{
	char userInput;
	printf("\n\nSelect Vehicle Type:\n");
	printf("  1. Car $1000\n");
	printf("  2. Boat $2000\n");
	printf("  3. Plane $5000\n");
	printf("(1,2,3): ");
	std::cin >> userInput;

	switch (userInput)
	{
	case '1':
		if (!spendMoney(1000)) return;
		m_vm.newVehicle(Vehicle::VEHICLE_TYPE::CAR);
		break;
	case '2':
		if (!spendMoney(2000)) return;
		m_vm.newVehicle(Vehicle::VEHICLE_TYPE::BOAT);
		break;
	case '3':
		if (!spendMoney(5000)) return;
		m_vm.newVehicle(Vehicle::VEHICLE_TYPE::PLANE);
		break;
	}
}

bool Game::spendMoney(int cost)
{
	if (m_money < cost)
	{
		printf("Not enough money!! You're short by $%4.2f\n", cost - m_money);
		return false;
	}
	m_money -= cost;
	printf("Spent %d\n", cost);
	return true;
}

void Game::fuelVehicleMenu()
{
	if (m_vm.getVehicleCount() <= 0)
	{
		printf("\nERROR: Can't add fuel to vehicles that haven't been created yet!\n");
		return;
	}

	Vehicle* selectedVehicle = selectVehicle();
	if (selectedVehicle == nullptr) return;

	printf("How much fuel would you like to buy? Gas Price: %4.2f\n", m_gasPrice);
	printf("(>=0): ");
	double fuelInput;
	std::cin >> fuelInput;

	if (fuelInput < 0)
	{
		printf("\nERROR: Can't add negative fuel.\n");
		return;
	}

	if (!spendMoney(fuelInput * m_gasPrice)) return;

	selectedVehicle->addFuel(fuelInput);
	printf("Added %g fuel to vehicle named %s.\n",
		fuelInput,
		selectedVehicle->m_name.c_str());

	return;
}

void Game::driveVehicleMenu()
{
	if (m_vm.getVehicleCount() <= 0)
	{
		printf("\nERROR: Can't drive vehicles that haven't been created yet!\n");
		return;
	}

	Vehicle* selectedVehicle = selectVehicle();
	if (selectedVehicle == nullptr) return;

	printf("How far would you like to drive?\n");
	printf("(>=0): ");
	double distance;
	std::cin >> distance;

	Vehicle::VEHICLE_DRIVE_RESULT driveResult =
		selectedVehicle->drive(distance);

	switch (driveResult)
	{
	case Vehicle::VEHICLE_DRIVE_RESULT::NOT_ENOUGH_FUEL:
		printf("Not enough fuel!");
		return;
	case Vehicle::VEHICLE_DRIVE_RESULT::INVALID_DISTANCE:
		printf("Invlaid distance!");
		return;
	}

	printf("Drove %s for %g miles.\n",
		selectedVehicle->m_name.c_str(), distance);

	randomizeGasPrice();
	handleRandomEncounters(distance, selectedVehicle);

	return;
}

void Game::randomizeGasPrice()
{
	std::srand(std::time(nullptr));
	m_gasPrice = (double)(std::rand() % 300) / 100 + 2.00;
}

void Game::handleRandomEncounters(double distance, Vehicle* v)
{
	std::srand(std::time(nullptr));
	int numEncounters = distance / 100;

	(std::rand() % 2 == 1) ? numEncounters++ : 0;

	for (int i = 0; i < numEncounters; ++i)
	{
		int randomEncounterIndex = std::rand() % 3;

		string encounterText = v->randomEncounters[randomEncounterIndex];
		double moneyEarned = (double)(distance * 10.0) + (double)(std::rand() % (int)(distance * 10));

		printf("%s You gain: $%.2f\n", encounterText.c_str(), moneyEarned);

		m_money += moneyEarned;
	}


}