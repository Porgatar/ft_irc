/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:42:01 by mdesrose          #+#    #+#             */
/*   Updated: 2024/05/16 06:51:26 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void    Irc::topic(User &user) {
    
    std::list<Channel>::iterator it;
    
    if (_args.size() < 2) {
        user.sendMsg("TOPIC :Not enough parameters");
        return ;
    }
    if (!(checkExistingChannel(_args[1]))) {
        user.sendMsg(_args[1] + " :No such channel");
        return ;   
    }
    it = getChannelIteratorByName(_args[1]);
    if ((it->getMode(T) && it->isIn(OPERATOR_LIST, user.getNickname())) || it->getMode(T) == false) {
        if (_args.size() < 3 && it->getTopic() == "")
            user.sendMsg(_args[1] + " :No topic is set");
        else if (_args.size() < 3)
            user.sendMsg(_args[1] + " : " + it->getTopic());
        else if (_args.size() == 3 && _args[2] == ":" && it->getUserByNameFrom(USER_LIST, user.getNickname()))
            it->setTopic("");
        else if (_args.size() == 3 && it->getUserByNameFrom(USER_LIST, user.getNickname()))
            it->setTopic(_args[2]);
    }
    else 
        user.sendMsg(it->getName() + " :You're not channel operator");
}
