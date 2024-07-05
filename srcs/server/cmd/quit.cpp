/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:41:09 by parinder          #+#    #+#             */
/*   Updated: 2024/07/05 19:39:46 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::quit(User &actual) {

	std::list<Channel>::iterator chan;

	chan = this->_channels.begin();
	while (chan != this->_channels.end()) {

		chan->removeUserByNameFrom(OPERATOR_LIST, actual.getNickname());
		chan->removeUserByNameFrom(USER_LIST, actual.getNickname());
		chan->removeUserByNameFrom(INVITE_LIST, actual.getNickname());
		if (chan->getNbUser() < 1) {

			this->_channels.erase(chan);
			chan = this->_channels.begin();
			continue ;
		}
		else
			chan++;
	}
}
