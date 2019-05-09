#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocos2d::ui;
Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
 
}
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//创建一个物理世界, 大小和屏幕的尺寸相同, 使用默认材质, debug框的宽度为3个像素
	{	//定义世界的边界
		auto body = PhysicsBody::createEdgeBox(visibleSize,
			PHYSICSBODY_MATERIAL_DEFAULT, 5.0f);
		auto edgeNode = Node::create();
		edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));               
			edgeNode->setPhysicsBody(body);
		this->addChild(edgeNode);
		
	}
	player = Sprite::create("sp.jpg");
	player->setTag(1);
	player->setScale(0.2);
	auto body = PhysicsBody::createCircle(player->getContentSize().width / 1.5);
	body->setDynamic(true);
	body->setRotationEnable(false);//禁用旋转
	player->setPhysicsBody(body);
	player->setPosition(Vec2(500,500));
	this->addChild(player);
	//操作菜单
	Menu * ControlMenu = Menu::create();
	ControlMenu->setPosition(Vec2(400, 100));
	MenuItemImage * playItem = MenuItemImage::create("jumpbtn.jpg", "jumpbtn.jpg", CC_CALLBACK_1(HelloWorld::JumpCallBack, this));
	playItem->setScale(0.5);
	ControlMenu->addChild(playItem);

	this->addChild(ControlMenu);
	return true;
}
void HelloWorld::JumpCallBack(Ref* pSender)
{
	CCLOG("点击了");
	//JumpBy * jumpby = JumpBy::create(1, Vec2(50, 50), 0, 1);
	//player->runAction(jumpby);
 
	player->getPhysicsBody()->applyImpulse(Vec2(100000, 100000),player->getPosition());

	////
	
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
