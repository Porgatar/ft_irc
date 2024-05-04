/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:10:03 by parinder          #+#    #+#             */
/*   Updated: 2024/05/04 21:11:57 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.h"
#include "User.hpp"
#include "Channel.hpp"

#define ERROR	101
#define WARNING	102
#define DEBUG	103
#define INFO	104

class Irc {

private:

/*	-	-	-	-	-	private Variables	-	-	-	-	*/
	int								_socket;
	std::string						_password;
	std::list<User>					_users;
	std::list<Channel>				_channels;
	std::list<Channel>::iterator	_it;
	std::vector<std::string>		_args;
/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	Irc(void);
/*	-	-	-	-	-	Private Functions	-	-	-	-	*/
	void	checkClientRequest(void);
	void	exec_cmd(User &user);
	int		setSockets(fd_set *set);
	void	addUser(int socket);
	void	log(int log, const std::string &str);
/*	-	-	-	-	-	Command Functions	-	-	-	-	*/
	void 	cap(User &user);
	void	join(User &actual);
	void	nick(User &actual);
	void	pass(User &actual);
	void	privmsg(User &actual);
	void	user(User &actual);
	void    kick(User &actual);
	bool	checkExistingChannel(User &user, std::string channels_name);
public:

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	Irc(const Irc &src);
	Irc(const std::string port, const std::string password);
/*	-	-	-	-	-	Destructors	-	-	-	-	-	-	*/
	~Irc(void);
/*	-	-	-	-	-	Operators	-	-	-	-	-	-	*/
	Irc			&operator=(const Irc &rhs);
/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/
	void	setSigintHandler(void (*handler)(int));
	void	run(void);
};

extern Irc	*g_IrcPtr;

typedef void (Irc::*function_p)(User &);
