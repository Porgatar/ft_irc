/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:10:03 by parinder          #+#    #+#             */
/*   Updated: 2024/04/17 17:10:27 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/select.h>

class Irc {

private:

	Irc(void);

	int			_socket;
	std::string	_password;
public:

	Irc(const Irc &src);
	Irc(const std::string port, const std::string password);
	~Irc(void);

	Irc	&operator=(const Irc &rhs);
};
