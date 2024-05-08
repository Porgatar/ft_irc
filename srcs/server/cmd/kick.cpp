/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:37:08 by maxime            #+#    #+#             */
/*   Updated: 2024/05/08 15:22:42 by mdesrose         ###   ########.fr       */
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
        actual.sendMsg(_args[1] + " :No such channel\n");
    else if (it->isConnected(_args[2]) == false)
        actual.sendMsg(_args[2] + " " + it->getName() + " :They aren't on that channel\n");
    else if (_args.size() >= 4 && _args[3][0] != ':')
        actual.sendMsg("kick message begin with \':\'");
    else {
        if (_args[3] != "") {
            actual.setMessage(get_message(3, actual.getMessage()));
            actual.setMessage(actual.getMessage().substr(1));
        }
        it->kickuser(_args[2], msg);
    }
}
