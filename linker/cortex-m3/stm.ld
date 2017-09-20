SECTIONS {
   . = 0x08000000;
   flash_sdata = . ;
   . = 0x08000200;
   .interrupt00 : { __interrupt00_addr_start = .; KEEP(* (.interrupt00)) ;__interrupt00_addr_end = .; }
   .interrupt01 : { __interrupt01_addr_start = .; KEEP(* (.interrupt01)) ;__interrupt01_addr_end = .; }
   .interrupt02 : { __interrupt02_addr_start = .; KEEP(* (.interrupt02)) ;__interrupt02_addr_end = .; }
   .interrupt03 : { __interrupt03_addr_start = .; KEEP(* (.interrupt03)) ;__interrupt03_addr_end = .; }
   .interrupt04 : { __interrupt04_addr_start = .; KEEP(* (.interrupt04)) ;__interrupt04_addr_end = .; }
   .interrupt05 : { __interrupt05_addr_start = .; KEEP(* (.interrupt05)) ;__interrupt05_addr_end = .; }
   .interrupt06 : { __interrupt06_addr_start = .; KEEP(* (.interrupt06)) ;__interrupt06_addr_end = .; }
   .interrupt07 : { __interrupt07_addr_start = .; KEEP(* (.interrupt07)) ;__interrupt07_addr_end = .; }
   .interrupt08 : { __interrupt08_addr_start = .; KEEP(* (.interrupt08)) ;__interrupt08_addr_end = .; }
   .interrupt09 : { __interrupt09_addr_start = .; KEEP(* (.interrupt09)) ;__interrupt09_addr_end = .; }
   .interrupt0A : { __interrupt0A_addr_start = .; KEEP(* (.interrupt0A)) ;__interrupt0A_addr_end = .; }
   .interrupt0B : { __interrupt0B_addr_start = .; KEEP(* (.interrupt0B)) ;__interrupt0B_addr_end = .; }
   .interrupt0C : { __interrupt0C_addr_start = .; KEEP(* (.interrupt0C)) ;__interrupt0C_addr_end = .; }
   .interrupt0D : { __interrupt0D_addr_start = .; KEEP(* (.interrupt0D)) ;__interrupt0D_addr_end = .; }
   .interrupt0E : { __interrupt0E_addr_start = .; KEEP(* (.interrupt0E)) ;__interrupt0E_addr_end = .; }
   .interrupt0F : { __interrupt0F_addr_start = .; KEEP(* (.interrupt0F)) ;__interrupt0F_addr_end = .; }
   .test : { __test_start = .;KEEP( * (.test)) ;__test_end = .; }
   .testPendSV : { __testP_start = .;KEEP( * (.testPendSV)) ;__testP_end = .; }
   .testSVC : { __testS_start = .; KEEP(* (.testSVC)) ;__testS_end = .; }
   .test1 : { __test1_start = .; KEEP(* (.test1)); __test1_end = .; }
   .init_array : { __init_array_start = .; KEEP (*(.init_array*)) ; __init_array_end = .; }
   .text : {* (.text) }
   . = 0x20000000;
   .data : AT(0x08000000){ ram_0data = . ;KEEP(*(.datax)); ram_sdata = . ;KEEP(* (.data)); ram_edata = . ; }
   .bss  : { *(.bss); }
}
