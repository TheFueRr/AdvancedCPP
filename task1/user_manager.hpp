#include <map>
#include <memory>
#include <iostream>
#include "group.hpp"

class UserManager {
public:
    bool createUser(int userId, const std::string& username, const std::string& email, int age, int groupId = -1) {
        if (users_.find(userId) != users_.end()) return false;
        auto user = std::make_shared<User>(userId, username, email, age);
        if (groupId != -1) {
            auto groupIt = groups_.find(groupId);
            if (groupIt != groups_.end()) {
                user->setGroup(groupIt->second);
                groupIt->second->addUser(user);
            }
        }
        users_[userId] = user;
        return true;
    }

    bool deleteUser(int userId) {
        auto it = users_.find(userId);
        if (it == users_.end()) return false;
        if (auto group = it->second->getGroup().lock()) {
            group->removeUser(it->second);
        }
        users_.erase(it);
        return true;
    }

    void allUsers() const {
        for (const auto& [id, user] : users_) {
            printUser(user);
        }
    }

    void getUser(int userId) const {
        auto it = users_.find(userId);
        if (it != users_.end()) printUser(it->second);
        else std::cout << "User not found.\n";
    }

    bool createGroup(int groupId) {
        if (groups_.find(groupId) != groups_.end()) return false;
        groups_[groupId] = std::make_shared<Group>(groupId);
        return true;
    }

    bool deleteGroup(int groupId) {
        auto it = groups_.find(groupId);
        if (it == groups_.end()) return false;
        for (auto& [id, user] : users_) {
            if (auto group = user->getGroup().lock()) {
                if (group->getGroupId() == groupId) {
                    user->setGroup(std::shared_ptr<Group>());
                }
            }
        }
        groups_.erase(it);
        return true;
    }

    void allGroups() const {
        for (const auto& [id, group] : groups_) {
            printGroup(group);
        }
    }

    void getGroup(int groupId) const {
        auto it = groups_.find(groupId);
        if (it != groups_.end()) printGroup(it->second);
        else std::cout << "Group not found.\n";
    }

private:
    std::map<int, std::shared_ptr<User>> users_;
    std::map<int, std::shared_ptr<Group>> groups_;

    void printUser(const std::shared_ptr<User>& user) const {
        std::cout << "User ID: " << user->getUserId()
                  << "\nUsername: " << user->getUsername()
                  << "\nEmail: " << user->getEmail()
                  << "\nAge: " << user->getAge();
        if (auto group = user->getGroup().lock()) {
            std::cout << "\nGroup ID: " << group->getGroupId();
        } else {
            std::cout << "\nNot in a group.";
        }
        std::cout << "\n-------------------\n";
    }

    void printGroup(const std::shared_ptr<Group>& group) const {
        std::cout << "Group ID: " << group->getGroupId() << "\nUsers:";
        auto users = group->getUsers();
        if (users.empty()) std::cout << " None";
        else for (const auto& user : users) {
            std::cout << "\n  " << user->getUsername() << " (ID: " << user->getUserId() << ")";
        }
        std::cout << "\n-------------------\n";
    }
};