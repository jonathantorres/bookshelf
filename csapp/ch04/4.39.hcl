bool D_stall = E_icode in { IMRMOVQ, IPOPQ } &&
                E_dstM in { d_srcA, D_srcB };
