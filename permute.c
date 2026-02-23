#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define UPPER 100
#define ull unsigned long long
static int rsp = 0;
static inline ull fact(int n) {
    ull d = 1ULL;
    for (int i = 1; i <= n; i++) d *= (ull)i;
    return d;
}
static void generate(int * restrict origin, int * restrict cur, int d, int n, int * restrict perms, unsigned char * restrict track) {
    if (d == n) {
        memcpy(&perms[rsp], cur, sizeof(int) * d); 
        rsp += d; 
        return;
    }
    for (int i = 0; i < n; i++) {
        if (track[i]) {
            track[i] ^= 1; 
            cur[d] = origin[i];
            generate(origin, cur, d + 1, n, perms, track); 
            track[i] ^= 1; 
        }
    }
}
static inline void gprint(int *perms, int n, ull sz) {
    ull i = 0ULL;
    while (i < sz) {
        int st = i + n;
        for (; i < st; i++) printf("%d ", perms[i]);
        putchar('\n');
    }
}
int main(void) {
    srand(time(NULL)); 
    int t;
    printf("Number of tries: ");
    scanf("%d", &t);
    putchar('\n');
    while (t--) {
        int n;
        printf("Enter array size: ");
        scanf("%d", &n);
        putchar('\n');
        int arr[n];
        for (int i = 0; i < n; i++) arr[i] = rand() % UPPER;
        ull sz = fact(n); 
        int *perms = malloc(sizeof(int) * sz * n);
        unsigned char track[n];
        memset(track, 1, sizeof(track));
        int temp[n];
        generate(arr, temp, 0, n, perms, track);
        puts("Original array being printed:");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        putchar('\n');
        puts("Permutations of the array are:");
        gprint(perms, n, sz * n); 
        free(perms);
        rsp = 0; 
        putchar('\n');
    }
    return 0;
}
