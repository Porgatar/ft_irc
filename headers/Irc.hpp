/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:10:03 by parinder          #+#    #+#             */
/*   Updated: 2024/04/16 00:53:09 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class Irc {

private:

	int	_socket;
public:

	Irc(void);
	Irc(const Irc &src);
	Irc(const std::string port);
	Irc(const int port);
	~Irc(void);

	Irc	&operator=(const Irc &rhs);
};
