/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserManagement.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 00:05:32 by parinder          #+#    #+#             */
/*   Updated: 2024/05/08 15:53:04 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Channel.hpp"

bool	Channel::isOperator(const std::string &nick) {
	
	std::list<User>::iterator it;

	for (it = this->_operators.begin(); it != this->_operators.end(); it++)
		if (nick == it->getNickname())
			return (true);
	return (false);
}

bool	Channel::isUser(const std::string &nick) {
	
	std::list<User>::iterator it;

	for (it = this->_users.begin(); it != this->_users.end(); it++)
		if (nick == it->getNickname())
			return (true);
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
