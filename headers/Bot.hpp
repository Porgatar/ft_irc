/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:11:49 by parinder          #+#    #+#             */
/*   Updated: 2024/05/16 18:36:46 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

class	Bot {

private:
/*	-	-	-	-	-	private Variables	-	-	-	-	-	*/
	int			_socket;
	std::string	_password;
/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	Bot(void);

public:
/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	Bot(const Bot &src);
	Bot(const std::string port, const std::string password);
/*	-	-	-	-	-	Destructors	-	-	-	-	-	*/
	~Bot(void);
/*	-	-	-	-	-	Operators	-	-	-	-	-	*/
	Bot	&operator=(const Bot &rhs);
/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/
	void	run(void);

}
