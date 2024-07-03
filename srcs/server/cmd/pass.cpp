/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 03:30:21 by parinder          #+#    #+#             */
/*   Updated: 2024/07/03 18:20:50 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

// a l'appel de pass, verifier si on est pas deja connecter, pareil pour USER et NICK
void	Irc::pass(User &actual)
{
	if (this->_args.size() < 2)
		this->reply(NEEDMOREPARAMS(actual, "PASS"));
	else if (this->_args[1] == this->_password) {

		if (actual.getRegisteredLevel() == 0) {

			actual.setHigherRegisteredLevel();
//			this->reply(WELCOME(actual));
		}
	}
	else {

		actual.setLowerRegisteredLevel();
		this->reply(PASSWDMISMATCH(actual));
	}
}
