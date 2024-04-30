/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:37:08 by maxime            #+#    #+#             */
/*   Updated: 2024/04/30 21:40:09 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"
#include <vector>

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
    
    std::vector<std::string> 	    cmds;
    std::string 				    argument;
    std::string                     tmp; 

    tmp = " :has been kicked";
	argument = actual.getBuffer();
    if (argument != "")
        argument.erase(std::remove(argument.begin(), argument.end(), '\n'), argument.end());
    cmds = split_space(argument);
    if (cmds.size() < 2) {
        actual.sendMsg("KICK :Not enough parameters\n");
        return ;
    }
    else if (cmds.size() > 2) 
        tmp.erase(0, 19);
    if (cmds.size() >= 2) {
        for (_it = _channels.begin(); _it != _channels.end(); _it++) {
            if (_it->getName() == cmds[0])
                break ;
        }
        if (_it == _channels.end()) {
            actual.sendMsg(cmds[0] + " :No such channel\n");
            return ;
        }
        if (_it->isConnected(cmds[1]) == false) {
            actual.sendMsg(cmds[1] + " " + _it->getName() + " :They aren't on that channel\n");
            return ;
        }
        for (int i = 2; i < cmds.size(); i++) {
            if (cmds[2][0] != ':') {
                actual.sendMsg("kick message begin with \':\'\n");
                return ;   
            }
            else 
                tmp += cmds[i] + " ";
        }
        tmp.erase(0, 1);
        _it->kickuser(cmds[1], tmp);
    }
}