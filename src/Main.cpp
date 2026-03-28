#include <asm-generic/ioctls.h>
#include <exception>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <sys/ioctl.h>

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

//int last = 0;
//char wheel[] = {'/', '-', '\\', '|'};

struct winsize w;

void clear_line() {
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  std::cout << "\r";
  for (int i = 0; i < w.ws_col; i++) std::cout << " ";
  std::cout << "\r";
}

void update_status(int port_min, int port_max,int current){
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int exceptions = 10;
  float percentage = (float)current/port_max; // TODO:FIX THIS PLS
  int n_chars = (w.ws_col - exceptions)*percentage;
  std::cout << "\r[";
  for (int i = 0; i < w.ws_col-exceptions; i++){
    if (i < n_chars) std::cout << "#";
    else std::cout << "-";
  }
  printf("](%.1f%)",percentage*100);
}


int main(int argc, char* argv[]){
  int lastPort = 9999;
  int first_port = 1;
  int portCount = 0;
  if (argc < 2){
    std::cout << "Usage: portmap <192.168.x.x> [maxport] [minport]" << std::endl;
    return 1;
  }
  std::string ip = argv[1];
  
  try {
    if (argc > 2){
      if (argc > 3) {
        first_port = std::stoi(argv[3]);
      }
      lastPort = std::stoi(argv[2]);
    }
  } catch (std::exception e) {
    std::cout << "Usage: portmap <192.168.x.x> [maxport] [minport]" << std::endl;
    return 1;
  }
  

  std::cout << "Starting scan on host " << ip << "\n";
  std::cout << "Ports: " << first_port << ":" << lastPort << std::endl;
  
  long current = currentTimeMillis();
  for (int i = first_port; i <= lastPort; i++){
    update_status(first_port, lastPort, i);
    if (isPortOpen(ip, i)){
      clear_line();
      std::cout << "\r[+] " << i << " port open\n";
      portCount++;
    }
  }
  long elapsedMs = currentTimeMillis() - current;
  std::cout << "\rFinished in " << elapsedMs/1000 << "s, " << portCount << " open ports found\n";
  return 0;
}
