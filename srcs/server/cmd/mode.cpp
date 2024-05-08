/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:37:48 by parinder          #+#    #+#             */
/*   Updated: 2024/05/08 17:06:59 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::mode(User &actual) {

	std::list<Channel>::iterator	channel;
	std::string						mode("itkol");
	std::string						tmp;
	size_t							len;

	len = this->_args.size();
	if (len > 1)
		channel = this->getChannelIteratorByName(this->_args[1]);
	if (len == 1 || channel == this->_channels.end()) {

		if (len == 1)
			tmp = actual.getNickname() + "  :No such channel";
		else
			tmp = actual.getNickname() + " " + this->_args[1] + " :No such channel";
		actual.sendMsg(tmp);
		this->log(WARNING, std::string("server: request from ") + actual.getStringId() + \
			" '" + tmp + "'");
	}
	else if (len == 2) {

		tmp = actual.getNickname() + " " + this->_args[1] + " ";
		for (int i = 0; i < 5; i++) {

			std::string c;

			c = mode[i];
			if (channel->getMode(i))
				tmp = tmp + "+" + c;
			else
				tmp = tmp + "-" + c;
		}
		actual.sendMsg(tmp);
		this->log(WARNING, std::string("server: request from ") + actual.getStringId() + \
			" '" + tmp + "'");
	}
	for (size_t i = 2; i <= len; i++)
		std::cout << "arg mode request\n";
}
