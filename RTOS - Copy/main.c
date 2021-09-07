#include "stm32f10x.h"

#define DUMMY_XPSR  						 0x01000000U
#define MAX_TASKS                3U
#define TASK_READY_STATE         0x00U
#define TASK_BLOCKED_STATE       0xFFU
#define SRAM_START               0x20000000U
#define SIZE_SRAM                ((20U) * (1024))
#define SRAM_END                 ((SRAM_START) + (SIZE_SRAM) )
//#define DUMMY_XPSR               0x01000000U



/* some stack memory calculations */
#define SIZE_TASK_STACK          1024U
//#define SIZE_SCHED_STACK         1024U

#define T1_STACK_START           SRAM_END
#define T2_STACK_START           ( (SRAM_END) - (1U * SIZE_TASK_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (2U * SIZE_TASK_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (3U * SIZE_TASK_STACK) )

/* variables in task */
uint16_t u16Count1= 0, u16Count2= 0;


void SysTick_Interrupt(void);
void mainBlinkGreen_Task(void);
void mainBlinkRed_Task(void);
void task_delay(uint32_t tick_count);
void idle_task(void);
void enable_processor_faults(void);
void schedule(void);
uint32_t get_psp_value(void);
void save_psp_value(uint32_t current_psp_value);
void update_next_task(void);
__asm void init_scheduler_stack(uint32_t sched_top_of_stack);
void init_tasks_stack(void);
__asm void switch_sp_to_psp(void);
void unblock_tasks(void);
void update_global_tick_count(void);

typedef struct
{
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t  current_state;
	void (*task_handler)(void);
}TCB_t;

TCB_t user_tasks[MAX_TASKS];
uint8_t current_task = 1; //task1 is running
uint32_t g_tick_count = 0;

int main()
{ 
	enable_processor_faults();	
	init_scheduler_stack(SCHED_STACK_START);
	init_tasks_stack();
	switch_sp_to_psp();
  SysTick_Interrupt();
	NVIC_SetPriority(SysTick_IRQn, 0U);
	
	mainBlinkRed_Task();
	
}
__asm void switch_sp_to_psp(void)
{
	IMPORT get_psp_value
	
	PRESERVE8 {TRUE}
	PUSH {LR}
	BL get_psp_value
	MSR PSP,R0
	POP {LR}

	MOV R0,#0x02
	MSR CONTROL,R0
	BX LR
}
__asm void init_scheduler_stack(uint32_t sched_top_of_stack)
{
 	MSR MSP,R0
	BX LR
}
void enable_processor_faults(void)
{
	SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
	SCB->SHCSR |= SCB_SHCSR_BUSFAULTENA_Msk;
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk;
}
void init_tasks_stack(void)
{

	user_tasks[0].current_state = TASK_READY_STATE;
	user_tasks[1].current_state = TASK_READY_STATE;
	user_tasks[2].current_state = TASK_READY_STATE;

	user_tasks[0].psp_value = IDLE_STACK_START;
	user_tasks[1].psp_value = T1_STACK_START;
	user_tasks[2].psp_value = T2_STACK_START;

	user_tasks[0].task_handler = idle_task;
	user_tasks[1].task_handler = mainBlinkRed_Task;
	user_tasks[2].task_handler = mainBlinkGreen_Task;


	uint32_t *pPSP;

	for(int i = 0 ; i < MAX_TASKS ;i++)
	{
		pPSP = (uint32_t*) user_tasks[i].psp_value;

		pPSP--;
		*pPSP = DUMMY_XPSR;//0x00100000

		pPSP--; //PC
		*pPSP = (uint32_t) user_tasks[i].task_handler;

		pPSP--; //LR
		*pPSP = 0xFFFFFFFD;

		for(int j = 0 ; j < 13 ; j++)
		{
			   pPSP--;
		    *pPSP = 0;
		}
		user_tasks[i].psp_value = (uint32_t)pPSP;
	}
}
void task_delay(uint32_t tick_count)
{
	__disable_irq();
	
	if(current_task)
	{
	   user_tasks[current_task].block_count = g_tick_count + tick_count;
	   user_tasks[current_task].current_state = TASK_BLOCKED_STATE;
	   schedule();
	}
  __enable_irq();
}
uint32_t get_psp_value(void)
{
	
	return user_tasks[current_task].psp_value;
}


void save_psp_value(uint32_t current_psp_value)
{
	user_tasks[current_task].psp_value = current_psp_value;
}
void update_next_task(void)
{
	int state = TASK_BLOCKED_STATE;

	for(int i= 0 ; i < (MAX_TASKS) ; i++)
	{
		current_task++;
	  current_task %= MAX_TASKS;
		state = user_tasks[current_task].current_state;
		if( (state == TASK_READY_STATE) && (current_task != 0) )
			break;
	}

	if(state != TASK_READY_STATE)
		current_task = 0;
}

void idle_task(void)
{
	while(1);
}

/*============== Task 2 ==============*/
void mainBlinkGreen_Task(void)
{
	while(1)
	{
		u16Count1++;
		task_delay(500);
	}
}

/*============== Task 2 ==============*/
void mainBlinkRed_Task(void)
{
	while(1)
	{
		u16Count2++;
		task_delay(1000);

	}
}
void schedule(void)
{
	//pend the pendsv exception
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

}


void SysTick_Interrupt(void)
{
	/* Dealy 1ms*/
		SysTick->LOAD = 72U * 1000U - 1U;
		SysTick->VAL = 0U;
		SysTick->CTRL = 7U;
}
void SysTick_Handler(void)
{
   update_global_tick_count();

   unblock_tasks();

   SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}


__ASM void PendSV_Handler(void) 
{
	CPSID    I     // Clear PRIMASK (Enable interrupts)
	
	IMPORT save_psp_value
	IMPORT update_next_task
	IMPORT get_psp_value
	
	MRS R0,PSP
	STMDB R0!,{R4-R11}
	PUSH {LR}
	BL save_psp_value
	BL update_next_task
	BL get_psp_value
	LDMIA R0!,{R4-R11}
	MSR PSP,R0
	POP {LR}
	
	CPSIE    I  // Set PRIMASK (Disable interrupts)
	
	BX LR
	
}



void update_global_tick_count(void)
{
	g_tick_count++;
}
void unblock_tasks(void)
{
	for(int i = 1 ; i < MAX_TASKS ; i++)
	{
		if(user_tasks[i].current_state != TASK_READY_STATE)
		{
			if(user_tasks[i].block_count == g_tick_count)
			{
				user_tasks[i].current_state = TASK_READY_STATE;
			}
		}
	}
}
