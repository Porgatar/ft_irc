/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserManagement.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 00:05:32 by parinder          #+#    #+#             */
/*   Updated: 2024/07/04 20:13:05 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Channel.hpp"

void	Channel::sendGroupMsg(User &user, bool selfSend, const std::string& msg) {

	std::list<User>::iterator	it;

	for (it = this->_users[USER_LIST].begin(); it != this->_users[USER_LIST].end(); it++)
		if (selfSend || it->getNickname() != user.getNickname())
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
