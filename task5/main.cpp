#include "log.hpp"

int main() {
    Log* log = Log::Instance();
    
    log->message(LOG_NORMAL, "Program initialized");
    log->message(LOG_WARNING, "Low memory warning");
    log->message(LOG_ERROR, "Critical error: File not found");
    log->message(LOG_NORMAL, "Loading modules...");
    log->message(LOG_NORMAL, "User logged in");
    log->message(LOG_WARNING, "High CPU usage");
    log->message(LOG_NORMAL, "Data saved successfully");
    log->message(LOG_ERROR, "Network connection lost");
    log->message(LOG_NORMAL, "Backup started");
    log->message(LOG_NORMAL, "Processing complete");
    log->message(LOG_WARNING, "Disk space low");
    
    log->print();
    return 0;
}