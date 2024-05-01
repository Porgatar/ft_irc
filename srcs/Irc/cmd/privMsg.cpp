/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:50:04 by parinder          #+#    #+#             */
/*   Updated: 2024/05/01 01:18:33 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

/*Get the first <argument>'s word; who is separated by a isspace*/
std::string	getWord(std::string argument) {

	std::string target;
	int			i = 0;

	while (argument[i] && !((argument[i] >= 9 && argument[i] <= 13) || argument[i] == 32))
		i++;
	target = argument.substr(0, i);
	return (target);
}

//buggggggggggg
void	Irc::privmsg(User &actual) {

	std::list<User>::iterator 	it;
	std::string 				argument;
	std::string					target;
	std::string					message;
	bool						finded;
	
	finded = false;
	argument = actual.getBuffer();
	target = getWord(argument);
	// target = argument.substr(0, argument.find(' ', 0));
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
	// std::cout << it->getNickname() << std::endl;
}
