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
;1 : <Next_Candidate>    : MOV R60, $CNST_Minus_One     ; Set Divider
 1 : <Next_Candidate>    : MOV R60, R44                 ; Set Divider
;2 : <Next_Divider>      : MOV R61, $CNST_Minus_Two     ; Set Divider increment
 2 : <Next_Divider>      : MOV R61, R45                 ; Set Divider increment
 3 :                       MOV R60, R61                 ; Increment divider
;4 :                       MOV R61 ,$Square_Root        ; Set Square root as first operand of adder
 4 :                       MOV R61 ,R41                 ; Set Square root as first operand of adder
 5 :                       MOV R53, R61                 ; Prepare to Apply bit mask to addition result
;6 :                       MOV R55, $LBL_Prime          ; Prepare branch to prime as divider is grater than root square of candidate
 6 :                       MOV R55, R50                 ; Prepare branch to prime as divider is grater than root square of candidate
;7 :                       MOV R57, $LBL_Loop_div       ; Prepare branch to division loop as we have a valid divider
 7 :                       MOV R57, R48                 ; Prepare branch to division loop as we have a valid divider
 8 :                       MOV R56, R54                 ; Test result of addition
 9 :                       MOV R63, R56                 ; Jump depending on addition result
;10 :                       MOV R61, $Candidate          ; Set candidate as second operand of adder, divider should be the first operand
10 :                       MOV R61, R43                 ; Set candidate as second operand of adder, divider should be the first operand
;11 : <Loop_Div>          : MOV R57, $LBL_Common         ; Prepare branch to common in case division reminder is null
11 : <Loop_Div>          : MOV R57, R51                 ; Prepare branch to common in case division reminder is null
;12 :                       MOV R55, $LBL_Div_not_null   ; Prepare branch to sign test in case division reminder is not null
12 :                       MOV R55, R49                 ; Prepare branch to sign test in case division reminder is not null
13 :                       MOV R56, R61                 ; Test substraction result
14 :                       MOV R63, R56                 ; Branch on null result of substraction
;15 :                       MOV R57, $LBL_Loop_div       ; if result negative then need to test a new divider
15 :                       MOV R57, R48                 ; if result negative then need to test a new divider
;16 : <Div_not_null>      : MOV R55, $LBL_Next_Divider   ; if result positive then need to continue the loop
16 : <Div_not_null>      : MOV R55, R46                 ; if result positive then need to continue the loop
17 :                       MOV R53, R61                 ; Prepare to check if division result is negative
18 :                       MOV R56, R54                 ; Perform the check of negative result
19 :                       MOV R63, R56                 ; branch depending if result is negative or not
20 :                       MOV R61, R61                 ; Store division result in case division continue
;21 : <Prime>             : MOV R0 , $Candidate          ; Display Prime
21 : <Prime>             : MOV R0 , R43                 ; Display Prime
;22 : <Common>            : MOV R60, $Candidate          ; Prepare to add 2 to p by Candidate as first operand of adder
22 : <Common>            : MOV R60, R43                 ; Prepare to add 2 to p by Candidate as first operand of adder
;23 :                       MOV R61, $CNST_Two           ; Prepare to add 2 to p by Candidate as second operand of adder
23 :                       MOV R61, R46                 ; Prepare to add 2 to p by Candidate as second operand of adder
24 :                       MOV R62, R61                  ; Prepare computation of minus of new Candidate value
;25 :                       MOV $Candidate, R61          ; Store new candidate value
25 :                       MOV R43, R61                ; Store new candidate value
26 :                       MOV R60, R62                 ; Set new minus Candidate as add first operand
;27 :                       MOV R61, $Square             ; Set square as second operand
27 :                       MOV R61, R42                 ; Set square as second operand
;28 :                       MOV R55, $LBL_Up_Square      ; Prepare branch to next candidate in case 0 > Square - P
28 :                       MOV R55, R52                 ; Prepare branch to next candidate in case 0 > Square - P
;29 :                       MOV R57, $LBL_Next_Candidate ; Prepare branch to upgrade to next square in case 
29 :                       MOV R57, R47                 ; Prepare branch to upgrade to next square in case 
30 :                       MOV R53, R61                 ; Prepare to Apply bit mask to addition result
31 :                       MOV R56, R54                 ; Check addition result sign
32 :                       MOV R63, R56                 ; Branch on result
;33 :                       MOV R59, $Square_Root        ; Prepare multiplication of square by too
33 :                       MOV R59, R41                 ; Prepare multiplication of square by too
34 :<Up_Square>          : MOV R60, R59                 ; Prepare addition of 2 * r + C
35 :                       MOV R60, R61                 ; Perform addition of 2 * r + C
;36 :                       MOV R61, $CNST_One           ; Prepare to add 1 to 2 * r + C
36 :                       MOV R61, R47                 ; Prepare to add 1 to 2 * r + C
;37 :                       MOV $Square, R61             ; Compute new value of C
37 :                       MOV R42, R61                 ; Compute new value of C
;38 :                       MOV R60, $Square_Root        ; Prepare computation of new square root value
38 :                       MOV R60, R41                 ; Prepare computation of new square root value
;39 :                       MOV R63, $LBL_Next_Candidate ; Preparebranch to new candidate
39 :                       MOV R63, R47                 ; Preparebranch to new candidate
;40 :                       MOV $Square_Root, R61        ; Compute new square root
40 :                       MOV R41, R61                 ; Compute new square root
41 : <Square_Root>       : 0x0001       ; Current square root
42 : <Square>            : 0x0001       ; Current square
43 : <Candidate>         : 0x0003       ; Init value of candidate prime number
44 : <CNST_Minus_One>    : 0xfffe       ; Constant -1
45 : <CNST_Minus_Two>    : 0xfffd       ; Constant -2
46 : <CNST_Two>          : 0x0002       ; Constant 2
47 : <CNST_One>          : 0x0001       ; Constant 1
;48 : <LBL_Next_Candidate>: 0x0000       ; Define the start of code managing a new prime candidate
;49 : <LBL_Next_Divider>  : 0x0000       ; Define the start of code managing a new divisor
48 : <LBL_Loop_div>      : 0x000B       ; Define the start of loop code performing division
49 : <LBL_Div_not_null>  : 0x0010       ; Define the start of code executed if division reminder is not null
50 : <LBL_Prime>         : 0x0015       ; Define the start of code executed if p is prime
51 : <LBL_Common>        : 0x0016       ; Define the start of code executed if p is prime or not
52 : <LBL_Up_Square>     : 0x0022       ; Define the start of code managing the increment of square
53 :                       UNUSED
54 :                       0x7fff       ; Constant used in AND NOT to check if number is negative or not 
55 :                       UNUSED
56 :                       UNUSED
57 :                       UNUSED
58 :                       UNUSED
59 :                       UNUSED
60 :                       0x0000
61 :                       MOV R63, R47
62 :                       0xFFD1
;63 : <PC>                : 0x003D       ; Starting PC
63 : <PC>                : 0x003D       ; Starting PC
