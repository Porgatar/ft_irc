/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/04/18 11:41:23 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Irc.hpp"

Irc::Irc(void){};

Irc::Irc(const Irc &src) {

	*this = src;
}

Irc::Irc(const std::string port, const std::string password) {

	this->_port = atoi(port.c_str()); // temporary
	this->_password = password;
}

Irc::~Irc(void){};

Irc	&Irc::operator=(const Irc &rhs) {

	this->_socket = rhs._socket;
	this->_password = rhs._password;
	return (*this);
}

int Irc::getsocket() const {
	
	return this->_socket;
}

std::string Irc::getpassword() const {
	
	return this->_password;
}

int	Irc::getport() const {

	return this->_port;
}

int Irc::create_server(int port)
{
    struct protoent     *proto;
    struct sockaddr_in  sin;
    
    proto = getprotobyname("tcp");
    if (proto == 0)
    {
        std::cerr << "proto failed\n";
        return (-1);
    }
    this->_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto);
    if (this->_socket == -1)
    {
        std::cerr << "socket failed\n";
        return (-1);
    }
    fcntl(this->_socket, F_SETFL, O_NONBLOCK); /* Passe la socket en mode non bloquant: fortement deconseillé ça bouffe le CPU*/
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); /* inet return : network bytes order */
    if (bind(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        std::cerr << "bind failed\n";
        return (-1);
    }
    listen(this->_socket, 5);
	return (0);
}