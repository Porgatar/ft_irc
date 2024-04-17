/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:30:30 by parinder          #+#    #+#             */
/*   Updated: 2024/04/17 03:21:16 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../headers/header.h"
#include "../headers/Irc.hpp"

int	main(int ac, char **av){

	if (ac == 3)
	{
		Irc	server(av[1], av[2]);
		std::cout << "server instance up\n";
		return (0);
	}
	std::cerr << PRED << "Error, invalid format\n";
	std::cerr << "format: ./ircserv <port> <password>" << PRESET << std::endl;
	return (-1);
}
