/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 03:21:05 by parinder          #+#    #+#             */
/*   Updated: 2024/04/30 19:27:19 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

bool	Irc::checkExistingChannel(User &user, std::string channels_name)
{
	std::list<Channel>::iterator		it;

	for (it = _channels.begin(); it != _channels.end(); it++) {

		if (it->getName().compare(channels_name.c_str()) == 0) {

			if (it->isConnected(user.getNickname()) == false) {

				it->addUser(user);
				it->sendGroupMsg(user.getNickname() + " is joining the channel " + it->getName() + "\n");
			}
			return (true);
		}
	}
	return (false);
}

void	Irc::join(User &user) {

	std::list<std::string>::iterator	it;
    std::list<std::string> 				cmds;
    std::string 						argument;

	argument = user.getBuffer();
    argument.erase(std::remove(argument.begin(), argument.end(), '\n'), argument.end());
    if (argument[0] != '&' && argument[0] != '#') {

        user.sendMsg("Channel begin with & or #\n"); // TEMPORAIRE
        return;
    }
    size_t start = 0;
    size_t end = 0;
    while (end < argument.size() && argument[end] != ' ') {

        while (end < argument.size() && argument[end] != '&' && argument[end] != '#')
            end++;
        if (end < argument.size()) {

            size_t next = end + 1;
            while (next < argument.size() && argument[next] != ',' && argument[next] != ' ')
                next++;
			if (argument[next] == ',' && argument[next + 1] != '&' && argument[next + 1] != '#') {

				user.sendMsg("no comma allowed\n");
				return ;
			}
			/*si argument [next] == espace, regarder si il ya une clé apres, sinon retourner une erreur*/
            std::string channel_name = argument.substr(start, next - start);
            cmds.push_back(channel_name);
            start = next + 1;
        }
        end = start;
    }
	for (it = cmds.begin(); it != cmds.end(); it++) {

		if (!(checkExistingChannel(user, *it))) {

			Channel	channel(*it, user);
			_channels.push_back(channel);
			channel.sendGroupMsg(user.getNickname() + " is joining the channel " \
														+ channel.getName() + "\n");
		}
	}
}
