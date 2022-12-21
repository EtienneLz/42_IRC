#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <vector>
#include <sstream>
#include <cctype>
#include "../RepliesCodeDef.hpp"
#include "../utils.hpp"

class socketRun;

void    user_cmd(socketRun server, const std::string &params, int id);
int	    PASS(std::map<int, User*> &clients, socketRun serv, std::string pass, int id);

#include "../socketRun.hpp"
#endif