/**
 * catch_setup.h and catch_setup.cpp contain the #define directive for
 * the CATCH2 framework.
 *
 * On average, this should reduce the build time for project on local
 * machine.
 */
#include "catch_setup.h"
#include "AutoIndexer.h"

int main(int argc, char** argv) {

    if(argc == 1) {
        runCatchTests();
    }
    else {
        AutoIndexer a;
        a.readIn(argv[1]);
        a.print(argv[2]);
    }
    return 0;
}
