; Register | Action on read                           | Action on write
;----------------------------------------------------------------------------------------
; R0       | Returns zero                             | Writes value to display module
; R1-R52   | Reads value from register                | Writes value to register
; R53      | Returns bitwise AND of R54 with NOT R53  | Writes value to register
; R54      | Returns bitwise AND of R53 with NOT R54  | Writes value to register
; R55      | Returns zero                             | Writes value to register
; R56      | Returns value in R55 if register R56 is  | Writes value to register
;          | non-zero, and the value in R57 otherwise | 
; R57      | Returns zero                             | Writes value to register
; R58      | Returns R58 rotated right one place      | Writes value to register
; R59      | Returns R59 rotated left one place       | Writes value to register
; R60      | Reads value from register                | Writes value to register
; R61      | Returns sum of R60 and R61               | Writes value to register
; R62      | Reads NOT R62                            | Writes value to register
; R63      | Returns program counter value            | Causes branch to given target
;----------------------------------------------------------------------------------------
 0 :       UNUSED
 1 :       MOV R62, R42 ; Compute negative value of upper limit
 2 :       MOV R61, R48 ; Load -1 in adder as second operand
 3 :       MOV R60, R62 ; negative (upper limit - 1) as first operand of adder
 4 :       MOV R60, R61 ; perform addition to set the Carry
 5 :       MOV R61, R41 ; current variable as second operand of adder
 6 :       MOV R56, R61 ; Perform the addition whose result should be 0 if limit has been reached
 7 :       MOV R55, R47 ; Prepare branch if limit non reached
 8 :       MOV R57, R44 ; Prepare branch if limit reached
 9 :       MOV R63, R56 ; Branch on addition result
10 :       MOV R60, R45 ; Preparing addition
11 :       MOV R0 , R41 ; Display variable
12 :       MOV R63, R43 ; Preparing branch at the beginning of the loop
13 :       MOV R41, R61 ; Incrementing current variable
14 :       MOV R63, R44 ; Branching on end of the loop
15 :       MOV R0 , R46 ; End of loop
16 :       0x0000
17 :       0x0000
18 :       0x0000
19 :       0x0000
20 :       0x0000
21 :       0x0000
22 :       0x0000
23 :       0x0000
24 :       0x0000
25 :       0x0000
26 :       0x0000
27 :       0x0000
28 :       0x0000
29 :       0x0000
30 :       0x0000
31 :       0x0000
32 :       0x0000
33 :       0x0000
34 :       0x0000
35 :       0x0000
36 :       0x0000
37 :       0x0000
38 :       0x0000
39 :       0x0000
40 :       0x0000
41 :       0x0000       ; Initialisation running variable to 0
42 :       0x0009       ; Set upper limit -1
43 :       0x0002       ; Branch value to restart the loop
44 :       0x000e       ; Branch value to end the loop
45 :       0x0001       ; Increment value
46 :       0xffff       ; Final value
47 :       0x000b       ; Branch value to continue the loop
48 :       0xfffe       ; -1
49 :       0x0000
50 :       0x0000
51 :       0x0000
52 :       0x0000
53 :       UNUSED
54 :       UNUSED
55 :       UNUSED
56 :       UNUSED
57 :       UNUSED
58 :       UNUSED
59 :       UNUSED
60 :       0x0000
61 :       UNUSED
62 :       UNUSED
63 : <PC>: 0x0001       ; Initial PC
