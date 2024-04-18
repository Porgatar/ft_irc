/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:54:12 by maxime            #+#    #+#             */
/*   Updated: 2024/04/18 11:15:22 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/User.hpp"

User::User()
{
}

User::User(const User &src)
{
}

User& User::operator=(const User &src)
{
    if (this != &src)
    {
        // TODO: Implement copy assignment
    }
    return *this;
}

User::~User() {
    // TODO: Implement destructor
}

int User::getsocket() const
{
    return this->_socket;
}