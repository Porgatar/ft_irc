/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:37:08 by maxime            #+#    #+#             */
/*   Updated: 2024/06/30 16:02:22 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void    Irc::kick(User &actual) {
    
    std::list<Channel>::iterator it;
    std::string msg = " :has been kicked"; 

    if (_args.size() < 3) {
        actual.sendMsg("KICK :Not enough parameters");
        return ;    
    }
    for (it = _channels.begin(); it != _channels.end(); it++) {
        if (it->getName() == _args[1])
            break ;
    }
    if (it == _channels.end())
        actual.sendMsg(_args[1] + " :No such channel");
    else if (!it->getUserByNameFrom(USER_LIST, _args[2]))
        actual.sendMsg(_args[2] + " " + it->getName() + " :They aren't on that channel");
    else if (!it->isIn(OPERATOR_LIST, actual.getNickname()))
        actual.sendMsg(":You are not operator");
    else if (_args.size() >= 4 && _args[3][0] != ':')
        actual.sendMsg("kick message begin with \':\'");
    else if (_args[2] == actual.getNickname())
        actual.sendMsg("You cannot kick yourself");
    else {
        if (_args.size() >= 4) {
            actual.setMessage(skip_words(3, actual.getMessage()));
            actual.setMessage(actual.getMessage().substr(1));
            it->kickuser(_args[2], actual.getMessage());
        }
        else
            it->kickuser(_args[2], msg);
    }
}
