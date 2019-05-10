#include"ComeScene.h"
#include"ui\UIImageView.h"
#include"HelloWorldScene.h"
#include"PlayScene.h"
USING_NS_CC;
Scene * ComeScene::createScene()
{
	Scene * scene = Scene::create();
	auto layer = ComeScene::create();
	scene->addChild(layer);
	return scene;
}
bool ComeScene::init()
{
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto imgview = ui::ImageView::create("comeBkg.jpg");
	imgview->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	imgview->setSize(visibleSize);
	this->addChild(imgview);
	//
	auto myLabel = Label::createWithSystemFont("DouDou Play", "Arial", 40);
	myLabel->setPosition(Vec2(visibleSize.width / 2-50, visibleSize.height / 2 + 200));
	this->addChild(myLabel);

	CCLabelTTF* stopLabel = CCLabelTTF::create("Play Game", "arial", 50);
	stopLabel->setColor(ccc3(0, 255, 0));
	CCLabelTTF* startLabel = CCLabelTTF::create("About", "arial", 50);
	startLabel->setColor(ccc3(0, 255, 0));

	//创建文字菜单选项，参数（文字label，目标类，要执行的函数）
	CCMenuItemLabel* mLabel1 = CCMenuItemLabel::create(stopLabel,CC_CALLBACK_1(ComeScene::startGameEvt,this));
	mLabel1->setPosition(ccp(visibleSize.width / 2, 250));
	CCMenuItemLabel* mLabel2 = CCMenuItemLabel::create(startLabel);
	mLabel2->setPosition(ccp(visibleSize.width / 2, 50));
	//将选项添加进菜单，参数（n个MneuItem，NULL）
	CCMenu* m1 = CCMenu::create(mLabel1, mLabel2, NULL);
	m1->setPosition(ccp(0,0+200));
	this->addChild(m1);
	return true;
}
void ComeScene::startGameEvt(Ref * Sender)
{
	Director::getInstance()->replaceScene(PlayScene::createScene());
}
