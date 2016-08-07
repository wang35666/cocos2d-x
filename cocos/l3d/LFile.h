#ifndef __LFILE_H__
#define __LFILE_H__

#include <string>

#include "math/Vec3.h"
#include "math/Quaternion.h"

NS_CC_BEGIN

// mode parm for Seek
typedef enum {
	FS_SEEK_SET,
	FS_SEEK_CUR,
	FS_SEEK_END,
} fsOrigin_t;

class CC_DLL LBuffer
{
public:
	 std::string ReadString();
	 int ReadInt();
	 float ReadFloat();
	 int ReadChar();
	 Vec3 ReadVec3();
	 Quaternion ReadQuat();

	 unsigned int ReadUnsignedInt();
	 unsigned short ReadUnsignedShort();
	 unsigned char ReadUnsignedChar();

	 virtual int Length();
	 virtual int Read( void *buffer, int len );
	 virtual int Seek( long offset, fsOrigin_t origin );
};

class LFile : public LBuffer
{
public:
	LFile()  {}
	~LFile();

	bool Open( const char* filepath, const char* mode = "rb");

	int Tell();
public:
	virtual int Read( void *buffer, int len );
	virtual int Length();
	virtual int Seek( long offset, fsOrigin_t origin );
	virtual int Skip( int len );

	void WriteString(const char* fmt, ...);
	//lfFile& operator>>(unsigned char& value)
	//{
	//	value = ReadUnsignedChar();
	//	return *this;
	//}

private:
	FILE* fp;
	int current;
	int fileSize;
};


NS_CC_END

#endif

