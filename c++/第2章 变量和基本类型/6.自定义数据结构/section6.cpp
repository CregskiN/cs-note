#include <iostream>
#include <string>

#include "Sales_data.h"

/*
 *  2.6 自定义数据结构
 *
 * + 2.6.1 定义 Sales_data 类型
 * + 2.6.2 使用 Sales_data 类
 * + 2.6.3 编写自己的头文件
 */

int main() {
    /**
     * 2.6.1 定义 Sales_data 类型
     *
     * + 类数据成员
     */
    // struct Sales_data {
    //     std::string bookNo;
    //     unsigned units_sold = 0;
    //     double revenue = 0.0;
    // };
    // Sales_data accum, trans, *salesptr;

    /*
        类数据成员 data member
        类内初始值 in-class initializer
     */

    /**
     * 2.6.2 使用 Sales_data 类
     *
     * + 添加两个 Sales_data 对象
     * + Sales_data 对象读入数据
     * + 输出两个 Sales_data 对象的和
     */
    Sales_data data1, data2;
    // 1. 读入data1 data2的代码
    // 2. 对比 data1 data2的ISBN代码是否相同
    // 3. 如果相同，球data1 data2 数量总和
    double price = 0;
    // 读入第一笔交易：ISBN、销售数量、单价
    std::cin >> data1.bookNo >> data1.units_sold >> price;
    // 计算销售收入
    data1.revenue = data1.units_sold * price;

    // 读入第二笔交易：ISNB、销售数量、单价
    std::cin >> data2.bookNo >> data2.units_sold >> price;
    data2.revenue = data2.units_sold * price;

    // 检查笔订单对应的 ISBN 是否相同
    if (data1.bookNo == data2.bookNo) {
        // 计算总销量
        unsigned totalCount = data1.units_sold + data2.units_sold;
        // 计算总销售额
        double totalRevenue = data1.revenue + data2.revenue;
        // 输出：ISBN、总销量、总销售额、平均价格
        std::cout << data1.bookNo << " " << totalCount << " " << totalRevenue
                  << " " << std::endl;
        if (totalCount != 0) {
            std::cout << totalRevenue / totalCount << std::endl;
        } else {
            std::cout << "(no sales)" << std::endl;
        }
        return 0;
    } else {
        std::cerr << "Data must refer to the same ISBN"
                  << std::endl;  // 标示失败
        return -1;
    }

    /**
     * 2.6.3 编写自己的头文件
     * 
     * + 与处理器概述
     * 
     */
    

    return 0;
}
