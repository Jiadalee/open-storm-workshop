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
#include "project.h"
int depth_analog = -9999;  
    
int take_analog_depth_reading(){
    //initialize the variables
    int16 adc_result = 0;
    float volt_reading = 0;
    int distance = 9999;
    
    //start ADC
    ADC_SAR_1_Wakeup();
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();
    
    //Power up sensor
    Ultrasonic_power_Write(1);
    CyDelay(1000);
    
    // Get the result from ADC
    adc_result = ADC_SAR_1_GetResult16();
    
    //Convert the result to volts
    volt_reading = ADC_SAR_1_CountsTo_Volts(adc_result);
    distance = volt_reading*(5120/4.75);
    
    //power down sensor
    Ultrasonic_power_Write(0);
    
    //Stop ADC
    ADC_SAR_1_StopConvert();
    ADC_SAR_1_Sleep();
    
    return distance;
    
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    for(;;)
    {
        /* Place your application code here. */
        Pin_LED_Write(1);
        CyDelay(200);
        Pin_LED_Write(0);
        CyDelay(200);
        
        //depth measurement
        depth_analog = take_analog_depth_reading();
        CyDelay(1000);
    }
}

/* [] END OF FILE */
