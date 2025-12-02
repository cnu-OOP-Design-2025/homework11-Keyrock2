#include <iostream>
#include <memory>
#include <vector>
#include "character.h"
#include "undead.h"
#include "my_smart_ptr.h"
using namespace std;

void equip_test1(shared_ptr<Character> c1)
{
    c1 = make_shared<Armor>(c1);
    c1 = make_shared<Boots>(c1);
    c1 = make_shared<Sword>(c1);
    cout << c1->getDescription()
         << " | Attack: " << c1->getAttack()
         << " | Speed: " << c1->getSpeed()
         << " | Defense: " << c1->getDefense() << endl;
}

void equip_test2(shared_ptr<Character> c1)
{
    c1 = make_shared<Armor>(c1);
    c1 = make_shared<Bow>(c1);
    cout << c1->getDescription()
         << " | Attack: " << c1->getAttack()
         << " | Speed: " << c1->getSpeed()
         << " | Defense: " << c1->getDefense() << endl;
}

void equip_test3(shared_ptr<Character> c1)
{
    c1 = make_shared<Boots>(c1);
    c1 = make_shared<Staff>(c1);
    cout << c1->getDescription()
         << " | Attack: " << c1->getAttack()
         << " | Speed: " << c1->getSpeed()
         << " | Defense: " << c1->getDefense() << endl;
}

void doTest3()
{
    cout << "=== Test 3 ===" << endl;
    vector<shared_ptr<Character>> players;
    players.push_back(make_shared<Knight>());
    players.push_back(make_shared<Wizard>());
    players.push_back(make_shared<Archer>());

    /* TODO: Adapter를 사용하여 Undead 캐릭터들 추가 */
    // Zombie 캐릭터를 players에 추가 (UndeadAdapter로 감싸서)
    players.push_back(make_shared<UndeadAdapter>(make_shared<Zombie>()));

    // Skeleton 캐릭터를 players에 추가
    players.push_back(make_shared<UndeadAdapter>(make_shared<Skeleton>()));

    // Lich 캐릭터를 players에 추가
    players.push_back(make_shared<UndeadAdapter>(make_shared<Lich>()));

    for (auto player : players)
    {
        cout << "-------------------------------------------------------------" << endl;
        equip_test1(player);
        equip_test2(player);
        equip_test3(player);
    }
    cout << "-------------------------------------------------------------" << endl;
}

struct Student
{
    string name;
    Student(string name) : name(name) {};
    Student() = delete;
    ~Student() { cout << "Delete Student " << name << endl; }
};

void doTest2()
{
    cout << "=== Test 2 ===" << endl;
    my_shared_ptr<Student> p1(new Student("Jack"));
    cout << "p1 use_count: " << p1.use_count() << endl;
    {
        my_shared_ptr<Student> p2 = p1; // 복사
        cout << "After copy, p1 use_count: " << p1.use_count() << endl;
        {
            my_shared_ptr<Student> p3 = p2; // 복사
            cout << "After copy, p1 use_count: " << p1.use_count() << endl;
        }
        cout << "After p3 goes out of scope, p1 use_count: " << p1.use_count() << endl;

        p2.reset(new Student("Kim"));
        cout << "After p2 reset, p1 use_count: " << p1.use_count() << ":" << p1.get()->name << endl;
        cout << "After p2 reset, p2 use_count: " << p2.use_count() << ":" << p2.get()->name << endl;
    }
    p1.reset();

    cout << "After p1 reset, p1 use_count: " << p1.use_count() << endl;

    if (p1.get() == nullptr)
        cout << "After p1 reset, p1 is nullptr" << endl;
}

void doTest1()
{
    cout << "=== Test 1 ===" << endl;
    my_unique_ptr<Student> p1(new Student("Jack"));
    cout << "Create p1 : " << p1->name << endl;

    my_unique_ptr<Student> p2 = std::move(p1); // 이동 생성자
    if (p1.get() == nullptr)
        cout << "After move, p1 is empty" << endl;

    if (p2.get() == nullptr)
        return;
    cout << "Create p2 : " << p2->name << endl;

    my_unique_ptr<Student> p3(new Student("Kim"));
    cout << "Create p3 : " << p3->name << endl;

    p3 = std::move(p2); // 이동 할당자

    if (p2.get() == nullptr)
        cout << "After move, p2 is empty" << endl;

    cout << "After move, p3 : " << p3->name << endl;

    p3.reset(new Student("Lee"));
    cout << "After p3 reset, p3 : " << p3->name << endl;

    Student *ptr = p3.release();
    if (p3.get() == nullptr)
        cout << "p3 release ownership" << endl;

    cout << "raw pointer: " << ptr->name << endl;

    delete ptr;
}

int main(int argc, const char *argv[])
{
    if (argc == 2)
    {
        switch (atoi(argv[1]))
        {
        case 1:
            doTest1();
            return 0;
        case 2:
            doTest2();
            return 0;
        case 3:
            doTest3();
            return 0;
        }
    }
    doTest1();
    doTest2();
    doTest3();

    return 0;
}