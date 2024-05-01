#include "queue.h"
#include "receiver.h"
#include "util.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include "client.h"

int main()
{
    std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();
    // sf::Socket::Status status = socket->connect("152.105.66.60", PORT);
    sf::Socket::Status status = socket->connect("127.0.0.1", PORT);
    if (status != sf::Socket::Done) {
        return 1;
    }
    std::cout << "Connected\n";
    Queue<std::string> queue;
    // TODO launch a receiver thread to receive messages from the server.

    Receiver R(socket, queue);
    std::thread recv_thread(&Receiver::recv_loop, &R);

    std::string s = "";
    while (1)
    {
        std::getline(std::cin, s);
        std::cout << "Sending: \"" << s << "\"" << std::endl;
        // TODO send messages to the server

        if(socket->send(s.c_str(), s.size() + 1) != sf::Socket::Done)
        {
            //error
            std::cerr << "Error sending\n";
            return 1;
        }
    }
    recv_thread.join();
    return 0;
}
