/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:37:08 by maxime            #+#    #+#             */
/*   Updated: 2024/05/02 16:58:48 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

std::vector<std::string> split_space(std::string s) {
    
    size_t pos_start = 0;
    size_t pos_end;
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(" ", pos_start)) != std::string::npos) {
        if (s[pos_start] == ' ') {
            pos_start++;   
            continue;
        }
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + 1;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    return res;
}

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
            for (int i = 4; i < _args.size(); i++)
                msg += " " + _args[i];
        }
        _it->kickuser(_args[2], msg);
    }
}