volatile unsigned const char f(const unsigned volatile char lol) {
    const volatile int * c;
    const volatile char x = 10;
    return x + lol;
}