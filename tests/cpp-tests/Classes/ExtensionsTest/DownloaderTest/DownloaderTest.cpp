#include "DownloaderTest.h"
#include "../../testResource.h"
#include "cocos2d.h"
#include "extensions/assets-manager/FileDownloader.h"

USING_NS_CC;
USING_NS_CC_EXT;

DownloaderTests::DownloaderTests()
{
	addTestCase("DownloaderTests", [](){ return DownloaderScene::create(); });
}

DownloaderScene* DownloaderScene::create()
{
    auto scene = new (std::nothrow) DownloaderScene();
    if (scene && scene->init())
    {
        scene->autorelease();
    }
    else
    {
        delete scene;
        scene = nullptr;
    }

    return scene;
}

DownloaderScene::DownloaderScene()
: _loadLayer(nullptr)
, _downloadMenu(nullptr)
, _progress(nullptr)
{

}

bool DownloaderScene::init()
{
    if (!TestCase::init())
    {
        return false;
    }

    //auto downloadLabel = Label::createWithTTF("Start Download", "fonts/arial.ttf", 16);
    //auto downloadItem = MenuItemLabel::create(downloadLabel, CC_CALLBACK_1(DownloaderScene::startDownloadCallback, this));
    //downloadItem->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y + 100));
    //_downloadMenu = Menu::create(downloadItem, nullptr);
    //_downloadMenu->setPosition(Vec2::ZERO);
    //this->addChild(_downloadMenu, 1);

    //_loadLayer = Layer::create();
    //addChild(_loadLayer);

    //auto sprite = Sprite::create("Images/Icon.png");
    //_loadLayer->addChild(sprite);
    //sprite->setPosition( VisibleRect::center() );
    //
    //TTFConfig config("fonts/tahoma.ttf", 30);
    //_progress = Label::createWithTTF(config, "0%", TextHAlignment::CENTER);
    //_progress->setPosition( Vec2(VisibleRect::center().x, VisibleRect::center().y + 50) );
    //_loadLayer->addChild(_progress);
    
	FileDownloader loder;
	loder.downloadAndUncompress("localhost/behaviac-master.zip", "");

    return true;
}

void DownloaderScene::onLoadEnd()
{
}

void DownloaderScene::onExit()
{
    TestCase::onExit();
}

std::string DownloaderScene::title() const
{
    return "DownloaderScene";
}
