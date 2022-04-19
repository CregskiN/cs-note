#ifndef _OUR_GL_H
#define _OUR_GL_H

#include "tgaimage.h"
#include "geometry.h"

extern Matrix ModelView;
extern Matrix Projection;
extern Matrix Viewport;

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;
const float SCR_DEPTH = 2000.0f;  // 考虑做深度测试时的精度需求，必须大一点

void viewport(int screen_cube_x, int screen_cube_y, int screen_width, int screen_height);
void projection(float coeff = 0.0f);
void lookAt(Vec3f eye, Vec3f center, Vec3f up);

struct IShader {
    virtual ~IShader();
    virtual Vec4f vertexShader(int iface, int nthvert) = 0;
    virtual bool fragmentShader(Vec3f bar, TGAColor &color) = 0;
};

void triangle(Vec4f screen_coords[3], IShader &shader, TGAImage &image, float *z_buffer);

#endif