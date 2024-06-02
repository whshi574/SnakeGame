#pragma once
#include "Actor.h"
// 结构体表示碰撞信息
struct CollisionInfo {
    bool collided; // 是否发生了碰撞
    int collisionType; // 碰撞类型
    Actor* actor;//collision item type
    // 其他可能的信息
};