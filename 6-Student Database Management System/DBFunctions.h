#ifndef DBFUNCTIONS_H_
#define DBFUNCTIONS_H_

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "mysql_connection.h"
#include "student.h"
#include "userCredentials.h"
#include "supportFunctions.h"

const std::string server = "";//type your server IP and port here

sql::Connection* connectToDB(std::string, const userCredentials&);
//void createTable(std::string, const userCredentials&);
void addEntry(std::string, std::string, Student, const userCredentials&);
void viewEntry(std::string, std::string, const userCredentials&, Student);
void editEntry(std::string, std::string, Student, std::vector<int>, const userCredentials&);
void deleteEntry(std::string, std::string, Student, std::vector<int>, const userCredentials&);
void backupTable(std::string, std::string, const userCredentials&);
bool deleteTable(std::string, std::string, const userCredentials&);
void printResult(Student);
std::vector<int> findEntry(std::string, std::string, Student, const userCredentials&);
std::vector<std::string> retrieveTables(std::string, const userCredentials&);
std::string buildViewQuery(std::string, Student);
std::string buildFindQuery(std::string, Student);
std::string buildEditQuery(std::string, Student, std::vector<int>);
std::string buildDeleteQuery(std::string, Student, std::vector<int>);
//std::string buildCreateTableQuery();

//void createTable(std::string databaseName, const userCredentials& userCred) {
//
//	try {
//		sql::Statement* stmt;
//		std::string statement = buildCreateTableQuery();
//		if (statement == " ") throw std::exception("Query returned with no results.");
//		sql::Connection* con = connectToDB(databaseName, userCred);
//		stmt = con->createStatement();
//		stmt->execute(statement);
//		delete stmt;
//	}
//	catch (const std::exception e)
//	{
//		std::cout << "Error: " << e.what() << std::endl;
//		return;
//	}
//
//	std::cout << "Finished creating table." << std::endl;
//}

sql::Connection* connectToDB(std::string databaseName, const userCredentials& userCred) {
	sql::Driver* driver;
	sql::Connection* connection = nullptr;

	try
	{
		driver = get_driver_instance();
		connection = driver->connect(server, userCred.username, userCred.pass);
	}
	catch (sql::SQLException e)
	{
		std::cout << "Could not connect to server. Error: " << e.what() << std::endl;
		delete connection;
	}

	try
	{
		connection->setSchema(databaseName); //name of database
	}
	catch (sql::SQLException e)
	{
		std::cout << "Could not connect. Error: " << e.what() << std::endl;
		delete connection;
	}

	if (connection != nullptr)return connection;
}


void addEntry(std::string tableName, std::string databaseName, Student student, const userCredentials& userCred) {
	sql::Connection* con = connectToDB(databaseName, userCred);
	sql::PreparedStatement* pstmt;
	pstmt = con->prepareStatement("INSERT INTO " + tableName + "(name, surname, age, grade, GPA) VALUES(? , ? , ? , ? , ? )");
	try {
		pstmt->setString(1, student.getName());
		pstmt->setString(2, student.getSurname());
		pstmt->setInt(3, student.getAge());
		pstmt->setInt(4, student.getGrade());
		pstmt->setDouble(5, student.getGPA());
		pstmt->execute();
		delete pstmt;
		delete con;
	}
	catch (const std::exception e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return;
	}

	std::cout << "Student successfully added." << std::endl;

}

void viewEntry(std::string tableName, std::string databaseName, const userCredentials& userCred, Student student = Student("bobbelcher")) {
	sql::Connection* con = connectToDB(databaseName, userCred);
	std::string statement;

	if (student.getName() == "*" || student.getName() == "bobbelcher") { //retrieve all entries if student's name is *
		statement = "SELECT * FROM " + tableName;
	}
	else { statement = buildViewQuery(tableName, student); }

	try
	{
		sql::PreparedStatement* pstmt = con->prepareStatement(statement);
		sql::ResultSet* res = pstmt->executeQuery();

		Student* temp = new Student;

		while (res->next()) {
			temp->setName(res->getString("name"));
			temp->setSurname(res->getString("surname"));
			temp->setAge(res->getInt("age"));
			temp->setGrade(res->getInt("grade"));
			temp->setGPA(res->getDouble("GPA"));
			temp->setID(res->getInt("id"));
			printResult(*temp);
		}
		delete temp;
		delete res;
		delete pstmt;
		delete con;
	}
	catch (const std::exception e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return;
	}
}

void editEntry(std::string tableName, std::string databaseName, Student student, std::vector<int> entryIndexes, const userCredentials& userCred) {
	sql::Connection* con = connectToDB(databaseName, userCred);
	std::string statement = buildEditQuery(tableName, student, entryIndexes);

	try
	{
		sql::PreparedStatement* pstmt = con->prepareStatement(statement);
		sql::ResultSet* res = pstmt->executeQuery();
		delete res;
		delete pstmt;
		delete con;
	}
	catch (const std::exception e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return;
	}
	std::cout << "Student(s) successfully edited." << std::endl;
}

void deleteEntry(std::string tableName, std::string databaseName, Student student, std::vector<int> entryIndexes, const userCredentials& userCred) {
	sql::Connection* con = connectToDB(databaseName, userCred);
	std::string statement = buildDeleteQuery(tableName, student, entryIndexes);

	try
	{
		sql::PreparedStatement* pstmt = con->prepareStatement(statement);
		sql::ResultSet* res = pstmt->executeQuery();
		delete res;
		delete pstmt;
		delete con;
	}
	catch (const std::exception e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return;
	}
	std::cout << "Student(s) successfully deleted." << std::endl;
}

std::vector<int> findEntry(std::string tableName, std::string databaseName, Student student, const userCredentials& userCred) {
	// finds requested rows and returns their id's
	sql::Connection* con = connectToDB(databaseName, userCred);
	std::vector<int> indexes;
	std::string statement = buildFindQuery(tableName, student);
	bool errorOccurred{ false };

	try
	{
		sql::PreparedStatement* pstmt = con->prepareStatement(statement);
		sql::ResultSet* res = pstmt->executeQuery();

		while (res->next()) {
			indexes.push_back(res->getInt("id"));
		}
		delete res;
		delete pstmt;
		delete con;
	}
	catch (const std::exception e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		errorOccurred = true;
	}

	if (!errorOccurred)return indexes;
}

std::vector<std::string> retrieveTables(std::string databaseName, const userCredentials& userCred) {
	std::vector<std::string> tables;
	bool errorOccurred{ false };
	std::string statement{ "SHOW TABLES" };

	try {
		sql::Connection* con = connectToDB(databaseName, userCred);
		sql::PreparedStatement* pstmt;
		pstmt = con->prepareStatement(statement);
		sql::ResultSet* res = pstmt->executeQuery();

		while (res->next()) {
			tables.push_back(res->getString("Tables_in_" + databaseName));
		}
		delete pstmt;
		delete con;
	}
	catch (const std::exception e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		errorOccurred = true;
	}
	if (!errorOccurred) return tables;
}

void printResult(Student student) {
	int width{ 20 };
	std::cout << std::left
		<< std::setw(width) << student.getID()
		<< std::setw(width) << student.getName()
		<< std::setw(width) << student.getSurname()
		<< std::setw(width) << student.getAge()
		<< std::setw(width) << student.getGrade()
		<< std::setw(width) << student.getGPA()
		<< std::endl;
}

std::string buildViewQuery(std::string tableName, Student student) {
	int parameterCount{ 0 };
	std::string statement{ "SELECT * FROM " + tableName + " WHERE " };

	if (student.getName() != "")
	{
		statement += "name = '" + student.getName() + "'"; parameterCount++;
	}
	if (student.getSurname() != "")
		if (parameterCount > 0) {
			statement += " AND surname = '" + student.getSurname() + "'"; parameterCount++;
		}
		else {
			statement += "surname = '" + student.getSurname() + "'"; parameterCount++;
		}
	if (student.getAge() != 0)
		if (parameterCount > 0) {
			statement += " AND age = " + std::to_string(student.getAge()); parameterCount++;
		}
		else {
			statement += "age = " + std::to_string(student.getAge()); parameterCount++;
		}
	if (student.getGrade() != 0) {
		if (parameterCount > 0) {
			statement += " AND grade = " + std::to_string(student.getGrade()); parameterCount++;
		}
		else {
			statement += "grade = " + std::to_string(student.getGrade()); parameterCount++;
		}
	}
	if (student.getGPA() != 0.0) {
		if (parameterCount > 0) {
			statement += " AND gpa = " + std::to_string(student.getGPA()); parameterCount++;
		}
		else {
			statement += "gpa = " + std::to_string(student.getGPA()); parameterCount++;
		}
	}
	//std::cout << "Statement = " << statement << std::endl;
	return statement;
}

std::string buildFindQuery(std::string tableName, Student student) {
	// finds requested rows and returns their id's
	int parameterCount{ 0 };
	std::string statement{ "SELECT id FROM " + tableName + " WHERE " };

	if (student.getName() != "")
	{
		statement += "name = '" + student.getName() + "'"; parameterCount++;
	}
	if (student.getSurname() != "")
		if (parameterCount > 0) {
			statement += " AND surname = '" + student.getSurname() + "'"; parameterCount++;
		}
		else {
			statement += "surname = '" + student.getSurname() + "'"; parameterCount++;
		}
	if (student.getAge() != 0)
		if (parameterCount > 0) {
			statement += " AND age = " + std::to_string(student.getAge()); parameterCount++;
		}
		else {
			statement += "age = " + std::to_string(student.getAge()); parameterCount++;
		}
	if (student.getGrade() != 0) {
		if (parameterCount > 0) {
			statement += " AND grade = " + std::to_string(student.getGrade()); parameterCount++;
		}
		else {
			statement += "grade = " + std::to_string(student.getGrade()); parameterCount++;
		}
	}
	if (student.getGPA() != 0.0) {
		if (parameterCount > 0) {
			statement += " AND gpa = " + std::to_string(student.getGPA()); parameterCount++;
		}
		else {
			statement += "gpa = " + std::to_string(student.getGPA()); parameterCount++;
		}
	}
	//std::cout << "Find Statement = " << statement << std::endl;
	return statement;
}

std::string buildEditQuery(std::string tableName, Student student, std::vector<int> indexes) {
	int parameterCount{ 0 };
	std::string statement{ "UPDATE " + tableName + " SET " };

	if (student.getName() != "")
	{
		statement += "name = '" + student.getName() + "'"; parameterCount++;
	}
	if (student.getSurname() != "")
		if (parameterCount > 0) {
			statement += ", surname = '" + student.getSurname() + "'"; parameterCount++;
		}
		else {
			statement += "surname = '" + student.getSurname() + "'"; parameterCount++;
		}
	if (student.getAge() != 0)
		if (parameterCount > 0) {
			statement += ", age = " + std::to_string(student.getAge()); parameterCount++;
		}
		else {
			statement += "age = " + std::to_string(student.getAge()); parameterCount++;
		}
	if (student.getGrade() != 0) {
		if (parameterCount > 0) {
			statement += ", grade = " + std::to_string(student.getGrade()); parameterCount++;
		}
		else {
			statement += "grade = " + std::to_string(student.getGrade()); parameterCount++;
		}
	}
	if (student.getGPA() != 0.0) {
		if (parameterCount > 0) {
			statement += ", gpa = " + std::to_string(student.getGPA()); parameterCount++;
		}
		else {
			statement += "gpa = " + std::to_string(student.getGPA()); parameterCount++;
		}
	}

	statement += "\nWHERE id IN (";
	for (int i = 0; i < indexes.size(); i++)
	{
		statement += std::to_string(indexes[i]);
		if (i < indexes.size() - 1)statement += ",";
	}
	statement += ")";
	//std::cout << "Edit Statement = " << statement << std::endl;

	return statement;
}

std::string buildDeleteQuery(std::string tableName, Student student, std::vector<int> indexes) {
	int parameterCount{ 0 };
	std::string statement{ "DELETE FROM " + tableName + " WHERE id IN ( " };

	for (int i = 0; i < indexes.size(); i++)
	{
		statement += std::to_string(indexes[i]);
		if (i < indexes.size() - 1)statement += ",";
	}
	statement += ")";
	//std::cout << "Delete Statement = " << statement << std::endl;

	return statement;
}

//std::string buildCreateTableQuery() {
//	std::string input{ "" };
//	int tmp;
//	std::string statement{ "CREATE TABLE IF NOT EXISTS " };
//	std::cout << "Enter new table name: ";
//	std::cin >> input;
//	statement.append(input);
//	std::cout << "Enter number of columns: ";
//	std::cin >> tmp;
//	std::vector<std::string> columns, columnTypes;
//
//	for (int i = 0; i < tmp; i++)
//	{
//		std::cout << "Enter " + std::to_string(i + 1) + ". column name: ";
//		std::cin >> input;
//		columns.push_back(input);
//	}
//
//	for (int i = 0; i < tmp; i++)
//	{
//		bool inputOK{ false };
//		while (!inputOK)
//		{
//			std::cout << "Enter type of column " + columns[i] + " (string, integer, double): ";
//			std::cin >> input;
//			if (input == "string" || input == "integer" || input == "double")inputOK = true;
//			else std::cout << "Wrong type. Please try again." << std::endl;
//		}
//		columnTypes.push_back(input);
//	}
//	statement += " (id INT PRIMARY KEY, ";
//	for (int i = 0; i < tmp; i++)
//	{
//		std::string dataType;
//		if (columnTypes[i] == "string") dataType = "VARCHAR(50)";
//		else if (columnTypes[i] == "integer") dataType = "int(11)";
//		else if (columnTypes[i] == "double") dataType = "double";
//		else { std::cout << "Error. Wrong datatype. Command terminated." << std::endl; return " "; }
//		statement += columns[i] + " " + dataType + ",";
//	}
//	statement.erase(statement.size() - 1);
//	statement.append(")");
//	std::cout << "createTableStatement = " + statement << std::endl;
//	return statement;
//}

void backupTable(std::string tableName, std::string databaseName, const userCredentials& userCred) {
	//CREATE TABLE target_database.backup_table AS SELECT * FROM source_database.original_table;
	std::string backupTableName{ "backup_" + tableName + "_" + todaysDate() };
	std::string statement{ "CREATE TABLE " + backupTableName + " AS SELECT * FROM " + tableName };

	try
	{
		sql::Connection* con = connectToDB(databaseName, userCred);
		sql::PreparedStatement* pstmt = con->prepareStatement(statement);
		sql::ResultSet* res = pstmt->executeQuery();
		delete res;
		delete pstmt;
		delete con;
	}
	catch (const std::exception e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return;
	}
	std::cout
		<< "Backup complete. Table backed up as " + backupTableName + "." << std::endl;
}

bool deleteTable(std::string tableName, std::string databaseName, const userCredentials& userCred) {
	std::string statement{ "DROP TABLE " + tableName };

	try
	{
		sql::Connection* con = connectToDB(databaseName, userCred);
		sql::PreparedStatement* pstmt = con->prepareStatement(statement);
		sql::ResultSet* res = pstmt->executeQuery();
		delete res;
		delete pstmt;
		delete con;
	}
	catch (const std::exception e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return false;
	}
	std::cout << "Delete complete." << std::endl;
	return true;
}

#endif
