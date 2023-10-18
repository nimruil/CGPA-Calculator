#include "functions.h"

int main()
{
    createUsersFile();
    std::string username,
        password;
    std::cout << "Welcome, guest! Enter your username or \"newuser\" to register: ";
    std::cin >> username;
    if (login(username, password))
        openUserFile(username);
    std::cout << "Press any key to exit.." << std::endl;
    getch();
    return 0;
}
