        noop
        halt
cool    jalr    1       1
        lw      0       5       2000
        sw      4       2       30
        beq     4       4       -2
        nor     3       3       3
        add     4       3       1
start   add     1       2       1       decrement reg1
        beq     0       1       2       goto end of program when reg1==0
        beq     0       0       start   go back to the beginning of the loop
        noop
done    halt                            end of program
five    .fill   5
neg1    .fill   -1
stAddr  .fill   start                   will contain the address of start (2)
