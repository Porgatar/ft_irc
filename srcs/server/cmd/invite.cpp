#include "../../../headers/Irc.hpp"

//TODO : messages d'erreurs
void    Irc::invite(User &actual)
{
    std::list<User>::iterator it;
    std::list<Channel>::iterator chan;

    if (_args.size() < 3)
        return; //a changer
    else if (checkExistingUser(_args[1]) == false)
        return;
    else if (checkExistingChannel(_args[2]) == false)
        return;
    chan = getChannelIteratorByName(_args[2]);
    //si ce user est sur le channel ou il souhaite inviter quelquun
    if (chan->isIn(USER_LIST, actual.getNickname()) == false)
        return; // n'est pas dans le canal
    else if (chan->isIn(OPERATOR_LIST, actual.getNickname()) == false)
        return; // nest pas operateur du canal
    else if (chan->isIn(USER_LIST, _args[1]) == true)
        return; // si il est deja dans le canal
    for (it = _users.begin(); it != _users.end(); it++) {
        if (_args[1] == it->getNickname())
            break;
    }
    chan->addUserTo(INVITE_LIST, *it);
    actual.sendMsg(it->getNickname() + " has been invited to channel : " + _args[2]);
}