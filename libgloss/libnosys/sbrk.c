/* Version of sbrk for no operating system.  */

#include "config.h"
#include <_syslist.h>
#include <errno.h>
#undef errno
extern int errno;

#ifdef __arm__
/* Register name faking - works in collusion with the linker.  */
register char *stack_ptr asm ("sp");
#endif

void *
_sbrk (incr)
     int incr;
{ 
   extern char   end; /* Set by linker.  */
   static char * heap_end; 
   char *        prev_heap_end; 

   if (heap_end == 0)
     heap_end = & end; 

   prev_heap_end = heap_end; 

#ifdef __arm__
  if (heap_end + incr > stack_ptr)
    {
      errno = ENOMEM;
      return (void *) -1;
    }
#endif

   heap_end += incr; 

   return (void *) prev_heap_end; 
} 
