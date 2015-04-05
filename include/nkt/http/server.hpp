#ifndef NKT_HTTP_SERVER_HPP
#define NKT_HTTP_SERVER_HPP

#include <iostream>
#include <functional>
#include <stack>
#include <thread>
#include <vector>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <nkt/http/request.hpp>
#include <nkt/http/response.hpp>

namespace nkt {
namespace http {

class server {
public:
    typedef std::function<void(request &, response &)> server_callback_t;
private:
    std::string _receive(const int &sock, const size_t buffer_length = 1024) {
        std::string result;
        char *buffer = new char[buffer_length];
        ssize_t len;
        do {
            ::memset(buffer, 0, buffer_length);
            len = ::recv(sock, &buffer, buffer_length, 0);
            if (len == -1) {
                throw std::runtime_error(::strerror(errno));
            }
            result += buffer;
            if (buffer_length > (size_t) len) {
                break;
            }
        } while (len > 0);

        delete[]buffer;

        return result;
    }

    void _send(const int &sock, const std::string &message) {
        long length = message.length();
        const char *bytes = message.c_str();
        while (length > 0) {
            long sent_length = ::send(sock, bytes, length, 0);
            if (sent_length == 0) {
                return;
            } else if (sent_length == -1) {
                throw std::runtime_error(::strerror(errno));
            }
            bytes += sent_length;
            length -= sent_length;
        }
    }

protected:
    server_callback_t _callback;
    int _listener;
public:

    server(const int &port) {
        _listener = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (_listener == -1) {
            throw std::runtime_error(::strerror(errno));
        }

        sockaddr_in address;
        ::memset(&address, 0, sizeof(address));
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if (::bind(_listener, (sockaddr *) &address, sizeof(address)) == -1) {
            throw std::runtime_error(::strerror(errno));
        }

        int optvalue = 1;
        int optlength = sizeof(optvalue);
        if (::setsockopt(_listener, SOL_SOCKET, SO_REUSEADDR, &optvalue, optlength) == -1) {
            throw std::runtime_error(::strerror(errno));
        }

        if (::listen(_listener, SOMAXCONN) == -1) {
            throw std::runtime_error(::strerror(errno));
        }
    }

    ~server() {
        if (_listener != -1) {
            close(_listener);
        }
    }

    void set_callback(server_callback_t callback) {
        _callback = callback;
    }

    void run() {
        unsigned cpus = std::thread::hardware_concurrency();
        if (cpus < 1) {
            cpus = 1;
        }

        auto listeners = new std::thread[cpus];

        for (unsigned i = 0; i < cpus; i++) {
            listeners[i] = std::thread([this]() -> void {
                for (; ;) {
                    sockaddr in_addr;
                    socklen_t in_len = sizeof(sockaddr);
                    int client = ::accept(_listener, &in_addr, &in_len);
                    if (client == -1) {
                        throw std::runtime_error(::strerror(errno));
                    }

                    request req(_receive(client));
                    response res;
                    _callback(req, res);
                    _send(client, res.to_string());

                    if (close(client) == -1) {
                        throw std::runtime_error(::strerror(errno));
                    }
                }
            });
        }
        for (unsigned i = 0; i < cpus; i++) {
            listeners[i].join();
        }
    }
};

} // namespace http
} // namespace nkt

#endif // NKT_HTTP_SERVER_HPP
