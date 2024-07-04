/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:42:01 by mdesrose          #+#    #+#             */
/*   Updated: 2024/07/04 20:59:58 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void    Irc::topic(User &user) {
    
    std::list<Channel>::iterator it;
    
    if (this->_args.size() < 2) {

		this->reply(NEEDMOREPARAMS(user, "TOPIC"));
        return ;
    }
    if (!(checkExistingChannel(this->_args[1]))) {

		this->reply(NOSUCHCHAN(user, this->_args[1]));
        return ;   
    }
    it = getChannelIteratorByName(this->_args[1]);
    if (!it->isIn(USER_LIST, user.getNickname())) {

		this->reply(NOTONCHAN(user, this->_args[1]));
        return;
    }
    if (this->_args.size() < 3 && it->getTopic() == "")
		this->reply(NOTOPIC(user, this->_args[1]));
    else if (this->_args.size() < 3)
		this->reply(SEETOPIC(user, this->_args[1], it->getTopic()));
    else if (!it->getMode(T) || (it->getMode(T) && it->isIn(OPERATOR_LIST, user.getNickname()))) {

		this->_args[2].substr(1);
		it->setTopic(this->_args[2]);
		it->sendGroupMsg(TOPIC(user, it->getName(), this->_args[2]));
    }
    else 
		this->reply(CHANOPRIVSNEEDED(user, this->_args[1]));
}
