#include <string>
#include <map>
#include <cctype>
#include "User.hpp"
#include "socketRun.hpp"
#define ERR_NEEDMOREPARAMS 461
#define ERR_ALREADYREGISTRED 462
#define ERR_PASSWDMISMATCH 464

int	PASS(std::map<int, User*> &clients, socketRun serv, std::string pass, int id)
{
	if (clients[id]->getRegister() == true)
		return (ERR_ALREADYREGISTRED);
	else if (!pass.size())
		return (ERR_NEEDMOREPARAMS);
	else if (pass == serv.getPwd())
		clients[id]->setRegister(true);
	else
		return (send_message(serv, id, ERR_PASSWDMISMATCH, NULL));
}