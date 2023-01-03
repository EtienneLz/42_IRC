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

int     searchUsername(socketRun server, std::string name) {
    for (std::map<int, User*>::iterator it = server.getUserMap().begin(); it != server.getUserMap().end(); it ++) {
        if (name == (*it).second->getUsername())
            return (*it).first;
    }
    return -1;
}

std::string mode_str(socketRun server, int id_cli) {
    std::string ret = "";
    if (server.getUserMap()[id_cli]->getMode('r'))
        ret += "r";
    if (server.getUserMap()[id_cli]->getMode('o'))
        ret += "o";
    if (server.getUserMap()[id_cli]->getMode('i'))
        ret += "i";
    return ret;
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
    else
        realCode = codeStr;
    
    std::string message = ":" + server.getHostname() + " " + realCode;
    if (server.getUserMap()[id_cli]->getNick().empty())
        message += " * ";
    else
        message += " " + server.getUserMap()[id_cli]->getNick() + " ";

    switch (code) {
        // REPLIES
        case RPL_WELCOME:
            message += ":Welcome to our IRC server " + server.getUserMap()[id_cli]->getNick(); break;
        case RPL_YOURHOST:
            message += ":Your host is " + server.getHostname() + ", running version Alpha 0.1"; break;
        case RPL_CREATED:
            message += ":This server was created \"coder temps ecoule\""; break;
        case RPL_MYINFO:
            message += server.getHostname() + " Alpha 0.1 " + " Trucs a rajouter"; break;
        case RPL_UMODEIS:
            message += mode_str(server, id_cli); break;
        case RPL_YOUREOPER:
            message += ":You are now an IRC operator"; break;

        // ERRORS
        case ERR_NONICKNAMEGIVEN:
            message += ":No nickname given"; break;
        case ERR_ERRONEUSNICKNAME:
            message += str + " :Erroneous nickname"; break;
        case ERR_NICKNAMEINUSE:
            message += str + " :Nickname is already in use"; break;
        case ERR_NOTREGISTERED:
            message += ":You have not registered"; break;
        case ERR_NEEDMOREPARAMS:
            message += str + " :Not enough parameters"; break;
        case ERR_ALREADYREGISTRED:
            message += ":Unauthorized command (already registered)"; break;
        case ERR_PASSWDMISMATCH:
            message += ":Password incorrect"; break;
        case ERR_RESTRICTED:
            message += ":Your connection is restricted!"; break;
        case ERR_UMODEUNKNOWNFLAG:
            message += ":Unknown MODE flag"; break;
        case ERR_USERSDONTMATCH:
            message += ":Cannot change mode for other users"; break;
    }

    message += "\r\n";
    std::cout << "REPLY --- " << message << std::endl;
    send(id_cli, message.c_str(), message.length(), MSG_DONTWAIT);
}