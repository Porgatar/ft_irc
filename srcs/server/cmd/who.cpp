/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:05:11 by parinder          #+#    #+#             */
/*   Updated: 2024/07/04 17:12:51 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::who(User &user) {

	std::list<Channel>::iterator	chan;

	chan = this->getChannelIteratorByName(this->_args[1]);
	if (chan == this->_channels.end())
		return ;
	this->reply(NAMES(user, chan->getName(), chan->getUsersString()));
	this->reply(ENDOFNAMES(user, chan->getName()));
}
