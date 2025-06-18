//
// Created by ulr9661 on 07/06/25.
//

#include <utility>
#include <future>


#include "expresscpp/app.hpp"

namespace expresscpp {
    App::App() : crow_app_(std::make_unique<crow::SimpleApp>()), main_router_(std::make_shared<Router>()),
                 logger_(std::make_shared<ExpressCPPLogger>()) {
        crow::logger::setHandler(logger_.get());
        crow_app_->loglevel(crow::LogLevel::Info);
    }

    App::~App() = default;

    Router &App::get(const std::string &path, Handler handler) const {
        return main_router_->get(path, std::move(handler));
    }

    Router &App::post(const std::string &path, Handler handler) const {
        return main_router_->post(path, std::move(handler));
    }

    Router &App::put(const std::string &path, Handler handler) const {
        return main_router_->put(path, std::move(handler));
    }

    Router &App::del(const std::string &path, Handler handler) const {
        return main_router_->del(path, std::move(handler));
    }

    Router &App::patch(const std::string &path, Handler handler) const {
        return main_router_->put(path, std::move(handler));
    }

    Router &App::options(const std::string &path, Handler handler) const {
        return main_router_->get(path, std::move(handler));
    }

    App &App::use(Middleware middleware) {
        main_router_->use(std::move(middleware));
        return *this;
    }

    App &App::use(const std::string &path, std::shared_ptr<Router> router) {
        main_router_->use(path, std::move(router));
        return *this;
    }

    Router &App::route(const std::string &path) const {
        return *main_router_;
    }

    void App::listen(uint16_t port, const std::string &host, const std::function<void()> &callback) const {
        crow_app_->bindaddr(host).port(port);
        routes();
        if (callback) {
            callback();
        }
        crow_app_->run_async();
    }


    crow::SimpleApp &App::getCrowApp() const {
        return *crow_app_;
    }

    void App::routes() const {
        main_router_->registerRoute(*crow_app_);
    }
}
