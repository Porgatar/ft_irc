/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 03:30:21 by parinder          #+#    #+#             */
/*   Updated: 2024/04/30 03:33:04 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

// a l'appel de pass, verifier si on est pas deja connecter, pareil pour USER et NICK
void	Irc::pass(User &actual)
{
	std::string	argument;

	argument = actual.getBuffer();
	argument.erase(std::remove(argument.begin(), argument.end(), '\n'), argument.end());
	argument = skip_isspace(argument);
	if (argument.empty())
		actual.sendMsg("PASS :Not enough parameters\n");	// test avec la commande 
															// PASS seule a verifier
	else if (argument.compare(_password) == 0) {

		if (actual.getRegisteredLevel() == 0) 
			actual.setHigherRegisteredLevel();
	}
	else {

		actual.setLowerRegisteredLevel();
		actual.sendMsg(" :Password incorrect\n");
	}
}
