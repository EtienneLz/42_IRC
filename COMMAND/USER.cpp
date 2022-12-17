#include <vector>
#include "../socketRun.hpp"
#include "../Replies_Code_Def.hpp"

void    user_cmd(std::map<int, User*> clients, const std::string &params, int id) {
    std::vector<std::string> parts;
    std::stringstream ss(params);
    std::string s;
    while (std::getline(ss, s, ' '))
        parts.push_back(s);

    std::string message;
    message = ":OurIRC ";
    if (parts.size() < 4) {
        message += "461";
        message += " * :Not enough parameters\r\n";
        send(id, message.c_str(), message.length(), MSG_DONTWAIT);
        return ;
    }
    std::string username = parts[1];
    std::string realname = parts[4];

    clients.setUsername(username);
    clients.setRealname(realname);

}