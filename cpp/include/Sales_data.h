#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>

class Sales_data {
    friend Sales_data add(const Sales_data &, const Sales_data &);
    friend std::istream &read(std::istream &is, Sales_data &item);
    friend std::ostream &print(std::ostream &os, const Sales_data &item);

   public:
    Sales_data(std::string s, unsigned cnt, double price)
        : bookNo(s), units_sold(cnt), revenue(price * cnt) {}  // 非委托构造函数
    // 委托构造函数
    Sales_data() : Sales_data("", 0, 0) {}
    explicit Sales_data(std::string s) : Sales_data(s, 0, 0) {}
    explicit Sales_data(std::istream &is) : Sales_data() { read(is, *this); }

    std::string isbn() const { return this->bookNo; }
    Sales_data &combine(const Sales_data &);  // 函数声明无需形参

   private:
    double avg_price() const {
        return this->units_sold ? revenue / units_sold : 0;
    };
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

// Sales_data 接口的非成员组成部分的声明
Sales_data add(const Sales_data &, const Sales_data &);
std::istream &read(std::istream &is, Sales_data &item);
std::ostream &print(std::ostream &os, const Sales_data &item);

Sales_data &Sales_data::combine(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

std::istream &read(std::istream &is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}
std::ostream &print(std::ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " "
       << item.avg_price();
    return os;
}

#endif