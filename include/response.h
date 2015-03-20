#include <string>

namespace http {
    class response {
    protected:
        int _status_code;
        std::string _status_message;
        std::string _body;
    public:
        void status(int code) {
            _status_code = code;
            _status_message = "";
        }

        void status(int code, std::string message) {
            _status_code = code;
            _status_message = message;
        }

        void send(std::string body) {
            _body = body;
        }
    };
}

