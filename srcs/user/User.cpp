/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:54:12 by maxime            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/06 14:17:22 by mdesrose         ###   ########.fr       */
=======
/*   Updated: 2024/05/06 14:19:45 by parinder         ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/User.hpp"

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/

User::User(void) : _socket(0), _registered(0), _username(""), _nickname(""), _buffer("") {}

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

const std::string	&User::getMessage(void) const {

	return (this->_message);
}


int	User::getSocket() const {

	return (this->_socket);
}

int	User::getRegisteredLevel() const {

	return (this->_registered);
}

std::string	User::getStringId() const {

	std::ostringstream	oss;

	oss << this->_socket - 3;
	return (std::string("client n°") + oss.str());
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

void	User::setMessage(std::string buf) {

	_message = buf;
}

/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/

void	User::sendMsg(std::string msg) {

	msg += "\r\n";
	write(this->_socket, msg.c_str(), msg.length());
}

bool	User::isRegistered(void) {

	if (this->_registered == REGISTERED)
		return (true);
	return (false);
}
