word dstE = [
    icode in { IRRMOVQ } && Cnd : rB;
    icde in { IIRMOVQ, IOPQ } : rB;
    icode in { IPUSHQ, IPOPQ, ICALL, IRET } : RRSP;
    1 : RNONE;
];
