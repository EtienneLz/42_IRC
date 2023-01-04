#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include <vector>
class Server;

class Channel {
	
	typedef std::vector<User *>::iterator iter;
public:
	Channel(User &creator, std::string name, Server &server);
	~Channel();

	// GETTER
	std::vector<User *> getUsers();
	std::vector<User *> getChanops();

	std::string				 getName();
	std::string				 getTopic();

	//SETTER
	void					 setTopic(std::string title);

private:
	const std::string			_name;
	std::string					_topic;
	User						_owner;

	std::vector<User *>	_chanops;
	std::vector<User *>	_users;
	// std::vector<char>			_modes;
	
};

# include "Server.hpp"

#endif