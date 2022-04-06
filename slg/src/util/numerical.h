// utility for integer manipulation

#pragma once

// returns the number of digits (including '-' sign) of a signed integer
int digit_count(long long value);

// converts signed integer to string
// bases [2, 16] are supported
// assumes buffer is sized sufficiently
void iota(long long value, char* buffer, int base);
