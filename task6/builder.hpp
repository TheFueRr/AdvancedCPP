#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <stdexcept>

// Базовый класс контрольного пункта
class Checkpoint {
public:
    Checkpoint(const std::string& name, double latitude, double longitude, bool isMandatory, double penalty = 0.0)
        : name(name), latitude(latitude), longitude(longitude), 
          isMandatory(isMandatory), penalty(penalty) {
        validateCoordinates();
    }

    void validateCoordinates() {
        if (latitude < -90.0 || latitude > 90.0 || longitude < -180.0 || longitude > 180.0) {
            throw std::invalid_argument("Invalid coordinates");
        }
    }

    std::string getName() const { return name; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    bool isMandatoryCheckpoint() const { return isMandatory; }
    double getPenalty() const { return penalty; }

private:
    std::string name;
    double latitude;
    double longitude;
    bool isMandatory;
    double penalty;
};

// Интерфейс
class CheckpointBuilder {
public:
    virtual ~CheckpointBuilder() = default;
    virtual void addCheckpoint(const Checkpoint& cp, int index) = 0;
    virtual std::string getResult() = 0;
};

// Конкретный Builder для текстового отчета
class TextReportBuilder : public CheckpointBuilder {
public:
    void addCheckpoint(const Checkpoint& cp, int index) override {
        report += std::to_string(index) + ". " + cp.getName() + " ("
                + formatCoordinate(cp.getLatitude()) + ", "
                + formatCoordinate(cp.getLongitude()) + ") degrees - ";
        
        if (cp.isMandatoryCheckpoint()) {
            report += "Mandatory (DNF)\n";
        } else {
            report += "Penalty: " + formatHours(cp.getPenalty()) + "\n";
        }
    }

    std::string getResult() override {
        return "Checkpoints List:\n" + report + "------------------\n";
    }

private:
    std::string report;
    
    std::string formatCoordinate(double coord) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << coord;
        return ss.str();
    }

    std::string formatHours(double hours) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << hours << " hours";
        return ss.str();
    }
};

// Concrete Builder for Penalty Calculation
class PenaltyCalculatorBuilder : public CheckpointBuilder {
public:
    void addCheckpoint(const Checkpoint& cp, int index) override {
        if (!cp.isMandatoryCheckpoint()) {
            totalPenalty += cp.getPenalty();
        }
    }

    std::string getResult() override {
        return "Total Penalty: " + formatHours(totalPenalty);
    }

private:
    double totalPenalty = 0.0;

    std::string formatHours(double hours) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << hours << " hours";
        return ss.str();
    }
};

// Класс Director
class CheckpointDirector {
public:
    void buildReport(const std::vector<Checkpoint>& checkpoints, CheckpointBuilder& builder) {
        for (size_t i = 0; i < checkpoints.size(); ++i) {
            builder.addCheckpoint(checkpoints[i], i+1);
        }
    }
};
