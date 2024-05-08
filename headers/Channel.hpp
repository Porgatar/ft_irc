/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:38:59 by parinder          #+#    #+#             */
/*   Updated: 2024/05/08 15:05:12 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.h"
#include "User.hpp"

class Channel {

private:

	std::string		_name;
	bool			_mode[5];
	std::list<User>	_operators;
	std::list<User>	_users;
public:

	Channel(void);
	Channel(const Channel &src);
	Channel(const std::string name, User user);
	~Channel(void);

	Channel	&operator=(const Channel &rhs);

	const std::string	&getName(void) const ;
	const bool			&getMode(const int &mode) const ;

	void	setMode(const int &mode, const bool &state);

	void	sendGroupMsg(std::string msg);
	void	addUser(User &user);
	void	addOperator(User &user);
	bool	isConnected(std::string nick);
	void	kickuser(std::string nick, std::string message);
};
