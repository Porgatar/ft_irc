/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:37:08 by maxime            #+#    #+#             */
/*   Updated: 2024/05/06 13:59:35 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void    Irc::kick(User &actual) {
    
    std::string msg = " :has been kicked"; 

    if (_args.size() < 3) {
        actual.sendMsg("KICK :Not enough parameters\n");
        return ;    
    }
    for (_it = _channels.begin(); _it != _channels.end(); _it++) {
        if (_it->getName() == _args[1])
            break ;
    }
    if (_it == _channels.end())
        actual.sendMsg(_args[1] + " :No such channel\n");
    else if (_it->isConnected(_args[2]) == false)
        actual.sendMsg(_args[2] + " " + _it->getName() + " :They aren't on that channel\n");
    else if (_args.size() >= 4 && _args[3][0] != ':')
        actual.sendMsg("kick message begin with \':\'\n");
    else {
        if (_args[3] != "")
            msg = _args[3];
        if (_args.size() >= 5) {
            for (size_t i = 4; i < _args.size(); i++)
                msg += " " + _args[i];
        }
        _it->kickuser(_args[2], msg);
    }
}
