#include <memory>
#include <string>
#include <iostream>

class Group;

class User {
public:
    User(int userId, std::string username, std::string email, int age)
        : userId_(userId), username_(std::move(username)), email_(std::move(email)), age_(age) {}

    int getUserId() const { return userId_; }
    const std::string& getUsername() const { return username_; }
    const std::string& getEmail() const { return email_; }
    int getAge() const { return age_; }
    std::weak_ptr<Group> getGroup() const { return group_; }
    void setGroup(const std::shared_ptr<Group>& group) { group_ = group; }

private:
    int userId_;
    std::string username_;
    std::string email_;
    int age_;
    std::weak_ptr<Group> group_;
};