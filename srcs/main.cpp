/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:05:07 by maxime            #+#    #+#             */
/*   Updated: 2024/04/18 15:17:43 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../headers/Irc.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "usage :./exe <port> <password>\n";
        return (-1);
    }
    
    Irc irc(argv[1], "password");
    
    if (irc.create_server() == -1)
    {
        std::cerr << "server failed\n";   
        return (-1);
    }
    irc.loop_for_connection();
    // close(sock);
    return (0);
}