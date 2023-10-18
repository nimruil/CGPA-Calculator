#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <filesystem>

void createUsersFile();
bool login(std::string &, std::string &);
void registerUser();
bool checkCredentials(bool, std::string, std::string = "");
void getNameAndPass(std::string &, std::string &, std::string);
void failedToLogin();
void createUserFile(std::string);
void openUserFile(std::string);

void createUsersFile()
{
    std::string fileName = "users.csv";

    if (!std::filesystem::exists(fileName))
        std::ofstream myFile(fileName);
}

bool login(std::string &username, std::string &password)
{

    bool userExists{false};

    if (username == "newuser")
        registerUser();
    else if (username != "")
    {
        userExists = checkCredentials(true, username);

        if (userExists)
            std::cout << "User exists in system. ";
        else
            std::cerr << "User does not exist!" << std::endl;
    }

    if (userExists)
    {
        int i{0};
        while (1)
        {
            std::cout << "Please enter password: ";
            std::cin >> password;
            if (checkCredentials(false, username, password))
            {
                std::cout << "Login successful." << std::endl;
                return 1;
            }
            else
                std::cerr << "Incorrect password." << std::endl;
            if (++i == 3)
                failedToLogin();
        }
    }
    else if (!userExists)
    {
        registerUser();
        return 1;
    }
    else
    {
        std::cerr << "Error occurred." << std::endl;
        failedToLogin();
    }
    return 0;
}

void registerUser()
{
    std::string username, password1, password2, lowerUsername;
    int i{0};
    while (1)
    { // check validity of username
        std::cout << "Enter username to register: ";
        std::cin >> username;
        lowerUsername = username;

        for (char &x : lowerUsername)
        {
            x = tolower(x);
        }

        if (lowerUsername != "newuser")
            break;
        else
            std::cerr << "newuser and its variants cannot be used as a username." << std::endl;
        if (++i == 3)
            failedToLogin();
    }
    i = 0;
    while (1)
    {
        std::cout << "Enter your password: ";
        std::cin >> password1;
        std::cout << "Repeat password: ";
        std::cin >> password2;
        if (password1 == password2)
            break;
        else
            std::cerr << "Passwords do not match. Enter again." << std::endl;
        if (++i == 3)
            failedToLogin();
    }
    std::ofstream myFile;
    myFile.open("users.csv", std::fstream::app);
    myFile << username << ";" << password1 << std::endl;
    myFile.close();
    createUserFile(username);
    std::cout << "Registration complete!" << std::endl;
}

bool checkCredentials(bool checkOnlyUsername, std::string user, std::string pass)
{
    int counter{0};
    std::string text;
    std::ifstream myFile("users.csv", std::ios::in);
    while (std::getline(myFile, text))
    {
        std::string userName, password;
        getNameAndPass(userName, password, text);
        if (checkOnlyUsername && user == userName)
        {
            myFile.close();
            return 1;
            break;
        }
        else if (!checkOnlyUsername && user == userName && pass == password)
        {
            myFile.close();
            return 1;
            break;
        }

        counter++;
    }
    myFile.close();
    return 0;
}

void getNameAndPass(std ::string &name, std::string &pass, std::string line)
{
    // gets username and pass from a ; separated text
    int endPos = line.find(';');
    name = line.substr(0, endPos);
    pass = line.substr(endPos + 1, line.size());
}

void failedToLogin()
{
    std::cerr << "You failed to login or error occurred." << std::endl;
    std::cerr << "Program is closing.." << std::endl;
    getch();
    std::abort();
}

void createUserFile(std::string username)
{
    std::string fileName = username + ".txt";
    std::ofstream myFile(fileName);
    myFile.close();
}

void openUserFile(std::string username)
{
    std::string fileName = username + ".txt";
    std::ifstream myFile(fileName);
    if (!myFile)
    {
        std::cerr << "Error: File cannot be opened." << std::endl;
    }
    std::string text;
    std::cout << "Accessing file contents.." << std::endl;
    while (std::getline(myFile, text))
    {
        std::cout << text << std::endl;
    }
    myFile.close();
    std::cout << "File viewing complete. ";
}
#endif //_FUNCTIONS_H_
