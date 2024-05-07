/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:37:48 by parinder          #+#    #+#             */
/*   Updated: 2024/05/07 20:05:14 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::mode(User &actual) {

	std::list<Channel>::iterator	channel;
	std::string						channelName("");
	std::string						tmp;
	size_t							len;
	char							mode[6] = {"itkol"};

	len = _args.size();
	if (len > 1)
	{
		channelName = _args[1];
		channel = this->getChannelIteratorByName(channelName);
	}
	if (len == 1 || channel == this->_channels.end()) {

		actual.sendMsg(actual.getNickname() + " " + channelName + " :No such channel");
		this->log(WARNING, std::string("server: request from ") + actual.getStringId() + \
			" '" + actual.getNickname() + " " + channelName + " :No such channel'");
	}
	else if (len == 2) {

		tmp = actual.getNickname() + " " + channelName + " ";
		for (int i = 0; i < 5; i++)
			if (channel->getMode(i))
				tmp += mode[i];
		actual.sendMsg(tmp);
		this->log(WARNING, std::string("server: request from ") + actual.getStringId() + \
			" " + tmp);
	}
	else {
		//	setting current mode to + or -.
		std::cout << "setting mode...\n";
	}
}
