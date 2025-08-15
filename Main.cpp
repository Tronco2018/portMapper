#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

bool isPortOpen(const std::string& host, int port){
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    return false;
  }

  sockaddr_in server{};
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  if (inet_pton(AF_INET, host.c_str(), &server.sin_addr) <= 0){
    close(sock);
    return false;
  }
  int result = connect(sock, (struct sockaddr*)&server, sizeof(server));
  close(sock);
  
  return (result == 0);
}

int main(int argc, char* argv[]){
  if (argc < 2){
    std::cout << "Usage: portmap <192.168.x.x>";
    return 0;
  }

}
