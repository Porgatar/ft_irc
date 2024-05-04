/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 04:06:33 by parinder          #+#    #+#             */
/*   Updated: 2024/05/02 15:38:09 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/Irc.hpp"

void	Irc::user(User &actual) {

	//.	argument.erase(std::remove(argument.begin(), argument.end(), '\n'), argument.end());
	if ((actual.getRegisteredLevel() == 2 || actual.getRegisteredLevel() == 1) && actual.getUsername() == "") {
		actual.setHigherRegisteredLevel();
		actual.setUsername(actual.getBuffer());
	}
}
