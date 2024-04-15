/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:30:30 by parinder          #+#    #+#             */
/*   Updated: 2024/04/16 00:51:19 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../headers/Irc.hpp"

int	main(int ac, char **av){

	Irc	server(1234);
	Irc	server1("5678");
	if (ac > 1)
	{
		Irc	server2(av[1]);
		Irc	server3(server2);
	}

	std::cout << "server instance up\n";
	return (0);
}
