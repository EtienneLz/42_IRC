#include <vector>
#include "../User.hpp"

void    cap(std::string params) {
    if (params != "LS")
        return;
    
    send_message("CAP * LS :")
}