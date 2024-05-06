/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:05:07 by maxime            #+#    #+#             */
/*   Updated: 2024/05/06 14:52:32 by mdesrose         ###   ########.fr       */
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

static int is_isspace(char c) {

    if (c >= 9 && c <= 13 || c == ' ')
        return (1);
    return (0);
}

//n is the number of arguments we want to skip
std::string	get_message(int n, const std::string &str) {

	int	words = 0;
    int i = 0;

	while (words < n) {
		while (!(is_isspace(str[i])))
            i++;
        while (is_isspace(str[i]))
            i++;
        words++;
	}
    return (&str[i]);
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
