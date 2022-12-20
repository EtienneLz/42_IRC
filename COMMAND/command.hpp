#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <vector>
#include <sstream>
#include <cctype>
#include "../socketRun.hpp"
#include "../RepliesCodeDef.hpp"
#include "../utils.hpp"



void    user_cmd(socketRun server, const std::string &params, int id);
int	    PASS(std::map<int, User*> &clients, socketRun serv, std::string pass, int id);

#endif