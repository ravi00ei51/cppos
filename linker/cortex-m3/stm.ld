SECTIONS {
   . = 0x08000000;
   flash_sdata = . ;
   . = 0x08003000;
   .test : {* (.test)}
   .init_array : { __init_array_start = .; KEEP (*(.init_array*)) ; __init_array_end = .; }
   . = 0x08004000;
   .text : {* (.text) }
   . = 0x20000000;
   .data : AT ( 0x08000000 ) { ram_0data = . ;*(.datax); ram_sdata = . ;* (.data); ram_edata = . ; }
   .bss  : AT ( 0x08000000 + SIZEOF(.datax ) + SIZEOF(.data) ) { bss_sdata = . ;*(.bss);bss_edata = . ; }
}
