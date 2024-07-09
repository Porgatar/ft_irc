/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 04:06:33 by parinder          #+#    #+#             */
/*   Updated: 2024/07/09 15:10:57 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::user(User &actual) {

	if (actual.getRegisteredLevel() == 0) {
		actual.sendMsg("Enter password first");
		return ;
	}
	if ((actual.getRegisteredLevel() == 2 || actual.getRegisteredLevel() == 1) && actual.getUsername() == "") {
		actual.setHigherRegisteredLevel();
		actual.setUsername(actual.getBuffer());
		if (actual.getRegisteredLevel() == 3)
			this->reply(WELCOME(actual));
	}
}
