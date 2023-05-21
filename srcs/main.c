#include "minirt.h"

int main(int argc, char **argv)
{
    t_mrt mrt;

    mrt.qcode = 0;
    
    if (argc == 1)
        return (elog("Usage: ./minirt [file]", 1));

    // parsing phase
    if (parsing(&mrt, argv[1]))
        return (1);

    setup(&mrt);

    // set to null
    mrt.ambt = 0;
    mrt.cam = 0;
    mrt.lght = 0;
    mrt.obj = 0;

    camera(&mrt);

    // set ambient
    mrt.ambt = malloc(sizeof(t_ambient));
    mrt.ambt->color = vec3(1, 1, 1);
    mrt.ambt->ratio = 0.2;

    // set object
    {
        // set circle
        t_object *obj0 = malloc(sizeof(t_object));
        obj0->type = 0;
        obj0->orig = vec3(-1, 5, -12);
        obj0->raduis = 3;
        obj0->color = vec3(1, 0 ,1);
        obj0->next = 0;
        addObject(&mrt, obj0);

        t_object *obj1 = malloc(sizeof(t_object));
        obj1->type = 0;
        obj1->orig = vec3(-6, 1, -25);
        obj1->raduis = 5;
        obj1->color = vec3(1, 0 ,0);
        obj1->next = 0;
        addObject(&mrt, obj1);

        t_object *obj2 = malloc(sizeof(t_object));
        obj2->type = 0;
        obj2->orig = vec3(6, -4, -18);
        obj2->raduis = 5;
        obj2->color = vec3(0, 1 ,0);
        obj2->next = 0;
        addObject(&mrt, obj2);

        // set plane
        t_object *obj3 = malloc(sizeof(t_object));
        obj3->type = 1;
        obj3->orig = vec3(0, 0, -40);
        obj3->rot = vec3(0, 0, 1);
        obj3->color = vec3(0, 0 ,1);
        obj3->next = 0;
        addObject(&mrt, obj3);

        t_object *obj4 = malloc(sizeof(t_object));
        obj4->type = 1;
        obj4->orig = vec3(30, 0, -40);
        obj4->rot = vec3(-1, 0, 0);
        obj4->color = vec3(0, 1 ,1);
        obj4->next = 0;
        addObject(&mrt, obj4);

        t_object *obj5 = malloc(sizeof(t_object));
        obj5->type = 1;
        obj5->orig = vec3(-30, 0, -40);
        obj5->rot = vec3(1, 0, 0);
        obj5->color = vec3(0, 1 ,1);
        obj5->next = 0;
        addObject(&mrt, obj5);

        t_object *obj6 = malloc(sizeof(t_object));
        obj6->type = 1;
        obj6->orig = vec3(0, 30, -40);
        obj6->rot = vec3(0, -1, 0);
        obj6->color = vec3(1, 1 ,0);
        obj6->next = 0;
        addObject(&mrt, obj6);

        t_object *obj7 = malloc(sizeof(t_object));
        obj7->type = 1;
        obj7->orig = vec3(0, -30, -40);
        obj7->rot = vec3(0, 1, 0);
        obj7->color = vec3(1, 1 ,0);
        obj7->next = 0;
        addObject(&mrt, obj7);
    }

    // set light
    t_light *lght = malloc(sizeof(t_light));
    lght->orig = vec3(-10, 15, 0);
    lght->ratio = 0.5;
    lght->color = vec3(1, 1, 1);
    lght->next = 0;
    addLight(&mrt, lght);

    render(&mrt);

    return (0);
}