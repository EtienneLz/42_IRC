#include "../command.hpp"

void    OPER(socketRun server, std::string params, int id) {
    std::vector<std::string> parts;
    std::stringstream ss(params);
    std::string s;

    if (server.getUserMap()[id]->getMode('r') == true)
		return (send_message(server, id, ERR_RESTRICTED, ""));

    while (std::getline(ss, s, ' '))
        parts.push_back(s);

    if (parts.size() < 2) {
        send_message(server, id, ERR_NEEDMOREPARAMS, "");
        return ;
    }

    std::cout << "DEBUG --- " << *parts.begin() << " \"" << *(parts.begin() + 1) << "\"" << std::endl;
    std::cout << server.getOpPwd() << std::endl;

    std::string pwd = *(parts.begin() + 1);
    if (pwd != server.getOpPwd()) {
        send_message(server, id, ERR_PASSWDMISMATCH, "");
        return ;
    }
    int idDest = searchUsername(server, *parts.begin());
    if (idDest < 0)
        return ;
    server.getUserMap()[idDest]->setMode('o', true);
    send_message(server, idDest, RPL_YOUREOPER, "");
    send_message(server, idDest, RPL_UMODEIS, "");
}
