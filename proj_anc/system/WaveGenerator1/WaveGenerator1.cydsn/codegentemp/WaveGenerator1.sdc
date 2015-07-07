# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\shubhamt\Documents\PSoC Creator\WaveGenerator1\WaveGenerator1.cydsn\WaveGenerator1.cyprj
# Date: Mon, 06 Jul 2015 21:19:54 GMT
#set_units -time ns
create_clock -name {ADC_SAR_theACLK(routed)} -period 1000 -waveform {0 500} [list [get_pins {ClockBlock/dclk_0}]]
create_clock -name {Clock(routed)} -period 125000 -waveform {0 62500} [list [get_pins {ClockBlock/dclk_2}]]
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {ADC_SAR_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 25 49} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {UART_1_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 27 53} -nominal_period 1083.3333333333333 [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {Clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3001 6001} [list [get_pins {ClockBlock/dclk_glb_2}]]


# Component constraints for C:\Users\shubhamt\Documents\PSoC Creator\WaveGenerator1\WaveGenerator1.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\shubhamt\Documents\PSoC Creator\WaveGenerator1\WaveGenerator1.cydsn\WaveGenerator1.cyprj
# Date: Mon, 06 Jul 2015 21:19:41 GMT
