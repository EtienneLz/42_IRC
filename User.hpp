#ifndef USER_HPP
# define USER_HPP

#include <string>
#include <iostream>

// ABSTRACT USERS CLASS
class User {
protected:
    std::string _nickname;
	std::string _username;
    std::string _realname;
    std::string _host;
    bool        _operator;
    bool        _register;
	
public:
    User();
    ~User();
    int fd;
	int num_conn;
	int count;

    const std::string getUsername() const;
    void        setUsername(std::string str);

    const std::string getRealname() const;
    void        setRealname(std::string str);

    const std::string getHost() const;
    void        setHost(std::string str);

    std::string const &getNick(void) const;
    void        setNick(std::string str);

    void        setRegister(void);
    bool const &getRegister(void) const;
};

std::ostream& operator<<(std::ostream& output, const User &user);

#endif