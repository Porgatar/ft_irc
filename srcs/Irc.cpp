/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/04/17 03:14:38 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Irc.hpp"

Irc::Irc(void){};

Irc::Irc(const Irc &src) {

	*this = src;
}

Irc::Irc(const std::string port, const std::string password) {

	this->_socket = atoi(port.c_str()); // temporary
	this->_password = password;
}

Irc::~Irc(void){};

Irc	&Irc::operator=(const Irc &rhs) {

	this->_socket = rhs._socket;
	this->_password = rhs._password;
	return (*this);
}
