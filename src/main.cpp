#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <filesystem>

#include "ThreadPool.hpp"
#include "Logger.hpp"

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 4096;

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    std::memset(buffer, 0, BUFFER_SIZE);
    read(clientSocket, buffer, BUFFER_SIZE);

    std::string request(buffer);
    std::string filePath = "./static/index.html";
    std::string requestPath = "/";
    int statusCode = 200;

    std::size_t pos = request.find("GET ");
    if (pos != std::string::npos) {
        std::size_t start = pos + 4;
        std::size_t end = request.find(' ', start);
        requestPath = request.substr(start, end - start);
        if (requestPath != "/") filePath = "./static" + requestPath;
    }

    std::string content = readFile(filePath);
    std::string response;

    if (content.empty()) {
        response = "HTTP/1.1 404 Not Found\r\n\r\n404 - Not Found";
        statusCode = 404;
    } else {
        response = "HTTP/1.1 200 OK\r\n\r\n" + content;
        statusCode = 200;
    }

    send(clientSocket, response.c_str(), response.size(), 0);
    Logger::getInstance().log("Requested: " + requestPath + " | Status: " + std::to_string(statusCode));
    close(clientSocket);
}

int main() {
    int server_fd, new_socket;
    sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 20);
    std::cout << "[INFO] Server listening on port " << PORT << "...\n";

    ThreadPool pool(8);
    while (true) {
        new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        pool.enqueue([new_socket]() {
            handleClient(new_socket);
        });
    }
    return 0;
}
