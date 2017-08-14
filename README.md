# fast itoa

## C++17

## Notice

对于负数来说，是不太合适将他们转换为二进制、八进制和十六进制的，但是因为某些工程实用性的原因，`fast_itoa`通过取绝对值转换并添加负号来实现转换。  

For negative numbers, it is illegal to convert them to binary, octal or hexadecimal form.  
But for some practical reasons, `fast_itoa` can deal with them by adding `-` to the converted result of their absolute value.

## Benchmark

Environment: Intel(R) Core(TM) i7-4710MQ CPU @ 2.50GHz / Win64 / GCC_7.1.0@MinGW-w64

```
Count: 100000000
================
itoa2: 506 ms
(C)itoa: 20385 ms
================
================
itoa8: 608 ms
snprintf: 6088 ms
(C)itoa: 5515 ms
================
================
itoa10: 540 ms
snprintf: 5623 ms
(C)itoa: 4803 ms
================
================
itoa16: 271 ms
snprintf: 5402 ms
(C)itoa: 3878 ms
================
```