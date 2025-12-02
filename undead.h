#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "character.h"
using namespace std;

class Undead
{
public:
    virtual string name() const = 0;
    virtual int power() const = 0;
    virtual int agility() const = 0;
    virtual int endurance() const = 0;
    virtual ~Undead() {}
};

class Zombie : public Undead
{
public:
    string name() const override { return "Zombie"; }
    int power() const override { return 15; }
    int agility() const override { return 5; }
    int endurance() const override { return 20; }
};

class Skeleton : public Undead
{
public:
    string name() const override { return "Skeleton"; }
    int power() const override { return 10; }
    int agility() const override { return 15; }
    int endurance() const override { return 10; }
};

class Lich : public Undead
{
public:
    string name() const override { return "Lich"; }
    int power() const override { return 25; }
    int agility() const override { return 12; }
    int endurance() const override { return 18; }
};

// 3. Adapter 구현: Undead → Character 변환
class UndeadAdapter : public Character
{
    shared_ptr<Undead> undead; // Undead 객체를 보유 (Composition)
public:
    UndeadAdapter(shared_ptr<Undead> u) : undead(u)
    {
        /* TODO: Character의 속성 설정 */
        this->description = u->name(); // Undead 이름 -> Character 설명

        // 이름에 따라 CharacterType 설정 (간단한 문자열 비교)
        if (description == "Zombie")
            this->type = CharacterType::Zombie;
        else if (description == "Skeleton")
            this->type = CharacterType::Skeleton;
        else if (description == "Lich")
            this->type = CharacterType::Lich;
        else
            this->type = CharacterType::Unknown;
    }

    // Undead의 능력치를 Character의 능력치로 매핑
    int getAttack() const override
    {
        /* TODO */
        return undead->power();
    }
    int getSpeed() const override
    {
        /* TODO */
        return undead->agility();
    }
    int getDefense() const override
    {
        /* TODO */
        return undead->endurance();
    }
};