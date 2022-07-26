#include "Game.h"

using std::string;
using namespace std::chrono;
using namespace std::this_thread;

void Game::Init()
{
	// seed the random number generator
	std::srand(std::time(nullptr));
	PrintTitleScreen();
	ClearScreen();
	Loop();
}

void Game::Loop()
{
	bool running = true;
	char userInput;

	while (running)
	{
		PrintMainMenu();
		std::cin >> userInput;

		switch (userInput) {
		case '1':
			NewVehicleMenu();
			break;
		case '2':
			RenameVehicleMenu();
			break;
		case '3':
			FuelVehicleMenu();
			break;
		case '4':
			DriveVehicleMenu();
			break;
		default:
			printf("Invalid option.\n");
		}
		sleep_for(seconds(3));
	}
}

void Game::PrintTitleScreen() {
	printf(" __      __  _     _      _       _____                      \n");
	printf(" \\ \\    / / | |   (_)    | |     / ____|                     \n");
	printf("  \\ \\  / ___| |__  _  ___| | ___| |  __  __ _ _ __ ___   ___ \n");
	printf("   \\ \\/ / _ | '_ \\| |/ __| |/ _ | | |_ |/ _` | '_ ` _ \\ / _ \\ \n");
	printf("    \\  |  __| | | | | (__| |  __| |__| | (_| | | | | | |  __/\n");
	printf("     \\/ \\___|_| |_|_|\\___|_|\\___|\\_____|\\__,_|_| |_| |_|\\___|\n\n");
	printf(" - A Game With No Real Objective Outside of Buying Vehicles And Amassing Wealth\n");
	printf("   from some rather silly random events.\n\n\n");
	printf("Game starting in 5...\n");
	sleep_for(seconds(3));
	printf("4...\n");
	sleep_for(seconds(1));
	printf("3...\n");
	sleep_for(seconds(1));
	printf("2...\n");
	sleep_for(seconds(1));
	printf("1!\n");
	sleep_for(seconds(1));
}

void Game::PrintScore()
{
	printf("\n---------------------------------------------------\n");
	printf("\nMoney: $%4.2f\n", m_money);
	printf("\nFuel Price: $%4.2f/gal\n", m_gasPrice);
	printf("\n---------------------------------------------------\n");

}

void Game::PrintMainMenu()
{
	ClearScreen();
	PrintScore();
	m_vm.ListVehicles();
	printf("\nOptions:\n");
	printf("  1. Purchase Vehicle\n");
	printf("  2. Rename Vehicle\n");
	printf("  3. Purchase Fuel For Vehicle\n");
	printf("  4. Drive Vehicle\n");
	printf("(1,2,3,4): ");
}


void Game::RenameVehicleMenu()
{
	if (m_vm.GetVehicleCount() <= 0)
	{
		printf("\nERROR: Can't rename vehicles that haven't been created yet!\n");
		return;
	}

	Vehicle* selectedVehicle = SelectVehicle();
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

Vehicle* Game::SelectVehicle()
{
	ClearScreen();
	int vehicleIndex;
	printf("\n\nType the position of Vehicle in the list:\n");
	m_vm.ListVehicles();
	printf("(0-%d): ", m_vm.GetVehicleCount() - 1);

	std::cin >> vehicleIndex;

	if (vehicleIndex < 0 || vehicleIndex >= m_vm.GetVehicleCount())
	{
		printf("\nERROR: Vehicle index out of range.\n");
		return nullptr;
	}

	printf("Selected: \n");
	m_vm.GetVehicle(vehicleIndex)->Output();
	ClearScreen();
	return m_vm.GetVehicle(vehicleIndex);
}

void Game::NewVehicleMenu()
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
		if (!SpendMoney(1000)) return;
		printf("Purchased car!");
		m_vm.NewVehicle(Vehicle::VEHICLE_TYPE::Car);
		break;
	case '2':
		if (!SpendMoney(2000)) return;
		printf("Purchased boat!");
		m_vm.NewVehicle(Vehicle::VEHICLE_TYPE::Boat);
		break;
	case '3':
		if (!SpendMoney(5000)) return;
		printf("Purchased airplane!");
		m_vm.NewVehicle(Vehicle::VEHICLE_TYPE::Airplane);
		break;
	}
}

bool Game::SpendMoney(int cost)
{
	if (m_money < cost)
	{
		printf("\nNot enough money!! You're short by $%4.2f\n", cost - m_money);
		return false;
	}
	m_money -= cost;
	printf("\nSpent $%d\n", cost);
	return true;
}

void Game::FuelVehicleMenu()
{
	if (m_vm.GetVehicleCount() <= 0)
	{
		printf("\nERROR: Can't add fuel to vehicles that haven't been created yet!\n");
		return;
	}

	Vehicle* selectedVehicle = SelectVehicle();
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

	if (!SpendMoney(fuelInput * m_gasPrice)) return;

	if(selectedVehicle->AddFuel(fuelInput))
	{
		printf("Added %g fuel to vehicle named %s.\n",
			fuelInput,
			selectedVehicle->m_name.c_str());
	}
	else
	{
		printf("Fuel exceeds car's fuel capacity. Unable to fuel.");
	}
	return;
}

void Game::DriveVehicleMenu()
{
	if (m_vm.GetVehicleCount() <= 0)
	{
		printf("\nERROR: Can't drive vehicles that haven't been created yet!\n");
		return;
	}

	Vehicle* selectedVehicle = SelectVehicle();
	if (selectedVehicle == nullptr) return;

	printf("How far would you like to drive?\n");
	printf("(>=0): ");
	double distance;
	std::cin >> distance;

	Vehicle::VEHICLE_DRIVE_RESULT driveResult =
		selectedVehicle->Drive(distance);

	switch (driveResult)
	{
	case Vehicle::VEHICLE_DRIVE_RESULT::Not_Enough_Fuel:
		printf("Not enough fuel!");
		return;
	case Vehicle::VEHICLE_DRIVE_RESULT::Negative_Distance:
		printf("Invlaid distance!");
		return;
	}

	printf("Drove %s for %g miles.\n",
		selectedVehicle->m_name.c_str(), distance);

	RandomizeGasPrice();
	HandleRandomEncounters(distance, selectedVehicle);

	return;
}

void Game::RandomizeGasPrice()
{
	std::srand(std::time(nullptr));
	m_gasPrice = (double)(std::rand() % 300) / 100 + 2.00;
}

void Game::HandleRandomEncounters(double distance, Vehicle* v)
{
	int numEncounters = CalculateNumEncounters(distance);

	for (int i = 0; i < numEncounters; ++i)
	{
		string encounterText = GetRandomEncounterText(v);
		double moneyEarned = CalculateMoneyEarned(distance);

		printf("%s You gain: $%.2f\n", encounterText.c_str(), moneyEarned);

		m_money += moneyEarned;
	}


}

int Game::CalculateNumEncounters(double distance)
{
	int numEncounters = distance / 100;

	
	// 50% chance to get an additional encounter.
	(std::rand() % 2 == 1) ? numEncounters++ : 0;

	return numEncounters;
}

string Game::GetRandomEncounterText(Vehicle* v)
{
	int randomEncounterIndex = std::rand() % (v->m_randomEncounters.size());
	string encounterText = v->m_randomEncounters[randomEncounterIndex];

	return encounterText;
}

double Game::CalculateMoneyEarned(double distance) {
	return (double)(std::rand() % (int)(distance * 10));
}


void Game::ClearScreen() {
	system("cls");
}