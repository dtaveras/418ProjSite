#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/_structs.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

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
  char rawBuffer[4096], *s, tstr[8], buffer[1024] ;
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
      //  read into buffer, cnvert to NSString and send to the NSTextView.
      bytesRead = read( inputfd, buffer, 1024 ) ;

      rawBytes = 0 ;
      for ( i = 0; i < bytesRead; i++ ) {
	v = buffer[i] & 0xff ;
	if ( v < 32 || v > 0x7f ) {
	  sprintf( tstr, "<%02X>", v ) ;
	  s = tstr ;
	  while ( *s ) rawBuffer[rawBytes++] = *s++ ;
	}
	else {
	  rawBuffer[rawBytes++] = v ;
	}
      }
      
      printf("%s\n",(const char*)rawBuffer);
    }
  }

  printf("Starting Main ...\n");
  return 1;
}
