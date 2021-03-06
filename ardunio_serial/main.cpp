#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/_structs.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>

#define MAX_NUM_SIZE 10
#define READ_AMOUNT 256

using namespace std;

//  common function to open port and set up serial port parameters
int openPort( const char *path, int speed, int bits, int parity, int stops, int openFlags)
{
  int fd, cflag ;
  struct termios termattr ;
  
  fd = open( path, openFlags ) ;
  if ( fd < 0 ) return -1 ;
  
  //  build other flags
  cflag = 0 ;
  cflag |= ( bits == 7 ) ? CS7 : CS8 ;//  bits
  if ( parity != 0 ) {
    cflag |= PARENB ;//  parity
    if ( parity == 1 ) cflag |= PARODD ;
  }
  if ( stops > 1 ) cflag |= CSTOPB ;
  
  //  merge flags into termios attributes
  tcgetattr( fd, &termattr ) ;
  termattr.c_cflag &= ~( CSIZE | PARENB | PARODD | CSTOPB ) ;// clear all bits and merge in our selection
  termattr.c_cflag |= cflag ;
  
  // set speed, split speed not support on Mac OS X?
  cfsetispeed( &termattr, speed ) ;
  cfsetospeed( &termattr, speed ) ;
  //  set termios
  tcsetattr( fd, TCSANOW, &termattr ) ;

  return fd ;
}

int main(){
  int count = 0;
  char port[] = "/dev/tty.usbserial-A1001N34";
  int baud = 115200;
  int bits = 8;
  int parity = 0;
  int stops = 1;
  int inputfd = openPort( port, baud, bits, parity, stops, ( O_RDONLY | O_NOCTTY | O_NDELAY ));
  if(inputfd < 0){
    printf("Unable to Open port Sorry!\n");
  }

  fd_set readfds, basefds, errfds ;
  int selectCount, bytesRead, i, v, rawBytes ;
  char rawBuffer[4096], *s, tstr[8], buffer[READ_AMOUNT] ;
  char numBuffer[MAX_NUM_SIZE];
  unsigned int size;
  FD_ZERO( &basefds ) ;
  FD_SET( inputfd, &basefds ) ;

  while ( 1 ) {
    FD_COPY( &basefds, &readfds ) ;
    FD_COPY( &basefds, &errfds ) ;
    selectCount = select( inputfd+1, &readfds, NULL, &errfds, 0 ) ;

    if ( FD_ISSET( inputfd, &errfds ) ) {
      printf("Exit Error in Stream\n");
      break ;//  exit if error in stream
    }

    if ( selectCount > 0 && FD_ISSET( inputfd, &readfds ) ) {
      bytesRead = read( inputfd, buffer, READ_AMOUNT) ;
      //printf("read:%d\n",bytesRead);
      //printf("%s\n",buffer);

      char* char_itr = buffer;
      numBuffer[0] = '\0';
      sscanf(char_itr, "%10[^,]",numBuffer);
      size = strlen(numBuffer);
      if(size > 0) {
	string str(numBuffer);
	if(str.find_first_not_of("0123456789") != std::string::npos){
	  printf("%s\n",numBuffer);
	}
      }

      while(size > 0){
	numBuffer[0] = '\0';
	char_itr += size+1;
	sscanf(char_itr, "%10[^,]",numBuffer);
	size = strlen(numBuffer);
	string str(numBuffer);
       	if(str.find_first_not_of("0123456789") != std::string::npos){
	  printf("%s\n",numBuffer);
	}
      }

    }
  }

  printf("Starting Main ...\n");
  return 1;
}
