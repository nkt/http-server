#include <iostream>
#include "server.h"

int main() {
    auto server = new http::server();

    server->use([=](http::request &req, http::response &res) -> void {
        res.status(200);
        res.send("Hello, world!");
    });
    server->listen(3000);
}