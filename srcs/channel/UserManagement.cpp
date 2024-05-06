/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserManagement.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 00:05:32 by parinder          #+#    #+#             */
/*   Updated: 2024/05/06 17:03:10 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Channel.hpp"

bool	Channel::isConnected(std::string nick) {
	
	std::list<User>::iterator it;

	for (it = _users.begin(); it != _users.end(); it++) {
		if (nick.compare(it->getNickname().c_str()) == 0)
			return (true);
	}
	return (false);
}

void	Channel::kickuser(std::string nick, std::string message) {
	
	std::list<User>::iterator it;
	
	for (it = _users.begin(); it != _users.end(); it++) {
		if (nick == it->getNickname()) {
			this->sendGroupMsg(it->getNickname() + " " + message + "\n");
			_users.erase(it);
			return ;
		}
	}
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
