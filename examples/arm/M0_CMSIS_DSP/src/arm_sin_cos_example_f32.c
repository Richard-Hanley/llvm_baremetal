#include <stdlib.h> 
#include <math.h>     
#include "arm_math.h" 
 
/* ---------------------------------------------------------------------- 
* Defines each of the tests performed 
* ------------------------------------------------------------------- */ 
#define MAX_BLOCKSIZE	32 
#define DELTA           (0.000001f) 
 
 
/* ---------------------------------------------------------------------- 
* Test input data for Floating point sin_cos example for 32-blockSize 
* Generated by the MATLAB randn() function 
* ------------------------------------------------------------------- */ 
 
const float32_t testInput_f32[MAX_BLOCKSIZE] =  
{    
 -1.244916875853235400,	-4.793533929171324800,  0.360705030233248850,
  0.827929644170887320, -3.299532218312426900,  3.427441903227623800,	
  3.422401784294607700,	-0.108308165334010680,  0.941943896490312180,
  0.502609575000365850,	-0.537345278736373500,  2.088817392965764500,
 -1.693168684143455700,	 6.283185307179590700, -0.392545884746175080,
  0.327893095115825040,	 3.070147440456292300,  0.170611405884662230,
 -0.275275082396073010,	-2.395492805446796300,  0.847311163536506600,
 -3.845517018083148800,	 2.055818378415868300,  4.672594161978930800,
 -1.990923030266425800,	 2.469305197656249500,  3.609002606064021000,
 -4.586736582331667500, -4.147080139136136300,  1.643756718868359500,
 -1.150866392366494800,	 1.985805026477433800 
};  
 
const float32_t testRefOutput_f32 = 1.000000000; 
 
/* ---------------------------------------------------------------------- 
* Declare Global variables  
* ------------------------------------------------------------------- */ 
uint32_t blockSize = 32; 
float32_t  testOutput;  
float32_t  cosOutput;  
float32_t  sinOutput;  
float32_t  cosSquareOutput;  
float32_t  sinSquareOutput; 
 
/* ---------------------------------------------------------------------- 
* Max magnitude FFT Bin test 
* ------------------------------------------------------------------- */ 

arm_status status; 
 
int32_t main(void) 
{ 
   float32_t diff; 
   uint32_t i; 

   printf("Starting Test...\n");
   for (i=0; i < blockSize; i++) 
   { 
      cosOutput = arm_cos_f32(testInput_f32[i]); 
      printf("Cos %f = %f\n", testInput_f32[i], cosOutput);
 
      sinOutput = arm_sin_f32(testInput_f32[i]); 
      printf("Sin %f = %f\n", testInput_f32[i], sinOutput);

      arm_mult_f32(&cosOutput, &cosOutput, &cosSquareOutput, 1); 
      printf("Cos squared %f = %f\n", cosOutput, cosSquareOutput);

      arm_mult_f32(&sinOutput, &sinOutput, &sinSquareOutput, 1); 
      printf("Sin squared %f = %f\n", sinOutput, sinSquareOutput);

      arm_add_f32(&cosSquareOutput, &sinSquareOutput, &testOutput, 1);
      printf("Add %f and %f = %f\n", cosSquareOutput, sinSquareOutput, testOutput);
 
      /* absolute value of difference between ref and test */ 
      diff = fabsf(testRefOutput_f32 - testOutput); 
      /* Comparison of sin_cos value with reference */ 
      if (diff > DELTA) 
      { 
         printf("Diff failure %f\n", diff);
         exit(EXIT_FAILURE); /* just for QEMU testing */
         while(1); 
      } 
   } 
   printf("Ending Test...\n");
   exit(EXIT_SUCCESS); /* just for QEMU testing */
   while(1); /* main function does not return */
} 
 