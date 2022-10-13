NAME = ircserv

SRCS = main1.cpp \
		socketRun.cpp \
		User.cpp

OBJS = ${SRCS:.cpp=.o}

#INCLUDES=

CXX = c++
#CC = cc

CXXFLAGS = -Wall -Wextra -Werror -std=c++98
#CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

PHONY.: all clean fclean re