/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 03:21:05 by parinder          #+#    #+#             */
/*   Updated: 2024/05/16 05:48:31 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::join(User &user) {

	std::list<std::string>::iterator	it;
    std::list<std::string> 				cmds;
    size_t 								start = 0;
    size_t 								end = 0;
	if (_args.size() < 2) {
		user.sendMsg("JOIN :Not enough parameters");
        return;
	}
	if (_args[1][end] != '&' && _args[1][end] != '#') {
		user.sendMsg("Channel begin with & or #");
        return;
	}
    while (end < _args[1].size()) {
		
        while (end < _args[1].size() && _args[1][end] != '&' && _args[1][end] != '#')
            end++;
        if (end < _args[1].size()) {
            size_t next = end + 1;
            while (next < _args[1].size() && _args[1][next] != ',')
                next++;
			if (_args[1][next] == ',' && _args[1][next + 1] != '&' && _args[1][next + 1] != '#') {

				user.sendMsg("no comma allowed");
				return ;
			}
			if (_args[1][0 + start] != '&' && _args[1][0 + start] != '#') {
       			user.sendMsg("Channel begin with & or #");
        		return;
   			}
            std::string channel_name = _args[1].substr(start, next - start);
            cmds.push_back(channel_name);
            start = next + 1;
        }
        end = start;
    }
	for (it = cmds.begin(); it != cmds.end(); it++) {
		if (!(checkExistingChannel(*it))) {
			Channel	channel(*it, user);
			_channels.push_back(channel);
			channel.sendGroupMsg(user.getNickname() + " is joining the channel " + channel.getName());
		}
		else
			AddUserInChannel(user, *it);
	}
	// if (_args.size() >= 3) {
		
	// }
}
