/* Just a simple test to get started
 * by Farshad Ghanei fgh@iit.edu */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "devices/timer.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"

static thread_func thread_func_one;
static thread_func thread_func_two;
static thread_func thread_func_three;

struct semaphore sema_one, sema_two, sema_three;

void
test_pa1_1_starter (void) 
{

  /* This test does not work with the MLFQS. */
  ASSERT (!thread_mlfqs);

  /* Make sure our priority is the default. */
  ASSERT (thread_get_priority () == PRI_DEFAULT);

  sema_init(&sema_one, 0);
  sema_init(&sema_two, 0);
  sema_init(&sema_three, 0);

  msg ("Creating thread one.");
  thread_create_report ("one", PRI_DEFAULT + 1, thread_func_one, NULL);
  
  msg ("Increase priority.");
  thread_current()->priority = PRI_DEFAULT + 5;

  sema_up(&sema_one);
  sema_down(&sema_two);

  msg ("Creating thread three.");
  thread_create_report ("three", PRI_DEFAULT, thread_func_three, NULL);

  sema_up(&sema_one);
  sema_up(&sema_three);

  thread_yield();
  thread_yield();
  thread_yield();
}

static void
thread_func_one (void *data_ UNUSED)
{
  sema_down(&sema_one);

  msg ("Creating thread two.");
  thread_create_report ("two", PRI_DEFAULT + 2, thread_func_two, NULL);

  sema_down(&sema_one);
}

static void
thread_func_two (void *data_ UNUSED)
{
  msg ("Decrease priority.");
  thread_current()->priority = PRI_DEFAULT - 5;
  sema_up(&sema_two);
  sema_down(&sema_three);
}

static void
thread_func_three (void *data_ UNUSED)
{
}
