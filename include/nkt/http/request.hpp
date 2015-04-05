#ifndef NKT_HTTP_REQUEST_HPP
#define NKT_HTTP_REQUEST_HPP

#include <string>

namespace nkt {
namespace http {

class request {
protected:
    std::string _raw;
public:
    request(const std::string &raw) {
        _raw = raw;
        for (size_t i = 0, len = raw.length(); i < len; i++) {

        }
    }

    const std::string &raw() {
        return _raw;
    }
};

} // namespace http
} // namespace nkt

#endif // NKT_HTTP_REQUEST_HPP
