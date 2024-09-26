#include <stdio.h>
#include <sys/mman.h> 
#include <fcntl.h> 
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "spi_regs.h"

#define _BSD_SOURCE
#define ARRSIZE 25

//get pointer that we can actually point to from this C code
volatile unsigned int * get_a_pointer(unsigned int phys_addr); 

//Initialize SPI control register
int spi_init(volatile unsigned int *my_periph);

//Write single 32-bit word to SPI channel
int spi_write(uint32_t word, volatile unsigned int *my_periph);

//Write entire 32-bit array to SPI channel - optimized to be very fast
//Since UH88 protocol calls for 16-bit address then 16-bit data, we will OR them in software
//with address in top 16 bits and data in lower 16 bits
//There is NO DIFFERENCE TO THE MCU between 1 32-bit word and 2 16-bit words, but this is faster on the Zynq side
int spi_write_array(uint32_t array[ARRSIZE], volatile unsigned int *my_periph);

int set_cs(volatile unsigned int *my_periph);
int clear_cs(volatile unsigned int *my_periph);
int master_transact_block(volatile unsigned int *my_periph);
int master_transact_unblock(volatile unsigned int *my_periph);

int main()
{
    clock_t start_time, end_time;
    double time_spent;

    printf("\n\nStarting SPI code\n\n");
    
    volatile unsigned int *spi0 = get_a_pointer(SPI0_baseaddr);
    printf("spi0 = %p\nstar my periph = %u\n", (void *)spi0, *spi0);
    spi_init(spi0); //initialize SPI peripheral
    
    volatile unsigned int *spi1 = get_a_pointer(SPI1_baseaddr);
    printf("spi0 = %p\nstar my periph = %u\n", (void *)spi1, *spi1);
    spi_init(spi1); //initialize SPI peripheral
    
    // Generate random uint32_t values and store them in the array
    srand(time(NULL));
    uint32_t array[ARRSIZE];
    for (int i = 0; i < ARRSIZE; i++) {
        array[i] = (uint32_t)((i<<16) | (rand() % 256));  // Example of bitwise-ORing the address with the data
        printf("random_array[%d] = 0x%08x\n", i, array[i]);
    }
    
    while(1)
    {
        
        usleep(.1);
        clear_cs(spi0);
        clear_cs(spi1);        
        master_transact_block(spi0);
        master_transact_block(spi1);

        start_time = clock();
        spi_write_array(array, spi0);
        spi_write_array(array, spi1);
        end_time = clock();

        time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        set_cs(spi0);
        set_cs(spi1);
        master_transact_unblock(spi0);
        master_transact_unblock(spi1);    
        printf("Time taken: %f seconds\n", time_spent);

    }
}

// the below code uses a device called /dev/mem to get a pointer to a physical
// address.  We will use this pointer to read/write the custom peripheral
volatile unsigned int * get_a_pointer(unsigned int phys_addr)
{

	int mem_fd = open("/dev/mem", O_RDWR | O_SYNC); 
	void *map_base = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, phys_addr); 
	volatile unsigned int *radio_base = (volatile unsigned int *)map_base; 
	return (radio_base); 

}

int spi_init(volatile unsigned int *my_periph)
{
    //Write to control register to set as SPI Controller, enable SPI
    unsigned int reg_value = *(my_periph + SPI_SPICR_OFFSET);
    printf("SPI Control Reg Before: 0x%32x\n", reg_value);

    *(my_periph + SPI_SPICR_OFFSET) |= (SPI_CR_SPE_MASK | SPI_CR_MASTER_MASK);
    *(my_periph + SPI_SPICR_OFFSET) &= (0xFFFF - SPI_CR_MSTR_INHIBIT_MASK);

    reg_value = *(my_periph + SPI_SPICR_OFFSET);

    printf("SPI Control Reg After: 0x%32x\n", reg_value);
    
    //check that device was properly configured to master mode
    printf("SPI Status Register: 0x%32X\n",*(my_periph + SPI_SPISR_OFFSET));

    int configured_mstr = 0;
    if ((*(my_periph + SPI_SPISR_OFFSET) & SPI_SR_SLV_MODE_SEL_MASK) != 0)
    {
        configured_mstr = 1;
        return 0;
    }
    else
    {
        printf("\nUnable to set SPI to master mode!!\n\n");
        return -1;
    }
    
}


int spi_write(uint32_t word, volatile unsigned int *my_periph)
{

    //set data transmit register to word to send
    *(my_periph + SPI_DTR_OFFSET) = word;

    return 0;
}

int spi_write_array(uint32_t array[ARRSIZE], volatile unsigned int *my_periph)
{

        volatile unsigned int *spi_dtr = my_periph + SPI_DTR_OFFSET; //pointer to data transmit register
        
        for(int i = 0; i < ARRSIZE; i++)
        {
            *spi_dtr = array[i];
        }  
}

int set_cs(volatile unsigned int *my_periph)
{
    //Flip LSB
    *(my_periph + SPI_SPISSR_OFFSET) &= 0xFFFE;
}

int clear_cs(volatile unsigned int *my_periph)
{
    //Flip LSB
    *(my_periph + SPI_SPISSR_OFFSET) |= 0x0001;
}

int master_transact_block(volatile unsigned int *my_periph)
{
    *(my_periph + SPI_SPICR_OFFSET) |= SPI_CR_MSTR_INHIBIT_MASK;
}

int master_transact_unblock(volatile unsigned int *my_periph)
{
    *(my_periph + SPI_SPICR_OFFSET) &= ~SPI_CR_MSTR_INHIBIT_MASK;
}