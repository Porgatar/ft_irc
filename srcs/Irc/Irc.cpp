/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/05/01 01:17:34 by maxime           ###   ########.fr       */
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
		std::cerr << PRED << "Error\nserver: port " << port \
			<< " is out of range\nrange: 1024 - 65535" << PRESET << std::endl;
		exit(EXIT_FAILURE);
	}
	proto = getprotobyname("tcp");
	if (proto == 0) {
		std::cerr << PRED << "Error\nserver: could not get prototype" \
			<< PRESET << std::endl;
		exit(EXIT_FAILURE);
	}
	this->_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (this->_socket == -1) {
		std::cerr << PRED << "Error\nserver: could not get socket" \
			<< PRESET << std::endl;
		exit(EXIT_FAILURE);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1"); /* inet return : network bytes order */
	if (bind(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1) {
		std::cerr << PRED << "Error\nserver: could not bind" \
			<< PRESET << std::endl;
		exit(EXIT_FAILURE);
	}
	listen(this->_socket, 5);
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

std::string	skip_isspace(std::string str) {

	int	i;

	i = 0;
	while (str[i] && str[i] >= 9 && str[i] <= 13 || str[i] == 32) // white space !
		i++;
	return (&str[i]);
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
