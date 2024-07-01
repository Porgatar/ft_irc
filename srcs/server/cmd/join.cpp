/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 03:21:05 by parinder          #+#    #+#             */
/*   Updated: 2024/07/01 18:54:54 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::join(User &user) {

	std::list<std::string>::iterator	it;
	std::list<Channel>::iterator		chan;
    std::list<std::string> 				channelsName;
    std::vector<std::string> 			keys;
	std::vector<std::string>::iterator	indexKey;
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
	// boucle qui parse les channel separer par une virgule
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
			if (_args[1][start] != '&' && _args[1][start] != '#') {
       			user.sendMsg("Channel begin with & or #");
        		return;
   			}
            std::string channel_name = _args[1].substr(start, next - start);
            channelsName.push_back(channel_name);
            start = next + 1;
        }
        end = start;
    }
	start = 0;
	end = 0;
	if (_args.size() >= 3) {
		while (end < _args[2].size()) {
			while (end < _args[2].size() && _args[2][end] != ',') 
				end++;
			size_t next = end + 1;
			if (_args[2][next] == ',') {
				user.sendMsg("No consecutive commas allowed");
				return;
			}
			std::string key_name = _args[2].substr(start, end - start);
			keys.push_back(key_name);
			end = next;
			start = next;
		}
	}
	int i = 0;
	for (it = channelsName.begin(); it != channelsName.end(); it++) {
		if (!(checkExistingChannel(*it))) {
			Channel	channel(*it, user);
			channel.sendGroupMsg(user.getNickname() + " is joining the channel " + channel.getName());
			_channels.push_back(channel);
		}
		else {
			chan = getChannelIteratorByName(*it);
			if (chan->isIn(USER_LIST, user.getNickname()) == true)
        		reply(USERONCHANNEL(user, user.getNickname(), chan->getName()));
			else if (chan->getMode(I) == true && chan->isIn(INVITE_LIST, user.getNickname()) == false)
				user.sendMsg(user.getNickname() + " " + chan->getName() + " :Cannot join channel (+i)");
			else if (chan->getKey().empty() == false && _args.size() < 3)
				user.sendMsg("Need a key");
			else if (chan->getKey().empty() == false && chan->getKey() != keys[i])
				user.sendMsg(user.getNickname() + " " + chan->getName() + " :Cannot join channel (+k)");
			else if (chan->getUserLimit() != 0 && chan->getNbUser() >= chan->getUserLimit())
				user.sendMsg(user.getNickname() + " " + chan->getName() + " :Cannot join channel (+l)");
			else {
				std::cerr << "chan userlimit" << chan->getUserLimit() << " nb user: " 	<< chan->getNbUser();
				chan->addUserTo(USER_LIST, user);
				chan->sendGroupMsg(user.getNickname() + " is joining the channel " + chan->getName());
				chan->incrementNbUser();
			}
		}
		i++;
	}
}
