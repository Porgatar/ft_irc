/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:28:31 by parinder          #+#    #+#             */
/*   Updated: 2024/06/25 16:13:07 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//	std::string & print redirection dependency
#include <iostream>
#include <sstream>
//	list for users & channels dependency
#include <list>
#include <vector>
//	fcntl dependency
#include <unistd.h>
#include <fcntl.h>
//	getprotobyname dependency
#include <netdb.h>
//	select dependency
#include <sys/select.h> // not needed to compile ????
//	inet_addr/socket/htons/bind/listen dependency
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//	memset dependency
#include <cstring>
//	signal handler dependency
#include <signal.h>
#include <cstdio>
//	itoa
#include <stdlib.h>

//	unknown dependency
#include <algorithm>
#include <netdb.h>

#define PRED		"\033[0;31m"
#define PYELLOW		"\033[0;33m"
#define PORANGE		"\033[0;93m"
#define PRESET		"\033[0m"

//	irc class defines
#define ERROR	101
#define WARNING	102
#define DEBUG	103
#define INFO	104

//	user class defines
#define REGISTERED	3

//	channel class get(), add() '_users' and _mode defines
#define USER_LIST		0
#define OPERATOR_LIST	1
#define INVITE_LIST		2

// channel mode
#define I				0
#define T				1
#define K				2
#define L				3
#define O				4

//	Reply Macros
#define MODE_RPL(client, channelName, mode)	client, INFO, ":" + client.getNickname() + \
												" " + channelName + " " + mode

//	Warning Reply Macros
#define NOTREGISTERED(client)				client, WARNING, ": 451 " + client.getNickname() + \
												" :You have not registered"
#define ALREADYREGISTERED(client)			client, WARNING, ": 462 " + client.getNickname() + \
												" :You may not reregister"
#define UNKNOWNCOMMAND(client)				client, WARNING, ":" + client.getNickname() + \
												" :Unkown command"
#define NOSUCHCHANNEL(client, channel)		client, WARNING, ": 403 " + client.getNickname() + \
												" " + channel + " :No such channel"
#define CHANOPRIVSNEEDED(client, channel)	client, WARNING, ": 482 " + client.getNickname() + \
												" " + channel + " :You're not channel operator"
#define UNKNOWNMODE(client, mode)			client, WARNING, ": 472 " + client.getNickname() + \
												" " + mode + " :Is unknown mode char to me"
#define UNKNOWNUSER(client, nickName)		client, WARNING, ":" + client.getNickname() + \
												" " + nickName + " :Unknown user"

/*	momontanly unused Macros
#define JOIN_RPL(nick, channel)                        (":" + nick + " JOIN " + channel)
#define PART_RPL(client, channel)                    (":" + client + " PART " + channel)
#define KICK_RPL(client, channel, target)            (":" + client + " KICK " + channel + " " + target)
#define INVITERCVR_RPL(client, invitee, channel)    (":" + client + " INVITE " + invitee + " " + channel)
#define NICK_RPL(oldNick, newNick)                    (":" + oldNick + " NICK " + newNick)
#define TOPIC_RPL(client, channel, topic)            (":" + client + " TOPIC " + channel + " :" + topic)
#define WELCOME_RPL(client)                            (": 001 " + client + " :Welcome to The Internet Relay Chat world, " + client)
#define NOTOPIC_RPL(client, channel)                (": 331 " + client + " " + channel + " :No topic is set")
#define SEETOPIC_RPL(client, channel, topic)        (": 332 " + client + " " + channel + " :" + topic)
#define INVITESNDR_RPL(client, invitee, channel)    (": 341 " + client + " " + invitee + " " + channel)
#define NAMEREPLY_RPL(nick, channel, nicknames)        (": 353 " + nick + " = " + channel + " :" + nicknames)

#define TOOMUCHPARAMS_ERR(client, cmd)                (client + " " + cmd + " :Too much parameters")
#define USERONCHANNEL_ERR(nick, channel)            (": 303 " + nick + " " + channel + " :is already on channel")
#define NOSUCHNICK_ERR(client, nickname)            (": 401 " + client + " " + nickname + " :No such nickname")

#define CANNOTSENDTOCHAN_ERR(client, channel)        (": 404 " + client + " " + channel + " :Cannot send to channel")
#define NOTEXTTOSEND_ERR(client)                    (": 412 " + client + " :No text to send")
#define NONICKNAMEGIVEN_ERR(client, nick)            (": 431 " + client + " " + nick + " :No nickname given")
#define ERRONEUSNICKNAME_ERR(client, nickname)        (": 432 " + client + " " + nickname + " :Erroneus nickname")
#define NICKNAMEINUSE_ERR(client, nick)                (": 433 * " + client + " " + nick + " :Nickname is already in use")
#define USERNOTINCHANNEL_ERR(client, nick, channel)    (": 441 " + client + " " + nick + " " + channel + " :They aren't on that channel")
#define NOTONCHANNEL_ERR(client, channel)            (": 442 " + client + " " + channel + " :Not on that channel")
#define NEEDMOREPARAMS_ERR(client, cmd)                (": 461 " + client + " " + cmd + " :Not enough parameters")
#define PASSWDMISMATCH_ERR(client)                    (": 464 " + client + " :Password incorrect")
#define KEYSET_ERR(channel)                            (": 467 " + channel + " :Channel key already set")	//	a voir si on laisse la possibiliter  de remplacer le mdp.
#define CHANNELISFULL_ERR(client, channel)            (": 471 " + client + " " + channel + " :Cannot join channel (+l)")
#define INVITEONLYCHAN_ERR(client, channel)            (": 473 " + client + " " + channel + " :Cannot join channel (+i)")
#define BADCHANNELKEY_ERR(client, channel)            (": 475 " + client + " " + channel + " :Cannot join channel (+k)")
*/

std::string	skip_words(int n, const std::string &str);
    