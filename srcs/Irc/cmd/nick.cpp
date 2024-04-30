/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:52:42 by parinder          #+#    #+#             */
/*   Updated: 2024/04/30 03:51:05 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

/*return true if the nickname respect the norm*/
static bool rfc_nickname(const std::string& str) {

    const std::string set = "([{{|\\}}])";

    for (int i = 0; str[i]; i++) {
        if (isalnum(str[i]) || set.find(str[i]) != std::string::npos)
            continue;
        else
			return false;
    }
    return true;
}

void	Irc::nick(User &actual) {

	std::list<User>::iterator	it;
	std::string					argument;

	argument = actual.getBuffer();
	argument.erase(std::remove(argument.begin(), argument.end(), '\n'), argument.end());
	if (argument.empty()) {

		actual.sendMsg(" :No nickname given\n");
		return ;
	}
	if (!rfc_nickname(argument)) {

		actual.sendMsg(argument + " :Erroneus nickname\n");
		return ;
	}
	for (it = _users.begin(); it != _users.end(); it++) {

		if (it->getNickname().compare(argument.c_str()) == 0) {

			actual.sendMsg(argument + " :Nickname is already in use\n");
			return ;
		}
	}
	if ((actual.getRegisteredLevel() == 2 || actual.getRegisteredLevel() == 1) \
												&& actual.getNickname().empty()) {
		actual.setHigherRegisteredLevel();
		actual.setNickname(argument);
	}
}
