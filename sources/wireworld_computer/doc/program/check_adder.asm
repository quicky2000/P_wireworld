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
 1 :       MOV R60, R40 ;
 2 :       MOV R61, R43 ;
 3 :       MOV R0 , R61 ;
 4 :       MOV R60, R41 ; Prepare computation of negative value
 5 :       MOV R61, R42 ; to set the carry to one and have
 6 :       MOV R60, R61 ; the correct zero value
 7 :       MOV R61, R43 ;
 8 :       MOV R0 , R61 ;
 9 :       MOV R63, R47 ; Prepare infinite loop
10 :       MOV R1 , R1  ; NOP
11 :       0x0000
12 :       0x0000
13 :       0x0000
14 :       0x0000
15 :       0x0000
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
40 :       0xfffc       ; -3
41 :       0xfffe       ; -1
42 :       0xfffd       ; -2
43 :       0x0003       ; 3
44 :       0x0007       ; Branch value to end the loop
45 :       0x0001       ; Increment value
46 :       0xffff       ; Final value
47 :       0x0009       ; Branch value to continue the loop
48 :       0x0000
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
