/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:50:04 by parinder          #+#    #+#             */
/*   Updated: 2024/06/26 14:05:01 by maxime           ###   ########.fr       */
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
	for (_it = _channels.begin(); _it != _channels.end(); _it++) {
		if (_it->getName().compare(target.c_str()) == 0) {
			if (_it->isIn(USER_LIST, actual.getNickname()) == false)
				actual.sendMsg(target + " :You are not in channel");
			_it->sendGroupMsg(actual.getMessage());
			return ;
		}
	}
	actual.sendMsg(target + " :No such nick/channel");
}
