#include "command.hpp"

void	PASS(socketRun server, std::string pass, int id) {
	std::map<int, User*> clients = server.getUserMap();

	if (clients[id]->getRegister() == true)
		return (send_message(server,id, ERR_ALREADYREGISTRED, NULL));
	else if (!pass.size())
		return (send_message(server, id, ERR_NEEDMOREPARAMS, pass));
	else if (pass == server.getPwd())
		server.getUserMap()[id]->setRegister();
	else
		return (send_message(server, id, ERR_PASSWDMISMATCH, NULL));
}