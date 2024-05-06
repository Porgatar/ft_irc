/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:37:48 by parinder          #+#    #+#             */
/*   Updated: 2024/05/06 19:57:12 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::mode(User &actual) {

	std::string	tmp("");
	size_t		len;

	len = _args.size();
	if (len > 1)
		tmp = _args[1];
	if (len == 1 || !this->checkExistingChannel(tmp)) {

		actual.sendMsg(tmp + " :No such channel");
		this->log(actual.getStringId() + " " + tmp + " :No such channel");
		return ;
	}
	else if (len == 2) {

//		actual.sendMsg(tmp + " " + );
//		this->log(actual.getStringId() + " " + tmp + " :");
		//	need to create channel member function getMode();
	}
}
