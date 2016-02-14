#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "GL/glew.h"

#include "prerequisites.h"

#include "stb_image.h"

class Texture
{
public:

	Texture();
	Texture(const std::string& filename);
	~Texture();

	void load(const std::string& filename);
	bool hasImage() const;

	void init();
	void update();

	void resize(uint w, uint h);

	void setFilters(uint min, uint mag);

	int getWidth() const;
	int getHeight() const;
	
	GLuint mGLuid;

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