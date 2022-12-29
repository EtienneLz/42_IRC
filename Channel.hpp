#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include "socketRun.hpp"

class Channel {
	
	typedef std::vector<std::string>::iterator iter;
public:
	Channel(User &creator, std::string name, socketRun &server);
	~Channel();

	// GETTER
	std::vector<std::string> getUsers();
	std::vector<std::string> getChanops();
	std::vector<std::string> getBanned();
	std::string				 getName();
	std::string				 getTopic();

	//SETTER
	void					 setTopic(std::string title);

private:
	const std::string			_name;
	std::string					_topic;

	std::vector<std::string>	_banned;
	std::vector<std::string>	_chanops;
	std::vector<std::string>	_users;
	// std::vector<char>			_modes;
	
};

#endif