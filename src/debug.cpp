#include "debug.hpp"

namespace Base {

void Print(const char*& txt, const char* _txt) {
    std::string name = "";
    while (*txt != '\0' and *txt != ',') {
        name += *txt;
        txt++;
    }

    while (*txt != '\0' and (*txt == ',' or *txt == ' ')) {
        txt++;
    }

    if (name == "\"\\n\"") {
        std::cerr << "\n";
        return ;
    }

    std::string txt_ = _txt;
    if (name.substr(1, txt_.size()) == txt_) {
        std::cerr << txt_ << '\n';
    } else {
        std::cerr << name << " = " << txt_ << '\t';
    }
}

} // namespace Base
