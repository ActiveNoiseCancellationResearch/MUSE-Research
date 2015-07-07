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
#include "mic_model.h"
#include "ANC.h"
#define FILTER_ORDER (16)
#define FO1 (FILTER_ORDER-1)
static int recent_samps [FILTER_ORDER];
static int model_coeffs [FILTER_ORDER];

void 
mic_model_new(int *coeffs)
{
    int i;
    for (i=0; i<FILTER_ORDER; ++i)
    {
       recent_samps [i]=0;
       model_coeffs[i]=coeffs[i];
    }
}

int
mic_model_new_sample (int x)
{
    int sum=0;
    int i=0;
    static int wptr=0;
    recent_samps[wptr]=x;
    for (i=0 ; i<FILTER_ORDER ; ++i)
        {
            sum+=recent_samps[(wptr-i+FILTER_ORDER)&FO1]*model_coeffs[i];
        }
    sum=(sum+FP_ROUND)>>FP_SHIFT;
    return sum;        
    wptr=(wptr+1)&FO1;
}


/* [] END OF FILE */
