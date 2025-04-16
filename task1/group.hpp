#include <vector>
#include <memory>
#include <algorithm>
#include "user.hpp"

class Group {
public:
    Group(int groupId) : groupId_(groupId) {}

    int getGroupId() const { return groupId_; }

    void addUser(const std::shared_ptr<User>& user) {
        users_.emplace_back(user);
        purgeExpiredUsers();
    }

    void removeUser(const std::shared_ptr<User>& user) {
        users_.erase(
            std::remove_if(users_.begin(), users_.end(),
                [&](const std::weak_ptr<User>& wUser) {
                    auto sUser = wUser.lock();
                    return sUser && sUser->getUserId() == user->getUserId();
                }),
            users_.end());
        purgeExpiredUsers();
    }

    std::vector<std::shared_ptr<User>> getUsers() const {
        purgeExpiredUsers();
        std::vector<std::shared_ptr<User>> validUsers;
        for (const auto& wUser : users_) {
            if (auto sUser = wUser.lock()) {
                validUsers.push_back(sUser);
            }
        }
        return validUsers;
    }

    void purgeExpiredUsers() const {
        auto& mutableUsers = const_cast<std::vector<std::weak_ptr<User>>&>(users_);
        mutableUsers.erase(
            std::remove_if(mutableUsers.begin(), mutableUsers.end(),
                [](const std::weak_ptr<User>& wUser) { return wUser.expired(); }),
            mutableUsers.end());
    }

private:
    int groupId_;
    mutable std::vector<std::weak_ptr<User>> users_;
};