/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *         Simon Goldschmidt
 *
 */

#include <stdlib.h>
#include <stdio.h> /* sprintf() for task names */

#include <lwip/opt.h>
#include <lwip/arch.h>
#include <lwip/stats.h>
#include <lwip/debug.h>
#include <lwip/sys.h>

#if (NO_SYS == 0)

/* These functions are used from NO_SYS also, for precise timer triggering */
LARGE_INTEGER freq, sys_start_time;
#define SYS_INITIALIZED() (freq.QuadPart != 0)

u32_t sys_jiffies(void)
{
    return (u32_t)sys_get_ms_longlong();
}

u32_t sys_now(void)
{
    return (u32_t)LOS_TickCountGet();
}

sys_prot_t sys_arch_protect(void)
{
    return LOS_IntLock();
}

void sys_arch_unprotect(sys_prot_t pval)
{
    LOS_IntRestore(pval);
}

void sys_init(void)
{

}

#if !NO_SYS

struct threadlist {
    lwip_thread_fn function;
    void *arg;
    DWORD id;
    struct threadlist *next;
};

struct threadlist *lwip_win32_threads = NULL;

/*---------------------------------------------------------------------------*
 * Routine:  sys_sem_new
 *---------------------------------------------------------------------------*
 * Description:
 *      Creates and returns a new semaphore. The "count" argument specifies
 *      the initial state of the semaphore.
 *      NOTE: Currently this routine only creates counts of 1 or 0
 * Inputs:
 *      sys_sem_t *sem            -- Handle of semaphore
 *      u8_t count              -- Initial count of semaphore (1 or 0)
 * Outputs:
 *      sys_sem_t               -- Created semaphore or 0 if could not create.
 *---------------------------------------------------------------------------*/
err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
    err_t ret = ERR_MEM;
    UINT32 uwRet;

    LWIP_ASSERT("sem != NULL", sem != NULL);
  
    /* create mutex */
    if(LOS_MuxCreate(sem) != LOS_OK);
    {
        ret = ERR_MEM;
        //SYS_STATS_INC(sem.err);
    }
    else
    {
        ret = ERR_OK;
        //SYS_STATS_INC_USED(sem);
    }

    if(count == 0UL)
    {
        /* get the mutex */
        if(LOS_MuxPend(*sem, LOS_WAIT_FOREVER) != LOS_OK)
        {
            ret = ERR_MEM;
            //SYS_STATS_INC(sem.err);
        }
        else
        {
            ret = ERR_OK;
        }
    }

    return ret;
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_sem_free
 *---------------------------------------------------------------------------*
 * Description:
 *      Deallocates a semaphore
 * Inputs:
 *      sys_sem_t *sem           -- Semaphore to free
 *---------------------------------------------------------------------------*/
void sys_sem_free(sys_sem_t *sem)
{
    /* parameter check */
    LWIP_ASSERT("sem != NULL", sem != NULL);
    
    // SYS_STATS_DEC(sem.used);
    LOS_MuxDelete(*sem);
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_sem_signal
 *---------------------------------------------------------------------------*
 * Description:
 *      Signals (releases) a semaphore
 * Inputs:
 *      sys_sem_t sem           -- Semaphore to signal
 *---------------------------------------------------------------------------*/
void sys_sem_signal(sys_sem_t *sem)
{
    LOS_MuxPost(*sem);
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_arch_sem_wait
 *---------------------------------------------------------------------------*
 * Description:
 *      Blocks the thread while waiting for the semaphore to be
 *      signaled. If the "timeout" argument is non-zero, the thread should
 *      only be blocked for the specified time (measured in
 *      milliseconds).
 *
 *      If the timeout argument is non-zero, the return value is the number of
 *      milliseconds spent waiting for the semaphore to be signaled. If the
 *      semaphore wasn't signaled within the specified time, the return value is
 *      SYS_ARCH_TIMEOUT. If the thread didn't have to wait for the semaphore
 *      (i.e., it was already signaled), the function may return zero.
 *
 *      Notice that lwIP implements a function with a similar name,
 *      sys_sem_wait(), that uses the sys_arch_sem_wait() function.
 * Inputs:
 *      sys_sem_t sem           -- Semaphore to wait on
 *      u32_t timeout           -- Number of milliseconds until timeout
 * Outputs:
 *      u32_t                   -- Time elapsed or SYS_ARCH_TIMEOUT.
 *---------------------------------------------------------------------------*/
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
    u32_t ret;
    UINT64 time_start, time_end, time_diff;

    time_start = LOS_TickCountGet();
    
    if( timeout != 0UL )
    {
        if(LOS_MuxPend(*sem, timeout) == LOS_OK)
        {
            time_end = LOS_TickCountGet();
            time_diff = time_end - time_start;
            ret = time_diff;
        }
        else
        {
            ret = SYS_ARCH_TIMEOUT;
        }
    }
    else
    {
        LOS_MuxPend(*sem, LOS_WAIT_FOREVER);
        time_end = LOS_TickCountGet();
        time_diff = time_end - time_start;
        ret = time_diff;
    }

    return ret;
}

err_t sys_mutex_new(sys_mutex_t *mutex)
{
    return sys_sem_new((sys_sem_t *)mutex);
}

void sys_mutex_free(sys_mutex_t *mutex)
{
    sys_sem_free((sys_sem_t *)mutex);
}

void sys_mutex_lock(sys_mutex_t *mutex)
{
    sys_arch_sem_wait((sys_sem_t *)mutex, 0);
}

void sys_mutex_unlock(sys_mutex_t *mutex)
{
    sys_sem_signal((sys_sem_t *)mutex);
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_mbox_new
 *---------------------------------------------------------------------------*
 * Description:
 *      Creates a new mailbox
 * Inputs:
 *      int size                -- Size of elements in the mailbox
 * Outputs:
 *      sys_mbox_t              -- Handle to new mailbox
 *---------------------------------------------------------------------------*/
err_t sys_mbox_new( sys_mbox_t *q, int size )
{
    err_t ret = ERR_MEM;

    /* parameter check */
    LWIP_ASSERT("q != NULL", q != NULL);
    LWIP_ASSERT("size != NULL", size != NULL);

    if(LOS_QueueCreate("", size, q, sizeof(void *)) == LOS_OK)
    {
        ret = ERR_OK;
        //SYS_STATS_INC_USED(mbox);
    }
    
    return ret;
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_mbox_free
 *---------------------------------------------------------------------------*
 * Description:
 *      Deallocates a mailbox. If there are messages still present in the
 *      mailbox when the mailbox is deallocated, it is an indication of a
 *      programming error in lwIP and the developer should be notified.
 * Inputs:
 *      sys_mbox_t mbox         -- Handle of mailbox
 * Outputs:
 *      sys_mbox_t              -- Handle to new mailbox
 *---------------------------------------------------------------------------*/
void sys_mbox_free( sys_mbox_t *q )
{
    LWIP_ASSERT("q != NULL", q != NULL);
    
    while (LOS_QueueDelete(*q) != LOS_OK)
    {
        LOS_TaskDelay(1);
    }
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_mbox_post
 *---------------------------------------------------------------------------*
 * Description:
 *      Post the "msg" to the mailbox.
 * Inputs:
 *      sys_mbox_t mbox         -- Handle of mailbox
 *      void *data              -- Pointer to data to post
 *---------------------------------------------------------------------------*/
void sys_mbox_post(sys_mbox_t *q, void *data)
{
    LWIP_ASSERT("q != NULL", q != NULL);

    LOS_QueueWrite(*q, data, sizeof(void *), LOS_WAIT_FOREVER);
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_mbox_trypost
 *---------------------------------------------------------------------------*
 * Description:
 *      Try to post the "msg" to the mailbox.  Returns immediately with
 *      error if cannot.
 * Inputs:
 *      sys_mbox_t mbox         -- Handle of mailbox
 *      void *msg               -- Pointer to data to post
 * Outputs:
 *      err_t                   -- ERR_OK if message posted, else ERR_MEM
 *                                  if not.
 *---------------------------------------------------------------------------*/
err_t sys_mbox_trypost(sys_mbox_t *q, void *data)
{
    err_t ret = ERR_OK;

    LWIP_ASSERT("q != NULL", q != NULL);

    if(LOS_QueueWrite(*q, data, sizeof(void *), LOS_NO_WAIT) != LOS_OK)
    {
        /* The queue was already full. */
        ret = ERR_MEM;
        SYS_STATS_INC( mbox.err );
    }

    return ret;
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_arch_mbox_fetch
 *---------------------------------------------------------------------------*
 * Description:
 *      Blocks the thread until a message arrives in the mailbox, but does
 *      not block the thread longer than "timeout" milliseconds (similar to
 *      the sys_arch_sem_wait() function). The "msg" argument is a result
 *      parameter that is set by the function (i.e., by doing "*msg =
 *      ptr"). The "msg" parameter maybe NULL to indicate that the message
 *      should be dropped.
 *
 *      The return values are the same as for the sys_arch_sem_wait() function:
 *      Number of milliseconds spent waiting or SYS_ARCH_TIMEOUT if there was a
 *      timeout.
 *
 *      Note that a function with a similar name, sys_mbox_fetch(), is
 *      implemented by lwIP.
 * Inputs:
 *      sys_mbox_t mbox         -- Handle of mailbox
 *      void **msg              -- Pointer to pointer to msg received
 *      u32_t timeout           -- Number of milliseconds until timeout
 * Outputs:
 *      u32_t                   -- SYS_ARCH_TIMEOUT if timeout, else number
 *                                  of milliseconds until received.
 *---------------------------------------------------------------------------*/
u32_t sys_arch_mbox_fetch( sys_mbox_t *q, void **data, u32_t timeout )
{
	void *pvDummy;
	portTickType xStartTime, xEndTime, xElapsed;
	unsigned long ulReturn;

	xStartTime = xTaskGetTickCount();

	if( NULL == ppvBuffer )
	{
		ppvBuffer = &pvDummy;
	}

	if( ulTimeOut != 0UL )
	{
		if( pdTRUE == xQueueReceive( *pxMailBox, &( *ppvBuffer ), ulTimeOut/ portTICK_RATE_MS ) )
		{
			xEndTime = xTaskGetTickCount();
			xElapsed = ( xEndTime - xStartTime ) * portTICK_RATE_MS;

			ulReturn = xElapsed;
		}
		else
		{
			/* Timed out. */
			*ppvBuffer = NULL;
			ulReturn = SYS_ARCH_TIMEOUT;
		}
	}
	else
	{
		while( pdTRUE != xQueueReceive( *pxMailBox, &( *ppvBuffer ), portMAX_DELAY ) );
		xEndTime = xTaskGetTickCount();
		xElapsed = ( xEndTime - xStartTime ) * portTICK_RATE_MS;

		if( xElapsed == 0UL )
		{
			xElapsed = 1UL;
		}

		ulReturn = xElapsed;
	}

	return ulReturn;

    u32_t ret;
    UINT64 time_start, time_end, time_diff;

    LWIP_ASSERT("q != NULL", q != NULL);

    time_start = LOS_TickCountGet();
    
    if(timeout != 0UL)
    {
        if(LOS_QueueRead(*q, timeout) == LOS_OK)
        {
            time_end = LOS_TickCountGet();
            time_diff = time_end - time_start;
            ret = time_diff;
        }
        else
        {
            ret = SYS_ARCH_TIMEOUT;
        }
    }
    else
    {
        LOS_MuxPend(*sem, LOS_WAIT_FOREVER);
        time_end = LOS_TickCountGet();
        time_diff = time_end - time_start;
        ret = time_diff;
    }

    return ret;
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_arch_mbox_tryfetch
 *---------------------------------------------------------------------------*
 * Description:
 *      Similar to sys_arch_mbox_fetch, but if message is not ready
 *      immediately, we'll return with SYS_MBOX_EMPTY.  On success, 0 is
 *      returned.
 * Inputs:
 *      sys_mbox_t mbox         -- Handle of mailbox
 *      void **msg              -- Pointer to pointer to msg received
 * Outputs:
 *      u32_t                   -- SYS_MBOX_EMPTY if no messages.  Otherwise,
 *                                  return ERR_OK.
 *---------------------------------------------------------------------------*/
u32_t sys_arch_mbox_tryfetch( sys_mbox_t *pxMailBox, void **ppvBuffer )
{
	void *pvDummy;
	unsigned long ulReturn;

	if( ppvBuffer== NULL )
	{
		ppvBuffer = &pvDummy;
	}

	if( pdTRUE == xQueueReceive( *pxMailBox, &( *ppvBuffer ), 0UL ) )
	{
		ulReturn = ERR_OK;
	}
	else
	{
		ulReturn = SYS_MBOX_EMPTY;
	}

	return ulReturn;
}

#ifdef _MSC_VER
const DWORD MS_VC_EXCEPTION=0x406D1388;
#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
  DWORD dwType; /* Must be 0x1000. */
  LPCSTR szName; /* Pointer to name (in user addr space). */
  DWORD dwThreadID; /* Thread ID (-1=caller thread). */
  DWORD dwFlags; /* Reserved for future use, must be zero. */
} THREADNAME_INFO;
#pragma pack(pop)
static void SetThreadName(DWORD dwThreadID, const char* threadName)
{
  THREADNAME_INFO info;
  info.dwType = 0x1000;
  info.szName = threadName;
  info.dwThreadID = dwThreadID;
  info.dwFlags = 0;

  __try
  {
    RaiseException(MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info);
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
  }
}
#else /* _MSC_VER */
static void SetThreadName(DWORD dwThreadID, const char* threadName)
{
  LWIP_UNUSED_ARG(dwThreadID);
  LWIP_UNUSED_ARG(threadName);
}
#endif /* _MSC_VER */

static void sys_thread_function(void* arg)
{
  struct threadlist* t = (struct threadlist*)arg;
#if LWIP_NETCONN_SEM_PER_THREAD
  sys_arch_netconn_sem_alloc();
#endif
  t->function(t->arg);
#if LWIP_NETCONN_SEM_PER_THREAD
  sys_arch_netconn_sem_free();
#endif
}

sys_thread_t sys_thread_new(const char *name, lwip_thread_fn function, void *arg, int stacksize, int prio)
{
  struct threadlist *new_thread;
  HANDLE h;
  SYS_ARCH_DECL_PROTECT(lev);

  LWIP_UNUSED_ARG(name);
  LWIP_UNUSED_ARG(stacksize);
  LWIP_UNUSED_ARG(prio);

  new_thread = (struct threadlist*)malloc(sizeof(struct threadlist));
  LWIP_ASSERT("new_thread != NULL", new_thread != NULL);
  if(new_thread != NULL) {
    new_thread->function = function;
    new_thread->arg = arg;
    SYS_ARCH_PROTECT(lev);
    new_thread->next = lwip_win32_threads;
    lwip_win32_threads = new_thread;

    h = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sys_thread_function, new_thread, 0, &(new_thread->id));
    LWIP_ASSERT("h != 0", h != 0);
    LWIP_ASSERT("h != -1", h != INVALID_HANDLE_VALUE);
    LWIP_UNUSED_ARG(h);
    SetThreadName(new_thread->id, name);

    SYS_ARCH_UNPROTECT(lev);
    return new_thread->id;
  }
  return 0;
}

err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
  LWIP_ASSERT("mbox != NULL", mbox != NULL);
  LWIP_UNUSED_ARG(size);

  mbox->sem = CreateSemaphore(0, 0, MAX_QUEUE_ENTRIES, 0);
  LWIP_ASSERT("Error creating semaphore", mbox->sem != NULL);
  if(mbox->sem == NULL) {
    SYS_STATS_INC(mbox.err);
    return ERR_MEM;
  }
  memset(&mbox->q_mem, 0, sizeof(u32_t)*MAX_QUEUE_ENTRIES);
  mbox->head = 0;
  mbox->tail = 0;
  SYS_STATS_INC_USED(mbox);
#if LWIP_STATS && SYS_STATS
  LWIP_ASSERT("sys_mbox_new() counter overflow", lwip_stats.sys.mbox.used != 0 );
#endif /* LWIP_STATS && SYS_STATS */
  return ERR_OK;
}

void sys_mbox_free(sys_mbox_t *mbox)
{
  /* parameter check */
  LWIP_ASSERT("mbox != NULL", mbox != NULL);
  LWIP_ASSERT("mbox->sem != NULL", mbox->sem != NULL);
  LWIP_ASSERT("mbox->sem != INVALID_HANDLE_VALUE", mbox->sem != INVALID_HANDLE_VALUE);

  CloseHandle(mbox->sem);

   SYS_STATS_DEC(mbox.used);
#if LWIP_STATS && SYS_STATS
   LWIP_ASSERT( "sys_mbox_free() ", lwip_stats.sys.mbox.used!= (u16_t)-1 );
#endif /* LWIP_STATS && SYS_STATS */
  mbox->sem = NULL;
}

void sys_mbox_post(sys_mbox_t *q, void *msg)
{
  DWORD ret;
  SYS_ARCH_DECL_PROTECT(lev);

  /* parameter check */
  LWIP_ASSERT("q != SYS_MBOX_NULL", q != SYS_MBOX_NULL);
  LWIP_ASSERT("q->sem != NULL", q->sem != NULL);
  LWIP_ASSERT("q->sem != INVALID_HANDLE_VALUE", q->sem != INVALID_HANDLE_VALUE);

  SYS_ARCH_PROTECT(lev);
  q->q_mem[q->head] = msg;
  (q->head)++;
  if (q->head >= MAX_QUEUE_ENTRIES) {
    q->head = 0;
  }
  LWIP_ASSERT("mbox is full!", q->head != q->tail);
  ret = ReleaseSemaphore(q->sem, 1, 0);
  LWIP_ASSERT("Error releasing sem", ret != 0);
  LWIP_UNUSED_ARG(ret);

  SYS_ARCH_UNPROTECT(lev);
}

err_t sys_mbox_trypost(sys_mbox_t *q, void *msg)
{
  u32_t new_head;
  DWORD ret;
  SYS_ARCH_DECL_PROTECT(lev);

  /* parameter check */
  LWIP_ASSERT("q != SYS_MBOX_NULL", q != SYS_MBOX_NULL);
  LWIP_ASSERT("q->sem != NULL", q->sem != NULL);
  LWIP_ASSERT("q->sem != INVALID_HANDLE_VALUE", q->sem != INVALID_HANDLE_VALUE);

  SYS_ARCH_PROTECT(lev);

  new_head = q->head + 1;
  if (new_head >= MAX_QUEUE_ENTRIES) {
    new_head = 0;
  }
  if (new_head == q->tail) {
    SYS_ARCH_UNPROTECT(lev);
    return ERR_MEM;
  }

  q->q_mem[q->head] = msg;
  q->head = new_head;
  LWIP_ASSERT("mbox is full!", q->head != q->tail);
  ret = ReleaseSemaphore(q->sem, 1, 0);
  LWIP_ASSERT("Error releasing sem", ret != 0);
  LWIP_UNUSED_ARG(ret);

  SYS_ARCH_UNPROTECT(lev);
  return ERR_OK;
}

u32_t sys_arch_mbox_fetch(sys_mbox_t *q, void **msg, u32_t timeout)
{
  DWORD ret;
  LONGLONG starttime, endtime;
  SYS_ARCH_DECL_PROTECT(lev);

  /* parameter check */
  LWIP_ASSERT("q != SYS_MBOX_NULL", q != SYS_MBOX_NULL);
  LWIP_ASSERT("q->sem != NULL", q->sem != NULL);
  LWIP_ASSERT("q->sem != INVALID_HANDLE_VALUE", q->sem != INVALID_HANDLE_VALUE);

  if (timeout == 0) {
    timeout = INFINITE;
  }
  starttime = sys_get_ms_longlong();
  if ((ret = WaitForSingleObject(q->sem, timeout)) == WAIT_OBJECT_0) {
    SYS_ARCH_PROTECT(lev);
    if(msg != NULL) {
      *msg  = q->q_mem[q->tail];
    }

    (q->tail)++;
    if (q->tail >= MAX_QUEUE_ENTRIES) {
      q->tail = 0;
    }
    SYS_ARCH_UNPROTECT(lev);
    endtime = sys_get_ms_longlong();
    return (u32_t)(endtime - starttime);
  }
  else
  {
    LWIP_ASSERT("Error waiting for sem", ret == WAIT_TIMEOUT);
    if(msg != NULL) {
      *msg  = NULL;
    }

    return SYS_ARCH_TIMEOUT;
  }
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t *q, void **msg)
{
  DWORD ret;
  SYS_ARCH_DECL_PROTECT(lev);

  /* parameter check */
  LWIP_ASSERT("q != SYS_MBOX_NULL", q != SYS_MBOX_NULL);
  LWIP_ASSERT("q->sem != NULL", q->sem != NULL);
  LWIP_ASSERT("q->sem != INVALID_HANDLE_VALUE", q->sem != INVALID_HANDLE_VALUE);

  if ((ret = WaitForSingleObject(q->sem, 0)) == WAIT_OBJECT_0) {
    SYS_ARCH_PROTECT(lev);
    if(msg != NULL) {
      *msg  = q->q_mem[q->tail];
    }

    (q->tail)++;
    if (q->tail >= MAX_QUEUE_ENTRIES) {
      q->tail = 0;
    }
    SYS_ARCH_UNPROTECT(lev);
    return 0;
  }
  else
  {
    LWIP_ASSERT("Error waiting for sem", ret == WAIT_TIMEOUT);
    if(msg != NULL) {
      *msg  = NULL;
    }

    return SYS_ARCH_TIMEOUT;
  }
}

#if LWIP_NETCONN_SEM_PER_THREAD
sys_sem_t* sys_arch_netconn_sem_get(void)
{
  LPVOID tls_data = TlsGetValue(netconn_sem_tls_index);
  return (sys_sem_t*)tls_data;
}

void sys_arch_netconn_sem_alloc(void)
{
  sys_sem_t *sem;
  err_t err;
  BOOL done;

  sem = (sys_sem_t*)malloc(sizeof(sys_sem_t));
  LWIP_ASSERT("failed to allocate memory for TLS semaphore", sem != NULL);
  err = sys_sem_new(sem, 0);
  LWIP_ASSERT("failed to initialise TLS semaphore", err == ERR_OK);
  done = TlsSetValue(netconn_sem_tls_index, sem);
  LWIP_UNUSED_ARG(done);
  LWIP_ASSERT("failed to initialise TLS semaphore storage", done == TRUE);
}

void sys_arch_netconn_sem_free(void)
{
  LPVOID tls_data = TlsGetValue(netconn_sem_tls_index);
  if (tls_data != NULL) {
    BOOL done;
    free(tls_data);
    done = TlsSetValue(netconn_sem_tls_index, NULL);
    LWIP_UNUSED_ARG(done);
    LWIP_ASSERT("failed to de-init TLS semaphore storage", done == TRUE);
  }
}
#endif /* LWIP_NETCONN_SEM_PER_THREAD */

#endif /* !NO_SYS */
