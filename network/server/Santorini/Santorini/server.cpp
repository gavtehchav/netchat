#include "accepter.h"
#include "queue.h"
#include "list.h"
#include "receiver.h"
#include "util.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include "server.h"


int main()
{
    Queue<std::string> queue;
    List<std::shared_ptr<sf::TcpSocket>> sockets;
    // TODO launch an accepter thread.
    std::thread(Accepter(queue,sockets)).detach();

    while(1)
    {
        std::string s = queue.pop(); // s is the message
        std::cout << "Main read: \"" << s << "\"\n";
        // TODO send to all in sockets. Be careful to synchronise.
        // 1 Lambda
        // 2 call for_each
        auto send_to_one = [&](std::shared_ptr<sf::TcpSocket> socket) {
            if(socket->send(s.c_str(), s.size() + 1) != sf::Socket::Done) 
            {
                //error

                std::cerr << "Error sending\n";
                return;
            }
        };
        sockets.for_each(send_to_one);
    }
    return 0;
}