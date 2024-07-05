/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:02:07 by parinder          #+#    #+#             */
/*   Updated: 2024/07/05 16:01:10 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::part(User &actual) {

	std::list<Channel>::iterator chan;

	chan = getChannelIteratorByName(_args[1]);
	if (this->_args.size() < 2) {

		this->reply(NEEDMOREPARAMS(actual, "PART"));
		return;
	}
	else if (chan == this->_channels.end())
        reply(NOSUCHCHAN(actual, this->_args[1]));
    else if (chan->isIn(USER_LIST, actual.getNickname()) == false)
        reply(NOTONCHAN(actual, chan->getName()));
	else {

		chan->sendGroupMsg(PART(actual, chan->getName()));
		clearUserFromChan(actual.getNickname());
		if (chan->getNbUser() < 1)
			this->_channels.erase(chan);
	}
}
