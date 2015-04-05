#include <iostream>
#include <nkt/http.hpp>

int main() {
    try {
        nkt::http::server server(3030);
        server.set_callback([](nkt::http::request &req, nkt::http::response &res) -> void {
            res.header("Content-Type", "text/plain");
            res.body(req.raw());
            res.status(200, "OK");
        });
        server.run();
    } catch (std::runtime_error &e) {
        std::cerr << e.what();
    }
}
