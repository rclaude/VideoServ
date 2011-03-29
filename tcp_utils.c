#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/epoll.h>
#include <unistd.h>

#include "serv.h"
#include "utils.h"

#include "tcp_utils.h"


int send_image_tcp(int sock, int image)
{
  int len, len_buff, sent;
  char str[12], *buff_ima;
  sprintf(str, "%d.jpg", image);
  file_to_buffer(str, &buff_ima, &len);

  char buff[len + 20];

  FILE * f = fopen("dump.jpg", "a");

  fwrite(buff_ima, sizeof(char), len, f);
  
  fclose(f);

  sprintf(buff, "%d\r\n%d\r\n", image, len);
  //perror("sprintf");


  sent = len_buff = strlen(buff);
  printf("Going to send image %d\n", image);
  do{
    sent -= send(sock, buff, len_buff, MSG_MORE);
  }
  while(sent > 0);

  sent = len;
  do{
    sent -= send(sock, buff_ima, len, 0);
  }
  while(sent > 0);
}

