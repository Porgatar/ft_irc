/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:28:31 by parinder          #+#    #+#             */
/*   Updated: 2024/07/09 15:09:14 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER
#define HEADER

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

/*	-	-	-	-	-	Reply Macros	-	-	-	-	-	*/

#define UNKNOWNCOMMAND(client) \
	client, WARNING, std::string(":") + client.getNickname() + " :Unkown command"

#define TOPIC(client, channel, topic) \
	std::string(":") + client.getNickname() + " TOPIC " + channel + " :" + topic

#define MODE(client, channel, mode, target) \
	client, true, std::string(":") + client.getNickname() + " MODE " + channel + " :" \
	+ mode + " " + target

#define KICK(client, channel, target) \
	client, true, std::string(":") + client.getNickname() + " KICK " + channel + " " + target

#define PART(client, channel) \
	client, true, std::string(":") + client.getNickname() + " PART " + channel

#define	PRIVMSG(client, target, msg) \
	std::string(":") + client.getNickname() + " PRIVMSG " + target + " " + msg

#define	GROUPPRIVMSG(client, target, msg) \
	client, false, std::string(":") + client.getNickname() + " PRIVMSG " + target + " " + msg

#define JOIN(client, channel) \
	client, true, std::string(":") + client.getNickname() + " JOIN " + channel

#define WELCOME(client) \
	client, INFO, std::string(": 001 ") + client.getNickname() \
	+ " :Welcome to The Internet Relay Chat world, " + client.getNickname()

#define USERONCHAN(client, nick, channel) \
	client, WARNING, std::string(": 303 ") + client.getNickname() + " " + nick \
	+ " " +  channel + " :is already on channel"

#define CHANMODEIS(client, channel, mode)	\
	client, INFO, std::string(": 324 ") + client.getNickname() + " " + channel \
	+ " " + mode

#define NOTOPIC(client, channel) \
	client, INFO, std::string(": 331 ") + client.getNickname() + " " + channel \
	+ " :No topic is set"

#define SEETOPIC(client, channel, topic) \
	client, INFO, std::string(": 332 ") + client.getNickname() + " " + channel + " " + topic

#define INVITE(client, invitee, channel) \
	": 341 " + client.getNickname() + " " + invitee + " " + channel

#define NAMES(client, channel, nicknames) \
	client, INFO, std::string(": 353 ") + client.getNickname() + " = " + channel \
	+ " :" + nicknames

#define ENDOFNAMES(client, channel) \
	client, INFO, std::string(": 366 ") + client.getNickname() + " " + channel \
	+ " :End of /NAMES list"

#define NOSUCHNICK(client, channel, nickname) \
	client, WARNING, std::string(": 401 ") + client.getNickname() + " " + channel \
	+ " " + nickname + " :No such nick/channel"

#define NOSUCHCHAN(client, channel) \
	client, WARNING, std::string(": 403 ") + client.getNickname() + " " + channel \
	+ " :No such channel"

#define CANNOTSENDTOCHAN(client, channel) \
	client, WARNING, std::string(": 404 ") + client.getNickname() + " " + channel \
	+ " :Cannot send to channel"

#define NORECIPIENT(client) \
	client, WARNING, std::string(": 411 ") + client.getNickname() + " :No recipient given"

#define NOTEXTTOSEND(client) \
	client, WARNING, std::string(": 412 ") + client.getNickname() + " :No text to send"

#define NONICKNAMEGIVEN(client) \
	client, WARNING, std::string(": 431 ") + client.getNickname() \
	+ " :No nickname given"

#define ERRONEUSNICKNAME(client, nick) \
	client, WARNING, std::string(": 432 ") + client.getNickname() + " " + nick \
	+ " :Erroneus nickname"

#define NICKNAMEINUSE(client, nick) \
	client, WARNING, std::string(": 433 ") + client.getNickname() + " " + nick \
	+ " :Nickname is already in use"

#define USERNOTINCHAN(client, nick, channel) \
	client, WARNING, std::string(": 441 ") + client.getNickname() + " " + nick + " " \
	+ channel + " :They aren't on that channel"

#define NOTONCHAN(client, channel) \
	client, WARNING, std::string(": 442 ") + client.getNickname() + " " + channel \
	+ " :Not on that channel"

#define NOTREGISTERED(client) \
	client, WARNING, std::string(": 451 ") + client.getNickname() \
	+ " :You have not registered"

#define NEEDMOREPARAMS(client, cmd) \
	client, WARNING, std::string(": 461 ") + client.getNickname() + " " + cmd \
	+ " :Not enough parameters"

#define ALREADYREGISTERED(client) \
	client, WARNING, std::string(": 462 ") + client.getNickname() \
	+ " :You may not reregister"

#define PASSWDMISMATCH(client) \
	client, WARNING, std::string(": 464 ") + client.getNickname() \
	+ " :Password incorrect"

#define CHANISFULL(client, channel) \
	client, WARNING, std::string(": 471 ") + client.getNickname() + " " + channel \
	+ " :Cannot join channel (+l)"

#define INVITEONLYCHAN(client, channel) \
	client, WARNING, std::string(": 473 ") + client.getNickname() + " " + channel \
	+ " :Cannot join channel (+i)"

#define UNKNOWNMODE(client, mode) \
	client, WARNING, std::string(": 472 ") + client.getNickname() + " " + mode \
	+ " :Is unknown mode char to me"

#define BADCHANKEY(client, channel) \
	client, WARNING, std::string(": 475 ") + client.getNickname() + " " + channel \
	+ " :Cannot join channel (+k)"

#define BADCHANMASK(client, channel) \
	client, WARNING, std::string(": 476 ") + client.getNickname() + channel \
	+ " :Bad Channel Mask"

#define CHANOPRIVSNEEDED(client, channel) \
	client, WARNING, std::string(": 482 ") + client.getNickname() + " " + channel \
	+ " :You're not channel operator"

std::string	skip_words(int n, const std::string &str);

#endif