/**
 * @file ctl_main.cpp
 * @author Javnson (javnson@zju.edu.cn)
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright GMP(c) 2024
 *
 */

#include <xplt.peripheral.h>

#include <ctl/component/intrinsic/discrete/lead_lag.h>

//=================================================================================================
// include Necessary control modules

#include <ctl/component/interface/adc_channel.h>
#include <ctl/component/interface/pwm_channel.h>
#include <ctl/component/interface/spwm_modulator.h>

#include <ctl/framework/cia402_state_machine.h>

#ifndef _FILE_CTL_MAIN_H_
#define _FILE_CTL_MAIN_H_

#ifdef __cplusplus
extern "C"
#endif // __cplusplus

//=================================================================================================
// controller modules with extern



//=================================================================================================
// function prototype

void ctl_init(void);

void ctl_mainloop(void);

void clear_all_controllers();

//=================================================================================================
// controller process

extern ctl_lead_t lead_comp;//先申明变量
extern adc_channel_t input_wave_adc;
extern ctrl_gt comp_out;
extern ctl_lead_t lead_comp2;
extern uint16_t cur_val_lead_comp;

// periodic callback function things.
GMP_STATIC_INLINE void ctl_dispatch(void)
{
    if(cur_val_lead_comp == 1)
    {
        comp_out = ctl_step_lead(&lead_comp,input_wave_adc.control_port.value);//对标幺后信号做超前补偿，同理&lead_comp要在这里上面先声明;然后去main.c中初始化补偿器
    }
    else
    {
        comp_out = ctl_step_lead(&lead_comp2,input_wave_adc.control_port.value);
    }
}

#ifdef __cplusplus
}
#endif // _cplusplus

#endif // _FILE_CTL_MAIN_H_
