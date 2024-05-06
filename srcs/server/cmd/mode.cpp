/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:37:48 by parinder          #+#    #+#             */
/*   Updated: 2024/05/06 19:16:41 by parinder         ###   ########.fr       */
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
	}
	else if ()
}
