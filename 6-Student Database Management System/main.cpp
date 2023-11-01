#include "student.h"
#include "DBFunctions.h"
#include "UIFunctions.h"
#include "userCredentials.h"

std::string defaultTable{ "students" };

int main()
{
	std::string databaseName;
	std::cout << "Please enter database name: ";
	std::cin >> databaseName;
	if (databaseName == "*") databaseName = "";
	userCredentials userCred;
	int loginSuccess = login(userCred);
	if (loginSuccess) prompt(defaultTable, databaseName, userCred);
	else return 1;
	return 0;
}
