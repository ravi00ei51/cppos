.global    test_func
.data
val1:    .4byte 0x20005000        @ Read-only array of bytes
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
val12:   .4byte reset10
val13:   .4byte reset11+1
val14:   .4byte reset12+1
val15:   .4byte reset13+1
val16:   .4byte reset14+1
val17:   .4byte reset15+1
val18:   .4byte reset16+1

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
        mov   r4, #4             @ Load register r0 with the value 5
        mov   r5, #5             @ Load register r1 with the value 4
        add   r6, r4, r5         @ Add r0 and r1 and store in r2
        ldr   r4, =0x40021000
        str   r1, [r4]
#        ldr   r0, =flash_sdata
#        ldr   r1, =ram_sdata
#        ldr   r2, =ram_data_size
#copy:
#        ldmia   r0, {r3}
#        stmia   r1, {r3}
#        cmp     r1,r2
#        bne   copy
        cpsie i
        b 0x08003000
stop:   b stop                   @ Infinite loop to stop execution

