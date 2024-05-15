/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:38:59 by parinder          #+#    #+#             */
/*   Updated: 2024/05/15 18:33:23 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.h"
#include "User.hpp"

class Channel {

private:

	std::string		_name;
	std::string		_key;
	std::string		_topic;
	bool			_modes[2];
	std::list<User>	_users[3];
	size_t			_userLimit;

public:

	Channel(void);
	Channel(const Channel &src);
	Channel(const std::string &name, const User &user);
	~Channel(void);

	Channel	&operator=(const Channel &rhs);
	
	const std::string	&getName(void) const ;
	const std::string	&getKey(void) const ;
	const std::string	&getTopic(void) const ;
	bool				getMode(const int &mode) const ;
	User				*getUserByNameFrom(const int &list, const std::string &nick);
	const size_t		&getUserLimit(void) const ;

	void	setKey(const std::string &key);
	void	setTopic(const std::string &name);
	void	setMode(const int &mode, const bool &state);
	void	addUserTo(const int &list, const User &user);
	void	setUserLimit(const size_t &userLimit);

	void	sendGroupMsg(const std::string &msg);
	void	removeUserByNameFrom(const int &list, const std::string &nick);
	void	kickuser(const std::string &nick, const std::string &msg);
};
