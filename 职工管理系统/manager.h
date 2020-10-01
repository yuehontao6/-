#pragma once
#include<iostream>
using namespace std;
#include"worker.h"


//经理类
class Manager :public Worker
{
public:
	//构造函数
	Manager(int id, string name, int dId);

	virtual void showInfo();

	//获取岗位名称
	virtual string getDeptName();

	
};
