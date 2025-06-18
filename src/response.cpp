//
// Created by ulr9661 on 09/06/25.
//
#include "expresscpp/response.hpp"

#include <fstream>

namespace expresscpp {
    class Response::Impl {
    public:
        int statusCode = 200;
        std::string contentType = "text/plain";
        std::string body;
        std::map<std::string, std::string> headers;
        std::map<std::string, std::string> cookies;
    };

    Response::Response() : m_impl_(std::make_unique<Impl>()) {}

    Response::~Response() = default;

    Response &Response::status(const int code) {
        m_impl_->statusCode = code;
        return *this;
    }

    Response &Response::set(const std::string &field, const std::string &value) {
        m_impl_->headers[field] = value;
        return *this;
    }

    Response &Response::cookie(const std::string &name, const std::string &value) {
        m_impl_->cookies[name] = value;
        return *this;
    }

    Response &Response::json(const nlohmann::json &data) {
        m_impl_->contentType = "application/json";
        m_impl_->body = data.dump();
        return *this;
    }

    Response &Response::send(const std::string &content) {
        m_impl_->body = content;
        std::cout << "Sending: " << content << std::endl;
        return *this;
    }

    Response &Response::sendFile(const std::string &path) {
        if (std::ifstream file(path); file) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            m_impl_->body = buffer.str();
            m_impl_->contentType = "text/html"; // TODO: improve MIME detection
        } else {
            m_impl_->body = "File not found";
            m_impl_->statusCode = 404;
        }
        return *this;
    }

    Response &Response::redirect(const std::string &location) {
        m_impl_->statusCode = 302;
        m_impl_->headers["Location"] = location;
        return *this;
    }

    Response &Response::end() {
        // Nothing to do, included for Express-style chaining
        return *this;
    }

    crow::response Response::to_crow_reponse(const Response &response) {
        const auto &[statusCode, contentType, body, headers, cookies] = *response.m_impl_;
        crow::response crowRes(statusCode);
        crowRes.set_header("Content-Type", contentType);
        crowRes.write(body);

        for (const auto &[key, value]: headers) {
            crowRes.set_header(key, value);
        }

        for (const auto &[name, value]: cookies) {
            crowRes.add_header("Set-Cookie", name + "=" + value);
        }

        return crowRes;
    }
}
