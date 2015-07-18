#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "GL/glew.h"

#include "prerequisites.h"

#include "stb_image.h"

class Texture
{
public:

	Texture();
	Texture(std::string filename, uint index = 0);
	~Texture();

	void load(std::string filename);

	void init();
	void bind();
	void update();

	void resize(uint w, uint h);

	void setFilters(uint min, uint mag);

	int getWidth() const;
	int getHeight() const;

	static GLuint unitFromIndex(uint index);
	
	GLuint mGLuid;
	GLuint mGLunit;
	GLuint mIndex;

private:

	unsigned char* mData;
	bool mHasImage;

	int mWidth;
	int mHeight;

	uint mMinFilter;
	uint mMagFilter;

	uint mFormat;
	uint mGlobalFormat;

};

#endif