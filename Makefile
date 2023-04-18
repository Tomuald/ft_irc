NAME	=	ircserv

SRCS	=	Server/Server.class.cpp		\
			Client/Client.class.cpp		\
			Channel/Channel.class.cpp	\
			Message/Message.class.cpp	\
			Server/Commands/nick.cpp	\
			Server/Commands/user.cpp	\
			Server/Commands/quit.cpp	\
			Server/Commands/pass.cpp	\
			Server/Commands/join.cpp	\
			Server/Commands/privmsg.cpp	\
			Server/Commands/pong.cpp	\
			Server/Commands/who.cpp		\
			Server/Commands/part.cpp	\
			Server/Commands/mode.cpp	\
			Server/Commands/die.cpp		\
			Server/Commands/oper.cpp	\
			Server/Commands/kick.cpp	\
			Server/Commands/topic.cpp	\
			response.cpp				\

OBJS	=	${SRCS:.cpp=.o}

CFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g

CC		=	c++

RM		=	rm -Rf

all:		${NAME}

${NAME}:	${SRCS} main.cpp
			${CC} ${CFLAGS} ${SRCS} main.cpp -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all
