#include "accepter.h"
#include "receiver.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <thread>

Accepter::Accepter(Queue<std::string>& q, List<std::shared_ptr<sf::TcpSocket>>& s):
    m_queue(q),
    m_socket(s)
{}

void Accepter::operator()()
{
    sf::TcpListener listener;
    // TODO the listener has to listen.

    if (listener.listen(PORT) != sf::Socket::Done)
    {
        // error...
        std::cerr << "Listen does not work\n";
        return;
    }

   

    std::cout << "Bound to port\n";
    while (true)
    {
        std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();
        // TODO accept a connection on socket
        if (listener.accept(*socket) != sf::Socket::Done)
        {
           // error...
        }

        m_socket.push(socket);
        std::stringstream ss;
        ss << "Accepted a connection from: "
            << socket->getRemoteAddress()
            << ":"
            << socket->getRemotePort()
            << std::endl;
        std::cout << ss.str();
        std::shared_ptr<Receiver> receiver = std::make_shared<Receiver>(socket, m_queue);
        // TODO launch a thread to receive with the receiver

        std::thread recv_thread(&Receiver::recv_loop, receiver);
        recv_thread.detach();
    }
}

