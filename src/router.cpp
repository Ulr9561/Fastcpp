//
// Created by ulr9661 on 09/06/25.
//

#include <utility>

#include "expresscpp/router.hpp"

namespace expresscpp {
    Router::Router(std::string path) : base_path_(std::move(path)) {}

    Router &Router::use(Middleware middleware) {
        global_middlewares_.push_back(std::move(middleware));
        return *this;
    }

    Router &Router::use(const std::string &path, Middleware middleware) {
        pathMiddlewares_.emplace_back(path, std::move(middleware));
        return *this;
    }

    Router &Router::use(const std::string &path, std::shared_ptr<Router> subRouter) {
        subRouters_.emplace_back(path, std::move(subRouter));
        return *this;
    }

    Router &Router::get(const std::string &path, Handler handler) {
        routes_.emplace_back("GET", path, std::vector<Middleware>{}, std::move(handler));
        return *this;
    }

    Router &Router::post(const std::string &path, Handler handler) {
        routes_.emplace_back("POST", path, std::vector<Middleware>{}, std::move(handler));
        return *this;
    }

    Router &Router::put(const std::string &path, Handler handler) {
        routes_.emplace_back("PUT", path, std::vector<Middleware>{}, std::move(handler));
        return *this;
    }

    Router &Router::del(const std::string &path, Handler handler) {
        routes_.emplace_back("DELETE", path, std::vector<Middleware>{}, std::move(handler));
        return *this;
    }

    void Router::registerRoute(crow::SimpleApp &app, const std::string &path) const {
        const std::string prefix = path + base_path_;

        for (const auto &route: routes_) {
            std::cout << "Adding route:" << route.uri << std::endl;
            addCrowRoute(app, route, prefix);
        }
        for (const auto &[subPath, subRouter]: subRouters_) {
            subRouter->registerRoute(app, prefix + subPath);
        }
    }

    void Router::addCrowRoute(crow::SimpleApp &app, const Route &route, const std::string &prefix) const {
        const std::string full_path = prefix + route.uri;

        std::cout << "Adding route: " << full_path << std::endl;

        // Convert method string to crow::HTTPMethod
        crow::HTTPMethod method;
        if (route.method == "GET") method = crow::HTTPMethod::GET;
        else if (route.method == "POST") method = crow::HTTPMethod::POST;
        else if (route.method == "PUT") method = crow::HTTPMethod::PUT;
        else if (route.method == "DELETE") method = crow::HTTPMethod::DELETE;
        else throw std::runtime_error("Unsupported HTTP method");

        // Create handler chain
        auto crow_handler = [=, this](const crow::request &crow_req, crow::response &crow_res) {
            Request req(crow_req, prefix);
            Response res;

            // Create a middleware chain
            std::vector<Middleware> handlers;
            handlers.insert(handlers.end(), global_middlewares_.begin(), global_middlewares_.end());

            // Add path-specific middlewares
            for (const auto &[mwPath, mw]: pathMiddlewares_) {
                if (req.path().starts_with(mwPath)) {
                    handlers.push_back(mw);
                }
            }

            // Add route-specific handlers
            handlers.insert(handlers.end(), route.middlewares.begin(), route.middlewares.end());

            handlers.emplace_back([&route](auto &req, auto &res, auto &&) {
                route.handler(req, res);
            });

            // Execute the chain
            size_t current = 0;
            std::function<void()> next = [&]() {
                if (current < handlers.size()) {
                    auto &handler = handlers[current++];
                    handler(req, res, next);
                }
            };
            next();
        };

        // Register a route with Crow
        app.route_dynamic(full_path).methods(method)(crow_handler);
    }
}