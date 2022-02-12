#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

int main() {
    return 0;
}

/**
 * @brief 实际转换操作
 *
 * @param s
 * @param m
 * @return const std::string
 */
const std::string transform(const std::string &s, const std::map<std::string, std::string> &m) {
    auto map_it = m.find(s);
    // 如果单词 s 在转换规则 m 中
    if (map_it != m.cend())
        return map_it->second;  // 使用替换短语
    else
        return s;  // 返回原单词
}

/**
 * @brief 1. 创建转换映射
 *
 * @param map_file
 * @return std::map<std::string, std::string>
 */
std::map<std::string, std::string> buildMap(std::ifstream &map_file) {
    std::map<std::string, std::string> trans_map;
    std::string key;
    std::string value;
    while (map_file >> key && std::getline(map_file, value)) {  // 读取第一个单词存入key，剩余内容存入 value
        if (value.size() > 1)
            trans_map[key] = value.substr(1);  // 跳过隔离空格
        else
            throw std::runtime_error("没有提供给" + key + "的规则");
    }
    return trans_map;
}

/**
 * @brief 外部转化接口
 *
 * @param map_file
 * @param input
 */
void word_transform(std::ifstream &map_file, std::ifstream &input) {
    auto trans_map = buildMap(map_file);
    std::string text;
    while (std::getline(input, text)) {  // 读取每个单词
        std::istringstream stream(text);
        std::string word;
        bool firstword = true;  // 控制是否打印空格
        while (stream >> word) {
            if (firstword)
                firstword = false;
            else
                std::cout << " ";
            std::cout << transform(word, trans_map);
        }
        std::cout << std::endl;
    }
}