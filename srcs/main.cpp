/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:05:07 by maxime            #+#    #+#             */
/*   Updated: 2024/04/24 19:37:12 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/header.h"
#include "../headers/Irc.hpp"

int main(int ac, char **av)
{
	if (ac == 3)
	{
		Irc	server(av[1], av[2]);
		server.loop_for_connection();
		return (0);
	}
	std::cerr << PRED << "Error\ninvalid format\n" \
		<< "usage: ./ircserv <port> <password>" << PRESET << std::endl;
	return (-1);
}
