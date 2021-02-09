#ifndef SALES_DATA_H

#define SALES_DATA_H
#include <iostream>
#include <string>

/* 
    Sales_data 的接口应包含：
    + isbn 成员函数：用于返回对象的ISBN编号
    + combine 成员函数：用于将一个Sales_data对象加到另一个对象上
    + avg_price 成员函数：返回书的平均价格
    + add 函数：执行两个Sales_data的加法
    + read 函数：将数据从istream读入到Sales_data对象中
    + print 函数：将Sales_data对象的值，输出到ostream
*/

/* 
    定义 Sales_data 的构造函数，需要以下四个：
        1. 形参列表：istream&
        说明：从中获取一条交易信息
        2. 形参列表：const string& ISBN编号，unsigned 售出图书数量，double 售出价格
        说明：
        3. 形参列表：const string& ISBN编号
        说明：编译器将赋予其他成员默认值
        4. 一个空参数列表（即默认构造函数）
        说明：我们已经定义其他构造函数，也必须定义一个默认构造函数
 */

/**
 * @brief 销售数据类
 * 
 */
struct Sales_data {
    // 构造函数
    Sales_data() = default;
    Sales_data(const std::string &s) : bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n) {}
    Sales_data(std::istream &);

    // 成员函数：对Sales_data对象的操作
    // std::string isbn() const { return (*this).bookNo; }
    std::string isbn() const { return this->bookNo; }  // 成员函数：用于返回对象的ISBN编号
    Sales_data &combine(const Sales_data &);           // 成员函数：用于将一个Sales_data对象加到另一个对象上
    double avg_price() const;                          // 成员函数：返回书的平均价格

    std::string bookNo;       // 书的ISBN编号
    unsigned units_sold = 0;  // 书的销量
    double revenue = 0.0;     // 这本书的总销售收入
};

// 非成员函数的接口
Sales_data add(const Sales_data &, const Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &);

/**
 * @brief 返回单价
 * 
 * @return double 
 */
double Sales_data::avg_price() const {
    if (units_sold) {
        return revenue / units_sold;
    } else {
        return 0;
    }
}

/**
 * @brief 这个构造函数没有使用构造函数初始值列表，因为函数体内部完成了初始化操作(read)
 * 
 * @param is 
 */
Sales_data::Sales_data(std::istream &is) {
    read(is, *this);  // read 作用是从 is 中读取一条信息，然后存入 this
}

/**
 * @brief 合并 Sales_data rhs 对象到本对象，并返回
 * 
 * @param rhs 
 * @return Sales_data& 
 */
Sales_data &Sales_data::combine(const Sales_data &rhs) {
    units_sold = units_sold + rhs.units_sold;
    revenue = revenue + rhs.revenue;
    return *this;
}

/**
 * @brief 融合两个销售数据对象
 * 
 * @param lhs 
 * @param rhs 
 * @return Sales_data 
 */
Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

/**
 * @brief 读销售数据
 * 
 * @param is 输入流，用于读取
 * @param item 读入的 Sales_data 对象
 * @return std::istream& 
 */
std::istream &read(std::istream &is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

/**
 * @brief 打印销售数据
 * 
 * @param os 输出流，用于打印
 * @param item 读入的 Slaes_data 对象
 * @return std::ostream& 
 */
std::ostream &print(std::ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}

#endif
