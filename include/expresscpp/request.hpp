//
// Created by ulr9661 on 07/06/25.
//

#ifndef REQUEST_H
#define REQUEST_H

#pragma once
#include <crow.h>
#include <string>
#include <nlohmann/json.hpp>

namespace expresscpp {
    class Request {
    public:
        explicit Request(const crow::request &crowReq, std::string baseUrl);

        ~Request();

        [[nodiscard]] std::string method() const;

        [[nodiscard]] std::string url() const;

        [[nodiscard]] std::string original_url() const;

        [[nodiscard]] std::string base_url() const;

        [[nodiscard]] std::string path() const;

        [[nodiscard]] static std::string param(const std::string &key);

        [[nodiscard]] static std::string query(const std::string &key);

        [[nodiscard]] std::string body() const;

        [[nodiscard]] nlohmann::json json() const;

        [[nodiscard]] std::string get(const std::string &key) const;

        [[nodiscard]] std::string ip() const;

        [[nodiscard]] std::string hostname() const;

        [[nodiscard]] std::string protocol() const;

        class Impl;

    private:
        std::unique_ptr<Impl> m_impl_;
    };
}
#endif //REQUEST_H
