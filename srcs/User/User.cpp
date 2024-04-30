/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:54:12 by maxime            #+#    #+#             */
/*   Updated: 2024/04/30 02:46:37 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/User.hpp"

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/

User::User(void) : _registered(0), _socket(0), _username(""), _nickname(""), _buffer("") {}

User::User(const User &src) {

	*this = src;
}

/*	-	-	-	-	-	Destructors	-	-	-	-	-	*/

User::~User(void) {}

/*	-	-	-	-	-	Operators	-	-	-	-	-	*/

User	&User::operator=(const User &rhs) {

	this->_registered = rhs._registered;
	this->_socket = rhs._socket;
	this->_username = rhs._username;
	this->_nickname = rhs._nickname;
	this->_buffer = rhs._buffer;
	return (*this);
}

/*	-	-	-	-	-	Getters	-	-	-	-	-	*/

int	User::getSocket() const {

	return (this->_socket);
}

int	User::getRegisteredLevel() const {

	return (this->_registered);
}

const std::string	&User::getUsername() const {

	return (this->_username);
}

const std::string	&User::getNickname() const {

	return (this->_nickname);
}

const std::string	&User::getBuffer() const {

	return (this->_buffer);
}

/*	-	-	-	-	-	Setters	-	-	-	-	-	*/

void	User::setSocket(int fd) {

	this->_socket = fd;
}

void	User::setHigherRegisteredLevel(void) {

	if (this->_registered < 3)
		this->_registered++;
}

void	User::setLowerRegisteredLevel(void) {
	
	if (this->_registered > 0)
		this->_registered--;
}


void	User::setUsername(std::string username) {

	this->_username = username;
}

void	User::setNickname(std::string nickname) {

	this->_nickname = nickname;
}

void	User::setBuffer(std::string buf) {

	this->_buffer = buf;
}

/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/

void	User::sendMsg(std::string msg) {

	write(this->_socket, msg.c_str(), msg.length());
}

bool	User::isRegistered(void) {

	if (this->_registered == REGISTERED)
		return (true);
	return (false);
}
