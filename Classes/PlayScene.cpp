#include"PlayScene.h"
#include"SimpleAudioEngine.h"
#include"ui\CocosGUI.h"  // LoadingBar
#include<random>
#define PLAYERTAG 1
#define GOODSTAG 2
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;
Scene * PlayScene::createScene()
{
	Scene * scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = PlayScene::create();
	scene->addChild(layer);
	return scene;
}
bool PlayScene::init()
{
	if (!Layer::init())
		return false;
	this->setTouchEnabled(true);


	GoodsList = new list<Sprite*>();//������Ʒ����
	Size visibleSize = Director::getInstance()->getVisibleSize();
	addWorldEdge();//�����������߽�
	Sprite * bkg = Sprite::create("playScene.jpeg");
	bkg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	bkg->setContentSize(visibleSize);
	this->addChild(bkg, -1);
	//���ű�������
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("zb.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("zb.mp3");
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	//����
	player = Sprite::create("bag.jpg");
	player->setPosition(Vec2(50, 100));
	player->setTag(PLAYERTAG);
	PhysicsBody *body = PhysicsBody::createCircle(player->getContentSize().width / 2);
	body->setCategoryBitmask(PLAYERTAG);
	body->setContactTestBitmask(GOODSTAG);
	//
	/*1����Node�趨PhysicBody���������״
		2��isDynamic(true)�Ż���ײ(ֻҪһ����̬����)
		3���������ͣ�setCategoryBitmask����һ������������AΪ1��BΪ2��CΪ3
		4��������ײ���ˣ�����AҪ��B��C��ײ������a->setContactTestBitmask(2 | 3)*/
	body->setDynamic(false);
	this->player->setPhysicsBody(body);
	this->addChild(player);
	//�����¼�
	auto touchListener = EventListenerTouchOneByOne::create();//������ģ�¼�����
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [this](Touch * touch, Event*event)  //[]�������ⲿ����Ĳ�����()�����ǵ����ߴ������,���[=] c++11��ʾ ����ֱ�ӷ����ⲿ����
	{
		Vec2 pos = touch->getLocation(); //��ȡOpenGl���꣬Cocos2dx�õ������� ���½ǿ�ʼ������
		CCLOG("Begin Touch:%f,%f", pos.x, pos.y);
		this->player->setPositionX(pos.x);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	//��ײ�¼�����
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact &contact)
	{
		Sprite * sA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		Sprite * sB = (Sprite*)contact.getShapeB()->getBody()->getNode();
		int tagA = sA->getTag();
		int tagB = sB->getTag();
		if (tagA == PLAYERTAG&&tagB == GOODSTAG)
		{
			this->GoodsList->remove(sB);
			this->removeChild(sB);
			SimpleAudioEngine::sharedEngine()->playEffect("623.mp3");
			if (this->loadingbar0->getPercent() < 100)
				this->loadingbar0->setPercent(this->loadingbar0->getPercent() + 5);
		}
		if (tagA == GOODSTAG&&tagB == PLAYERTAG)
		{
			this->GoodsList->remove(sA);
			this->removeChild(sA);
			SimpleAudioEngine::sharedEngine()->playEffect("623.mp3");
			if (this->loadingbar0->getPercent() < 100)
				this->loadingbar0->setPercent(this->loadingbar0->getPercent() + 5);
		}
		return true;
	};
	//������
	this->loadingbar0 = ui::LoadingBar::create("LoadingBarFile.png");
	loadingbar0->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingbar0->setPercent(35);
	loadingbar0->setPosition(Vec2(visibleSize.width - loadingbar0->getContentSize().width + 10, visibleSize.height - 50));
	addChild(loadingbar0);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	//������Ʒ��ʱ��
	this->schedule(schedule_selector(PlayScene::Down), 2.0);
	return true;
}
bool PlayScene::addWorldEdge()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize,
		PHYSICSBODY_MATERIAL_DEFAULT, 5.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	return true;
}
void PlayScene::Down(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	std::default_random_engine e(time(nullptr));
	std::uniform_real_distribution<double> u(0, 1);
	CCLOG("schedule %f", u(e));
	//����������Ʒ
	auto Good = Sprite::create("money.jpg");
	Good->setTag(GOODSTAG);

	Good->setScale(0.5);
	PhysicsBody * body = PhysicsBody::createCircle(Good->getContentSize().width / 2);
	body->setDynamic(true);
	body->setCategoryBitmask(GOODSTAG);
	body->setContactTestBitmask(PLAYERTAG);
	Good->setPhysicsBody(body);
	Good->setPosition(visibleSize.height* u(e), 500);
	this->addChild(Good);
	this->GoodsList->push_back(Good);
	//###################�жϵ�����Ʒ�Ƿ��ڵ���##########################
	/*list<Sprite*> * willdellist = new list<Sprite*>();
	for (list<Sprite*>::iterator iterator = GoodsList->begin(); iterator != GoodsList->end(); iterator++)
	{
	Sprite * pSprite = (Sprite*)(*iterator);
	float posY = pSprite->getPositionY();
	if (posY <= pSprite->getContentSize().height + 1)
	{
	willdellist->push_back(*iterator);
	}
	}
	//ִ��ɾ��
	for (list<Sprite*>::iterator iterator = willdellist->begin(); iterator != willdellist->end(); iterator++)
	{
	GoodsList->remove(*iterator);
	this->removeChild(*iterator);
	}
	delete willdellist;//�ͷ��ڴ�
	*/
}
void PlayScene::touchEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{

}
void PlayScene::childThreadPlayContactBGM()
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("smzy_2013131635677.mp3", false);
}