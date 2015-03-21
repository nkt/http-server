#include <string>

namespace http {
    class request {
    private:
        std::string _raw;
    public:
        request(const std::string &raw) {
            _raw = raw;
        }

        const std::string &raw() {
            return _raw;
        }
    };
};
