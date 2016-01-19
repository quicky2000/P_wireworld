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
 0 :             UNUSED
 1 :             MOV R0 , R30 ; set display to 2
 2 :             MOV R54, R31 ; initialise mask register for sign bit test
 3 :             MOV R32, R33 ; set candidate prime p=3
 4 :             MOV R60, R34 ; the trial divisor q is stored in the adder as its negative: here it is initialised to -1, i.e. q=1
 5 :             MOV R61, R35 ; other summand=-2
 6 :             MOV R60, R61 ; next trial divisor q=q+2
 7 :             MOV R61, R32 ; move p to adder summand input a, which holds remainder
 8 :             MOV R57, R36 ; for the first time round the loop, set the target for the branch if subtraction gives zero to 20: this detects the case p==q, which means we have done all the trial divisors and p is prime
 9 :             MOV R55, R37 ; if subtraction result non-zero, target is 13
10 :             MOV R56, R61 ; test a-q
11 :             MOV R63, R56 ; branch to selected target
12 :             MOV R61, R61 ; a-=q
13 :             MOV R61, R61 ; a-=q (continuing here if subtraction result not zero)
14 :             MOV R53, R61 ; move a-q to and-not register to check sign
15 :             MOV R57, R38 ; target is 9 if a-q positive (round subtraction loop again)
16 :             MOV R55, R39 ; else target is 5 (q does not divide p, so try next q)
17 :             MOV R56, R54 ; test a-q AND 0x8000
18 :             MOV R63, R56 ; branch to selected target
19 :             MOV R57, R40 ; reset target for other branch to 21 (a zero result from the subtraction now indicates q properly divides p and so p is composite)
20 :             MOV R0 , R32 ; p is prime: write it to the display
21 :             MOV R61, R32 ; move p to adder
22 :             MOV R60, R30 ; other summand=2
23 :             MOV R63, R41 ; goto 4 to try new p
24 :             MOV R32, R61 ; p+=2
25 :             0x0000
26 :             0x0000
27 :             0x0000
28 :             0x0000
29 :             0x0000
30 :             0x0002       ; constant 2
31 :             0x7fff       ; constant mask for sign bit testing
32 : <p>       : 0x0005       ; current candidate p
33 :             0x0003       ; constant 3
34 :             0xfffe       ; constant -1
35 :             0xfffd       ; constant -2
36 : <Label_36>: 0x0014       ; branch target: trial divisor q equal to candidate p, and hence prime found
37 : <Label_37>: 0x000d       ; branch target: trial divisor q less than candidate p
38 : <Label_38>: 0x0009       ; branch target: more subtractions to do
39 : <Label_39>: 0x0005       ; branch target: next trial divisor q
40 : <Label_40>: 0x0015       ; branch target: subtraction gave zero, so p composite
41 : <Label_41>: 0x0004       ; branch target: next candidate p
42 :             0xfffc       ; constant -3
43 :             0x0000
44 :             0x0000
45 :             0x0000
46 :             0x0000
47 :             0x0000
48 :             0x0000
49 :             0x0000
50 :             0x0000
51 :             0x0000
52 :             0x0000
53 :             UNUSED
54 :             UNUSED
55 :             UNUSED
56 :             UNUSED
57 :             UNUSED
58 :             UNUSED
59 :             UNUSED
60 :             0x0000
61 :             UNUSED
62 :             UNUSED
63 : <PC>      : 0x0001       ; Starting PC
