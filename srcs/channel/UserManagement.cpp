/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserManagement.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 00:05:32 by parinder          #+#    #+#             */
/*   Updated: 2024/05/13 14:59:48 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Channel.hpp"

void	Channel::sendGroupMsg(const std::string &msg) {

	std::list<User>::iterator	it;

	for (it = this->_users[USER].begin(); it != this->_users[USER].end(); it++)
		it->sendMsg(msg);
}

void	Channel::removeFrom(const int &list, const std::string &nick) {

	std::list<User>::iterator it;

	for (it = this->_users[list].begin(); it != this->_users[list].end(); it++) {

		if (nick == it->getNickname()) {

			this->_users[list].erase(it);
			return ;
		}
	}
}

void	Channel::kickuser(const std::string &nick, const std::string &message) {

	std::list<User>::iterator it;

	for (it = _users[USER].begin(); it != _users[USER].end(); it++) {

		if (nick == it->getNickname()) {

			this->sendGroupMsg(it->getNickname() + " " + message + "\n");
			this->_users[USER].erase(it);
			//	le user doit aussi etre remove des operateur?
			this->removeFrom(OPERATOR, nick);
			return ;
		}
	}
}
