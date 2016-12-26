SECTIONS {
   . = 0x08000000;
   .data : {* (.data)}
   . = 0x08003000;
   .test : {* (.test)}
   .text : {* (.text)} 
}
