/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:37:08 by maxime            #+#    #+#             */
/*   Updated: 2024/07/04 20:24:18 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void    Irc::kick(User &actual) {
    
    std::list<Channel>::iterator it;
    std::string msg = " :has been kicked"; 

    if (this->_args.size() < 3) {

		this->reply(NEEDMOREPARAMS(actual, "KICK"));
        return ;    
    }
    for (it = this->_channels.begin(); it != this->_channels.end(); it++)
        if (it->getName() == this->_args[1])
            break ;
    if (it == this->_channels.end())
		this->reply(NOSUCHCHAN(actual, this->_args[1]));
    else if (!it->getUserByNameFrom(USER_LIST, this->_args[2]))
		this->reply(USERNOTINCHAN(actual, this->_args[2], this->_args[1]));
    else if (!it->isIn(OPERATOR_LIST, actual.getNickname()))
		this->reply(CHANOPRIVSNEEDED(actual, this->_args[1]));
    else if (this->_args.size() >= 4 && this->_args[3][0] != ':')
        this->reply(actual, WARNING, "kick message begin with \':\'");
    else if (this->_args[2] == actual.getNickname())
        this->reply(actual, WARNING, "You cannot kick yourself");
    else {

        if (this->_args.size() >= 4) {

            actual.setMessage(skip_words(3, actual.getMessage()));
            actual.setMessage(actual.getMessage().substr(1));
            it->sendGroupMsg(KICK(actual, this->_args[1], this->_args[2]) + " " \
			+ actual.getMessage());
        }
		else
            it->sendGroupMsg(KICK(actual, this->_args[1], this->_args[2]));
		it->removeUserByNameFrom(USER_LIST, this->_args[2]);
		it->removeUserByNameFrom(OPERATOR_LIST, this->_args[2]);
    }
}
