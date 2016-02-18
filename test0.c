#include <stdio.h>
#include <stdlib.h>
#include "schema.h"
#include "data.h"
#include "init.h"
#include "onedim.h"

#define xmax 100

data1d *d;


int main() {
init_data(d, xmax, &rectangle);
//save_data("hello.txt", d);
return 0;
}
