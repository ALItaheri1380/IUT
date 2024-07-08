primitive Priority_4bit0(out0 , a , b , c , d , enable);
    
    output out0;
    input a , b , c , d , enable;

    table
    //  a b c d enable: output0
        ? ? ? ? 0 : 0;
        0 0 0 0 1 : x;
        0 0 0 1 1 : 0;
        0 0 1 ? 1 : 1;
        0 1 ? ? 1 : 0;
        1 ? ? ? 1 : 1;      
    endtable

endprimitive

primitive Priority_4bit1(out1 , a , b , c , d , enable);

    output out1;
    input a , b , c , d , enable;

    table
    //  a b c d enable: output1
        ? ? ? ? 0 : 0;
        0 0 0 0 1 : x;
        0 0 0 1 1 : 0;
        0 0 1 ? 1 : 0;
        0 1 ? ? 1 : 1;
        1 ? ? ? 1 : 1; 
    endtable
endprimitive