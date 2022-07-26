#include "Game.h"

using std::string;
using namespace std::chrono;
using namespace std::this_thread;

void Game::Loop()
{
	bool running = true;
	char userInput;

	while (running)
	{
		ClearScreen();
		printf("\n---------------------------------------------------\n");
		printf("\nMoney: $%4.2f\n", m_money);
		printf("\nFuel Price: $%4.2f/gal\n", m_gasPrice);
		printf("\n---------------------------------------------------\n");
		m_vm.ListVehicles();
		printf("\nOptions:\n");
		printf("  1. Purchase Vehicle\n");
		printf("  2. Rename Vehicle\n");
		printf("  3. Purchase Fuel For Vehicle\n");
		printf("  4. Drive Vehicle\n");
		printf("(1,2,3,4): ");
		std::cin >> userInput;
		ClearScreen();
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
		m_vm.NewVehicle(Vehicle::VEHICLE_TYPE::Plane);
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

	selectedVehicle->AddFuel(fuelInput);
	printf("Added %g fuel to vehicle named %s.\n",
		fuelInput,
		selectedVehicle->m_name.c_str());

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
		selectedVehicle->drive(distance);

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
	std::srand(std::time(nullptr));
	int numEncounters = distance / 100;

	(std::rand() % 2 == 1) ? numEncounters++ : 0;

	for (int i = 0; i < numEncounters; ++i)
	{
		int randomEncounterIndex = std::rand() % 3;

		string encounterText = v->m_randomEncounters[randomEncounterIndex];
		double moneyEarned = (double)(distance * 10.0) + (double)(std::rand() % (int)(distance * 10));

		printf("%s You gain: $%.2f\n", encounterText.c_str(), moneyEarned);

		m_money += moneyEarned;
	}


}

void Game::ClearScreen() {
	system("cls");
}