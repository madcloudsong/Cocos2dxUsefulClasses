#include "TestFrameManager.h"
#include "editor-support\cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

bool TestFrameManager::init()
{
    if ( !TestBase::init() )
    {
        return false;
    }

    auto item = MenuItemFont::create("SHOW", CC_CALLBACK_1(TestFrameManager::btVisbleCallback, this));
	item->setAnchorPoint(Vec2(0.5f,0.5f));
	item->setPosition(m_visibleCenter);

    auto menu = Menu::create(item, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu,0);
    
	/*Frame的测试*/
	Widget* frame = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("FrameManager/UIRes/DemoLogin.ExportJson");
	frame->setScale(0.8f); //缩放比例可以随便设置
	frame->setAnchorPoint(Vec2(0.5f,0.5f));//锚点可以随便设置
	frame->setPosition(m_visibleCenter);//坐标可以随便设置
	this->addChild(frame,1);
	
	//触碰测试
	Helper::seekWidgetByName(frame,"login_Button")->addTouchEventListener(CC_CALLBACK_2(TestFrameManager::touchUiItemCallBack,this));
	Helper::seekWidgetByName(frame,"close_Button")->addTouchEventListener(CC_CALLBACK_2(TestFrameManager::touchUiItemCallBack,this));
	Helper::seekWidgetByName(frame,"agree_CheckBox")->addTouchEventListener(CC_CALLBACK_2(TestFrameManager::touchUiItemCallBack,this));
	Helper::seekWidgetByName(frame,"name_TextField")->addTouchEventListener(CC_CALLBACK_2(TestFrameManager::touchUiItemCallBack,this));
	Helper::seekWidgetByName(frame,"password_TextField")->addTouchEventListener(CC_CALLBACK_2(TestFrameManager::touchUiItemCallBack,this));
	Helper::seekWidgetByName(frame,"confirm_TextField")->addTouchEventListener(CC_CALLBACK_2(TestFrameManager::touchUiItemCallBack,this));

	//frame初始化,可以试一下不初始化，直接layer->setVisible(false);设置窗口不可见之后,鼠标点击原本的按钮区域，看看是否有对话框出现
	m_frame.setFrame(frame,Helper::seekWidgetByName(frame,"backageImg"));

	//设置点击在对话框外部时候的监听事件，可以在这里将对话框隐藏
	m_frame.setTouchOutOfFrameEventListener(CC_CALLBACK_1(TestFrameManager::touchOutOfFrame,this));
	
	m_frame.setFrameVisible(true);

    return true;
}

void TestFrameManager::btVisbleCallback(Ref* pSender)
{
	//设置对话框可见
	m_frame.setFrameVisible(true);
}

void TestFrameManager::touchUiItemCallBack(Ref* pObject,Widget::TouchEventType eventType)
{
	if(eventType == Widget::TouchEventType::ENDED)
	{
		MessageBox("touch ui widget","touch ui widget");
	}
}

void TestFrameManager::touchOutOfFrame(cocos2d::ui::Widget*)
{
	//触碰点在对话框外，将对话框隐藏
	m_frame.setFrameVisible(false);
}

