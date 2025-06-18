//
// Created by ulr9661 on 07/06/25.
//

#ifndef RESPONSE_H
#define RESPONSE_H

#include <crow.h>
#include <string>
#include <nlohmann/json.hpp>

namespace expresscpp {
    class Response {
    public:
        Response();
        ~Response();

        Response& status(int code);
        Response& set(const std::string& field, const std::string& value);
        Response& cookie(const std::string& name, const std::string& value);
        Response& json(const nlohmann::json& data);
        Response& send(const std::string& content);
        Response& sendFile(const std::string& path);
        Response& redirect(const std::string& location);
        Response& end();

        static crow::response to_crow_reponse(const Response& response);
        class Impl;
    private:
        std::unique_ptr<Impl> m_impl_;
    };
}
#endif //RESPONSE_H
