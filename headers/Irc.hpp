/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:10:03 by parinder          #+#    #+#             */
/*   Updated: 2024/07/05 19:17:25 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC
#define IRC

#include "header.h"
#include "User.hpp"
#include "Channel.hpp"

class Irc {

private:

/*	-	-	-	-	-	private Variables	-	-	-	-	*/
	int								_socket;
	std::string						_password;
	std::list<User>					_users;
	std::list<Channel>				_channels;
	std::vector<std::string>		_args;
/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	Irc(void);
/*	-	-	-	-	-	Private Functions	-	-	-	-	*/
	bool							checkExistingChannel(std::string channels_name);
	bool							checkExistingUser(std::string nickname);
	void							AddUserInChannel(User &user, std::string channels_name);
	void							log(const int log, const std::string &str);
	std::list<Channel>::iterator	getChannelIteratorByName(const std::string &channelName);
	void							reply(const User &user, const int log, const std::string &str);
	int								setSockets(fd_set *set);
	void							checkClientRequest(void);
	void							exec_cmd(User &user);
/*	-	-	-	-	-	Command Functions	-	-	-	-	*/
	void 	cap(User &actual);
	void	join(User &actual);
	void	nick(User &actual);
	void	part(User &actual);
	void	pass(User &actual);
	void    invite(User &actual);
	void	privmsg(User &actual);
	void	user(User &actual);
	void    kick(User &actual);
	void	mode(User &actual);
	void	who(User &actual);
	void	quit(User &actual);
	void	topic(User &actual);
public:

	Channel	getChannel(std::string name);
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

#endif // !IRC
