/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:49:49 by maxime            #+#    #+#             */
/*   Updated: 2024/05/08 15:24:40 by mdesrose         ###   ########.fr       */
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
	std::string	_message;
public:

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	User(void);
	User(const User &src);	
/*	-	-	-	-	-	Destructors	-	-	-	-	-	-	*/
	~User(void);
/*	-	-	-	-	-	Operators	-	-	-	-	-	-	*/
	User				&operator=(const User &rhs);
/*	-	-	-	-	-	Getters	-	-	-	-	-	-	-	*/
	const int			&getSocket(void) const;
	const int			&getRegisteredLevel(void) const;
	const std::string	getStringId(void) const;
	const std::string	&getBuffer(void) const;
	const std::string	&getNickname(void) const;
	const std::string	&getUsername(void) const;
	const std::string	&getMessage(void) const;
	
/*	-	-	-	-	-	Setters	-	-	-	-	-	-	-	*/
	void				setMessage(std::string str);
	void				setSocket(int fd);
	void				setHigherRegisteredLevel(void);
	void				setLowerRegisteredLevel(void);
	void				setUsername(std::string username);
	void				setNickname(std::string nickname);
	void				setBuffer(std::string buf);
	void				setMessage(std::string buf);
/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/
	void				sendMsg(std::string msg);
	bool				isRegistered(void);
};
