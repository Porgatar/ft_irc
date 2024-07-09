/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:52:42 by parinder          #+#    #+#             */
/*   Updated: 2024/07/09 15:11:00 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

/* return true if the nickname respect the norm */
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

	if (actual.getRegisteredLevel() == 0) {

		this->reply(NOTREGISTERED(actual));
		return ;
	}
	if (this->_args.size() < 2) {

		this->reply(NONICKNAMEGIVEN(actual));
		return ;
	}
	if (!rfc_nickname(this->_args[1])) {

		this->reply(ERRONEUSNICKNAME(actual, this->_args[1]));
		return ;
	}
	for (it = this->_users.begin(); it != this->_users.end(); it++) {

		if (it->getNickname().compare(this->_args[1].c_str()) == 0) {

			this->reply(NICKNAMEINUSE(actual, this->_args[1]));
			return ;
		}
	}
	if ((actual.getRegisteredLevel() == 2 || actual.getRegisteredLevel() == 1) \
	&& actual.getNickname().empty()) {

		actual.setHigherRegisteredLevel();
		actual.setNickname(this->_args[1]);
		if (actual.getRegisteredLevel() == 3)
			this->reply(WELCOME(actual));
	}
}
