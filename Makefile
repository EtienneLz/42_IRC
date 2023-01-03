NAME = ircserv

SRCS = main1.cpp \
		socketRun.cpp \
		User.cpp \
		COMMAND/USER.cpp \
		COMMAND/PASS.cpp \
		COMMAND/NICK.cpp \
		COMMAND/PING.cpp \
		COMMAND/OP_CMD/MODE.cpp \
		COMMAND/OP_CMD/OPER.cpp \
		COMMAND/PRIVMSG.cpp \
		utils.cpp \


OBJS = ${SRCS:.cpp=.o}

#INCLUDES=

CXX = c++
#CC = cc

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3 #-fsanitize=address
#CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all