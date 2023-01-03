#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <vector>
#include <sstream>
#include <cctype>
#include "../RepliesCodeDef.hpp"
#include "../utils.hpp"

void	NICK(socketRun server, std::string nick, int id);
void	user_cmd(socketRun server, std::string params, int id);
void	PASS(socketRun serv, std::string pass, int id);
void	PRIVMSG(socketRun server, std::string params, int id);

#include "../socketRun.hpp"
#endif