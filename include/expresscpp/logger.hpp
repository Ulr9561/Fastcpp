//
// Created by ulr9661 on 10/06/25.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <crow.h>

namespace expresscpp {
    class ExpressCPPLogger : public crow::ILogHandler {
    public:
        ExpressCPPLogger() = default;

        void log(std::string message, crow::LogLevel level) override {
            static constexpr const char *colors[] = {
                    "\033[90m",  // DEBUG (gris)
                    "\033[37m",  // INFO (blanc)
                    "\033[33m",  // WARNING (jaune)
                    "\033[31m",  // ERROR (rouge)
                    "\033[41m"   // CRITICAL (fond rouge)
            };

            static constexpr const char *level_names[] = {
                    "DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"
            };

            std::cerr << colors[static_cast<int>(level)]
                      << "[ExpressCpp][" << level_names[static_cast<int>(level)] << "] "
                      << message << "\033[0m" << std::endl;
        }
    };
}

#endif //LOGGER_H
