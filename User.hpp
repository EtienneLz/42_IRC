#ifndef USER_HPP
# define USER_HPP

#include <string>

// ABSTRACT USERS CLASS
class User {
protected:
    std::string _nickname;
	std::string _username;
    std::string _realname;
    bool        _operator;
    bool        _register;
	
public:
    User();
    ~User();
    int fd;
	int num_conn;
	int count;

    std::string getUsername();
    void        setUsername(std::string str);

    std::string getRealname();
    void        setRealname(std::string str);

    std::string const &getNick(void) const;
    void        setNick(std::string str);

    void        setRegister(void);
    bool const &getRegister(void) const;
};

#endif