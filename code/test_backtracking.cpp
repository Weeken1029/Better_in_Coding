//---------------------------------------------------
using namespace std;

//------------------ LeetCode Test ---------------------------
//------------------ From BackTracking To ……--------------
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <unordered_set>

//组合
vector<vector<int>> combineAns;
vector<int> combinePath;
void combineBackTracking(int n, int k, int startIndex) {
    // 1.终止条件
    if (combinePath.size() == k) {
        combineAns.push_back(combinePath);
        return;
    }

    // 2.for循环，横向遍历，剪枝
    for (int i = startIndex; i <= (n - (k - combinePath.size()) + 1); i++) {
        combinePath.push_back(i);
        // 3.递归，纵向遍历
        combineBackTracking(n, k, i + 1);
        combinePath.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) {
    combinePath.clear();
    combineAns.clear();
    combineBackTracking(n, k, 1);
    return combineAns;
}

// 组合总和 III
vector<int> combinationSum3Path;
vector<vector<int>> combinationSum3Ans;
void combinationSum3BackTracking(int k, int n, int startIdx, int& sum) {// 这里的sum没必要引用
    // 0.附加：剪枝操作
    if (sum > n) return;

    // 1.终止条件
    if (combinationSum3Path.size() == k) {
        if(sum == n) combinationSum3Ans.push_back(combinationSum3Path);
        return;
    }

    // 2.for循环， 横向遍历， 剪枝操作
    for (int i = startIdx; i <= (10 - k + combinationSum3Path.size()); i++) {
        combinationSum3Path.push_back(i);
        sum += i;
        // 递归
        combinationSum3BackTracking(k, n, i + 1, sum);
        sum -= i;
        combinationSum3Path.pop_back();
    }
}

vector<vector<int>> combinationSum3(int k, int n) {
    combinationSum3Path.clear();
    combinationSum3Ans.clear();
    int sum = 0;
    combinationSum3BackTracking(k, n, 1, sum);
    return combinationSum3Ans;
}

//电话号码的字母组合
const string letterMap[10] = {
    "",     //0
    "",     //1
    "abc",  //2
    "def",  //3
    "ghi",  //4
    "jkl",  //5
    "mno",  //6
    "pqrs", //7
    "tuv",  //8
    "wxyz", //9
};

vector<string> letterAns;
string letterS;
void letterCombinationsBackTracking(const string& digits, int index){
    // 1.终止条件
    if (index == digits.size()) {
        letterAns.push_back(letterS);
        return;
    }

    int digit = digits[index] - '0';        // index指向的数字转化为int型
    string letter = letterMap[digit];
    // 2.for循环， 横向遍历
    for (int i = 0; i < letter.size(); i++) {
        letterS.push_back(letter[i]);
        letterCombinationsBackTracking(digits, index + 1);
        letterS.pop_back();
    }
}

vector<string> letterCombinations(string digits) {
    letterS.clear();
    letterAns.clear();
    if (digits.size() == 0) return letterAns;
    letterCombinationsBackTracking(digits, 0);
    return letterAns;
}

// 组合总和
vector<int> combinationSumPath;
vector<vector<int>> combinationSumAns;
void combinationSumBackTracking(int targetSum, vector<int>& candidates, int startIdx) {
    
    // 1.终止条件
    if (targetSum == 0) {
        combinationSumAns.push_back(combinationSumPath);
        return;
    }

    //2.for循环，横向遍历
    for (int i = startIdx; i < candidates.size(); i++) {
        if (targetSum < candidates[i]) break;
        // 处理
        combinationSumPath.push_back(candidates[i]);
        // 递归
        // 注意：这里是i，上面几题是i + 1。处理一个点可多次选的问题
        combinationSumBackTracking(targetSum - candidates[i], candidates, i);
        // 回溯
        combinationSumPath.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    combinationSumPath.clear();
    combinationSumAns.clear();
    sort(candidates.begin(), candidates.end(), less<int>());
    combinationSumBackTracking(target, candidates, 0);
    return combinationSumAns;
}

// 组合总和II
// ！！！注意！！！重复的元素组合，组成的组合间不重复的处理方法：同一维度上元素不重复
vector<vector<int>> combinationSum2Ans;
vector<int> combinationSum2Path;
void combinationSum2BackTracking(vector<int>& candidates, int targetSum, int startIdx) {
    // 1.终止条件
    if (targetSum == 0) {
        combinationSum2Ans.push_back(combinationSum2Path);
        return;
    }

    // 2.for循环 横向遍历
    for (int i = startIdx; i < candidates.size(); i++) {
        // 去重
        if (i != startIdx && candidates[i] == candidates[i - 1]) continue;
        // 剪枝操作
        if (candidates[i] > targetSum) break;
        // 处理
        combinationSum2Path.push_back(candidates[i]);
        // 递归
        combinationSum2BackTracking(candidates, targetSum - candidates[i], i + 1);
        // 回溯
        combinationSum2Path.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    combinationSum2Ans.clear();
    combinationSum2Path.clear();
    sort(candidates.begin(), candidates.end(), less<int>());
    combinationSum2BackTracking(candidates, target, 0);
    return combinationSum2Ans;
}

// 分割回文串
vector<string> partitionPath;
vector<vector<string>> partitionAns;
bool isPalidrome(const string &s, int start, int end) {
    for (int i = start, j = end; i < j; i++, j--) {
        if (s[i] != s[j]) {
            return false;
        }
    }
    return true;
}

void partitionBackTracking(string s, int startIdx) {
    //1.终止条件
    if (startIdx == s.size()) {
        partitionAns.push_back(partitionPath);
        return;
    }
    //2.for循环
    for (int i = startIdx; i < s.size(); i++) {
        if (isPalidrome(s, startIdx, i) == false) continue;
        string tmpStr = s.substr(startIdx, i - startIdx + 1);

        partitionPath.push_back(tmpStr);
        partitionBackTracking(s, i + 1);
        partitionPath.pop_back();
    }
}

vector<vector<string>> partition(string s) {
    partitionPath.clear();
    partitionAns.clear();
    partitionBackTracking(s, 0);
    return partitionAns;
}

// 复原IP地址
vector<int> ipAddressPath;
vector<string> ipAddressAns;
bool isValidIpAddress(string s) {
    if (s.size() > 3 || s.size() < 1) return false;
    if (s.size() > 1 && s[0] == '0') return false;
    
    int sum = 0;
    for (int i = 0; i < s.size(); i++) {
        sum = sum * 10 + s[i] - '0';
    }
    if (sum > 255 || sum < 0) return false;
    return true;
}

int ipAddressTransToInte(string s) {
    int sum = 0;
    for(int i = 0; i < s.size(); i++) {
        sum = sum * 10 + s[i] - '0';
    }
    return sum;
}

void restoreIpAddressBackTracking(string s, int startIdx) {
    //1.终止条件
    if (ipAddressPath.size() == 4 && startIdx == s.size()) {
        string Path;
        Path.clear();
        Path = Path + to_string(ipAddressPath[0]);
        Path = Path + '.';
        Path = Path + to_string(ipAddressPath[1]);
        Path = Path + '.';
        Path = Path + to_string(ipAddressPath[2]);
        Path = Path + '.';
        Path = Path + to_string(ipAddressPath[3]);
        ipAddressAns.push_back(Path);
        return;
    }

    //2.for循环 横向遍历
    for (int i = startIdx; i < s.size(); i++) {
        string tmpStr = s.substr(startIdx, i - startIdx + 1);
        if (isValidIpAddress(tmpStr) == false) continue;

        int tmpNum = ipAddressTransToInte(tmpStr);
        ipAddressPath.push_back(tmpNum);
        // 剪枝
        if ((s.size() - i - 1) > 3 * (4 - ipAddressPath.size())) {
            ipAddressPath.pop_back();
            continue;
        }
        restoreIpAddressBackTracking(s, i + 1);
        ipAddressPath.pop_back();
    }
}

vector<string> restoreIpAddresses(string s) {
    ipAddressPath.clear();
    ipAddressAns.clear();
    restoreIpAddressBackTracking(s, 0);
    return ipAddressAns;
}

// 子集
vector<int> subsetsPath;
vector<vector<int>> subsetsAns;
void subsetsBackTracking(vector<int>& nums, int startIdx) {
    //1.终止条件，此处终止条件比较特殊
    subsetsAns.push_back(subsetsPath);
    if (startIdx == nums.size()) {
        return;
    }

    //2.for循环 横向遍历
    for (int i = startIdx; i < nums.size(); i++) {
        subsetsPath.push_back(nums[i]);
        subsetsBackTracking(nums, i + 1);
        subsetsPath.pop_back();
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    subsetsPath.clear();
    subsetsAns.clear();
    subsetsBackTracking(nums, 0);
    return subsetsAns;
}

// 子集 II
// 注意：nums中相同元素并不一定挨着，所以先sort
vector<int> subsetDupPath;
vector<vector<int>> subsetDupAns;
void subsetsWithDupBackTracking(vector<int>& nums, int startIdx) {
    //1.终止条件
    subsetDupAns.push_back(subsetDupPath);
    if (startIdx == nums.size()) return;

    //2.for循环，横向遍历
    for (int i = startIdx; i < nums.size(); i++) {
        // 去重
        if (i != startIdx && nums[i] == nums[i - 1]) continue;
        subsetDupPath.push_back(nums[i]);
        subsetsWithDupBackTracking(nums, i + 1);
        subsetDupPath.pop_back();
    }
}

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    subsetDupPath.clear();
    subsetDupAns.clear();
    sort(nums.begin(), nums.end());
    subsetsWithDupBackTracking(nums, 0);
    return subsetDupAns;
}

// 递增子序列
vector<int> findSubseqPath;
vector<vector<int>>findSubseqAns;
void findSubsequencesBackTracking(vector<int>& nums, int startIdx) {
    // 这个判断里面不加return，因为取树上节点
    if (findSubseqPath.size() >= 2) {
        findSubseqAns.push_back(findSubseqPath);
    }
    //1.终止条件
    if (startIdx == nums.size()) {
        return;
    }

    unordered_set<int> uset;
    //2.for循环 横向遍历
    for (int i = startIdx; i < nums.size(); i++) {
        // 节点递增   同一树层去重
        if ((!findSubseqPath.empty() && nums[i] < findSubseqPath.back())
            || uset.find(nums[i]) != uset.end()) {
            continue;
        }
        // 记录当前元素使用过了
        uset.insert(nums[i]);
        findSubseqPath.push_back(nums[i]);
        findSubsequencesBackTracking(nums, i + 1);
        findSubseqPath.pop_back();
    }
}

vector<vector<int>> findSubsequences(vector<int>& nums) {
    findSubseqPath.clear();
    findSubseqAns.clear();
    findSubsequencesBackTracking(nums, 0);
    return findSubseqAns;
}

// 全排列
vector<int> permutePath;
vector<vector<int>> permuteAns;
void permuteBackTracking(vector<int>& nums, vector<bool>& used) {
    // 1.终止条件
    if(permutePath.size() == nums.size()){
        permuteAns.push_back(permutePath);
        return;
    }
    
    // 2.for循环 横向遍历
    for (int i = 0; i < nums.size(); i++) {
        if (used[i] == true) continue;
        else used[i] = true;
        permutePath.push_back(nums[i]);
        permuteBackTracking(nums, used);
        permutePath.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    permutePath.clear();
    permuteAns.clear();
    vector<bool> used(nums.size(), false);
    permuteBackTracking(nums, used);
    return permuteAns;
}

// 全排列 II
vector<int> permuteUniquePath;
vector<vector<int>> permuteUniqueAns;
void permuteUniqueBackTracking(vector<int>& nums, vector<bool>& used) {
    // 1.终止条件
    if (nums.size() == permuteUniquePath.size()) {
        permuteUniqueAns.push_back(permuteUniquePath);
        return;
    }
    // unordered_set不改变原数组顺序，也可以先排序采用先后判断
    unordered_set<int> uset;
    //2.for循环 横向遍历
    for (int i = 0; i < nums.size(); i++) {
        // 注意！！！ used和uset不直接放在if下，隐含了回溯
        if (uset.find(nums[i]) != uset.end()) continue;
        if (used[i] == true) continue;
        uset.insert(nums[i]);
        used[i] = true;

        permuteUniquePath.push_back(nums[i]);
        permuteUniqueBackTracking(nums, used);
        permuteUniquePath.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    permuteUniquePath.clear();
    permuteUniqueAns.clear();
    vector<bool> used(nums.size(), false);
    permuteUniqueBackTracking(nums, used);
    return permuteUniqueAns;
}

//TODO List 17.回溯总结要再看一遍，总结下规范的写法便于记忆

// 重新安排行程
vector<bool> used;
vector<vector<string>> findItineraryPath;
vector<string> findItineraryAns;
bool initFlag = false;
void findItineraryBackTracking(vector<vector<string>>& tickets){
    int pathSize = findItineraryPath.size();
    // 1.终止条件
    if (pathSize == tickets.size()) {
        bool flag = false;
        for (int idx = 0; idx < pathSize; idx++) {
            // 未初始化 / 比现有的更好
            if (initFlag != false && flag == false) {
                for (int j = 0; j < 3; ++j) {
                    // 当前路径更小
                    if (findItineraryPath[idx][0][j] < findItineraryAns[idx][j]) {
                        flag = true;
                        break;
                    }
                    // 当前路径更大
                    else if (findItineraryPath[idx][0][j] > findItineraryAns[idx][j]) {
                        return;
                    }
                }
            }
            findItineraryAns[idx] = findItineraryPath[idx][0];
        }
        findItineraryAns[pathSize] = findItineraryPath[pathSize - 1][1];
        initFlag = true;
        return;
    }

    // 2.for循环 横向遍历
    for (int i = 0; i < tickets.size(); i++) {
        // 判断首程为JFK
        if ((pathSize == 0) && (tickets[i][0] != "JFK"))  
            continue;

        // 判断相邻路程能否串起来
        if (pathSize != 0 && findItineraryPath[pathSize - 1][1] != tickets[i][0]) 
            continue;

        // 判断是否使用过
        if (used[i] == true)
            continue;

        // 递归and回溯
        used[i] = true;
        findItineraryPath.push_back(tickets[i]);
        findItineraryBackTracking(tickets);
        findItineraryPath.pop_back();
        used[i] = false;
    }
}

vector<string> findItinerary(vector<vector<string>>& tickets) {
    findItineraryPath.clear();
    findItineraryAns.clear();
    findItineraryAns.resize(tickets.size() + 1);
    used.resize(tickets.size(), false);
    findItineraryBackTracking(tickets);
    return findItineraryAns;
}

// N 皇后
vector<vector<string>> solveNQueensAns;
bool solveNQueenValid(int row, int col, vector<string>chessboard, int n) {
    // 检查列
    for (int i = 0; i < row; i++) {
        if (chessboard[i][col] == 'Q') {
            return false;
        }
    }

    // 检查45度
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (chessboard[i][j] == 'Q') {
            return false;
        }
    }

    // 检查135度
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (chessboard[i][j] == 'Q') {
            return false;
        }
    }
    return true;
}

// 这里的row作用 1)退出判断条件 2)当前元素是否合格提供索引。
// 这里的row意义：可理解为记录递归次数，像前面的startIdx，但用法不一样
void solveNQueensBackTracking(int n, int row, vector<string>& chessboard) {
    // 1.退出条件 因为已经到达叶子节点了
    if (row == n) {
        solveNQueensAns.push_back(chessboard);
        return;
    }

    //2.for循环 
    for (int col = 0; col < n; col++) {
        if (solveNQueenValid(row, col, chessboard, n)) {
            chessboard[row][col] = 'Q';
        }
        else continue;

        // 递归与回溯
        solveNQueensBackTracking(n, row + 1, chessboard);
        chessboard[row][col] = '.';
    }
}

vector<vector<string>> solveNQueens(int n) {
    solveNQueensAns.clear();
    vector<string> chessboard(n, string(n, '.'));
    solveNQueensBackTracking(n, 0, chessboard);
    return solveNQueensAns;
}

// 解数独
bool isValidSudoku(vector<vector<char>>& board, char num, int row, int col) {
    // 1.同一行
    for (int m_col = 0; m_col < 9; m_col++) {
        if (board[row][m_col] == num) return false;
    }

    // 2.同一列
    for (int m_row = 0; m_row < 9; m_row++) {
        if (board[m_row][col] == num) return false;
    }

    // 3.3X3
    int tmpRow = row / 3;
    int tmpCol = col / 3;
    for (int m_row = tmpRow * 3; m_row < (tmpRow + 1) * 3; m_row++) {
        for (int m_col = tmpCol * 3; m_col < (tmpCol + 1) * 3; m_col++) {
            if (board[m_row][m_col] == num) return false;
        }
    }

    return true;
}

bool solveSudokuBackTracking(vector<vector<char>>& board) {
    char tmpNum;
    // 1.行遍历， 纵向遍历
    for (int row = 0; row < board.size(); row++) {
        // 2.列遍历，横向遍历
        for (int col = 0; col < board[row].size(); col++) {
            if (board[row][col] != '.') continue;
            // 3.每格有9个数
            for (int num = 1; num < 10; num++) {
                tmpNum = num + '0';
                // 判断有效性
                if (isValidSudoku(board, tmpNum, row, col) == true) 
                    board[row][col] = tmpNum;
                else 
                    continue;
                //递归和回溯
                if (solveSudokuBackTracking(board) == true) 
                    return true;
                // 初始填数字的格子 不会被回溯，因此不用担心
                board[row][col] = '.';
            }
            // 9个数都不行
            return false;
        }
    }
    // 遍历结束也没返回FALSE 
    return true;
}


void solveSudoku(vector<vector<char>>& board) {
    solveSudokuBackTracking(board);
}

//------------------ 回溯测试 ---------------------------
namespace testBackTracking {

    void test_combine() {
        vector<vector<int>> ans = combine(4, 2);
        for (auto iter1 : ans) {
            for (auto iter2 : iter1) {
                cout << iter2 << ",";
            }
            cout << endl;
        }
    }

    void test_combinationSum3() {
        vector<vector<int>> ans = combinationSum3(3, 7);
        for (auto iter1 : ans) {
            for (auto iter2 : iter1) {
                cout << iter2 << ",";
            }
            cout << endl;
        }
    }

    void test_letterCombinations() {
        vector<string> ans = letterCombinations("23");
        for (auto iter1 : ans) {
            for (auto iter2 : iter1) {
                cout << iter2 << ",";
            }
            cout << endl;
        }
    }

    void test_combinationSum() {
        vector<int> candidates = { 2,3,6,7 };
        int target = 7;
        vector<vector<int>> ans = combinationSum(candidates, target);
    }

    void test_combinationSum2() {
        vector<int> candidates = { 2,5,2,1,2 };
        vector<vector<int>> ans = combinationSum2(candidates, 5);
        for (auto iter1 : ans) {
            for (auto iter2 : iter1) {
                cout << iter2 << ",";
            }
            cout << endl;
        }
    }

    void test_partition() {
        vector<vector<string>> ans = partition("a");
        for (auto iter1 : ans) {
            for (auto iter2 : iter1) {
                cout << iter2 << ",";
            }
            cout << endl;
        }
        cout << endl;
    }

    void test_restoreIpAddresses() {
        vector<string> ans = restoreIpAddresses("25525511135");
        for (auto iter1 : ans) {
            cout << iter1 << endl;
        }
    }

    void test_subsets() {
        vector<int> nums = { 1,2,3 };
        vector<vector<int>> ans = subsets(nums);
        for (auto& iter1 : ans) {
            for (auto& iter2 : iter1) {
                cout << iter2 << ", ";
            }
            cout << endl;
        }
    }

    void test_subsetsWithDup() {
        vector<int> nums = { 1,2,2 };
        vector<vector<int>> ans = subsetsWithDup(nums);
        for (auto iter1 : ans) {
            for (auto iter2 : iter1) {
                cout << iter2 << " ";
            }
            cout << endl;
        }
    }

    void test_findSubsequences() {
        vector<int> nums = { 4,6,4,7 };
        //vector<int> nums = { 1,2,3,4,5,6,7,8,9,10,1,1,1,1,1 };
        vector<vector<int>> ans = findSubsequences(nums);
        for (auto iter1 : ans) {
            for (auto iter2 : iter1) {
                cout << iter2 << " ";
            }
            cout << endl;
        }
    }

    void test_permute() {
        vector<int> nums = { 1,2,3 };
        vector<vector<int>> ans = permute(nums);
        for (auto iter1 : ans) {
            for (auto iter2 : iter1) {
                cout << iter2 << " ";
            }
            cout << endl;
        }
    }

    void test_permuteUnique() {
        vector<int> nums = { 1,1,2 };
        vector<vector<int>> ans = permuteUnique(nums);
        for (auto iter1 : ans) {
            for (auto iter2 : iter1) {
                cout << iter2 << " ";
            }
            cout << endl;
        }
    }

    void test_findItinerary() {
        string FromPortName, dstPortName;
        vector<string> FromAndToPorts(2," ");
        vector<vector<string>> airlineList;
        FromPortName = "JFK"; dstPortName = "SFO"; 
        FromAndToPorts[0] = FromPortName;
        FromAndToPorts[1] = dstPortName;
        airlineList.push_back(FromAndToPorts);
        FromPortName = "JFK"; dstPortName = "ATL";
        FromAndToPorts[0] = FromPortName;
        FromAndToPorts[1] = dstPortName;
        airlineList.push_back(FromAndToPorts);
        FromPortName = "SFO"; dstPortName = "ATL";
        FromAndToPorts[0] = FromPortName;
        FromAndToPorts[1] = dstPortName;
        airlineList.push_back(FromAndToPorts);
        FromPortName = "ATL"; dstPortName = "JFK";
        FromAndToPorts[0] = FromPortName;
        FromAndToPorts[1] = dstPortName;
        airlineList.push_back(FromAndToPorts);
        FromPortName = "ATL"; dstPortName = "SFO";
        FromAndToPorts[0] = FromPortName;
        FromAndToPorts[1] = dstPortName;
        airlineList.push_back(FromAndToPorts);
        vector<string> ans = findItinerary(airlineList);
        for (auto &iter : ans) {
            cout << iter << ' ';
        }
        cout << endl;
    }

    void test_solveNQueens() {
        vector<vector<string>> ans = solveNQueens(4);
        for (auto &iter : ans) {
            for (auto &iter2 : iter) {
                cout << iter2 << endl;
            }
            cout << endl << endl;
        }
    }

    void test_solveSudoku() {
        int n = 9;
        vector<vector<char>> board(n, vector<char>(n, '.'));
        board[0][0] = '5'; board[0][1] = '3'; board[0][4] = '7'; 
        board[1][0] = '6'; board[1][3] = '1'; board[1][4] = '9'; board[1][5] = '5'; 
        board[2][1] = '9'; board[2][2] = '8'; board[2][7] = '6'; 
        board[3][0] = '8'; board[3][4] = '6'; board[3][8] = '3'; 
        board[4][0] = '4'; board[4][3] = '8'; board[4][5] = '3'; board[4][8] = '1';
        board[5][0] = '7'; board[5][4] = '2'; board[5][8] = '6';
        board[6][1] = '6'; board[6][6] = '2'; board[6][7] = '8';
        board[7][3] = '4'; board[7][4] = '1'; board[7][5] = '9'; board[7][8] = '5';
        board[8][4] = '8'; board[8][7] = '7'; board[8][8] = '9';
        solveSudoku(board);
        for (auto iter : board) {
            for (auto iter2 : iter) {
                cout << iter2 << " ";
            }
            cout << endl;
        }
    }
}


//------------------ 主程序 ---------------------------
int main(int argc, char **argv) {

    // 组合
    //testBackTracking::test_combine();                           // 77.组合
    //testBackTracking::test_combinationSum3();                   // 216. 组合总和 III
    //testBackTracking::test_letterCombinations();                // 17. 电话号码的字母组合
    //testBackTracking::test_combinationSum();                    // 39. 组合总和
    //testBackTracking::test_combinationSum2();                   // 40.组合总和II
    
    // 分割
    //testBackTracking::test_partition();                         // 131.分割回文串（待写）
    //testBackTracking::test_restoreIpAddresses();                // 93.复原IP地址
    
    // 子集
    //testBackTracking::test_subsets();                           // 78. 子集
    //testBackTracking::test_subsetsWithDup();                    // 90. 子集 II
    //testBackTracking::test_findSubsequences();                  // 491. 递增子序列 (抄的代码随想录答案)

    // 排列
    //testBackTracking::test_permute();                           // 46. 全排列
    //testBackTracking::test_permuteUnique();                     // 47. 全排列 II

    // 其他 add 491
    //testBackTracking::test_findItinerary();                     // 332. 重新安排行程(代码有问题 超时)

    // 棋盘
    //testBackTracking::test_solveNQueens();                      // 51. N 皇后
    //testBackTracking::test_solveSudoku();                       // 37. 解数独


    system("pause");
}