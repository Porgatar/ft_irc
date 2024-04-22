/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:54:12 by maxime            #+#    #+#             */
/*   Updated: 2024/04/22 05:17:39 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/User.hpp"

User::User(void) : _socket(0), _username(""), _nickname(""), _buffer("") {

	std::cout << "User: default constructor\n";
};

User::User(const User &src) {

	std::cout << "User: copy constructor\n";
	*this = src;
}

User::User(int socket, std::string username, std::string nickname) : _socket(socket), _username(username), _nickname(nickname), _buffer("") {

	std::cout << "User: socket/name constructor\n";
    // std::cout << ;
    // std::cout << ;
    // std::cout << ;
    // std::cout << ;
    // std::cout << ;
}

User::~User(void) {

	std::cout << "User: destructor\n";
};

User	&User::operator=(const User &rhs) {

	std::cout << "User: copy operator'='\n";
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
