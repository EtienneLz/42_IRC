#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <vector>
#include <sstream>
#include <cctype>
#include <unistd.h>
#include "../RepliesCodeDef.hpp"
#include "../utils.hpp"

void	NICK(Server *server, std::string nick, int id);
void	user_cmd(Server *server, std::string params, int id);
void	PASS(Server *serv, std::string pass, int id);
void    MODE(Server *server, std::string params, int id);
void    OPER(Server *server, std::string params, int id);
void	PING(Server *server, std::string params, int id);
void	PRIVMSG(Server *server, std::string params, int id);
void	KICK(Server *serv, std::string params, int id);
void	KILL(Server *serv, std::string params, int id);

// void	EXIT(Server server, std::string params, int id) { QUIT(Server server, std::string params, int id); }

#include "../Server.hpp"
#endif