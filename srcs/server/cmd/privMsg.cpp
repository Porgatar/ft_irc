/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:50:04 by parinder          #+#    #+#             */
/*   Updated: 2024/07/04 15:53:48 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

/*Get the first <argument>'s word; who is separated by a isspace*/
// std::string	getWord(std::string argument) {

// 	std::string target;
// 	int			i = 0;

// 	while (argument[i] && !((argument[i] >= 9 && argument[i] <= 13) || argument[i] == 32))
// 		i++;
// 	target = argument.substr(0, i);
// 	return (target);
// }

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

			it->sendMsg(actual.getMessage());
			this->log(PRIVMSG(actual, target, actual.getMessage()));
			return ;	
		}
	}
	for (this->_it = this->_channels.begin(); this->_it != this->_channels.end(); this->_it++) {

		if (this->_it->getName().compare(target.c_str()) == 0) {

			if (this->_it->isIn(USER_LIST, actual.getNickname()) == false)
				this->reply(CANNOTSENDTOCHAN(actual, target));
			this->_it->sendGroupMsg(actual.getMessage());
			this->log(PRIVMSG(actual, target, actual.getMessage()));
			return ;
		}
	}
	this->reply(NOSUCHNICK(actual, target));
}
