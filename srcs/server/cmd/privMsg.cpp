/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:50:04 by parinder          #+#    #+#             */
/*   Updated: 2024/07/04 20:08:51 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::privmsg(User &actual) {

	std::list<User>::iterator 		it;
	std::list<Channel>::iterator 	ite;
	std::string						target;
	
	if (this->_args.size() == 1) {

		this->reply(NORECIPIENT(actual));
		return ;
	}
	if (this->_args.size() == 2) {

		this->reply(NOTEXTTOSEND(actual));
		return ;
	}
	target = this->_args[1];
	actual.setMessage(skip_words(2, actual.getMessage()));
	for (it = this->_users.begin(); it != this->_users.end(); it++) {

		if (it->getNickname().compare(target.c_str()) == 0) {

			it->sendMsg(PRIVMSG(actual, target, actual.getMessage()));
			return ;	
		}
	}
	for (ite = this->_channels.begin(); ite != this->_channels.end(); ite++) {

		if (ite->getName().compare(target.c_str()) == 0) {

			if (ite->isIn(USER_LIST, actual.getNickname()) == false) {

				this->reply(CANNOTSENDTOCHAN(actual, target));
				return ;
			}
			ite->sendGroupMsg(GROUPPRIVMSG(actual, target, actual.getMessage()));
			return ;
		}
	}
	this->reply(NOSUCHNICK(actual, target));
}
