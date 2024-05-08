/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/05/08 15:24:32 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Irc.hpp"

Irc	*g_IrcPtr;

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/

Irc::Irc(void) : _socket(0), _password("") {};

Irc::Irc(const Irc &src) {

	*this = src;
}

Irc::Irc(const std::string s_port, const std::string password) \
	: _socket(0), _password(password) {

	struct protoent		*proto;
	struct sockaddr_in	sin;
	int					port;

	port = atoi(s_port.c_str());
	if (port < 1024 || port > 65535) {

		this->log(ERROR, std::string("Error\nserver: port ") + s_port + \
								" is out of range\nrange: 1024 - 65535");
		exit(EXIT_FAILURE);
	}
	proto = getprotobyname("tcp");
	if (proto == 0) {

		this->log(ERROR, "Error\nserver: could not get prototype");
		exit(EXIT_FAILURE);
	}
	this->_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (this->_socket == -1) {

		this->log(ERROR, "Error\nserver: could not get socket");
		exit(EXIT_FAILURE);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1"); /* inet return : network bytes order */
	if (bind(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1) {

		this->log(ERROR, "Error\nserver: could not bind");
		close(this->_socket);
		exit(EXIT_FAILURE);
	}
	if (listen(this->_socket, 5) == -1) {
		this->log(ERROR, "Error\nserver: could not listen");
		close(this->_socket);
		exit(EXIT_FAILURE);
	}
}

/*	-	-	-	-	-	Destructors	-	-	-	-	-	*/

Irc::~Irc(void) {

	std::list<User>::iterator	i;

	for (i = _users.begin(); i != _users.end(); ++i)
		close((*i).getSocket());
	this->_users.clear();
	this->_channels.clear();
	close(this->_socket);
}

/*	-	-	-	-	-	Operators	-	-	-	-	-	*/

Irc &Irc::operator=(const Irc &rhs) {

	this->_socket = rhs._socket;
	this->_password = rhs._password;
	this->_users = rhs._users;
	this->_channels = rhs._channels;
	return (*this);
}

/*	-	-	-	-	-	Private Functions	-	-	-	-	-	*/

int Irc::setSockets(fd_set *set) {

	int max = this->_socket;
	std::list<User>::iterator it;

	for (it = _users.begin(); it != _users.end(); ++it) {

		if (it->getSocket() > 0) {

			FD_SET(it->getSocket(), set);
			if (it->getSocket() > max)
				max = it->getSocket();
		}
	}
	return (max);
}

std::list<Channel>::iterator	Irc::getChannelIteratorByName(const std::string &channelName)
{
	std::list<Channel>::iterator	it;

	for (it = this->_channels.begin(); it != this->_channels.end(); it++)
		if (channelName == it->getName())
			return (it);
	return (it);
}

/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/

void	Irc::setSigintHandler(void (*handler)(int)) {

	struct sigaction	sa;

	g_IrcPtr = this;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, 0);
}

bool	Irc::checkExistingChannel(std::string channels_name)
{
	std::list<Channel>::iterator		it;

	for (it = _channels.begin(); it != _channels.end(); it++) {
		if (it->getName() == channels_name)
			return (true);
	}
	return (false);
}

void	Irc::AddUserInChannel(User &user, std::string channels_name)
{
	std::list<Channel>::iterator		it;

	for (it = _channels.begin(); it != _channels.end(); it++) {
		if (it->getName() == channels_name) {
			if (it->isConnected(user.getNickname()) == false) {
				it->addUser(user);
				it->sendGroupMsg(user.getNickname() + " is joining the channel " + it->getName() + "\n");
			}
		}
	}
}

Channel	Irc::getChannel(std::string name) {
	
	std::list<Channel>::iterator it;

	for (it = _channels.begin(); it != _channels.end(); it++) {
		if (it->getName() == name)
			return (*it);
	}
	return (Channel());
}
