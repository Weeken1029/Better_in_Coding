//---------------------------------------------------
using namespace std;

//------------------ LeetCode Test ---------------------------
//------------------ From Greed To ……--------------
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include <list>

struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() {};
    TreeNode(int m_val) :val(m_val), left(nullptr), right(nullptr) {}
    TreeNode(int m_val, TreeNode* m_left, TreeNode* m_right) :
        val(m_val), left(m_left), right(m_right) {}
};

// 分发饼干
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end(), greater<int>());
    sort(s.begin(), s.end(), greater<int>());
    
    int sIndex = 0;
    int cnt = 0;
    for (int j = 0; j < g.size(); j++) {
        // s[sIndex]表示当前最大尺寸，需考虑s为null
        if (sIndex < s.size() && g[j] <= s[sIndex]) {
            sIndex++;
            cnt++;
        }
    }
    return cnt;
}

// 摆动序列
int wiggleMaxLength(vector<int>& nums) {

    int preDiff = 0;
    int curDiff = 0;
    int result = 1;

    for (int i = 1; i < nums.size(); i++) {
        curDiff = nums[i] - nums[i - 1];
        if ((curDiff > 0 && preDiff <= 0) || (curDiff < 0 && preDiff >= 0)) {
            result++;
            preDiff = curDiff;
        }
    }
    return result;
}

// 最大子数组和
int maxSubArray(vector<int>& nums) {
    
    int preSum = -1;
    int maxSum = INT16_MIN;

    for (int i = 0; i < nums.size(); i++) {
        // 前一个数 < 0直接更新到当前数，任何一个数加负数只会更小
        preSum = preSum < 0 ? nums[i] : (preSum + nums[i]);
        maxSum = maxSum < preSum ? preSum : maxSum;
    }

    return maxSum;
}

// 买卖股票的最佳时机 II
int maxProfit(vector<int>& prices) {
    int profitDiff = 0;
    int profitSum = 0;
    for (int i = 1; i < prices.size(); i++) {
        profitDiff = prices[i] - prices[i - 1];
        if (profitDiff > 0) {
            profitSum += profitDiff;
        }
    }
    return profitSum;
}

// 跳跃游戏
bool canJump(vector<int>& nums) {
    if (nums.size() == 1)return true;

    int endIndex = nums.size() - 1;
    int maxIndex = nums[0];

    for (int i = 1; i <= maxIndex; i++) {
        maxIndex = maxIndex > (i + nums[i]) ? maxIndex : (i + nums[i]);
        if (maxIndex >= endIndex) return true;
    }
    return false;
}

// 跳跃游戏 II
int jump(vector<int>& nums) {
    if (nums.size() == 1) return 0;

    int endIndex = nums.size() - 1;
    int count = 1;
    int maxIndex = nums[0];
    int curMaxIndex = maxIndex;


    for (int i = 1; i <= maxIndex; i++) {
        // 上一步走完后，最远能到的地方
        if (maxIndex >= endIndex)
        {
            break;
        }
        curMaxIndex = max(curMaxIndex, (i + nums[i]));
        if (curMaxIndex >= endIndex)
        {
            count++;
            break;
        }
        // 选择当前可走的所有步数，再更新maxIndex
        if (i == maxIndex) 
        {
            maxIndex = curMaxIndex;
            count++;
        }
    }
    return count;
}

// K次取反后最大化的数组和
int largestSumAfterKNegations(vector<int>& nums, int k) {
    int sum = 0;
    // 升序排列
    sort(nums.begin(), nums.end(), less<int>());
    int negNum = 0;
    // 负数数量
    while (negNum < nums.size() && nums[negNum] < 0) 
    {
        negNum++;
    }

    for (int i = 0; i < k; i++) {
        // 负数先取反为正
        if (i < negNum) 
        {
            nums[i] = -nums[i];
            continue;
        }
        // 没有负数
        if (negNum == 0) 
        {
            nums[0] = -nums[0];
            continue;
        }

        // 绝对值最小的取反
        if (negNum < nums.size() && (abs(nums[negNum - 1]) > abs(nums[negNum])))
        {
            nums[negNum] = -nums[negNum];
        }
        else 
        {
            nums[negNum - 1] = -nums[negNum - 1];
        }
    }
    // 求和
    for (auto iter : nums) {
        sum += iter;
    }
    return sum;
}

// 加油站
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int sum = 0;
    for (int i = 0; i < gas.size(); i++) {
        sum = sum + gas[i] - cost[i];
    }
    if (sum < 0) return -1;
    
    // 此时一定存在解 即sum >= 0
    int curGas = 0;
    int startIdx = 0;
    for (int i = 0; i < gas.size(); i++) 
    {
        if (curGas < 0)
        {
            curGas = 0;
            startIdx = i;
        }

        curGas = curGas + gas[i] - cost[i];
    }
    return startIdx;
}

// 分发糖果
int candy(vector<int>& ratings) {
    vector<int> minCandy(ratings.size(), 1);
    // 从左往右, 右边大加
    for (int i = 0; i < ratings.size() - 1; i++) {
        if (ratings[i + 1] > ratings[i]) 
        {
            minCandy[i + 1] = minCandy[i] + 1;
        }
    }

    // 从右往左，左边大加
    for (int i = ratings.size() - 1; i > 0; i--) {
        // 注意：第二次遍历时要判断是否已经左边比右边糖果多
        if (ratings[i - 1] > ratings[i] && minCandy[i - 1] <= minCandy[i])
        {
            minCandy[i - 1] = minCandy[i] + 1;
        }
    }
    int sum = 0;
    for (int i : minCandy) 
    {
        sum += i;
    }
    return sum;
}

// 柠檬水找零
bool lemonadeChange(vector<int>& bills) {
    int five = 0, ten = 0;
    if (bills[0] != 5) return false;

    for (int i = 0; i < bills.size(); i++) {
        // 5美元
        if (bills[i] == 5) five++;
        // 10美元
        if (bills[i] == 10) 
        {
            ten++;
            five--;
        }
        // 20美元
        if (bills[i] == 20) 
        {
            // 优先给出去10美元
            if (ten > 0) 
            {
                ten--;
                five--;
            }
            else 
            {
                five -= 3;
            }
        }
        //每次找零后判断5美元是否为负
        if (five < 0) return false;
    }
    return true;
}

// 根据身高重建队列
bool reconstructQueueComp(const vector<int> &a, const vector<int> &b) {
    if (a[0] == b[0]) 
    {
        // h相同k小的排前面
        return a[1] < b[1];
    }
    return a[0] > b[0];
}

vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), reconstructQueueComp);

    //链表更适合插入
    list<vector<int>> list;
    for (int i = 0; i < people.size(); i++) {
        int k = people[i][1];
        auto iter = list.begin();
        while (k--) 
        {
            iter++;
        }
        list.insert(iter, people[i]);
    }

    vector<vector<int>> ans(list.begin(), list.end());
    return ans;
}

// 用最少数量的箭引爆气球
bool findMinArrowShotsComp(const vector<int>&a, const vector<int>&b) 
{   
    if (a[0] == b[0]) return a[1] < b[1];
    return a[0] < b[0];
}

int findMinArrowShots(vector<vector<int>>& points) {
    // 先快排保证从低到高
    sort(points.begin(), points.end(), findMinArrowShotsComp);

    int curMax = points[0][1];
    int count = 1;
    for (int i = 1; i < points.size(); i++) 
    {
        // 当前点 最下限高于 前n次上限，需要加箭
        if (points[i][0] > curMax)
        {
            count++;
            curMax = points[i][1];
            continue;
        }
        
        // 当前点最高点低于 前n次上限，需要更新n次的上限
        if (points[i][1] < curMax)
        {
            curMax = points[i][1];
        }
    }
    return count;
}

// 无重叠区间
bool eraseOverlapIntervalsComp(const vector<int>& a, const vector<int>& b) 
{
    if (a[0] == b[0]) return a[1] < b[1];
    return a[0] < b[0];
}

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), eraseOverlapIntervalsComp);

    int curMax = intervals[0][1];
    int count = 0;

    for (int i = 1; i < intervals.size(); i++) 
    {
        // 有重叠
        if (intervals[i][0] < curMax) 
        {
            count++;
            // 判断是否更新最大上限
            // 保留的最大上限越小越好
            if (intervals[i][1] < curMax) 
            {
                curMax = intervals[i][1];
            }
        }
        // 无重叠，更新最大上限
        else 
        {
            curMax = intervals[i][1];
        }
    }
    return count;
}

// 划分字母区间
vector<int> partitionLabels(string s) {
    int hash[26] = { 0 };
    // 统计每个字母出现的最远位置
    for (int i = 0; i < s.size(); i++) {
        hash[s[i] - 'a'] = i;
    }

    vector<int> result;
    int curMaxPos = hash[s[0] - 'a'];
    int preMaxPos = -1;
    for (int i = 1; i < s.size(); i++)
    {
        if (i < curMaxPos)
        {
            if (hash[s[i] - 'a'] > curMaxPos) 
            {
                curMaxPos = hash[s[i] - 'a'];
            }
        }
        // 前一字符段塞入结果
        else if(i > curMaxPos)
        {
            result.push_back(curMaxPos - preMaxPos);
            preMaxPos = curMaxPos;
            curMaxPos = hash[s[i] - 'a'];
        }
        // 最后一个字母及其结果塞入
        if (i == s.size() - 1) 
        {
            result.push_back(curMaxPos - preMaxPos);
        }

    }
    return result;
}

// 合并区间
bool mergeComp(const vector<int>& a, const vector<int>& b) 
{
    if (a[0] == b[0]) return a[1] < b[1];
    return a[0] < b[0];
}

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), mergeComp);

    vector<vector<int>> ans;
    int curMinPos = intervals[0][0];
    int curMaxPos = intervals[0][1];
    for (int i = 1; i < intervals.size(); i++) 
    {
        // 1.当前点下限在区间内
        if (intervals[i][0] <= curMaxPos) 
        {
            // 更新最大上限
            curMaxPos = max(intervals[i][1], curMaxPos);
        }
        // 2.当前点下限在区间外
        else 
        {
            ans.push_back({ curMinPos, curMaxPos });
            curMinPos = intervals[i][0];
            curMaxPos = intervals[i][1];
        }
    }
    // 3.最后一组处理
    ans.push_back({ curMinPos, curMaxPos });
    return ans;
}

// 单调递增的数字
int monotoneIncreasingDigits(int n) {
    if (n == 0) return 0;

    // 1.从个位到最高位存储到vector中
    vector<int>nums;
    while (n > 0 ) 
    {
        nums.push_back(n % 10);
        n = n / 10;
    }
    // 2.低位往高位比较
    for (int i = 0; i < nums.size() - 1; i++) 
    {
        if (nums[i] < nums[i + 1]) 
        {
            nums[i] = 9;
            nums[i + 1] = nums[i + 1] - 1;
        }
    }

    // 3.高位往低位比较
    for (int i = nums.size() - 1; i > 0; i--) 
    {
        if (nums[i] > nums[i - 1]) 
        {
            nums[i - 1] = 9;
        }
    }

    int ans = 0;
    for (int i = nums.size() -1; i >= 0 ; i--)
    {
        ans = ans * 10 + nums[i];
    }

    return ans;
}

// 买卖股票的最佳时机含手续费
int maxProfitWithServiceCharge(vector<int>& prices, int fee) {
    int result = 0;
    int minPrice = prices[0];
    for (int i = 1; i < prices.size(); i++) 
    {
        //相当于买入
        if (prices[i] < minPrice) minPrice = prices[i];

        // 继续持有
        if (prices[i] >= minPrice && prices[i] <= minPrice + fee) continue;

        // 相当于卖出，但是最后一次卖出才是真正卖出
        if (prices[i] > minPrice + fee) 
        {
            result += prices[i] - minPrice - fee;
            // 最关键的一步，算出卖出后等价的最小成本
            // 可以理解为：当下卖出后，下次买入是否存在套利空间
            minPrice = prices[i] - fee;
        }
    }
    return result;
}

// 监控二叉树
int minCameraCover(TreeNode* root) {
    return 0;
}



//------------------ 回溯测试 ---------------------------
namespace testGreed {

    void test_findContentChildren() {
        vector<int> g{ 1,2 };
        vector<int> s{ 1,2,3 };
        cout << findContentChildren(g, s) << endl;
    }

    void test_wiggleMaxLength() {
        //vector<int> nums = { 1,7,4,9,2,5 };
        vector<int> nums = { 1, 17, 5, 10, 13, 15, 10, 5, 16, 8 };
        cout << wiggleMaxLength(nums) << endl;
    }

    void test_maxSubArray() {
        vector<int>nums = { -2,1,-3,4,-1,2,1,-5,4 };
        vector<int>nums2 = { 5,4,-1,7,8 };
        cout << maxSubArray(nums) << endl;
        cout << maxSubArray(nums2) << endl;
    }

    void test_maxProfit() {
        vector<int> prices = { 7,1,5,3,6,4 };
        vector<int> prices2 = { 7,6,4,3,1 };
        cout << maxProfit(prices) << endl;
        cout << maxProfit(prices2) << endl;
    }

    void test_canJump() {
        vector<int>nums = {0};
        cout << canJump(nums) << endl;
    }

    void test_jump() {
        vector<int> nums = { 1,2};
        cout << jump(nums) << endl;
    }

    void test_largestSumAfterKNegations() {
        vector<int> nums = { -4,-2,-3 };
        int k = 4;
        cout << largestSumAfterKNegations(nums, k) << endl;
    }
    
    void test_canCompleteCircuit() {
        vector<int> gas = { 2,3,4 };
        vector<int> cost = { 3,4,3 };
        cout << canCompleteCircuit(gas, cost) << endl;
    }

    void test_candy() {
        vector<int> ratings = { 1,3,4,5,2 };
        cout << candy(ratings) << endl;
    }

    void test_lemonadeChange() {
        vector<int> bills = { 10,10 };
        cout << lemonadeChange(bills) << endl;
    }

    void test_reconstructQueue() {
        vector<vector<int>> people = { {7,0}, {4,4}, {7,1}, {5,0}, {6,1}, {5,2} };
        vector<vector<int>> ans = reconstructQueue(people);

        for (auto iter : ans) {
            for (int i : iter) {
                cout << i << " ";
            }
            cout << endl;
        }
    }

    void test_findMinArrowShots() {
        vector<vector<int>> points = { {9,12},{1,10},{4,11},{8,12},{3,9},{6,9},{6,7}};
        cout << findMinArrowShots(points) << endl;
    }

    void test_eraseOverlapIntervals() {
        vector<vector<int>> interval = { {1,100},{11,22},{1,11},{2,12} };
        //vector<vector<int>> interval = { {-52,31},{-73,-26},{ 82,97 },{ -65,-11 },{ -62,-49 },\
        //{ 95,99 },{ 58,95 },{ -31,49 },{ 66,98 },{ -63,2 },{ 30,47 },{ -40,-26 } };
        cout << eraseOverlapIntervals(interval) << endl;
    }

    void test_partitionLabels(){
        string s = "ababcbacadefegdehijhklij";
        vector<int> ans = partitionLabels(s);
        for (auto iter : ans) 
        {
            cout << iter << " ";
        }
    }

    void test_merge() {
        vector<vector<int>> intervals = { {1,3}, {2,6}, {8,10}, {15,18} };
        vector<vector<int>> ans = merge(intervals);
        for (auto iter : ans) 
        {
            for(auto iter2: iter)
            {
                cout << iter2 << " ";
            }
            cout << endl;
        }
    }

    void test_monotoneIncreasingDigits() {
        int n = 100;
        cout << monotoneIncreasingDigits(n) << endl;
    }

    void test_maxProfitWithServiceCharge() {
        vector<int> prices = { 5,1,3,2,8,4,9 };
        int fee = 2;
        cout << maxProfitWithServiceCharge(prices, fee) << endl;
    }

    void test_minCameraCover() 
    {
        TreeNode* root = new TreeNode(0);
        TreeNode* level_11 = new TreeNode(0);
        TreeNode* level_21 = new TreeNode(0);
        TreeNode* level_22 = new TreeNode(0);
        root->left = level_11; level_11->left = level_21; level_11->right = level_22;
        cout << minCameraCover(root) << endl;
    }

}


//------------------ 主程序 ---------------------------
int main(int argc, char **argv) {
    
    // 类型一：取巧
    //testGreed::test_findContentChildren();                                      // 455. 分发饼干
    //testGreed::test_wiggleMaxLength();                                          // 376. 摆动序列
    //testGreed::test_maxSubArray();                                              // 53. 最大子数组和
    //testGreed::test_maxProfit();                                                // 122. 买卖股票的最佳时机 II
    //testGreed::test_canJump();                                                  // 55. 跳跃游戏
    //testGreed::test_jump();                                                     // 45. 跳跃游戏 II
    //testGreed::test_largestSumAfterKNegations();                                // 1005. K 次取反后最大化的数组和
    //testGreed::test_canCompleteCircuit();                                       // 134. 加油站

    // 类型二：两个维度问题
    //testGreed::test_candy();                                                    // 135. 分发糖果
    //testGreed::test_lemonadeChange();                                           // 860.柠檬水找零
    //testGreed::test_reconstructQueue();                                         // 406. 根据身高重建队列
    //testGreed::test_findMinArrowShots();                                        // 452. 用最少数量的箭引爆气球
    //testGreed::test_eraseOverlapIntervals();                                    // 435. 无重叠区间
    //testGreed::test_partitionLabels();                                          // 763. 划分字母区间
    //testGreed::test_merge();                                                    // 56. 合并区间
    //testGreed::test_monotoneIncreasingDigits();                                 // 738. 单调递增的数字（类似135. 分发糖果）
    
    //类型三
    //testGreed::test_maxProfitWithServiceCharge();                               // 714. 买卖股票的最佳时机含手续费（代码随想录答案）
    //testGreed::test_minCameraCover();                                           // 968.监控二叉树(delay)

    system("pause");
}
