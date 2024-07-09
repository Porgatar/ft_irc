/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 03:30:21 by parinder          #+#    #+#             */
/*   Updated: 2024/07/09 19:09:50 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::pass(User &actual)
{
	if (this->_args.size() < 2)
		this->reply(NEEDMOREPARAMS(actual, "PASS"));
	else if (this->_args[1] == this->_password) {

		if (actual.getRegisteredLevel() == 0) {
			actual.setHigherRegisteredLevel();
		}
	}
	else {

		actual.setLowerRegisteredLevel();
		this->reply(PASSWDMISMATCH(actual));
	}
}
