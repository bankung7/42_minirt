#include "minirt.h"

void ft_mlx_put_pixel(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->len + x * (data->bpp / 8));
    *(unsigned int *)dst = color;
}

int ft_makeColor(t_color c)
{
    return (c.r << 16 | c.g << 8 | c.b);
}

// o = Sphere center, rd = Radius, r = Ray
double ft_hitSphere(t_sphere sp, t_ray r)
{
    t_vec oc = ft_vecMinus(r.o, sp.crdt);
    double a = pow(ft_vecLen(r.dir), 2);
    double hb = ft_vecDot(oc, r.dir);
    double c = pow(ft_vecLen(oc), 2) - ((sp.dmt / 2.0) * (sp.dmt / 2.0));
    double dis = (hb * hb) - (a * c);
    if (dis < 0.0 || a == 0)
        return (INFINITY);
    return ((- hb - sqrt(dis)) / a);
}

double ft_hitPlane(t_plane pl, t_ray r)
{
    t_vec oc = ft_vecMinus(pl.crdt, r.o);
    if (ft_vecDot(r.dir, pl.rot) == 0.0)
        return (INFINITY);
    double t = ft_vecDot(oc, pl.rot) / ft_vecDot(r.dir, pl.rot);
    return (t);
}

double ft_hitDisc(t_plane pl, t_ray r, double rd)
{
    t_vec oc = ft_vecMinus(pl.crdt, r.o);
    if (ft_vecDot(r.dir, pl.rot) == 0.0)
        return (INFINITY);
    double t = ft_vecDot(oc, pl.rot) / ft_vecDot(r.dir, pl.rot);
    t_vec p = ft_vecPlus(r.o, ft_vecMul(r.dir, t));
    if (ft_vecLen(ft_vecMinus(p, pl.crdt)) <= rd)
        return (t);
    return (INFINITY);

    // if (tpl1 != INFINITY)
    // {
    //     p = ft_vecPlus(r.o, ft_vecMul(r.dir, tpl1));
    //     double 
    //     if (ft_vecLen(ft_vecMinus(cy.pl1.crdt, p)) <= cy.dmt / 2)
         
    //     else

    // }
    // if (tpl2 != INFINITY)
    // {
    //     p = ft_vecPlus(r.o, ft_vecMul(r.dir, tpl2));
    //     if (ft_vecLen(ft_vecMinus(cy.pl2.crdt, p)) <= cy.dmt / 2)
    //         double 
    // }
}

double ft_hitCynd(t_cynd cy, t_ray r)
{
	t_vec x = ft_vecMinus(r.o, cy.crdt);
	double dv = ft_vecDot(r.dir, cy.rot);
	double xv = ft_vecDot(x, cy.rot);
	double a = pow(ft_vecLen(r.dir), 2) - pow(dv, 2);
    double hb = ft_vecDot(x, r.dir) - (dv * xv);
    double c = pow(ft_vecLen(x), 2) - ((cy.dmt * cy.dmt) / 4.0) - pow(xv, 2);
    double dis = (hb * hb) - (a * c);
    if (dis < 0.0 || a == 0)
        return (INFINITY);
    double t = (- hb - sqrt(dis)) / a;
    t_vec p = ft_vecPlus(r.o, ft_vecMul(r.dir, t));
    t_vec diff = ft_vecMinus(cy.crdt, p);
    if (fabs(ft_vecDot(diff, cy.rot)) <= (cy.hgt / 2))
        return (t);
    cy.pl1.crdt = ft_vecPlus(cy.crdt, ft_vecMul(cy.rot, (cy.hgt / 2)));
    cy.pl2.crdt = ft_vecMinus(cy.crdt, ft_vecMul(cy.rot, (cy.hgt / 2)));
    cy.pl1.rot = cy.rot;
    cy.pl2.rot = cy.rot;
    double tpl1 = ft_hitDisc(cy.pl1, r, cy.dmt / 2);
    double tpl2 = ft_hitDisc(cy.pl2, r, cy.dmt / 2);
    if (tpl1 < tpl2)
        return (tpl1);
    return (tpl2);
}


int ft_rayColor(t_ray r)
{
    // double t = ft_hitSphere((t_sphere){(t_vec){0,0,-1}, 1.0, (t_color){255,0,0}, NULL}, r);
    double mint = INFINITY;
    double t = INFINITY;
    t_color cl;
    t_sphere sp1, sp2;
    sp1.crdt = (t_vec){0,0,-1};
    sp1.dmt = 0.5;
    sp1.color = (t_color){255,0,0};
    sp1.next = &sp2;
    sp2.crdt = (t_vec){0.5,0,-1.5};
    sp2.dmt = 0.7;
    sp2.color = (t_color){0,255,0};
    sp2.next = NULL;

    t_plane pl1, pl2;
    pl1.crdt = (t_vec){0,0,-2.0};
    pl1.rot = (t_vec){0,0,1.0};
    pl1.color = (t_color){100,10,100};
    pl1.next = &pl2;
    pl2.crdt = (t_vec){0,0,-2.0};
    pl2.rot = (t_vec){0,sin(3.14/4),cos(3.14/4)};
    pl2.color = (t_color){10,100,100};
    pl2.next = NULL;

	t_cynd cy;
	cy.crdt = (t_vec){-1.0,0,-1.5};
	cy.rot = ft_vecNrml((t_vec){1,0,1});
	cy.dmt = 0.5;
	cy.hgt = 1.0;
	cy.color = (t_color){229,193,253};
	cy.next = NULL;
    cy.pl1.color = (t_color){90,188,230};
    cy.pl2.color = (t_color){90,188,230};

	t_cynd *ptrcy;
	ptrcy = &cy;
	while (ptrcy)
	{
		t = ft_hitCynd(*ptrcy, r);
		if (t < mint)
		{
			mint = t;
			cl = ptrcy->color;
		}
		ptrcy = ptrcy->next;
	}
	t_plane *ptrp;
    ptrp = &pl1;
    while (ptrp)
    {
        t = ft_hitPlane(*ptrp, r);
        if (t < mint)
        {
            mint = t;
            cl = ptrp->color;
        }
        ptrp = ptrp->next;
    }
    t_sphere *ptr;
    ptr = &sp1;
    while (ptr)
    {
        t = ft_hitSphere(*ptr, r);
        if (t < mint)
        {
            mint = t;
            cl = ptr->color;
        }
        ptr = ptr->next;
    }
    // printf("sp.dmt = %f\n", t);
    if (mint == INFINITY)
        return (ft_makeColor((t_color){0,0,255}));
    if (mint > 0.0)
    {
        // printf("[%f]\n", t);
        // t_vec pAt = ft_vecPlus(r.o, ft_vecMul(r.dir, t));
        // t_vec uni = ft_vecNrml(ft_vecMinus(pAt, (t_vec){0, 0, -1}));
        // t_vec c = ft_vecMul((t_vec){uni.x + 1, uni.y + 1, uni.z + 1}, 0.5);
        // c = ft_vecMul(c, 255);
        // return ((int)c.x << 16 | (int)c.y << 8 | (int)c.z);
        return (ft_makeColor(cl));
    }
    // t_vec uni = ft_vecNrml(r.dir);
    // t = 0.5 * (uni.y + 1.0);
    // t_vec c = ft_vecMul((t_vec){1, 1, 1}, (1.0 - t));
    // c = ft_vecPlus(c, ft_vecMul((t_vec){0.5, 0.7, 1.0}, t));
    // c = ft_vecMul(c, 255);
    // return ((int)c.x << 16 | (int)c.y << 8 | (int)c.z);
    return (ft_makeColor((t_color){0,0,0}));
}

// ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
t_ray ft_createRay(t_cam cam, double u, double v)
{
    t_ray r;
    r.o = cam.crdt;
    // fixed ray direction
    // r.dir.x = cam.llc.x + u * cam.hoz.x + v * cam.vet.x;
    // r.dir.y = cam.llc.y + u * cam.hoz.y + v * cam.vet.y;
    // r.dir.z = cam.llc.z + u * cam.hoz.z + v * cam.vet.z;
    r.dir.x = cam.llc.x + u * cam.hoz.x + v * cam.vet.x - cam.crdt.x;
    r.dir.y = cam.llc.y + u * cam.hoz.y + v * cam.vet.y - cam.crdt.y;
    r.dir.z = cam.llc.z + u * cam.hoz.z + v * cam.vet.z - cam.crdt.z;
    // ft_info(r.dir);
    return (r);
}

// u = l + (r - l)(i + 0.5)/Nx
// v = b + (t - b)(j + 0.5)/Ny

// Ray direction → -d*(w-axis) + u*(u-axis) + v*(v-axis)
