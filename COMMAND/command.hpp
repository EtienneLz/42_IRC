#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <vector>
#include <sstream>
#include "../socketRun.hpp"
#include "../RepliesCodeDef.hpp"

void    user_cmd(std::map<int, User*> clients, const std::string &params, int id);

#endif