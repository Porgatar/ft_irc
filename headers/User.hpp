/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:49:49 by maxime            #+#    #+#             */
/*   Updated: 2024/04/24 22:25:31 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <list>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <cstring>

#include "header.h"

class User {

private:

/*	-	-	-	-	-	member variables	-	-	-	-	*/
	int			_socket;
	int			_registered;
	std::string	_username;
	std::string	_nickname;
	std::string	_buffer;
public:

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	User(void);
	User(int socket, std::string username, std::string nickname);
	User(const User &src);	

/*	-	-	-	-	-	Destructors	-	-	-	-	-	-	*/
	~User(void);

/*	-	-	-	-	-	Operators	-	-	-	-	-	-	*/
	User		&operator=(const User &rhs);

/*	-	-	-	-	-	Getters	-	-	-	-	-	-	-	*/
	int					getSocket(void) const;
	int					getRegisteredLevel(void) const;
	const std::string	&getBuffer(void) const;
	const std::string	&getNickname(void) const;
	const std::string	&getUsername(void) const;

/*	-	-	-	-	-	Setters	-	-	-	-	-	-	-	*/
	void		setSocket(int fd);
	void		setHigherRegisteredLevel(void);
	void		setUsername(std::string username);
	void		setNickname(std::string nickname);
	void		setBuffer(std::string buf);

/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/
	void		sendMsg(std::list<User> users);
	bool		isRegistered(void);
};
