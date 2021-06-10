#include "../def/InputMatcher.h"

void read(map<pair<string, string>, vector<string> > &parsing_table, map<string, unordered_set<string>> &sync_table) {
    int rows;
    std::cin >> rows;
    for (int row = 0; row < rows; row++) {
        string token;
        int input_tokens;
        std::cin >> token;
        std::cin >> input_tokens;
        for (int i = 0; i < input_tokens; i++) {
            string input_str;
            std::cin >> input_str;
            int next_count;
            std::cin >> next_count;
            while (next_count--) {
//                std::cout << "shit " << std::endl;
                string to;
                std::cin >> to;
//                std::cout << to << std::endl;
                parsing_table[make_pair(token, input_str)].push_back(to);
            }
        }
    }
    int sync_cnt;
    std::cin >> sync_cnt;
    while (sync_cnt-- > 0) {

    }
}

void test1() {
    freopen("../tests/in1", "r", stdin);
    map<pair<string, string>, vector<string> > t;
    map<string, unordered_set<string>> t2;
    read(t, t2);
    InputMatcher::getInstance().setTable(t, t2, "E");
    vector<string> input = {"id", "+", "id", "$"};
    for (auto s : input) {
        InputMatcher::getInstance().match(s);
    }

}

void test2() {
    freopen("../tests/in2", "r", stdin);
    map<pair<string, string>, vector<string> > t;
    map<string, unordered_set<string>> t2;
    read(t, t2);
    InputMatcher::getInstance().setTable(t, t2, "S");
    vector<string> input = {"c", "e", "a", "d", "b", "$"};
    for (auto s : input) {
        InputMatcher::getInstance().match(s);
    }

}

int main() {
    // Don't run both tests together !!!!
    std::cout << "test_1 begin=============" << std::endl;
    test1();
    std::cout << "test_1 end================" << std::endl;
    std::cout << "test_2 begin===============" << std::endl;
//    test2();
    std::cout << "test_2 end=============" << std::endl;
    return 0;
}