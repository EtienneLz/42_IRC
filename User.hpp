#ifndef USER_HPP
# define USER_HPP

#include "socketRun.hpp"
#include "Channel.hpp"
#include <string>

// ABSTRACT USERS CLASS
class User {
protected:
    std::string _nickname;
    bool        _register;
	// std::string _username;
	// std::vector<Channel> _chan;

public:
    User();
    //virtual ~User();
    ~User();

    std::string const &getNick(void) const;
    bool const &getRegister(void) const;

    void    setNick(std::string nick);
    void    setRegister(bool const true);

    int fd;
	int num_conn;
	int count;

};

#endif