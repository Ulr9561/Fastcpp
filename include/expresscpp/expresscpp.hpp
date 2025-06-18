//
// Created by ulr9661 on 10/06/25.
//

#ifndef EXPRESSCPP_H
#define EXPRESSCPP_H
#pragma once

#include "app.hpp"
#include "request.hpp"
#include "response.hpp"
#include "router.hpp"

namespace expresscpp {
    inline std::shared_ptr<App> createApp() {
        return std::make_shared<App>();
    }
}
#endif //EXPRESSCPP_H
