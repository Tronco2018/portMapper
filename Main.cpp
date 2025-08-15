#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <chrono>

long long currentTimeMillis(){
  using namespace std::chrono;
  return duration_cast<milliseconds>(
    system_clock::now().time_since_epoch()
  ).count();
}

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
  int lastPort = 9999;
  int portCount = 0;
  if (argc < 2){
    std::cout << "Usage: portmap <192.168.x.x>";
    return 0;
  }
  std::string ip = argv[1];
  std::cout << "Starting scan on host " << ip << "\n";
  long current = currentTimeMillis();
  for (int i = 0; i <= lastPort; i++){
    if (isPortOpen(ip, i)){
      std::cout << "[+] " << i << " port open\n";
      portCount++;
    }
  }
  long elapsedMs = currentTimeMillis() - current;
  std::cout << "Finished in " << elapsedMs/1000 << "s, " << portCount << " open ports found\n";
  return 0;
}
