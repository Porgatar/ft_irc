#include "../../../headers/Irc.hpp"

//TODO : messages d'erreurs
void    Irc::invite(User &actual)
{
    std::list<User>::iterator it;
    std::list<Channel>::iterator chan;

    chan = getChannelIteratorByName(_args[2]);
    if (_args.size() < 3)
        actual.sendMsg("Not enough param");
    else if (checkExistingUser(_args[1]) == false)
        actual.sendMsg(_args[1] + " :No such nick/channel");
    else if (chan == _channels.end())
        reply(NOSUCHCHANNEL(actual, _args[2]));
    else if (chan->isIn(USER_LIST, actual.getNickname()) == false)
        reply(NOTONCHANNEL_ERR(actual, chan->getName()));
    else if (chan->isIn(OPERATOR_LIST, actual.getNickname()) == false)
        reply(ERR_CHANOPRIVSNEEDED(actual, chan->getName()));
    else if (chan->isIn(USER_LIST, _args[1]) == true)
        reply(ERR_USERONCHANNEL(actual, _args[1], chan->getName()));
    else {
        for (it = _users.begin(); it != _users.end(); it++) {
            if (_args[1] == it->getNickname())
                break;
        }
        chan->addUserTo(INVITE_LIST, *it);
        actual.sendMsg(it->getNickname() + " has been invited to channel : " + _args[2]);
    }
}