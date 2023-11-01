#ifndef UIFUNCTIONS_H_
#define UIFUNCTIONS_H_

#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "student.h"
#include "userCredentials.h"

std::string tableName;

void addStudent(std::string, std::string, const userCredentials&);
void viewStudents(std::string, std::string, const userCredentials&);
void editStudents(std::string, std::string, const userCredentials&);
void deleteStudents(std::string, std::string, const userCredentials&);
void adminPanel(std::string, std::string, const userCredentials&);
void prompt(std::string, std::string, const userCredentials&);
void promptSelection(int, std::string, std::string, const userCredentials&);
void switchCurrentTable(std::string, const userCredentials&);
void adminDeleteTable(std::string, std::string, const userCredentials&);
int evaluateInput(int, Student&);
int evaluateAdminInput(int, std::string, std::string, const userCredentials&);
int login(userCredentials&);

void addStudent(std::string tableName, std::string databaseName, const userCredentials& userCred) {
	std::string name, surname;
	int age{ 0 }, grade{ 0 };
	double gpa{ 0.0 };
	std::cout << "Enter student name and surname: ";
	std::cin >> name >> surname;
	std::cout << "Enter age: ";
	std::cin >> age;
	std::cout << "Enter grade: ";
	std::cin >> grade;
	std::cout << "Enter GPA: ";
	std::cin >> gpa;
	Student* temp = new Student(name, surname, age, grade, gpa);
	addEntry(tableName, databaseName, *temp, userCred);
	delete temp;
}

void viewStudents(std::string tableName, std::string databaseName, const userCredentials& userCred) {
	int width{ 20 };
	Student* student = new Student;

	while (1) {
		std::cout
			<< "--------------------------------------------------" << std::endl
			<< "VIEW STUDENT(S) - table: " << tableName << std::endl
			<< "Type * to view all or use search parameters for specific students:" << std::endl
			<< "1) Name" << std::endl
			<< "2) Surname" << std::endl
			<< "3) Age" << std::endl
			<< "4) Grade" << std::endl
			<< "5) GPA" << std::endl
			<< "6) No more parameters" << std::endl
			<< "Other options:" << std::endl
			<< "7) Back to main menu" << std::endl
			<< "8) Exit Program" << std::endl
			<< "9) Help (currently disabled)" << std::endl
			<< "VIEW STUDENT(S) - table: " << tableName << std::endl
			<< "--------------------------------------------------" << std::endl
			<< "Please choose: ";

		char input;
		std::cin >> input;

		if (input == '*') {
			student->setName("*");
			break;
		}
		else {
			int selection = input - '0'; //cast char to int
			int result = evaluateInput(selection, *student);
			if (!result)break;
			else if (result == 1) return;
			else if (result == 2) exit(0);
		}
	}
	std::cout << "\n" << std::left
		<< std::setw(width) << "Id"
		<< std::setw(width) << "Name"
		<< std::setw(width) << "Surname"
		<< std::setw(width) << "Age"
		<< std::setw(width) << "Grade"
		<< std::setw(width) << "GPA"
		<< std::endl
		<< std::setw(width) << "-------"
		<< std::setw(width) << "-------"
		<< std::setw(width) << "-------"
		<< std::setw(width) << "-------"
		<< std::setw(width) << "-------"
		<< std::setw(width) << "-------"
		<< std::endl;

	viewEntry(tableName, databaseName, userCred, *student);
	delete student;
}

void editStudents(std::string tableName, std::string databaseName, const userCredentials& userCred) {
	Student* student = new Student;
	Student* student2 = new Student;

	while (1) {
		std::cout
			<< "--------------------------------------------------" << std::endl
			<< "EDIT STUDENT(S) - table: " << tableName << std::endl
			<< "Select/add an option:" << std::endl
			<< "1) Edit by Name" << std::endl
			<< "2) Edit by Surname" << std::endl
			<< "3) Edit by Age" << std::endl
			<< "4) Edit by Grade" << std::endl
			<< "5) Edit by GPA" << std::endl
			<< "6) No more parameters" << std::endl
			<< "7) Back to main menu" << std::endl
			<< "8) Exit Program" << std::endl
			<< "9) Help (currently disabled)" << std::endl
			<< "EDIT STUDENT(S) - table: " << tableName << std::endl
			<< "--------------------------------------------------" << std::endl
			<< "Please choose: ";

		int selection{ 0 };
		std::cin >> selection;
		int result = evaluateInput(selection, *student);
		if (!result)break;
		else if (result == 1) return;
		else if (result == 2) exit(0);
	}
	std::vector<int>entryIndexes = findEntry(tableName, databaseName, *student, userCred);

	while (1) {
		std::cout
			<< "--------------------------------------------------" << std::endl
			<< "EDIT STUDENT(S) - NEW INFORMATION" << std::endl
			<< "Select/add an option:" << std::endl
			<< "1) Change Name" << std::endl
			<< "2) Change Surname" << std::endl
			<< "3) Change Age" << std::endl
			<< "4) Change Grade" << std::endl
			<< "5) Change GPA" << std::endl
			<< "6) No more changes" << std::endl
			<< "7) Back to main menu" << std::endl
			<< "8) Exit Program" << std::endl
			<< "9) Help (currently disabled)" << std::endl
			<< "--------------------------------------------------" << std::endl
			<< "Please choose: ";

		int selection{ 0 };
		std::cin >> selection;
		int result = evaluateInput(selection, *student2);
		if (!result)break;
		else if (result == 1) return;
		else if (result == 2) exit(0);
	}
	editEntry(tableName, databaseName, *student2, entryIndexes, userCred);
	delete student;
	delete student2;
}

void deleteStudents(std::string tableName, std::string databaseName, const userCredentials& userCred) {
	Student* student = new Student;

	while (1) {
		std::cout
			<< "--------------------------------------------------" << std::endl
			<< "DELETE STUDENT(S) - table: " << tableName << std::endl
			<< "Select/add an option:" << std::endl
			<< "1) by Name" << std::endl
			<< "2) by Surname" << std::endl
			<< "3) by Age" << std::endl
			<< "4) by Grade" << std::endl
			<< "5) by GPA" << std::endl
			<< "6) No more parameters" << std::endl
			<< "7) Back to main menu" << std::endl
			<< "8) Terminate program" << std::endl
			<< "--------------------------------------------------" << std::endl
			<< "Please choose: ";

		int selection{ 0 };
		std::cin >> selection;
		int result = evaluateInput(selection, *student);
		if (!result)break;
		else if (result == 1) return;
		else if (result == 2) exit(0);
	}
	std::vector<int>entryIndexes = findEntry(tableName, databaseName, *student, userCred);
	deleteEntry(tableName, databaseName, *student, entryIndexes, userCred);
	delete student;
}

void adminPanel(std::string tableName, std::string databaseName, const userCredentials& userCred) {
	int input{ 0 };
	while (input != 7) {
		std::cout
			<< "--------------------------------------------------" << std::endl
			<< "ADMIN PANEL - table: " << tableName << std::endl
			<< "1) View table" << std::endl
			<< "2) Backup table" << std::endl
			<< "3) Switch current table" << std::endl //used to be createTable
			<< "4) Edit table (currently disabled)" << std::endl //later
			<< "5) Delete table" << std::endl
			<< "6) Back to main menu" << std::endl
			<< "7) Exit Program" << std::endl
			<< "8) Help (currently disabled)" << std::endl
			<< "ADMIN PANEL - table: " << tableName << std::endl
			<< "--------------------------------------------------" << std::endl
			<< "Please choose: ";

		std::cin >> input;
		int result = evaluateAdminInput(input, tableName, databaseName, userCred);
		if (!result)break;
		else if (result == 1) { std::cout << "Returning to main menu." << std::endl; return; }
		else if (result == 2) exit(0);
	}
}

void prompt(std::string tableNameVal, std::string databaseName, const userCredentials& userCred) {
	tableName = tableNameVal;
	int input{ 0 };
	while (input != 6) {
		std::cout
			<< "--------------------------------------------------" << std::endl
			<< "MAIN MENU - table: " << tableName << std::endl
			<< "1) Add a Student" << std::endl
			<< "2) View Student(s)" << std::endl
			<< "3) Edit Student(s)" << std::endl
			<< "4) Delete Student(s)" << std::endl
			<< "5) Admin Panel" << std::endl
			<< "6) Exit Program" << std::endl
			<< "7) Help (currently disabled)" << std::endl
			<< "MAIN MENU - table: " << tableName << std::endl
			<< "--------------------------------------------------" << std::endl
			<< "Please choose: ";

		std::cin >> input;
		promptSelection(input, tableName, databaseName, userCred);
	}
}

void promptSelection(int num, std::string tableName, std::string databaseName, const userCredentials& userCred) {
	if (num == 1) addStudent(tableName, databaseName, userCred);
	else if (num == 2) viewStudents(tableName, databaseName, userCred);
	else if (num == 3) editStudents(tableName, databaseName, userCred);
	else if (num == 4) deleteStudents(tableName, databaseName, userCred);
	else if (num == 5) adminPanel(tableName, databaseName, userCred);
	else std::cout << "Wrong input. Try again." << std::endl;
}

void switchCurrentTable(std::string databaseName, const userCredentials& userCred) {
	std::cout << "Current table is " + tableName + ". Available tables are:" << std::endl;
	std::vector<std::string> tables = retrieveTables(databaseName, userCred);

	for (int i = 0; i < tables.size(); i++)
	{
		std::cout << "- " << ". " + tables[i] << std::endl;
	}

	while (1) {
		std::cout << "Please choose: ";
		std::string userInput;
		std::cin >> userInput;
		if (std::find(tables.begin(), tables.end(), userInput) != tables.end()) {
			tableName = userInput;
			std::cout
				<< "Table successfully switched to " + tableName + "." << std::endl;
			break;
		}
		else std::cout << "Wrong input. Try again." << std::endl;
	}
}

void adminDeleteTable(std::string tableName, std::string databaseName, const userCredentials& userCred) {
	char input;
	std::cout << "Delete " + tableName + " table? (y / n) : ";
	std::cin >> input;
	if (input == 'y' || input == 'Y') {
		bool tableDeleted = deleteTable(tableName, databaseName, userCred);
		if (tableDeleted) switchCurrentTable(databaseName, userCred);
	}
	else std::cout << "Delete cancelled." << std::endl;
}

int evaluateInput(int selection, Student& student) {
	std::string name{ "" }, surname{ "" };
	int age{ 0 }, grade{ 0 };
	double gpa{ 0.0 };
	if (selection == 1) { std::cout << "Enter name: "; std::cin >> name; student.setName(name); }
	else if (selection == 2) { std::cout << "Enter surname: "; std::cin >> surname; student.setSurname(surname); }
	else if (selection == 3) { std::cout << "Enter age: "; std::cin >> age; student.setAge(age); }
	else if (selection == 4) { std::cout << "Enter grade: "; std::cin >> grade; student.setGrade(grade); }
	else if (selection == 5) { std::cout << "Enter GPA: "; std::cin >> gpa; student.setGPA(gpa); }
	else if (selection == 6) { std::cout << "Finished adding parameters." << std::endl; return 0; }
	else if (selection == 7) return 1;
	else if (selection == 8) return 2;
	else std::cout << "Wrong input. Try again." << std::endl;
	return -1;
}

int evaluateAdminInput(int selection, std::string tableName, std::string databaseName, const userCredentials& userCred) {
	if (selection == 1) { viewEntry(tableName, databaseName, userCred); }
	else if (selection == 2) {
		char input;
		std::cout << "Backup " + tableName + " table? (y / n) : ";
		std::cin >> input;
		if (input == 'y' || input == 'Y') backupTable(tableName, databaseName, userCred);
		else std::cout << "Backup cancelled." << std::endl;
	}
	else if (selection == 3) { switchCurrentTable(databaseName, userCred); return 1; }
	else if (selection == 4) { std::cout << "This feature is currently disabled." << std::endl; }
	else if (selection == 5) { adminDeleteTable(tableName, databaseName, userCred); return 1; }
	else if (selection == 6) return 1;
	else if (selection == 7) return 2;
	else std::cout << "Wrong input. Try again." << std::endl;
	return -1;
}

int login(userCredentials& userCred) {
	int tries{ 3 };
	while (tries > 0) {
		std::cout << "Please enter your username: ";
		std::string username, password;
		std::cin >> username;
		std::cout << "Please enter password: ";
		std::cin >> password;

		if (username == "*" && password == "*") {//for easy access purposes
			userCred.username = "";
			userCred.pass = "!!";
			return 1;
		}
		if (username == "" && password == "") {//type name and pass
			std::cout << "User confirmed." << std::endl;
			return 1;
		}
		else std::cout << "Wrong username/password combination." << std::endl;

		tries--;
		std::cout << tries << " tries left." << std::endl;
	}
	return 0;
}
#endif
