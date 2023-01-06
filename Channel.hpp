#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include <vector>
class Server;

class Channel {
	
	typedef std::vector<User*>::iterator iter;
public:
	Channel(User &creator, std::string name, Server &server);
	Channel ();
	~Channel();

	void				joinChan(User newUser);
	void				leaveChan(std::string oldUser);
	std::string			userList(void);

	// GETTER
	std::vector<User *> getUsers();
	std::vector<User *> getChanops();

	std::string			getName();
	std::string			getTopic();
	std::string			getOwner();

	//SETTER
	void				setName(std::string name);
	void				setTopic(std::string title);
	void				setOwner(User owner);
	

private:
	std::string			_name;
	std::string			_topic;
	User				_owner;

	std::vector<User *>	_chanops;
	std::vector<User *>	_chanUsers;
	// std::vector<char>			_modes;
	
};

# include "Server.hpp"

#endif