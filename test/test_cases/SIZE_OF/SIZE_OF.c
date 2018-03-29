int f(int x, short y, char z) {
    return sizeof(char) + sizeof(short) + sizeof(int) + sizeof x + sizeof y + sizeof z;
}