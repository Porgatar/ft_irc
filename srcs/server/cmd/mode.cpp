/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:37:48 by parinder          #+#    #+#             */
/*   Updated: 2024/05/16 07:18:37 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::mode(User &actual) {

	std::list<Channel>::iterator	channel;
	std::string						modes("itklo");
	std::string						tmp;
	size_t							len;
	bool							state;
	int								modeIndex;
	User							*user;

	len = this->_args.size();
	if (len > 1)
		channel = this->getChannelIteratorByName(this->_args[1]);
	if (len == 1 || channel == this->_channels.end()) {

		if (len == 1)
			tmp = actual.getNickname() + "  :No such channel";
		else
			tmp = actual.getNickname() + " " + this->_args[1] + " :No such channel";
		actual.sendMsg(tmp);
		this->log(WARNING, std::string("reply to ") + actual.getStringId() +" " + tmp);
		return ;
	}
	else if (len == 2) {

		std::string c;

		tmp = actual.getNickname() + " " + this->_args[1] + " ";
		c = "+";
		if (channel->getMode(I))
			c += "i";
		if (channel->getMode(T))
			c += "t";
		if (!channel->getKey().empty())
			c += "k";
		if (channel->getUserLimit())
			c += "l";
		if (c.length() > 1)
			tmp += c;
		actual.sendMsg(tmp);
		this->log(WARNING, std::string("reply to ") + actual.getStringId() + " " + tmp);
		return ;
	}
	if (!channel->getUserByNameFrom(OPERATOR_LIST, actual.getNickname())) {

		tmp = actual.getNickname() + " " + this->_args[1] + " :You're not channel operator";
		actual.sendMsg(tmp);
		this->log(WARNING, std::string("reply to ") + actual.getStringId() + " " + tmp);
		return ;
	}
	for (size_t i = 2; i < len; i++) {

		for (size_t j = 0; this->_args[i][j]; j++) {

			if (this->_args[i][j] == '+' || this->_args[i][j] == '-')
				state = this->_args[i][j] % 3;	// sets true for '+' and false for '-'.
			else
				continue ;
			modeIndex = modes.find(this->_args[i][j + 1], 0);
			if (modeIndex == -1) {

				tmp = actual.getNickname() + " " + this->_args[1][j + 1] + \
					" :is unknown mode char to me";
				actual.sendMsg(tmp);
				this->log(WARNING, std::string("reply to ") + actual.getStringId() + " " + tmp);
				return ;
			}
			if (modes[modeIndex] == 'k') {	// if is mode 'l' set a new userLimit.

				if (i + 1 < len)
					channel->setKey(this->_args[i + 1]);
				i++;
				break ;
			}
			if (modes[modeIndex] == 'o') {	// if is mode 'o' set a new channel operator.

				user = 0;
				if (i + 1 < len)
					user = channel->getUserByNameFrom(USER_LIST, this->_args[i + 1]);
				if (!user) {

					if (i + 1 < len)
						tmp = actual.getNickname() + " " + this->_args[i + 1] + " :Unknown user";
					else
						tmp = actual.getNickname() + "  :Unknown user";
					actual.sendMsg(tmp);
					this->log(WARNING, std::string("reply to ") + actual.getStringId() + \
						" " + tmp);
					return ;
				}
				else if (state)
					channel->addUserTo(OPERATOR_LIST, *user);
				else if (!state)
					channel->removeUserByNameFrom(OPERATOR_LIST, user->getNickname());
				i++;
				break ;
			}
			if (modes[modeIndex] == 'l') {	// if is mode 'l' set a new userLimit.

				if (i + 1 < len)
					channel->setUserLimit(atoi(this->_args[i + 1].c_str()));
				i++;
				break ;
			}
			channel->setMode(modeIndex, state);
		}
	}
}
