NAME = ircserv

SRCS = main1.cpp \
		socketRun.cpp \
		User.cpp \
		COMMAND/USER.cpp \
		COMMAND/PASS.cpp \
		COMMAND/NICK.cpp \
		utils.cpp \
		

OBJS = ${SRCS:.cpp=.o}

#INCLUDES=

CXX = c++
#CC = cc

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3
#CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all