#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
  if (argc < 2){
    std::cout << "Usage: portmap <192.168.x.x>";
    return 0;
  }

}
