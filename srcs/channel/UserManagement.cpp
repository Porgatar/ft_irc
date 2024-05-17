/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserManagement.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 00:05:32 by parinder          #+#    #+#             */
/*   Updated: 2024/05/17 14:40:01 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Channel.hpp"

void	Channel::sendGroupMsg(const std::string &msg) {

	std::list<User>::iterator	it;

	for (it = this->_users[USER_LIST].begin(); it != this->_users[USER_LIST].end(); it++)
		it->sendMsg(msg);
}

void	Channel::removeUserByNameFrom(const int &list, const std::string &nick) {

	std::list<User>::iterator it;

	if (list >= 0 && list <= 2) {

		for (it = this->_users[list].begin(); it != this->_users[list].end(); it++) {

			if (nick == it->getNickname()) {
				if (list == USER_LIST)
					decrementNbUser();
				this->_users[list].erase(it);
				return ;
			}
		}
	}
}

void	Channel::kickuser(const std::string &nick, const std::string &message) {

	std::list<User>::iterator it;

	for (it = _users[USER_LIST].begin(); it != _users[USER_LIST].end(); it++) {

		if (nick == it->getNickname()) {

			this->sendGroupMsg(it->getNickname() + " " + message + "\n");
			this->_users[USER_LIST].erase(it);
			decrementNbUser();
			//	le user doit aussi etre remove des operateur?
			this->removeUserByNameFrom(OPERATOR_LIST, nick);
			return ;
		}
	}
}
