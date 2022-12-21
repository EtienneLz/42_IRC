#ifndef UTILS_HPP
# define UTILS_HPP

# include "RepliesCodeDef.hpp"
# include <sstream>

class socketRun;

bool    isspecial(char c);
bool    isforbidenuser(char c);
void    send_message(socketRun server, int id_cli, int code, std::string str);

# include "socketRun.hpp"
#endif