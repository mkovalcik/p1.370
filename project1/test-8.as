first	.fill	40
		add 	0		0		0
		sw		3		1		0
		sw		2 		0		0
		sw		0 		4 		0
		jalr	0		0
		add 	1 		0 		0
whoop   .fill   99
		jalr	0		1
		nor		5		3		1
		noop
        lw      0       1       five    load reg1 with 5 (symbolic address)
        lw      4       2       3       load reg2 with -1 (numeric address)
start   add     1       2       1       decrement reg1
        beq     0       1       2       goto end of program when reg1==0
        beq     0       0       start   go back to the beginning of the loop
        noop
done    halt                            end of program
five    .fill   5
neg1    .fill   -1
stAddr  .fill   start                   will contain the address of start (2)
