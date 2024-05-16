#include "../../../headers/Irc.hpp"

//TODO : messages d'erreurs
void    Irc::invite(User &actual)
{
    std::list<User>::iterator it;

    if (_args.size() < 3)
        return; //a changer
    else if (checkExistingUser(_args[1]) == false)
        return;
    else if (checkExistingChannel(_args[2]) == false)
        return;
    //si ce user est sur le channel ou il souhaite inviter quelquun
    else if (getChannelIteratorByName(_args[2])->isIn(USER_LIST, actual.getNickname()) == false)
        return;
    else if (getChannelIteratorByName(_args[2])->isIn(USER_LIST, _args[1]) == true)
        return;
    else {
        for (it = _users.begin(); it != _users.end(); it++) {
            if (_args[1] == it->getNickname())
                break;
        }
        getChannelIteratorByName(_args[2])->addUserTo(INVITE_LIST, *it);
    }
}