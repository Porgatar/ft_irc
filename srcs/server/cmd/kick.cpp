/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:37:08 by maxime            #+#    #+#             */
/*   Updated: 2024/05/06 18:15:29 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void    Irc::kick(User &actual) {
    
    std::string msg = " :has been kicked"; 

    if (_args.size() < 3) {
        actual.sendMsg("KICK :Not enough parameters");
        return ;    
    }
    for (_it = _channels.begin(); _it != _channels.end(); _it++) {
        if (_it->getName() == _args[1])
            break ;
    }
    if (_it == _channels.end())
        actual.sendMsg(_args[1] + " :No such channel");
    else if (_it->isConnected(_args[2]) == false)
        actual.sendMsg(_args[2] + " " + _it->getName() + " :They aren't on that channel");
    else if (_args.size() >= 4 && _args[3][0] != ':')
        actual.sendMsg("kick message begin with \':\'");
    else {
        if (_args.size() > 3) {
	        actual.setMessage(skip_words(3, actual.getMessage()));
            _it->kickuser(_args[2], actual.getMessage());
        }
        else
            _it->kickuser(_args[2], msg);
    }
}
