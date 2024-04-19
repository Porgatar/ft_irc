/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:38:59 by parinder          #+#    #+#             */
/*   Updated: 2024/04/18 00:07:41 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Channel {

private:

	std::string	_name;
	User		*_operators;
	User		*_users;
public:

	User	*next;

	Channel(void);
	Channel(const Channel &src);
	~Channel(void);

	Channel	&operator=(const Channel &rhs);
};
