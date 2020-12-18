target remote localhost:3000
monitor halt
file ./build/RTOSDemo.axf
load
set $pc=Reset_Handler
b main
#b prvPortStartFirstTask
add-symbol-file ~/Projects/dmon/build/top.sdk/app/Debug/app.elf 0x100000
#b DMon_SWI_Handler
#b DMon_IRQ_Handler
#b DMon_ERR_Handler
continue
