NAME = ircserv

SRCS = main1.cpp \
		socketRun.cpp \
		User.cpp

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.cpp=%.o))
# OBJS = ${SRCS:.cpp=.o}

OBJ_DIR = objs

#INCLUDES=

CXX = c++
#CC = cc

CXXFLAGS = -Wall -Wextra -Werror -std=c++98
#CFLAGS = -Wall -Wextra -Werror

$(OBJ_DIR)/%.o : %.cpp
				@echo -n "Compiling $(_YELLOW)$@$(_WHITE) ... "
				@mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
				@echo "$(_GREEN)DONE$(_WHITE)"

all: ${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

PHONY.: all clean fclean re