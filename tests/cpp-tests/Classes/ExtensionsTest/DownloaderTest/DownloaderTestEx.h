#ifndef __Downloader_Test_H__
#define __Downloader_Test_H__

#include "extensions/cocos-ext.h"
#include "../../BaseTest.h"

DEFINE_TEST_SUITE(DownloaderExTests);

class DownloaderScene : public TestCase
{
public:
    static DownloaderScene* create();

    DownloaderScene();
    
    virtual std::string title() const override;

    virtual bool init() override;
    virtual void onExit() override;
    
private:
    cocos2d::Layer* _loadLayer;
    cocos2d::Menu* _downloadMenu;

    cocos2d::Label* _progress;

    void onLoadEnd();
};

#endif /* defined(__Downloader_Test_H__) */
