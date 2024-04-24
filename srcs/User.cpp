/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:54:12 by maxime            #+#    #+#             */
/*   Updated: 2024/04/24 13:54:27 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/User.hpp"

User::User(void) : _socket(0), _username(""), _nickname(""), _buffer("") {

	//std::cout << "User: default constructor\n";
	_isconnected = false;
}

User::User(const User &src) {

	//std::cout << "User: copy constructor\n";
	*this = src;
}

User::User(int socket, std::string username, std::string nickname) : _socket(socket), _username(username), _nickname(nickname), _buffer("") {

	std::cout << "User: socket/name constructor\n";
	_isconnected = true;
}

User::~User(void) {

	//std::cout << "User: destructor\n";
	//close(this->_socket);
}

User	&User::operator=(const User &rhs) {

	//std::cout << "User: copy operator'='\n";
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

// bool	User::isconnect()
// {
// 	if (this->_isconnected == 1)
// 		return true;
// 	return false;
// }

std::string	User::getnickname() const
{
	return _nickname;
}

std::string	User::getusername() const
{
	
	return _username;
}

void	User::setnickname(std::string nickname)
{
	for (int i = 0; nickname[i]; i++)
		if (nickname[i] == '\n')
			nickname[i] = '\0';
	_nickname = nickname;
}

void	User::setusername(std::string username)
{
	for (int i = 0; username[i]; i++)
		if (username[i] == '\n')
			username[i] = '\0';
	_username = username;
}

void	User::send_message(std::list<User> users)
{
	std::list<User>::iterator receiver;
	for (receiver = users.begin(); receiver != users.end(); ++receiver)
	{
		if (_socket != receiver->getsocket() && !_buffer.empty())// && if in_channel
		{
			if (!receiver->getusername().empty()) {
				send(receiver->getsocket(), _username.c_str(), _username.length(), 0);
				send(receiver->getsocket(), " : ", 3, 0);
			}
			send(receiver->getsocket(), _buffer.c_str(), _buffer.length(), 0);
		}
	}
	std::cout << _buffer;
}

