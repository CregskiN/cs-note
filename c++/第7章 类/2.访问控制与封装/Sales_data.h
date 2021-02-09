#ifndef SALES_DATA_H

#define SALES_DATA_H
#include <iostream>
#include <string>

/**
 * @brief 销售数据类
 * 
 */
class Sales_data {
    // 为 Sales_data类的非成员函数 添加友元声明
    friend Sales_data add(const Sales_data &, const Sales_data &);
    friend std::istream &read(std::istream &, Sales_data &);
    friend std::ostream &print(std::ostream &, const Sales_data &);

   public:
    // 构造函数
    Sales_data() = default;
    Sales_data(const std::string &s) : bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n) {}
    Sales_data(std::istream &);

    // 成员函数：对Sales_data对象的操作
    std::string isbn() const { return this->bookNo; }  // 成员函数：用于返回对象的ISBN编号
    Sales_data &combine(const Sales_data &);           // 成员函数：用于将一个Sales_data对象加到另一个对象上
    double avg_price() const;                          // 成员函数：返回书的平均价格

   private:
    std::string bookNo;       // 书的ISBN编号
    unsigned units_sold = 0;  // 书的销量
    double revenue = 0.0;     // 这本书的总销售收入
};

// 非成员函数的接口
Sales_data add(const Sales_data &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);

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