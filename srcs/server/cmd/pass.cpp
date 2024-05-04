/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 03:30:21 by parinder          #+#    #+#             */
/*   Updated: 2024/05/02 16:00:20 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

// a l'appel de pass, verifier si on est pas deja connecter, pareil pour USER et NICK
void	Irc::pass(User &actual)
{
	if (_args[1].empty())
		actual.sendMsg("PASS :Not enough parameters\n");	// test avec la commande 
															// PASS seule a verifier
	else if (_args[1].compare(_password) == 0) {

		if (actual.getRegisteredLevel() == 0) 
			actual.setHigherRegisteredLevel();
	}
	else {

		actual.setLowerRegisteredLevel();
		actual.sendMsg(" :Password incorrect\n");
	}
}
