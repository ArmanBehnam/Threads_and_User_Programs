#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "string.h"
#include "threads/vaddr.h"

static void syscall_handler (struct intr_frame *);
void sys_exit(int status);


static bool is_valid_user_pointer (const void *ptr) {
  return (ptr != NULL && is_user_vaddr(ptr) && pagedir_get_page(thread_current()->pagedir, ptr) != NULL);
}

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}


static void
syscall_handler (struct intr_frame *f)
{
    int syscall_number;

  if (!is_valid_user_pointer(f->esp)) {
    sys_exit(-1);
  }

  syscall_number = *(int *) f->esp;  

  switch (syscall_number) {
    case SYS_WRITE: {
      int fd = *((int *) (f->esp + sizeof(int)));  // First argument
      void *buffer = *((void **) (f->esp + 2 * sizeof(int)));  // Second argument (buffer)
      unsigned size = *((unsigned *) (f->esp + 3 * sizeof(int)));  // Third argument (size)

      if (!is_valid_user_pointer(buffer)) {
        sys_exit(-1);
      }

      if (fd == STDOUT_FILENO) {
        putbuf((char *)buffer, size);
        f->eax = size;  
      } else {
        f->eax = -1;  // Return an error for now
      }
      break;
    }
    
    case SYS_EXIT: {
      int exit_status = *((int *) (f->esp + sizeof(int)));  // First argument (exit status)
      sys_exit(exit_status);  
      break;
    }
    
    default:
      printf("Unimplemented system call: %d\n", syscall_number);
      sys_exit(-1);  
  }
}

void
sys_exit (int status) 
{
  struct thread *cur = thread_current();
  printf("%s: exit(%d)\n", cur->name, status);
  cur->exit_status = status; 
  thread_exit();
}
