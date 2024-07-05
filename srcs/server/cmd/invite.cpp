/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:41:52 by parinder          #+#    #+#             */
/*   Updated: 2024/07/05 18:38:33 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void    Irc::invite(User &actual)
{
    std::list<User>::iterator		it;
    std::list<Channel>::iterator	chan;

    chan = getChannelIteratorByName(this->_args[2]);
    if (this->_args.size() < 3)
        this->reply(NEEDMOREPARAMS(actual, "INVITE"));
    else if (checkExistingUser(this->_args[1]) == false)
        this->reply(NOSUCHNICK(actual, this->_args[2], this->_args[1]));
    else if (chan == this->_channels.end())
        this->reply(NOSUCHCHAN(actual, this->_args[2]));
    else if (chan->isIn(USER_LIST, actual.getNickname()) == false)
        this->reply(NOTONCHAN(actual, chan->getName()));
    else if (chan->isIn(OPERATOR_LIST, actual.getNickname()) == false)
        this->reply(CHANOPRIVSNEEDED(actual, chan->getName()));
    else if (chan->isIn(USER_LIST, this->_args[1]) == true)
        this->reply(USERONCHAN(actual, this->_args[1], chan->getName()));
    else {

        for (it = this->_users.begin(); it != this->_users.end(); it++) {

            if (this->_args[1] == it->getNickname())
                break;
        }
        chan->addUserTo(INVITE_LIST, *it);
		it->sendMsg(INVITE(actual, this->_args[1], this->_args[2]));
		this->reply(actual, INFO, INVITE(actual, this->_args[1], this->_args[2]));
    }
}
