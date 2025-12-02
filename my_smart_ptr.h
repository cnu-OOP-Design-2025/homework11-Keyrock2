#pragma once
#include <algorithm>

// 2. my_shared_ptr 구현
template <typename T>
class my_shared_ptr
{
private:
    T *ptr;
    size_t *refCount;

public:
    // 생성자: ptr이 없어도 refCount는 무조건 생성
    explicit my_shared_ptr(T *p = nullptr) : ptr(p), refCount(new size_t(1)) {}

    // 복사 생성자
    my_shared_ptr(const my_shared_ptr &other) : ptr(other.ptr), refCount(other.refCount)
    {
        (*refCount)++; // 참조 카운트 증가
    }

    // 대입 연산자
    my_shared_ptr &operator=(const my_shared_ptr &other)
    {
        if (this != &other)
        {
            release(); // 기존 리소스 해제

            // 새로운 데이터 복사
            ptr = other.ptr;
            refCount = other.refCount;
            (*refCount)++; // 카운트 증가
        }
        return *this;
    }

    // 소멸자
    ~my_shared_ptr() { release(); }

    // 참조 해제
    void release()
    {
        if (refCount)
        {
            (*refCount)--; // 카운트 감소
            if (*refCount == 0)
            {
                if (ptr)
                    delete ptr;  // 객체 삭제
                delete refCount; // 카운트 변수 삭제
            }
        }
        // 안전을 위해 포인터 초기화
        ptr = nullptr;
        refCount = nullptr;
    }

    // 접근 연산자
    T &operator*() const { return *ptr; }
    T *operator->() const { return ptr; }

    // 참조 카운트 확인
    // refCount가 nullptr일 경우는 release된 이후뿐이므로 안전장치 추가
    size_t use_count() const
    {
        return (refCount) ? *refCount : 0;
    }

    // get() 기능
    T *get() const { return ptr; }

    // reset() 기능: 과제 규칙에 따라 무조건 카운트 1 생성
    void reset(T *p = nullptr)
    {
        release(); // 기존 연결 끊기

        ptr = p;
        refCount = new size_t(1); // null이어도 카운트 1로 새로 시작
    }
};

// 1. my_unique_ptr 구현 (기존과 동일)
template <typename T>
class my_unique_ptr
{
private:
    T *ptr;

public:
    explicit my_unique_ptr(T *p = nullptr) : ptr(p) {}

    ~my_unique_ptr()
    {
        delete ptr;
    }

    my_unique_ptr(const my_unique_ptr &) = delete;
    my_unique_ptr &operator=(const my_unique_ptr &) = delete;

    // 이동 생성자
    my_unique_ptr(my_unique_ptr &&other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    // 이동 대입 연산자
    my_unique_ptr &operator=(my_unique_ptr &&other) noexcept
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T &operator*() const { return *ptr; }
    T *operator->() const { return ptr; }
    T *get() const { return ptr; }

    T *release()
    {
        T *temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T *p = nullptr)
    {
        delete ptr;
        ptr = p;
    }
};