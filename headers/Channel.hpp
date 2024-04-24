/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:38:59 by parinder          #+#    #+#             */
/*   Updated: 2024/04/23 18:50:24 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <list>
#include "User.hpp"

class User;

class Channel {

private:


	std::string		_name;
	std::list<User>	_operators;
	std::list<User>	_users;
public:

	Channel(void);
	Channel(const Channel &src);
	Channel(const std::string name, User user);
	~Channel(void);

	Channel	&operator=(const Channel &rhs);

	void	send_group_msg(std::string msg);
	void	add_user(User user);
	void	add_operator(User user);
};
