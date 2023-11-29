/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include <stdlib.h>

#include "conv_sobel.h" // Header file of the created ip
#include "ff.h" // Header file for fat filesystem
#include "xil_io.h" // Header file for AXI communication
#include "xil_types.h" // Header file for datatypes
#include "xparameters.h"

#include "platform.h" // Header file for configuring the SD card
#include "xil_printf.h"

#define MEM_BASE_ADDR XPAR_PS7_DDR_0_S_AXI_BASEADDR // DDR AXI base address
#define CONV_BASE_ADDR XPAR_CONV_SOBEL_0_S00_AXI_BASEADDR // convolution IP Base Address
#define SIZE 64516

// Offset Address for the Multiplier AXI Register Address
#define REG0_OFFSET_ADDR CONV_SOBEL_S00_AXI_SLV_REG0_OFFSET
#define REG1_OFFSET_ADDR CONV_SOBEL_S00_AXI_SLV_REG1_OFFSET
#define REG2_OFFSET_ADDR CONV_SOBEL_S00_AXI_SLV_REG2_OFFSET
#define REG3_OFFSET_ADDR CONV_SOBEL_S00_AXI_SLV_REG3_OFFSET

static const char *card_path = "0:/"; // where is the SD card is mounted, i.e., card path
static FATFS fs; // Pointer to the filesystem
static FIL read_file, write_file; // File pointers to read and write in file
FRESULT status;

unsigned int n_bytes;


int main()
{
    init_platform(); // Initialize all the peripherals and configures everything

    // All the memories are byte addressable
    // Memory Allocation in DDR
    u32* arr1 = (u32*)calloc(SIZE, sizeof(u32));
    u32* arr2 = (u32*)calloc(SIZE, sizeof(u32));
    u32* arr3 = (u32*)calloc(SIZE, sizeof(u32));
    u32* ans = (u32*)calloc(SIZE, sizeof(u32));

    status = f_mount(&fs, card_path,1); // Mount the sd card and (1) load it immediately
    printf("Card Mounting Status = %d\n",status);

    // Read Data from File 1

    status = f_open(&read_file,"i1.txt",FA_READ); //Open the file in read mode from SD card
    // Note: The length of the file name must not be greater than 12 characters
    printf("File Opening status = %d\n",status);

    if(status == FR_OK){
    	/*
			FRESULT f_read (
  	  	  	  FIL* FileObject,    // Pointer to the file object structure
  	  	  	  void* Buffer,       // Pointer to the buffer to store read data
  	  	  	  UINT ByteToRead,    // Number of bytes to read
  	  	  	  UINT* ByteRead      // Pointer to the variable to return number of bytes read
			);
    	 */
    	status = f_read(&read_file, arr1, SIZE*sizeof(u32),&n_bytes);
    	printf("File reading status = %d\n",status);
    	printf("arr1[64] = %ld\n\r",arr1[64]);

    	status = f_close(&read_file);
    	printf("File closing status = %d\n",status);
    }

    // Reading from file 2

    status = f_open(&read_file,"i2.txt",FA_READ); //Open the file in read mode from SD card
        // Note: The length of the file name must not be greater than 12 characters
    printf("File Opening status = %d\n",status);

    if(status == FR_OK){
        	/*
    			FRESULT f_read (
      	  	  	  FIL* FileObject,    // Pointer to the file object structure
      	  	  	  void* Buffer,       // Pointer to the buffer to store read data
      	  	  	  UINT ByteToRead,    // Number of bytes to read
      	  	  	  UINT* ByteRead      // Pointer to the variable to return number of bytes read
    			);
        	 */
        status = f_read(&read_file, arr2, SIZE*sizeof(u32),&n_bytes);
        printf("File reading status = %d\n",status);
        printf("arr2[64] = %ld\n\r",arr2[64]);

        status = f_close(&read_file);
        printf("File closing status = %d\n",status);
       }
    status = f_open(&read_file,"i3.txt",FA_READ); //Open the file in read mode from SD card
        // Note: The length of the file name must not be greater than 12 characters
    printf("File Opening status = %d\n",status);

    if(status == FR_OK){
        	/*
    			FRESULT f_read (
      	  	  	  FIL* FileObject,    // Pointer to the file object structure
      	  	  	  void* Buffer,       // Pointer to the buffer to store read data
      	  	  	  UINT ByteToRead,    // Number of bytes to read
      	  	  	  UINT* ByteRead      // Pointer to the variable to return number of bytes read
    			);
        	 */
        status = f_read(&read_file, arr3, SIZE*sizeof(u32),&n_bytes);
        printf("File reading status = %d\n",status);
        printf("arr3[64] = %ld\n\r",arr3[64]);

        status = f_close(&read_file);
        printf("File closing status = %d\n",status);
       }

    // Perform Element wise multiplication

   /* for(uint8_t i= 0; i<SIZE ;i++){

    	// Writing from PS to PL
    	MYIP_SYNC_MUL32_mWriteReg(MULT_BASE_ADDR, REG0_OFFSET_ADDR, arr1[i]);
    	MYIP_SYNC_MUL32_mWriteReg(MULT_BASE_ADDR, REG1_OFFSET_ADDR, arr2[i]);

    	// Reading from PL
    	arr3[i]= MYIP_SYNC_MUL32_mReadReg(MULT_BASE_ADDR, REG2_OFFSET_ADDR);
    }*/
	for(u32 i = 0; i < SIZE; i++){
		//printf("Entered Iteration : %ld\n",i);
		CONV_SOBEL_mWriteReg(
				CONV_BASE_ADDR,
				REG0_OFFSET_ADDR,
				arr1[i]
		);

		CONV_SOBEL_mWriteReg(
				CONV_BASE_ADDR,
				REG1_OFFSET_ADDR,
				arr2[i]
		);

		CONV_SOBEL_mWriteReg(
				CONV_BASE_ADDR,
						 REG2_OFFSET_ADDR,
						arr3[i]
				);


		ans[i] = CONV_SOBEL_mReadReg(
				CONV_BASE_ADDR,
				 REG3_OFFSET_ADDR
		);
		//printf("Leaving Iteration : %ld\n",i);
	}

    printf("(arr1[64]*arr2[64])+arr3[64] = %ld*%ld+%ld=%ld\n\r", arr1[64], arr2[64], arr3[64],ans[64]);

    // Open file for writing
    status = f_open(&write_file, "ans.txt", FA_WRITE | FA_CREATE_ALWAYS);
   	printf("File opening for write: %d\n", status);

   	if(status == FR_OK){
   		// Write in the file
   		status = f_write(&write_file, ans, SIZE*sizeof(u32), &n_bytes);
    	printf("File writing status: %d\n", status);

    	status = f_close(&write_file);
    	printf("Closing file: %d\n", status);
    }

   		// Unmount the SD Card

    	status = f_unmount(card_path);
    	printf("Card unmounting: %d\n\n", status);
    	free(arr1);
    	free(arr2);
    	free(arr3);
    	free(ans);


    cleanup_platform();
    return 0;
}

