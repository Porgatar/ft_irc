/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:37:48 by parinder          #+#    #+#             */
/*   Updated: 2024/07/06 16:58:16 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::mode(User &actual) {

	std::list<Channel>::iterator	channel;
	std::string						modes("itklo");
	std::string						tmp("");
	size_t							len;
	bool							state;
	int								modeIndex;
	User							*user;

	len = this->_args.size();
	if (len > 1)
		channel = this->getChannelIteratorByName(this->_args[1]);
	if (len == 1 || channel == this->_channels.end()) {

		if (len == 1)
			this->reply(NOSUCHCHAN(actual, ""));
		else
			this->reply(NOSUCHCHAN(actual, this->_args[1]));
		return ;
	}
	else if (len == 2) {

		tmp = "+";
		if (channel->getMode(I))
			tmp += "i";
		if (channel->getMode(T))
			tmp += "t";
		if (!channel->getKey().empty())
			tmp += "k";
		if (channel->getUserLimit())
			tmp += "l";
		if (tmp.length() == 1)
			tmp.clear();
		this->reply(CHANMODEIS(actual, this->_args[1], tmp));
		return ;
	}
	if (!channel->getUserByNameFrom(OPERATOR_LIST, actual.getNickname())) {

		this->reply(CHANOPRIVSNEEDED(actual, this->_args[1]));
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

				this->reply(UNKNOWNMODE(actual, this->_args[1][j + 1]));
				return ;
			}
			if (modes[modeIndex] == 'k') {	// if is mode 'k' set a new channel password

				if (state && i + 1 < len)
					channel->setKey(this->_args[i + 1]);
				else if (!state)
					channel->setKey("");
				channel->sendGroupMsg(MODE(actual, this->_args[1], this->_args[i][j] + \
				modes[modeIndex], "*"));
				i++;
				break ;
			}
			if (modes[modeIndex] == 'o') {	// if is mode 'o' set a new channel operator.

				user = 0;
				if (i + 1 < len)
					user = channel->getUserByNameFrom(USER_LIST, this->_args[i + 1]);
				if (!user) {

					if (i + 1 < len)
						tmp = this->_args[i + 1];
					this->reply(NOSUCHNICK(actual, this->_args[1], tmp));
					return ;
				}
				else if (state) {

					channel->addUserTo(OPERATOR_LIST, *user);
					channel->sendGroupMsg(MODE(actual, this->_args[1], this->_args[i][j] \
					+ modes[modeIndex], user->getNickname()));
				}
				else if (!state) {

					if (actual.getNickname() != user->getNickname()) {

						channel->removeUserByNameFrom(OPERATOR_LIST, user->getNickname());
						channel->sendGroupMsg(MODE(actual, this->_args[1], this->_args[i][j] \
						+ modes[modeIndex], user->getNickname()));
					}
					else
						this->reply(actual, WARNING, std::string(":") + channel->getName() \
						+ " :you cannot remove oprivilege on yourself");
				}
				i++;
				break ;
			}
			if (modes[modeIndex] == 'l') {	// if is mode 'l' set a new userLimit.

				if (state && i + 1 < len) {

					std::stringstream	ss(this->_args[i + 1]);
					int					limit;

					ss >> limit;
					ss.str("");
					ss.clear();
					ss << limit;
					channel->setUserLimit(limit);
					channel->sendGroupMsg(MODE(actual, this->_args[1], '+' \
					+ modes[modeIndex], ss.str()));
				}
				else if (!state) {

					channel->setUserLimit(0);
					channel->sendGroupMsg(MODE(actual, this->_args[1], '-' \
					+ modes[modeIndex], ""));
				}
				i++;
				break ;
			}
			channel->setMode(modeIndex, state);
			channel->sendGroupMsg(MODE(actual, this->_args[1], this->_args[i][j] \
			+ modes[modeIndex], ""));
		}
	}
}
