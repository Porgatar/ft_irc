/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:10:03 by parinder          #+#    #+#             */
/*   Updated: 2024/04/30 19:25:59 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.h"
#include "User.hpp"
#include "Channel.hpp"
#include "Utils.h"

class Irc {

private:

/*	-	-	-	-	-	private Variables	-	-	-	-	*/
	int					_socket;
	std::string			_password;
	std::list<User>		_users;
	std::list<Channel>	_channels;
	std::list<Channel>::iterator _it;
/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	Irc(void);
/*	-	-	-	-	-	Private Functions	-	-	-	-	*/
	void	checkClientRequest(void);
	void	exec_cmd(User &user);
	int		setSockets(fd_set *set);
	void	addUser(int socket);
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

std::string	skip_isspace(std::string str); //temporary

extern Irc	*g_IrcPtr;

typedef void (Irc::*function_p)(User &);
std::string	getWord(std::string argument);