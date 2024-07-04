/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 03:21:05 by parinder          #+#    #+#             */
/*   Updated: 2024/07/04 14:35:51 by maxime           ###   ########.fr       */
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
	
	if (this->_args.size() < 2) {

		this->reply(NEEDMOREPARAMS(user, "PASS"));
        return;
	}
	if (this->_args[1][end] != '&' && this->_args[1][end] != '#') {

		this->reply(BADCHANMASK(user, this->_args[1]));
        return;
	}
	// boucle qui parse les channel separer par une virgule
    while (end < this->_args[1].size()) {

        while (end < this->_args[1].size() && this->_args[1][end] != '&' \
		&& this->_args[1][end] != '#')
            end++;
        if (end < this->_args[1].size()) {
            size_t next = end + 1;
            while (next < this->_args[1].size() && this->_args[1][next] != ',')
                next++;
			if (this->_args[1][next] == ',' && this->_args[1][next + 1] != '&' \
			&& this->_args[1][next + 1] != '#') {

				this->reply(BADCHANMASK(user, this->_args[1]));
				return ;
			}
			if (this->_args[1][start] != '&' && this->_args[1][start] != '#') {

				this->reply(BADCHANMASK(user, this->_args[1]));
        		return;
   			}
            std::string channel_name = this->_args[1].substr(start, next - start);

            channelsName.push_back(channel_name);
            start = next + 1;
        }
        end = start;
    }
	start = 0;
	end = 0;
	if (this->_args.size() >= 3) {

		while (end < this->_args[2].size()) {

			while (end < this->_args[2].size() && this->_args[2][end] != ',') 
				end++;
			size_t next = end + 1;
			if (this->_args[2][next] == ',') {

				this->reply(user, WARNING, "No consecutive commas allowed");
				return;
			}
			std::string key_name = this->_args[2].substr(start, end - start);
			keys.push_back(key_name);
			end = next;
			start = next;
		}
	}	
	int i = 0;
	for (it = channelsName.begin(); it != channelsName.end(); it++) {

		if (!(checkExistingChannel(*it))) {

			Channel	channel(*it, user);

			this->reply(JOIN(user, channel.getName()));
			this->reply(NAMES(user, channel.getName(), channel.getUsersString()));
			this->reply(ENDOFNAMES(user, channel.getName()));
			this->_channels.push_back(channel);
		}
		else {

			chan = getChannelIteratorByName(*it);
			if (chan->isIn(USER_LIST, user.getNickname()) == true)
        		reply(USERONCHAN(user, user.getNickname(), chan->getName()));
			else if (chan->getMode(I) == true \
			&& chan->isIn(INVITE_LIST, user.getNickname()) == false)
				this->reply(INVITEONLYCHAN(user, chan->getName()));
			else if (chan->getKey().empty() == false && _args.size() < 3)
				this->reply(BADCHANKEY(user, chan->getName()));
			else if (chan->getKey().empty() == false && chan->getKey() != keys[i])
				this->reply(BADCHANKEY(user, chan->getName()));
			else if (chan->getUserLimit() != 0 && chan->getNbUser() >= chan->getUserLimit())
				this->reply(CHANISFULL(user, chan->getName()));
			else {
<<<<<<< HEAD
=======

				chan->sendGroupMsg(user.getNickname() + " is joining the channel " \
				+ chan->getName());
				this->reply(JOIN(user, chan->getName()));
				this->reply(NAMES(user, chan->getName(), chan->getUsersString()));
				this->reply(ENDOFNAMES(user, chan->getName()));
>>>>>>> 3d628bf14606eee6534f1973e8824ce0528322fa
				chan->addUserTo(USER_LIST, user);
				chan->incrementNbUser();
			}
		}
		i++;
	}
}
