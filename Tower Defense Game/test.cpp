#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::IpAddress serverAddress = "127.0.0.1"; // Server IP address
    unsigned short serverPort = 53000; // Server port

    sf::TcpSocket socket;
    if (socket.connect(serverAddress, serverPort) != sf::Socket::Done) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }

    std::string message = "hello"; // Message to send to the server

    // Send the message to the server
    sf::Packet packet;
    packet << message;
    if (socket.send(packet) != sf::Socket::Done) {
        std::cerr << "Failed to send message to server" << std::endl;
        return 1;
    }

    std::cout << "Message sent to server: " << message << std::endl;

    // Receive response from the server (if any)
    sf::Packet responsePacket;
    if (socket.receive(responsePacket) == sf::Socket::Done) {
        std::string response;
        responsePacket >> response;
        std::cout << "Received response from server: " << response << std::endl;
    }

    // Close the socket
    socket.disconnect();

    return 0;
}