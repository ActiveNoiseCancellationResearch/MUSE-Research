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
static int recent_samps_in [FILTER_ORDER];
static int model_coeffs [FILTER_ORDER];
static int recent_samps_v [FILTER_ORDER];

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
}
int 
canceller_new_sample(int input_samp)
{
    //recent_samps_in[FILTER_ORDER - 1];
    int i;
    int sum=0;
    int tmp;
    int v;
    static int wptr=0;    //circular buffer write pointer, for recent_samps_in
    recent_samps_in[wptr]= input_samp;
    tmp=hs_model_new_sample(input_samp);
    v=mic_model_new_sample(tmp);
    recent_samps_v[wptr]=v;
    // into mic_model filter
              
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
    int mu_prime=(MU*(1<<FP_SHIFT)+0.5);     
    for (i=0 ; i<FILTER_ORDER;++i)
    {
        int temp;
        temp = (e_*recent_samps_v[i]+FP_ROUND)>>FP_SHIFT;
        temp = (mu_prime*temp+FP_ROUND)>>FP_SHIFT;
        model_coeffs[i]=model_coeffs[i]-temp;
    }
}

/* [] END OF FILE */
