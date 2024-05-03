/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:05:07 by maxime            #+#    #+#             */
/*   Updated: 2024/05/03 23:14:36 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/header.h"
#include "../headers/Irc.hpp"

//catching server global pointer to destroy class instance
static void	ft_exit(int sig)
{
	std::cout << PRED << "server: server shutdown..." << PRESET << std::endl;
	g_IrcPtr->~Irc();
	exit(0);
}

int main(int ac, char **av)
{
	if (ac == 3)
	{
		Irc	server(av[1], av[2]);
		server.setSigintHandler(ft_exit);
		server.run();
		return (0);
	}
	std::cerr << PRED << "Error\ninvalid format\n" \
		<< "usage: ./ircserv <port> <password>" << PRESET << std::endl;
	return (-1);
}
