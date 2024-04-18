/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:49:49 by maxime            #+#    #+#             */
/*   Updated: 2024/04/18 10:56:07 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include <iostream>

class User
{
    private:
    
        int         _socket;
        std::string _username;
        std::string _nickname;
        
    public:
        User();
        User(const User &src);
        User& operator=(const User &src);

        ~User();

        int getsocket() const;

};



#endif