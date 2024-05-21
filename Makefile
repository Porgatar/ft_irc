# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 19:13:25 by parinder          #+#    #+#              #
#    Updated: 2024/05/21 19:43:02 by parinder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS=	--silent

NAME=		ircserv

CC=			c++

CFLAGS=		-Wall -Werror -Wextra -std=c++98

ifdef DEBUG
CFLAGS +=	-g
endif

.cpp.o:
			${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

OBJ=		$(SRC:.cpp=.o)

SRC=		srcs/main.cpp \
			srcs/server/Irc.cpp \
			srcs/server/Irc_run.cpp \
			srcs/server/Irc_reply.cpp \
			srcs/server/cmd/cap.cpp \
			srcs/server/cmd/pass.cpp \
			srcs/server/cmd/user.cpp \
			srcs/server/cmd/nick.cpp \
			srcs/server/cmd/privMsg.cpp \
			srcs/server/cmd/join.cpp \
			srcs/server/cmd/kick.cpp \
			srcs/server/cmd/mode.cpp \
			srcs/server/cmd/topic.cpp \
			srcs/user/User.cpp \
			srcs/channel/Channel.cpp \
			srcs/channel/UserManagement.cpp \

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
			echo $(On_IGreen)"                                 "$(Color_Off)
			echo $(On_IGreen)$(BGreen)"       project compiled!        "$(Color_Off)
			echo $(On_IGreen)"                                 "$(Color_Off)

clean:
			rm -f $(OBJ)
			echo $(On_IGreen)"                                 "$(Color_Off)
			echo $(On_IGreen)$(BYellow)"       objects cleaned!         "$(Color_Off)
			echo $(On_IGreen)"                                 "$(Color_Off)

fclean:		clean
			rm -f $(NAME)
			echo $(On_IGreen)"                                 "$(Color_Off)
			echo $(On_IGreen)$(BYellow)"    project fully cleaned!      "$(Color_Off)
			echo $(On_IGreen)"                                 "$(Color_Off)

re:			fclean all

.PHONY:		all clean fclean re

#	-	-	-	-	-	Colors	-	-	-	-	-	-	#
#														|
BGreen=		'\033[1;32m'		#Bold Green				|
BYellow=	'\033[1;33m'		#Bold Yellow			|
#														|
On_IGreen=	'\033[0;102m'		#H.I-Green Background	|
#														|
Color_Off=	'\033[0m'			#Color Reset			|
#														|
#	-	-	-	-	-	-	-	-	-	-	-	-	-	#
