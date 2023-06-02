\ does maths, keeps output on the stack

: ans ( --)
\ displays the last value on the stack
 cr ." Answer: "
 dup .
 cr
 ;

: add ( n n -- n+n n)
 + ans ;

: sub ( n n -- n-n n)
 - ans ;

: mul ( n n -- n*n n)
 * ans ;

: div ( n n -- n/n n)
 / ans ;

: sqr ( n -- n^2 n)
 dup * ans ;

: abs ( n -- +n)
 dup 0 < if
  negate
 then 
 ans ;

: tohex ( n -- n)
 hex u. decimal
 ;

