/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:50:04 by parinder          #+#    #+#             */
/*   Updated: 2024/06/30 14:16:01 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::privmsg(User &actual) {

	std::list<User>::iterator 		it;
	std::list<Channel>::iterator 	ite;
	std::string						target;
	
	if (_args.size() == 1) {
		actual.sendMsg(" :No recipient given");
		return ;
	}
	if (_args.size() == 2) {
		actual.sendMsg(" :No text to send");
		return ;
	}
	target = _args[1];
	actual.setMessage(skip_words(2, actual.getMessage()));
	for (it = _users.begin(); it != _users.end(); it++) {
		if (it->getNickname().compare(target.c_str()) == 0) {
			it->sendMsg(actual.getMessage());
			return ;	
		}
	}
	for (ite = _channels.begin(); ite != _channels.end(); ite++) {
		if (ite->getName().compare(target.c_str()) == 0) {
			if (ite->isIn(USER_LIST, actual.getNickname()) == false)
				actual.sendMsg(target + " :You are not in channel");
			ite->sendGroupMsg(actual.getMessage());
			return ;
		}
	}
	actual.sendMsg(target + " :No such nick/channel");
}
