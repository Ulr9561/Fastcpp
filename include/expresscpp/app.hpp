//
// Created by ulr9661 on 07/06/25.
//

#ifndef APP_H
#define APP_H


#pragma once
#include <cstdint>
#include <functional>
#include <crow.h>

#include "request.hpp"
#include "response.hpp"
#include "router.hpp"
#include "logger.hpp"

namespace expresscpp {
    using Handler = std::function<void(Request& req, Response& res)>;
    using Middleware = std::function<void(Request& req, Response& res, std::function<void()>)>;

    class App {
    public:
        App();
        ~App();

        [[nodiscard]] Router& get(const std::string& path, Handler handler) const;
        [[nodiscard]] Router& post(const std::string& path, Handler handler) const;
        [[nodiscard]] Router& put(const std::string& path, Handler handler) const;
        [[nodiscard]] Router& del(const std::string& path, Handler handler) const;
        [[nodiscard]] Router& patch(const std::string& path, Handler handler) const;
        [[nodiscard]] Router& options(const std::string& path, Handler handler) const;

        App& use(Middleware middleware);
        App& use(const std::string& path, std::shared_ptr<Router> router);

        [[nodiscard]] Router& route(const std::string& path) const;

        void listen(uint16_t port, const std::string& host = "0.0.0.0", const std::function<void()>& callback = nullptr) const;

        [[nodiscard]] crow::SimpleApp& getCrowApp() const;
    private:
        std::unique_ptr<crow::SimpleApp> crow_app_;
        std::shared_ptr<Router> main_router_;
        std::shared_ptr<ExpressCPPLogger> logger_;

        void routes() const;
    };
};

#endif //APP_H
