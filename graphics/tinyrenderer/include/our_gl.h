#ifndef _OUR_GL_H
#define _OUR_GL_H

#include "tgaimage.h"
#include "geometry.h"

extern Matrix ModelView;
extern Matrix Projection;
extern Matrix Viewport;

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;
const int SCR_DEPTH = 255;

void viewport(int screen_cube_x, int screen_cube_y, int screen_width, int screen_height);
void projection(float coeff = 0.0f);
void lookAt(Vec3f eye, Vec3f center, Vec3f up);

struct IShader {
    virtual ~IShader();
    virtual Vec4f vertex(int iface, int nthvert) = 0;
    virtual bool fragment(Vec3f bar, TGAColor &color) = 0;
};

void triangle(mat<4, 3, float> &clipped_coords, IShader& shader, TGAImage& image, TGAImage& zbuffer);

#endif