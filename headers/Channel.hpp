/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:38:59 by parinder          #+#    #+#             */
/*   Updated: 2024/05/14 17:47:23 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.h"
#include "User.hpp"

class Channel {

private:

	std::string		_name;
	std::string		_topic;
	bool			_modes[5];
	std::list<User>	_users[3];
	
public:

	Channel(void);
	Channel(const Channel &src);
	Channel(const std::string &name, const User &user);
	~Channel(void);

	Channel	&operator=(const Channel &rhs);
	
	const std::string	&getName(void) const ;
	const std::string	&getTopic(void) const ;
	const bool			&getMode(const int &mode) const ;
	bool				isIn(const int &list, const std::string &nick);

	void	setTopic(const std::string &name);
	void	setMode(const int &mode, const bool &state);
	void	addTo(const int &list, const User &user);

	void	sendGroupMsg(const std::string &msg);
	void	removeFrom(const int &list, const std::string &nick);
	void	kickuser(const std::string &nick, const std::string &msg);
};
