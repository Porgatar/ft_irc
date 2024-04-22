/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:38:59 by parinder          #+#    #+#             */
/*   Updated: 2024/04/22 05:27:57 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <forward_list>

class User;

class Channel {

private:

	Channel(void);

	std::string					_name;
	std::forward_list<User *>	_operators;
	std::forward_list<User *>	_users;
public:

	Channel(const Channel &src);
	Channel(const std::string name, User *user);
	~Channel(void);

	Channel	&operator=(const Channel &rhs);

	void	send_group_msg(std::string msg);
	void	add_user(User *user);
	void	add_operator(User *user);
};
