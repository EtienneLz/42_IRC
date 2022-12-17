#ifndef USER_HPP
# define USER_HPP

//#include "socketRun.hpp"
//#include "Channel.hpp"
#include <string>

// ABSTRACT USERS CLASS
class User {
protected:
    std::string _nickname;
	std::string _username;
    std::string _realname;
    bool        _operator;
	// std::vector<Channel> _chan;
	
public:
    User();
    //virtual ~User();
    ~User();
    int fd;
	int num_conn;
	int count;

    std::string getUsername();

};

#endif