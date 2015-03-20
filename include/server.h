#include <functional>
#include <stack>
#include "request.h"
#include "response.h"

namespace http {
    class server {
    public:
        typedef std::function<void(request &, response &)> server_callback_t;
    protected:
        std::stack<server_callback_t> _callbacks;
    public:

        void use(server_callback_t callback) {
            _callbacks.push(callback);
        }

        void listen(const int port) {
        }
    };
}
