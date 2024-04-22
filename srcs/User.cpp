/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:54:12 by maxime            #+#    #+#             */
/*   Updated: 2024/04/22 01:10:18 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/User.hpp"

User::User(void) : _socket(0), _username(""), _nickname(""), _buffer("") {};

User::User(int socket, std::string username, std::string nickname) : _socket(socket), _username(username), _nickname(nickname), _buffer("")
{
	_isconnected = 1;
    // std::cout << ;
    // std::cout << ;
    // std::cout << ;
    // std::cout << ; 
    // std::cout << ;
}

User::User(const User &src) {

	*this = src;
}

User::~User(void) {};

User	&User::operator=(const User &rhs) {

	this->_socket = rhs._socket;
	this->_username = rhs._username;
	this->_nickname = rhs._nickname;
	this->_buffer = rhs._buffer;
	return (*this);
}

int	User::getsocket() const {

	return this->_socket;
}

void	User::setsocket(int fd) {

	this->_socket = fd;
}

void	User::setbuffer(char *buf)
{
	std::string convert(buf);
	this->_buffer = convert;
}

std::string	User::getbuffer() const
{
	return this->_buffer;
}

bool	User::isconnect()
{
	if (this->_isconnected == 1)
		return true;
	return false;
}