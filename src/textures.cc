#include<textures.hh>
#include<GL/glut.h>
#include<cmath>

const int ptex_size = 128;
const int bgtex_size = 4096;

GLuint player_texture, background_texture;

static GLubyte player_tex[ptex_size][ptex_size][4];
static GLubyte background_tex[bgtex_size][bgtex_size][4];

void make_player_texture() {
	double rad2 = (ptex_size/2.0)*(ptex_size/2.0);
	for(int i = 0; i < ptex_size; i++) {
		for(int j = 0; j < ptex_size; j++) {
			double d2 = (i-ptex_size/2.0)*(i-ptex_size/2.0) + (j-ptex_size/2.0)*(j-ptex_size/2.0);
			player_tex[i][j][0] = (GLubyte) 255;
			player_tex[i][j][1] = (GLubyte) 0;
			player_tex[i][j][2] = (GLubyte) 255;
			if(d2 > rad2) {
				player_tex[i][j][3] = 0;
			} else {
				player_tex[i][j][3] = (GLubyte)(255*(1-sqrt(d2/rad2)));
			}
		}
	}
}

void make_background_texture() {
	for(int i = 0; i<bgtex_size; i++) {
		for(int j = 0; j<bgtex_size; j++) {
			background_tex[i][j][0] = (GLubyte) 0;
			background_tex[i][j][1] = (GLubyte) 0;
			background_tex[i][j][2] = (GLubyte) 0;
			background_tex[i][j][3] = (GLubyte) 255;
		}
	}
}

void init_textures() {
	make_player_texture();
	make_background_texture();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1,&player_texture);
	glBindTexture(GL_TEXTURE_2D,player_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ptex_size, ptex_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, player_tex);

	glGenTextures(1,&background_texture);
	glBindTexture(GL_TEXTURE_2D,background_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bgtex_size, bgtex_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, background_tex);
}

void use_player_texture() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, player_texture);
}

void use_background_texture() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, background_texture);
}

void end_texture() {
	glDisable(GL_TEXTURE_2D);
}
