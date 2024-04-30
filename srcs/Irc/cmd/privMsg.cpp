/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:50:04 by parinder          #+#    #+#             */
/*   Updated: 2024/04/30 04:12:41 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

static std::string	gettarget(std::string argument) {

	std::string target;
	int			i = 0;

	while (!((argument[i] >= 9 && argument[i] <= 13) || argument[i] == 32))
		i++;
	target = argument.substr(0, i);
	return (target);
}

void	Irc::privmsg(User &actual) {

	std::list<User>::iterator 	it;
	std::string 				argument;
	std::string					target;
	std::string					message;
	bool						finded;
	
	finded = false;
	argument = actual.getBuffer();
	target = gettarget(argument);
	if (target.empty()) {

		actual.sendMsg(" :No recipient given\n");
		return ;
	}
	for (it = _users.begin(); it != _users.end(); it++) {

		if (it->getNickname().compare(target.c_str()) == 0)
			finded = true;
	}
	message = argument.substr(target.length(), argument.length() - target.length());
	message = skip_isspace(message);
	if (message.empty()) {

		actual.sendMsg(" :No text to send\n");
		return ;
	}
	if (target[0] == '&' || target[0] == '#') {

		finded = true;
		for (std::list<Channel>::iterator ite = _channels.begin(); ite != _channels.end(); ite++) {

			if (ite->getName().compare(target.c_str()) == 0) {

				ite->sendGroupMsg(message);
				return ;
			}
		}
		// write(actual.getSocket(), "")
	}
	if (!finded)
		actual.sendMsg(target + " :No such nick\n");
	else
		it->sendMsg(message + "\n");
}
