#pragma once
#include "Actor.h"
// �ṹ���ʾ��ײ��Ϣ
struct CollisionInfo {
    bool collided; // �Ƿ�������ײ
    int collisionType; // ��ײ����
    Actor* actor;//collision item type
    // �������ܵ���Ϣ
};