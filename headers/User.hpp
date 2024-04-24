/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:49:49 by maxime            #+#    #+#             */
/*   Updated: 2024/04/24 12:59:47 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <cstring>

class User {

private:

	bool		_isconnected;
	int			_socket;
	std::string	_username;
	std::string	_nickname;
	std::string	_buffer;
	
public:

	User();
	User(int socket, std::string username, std::string nickname);
	User(const User &src);	
	~User(void);

	User		&operator=(const User &rhs);

	int			getsocket() const;
	std::string	getbuffer() const;
	std::string	getnickname() const;
	std::string	getusername() const;
	
	void		setusername(std::string username);
	void		setnickname(std::string nickname);
	void		setsocket(int fd);
	void		setbuffer(char *buf);
	void		send_message(std::list<User> users);


};
