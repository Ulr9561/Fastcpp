//
// Created by ulr9661 on 09/06/25.
//

#include "expresscpp/request.hpp"

#include <crow.h>

#include <utility>

namespace expresscpp {
    class Request::Impl {
    public:
        Impl(const crow::request &req, std::string base_url)
            : req_(req), base_url_(std::move(base_url)) {
        }

        const crow::request &req_;
        std::string base_url_;
        mutable nlohmann::json parsed_json_;
        mutable std::map<std::string, std::string> cookies_;
    };

    Request::Request(const crow::request& crowReq, std::string baseUrl)
    : m_impl_(std::make_unique<Impl>(crowReq, std::move(baseUrl))) {}


    Request::~Request() = default;

    std::string Request::body() const {
        return m_impl_->req_.body;
    }

    std::string Request::path() const {
        const size_t query_pos = m_impl_->req_.url.find('?');
        return query_pos != std::string::npos ? m_impl_->req_.url.substr(0, query_pos) : m_impl_->req_.url;
    }

    std::string Request::method() const {
        return method_name(m_impl_->req_.method);
    }

    std::string Request::url() const {
        return m_impl_->base_url_ + path();
    }

    std::string Request::original_url() const {
        return m_impl_->req_.url;
    }

    std::string Request::base_url() const {
        return m_impl_->base_url_;
    }

    nlohmann::json Request::json() const {
        if (m_impl_->parsed_json_.empty()) {
            m_impl_->parsed_json_ = nlohmann::json::parse(m_impl_->req_.body);
        }
        return m_impl_->parsed_json_;
    }

    std::string Request::param(const std::string &key) {
        return "";
    }

    std::string Request::query(const std::string &key) {
        return "";
    }

    std::string Request::get(const std::string &key) const {
        return m_impl_->req_.get_header_value(key);
    }

    std::string Request::hostname() const {
        std::string host = get("Host");
        const size_t pos = host.find(':');
        return pos != std::string::npos ? host.substr(0, pos) : host;
    }

    std::string Request::ip() const {
        return m_impl_->req_.remote_ip_address;
    }

    std::string Request::protocol() const {
        return get("X-Forwarded-Proto").empty() ? "http" : get("X-Forwarded-Proto");
    }

}
