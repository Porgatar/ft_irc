# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxime <maxime@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 19:13:25 by parinder          #+#    #+#              #
#    Updated: 2024/04/30 04:15:55 by parinder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS=	--silent

NAME=		ircserv

CC=			c++

CFLAGS=		-Wall -Werror -Wextra -std=c++98 -g

ifdef DEBUG
CFLAGS +=	-g
endif

OBJ=		$(SRC:.cpp=.o)

SRC=		srcs/main.cpp \
			srcs/Irc/Irc.cpp \
			srcs/Irc/Irc_run.cpp \
			srcs/Irc/cmd/join.cpp \
			srcs/Irc/cmd/nick.cpp \
			srcs/Irc/cmd/pass.cpp \
			srcs/Irc/cmd/privMsg.cpp \
			srcs/Irc/cmd/user.cpp \
			srcs/User/User.cpp \
			srcs/Channel/Channel.cpp \
			srcs/Channel/UserManagement.cpp \

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
