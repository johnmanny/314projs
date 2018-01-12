#include <stdio.h>

void printBytes(unsigned char *start, int len) {
 for (int i = 0; i < len; ++i) {
 printf(" %.2x", start[i]);
 }
 printf("\n");
}

void printInt(int x) {
 printBytes((unsigned char *) &x, sizeof(int));
}

void printFloat(float x) {
 printBytes((unsigned char *) &x, sizeof(float));
}

printShort() {

}

printLong() {

}

printDouble() {

}


int main () {


return 0;
}
