#include "builder.hpp"

int main() {
    std::vector<Checkpoint> checkpoints = {
        {"Start", 55.7558, 37.6176, true},
        {"Mountain Pass", 45.2345, 90.1123, false, 2.5},
        {"River Crossing", -35.1234, 150.1234, false, 1.75},
        {"Finish", -33.8688, 151.2093, true}
    };

    // Build text report
    TextReportBuilder textBuilder;
    CheckpointDirector director;
    director.buildReport(checkpoints, textBuilder);
    std::cout << textBuilder.getResult() << "\n";

    // Calculate total penalty
    PenaltyCalculatorBuilder penaltyBuilder;
    director.buildReport(checkpoints, penaltyBuilder);
    std::cout << penaltyBuilder.getResult() << std::endl;

    return 0;
}