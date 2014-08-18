#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <string.h>
#include <unistd.h>

// http://stackoverflow.com/questions/9067175/how-to-monitor-a-folder-with-all-subfolders-and-files-inside

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int main( int argc, char **argv ) 
{
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //you should check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
while (1==1)
{
  int length, i = 0;
  int fd;
  int wd;
  char buffer[BUF_LEN];
  int system(const char *command);

  fd = inotify_init();

  if ( fd < 0 ) {
    perror( "inotify_init" );
  }

  // get current working directory
  long size;
  char *ptr;
  char *buf;
  size = pathconf(".", _PC_PATH_MAX);
  if ((buf = (char *)malloc((size_t)size)) != NULL)
        {ptr = getcwd(buf, (size_t)size);}

  wd = inotify_add_watch( fd, ptr, 
                         IN_MODIFY | IN_CREATE );
  length = read( fd, buffer, BUF_LEN );  

  if ( length < 0 ) {
    perror( "read" );
  }  

  while ( i < length ) {
    struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
    if ( event->len ) {
      if ( event->mask & IN_CREATE ) {
        if ( event->mask & IN_ISDIR ) {
           continue;
        }
        else {
           if (strstr(event->name, ".csv") != NULL){ 
             char* frag = concat("import os,sys; sys.path.append(os.getcwd())\nfrom loader import load\nload('",event->name);
             char* code = concat(frag,"')");
             Py_SetProgramName(argv[0]);
             Py_Initialize();
             PyRun_SimpleString(code);
             Py_Finalize();
             free(frag);
             free(code);
             }
        }
      }
      
    }
    i += EVENT_SIZE + event->len;
  }

  ( void ) inotify_rm_watch( fd, wd );
  ( void ) close( fd );
}
exit( 1 );
}
