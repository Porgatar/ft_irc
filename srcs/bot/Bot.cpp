/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:10:50 by parinder          #+#    #+#             */
/*   Updated: 2024/05/16 18:52:13 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/Bot.hpp"

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/

Bot::Bot(void) : _socket(0), _password("") {};

Bot::Bot(const Bot &src) : _socket(src._socket), _password(src._password) {}

Bot::Bot(const std::string s_port, const std::string password) \
	: _socket(0), _password(password) {

	int	port;

	port = atoi(s_port.c_str());
	if (port < 1024 || port > 65535) {

		std::cout << PRED << "Error\n" << s_port << " is out of range\nrange: 1024 - 65535" << \
			PRESET << std::endl;
	}
}
