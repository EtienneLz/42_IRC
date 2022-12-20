#include "command.hpp"

void	PASS(std::map<int, User*> &clients, socketRun serv, std::string pass, int id)
{
	if (clients[id]->getRegister() == true)
		return (ERR_ALREADYREGISTRED);
	else if (!pass.size())
		return (ERR_NEEDMOREPARAMS);
	else if (pass == serv.getPwd())
		clients[id]->setRegister();
	else
		return (send_message(serv, id, ERR_PASSWDMISMATCH));
}