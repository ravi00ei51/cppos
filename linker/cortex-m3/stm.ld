SECTIONS {
   . = 0x08000000;
   flash_sdata = . ;
   . = 0x08000200;
   .test : { __test_start = .; * (.test) ;__test_end = .; }
   .testPendSV : { __testP_start = .; * (.testPendSV) ;__testP_end = .; }
   .testSVC : { __testS_start = .; * (.testSVC) ;__testS_end = .; }
   .test1 : { __test1_start = .; * (.test1); __test1_end = .; }
   .init_array : { __init_array_start = .; KEEP (*(.init_array*)) ; __init_array_end = .; }
   .text : {* (.text) }
   . = 0x20000000;
   .data : AT(0x08000000){ ram_0data = . ;KEEP(*(.datax)); ram_sdata = . ;* (.data); ram_edata = . ; }
   .bss  : { *(.bss); }
}
