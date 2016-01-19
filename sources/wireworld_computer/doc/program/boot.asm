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
 0 :                       UNUSED
 1 :                       MOV R1, R1
 2 :                       MOV R1, R1
 3 :                       MOV R1, R1
 4 :                       MOV R1, R1
 5 :                       MOV R1, R1
 6 :                       MOV R1, R1
 7 :                       MOV R0 , R47
 8 :                       MOV R1, R1
 9 :                       MOV R1, R1
10 :                       MOV R1, R1
10 :                       MOV R1, R1
11 :                       MOV R1, R1
12 :                       MOV R1, R1
13 :                       UNUSED
14 :                       UNUSED
15 :                       UNUSED
16 :                       UNUSED
17 :                       UNUSED
18 :                       UNUSED
19 :                       UNUSED
20 :                       UNUSED
21 :                       UNUSED
22 :                       UNUSED
23 :                       UNUSED
24 :                       UNUSED
25 :                       UNUSED
26 :                       UNUSED
27 :                       UNUSED
28 :                       UNUSED
29 :                       UNUSED
30 :                       UNUSED
31 :                       UNUSED
32 :                       UNUSED
33 :                       UNUSED
34 :                       UNUSED
35 :                       UNUSED
36 :                       UNUSED
37 :                       UNUSED
38 :                       UNUSED
39 :                       UNUSED
40 :                       UNUSED
41 :                       UNUSED
42 :                       UNUSED
43 :                       UNUSED
44 :                       UNUSED
45 :                       UNUSED
46 :                       0x0002
47 :                       0x0001                         
48 :                       UNUSED                         
49 :                       UNUSED
50 :                       UNUSED
51 :                       UNUSED                         
52 :                       UNUSED                         
53 :                       UNUSED
54 :                       UNUSED
55 :                       UNUSED
56 :                       UNUSED
57 :                       UNUSED
58 :                       UNUSED
59 :                       UNUSED
60 :                       UNUSED
61 :                       MOV R63, R47
62 :                       0xFFD1
63 : <PC>                : 0x003D       ; Starting PC
