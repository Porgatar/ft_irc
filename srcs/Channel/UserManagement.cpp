/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserManagement.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 00:05:32 by parinder          #+#    #+#             */
/*   Updated: 2024/04/30 00:12:54 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Channel.hpp"

bool	Channel::isConnected(User &user) {
	
	std::list<User>::iterator it;

	for (it = _users.begin(); it != _users.end(); it++) {

		if (user.getNickname().compare(it->getNickname().c_str()) == 0) {

			write(user.getSocket(), "User already connected\n", 23);	
			return (true);
		}
	}
	return (false);
}

void	Channel::sendGroupMsg(std::string msg) {

	std::list<User>::iterator	it;

	for (it = _users.begin(); it != _users.end(); it++) {

		write(it->getSocket(), msg.c_str(), msg.size());
	}
}

void	Channel::addUser(User &user) {

	this->_users.push_back(user);
}

void	Channel::addOperator(User &user) {

	this->_operators.push_back(user);
}
