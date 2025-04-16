#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "user_manager.hpp"

void printHelp() {
    std::cout << "\nAvailable commands:\n"
              << "  createUser {userId} {username} {email} {age} [groupId] - Create new user\n"
              << "  deleteUser {userId}          - Delete user\n"
              << "  allUsers                     - List all users\n"
              << "  getUser {userId}             - Show user details\n"
              << "  createGroup {groupId}        - Create new group\n"
              << "  deleteGroup {groupId}        - Delete group\n"
              << "  allGroups                    - List all groups with members\n"
              << "  getGroup {groupId}           - Show group details\n"
              << "  help                         - Show this help message\n"
              << "  exit                         - Exit the program\n\n"
              << "Examples:\n"
              << "  createUser 123 Alice alice@mail.com 25 456\n"
              << "  getGroup 456\n"
              << "  deleteUser 123\n\n";
}

int main() {
    UserManager manager;
    std::string line;

    std::cout << "User Management System\n";
    std::cout << "Type 'help' for list of commands\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line.empty()) continue;

        std::vector<std::string> tokens;
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        try {
            const std::string& cmd = tokens[0];
            
            if (cmd == "exit") {
                break;
            } else if (cmd == "help") {
                printHelp();
            } else if (cmd == "createUser" && tokens.size() >= 5) {
                int userId = std::stoi(tokens[1]);
                std::string username = tokens[2];
                std::string email = tokens[3];
                int age = std::stoi(tokens[4]);
                int groupId = (tokens.size() > 5) ? std::stoi(tokens[5]) : -1;

                if (manager.createUser(userId, username, email, age, groupId)) {
                    std::cout << "User created successfully\n";
                } else {
                    std::cout << "Error: User already exists\n";
                }
            } else if (cmd == "deleteUser" && tokens.size() == 2) {
                int userId = std::stoi(tokens[1]);
                if (manager.deleteUser(userId)) {
                    std::cout << "User deleted successfully\n";
                } else {
                    std::cout << "Error: User not found\n";
                }
            } else if (cmd == "allUsers" && tokens.size() == 1) {
                manager.allUsers();
            } else if (cmd == "getUser" && tokens.size() == 2) {
                int userId = std::stoi(tokens[1]);
                manager.getUser(userId);
            } else if (cmd == "createGroup" && tokens.size() == 2) {
                int groupId = std::stoi(tokens[1]);
                if (manager.createGroup(groupId)) {
                    std::cout << "Group created successfully\n";
                } else {
                    std::cout << "Error: Group already exists\n";
                }
            } else if (cmd == "deleteGroup" && tokens.size() == 2) {
                int groupId = std::stoi(tokens[1]);
                if (manager.deleteGroup(groupId)) {
                    std::cout << "Group deleted successfully\n";
                } else {
                    std::cout << "Error: Group not found\n";
                }
            } else if (cmd == "allGroups" && tokens.size() == 1) {
                manager.allGroups();
            } else if (cmd == "getGroup" && tokens.size() == 2) {
                int groupId = std::stoi(tokens[1]);
                manager.getGroup(groupId);
            } else {
                std::cout << "Invalid command. Type 'help' for assistance.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: Invalid input format. " << e.what() << "\n";
        } catch (...) {
            std::cout << "Error processing command\n";
        }
    }

    return 0;
}