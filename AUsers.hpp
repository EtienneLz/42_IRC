#ifndef AUSERS_HPP
# define AUSERS_HPP

#include "socketRun.hpp"
#include "Channel.hpp"

// ABSTRACT USERS CLASS
class AUsers {
private:
    std::string _nickname;
	std::string _username;
	std::vector<Channel> _chan;
	
public:
    AUsers();
    virtual ~AUsers();

};

#endif