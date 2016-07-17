/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "FileDownloader.h"
#include "base/CCConsole.h"
#include "platform/CCPlatformMacros.h"
#include "unzip.h"

#include <curl/curl.h>

static size_t writeFile(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	FILE *fp = (FILE*)userdata;
	size_t written = fwrite(ptr, size, nmemb, fp);
	return written;
}

static int progressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
	//GameUpdateMgr* downlolader = (GameUpdateMgr*)ptr;
	//if (0 != downlolader->_progressHandler) {
	//	int p = (totalToDownload > 0) ? (int)(nowDownloaded / totalToDownload * 100.0f) : 0;
	//	pthread_mutex_lock(&mutexProgressNum);
	//	progressNum = p;
	//	pthread_mutex_unlock(&mutexProgressNum);
	//}

	return 0;
}

NS_CC_EXT_BEGIN

using namespace cocos2d;

FileDownloader::FileDownloader()
{
}

FileDownloader::~FileDownloader()
{
}

void FileDownloader::downloadAndUncompress(const std::string & url, const std::string & path)
{
	if (download(url.c_str()))
	{
		uncompress(path.c_str());
	}
}

int FileDownloader::download(const std::string& url)
{
	std::string outFileName = "d:/update.zip";
	FILE *fp = fopen(outFileName.c_str(), "wb");
	if (NULL == fp) {
		CCLOG("file create failed ");
		return -1;
	}

	void* _curl = curl_easy_init();
	if (NULL == _curl) {
		CCLOG("performDownload(): curl easy init failed ");
		return -3;
	}

	curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, writeFile);
	curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
	//curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, this);
	//curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, progressFunc);
	curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_LIMIT, 1L);
	curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_TIME, 3L);
	//curl_easy_setopt( _curl, CURLOPT_TIMEOUT, 10);
	curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, 10);

	CURLcode res = curl_easy_perform(_curl);
	curl_easy_cleanup(_curl);
	if (0 != res) {
		//CCLOG("error when download package");
		fclose(fp);

		return -2;
	}

	fclose(fp);
	return 1;
}

void FileDownloader::uncompress(const std::string & path)
{
}

NS_CC_EXT_END