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
	int score = 0;
	cocos2d::Label * labelScore;
	std::list<cocos2d::Sprite*> * GoodsList;//������Ʒ����
	std::list<cocos2d::Sprite*> * daodan;//��������
public:
	cocos2d::ui::LoadingBar * loadingbar0;
	static cocos2d::Scene * createScene();
	void touchEvent(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	virtual bool init();
	bool addWorldEdge();
	void Down(float dt);
	void childThreadPlayContactBGM();
	//��ʾ�����б�
	void showPHList(cocos2d::Ref * pSender);
	void JudgeTimer(float dt);
	CREATE_FUNC(PlayScene);
};
#endif