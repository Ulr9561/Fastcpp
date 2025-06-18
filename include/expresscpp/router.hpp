//
// Created by ulr9661 on 09/06/25.
//

#ifndef ROUTER_HPP
#define ROUTER_HPP

#pragma once

#include <string>
#include <functional>
#include <vector>

#include "request.hpp"
#include "response.hpp"

namespace expresscpp {
    using Handler = std::function<void(Request& req, Response& res)>;
    using Middleware = std::function<void(Request& req, Response& res, std::function<void()>)>;
    struct Route {
        std::string method;
        std::string uri;
        std::vector<Middleware> middlewares;
        Handler handler;

        Route(std::string m, std::string p, std::vector<Middleware> mws, Handler h)
        : method(std::move(m)), uri(std::move(p)), middlewares(std::move(mws)) , handler(std::move(h)){}
    };
    class Router {
    public:
        explicit Router(std::string path = "");

        Router& use(Middleware middleware);
        Router& use(const std::string& path, Middleware middleware);
        Router& use(const std::string& path, std::shared_ptr<Router> subRouter);

        Router& get(const std::string& path, Handler handler);
        Router& post(const std::string& path, Handler handler);
        Router& put(const std::string& path, Handler handler);
        Router& del(const std::string& path, Handler handler);

        void registerRoute(crow::SimpleApp& app, const std::string& path = "") const;

    private:
        std::string base_path_;
        std::vector<Middleware> global_middlewares_;

        std::vector<Route> routes_;
        std::vector<std::pair<std::string, Middleware>> pathMiddlewares_;
        std::vector<std::pair<std::string, std::shared_ptr<Router>>> subRouters_;

        void addCrowRoute(crow::SimpleApp& app, const Route& route, const std::string& prefix) const;
    };
}


#endif //ROUTER_HPP