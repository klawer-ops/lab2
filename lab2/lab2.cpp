#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>

// **Wzorzec Factory Method**

class Log {
public:
    virtual std::string getMessage() const = 0; // Wirtualna metoda, którą będą implementować klasy dziedziczące
    virtual ~Log() {}
};

class InfoLog : public Log {
public:
    InfoLog(const std::string& msg) : message(msg) {}
    std::string getMessage() const override {
        return "[INFO]: " + message;
    }
private:
    std::string message;
};

class WarningLog : public Log {
public:
    WarningLog(const std::string& msg) : message(msg) {}
    std::string getMessage() const override {
        return "[WARNING]: " + message;
    }
private:
    std::string message;
};

class ErrorLog : public Log {
public:
    ErrorLog(const std::string& msg) : message(msg) {}
    std::string getMessage() const override {
        return "[ERROR]: " + message;
    }
private:
    std::string message;
};

class LogFactory {
public:
    // Fabryka logów tworząca odpowiedni obiekt logu
    static std::shared_ptr<Log> createLog(const std::string& type, const std::string& message) {
        if (type == "info") {
            return std::make_shared<InfoLog>(message);
        }
        else if (type == "warning") {
            return std::make_shared<WarningLog>(message);
        }
        else if (type == "error") {
            return std::make_shared<ErrorLog>(message);
        }
        else {
            return nullptr;
        }
    }
};

// **Wzorzec Singleton**

class Logger {
public:
    // Pobieranie instancji Loggera (wzorzec Singleton)
    static Logger& getInstance() {
        static Logger instance; // Jedyna instancja Loggera
        return instance;
    }

    // Metoda do dodawania logów
    void logMessage(const std::string& type, const std::string& message) {
        // Tworzymy odpowiedni log za pomocą fabryki
        auto log = LogFactory::createLog(type, message);
        if (log) {
            logs.push_back(log);
            std::cout << "Log added: " << log->getMessage() << std::endl;
        }
        else {
            std::cout << "Invalid log type!" << std::endl;
        }
    }

    // Metoda do wyświetlania wszystkich logów
    void showLogs() const {
        if (logs.empty()) {
            std::cout << "No logs available." << std::endl;
            return;
        }
        std::cout << "All logs:" << std::endl;
        for (const auto& log : logs) {
            std::cout << log->getMessage() << std::endl;
        }
    }

private:
    Logger() {} // Konstruktor prywatny (wzorzec Singleton)
    ~Logger() {}

    Logger(const Logger&) = delete; // Zapobiega kopiowaniu
    Logger& operator=(const Logger&) = delete; // Zapobiega przypisaniu

    std::vector<std::shared_ptr<Log>> logs; // Przechowywanie logów
};

// **Funkcja do obsługi interakcji z użytkownikiem**

void menu() {
    std::string choice;
    Logger& logger = Logger::getInstance(); // Uzyskiwanie instancji loggera

    while (true) {
        std::cout << "\nLogger Menu:\n";
        std::cout << "1. Add log\n";
        std::cout << "2. Show all logs\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::string logType, logMessage;
            std::cout << "Enter log type (info, warning, error): ";
            std::getline(std::cin, logType);
            std::cout << "Enter log message: ";
            std::getline(std::cin, logMessage);
            logger.logMessage(logType, logMessage);
        }
        else if (choice == "2") {
            logger.showLogs();
        }
        else if (choice == "3") {
            std::cout << "Exiting program.\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

// **Testowanie Singletona**

void testSingleton() {
    Logger& logger1 = Logger::getInstance();
    Logger& logger2 = Logger::getInstance();

    if (&logger1 == &logger2) {
        std::cout << "Singleton test passed: Both logger1 and logger2 are the same instance.\n";
    }
    else {
        std::cout << "Singleton test failed: logger1 and logger2 are different instances.\n";
    }
}

int main() {
    // Testowanie Singletona
    testSingleton();

    // Uruchomienie menu
    menu();

    return 0;
}
