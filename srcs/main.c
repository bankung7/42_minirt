#include "minirt.h"

int main(int argc, char **argv)
{
    t_mrt mrt;

    if (argc == 1)
        return (elog("Usage: ./minirt [file]", 1));

    // set to null
    mrt.qcode = 0;
    mrt.ambt = 0;
    mrt.cam = 0;
    mrt.lght = 0;
    mrt.obj = 0;

    // parsing phase
    if (parsing(&mrt, argv[1]))
        return (1);

    setup(&mrt);
    camera(&mrt);
    render(&mrt);

    return (0);
}

// to do //
// check input value in each item => done
// check multiple item add if have to be single
// multiple light idea
// keycode
// cylinder

// bug //
// shadow have something wrong => fixed maybe
// rotation, it should be with up first, then rotatage
