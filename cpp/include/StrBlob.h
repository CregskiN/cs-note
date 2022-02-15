#ifndef STRBLOB_H
#define STRBLOB_H
#include <memory>
#include <string>
#include <vector>

using namespace std;

class StrBlob {
   public:
    typedef vector<string>::size_type size_type;
    // 构造函数
    StrBlob();
    StrBlob(initializer_list<string> il);
    //
    size_type size() const { return data->size(); };
    bool empty() const { return data->empty(); };
    // 增删元素
    void push_back(const string &t);
    void pop_back();
    // 元素访问
    string &front();
    string &back();

   private:
    shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg) const;
};

// 构造函数
StrBlob::StrBlob() : data(make_shared<vector<string>>()){};
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)){};

// public 成员函数
/**
 * @brief 检查 StrBlob 内是否有 i 个元素
 *
 * @param i 假设 StrBlob 内元素数量
 * @param msg 若检查出错，给出的提示
 */
void StrBlob::check(size_type i, const string &msg) const {
    // 检查
    if (i >= data->size())
        throw out_of_range(msg);
}

/**
 * @brief 返回头部元素
 *
 * @return string&
 */
string &StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}

/**
 * @brief 返回尾部元素
 *
 * @return string&
 */
string &StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

/**
 * @brief
 *
 */
void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

void StrBlob::push_back(const string &t) {
    data->push_back(t);
}

#endif