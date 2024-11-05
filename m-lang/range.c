#include <stddef.h>

typedef struct RANGE {
    size_t start;
    size_t stop;
    size_t step;
} RANGE;

RANGE range(size_t start, size_t stop, size_t step) {
    return (RANGE){.start=start, .stop=stop, .step=step};
}
