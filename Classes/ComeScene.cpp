#include"ComeScene.h"
#include"ui\UIImageView.h"
#include"HelloWorldScene.h"
#include"PlayScene.h"
#include<ui\UIListView.h>
#include<ui/UILayout.h>
USING_NS_CC;
using namespace cocos2d::ui;
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
	myLabel->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2 + 200));
	this->addChild(myLabel);

	CCLabelTTF* stopLabel = CCLabelTTF::create("Play Game", "arial", 50);
	stopLabel->setColor(ccc3(0, 255, 0));
	CCLabelTTF* startLabel = CCLabelTTF::create("About", "arial", 50);
	startLabel->setColor(ccc3(0, 255, 0));

	//创建文字菜单选项，参数（文字label，目标类，要执行的函数）
	CCMenuItemLabel* mLabel1 = CCMenuItemLabel::create(stopLabel, CC_CALLBACK_1(ComeScene::startGameEvt, this));
	mLabel1->setPosition(ccp(visibleSize.width / 2, 250));
	//About
	CCMenuItemLabel* mLabel2 = CCMenuItemLabel::create(startLabel, [this, visibleSize](Ref * Sender){
		Layout* 	layout = Layout::create();
		layout->setSize(Size(visibleSize.width, visibleSize.height));
		//横向排列，这里类似Android里的线性布局
		//layout->setLayoutType(LAYOUT_RELATIVE);
		/*以图片为背景*/
		layout->setBackGroundImageScale9Enabled(true);
		layout->setBackGroundImage("green_edit.png");
		layout->setPosition(Point(50, 0));
		addChild(layout);

		ListView* listView = ListView::create();
		//SCROLLVIEW_DIR_VERTICAL  SCROLLVIEW_DIR_HORIZONTAL   
		listView->setDirection(SCROLLVIEW_DIR_VERTICAL);
		listView->setTouchEnabled(true);
		listView->setBounceEnabled(true);
		listView->setBackGroundImage("green_edit.png");
		listView->setBackGroundImageScale9Enabled(true);
		listView->setSize(Size(480, 260));
		listView->setPosition(Point(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
		//	listView->addEventListenerListView(this, listvieweventselector(LayoutTest::selectedItemEvent));
		layout->addChild(listView);
		//create model
		Button* default_button = Button::create("backtotoppressed.png");
		default_button->setName("Title Button");

		Layout* default_item = Layout::create();
		default_item->setTouchEnabled(true);
		default_item->setSize(default_button->getSize());
		default_button->setPosition(Point(default_item->getSize().width / 2.0f, default_item->getSize().height / 2.0f));
		default_item->addChild(default_button);
		//set model
		listView->setItemModel(default_item);
		listView->setItemsMargin(20);
		//add default item
		listView->pushBackDefaultItem();
		listView->pushBackDefaultItem();
		listView->pushBackDefaultItem();
		listView->pushBackDefaultItem();
	});
	mLabel2->setPosition(ccp(visibleSize.width / 2, 50));
	//将选项添加进菜单，参数（n个MneuItem，NULL）
	CCMenu* m1 = CCMenu::create(mLabel1, mLabel2, NULL);
	m1->setPosition(ccp(0, 0 + 200));
	this->addChild(m1);
	return true;
}
void ComeScene::startGameEvt(Ref * Sender)
{
	Director::getInstance()->replaceScene(PlayScene::createScene());
}
