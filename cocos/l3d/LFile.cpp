#include "LFile.h"

NS_CC_BEGIN

int LBuffer::ReadInt()
{
	int value;
	Read(&value, sizeof(int));
	return value;
}

float LBuffer::ReadFloat()
{
	float value;
	Read(&value, sizeof(float));
	return value;
}

int LBuffer::ReadChar()
{
	int value;
	Read(&value, sizeof(char));
	return value;
}

unsigned int LBuffer::ReadUnsignedInt()
{
	unsigned int value;
	Read(&value, sizeof(unsigned int));
	return value;
}

std::string LBuffer::ReadString()
{
	std::string str;
	char c = ReadChar();

	while (c)
	{
		str += c;
		if (c=='/0')
			break;
		c = ReadChar();
	}
	return str;
}

int LBuffer::Read( void *buffer, int len )
{
	return 0;
}

int LBuffer::Length()
{
	return 0;
}

Vec3 LBuffer::ReadVec3()
{
	Vec3 value;
	Read(&value, sizeof(Vec3));
	return value;
}

Quaternion LBuffer::ReadQuat()
{
	float w = ReadFloat();
	float x = ReadFloat();
	float y = ReadFloat();
	float z = ReadFloat();
	return Quaternion(x, y, z, w);
}

unsigned short LBuffer::ReadUnsignedShort()
{
	unsigned short value;
	Read(&value, sizeof(unsigned short));
	return value;
}

unsigned char LBuffer::ReadUnsignedChar()
{
	unsigned char value;
	Read(&value, sizeof(unsigned char));
	return value;
}

int LBuffer::Seek( long offset, fsOrigin_t origin )
{
	return 0;
}

bool LFile::Open( const char* filepath, const char* mode )
{
	fp = fopen(filepath, mode);
	if (fp == nullptr)
	{
		CCLOG("open file failed", filepath);
		return false;
	}

	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	current = 0;
	return true;
}

int LFile::Read( void *buffer, int len )
{
	current += len;
	fread(buffer, len, 1, fp);
	return len;
}

int LFile::Length()
{
	return fileSize;
}

LFile::~LFile()
{
	if (fp != nullptr)
		fclose(fp);
}

int LFile::Tell()
{
	return ftell(fp);
}

int LFile::Seek( long offset, fsOrigin_t origin )
{
	fseek(fp, offset, origin);
	return 0;
}

int LFile::Skip( int len )
{
	Seek(len, FS_SEEK_CUR);
	return 0;
}

char* F_ReadFileData( const char* filename )
{
	FILE* fp;
	char* buf;
	long len;

	//must read files as binary to prevent problems from newline translation
	fp = fopen( filename, "rb");

	if ( fp == NULL)
		return 0;

	fseek( fp, 0, SEEK_END);
	len = ftell(fp);
	fseek( fp, 0, SEEK_SET);
	buf = new char[len+1];
	fread( buf, len, 1, fp);
	fclose( fp);

	buf[len] = '\0';
	return buf;
}

void LFile::WriteString(const char* fmt, ...)
{
	char szBuf[255];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(szBuf, 255, fmt, ap);
	va_end(ap);
	fwrite(szBuf, strlen(szBuf), 1, fp);
}

NS_CC_END