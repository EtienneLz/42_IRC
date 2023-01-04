#ifndef UTILS_HPP
# define UTILS_HPP

# include "RepliesCodeDef.hpp"
# include <sstream>

class Server;

bool    isspecial(char c);
bool    isforbidenuser(char c);
int     searchUsername(Server *server, std::string name);
void    send_message(Server *server, int id_cli, int code, std::string str);

# include "Server.hpp"
#endif