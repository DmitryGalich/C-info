#include <iostream>
#include <utility>
#include <memory>

class Object
{
private:
    int m_num{-1};
    std::string m_text;
    int *m_pointerNum{nullptr};
    std::unique_ptr<std::string> m_uniqueStr;

public:
    Object() = delete;
    Object(const int num,
           const std::string &text,
           int pointerNum,
           const std::string &uniqueStr);

    // 3
    Object(const Object &obj);
    Object &operator=(const Object &obj);
    ~Object();

    // 5
    Object(Object &&obj) noexcept;
    Object &operator=(Object &&obj) noexcept;

private:
    void handleCopy(const Object &obj);
    void handleMove(Object &&obj);
};

Object::Object(const int num,
               const std::string &text,
               int pointerNum,
               const std::string &uniqueStr)
    : m_num(num),
      m_text(text),
      m_pointerNum(new int(pointerNum)),
      m_uniqueStr(std::make_unique<std::string>(uniqueStr))
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

Object::Object(const Object &obj)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    handleCopy(obj);
};

Object &Object::operator=(const Object &obj)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    if (&obj == this)
        return *this;

    handleCopy(obj);
    return *this;
}

Object::~Object()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    if (m_pointerNum != nullptr)
    {
        delete m_pointerNum;
        m_pointerNum = nullptr;
    }
};

Object::Object(Object &&obj) noexcept
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    handleMove(std::move(obj));
};

Object &Object::operator=(Object &&obj) noexcept
{
    if (&obj == this)
        return *this;

    handleMove(std::move(obj));
    return *this;
}

void Object::handleCopy(const Object &obj)
{
    m_num = obj.m_num;
    m_text = obj.m_text;
    m_pointerNum = new int(*obj.m_pointerNum);

    if (obj.m_uniqueStr)
    {
        m_uniqueStr = std::make_unique<std::string>(*obj.m_uniqueStr.get());
    }
}

void Object::handleMove(Object &&obj)
{
    m_num = std::exchange(obj.m_num, -1);
    m_text = std::exchange(obj.m_text, "");
    m_pointerNum = std::exchange(obj.m_pointerNum, nullptr);
    m_uniqueStr = std::move(obj.m_uniqueStr);
}

int main()
{
    Object obj0(100, "KEK", 42, "unique_KEK");
    Object obj1(obj0);
    Object obj2(std::move(obj0));

    obj0 = obj1;
    obj1 = std::move(obj2);

    return 0;
}