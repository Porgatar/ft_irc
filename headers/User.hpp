/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:49:49 by maxime            #+#    #+#             */
/*   Updated: 2024/04/27 00:11:20 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.h"

class User {

private:

/*	-	-	-	-	-	private variables	-	-	-	-	*/
	int			_socket;
	int			_registered;
	std::string	_username;
	std::string	_nickname;
	std::string	_buffer;
public:

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	User(void);
	User(const User &src);	
/*	-	-	-	-	-	Destructors	-	-	-	-	-	-	*/
	~User(void);
/*	-	-	-	-	-	Operators	-	-	-	-	-	-	*/
	User				&operator=(const User &rhs);
/*	-	-	-	-	-	Getters	-	-	-	-	-	-	-	*/
	int					getSocket(void) const;
	int					getRegisteredLevel(void) const;
	const std::string	&getBuffer(void) const;
	const std::string	&getNickname(void) const;
	const std::string	&getUsername(void) const;
/*	-	-	-	-	-	Setters	-	-	-	-	-	-	-	*/
	void				setSocket(int fd);
	void				setHigherRegisteredLevel(void);
	void				setLowerRegisteredLevel(void);
	void				setUsername(std::string username);
	void				setNickname(std::string nickname);
	void				setBuffer(std::string buf);
/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/
	void				sendMsg(std::string msg);
	bool				isRegistered(void);
};
