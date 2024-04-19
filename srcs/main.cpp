/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:05:07 by maxime            #+#    #+#             */
/*   Updated: 2024/04/19 13:10:57 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../headers/Irc.hpp"

# define PRED		"\033[0;31m"
# define PRESET		"\033[0m"

int main(int ac, char **av)
{
	if (ac == 3)
	{
		Irc	server(av[1], av[2]);
		server.loop_for_connection();
		std::cout << "server instance up\n";
		return (0);
	}
	std::cerr << PRED << "Error, invalid format\n";
	std::cerr << "format: ./ircserv <port> <password>" << PRESET << std::endl;
	return (-1);
}
