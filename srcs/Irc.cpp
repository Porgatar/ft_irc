/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/04/16 00:53:53 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Irc.hpp"

Irc::Irc(void){};

Irc::Irc(const Irc &src) {

	*this = src;
}

Irc::Irc(const std::string port) {

	this->_socket = atoi(port.c_str()); // temporary
}

Irc::Irc(const int port) {

	this->_socket = port; // temporary
}

Irc::~Irc(void){};

Irc	&Irc::operator=(const Irc &rhs) {

	this->_socket = rhs._socket;
	return (*this);
}
