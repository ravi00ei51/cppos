.section ".datax"
val1:    .4byte 0x20004000        @ Read-only array of bytes
val2:    .4byte start+1
val3:    .4byte __interrupt00_addr_start+1
val4:    .4byte __interrupt01_addr_start+1
val5:    .4byte __interrupt02_addr_start+1
val6:    .4byte __interrupt03_addr_start+1
val7:    .4byte __interrupt04_addr_start+1
val8:    .4byte __interrupt05_addr_start+1
val9:    .4byte __interrupt06_addr_start+1
val10:   .4byte __interrupt07_addr_start+1
val11:   .4byte __interrupt08_addr_start+1
val12:   .4byte __interrupt09_addr_start+1
val13:   .4byte __interrupt0A_addr_start+1
val14:   .4byte __interrupt0B_addr_start+1
val15:   .4byte __interrupt0C_addr_start+1
val16:   .4byte __interrupt0D_addr_start+1
val17:   .4byte __interrupt0E_addr_start+1
val18:   .4byte __interrupt0F_addr_start+1


        .text
reset1:  b reset1
reset2:  b reset2
reset3:  b reset3
reset4:  b reset4
reset5:  b reset5
reset6:  b reset6
reset7:  b reset7
reset8:  b reset8
reset9:  b reset9
reset10: b reset10
reset11: b reset11
reset12: b reset12
reset13: b reset13
reset14: b reset14
reset15: b reset15
reset16: b reset16
.align 

start:                           @ Label, not really required
        cpsie i
        bl __test1_start+1
stop:   b stop                   @ Infinite loop to stop execution

