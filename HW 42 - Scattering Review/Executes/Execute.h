#pragma once

class Execute
{
public:
	Execute()
	{

	}
	
	// 사실 추상 클래스에서 소멸자의 경우 virtual 안써도 가상으로 이루어짐
	virtual ~Execute() {} // virtual 안하면 호출 안됨 protected 있어서

	virtual void Update() = 0;
	
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	virtual void ResizeScreen() = 0;
};