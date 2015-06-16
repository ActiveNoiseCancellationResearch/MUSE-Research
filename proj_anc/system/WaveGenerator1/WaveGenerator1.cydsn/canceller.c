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
#define CANCELLER_FILTER_ORDER (10)
 int hs_model [sizeof(ui_data)];
        int mic_model [sizeof(ui_data)];
static int recent_samps_in [CANCELLER_FILTER_ORDER];
static int model_coeffs [CANCELLER_FILTER_ORDER];
static int recent_samps_v [CANCELLER_FILTER_ORDER];

void 
canceller_new(void)
{
    int i;
    for (i=0; i<CANCELLER_FILTER_ORDER; ++i)
    {
       recent_samps_in [i]=0;
       model_coeffs[i]=0;    
    }
    model_coeffs[0]=1;
}
int
canceller_new_sample(
    int input_samp)
{
    
            recent_samps_in[2:end] = my_canceller.recent_samps_in[1:end-1];    // deletes last value in array 
            recent_samps_in[1] = input_samp;                                   // adds input_samp to array
            current_output = recent_samps_in*model_coeffs';       // sum of products //make for loop here
            temp = hs_model.new_sample[input_samp];   //                         // cascaded hs_model filter
            v = mic_model.new_sample[temp];                                    // into mic_model filter
            recent_samps_v[2:end] = recent_samps_v[1:end-1];       
            recent_samps_v[1] = v;  
        }
/* [] END OF FILE */
