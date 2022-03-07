//---------------------------------------------------
using namespace std;

//------------------ LeetCode Test ---------------------------
//------------------ From Greed To ����--------------
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

// �ַ�����
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end(), greater<int>());
    sort(s.begin(), s.end(), greater<int>());
    
    int sIndex = 0;
    int cnt = 0;
    for (int j = 0; j < g.size(); j++) {
        // s[sIndex]��ʾ��ǰ���ߴ磬�迼��sΪnull
        if (sIndex < s.size() && g[j] <= s[sIndex]) {
            sIndex++;
            cnt++;
        }
    }
    return cnt;
}

// �ڶ�����
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

// ����������
int maxSubArray(vector<int>& nums) {
    
    int preSum = -1;
    int maxSum = INT16_MIN;

    for (int i = 0; i < nums.size(); i++) {
        // ǰһ���� < 0ֱ�Ӹ��µ���ǰ�����κ�һ�����Ӹ���ֻ���С
        preSum = preSum < 0 ? nums[i] : (preSum + nums[i]);
        maxSum = maxSum < preSum ? preSum : maxSum;
    }

    return maxSum;
}

// ������Ʊ�����ʱ�� II
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

// ��Ծ��Ϸ
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

// ��Ծ��Ϸ II
int jump(vector<int>& nums) {
    if (nums.size() == 1) return 0;

    int endIndex = nums.size() - 1;
    int count = 1;
    int maxIndex = nums[0];
    int curMaxIndex = maxIndex;


    for (int i = 1; i <= maxIndex; i++) {
        // ��һ���������Զ�ܵ��ĵط�
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
        // ѡ��ǰ���ߵ����в������ٸ���maxIndex
        if (i == maxIndex) 
        {
            maxIndex = curMaxIndex;
            count++;
        }
    }
    return count;
}

// K��ȡ������󻯵������
int largestSumAfterKNegations(vector<int>& nums, int k) {
    int sum = 0;
    // ��������
    sort(nums.begin(), nums.end(), less<int>());
    int negNum = 0;
    // ��������
    while (negNum < nums.size() && nums[negNum] < 0) 
    {
        negNum++;
    }

    for (int i = 0; i < k; i++) {
        // ������ȡ��Ϊ��
        if (i < negNum) 
        {
            nums[i] = -nums[i];
            continue;
        }
        // û�и���
        if (negNum == 0) 
        {
            nums[0] = -nums[0];
            continue;
        }

        // ����ֵ��С��ȡ��
        if (negNum < nums.size() && (abs(nums[negNum - 1]) > abs(nums[negNum])))
        {
            nums[negNum] = -nums[negNum];
        }
        else 
        {
            nums[negNum - 1] = -nums[negNum - 1];
        }
    }
    // ���
    for (auto iter : nums) {
        sum += iter;
    }
    return sum;
}

// ����վ
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int sum = 0;
    for (int i = 0; i < gas.size(); i++) {
        sum = sum + gas[i] - cost[i];
    }
    if (sum < 0) return -1;
    
    // ��ʱһ�����ڽ� ��sum >= 0
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

// �ַ��ǹ�
int candy(vector<int>& ratings) {
    vector<int> minCandy(ratings.size(), 1);
    // ��������, �ұߴ��
    for (int i = 0; i < ratings.size() - 1; i++) {
        if (ratings[i + 1] > ratings[i]) 
        {
            minCandy[i + 1] = minCandy[i] + 1;
        }
    }

    // ����������ߴ��
    for (int i = ratings.size() - 1; i > 0; i--) {
        // ע�⣺�ڶ��α���ʱҪ�ж��Ƿ��Ѿ���߱��ұ��ǹ���
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

// ����ˮ����
bool lemonadeChange(vector<int>& bills) {
    int five = 0, ten = 0;
    if (bills[0] != 5) return false;

    for (int i = 0; i < bills.size(); i++) {
        // 5��Ԫ
        if (bills[i] == 5) five++;
        // 10��Ԫ
        if (bills[i] == 10) 
        {
            ten++;
            five--;
        }
        // 20��Ԫ
        if (bills[i] == 20) 
        {
            // ���ȸ���ȥ10��Ԫ
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
        //ÿ��������ж�5��Ԫ�Ƿ�Ϊ��
        if (five < 0) return false;
    }
    return true;
}

// ��������ؽ�����
bool reconstructQueueComp(const vector<int> &a, const vector<int> &b) {
    if (a[0] == b[0]) 
    {
        // h��ͬkС����ǰ��
        return a[1] < b[1];
    }
    return a[0] > b[0];
}

vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), reconstructQueueComp);

    //������ʺϲ���
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

// �����������ļ���������
bool findMinArrowShotsComp(const vector<int>&a, const vector<int>&b) 
{   
    if (a[0] == b[0]) return a[1] < b[1];
    return a[0] < b[0];
}

int findMinArrowShots(vector<vector<int>>& points) {
    // �ȿ��ű�֤�ӵ͵���
    sort(points.begin(), points.end(), findMinArrowShotsComp);

    int curMax = points[0][1];
    int count = 1;
    for (int i = 1; i < points.size(); i++) 
    {
        // ��ǰ�� �����޸��� ǰn�����ޣ���Ҫ�Ӽ�
        if (points[i][0] > curMax)
        {
            count++;
            curMax = points[i][1];
            continue;
        }
        
        // ��ǰ����ߵ���� ǰn�����ޣ���Ҫ����n�ε�����
        if (points[i][1] < curMax)
        {
            curMax = points[i][1];
        }
    }
    return count;
}

// ���ص�����
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
        // ���ص�
        if (intervals[i][0] < curMax) 
        {
            count++;
            // �ж��Ƿ�����������
            // �������������ԽСԽ��
            if (intervals[i][1] < curMax) 
            {
                curMax = intervals[i][1];
            }
        }
        // ���ص��������������
        else 
        {
            curMax = intervals[i][1];
        }
    }
    return count;
}

// ������ĸ����
vector<int> partitionLabels(string s) {
    int hash[26] = { 0 };
    // ͳ��ÿ����ĸ���ֵ���Զλ��
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
        // ǰһ�ַ���������
        else if(i > curMaxPos)
        {
            result.push_back(curMaxPos - preMaxPos);
            preMaxPos = curMaxPos;
            curMaxPos = hash[s[i] - 'a'];
        }
        // ���һ����ĸ����������
        if (i == s.size() - 1) 
        {
            result.push_back(curMaxPos - preMaxPos);
        }

    }
    return result;
}

// �ϲ�����
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
        // 1.��ǰ��������������
        if (intervals[i][0] <= curMaxPos) 
        {
            // �����������
            curMaxPos = max(intervals[i][1], curMaxPos);
        }
        // 2.��ǰ��������������
        else 
        {
            ans.push_back({ curMinPos, curMaxPos });
            curMinPos = intervals[i][0];
            curMaxPos = intervals[i][1];
        }
    }
    // 3.���һ�鴦��
    ans.push_back({ curMinPos, curMaxPos });
    return ans;
}

// ��������������
int monotoneIncreasingDigits(int n) {
    if (n == 0) return 0;

    // 1.�Ӹ�λ�����λ�洢��vector��
    vector<int>nums;
    while (n > 0 ) 
    {
        nums.push_back(n % 10);
        n = n / 10;
    }
    // 2.��λ����λ�Ƚ�
    for (int i = 0; i < nums.size() - 1; i++) 
    {
        if (nums[i] < nums[i + 1]) 
        {
            nums[i] = 9;
            nums[i + 1] = nums[i + 1] - 1;
        }
    }

    // 3.��λ����λ�Ƚ�
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

// ������Ʊ�����ʱ����������
int maxProfitWithServiceCharge(vector<int>& prices, int fee) {
    int result = 0;
    int minPrice = prices[0];
    for (int i = 1; i < prices.size(); i++) 
    {
        //�൱������
        if (prices[i] < minPrice) minPrice = prices[i];

        // ��������
        if (prices[i] >= minPrice && prices[i] <= minPrice + fee) continue;

        // �൱���������������һ������������������
        if (prices[i] > minPrice + fee) 
        {
            result += prices[i] - minPrice - fee;
            // ��ؼ���һ�������������ȼ۵���С�ɱ�
            // �������Ϊ�������������´������Ƿ���������ռ�
            minPrice = prices[i] - fee;
        }
    }
    return result;
}

// ��ض�����
int minCameraCover(TreeNode* root) {
    return 0;
}



//------------------ ���ݲ��� ---------------------------
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


//------------------ ������ ---------------------------
int main(int argc, char **argv) {
    
    // ����һ��ȡ��
    //testGreed::test_findContentChildren();                                      // 455. �ַ�����
    //testGreed::test_wiggleMaxLength();                                          // 376. �ڶ�����
    //testGreed::test_maxSubArray();                                              // 53. ����������
    //testGreed::test_maxProfit();                                                // 122. ������Ʊ�����ʱ�� II
    //testGreed::test_canJump();                                                  // 55. ��Ծ��Ϸ
    //testGreed::test_jump();                                                     // 45. ��Ծ��Ϸ II
    //testGreed::test_largestSumAfterKNegations();                                // 1005. K ��ȡ������󻯵������
    //testGreed::test_canCompleteCircuit();                                       // 134. ����վ

    // ���Ͷ�������ά������
    //testGreed::test_candy();                                                    // 135. �ַ��ǹ�
    //testGreed::test_lemonadeChange();                                           // 860.����ˮ����
    //testGreed::test_reconstructQueue();                                         // 406. ��������ؽ�����
    //testGreed::test_findMinArrowShots();                                        // 452. �����������ļ���������
    //testGreed::test_eraseOverlapIntervals();                                    // 435. ���ص�����
    //testGreed::test_partitionLabels();                                          // 763. ������ĸ����
    //testGreed::test_merge();                                                    // 56. �ϲ�����
    //testGreed::test_monotoneIncreasingDigits();                                 // 738. �������������֣�����135. �ַ��ǹ���
    
    //������
    //testGreed::test_maxProfitWithServiceCharge();                               // 714. ������Ʊ�����ʱ���������ѣ���������¼�𰸣�
    //testGreed::test_minCameraCover();                                           // 968.��ض�����(delay)

    system("pause");
}
