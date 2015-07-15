/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "hs_model.h"                       
#include "mic_model.h"
#include "ANC.h"  
#include "canceller.h"

#define FILTER_ORDER (16)
#define FO1 (FILTER_ORDER-1) 
#define MU (0.001)
#define MU_Q20_12 ( (int) (MU * (1<<FP_SHIFT) + 0.5) )

static int recent_samps_in [FILTER_ORDER];
static int model_coeffs [FILTER_ORDER];
static int recent_samps_v [FILTER_ORDER];
static int wptr;                            //circular buffer write pointer, for recent_samps_in

void 
canceller_new(void)
{
    int i;
    for (i=0; i<FILTER_ORDER; ++i)
    {
        recent_samps_v [i]=0;
        recent_samps_in [i]=0;
        model_coeffs[i]=0;    
    }
    model_coeffs[0]=1;
    
    wptr = 0;
}


int 
canceller_new_sample(int input_samp)
{
    //recent_samps_in[FILTER_ORDER - 1];
    int i;
    int sum=0;
    int tmp;
    int v;
    
    // Deposit the newest input sample at wptr
    recent_samps_in[wptr]= input_samp;
    
    // Filter the new input sample through the headphone-speaker model
    tmp=hs_model_new_sample(input_samp);
        
    v=tmp;
    
    recent_samps_v[wptr]=v;

    sum=0;
    for (i=0 ; i<FILTER_ORDER ; ++i)
    {
        sum+=recent_samps_in[(wptr-i+FILTER_ORDER)&FO1]*model_coeffs[i];
    }

    sum=(sum+FP_ROUND)>>FP_SHIFT;
    
    wptr=(wptr+1)&FO1;
    
    return sum;
}


void
canceller_coeff_update (int e_)
{
    int i;

    for (i=0 ; i<FILTER_ORDER;++i)
    {
        int temp;
        
        // Compute tap weight update:
        //
        //   w[k] = w[k] - u * e * v[n-k]
        //
        // where n is the current time.
       
        // So - we assume that the new sample has been done for the current time,
        // which results in wptr pointing to the next location (one beyond the current
        // location in recent_samps_v).  That's why we have the '- 1' in the expression below.
        temp = (e_*recent_samps_v[(wptr - 1 - i + FILTER_ORDER) & FO1]+FP_ROUND)>>FP_SHIFT;         // Compute e * v[n-k], 
        temp = (MU_Q20_12*temp+FP_ROUND)>>FP_SHIFT;                                                  // Compute u * e * v[n-k]

        model_coeffs[i] = model_coeffs[i] - temp;
    }
}

/* [] END OF FILE */
