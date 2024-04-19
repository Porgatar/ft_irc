/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:49:49 by maxime            #+#    #+#             */
/*   Updated: 2024/04/19 14:36:31 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #pragma once

#include <iostream>

class User {

private:

	int			_socket;
	std::string	_username;
	std::string	_nickname;
	std::string	_buffer;
public:

	User	*next;

	User(void);
	User(const User &src);
	~User(void);

	User	&operator=(const User &rhs);

	int	getsocket() const;
	void	setsocket(int fd);
};
