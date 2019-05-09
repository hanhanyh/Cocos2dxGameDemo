#ifndef WELCOMESCENE_H_
#define WELCOMESCENE_H_
#include"cocos2d.h"
//»¶Ó­Ò³Ãæ
class ComeScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	void startGameEvt(Ref * Sender);
	CREATE_FUNC(ComeScene);
};
#endif