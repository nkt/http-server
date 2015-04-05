#ifndef NKT_HTTP_RESPONSE_HPP
#define NKT_HTTP_RESPONSE_HPP

#include <string>
#include <sstream>
#include <unordered_map>

namespace nkt {
namespace http {

class response {
protected:
    int _status_code = 200;
    std::string _status_message = "OK";
    std::string _body = "";
    std::unordered_map<std::string, std::string> _headers;
public:
    void status(int code, std::string message) {
        _status_code = code;
        _status_message = message;
    }

    void body(std::string body) {
        _body = body;
    }

    void header(std::string name, std::string value) {
        _headers[name] = value;
    }

    std::string to_string() {
        std::ostringstream result;
        result << "HTTP/1.0 " << _status_code << " " << _status_message << "\r\n";
        for (auto it : _headers) {
            result << it.first << ": " << it.second << "\r\n";
        }
        result << "\r\n" << _body;
        return result.str();
    }
};

} // namespace http
} // namespace nkt

#endif // NKT_HTTP_RESPONSE_HPP
