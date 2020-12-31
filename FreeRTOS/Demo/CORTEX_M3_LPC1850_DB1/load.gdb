target remote localhost:3000
monitor halt
#mem 0x10000000 0x20000000 32 rw
#mem 0x80000000 0xC0000000 32 rw
file ./build/RTOSDemo.axf
load
set $pc=Reset_Handler
b main
add-symbol-file ~/Projects/dmon/build/top.sdk/app/Debug/app.elf 0x100000
#b prvPortStartFirstTask
#b DMon_SWI_Handler
#b DMon_IRQ_Handler
#b DMon_ERR_Handler
continue
