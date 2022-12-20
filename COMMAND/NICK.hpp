#ifndef NICK_HPP
# define NICK_HPP

#include <vector>
#include "User.hpp"

class Nick
{
	private:

		Nick();
	public:
		Nick(std::vector<User*> clients);
		~Nick();
};

#endif