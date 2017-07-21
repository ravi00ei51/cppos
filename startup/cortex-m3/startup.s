.section ".datax"
val1:    .4byte 0x20004000        @ Read-only array of bytes
val2:    .4byte start+1
val3:    .4byte reset1
val4:    .4byte reset2
val5:    .4byte reset3
val6:    .4byte reset4
val7:    .4byte reset5
val8:    .4byte reset6
val9:    .4byte reset7
val10:   .4byte reset8
val11:   .4byte reset9
val12:   .4byte __testS_start+1
val13:   .4byte reset11
val14:   .4byte reset12
val15:   .4byte __testP_start+1
val16:   .4byte __test_start+1
val17:   .4byte reset15
val18:   .4byte reset16


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

