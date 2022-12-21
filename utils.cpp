#include "utils.hpp"

bool    isspecial(char c)
{
    if (c != '[' && c != ']' && c != '\\' && c != '`' && c != '_' && c != '^' && c != '{' && c != '|' && c != '}')
        return (false);
    return (true);
}

bool    isforbidenuser(char c)
{
    if (c == '\0' || c == ' ' || c == '\r' || c == '\n' || c == '@')
        return (true);
    return (false);
}

void    send_message(socketRun server, int id_cli, int code, std::string str) {
    std::string realCode;
    std::stringstream ss;
    ss << code;
    std::string codeStr = ss.str();
    if (code < 10)
        realCode = std::string(2, '0').append(codeStr);
    else if (code < 100)
        realCode = std::string(1, '0').append(codeStr);

    std::string message = ":" + server.getHostname() + " " + realCode;
    if (server.getUserMap()[id_cli]->getNick().empty())
        message += " * ";
    else
        message += server.getUserMap()[id_cli]->getNick() + " ";

    switch (code) {
        // REPLIES
        case RPL_WELCOME:
            message += "Welcome to our IRC server " + server.getUserMap()[id_cli]->getNick();
        case RPL_YOURHOST:
            message += "Your host is " + server.getHostname() + ", running version Alpha 0.1";
        case RPL_CREATED:
            message += "This server was created \"coder temps ecoule\"";
        case RPL_MYINFO:
            message += server.getHostname() + " Alpha 0.1 " + " Trucs a rajouter";

        // ERRORS
        case ERR_NONICKNAMEGIVEN:
            message += ":No nickname given";
        case ERR_ERRONEUSNICKNAME:
            message += str + " :Erroneous nickname";
        case ERR_NICKNAMEINUSE:
            message += str + " :Nickname is already in use";
        case ERR_NOTREGISTERED:
            message += ":You have not registered";
        case ERR_NEEDMOREPARAMS:
            message += str + " :Not enough parameters";
        case ERR_ALREADYREGISTRED:
            message += ":Unauthorized command (already registered)";
        case ERR_PASSWDMISMATCH:
            message += ":Password incorrect";
        case ERR_RESTRICTED:
            message += ":Your connection is restricted!";
    }

    message += "\r\n";
    send(id_cli, message.c_str(), message.length(), MSG_DONTWAIT);
}