#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "User.hpp"
# include "socketRun.hpp"

class Channel {
	
public:
	Channel(User &creator, std::string name, socketRun &server);
	~Channel();

private:
	const std::string			_name;
	std::string					_topic;

	std::vector<std::string>	_banned;
	std::vector<std::string>	_chanops;
	std::vector<std::string>	_users;
	// std::vector<char>			_modes;
	
};

#endif