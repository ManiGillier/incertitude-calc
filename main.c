#include <stdio.h>
#include <stdint.h>

struct number {
    double low;
    double high;
};


struct number get_strict_number(double real)
{
    struct number n = {
        .low = real,
        .high = real
    };
    return n;
}
struct number get_number(double real, uint8_t sig)
{
    sig--;
    uint8_t sign = real < 0.0 ? -1.0 : 1.0;
    int right_shift = 0;
    int left_shift = 0;

    real *= sign;
    printf("Positive : %f\n", real);
    while (real >= 1.0) {
        real /= 10.0;
        right_shift++;
        printf("Right shift #%d : %f\n", right_shift, real);
    }
    while (real <= 1.0) {
        real *= 10.0;
        left_shift++;
        printf("Left shift #%d : %f\n", left_shift, real);
    }
    for (uint8_t i = 0; i < sig; i++) {
        real *= 10.0;
        printf("Sig %d/%d : %f\n", i + 1, sig, real);
    }
    real = (int) real * sign;
    printf("Rounded %f\n", real);
    double real_low = real - 1;
    double real_high = real + 1;
    int shift = sig + left_shift - right_shift;
    for (; shift > 0; shift--) {
        real_low /= 10.0;
        real_high /= 10.0;
    }
    for (; shift < 0; shift++) {
        real_low *= 10.0;
        real_high *= 10.0;
    }
    struct number new_number = {
        .low = real_low,
        .high = real_high
    };
    return new_number;
}

double min(double a, double b, double c, double d)
{
    if (a < b)
        b = a;
    if (b < c)
        c = b;
    if (c < d)
        d = c;
    return d;
}
double max(double a, double b, double c, double d)
{
    if (a > b)
        b = a;
    if (b > c)
        c = b;
    if (c > d)
        d = c;
    return d;
}

struct number add(struct number n1, struct number n2)
{
    double nll = n1.low + n2.low;
    double nlh = n1.low + n2.high;
    double nhl = n1.high + n2.low;
    double nhh = n1.high + n2.high;
    
    struct number n = {
        .low = min(nll, nlh, nhl, nhh),
        .high = max(nll, nlh, nhl, nhh),
    };
    return n;
}
struct number mult(struct number n1, struct number n2)
{
    double nll = n1.low * n2.low;
    double nlh = n1.low * n2.high;
    double nhl = n1.high * n2.low;
    double nhh = n1.high * n2.high;
    
    struct number n = {
        .low = min(nll, nlh, nhl, nhh),
        .high = max(nll, nlh, nhl, nhh),
    };
    return n;
}
struct number div(struct number n1, struct number n2)
{
    double nll = n1.low / n2.low;
    double nlh = n1.low / n2.high;
    double nhl = n1.high / n2.low;
    double nhh = n1.high / n2.high;
    
    struct number n = {
        .low = min(nll, nlh, nhl, nhh),
        .high = max(nll, nlh, nhl, nhh),
    };
    return n;
}

void print_number(struct number n)
{
    double d = (n.high - n.low) / 2.0;
    double m = n.low + d;
    printf("[%g ± %g]\n", m, d);
}

int main()
{
    struct number m = get_number(6.17, 3);
    struct number M = get_number(248.2, 4);
    struct number V = get_number(0.1500, 4);

    print_number(m);
    print_number(M);
    print_number(V);
    print_number(div(m, mult(M, V)));
    return 0;
}
