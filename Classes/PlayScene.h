#ifndef PLAYSCENE_H_
#define PLAYSCENE_H_
#include "cocos2d.h"
#include"ui\UIWidget.h"
#include"ui\CocosGUI.h"
#include<list>
class PlayScene :public cocos2d::Layer
{
private:
	cocos2d::Sprite * player;
	
	std::list<cocos2d::Sprite*> * GoodsList;//掉落物品集合
public:
	cocos2d::ui::LoadingBar * loadingbar0;
	static cocos2d::Scene * createScene();
	void touchEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	virtual bool init();
	bool addWorldEdge();
	void Down(float dt);
	void childThreadPlayContactBGM();
	CREATE_FUNC(PlayScene);
};
#endif