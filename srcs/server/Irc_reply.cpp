/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc_reply.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:21:20 by parinder          #+#    #+#             */
/*   Updated: 2024/05/21 21:28:58 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Irc.hpp"

void	Irc::log(const int log, const std::string &str) {

	if (log == ERROR)
		std::cerr << PRED << str << PRESET << std::endl;
	else if (log == WARNING)
		std::cout << PORANGE << str << PRESET << "\n";
	else if (log == INFO)
		std::cout << PYELLOW << str << PRESET << "\n";
}

void	Irc::reply(const User &user, const int log, const std::string &str) {

	user.sendMsg(str);
	this->log(log, std::string("reply to ") + user.getStringId() + " " + str);
}
