/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:52:42 by parinder          #+#    #+#             */
/*   Updated: 2024/05/02 16:01:13 by maxime           ###   ########.fr       */
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

	if (_args[1].empty()) {

		actual.sendMsg(" :No nickname given\n");
		return ;
	}
	if (!rfc_nickname(_args[1])) {
		actual.sendMsg(_args[1] + " :Erroneus nickname\n");
		return ;
	}
	for (it = _users.begin(); it != _users.end(); it++) {

		if (it->getNickname().compare(_args[1].c_str()) == 0) {
			actual.sendMsg(_args[1] + " :Nickname is already in use\n");
			return ;
		}
	}
	if ((actual.getRegisteredLevel() == 2 || actual.getRegisteredLevel() == 1) \
												&& actual.getNickname().empty()) {
		actual.setHigherRegisteredLevel();
		actual.setNickname(_args[1]);
	}
}
