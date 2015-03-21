#include <iostream>
#include "server.h"

int main() {
    try {
        http::server server(3030);
        server.set_callback([](http::request &req, http::response &res) -> void {
            res.header("Content-Type", "text/txt");
            res.body(req.raw());
            res.status(200, "OK");
        });
        server.run();
    } catch (std::runtime_error &e) {
        std::cerr << e.what();
    }
}