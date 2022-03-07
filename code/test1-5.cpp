//---------------------------------------------------
using namespace std;

//------------------ LeetCode Test ---------------------------
//------------------ From Array To StackAndQueue--------------
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

// LC 链表定义
struct ListNode {
    int val;
    ListNode *next;
    ListNode() :val(0), next(nullptr) {}
    ListNode(int x) :val(x), next(nullptr) {}
    ListNode(int x, ListNode *m_next) :val(x), next(m_next) {}
};

int removeElement(vector<int>& nums, int val) {
    int slowIndex = 0;
    for (int fastIndex = 0; fastIndex < nums.size(); ++fastIndex) {
        if (nums[fastIndex] != val) {
            nums[slowIndex++] = nums[fastIndex];
        }
    }
    return slowIndex;
}

int removeDuplicates(vector<int>& nums) {
    int fastPtr = 1, slowPtr = 0;

    if (nums.size() == 0)
    {
        return 0;
    }
    
    while (fastPtr < nums.size())
    {
        if (nums[fastPtr] != nums[slowPtr]) {
            slowPtr++;
            nums[slowPtr] = nums[fastPtr];
        }
        fastPtr++;
    }
    return (slowPtr + 1);
}

void moveZeroes(vector<int>& nums){
    
    int slowPtr = 0;

    for (int fastPtr = 0; fastPtr < nums.size(); fastPtr++) {
        if (nums[fastPtr] != 0) {
            nums[slowPtr] = nums[fastPtr];
            slowPtr++;
        }
    }

    for (;slowPtr< nums.size();) {
        nums[slowPtr++] = 0;
    }
}

bool backspaceCompare(string s, string t){
    int i, bsCount;

    // 指针从后往前来
    for (i = s.size() - 1, bsCount = 0; i >= 0; i--) {
        if (s[i] == '#') {
            bsCount--;
            s.erase(i, 1);
            continue;
        }

        if (bsCount < 0) {
            bsCount++;
            s.erase(i, 1);
        }
    }

    for (i = t.size() - 1, bsCount = 0; i >= 0; i--) {
        if (t[i] == '#') {
            bsCount--;
            t.erase(i, 1);
            continue;
        }

        if (bsCount < 0) {
            bsCount++;
            t.erase(i, 1);
        }
    }

    return (s == t) ? true : false;
}

vector<int> sortedSquares(vector<int>& nums) {
    int i = 0;
    int j = 0;
    int k = nums.size() - 1;
    vector<int> result(nums);

    for (j = k ;i <= j;)
    {
        if (nums[i] * nums[i] > nums[j] * nums[j]) {
            result[k--] = nums[i] * nums[i];
            i++;
        }
        else {
            result[k--] = nums[j] * nums[j];
            j--;
        }
    }
    return result;
}

int minSubArrayLen(int target, vector<int>& nums) {
    int minLen  = INT32_MAX;
    int result  = 0;
    int sums    = 0;
    int i       = 0;
    int j       = 0;
    
    for (; j <= nums.size();) {
        if (sums >= target) {
            minLen = minLen < (j - i) ? minLen : (j - i);
            sums -= nums[i++];
            // 只有存在满足 >= target的条件才会修改result
            result = minLen;
            continue;
        }
        else if (j == nums.size()) {
            break;
        }
        sums += nums[j++];
    }
    return result;
}

int minSubArrayLen2(int target, vector<int>& nums) {
    int minLen = INT32_MAX;
    int fastIndex = 0, slowIndex = 0;
    int sum = nums[0];

    while (true) {

        while (sum >= target) {
            sum -= nums[slowIndex];
            minLen = (fastIndex - slowIndex + 1) > minLen ? minLen : (fastIndex - slowIndex + 1);
            slowIndex++;
        }

        if (fastIndex < nums.size() - 1) {
            fastIndex++;
            sum += nums[fastIndex];
        }
        else if (sum < target)
        {
            break;
        }
    }

    return (minLen == INT32_MAX) ? 0 : minLen;
}

int totalFruit(vector<int>& fruits) {

    int maxNum = 0, existTypeNum = 0;
    int fastFruitId = -1, slowFruitId = -1;
    int fastIndex = 0, slowIndex = 0;

    while(fastIndex < fruits.size()) {

        if (fruits[fastIndex] != fastFruitId && fruits[fastIndex] != slowFruitId) {

            if (existTypeNum < 2) {
                slowFruitId = fastFruitId;
                existTypeNum++;
            }
            else
            {
                // // 滑窗要连续，不能直接赋值为fastFruitId
                slowFruitId = fruits[fastIndex - 1];
                // 慢指针要放在slowFruitId最左侧
                slowIndex = fastIndex - 1;
                while (slowIndex >= 0) {
                    if (fruits[slowIndex] != slowFruitId) {
                        slowIndex++;
                        break;
                    }
                    slowIndex--;
                }
            }
            fastFruitId = fruits[fastIndex];
        }
        
        maxNum = maxNum >(fastIndex - slowIndex + 1) ? maxNum : (fastIndex - slowIndex + 1);
        fastIndex++;
    }

    return  maxNum;
}

string minWindow(string s, string t) {
    string ans;

    return ans;
}

vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> res(n, vector<int>(n, 0)); // 使用vector创建n*n的二维数组
    int startX = 0, startY = 0; // 每循环一圈的起始位置
    int loop = n / 2;           // 每个圈循环几次。n为奇数/偶数分别处理
    int mid = n / 2;            // 矩阵中间位置，n=1 (0,0) n=3 (1,1) n=5 (2,2)
    int count = 1;              // 给矩阵中每个空格赋值
    int offset = 1;             // 每圈循环，要控制的每条边遍历长度
    int i, j;

    int lenEveryLoop = n - 1;
    
    while (loop--) {
        i = startX;
        j = startY;

        // 模拟一圈，左闭右开
        // 上行
        for (j = startY; j < lenEveryLoop; j++){
            res[startX][j] = count++;
        }
        // 右列
        for (i = startX; i < lenEveryLoop; i++) {
            res[i][j] = count++;
        }
        // 下行
        for (; j > startY; j--) {
            res[i][j] = count++;
        }
        // 左列
        for (; i > startX; i--) {
            res[i][j] = count++;
        }

        // 每圈结束，起始位置变化
        startX++;
        startY++;
        // 每一圈要控制边长
        offset += 2;

        lenEveryLoop -= 1;
    }

    // n为奇数，矩阵最中间位置赋值
    if (n % 2) {
        res[mid][mid] = count;
    }

    return res;
}

ListNode* removeElements(ListNode* head, int val) {

    ListNode* dummyHead = new ListNode(0);
    dummyHead->next = head;
    ListNode* cur = dummyHead;
    while (cur->next != nullptr) {
        if (cur->next->val == val) {
            ListNode* tmp = cur->next;
            cur->next = cur->next->next;
            delete tmp;
        }
        else {
            cur = cur->next;
        }
    }
    head = dummyHead->next;
    delete dummyHead;
    return head;
}

class MyLinkedList {
public:
    MyLinkedList() {
        // 
        m_dummyHead = new ListNode(0);
        m_size = 0;
    }

    int get(int index) {
        if ((index > (m_size - 1)) || (index < 0)) {
            return -1;
        }

        ListNode* cur = m_dummyHead;

        while (index > 0) {
            cur = cur->next;
            index--;
        }
        return cur->val;
    }

    void addAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        if (m_size != 0) {
            newNode->next = m_dummyHead;
        }
        m_dummyHead = newNode;
        m_size++;
    }

    void addAtTail(int val) {

        ListNode *newNode = new ListNode(val);
        ListNode *cur = m_dummyHead;

        while (cur->next!= nullptr)
        {
            cur = cur->next;
        }

        if (m_size == 0) {
            m_dummyHead = newNode;
        }
        else {
            cur->next = newNode;
        }
        m_size++;
    }

    void addAtIndex(int index, int val) {

        ListNode *newNode = new ListNode(val);
        ListNode *beforeNode = m_dummyHead;
        ListNode *afterNode = beforeNode;

        while (index > 1) {
            beforeNode = beforeNode->next;
            index--;
        }
        afterNode = beforeNode->next;

        if (index < m_size && index >= 0) {
            beforeNode->next = newNode;
            newNode->next = afterNode;
            m_size++;
        }
        else if (index == m_size) {
            addAtTail(val);
        }
        else if(index <0 ) {
            addAtHead(val);
        }
    }

    void deleteAtIndex(int index) {
        ListNode *curNode = m_dummyHead;
        ListNode *dstNode;

        if ((index < m_size) &&  (index >= 0)) {

            if (index == 0) {
                dstNode = m_dummyHead;
                m_dummyHead = m_dummyHead->next;
            }
            else {
                while (index > 1) {
                    curNode = curNode->next;
                    index--;
                }
                dstNode = curNode->next;

                if (dstNode->next == nullptr) {
                    curNode->next = nullptr;
                }
            }
            delete dstNode;
            m_size--;
        }
    }
private:
    int m_size;
    ListNode *m_dummyHead;
};

ListNode* reverseList(ListNode* head) {
    
    ListNode *pre = nullptr;
    ListNode *tmp;
    ListNode *cur = head;

    while (cur) {
        tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }

    return pre;
}

ListNode* reverse(ListNode* pre, ListNode* cur) {
    if (cur == nullptr) return pre;
    ListNode* tmp = cur->next;
    cur->next = pre;
    return reverse(cur, tmp);
}

// 将上面reverseList写成递归，前序递归
ListNode* reverseList1(ListNode* head) {
    return reverse(nullptr, head);
}

// 从后往前，后序递归
ListNode* reverseList2(ListNode* head) {
    if (head == nullptr) return nullptr;
    if (head->next == nullptr) return head;

    ListNode *last = reverseList2(head->next);

    head->next->next = head;
    head->next = nullptr;

    return last;
}

ListNode* swapPairs(ListNode* head) {

    ListNode* dummyNode = new ListNode(0, head);
    ListNode* cur = dummyNode;

    while (cur->next != nullptr && cur->next->next != nullptr) {
        ListNode* tmp = cur->next;
        ListNode* tmp1 = cur->next->next->next;

        cur->next = cur->next->next;    // 步骤一
        cur->next->next = tmp;          // 步骤二
        cur->next->next->next = tmp1;   // 步骤三

        cur = cur->next->next;
    }
    return dummyNode->next;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    
    // 虚拟头节点
    ListNode* dummyNode = new ListNode(0, head);
    ListNode* cur = dummyNode;
    ListNode* slow = dummyNode;     // slow节点的next指向 倒数第n个点 即slow本身是待删除节点的上一个节点
    int interval = n;

    //双指针
    while (cur->next != nullptr) {
        cur = cur->next;
        if ( interval > 0) {
            interval--;
            continue;
        }
        slow = slow->next;
    }

    ListNode *dst = slow->next;
    slow->next = dst->next;
    delete dst;

    return dummyNode->next;
}

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {

    ListNode* nodeA = headA;
    ListNode* nodeB = headB;
    int lenA = 0, lenB = 0, diff = 0;

    while (nodeA != nullptr) {
        lenA++;
        nodeA = nodeA->next;
    }
    while (nodeB != nullptr) {
        lenB++;
        nodeB = nodeB->next;
    }

    if (lenA > lenB) {
        diff = lenA - lenB;
        nodeA = headA;
        nodeB = headB;
    }
    else {
        diff = lenB - lenA;
        nodeA = headB;
        nodeB = headA;
    }

    while (diff > 0) {
        nodeA = nodeA->next;
        diff--;
    }
    
    while (nodeA != nullptr && nodeA != nodeB) {
        nodeA = nodeA->next;
        nodeB = nodeB->next;
    }
    return nodeA;
}

ListNode *detectCycle(ListNode *head) {

    ListNode* fastNode = head;
    ListNode* slowNode = head;

    // 单节点链表或空表
    if (head == nullptr) {
        return nullptr;
    }
    else if (head->next == nullptr) {
        return nullptr;
    }

    // 首先判断是否闭环
    // 快: 2步 慢: 1步  间隔1步，若有环 必是快追上慢
    do {
        fastNode = fastNode->next->next;
        slowNode = slowNode->next;
    } while (fastNode != slowNode && fastNode != nullptr && fastNode->next != nullptr);

    if(fastNode == nullptr || fastNode->next == nullptr)
    {
        return nullptr;
    }

    // x = (n-1)*(y+z) + z;
    // 这会儿fastNode必然是在圈内了
    ListNode* index1 = fastNode;
    ListNode* index2 = head;

    while (index1 != index2) {
        index1 = index1->next;
        index2 = index2->next;
    }
    return index2;
}

bool isAnagram(string s, string t) {
    int i = 0;
    int result[26] = { 0 };

    for (i = 0; i < s.size(); i++) {
        result[s[i] - 'a']++;
    }
    for (i = 0; i < t.size(); i++) {
        result[t[i] - 'a']--;
    }
    for (i = 0; i < 26; i++) {
        if (result[i] != 0) {
            return false;
        }
    }
    return true;
}

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {

    unordered_set<int> result_set;
    unordered_set<int> nums1Set(nums1.begin(), nums1.end());

    for (int num : nums2) {
        if (nums1Set.find(num) != nums1Set.end()) {
            result_set.insert(num);
        }
    }
return vector<int>(result_set.begin(), result_set.end());
}

int getSum(int n) {
    int sum = 0;
    while (n) {
        sum += (n % 10)*(n % 10);
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {

    unordered_set<int> set;

    while (1) {
        int sum = getSum(n);

        // 快乐数的定义条件
        if (sum == 1) {
            return true;
        }

        // 隐含退出条件，sum重复出现则会循环
        if (set.find(sum) != set.end()) {
            return false;
        }
        else {
            set.insert(sum);
        }

        n = sum;
    }
}

vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> ans;
    unordered_map<int, int>map;
    for (int i = 0; i < nums.size(); i++) {
        auto iter = map.find(target - nums[i]);
        if (iter != map.end()) {
            ans.push_back(iter->second);
            ans.push_back(i);
            return ans;
        }
        map.insert(pair<int, int>(nums[i], i));
    }
    return{};
}

int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    int result = 0;
    unordered_map<int, int> umap;

    // 直接当成数组的下标来用
    for (int i : nums1) {
        for (int j : nums2) {
            umap[i + j]++;
        }
    }

    for (int i : nums3) {
        for (int j : nums4) {
            if (umap.find(0 - i - j) != umap.end())
                // 这里也是 反向算key
                result += umap[0 - i - j];
        }
    }

    return result;
}

bool canConstruct(string ransomNote, string magazine) {
    unordered_map<int, int> magazineMap;

    for (auto iter : magazine) {
        magazineMap[iter - 'a']++;
    }

    for (auto iter : ransomNote) {
        if (magazineMap.find(iter - 'a') == magazineMap.end()) {
            return false;
        }
        else
        {
            magazineMap[iter - 'a']--;
            if (magazineMap[iter - 'a'] < 0) {
                return false;
            }
        }
    }
    return true;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result = {};
    int leftPtr = 0, rightPtr = 0, sum = 0;
    sort(nums.begin(), nums.end());

    // 特殊情况，直接return
    if (nums.size() < 3 || nums[0] > 0) {
        return result;
    }

    // 理解成，固定住i，双指针找(nums[leftPtr] + nums[rightPtr]) = -nums[i]
    for (int i = 0; i < nums.size(); i++){

        // i去重
        if ((i > 0) && (nums[i] == nums[i - 1])) {
            continue;
        }

        leftPtr = i + 1;
        rightPtr = nums.size() - 1;
        while (leftPtr < rightPtr) {
            sum = nums[i] + nums[leftPtr] + nums[rightPtr];
            if (sum > 0) {
                rightPtr--;
            }
            else if (sum < 0) {
                leftPtr++;
            }
            else {
                result.push_back({ nums[i], nums[leftPtr], nums[rightPtr] });
                
                while ((leftPtr < rightPtr) && (nums[rightPtr - 1] == nums[rightPtr])) { rightPtr--; }
                while ((leftPtr < rightPtr) && (nums[leftPtr + 1] == nums[leftPtr]))  { leftPtr++; }

                rightPtr--;
                leftPtr++;
            }
        }
    }
    return result;
}

vector<vector<int>> fourSum(vector<int>& nums, int target) {

    vector<vector<int>> result = {};
    int leftPtr = 0, rightPtr = 0;
    long sum = 0;

    // 排序
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++) {
        // 剔除i重复的逻辑
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        for (int j = i + 1; j < nums.size(); j++) {
            // 剔除j重复的逻辑
            if ((j > (i + 1)) && nums[j] == nums[j - 1]) {
                continue;
            }

            leftPtr = j + 1;
            rightPtr = nums.size() - 1;
            sum = nums[i] + nums[j];

            while (rightPtr > leftPtr) {

                if (sum > (target - nums[leftPtr] - nums[rightPtr])) {
                    rightPtr--;
                }
                else if (sum < (target - nums[leftPtr] - nums[rightPtr])) {
                    leftPtr++;
                }
                else {
                    result.push_back(vector<int>{nums[i], nums[j], nums[leftPtr], nums[rightPtr]});

                    while ((leftPtr < rightPtr) && nums[rightPtr - 1] == nums[rightPtr]) rightPtr--;    // 右指针去重逻辑
                    while ((leftPtr < rightPtr) && nums[leftPtr + 1] == nums[leftPtr])  leftPtr++;      // 左指针去重逻辑

                    rightPtr--;
                    leftPtr++;
                }
            }
        }
    }
    return result;
}

void reverseString(vector<char>& s) {
    for (int i = 0; i <(s.size() / 2); i++) {   // 或者直接reverse(s.begin(), s.end());
        swap(s[i], s[s.size() - i - 1]);
    }
}

string reverseStr(string s, int k) {

    for (int i = 0; i < s.size(); i += 2 * k) {
        if ((i + k) > s.size()) {
            reverse(s.begin() + i, s.end());
        }
        else
        {
            reverse(s.begin() + i, s.begin() + i + k);
        }
    }
    return s;
}

string replaceSpace(string s) {
    int spaceNum = 0;
    // 找空格数量
    for (auto iter : s) {
        if (iter == ' ') {
            spaceNum++;
        }
    }

    //定义慢指针
    int slowPtr = s.size() - 1;
    // 扩充大小
    s.resize(s.size() + spaceNum * 2);
    // 定义快指针
    int fastPtr = s.size()- 1;

    
    while(slowPtr >= 0){
        if (s[slowPtr] == ' ') {
            slowPtr--;
            s[fastPtr--] = '0';
            s[fastPtr--] = '2';
            s[fastPtr--] = '%';
        }
        else
        {
            s[fastPtr--] = s[slowPtr--];
        }
    }
    return s;
}

string reverseWords(string s) {
    int slowPtr = 0;
    int fastPtr = 0;
    int i = 0, j = 0;

    // 去除头部空格符
    while (fastPtr < s.size() && s[fastPtr] == ' ') {
        fastPtr++;
    }
    // 去除多余的空格符
    for (; fastPtr < s.size(); fastPtr++) {
        
        if ( fastPtr > 0 && s[fastPtr] == ' ' && s[fastPtr - 1] == ' ') {
            continue;
        }

        s[slowPtr++] = s[fastPtr];
    }
    // 去除尾部空格
    while (s[slowPtr - 1] == ' ') {
        slowPtr--;
    }

    s.resize(slowPtr);
    // 逆转所有
    reverse(s.begin(), s.end());
    // 逆转单个单词
    for (i = 0, j = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            reverse(s.begin() + j, s.begin() + i);
            j = i + 1;
        }
    }
    reverse(s.begin() + j, s.end());

    return s;
}

string reverseLeftWords(string s, int n) {
    reverse(s.begin(), s.end());
    reverse(s.begin(), s.end() - n);
    reverse(s.end() - n, s.end());

    return s;
}

/*****************
下标   0 1 2 3 4 5 6 7 8 9 10 11 
       A B A B A A A B A B A  A
值     0 0 1 2 3 1 1 2 3 4 5  6
******************/
void getNext(vector<int>& next, const string &s) {

    // 1.初始化，包括i=1,j=0的操作
    next.push_back(0);
    for (int i = 1, j = 0; i < s.size(); i++) {
        // 2.前后缀不相同
        while (j > 0 && s[i] != s[j]) {
            j = next[j - 1];            // 最难以理解的一步
        }
        // 3.前后缀相同
        if (s[i] == s[j]) {
            j++;
        }
        // 4.next数据更新
        next.push_back(j);
    }
}

int strStr(string haystack, string needle) {

    if (needle.size() == 0) {
        return 0;
    }
    vector<int> next;
    getNext(next, needle);

    int j = 0;

    // 这里和getNext中不一样，是从i = 0开始的
    for (int i = 0; i < haystack.size(); i++) {
        while (j > 0 && haystack[i] != needle[j]) {
            j = next[j - 1];
        }

        if (haystack[i] == needle[j]) {
            j++;
        }

        // 退出条件
        if (j == needle.size()) {
            return (i - needle.size() + 1);
        }
    }
    return -1;
}

bool repeatedSubstringPattern(string s) {

    if (s.size() == 0) {
        return false;
    }

    // 先生成next数组
    vector<int> next;
    getNext(next, s);

    // 已知/总结出来的规律
    int len = s.size();
    if ((next[len - 1] != 0) && (len % (len - next[len - 1]) == 0)) {
        return true;
    }
    return false;


}

class MyQueue {
private:
    stack<int> stIn;
    stack<int> stOut;
public:
    MyQueue() {

    }

    void push(int x) {
        stIn.push(x);
    }

    int pop() {
        if (stOut.empty()) {
            while (!stIn.empty()) {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        stOut.pop();
        return result;
    }

    int peek() {
        int res = this->pop();
        stOut.push(res);
        return res;
    }

    bool empty() {
        return stIn.empty() && stOut.empty();
    }
};

class MyStack {
    queue<int> queIn;
    queue<int> queOut;

public:
    MyStack() {

    }

    void push(int x) {
        queIn.push(x);
    }

    int pop() {
        int tempVal = 0;
        
        if (queIn.size() <=0 ) {
            return 0;
        }

        // 留一个，返回出去
        while (queIn.size() > 1) {
            queOut.push(queIn.front());
            queIn.pop();
        }
        tempVal = queIn.front();
        queIn.pop();

        // 塞回queIn中
        while (queOut.size() > 0) {
            queIn.push(queOut.front());
            queOut.pop();
        }

        return tempVal;
    }

    int top() {
        int num = this->pop();
        queIn.push(num);
        return num;
    }

    bool empty() {
        return queIn.empty();
    }
};

// 优化版本，只用一个queue实现
class MyStack2 {
    queue<int> queIn;

public:
    MyStack2() {}
    
    void push(int x) { queIn.push(x); }

    int pop() {
        
        int stackSize = queIn.size();
        int tempNum = 0;

        // 移动size - 1次
        while (stackSize > 1) {
            tempNum = queIn.front();
            queIn.pop();
            queIn.push(tempNum);
            stackSize--;
        }
        tempNum = queIn.front();
        queIn.pop();
        return tempNum;
    }

    int top() { return queIn.back(); }

    bool empty() { return queIn.empty(); }
};

bool isValid(string s) {
    stack<int> st;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') st.push(')');
         else if (s[i] == '{') st.push('}');
         else if (s[i] == '[') st.push(']');
         // 右侧符多了 || 不匹配 
         else if (st.empty() || s[i] != st.top()) return false;
         else st.pop(); // 正常的场景，当前字符与栈顶字符相同，pop出去
    }
    // 若为空，则正常，返回true; 否则左侧符多了，返回false
    return st.empty();
}

// 栈这种容器非常适用“对称匹配”问题
string removeDuplicates(string s) {
    string result;
    stack<char> st;
    for (int i = 0; i < s.size(); i++) {
        if (st.empty() || s[i] != st.top()) {
            st.push(s[i]);
        }
        else {
            st.pop();
        }
    }

    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    reverse(result.begin(), result.end());

    return  result;
}

// 优化版本，避免申请一个stack。
string removeDuplicates2(string s) {
    string result;
    for (auto iter : s) {
        if (result.empty() || result.back() != iter) {
            result.push_back(iter);
        }
        else {
            result.pop_back();
        }
    }
    return result;
}

int evalRPN(vector<string>& tokens) {
    stack<int> num;
    int topNum1 = 0;
    int topNum2 = 0;
    int result = 0;
    
    if (tokens.size() == 1) {
        return atoi(tokens[0].c_str());
    }

    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "+") {
            topNum1 = num.top();
            num.pop();
            topNum2 = num.top();
            num.pop();
            result = topNum2 + topNum1;
            num.push(result);
        }
        else if (tokens[i] == "-") {
            topNum1 = num.top();
            num.pop();
            topNum2 = num.top();
            num.pop();
            result = topNum2 - topNum1;
            num.push(result);
        }
        else if (tokens[i] == "*") {
            topNum1 = num.top();
            num.pop();
            topNum2 = num.top();
            num.pop();
            result = topNum2 * topNum1;
            num.push(result);
        }
        else if (tokens[i] == "/") {
            topNum1 = num.top();
            num.pop();
            topNum2 = num.top();
            num.pop();
            result = topNum2 / topNum1;
            num.push(result);
        }
        else
        {
            //num.push(stoi(tokens[i]));        // 当前版本VS不支持全部C++11但是可以直接这么用
            num.push(atoi(tokens[i].c_str()));
        }
    }
    return result;
}

// 为maxSlidingWindow设计的类
class MyQueue2 {//单调队列(从大到小) 
public:
    deque<int> que; // 使用deque实现单调队列

    // 每次弹出的数值是单调队列中最前面（值最大）元素，则弹出
    void pop(int value) {
        if (!que.empty() && value == que.front()) {
            que.pop_front();
        }
    }

    // 保证单调队列的单调性
    void push(int value) {
        while (!que.empty() && value > que.back()) {
            que.pop_back();
        }
        que.push_back(value);
    }

    // 当前单调队列最大值（返回向量的元素）
    int front() {
        return que.front();
    }
};

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    MyQueue2 que;
    vector<int> result;

    for (int i = 0; i < k; i++) {
        que.push(nums[i]);
    }
    result.push_back(que.front());  // 第一次前k元素最大值

    for (int i = k; i < nums.size(); i++) {
        que.pop(nums[i - k]);
        que.push(nums[i]);
        result.push_back(que.front());
    }

    return result;
}

struct topKFcomparison {
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
        return lhs.second > rhs.second;
    }
};

vector<int> topKFrequent(vector<int>& nums, int k) {

    unordered_map<int, int> map;
    // 先统计各元素出现的频率
    for (int i = 0; i < nums.size(); i++) {
        map[nums[i]]++;
    }

    //对各元素频率排序，定义大小为K的小顶堆
    priority_queue<pair<int, int>, vector<pair<int, int>>, topKFcomparison> pri_que;

    // 遍历map，维护大小为k的小顶堆
    for (auto iter : map) {
        pri_que.push(iter);
        if (pri_que.size() > k) {
            pri_que.pop();
        }
    }

    vector<int> result(k);
    for (int i = k - 1; i >= 0; i--) {
        result[i] = pri_que.top().first;
        pri_que.pop();
    }
    return result;
}

bool topKFcomparison2(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return lhs.second < rhs.second;
}

// ！！！注意这里是错误的写法！！！
// sequence container不能使用sort，需要先把map结构转为vector
vector<int> topKFrequent2(vector<int>& nums, int k) {
    vector<int> result;
    unordered_map<int, int> map;

    // 先统计各元素出现的频率
    for (int i = 0; i < nums.size(); i++) {
        map[nums[i]]++;
    }

    // 依据频率快排map，频率由大到小
    sort(map.begin(), map.end(), topKFcomparison2);

    // 取出前k个
    for (int i = 0; i < k; i++) {
        result[i] = map[i];
    }
    return result;
}

//------------------ 数组测试 ---------------------------
#include <iostream>
#include <string>
namespace testArray
{
    void test_removeElement() {
        
        cout << "test_removeElement: " << endl;

        vector<int> nums = { 0,1,2,2,3,0,4,2 };
        int val = 2;
        int len = 0;

        len = removeElement(nums, val);

        for (int i = 0; i < len; i++) {
            cout << nums[i] << " "; 
        }
        cout << endl;
    }

    void test_removeDuplicates() {

        cout << "test_removeDuplicates: " << endl;

        vector<int> nums = { 0,0,1,1,1,2,2,3,3,4 };

        int len = removeDuplicates(nums);

        for (int i = 0; i < len; i++) {
            cout << nums[i] << " ";
        }
        cout << endl;
    }

    void test_moveZeros(){

        cout << "test_moveZeros: " << endl;

        vector<int> nums = { 0,1,0,3,12 };

        moveZeroes(nums);

        for (int i = 0; i < nums.size(); i++) {
            cout << nums[i] << " ";
        }
        cout << endl;
    }

    void test_backspaceCompare() {

        cout << "test_backspaceCompare: " << endl;

        string s = "a##c";
        string t = "#a#c";
        
        bool ans = backspaceCompare(s, t);

        cout << "ans: " << ans << endl;

    }

    void test_sortedSquares() {

        cout << "test_sortedSquares: " << endl;

        vector<int> nums = { -7,-3,2,3,11 };
        vector<int> result;
        result = sortedSquares(nums);

        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    }

    void test_minSubArrayLen() {

        cout << "test_minSubArrayLen: " << endl;

        int minLen = 0;
        int target = 7;/*int target = 4;*//*int target = 10;*/
        vector<int> nums = { 2,3,1,2,4,3 };/*vector<int> nums = { 1,4,4 };*//*vector<int> nums = { 1,1,1,1,1,1,1,1 };*/

        minLen = minSubArrayLen(target, nums);

        cout << minLen;
    }

    void test_totalFruit() {

        cout << "test_minSubArrayLen: " << endl;

        vector<int> fruits = { 1,2,1 };
        
        int ans = totalFruit(fruits);

        cout << ans << endl;
    }

    void test_minWindow() {

        cout << "test_minWindow: " << endl;

        string s = "ADOBECODEBANC";
        string t = "ABC";

        string minSubAns = minWindow(s, t);

        cout << minSubAns << endl;

    }

    void test_generateMatrix() {

        cout << "test_generateMatrix: " << endl;
        
        int n = 7;
        vector<vector<int>> res;

        res = generateMatrix(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << res[i][j] << " ";
            }
            cout << endl;
        }
    }
}

//------------------ 链表测试 ---------------------------
#include <iostream>
#include <string>
#include <list>
#include <algorithm> 
namespace testListNode
{
    // 创建ListNode
    ListNode* createList(vector<int> vec_list) {
        int         num     = 0;
        ListNode*   pNode   = new ListNode(1);
        ListNode*   pHead   = pNode;

        for (int i = 0; i < vec_list.size(); i++) {
            ListNode *pTemp = new ListNode(vec_list[i]);
            pNode->next = pTemp;
            pNode = pTemp;
        }
        cout << "Creat List End\n";
        return pHead->next;
    }

    // 释放ListNode内存
    void deleteList(ListNode* pNode) {
        while (pNode->next != nullptr) {
            deleteList(pNode->next);
            break;
        }
        delete pNode;
    }

    // 打印ListNode内容
    void printList(ListNode* pNode) {
        ListNode* pTraverse = pNode;
        if (!pTraverse) {
            return;
        }
        while (pTraverse) {
            cout << pTraverse->val << " ";
            pTraverse = pTraverse->next;
        }
        cout << endl;
    }

    void test_removeElements() {

        cout << "test_removeElements: " << endl;

        vector<int> vec_list = { 2,6,3,4,5,6 };
        ListNode* pNode = createList(vec_list);
        int val = 6;
        
        cout << "before removeElements:\n";
        printList(pNode);

        ListNode* ansNode = removeElements(pNode, val);

        cout << "after removeElements:\n";
        printList(ansNode);

        deleteList(pNode);
    }

    void test_MyLinkedList() {

        MyLinkedList *linkedList = new MyLinkedList();

        linkedList->addAtHead(1);
        linkedList->addAtTail(3);
        linkedList->addAtIndex(2, 2);   //链表变为1-> 3-> 2
        int ans = linkedList->get(1);   //返回2
        linkedList->deleteAtIndex(2);   //现在链表是1-> 3
        ans = linkedList->get(1);             //返回3
    }

    void test_reverseList() {

        cout << "test_reverseList: " << endl;

        vector<int> vec_list = { 1,2,3,4,5 };
        ListNode* pNode = createList(vec_list);

        cout << "before reverseList:\n";
        printList(pNode);

        ListNode* ansNode = reverseList1(pNode);

        cout << "after reverseList:\n";
        printList(ansNode);

        deleteList(ansNode);
    }

    void test_swapPairs() {

        cout << "test_swapPairs: " << endl;

        vector<int> vec_list = { 1 };
        ListNode* pNode = createList(vec_list);
        cout << "before swapPairs:\n";
        printList(pNode);

        ListNode* ansNode = swapPairs(pNode);

        cout << "after swapPairs:\n";
        printList(ansNode);
        deleteList(pNode);
    }

    void test_removeNthFromEnd() {

        cout << "test_removeNthFromEnd: " << endl;

        vector<int> vec_list = { 1,2 };
        int n = 1;
        ListNode* pNode = createList(vec_list);
        cout << "before removeNthFromEnd:\n";
        printList(pNode);

        ListNode* ansNode = removeNthFromEnd(pNode, n);

        cout << "after removeNthFromEnd:\n";
        printList(ansNode);
        deleteList(pNode);
    }

    void test_getIntersectionNode() {

        cout << "test_getIntersectionNode: " << endl;
        vector<int> vec_list = { 8,4,5 };
        ListNode* pNode = createList(vec_list);
        vec_list = { 4, 1 };
        ListNode*  pNode1 = createList(vec_list);
        pNode1->next->next = pNode;
        vec_list = { 5, 0, 1 };
        ListNode* pNode2 = createList(vec_list);
        pNode2->next->next->next = pNode;

        cout << "pNode1:\n";
        printList(pNode1);
        cout << "pNode2:\n";
        printList(pNode2);

        ListNode *ansNode = getIntersectionNode(pNode1, pNode2);

        cout << "ansNode:\n";
        printList(ansNode);
    }

    void test_detectCycle() {

        cout << "test_detectCycle: " << endl;

        //vector<int> vec_list = { 3, 2, 0, -4 };
        vector<int> vec_list = { 1,2 };
        ListNode* pNode = createList(vec_list);
        printList(pNode);
        //pNode->next->next->next->next = pNode->next;

        ListNode* ansNode = detectCycle(pNode);

    }

}

//------------------ 哈希表测试 ---------------------------
#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<unordered_map>
namespace testHashCode {

    void test_isAnagram() {

        cout << "test_isAnagram" << endl;

        string s = "anagram";
        string t = "nagaram";

        bool ans = isAnagram(s, t);

        cout << ans << endl;
    }

    void test_intersection() {
        vector<int> nums1 = { 4,9,5 };
        vector<int> nums2 = { 9,4,9,8,4 };

        vector<int> ans;
        ans = intersection(nums1, nums2);

        for (const auto i :ans) {
            cout << i << " ";
        }
        cout << endl;
    }

    void test_isHappy() {

        cout << "test_isHappy" << endl;

        int val = 91;
        bool ans = isHappy(val);

        cout << ans << endl;
    }

    void test_twoSum() {

        cout << "test_twoSum" << endl;

        vector<int> nums = { 2,7,11,15 };
        int target = 9;

        vector<int> ans = twoSum(nums, target);

        for (const auto i : ans) {
            cout << i << " ";
        }
        cout << endl;
    }

    void test_fourSumCount() {
        cout << "test_fourSumCount" << endl;
        vector<int> nums1 = { 1,2 };
        vector<int> nums2 = { -2,-1 };
        vector<int> nums3 = { -1, 2 };
        vector<int> nums4 = { 0,2 };

        int result = fourSumCount(nums1, nums2, nums3, nums4);
        
        cout << result << endl;
    }

    void test_canConstruct() {

        cout << "test_canConstruct" << endl;

        string ransomNote = { "aa" };
        string magazine = { "aab" };

        bool result = canConstruct(ransomNote, magazine);

        cout << "result: " << result << endl;
    }

    void test_threeSum() {

        cout << "test_threeSum" << endl;
        vector<int> nums = { -1,0,1,2,-1,-4 };

        vector<vector<int>> result = threeSum(nums);

    }
    
    void test_fourSum() {
        vector<int> nums = { 1,0,-1,0,-2,2};
        int target = 0;

        vector<vector<int>> result = fourSum(nums, target);

        for (auto iter : result) {
            for (auto iter2 : iter) {
                cout << iter2 << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

//------------------ 字符串测试 ---------------------------
#include<iostream>
#include<string>
namespace testString {

    void test_reverseString() {
        cout << "test_reverseString" << endl;
        vector<char> s = { 'h', 'e', 'l', 'l', 'o' };

        reverseString(s);
        
        for (auto iter : s) {
            cout << iter << " ";
        }
        cout << endl;
    }

    void test_reverseStr() {
        string s = "abcdefg";
        int k = 2;

        string ans = reverseStr(s, k);

        for (auto iter : ans) {
            cout << iter;
        }
        cout << endl;
    }

    void test_replaceSpace() {

        cout << "test_replaceSpace" << endl;

        string s = "We are happy.";

        string ans = replaceSpace(s);

        cout << ans;
    }

    void test_reverseWord() {

        cout << "test_reverseWord" << endl;

        string s = " the sky  is blue  ";

        string result = reverseWords(s);
        cout << result;
    }

    void test_reverseLeftWords() {

        cout << "test_reverseLeftWords" << endl;

        string s = "lrloseumgh"; 
        int k = 6;

        string result = reverseLeftWords(s, k);
        cout << result << endl;
    }

    void test_strStr() {

        cout << "test_strStr:" << endl;

        string haystack = "hello";
        string needle = "ll";

        int result = strStr(haystack, needle);
        cout << result << endl;
    }

    void test_repeatedSubstringPattern() {

        cout << "test_repeatedSubstringPattern:" << endl;

        string s = "abcabcabcabc";
        bool result = repeatedSubstringPattern(s);

        cout << result << endl;
    }
}

//------------------ 栈与队列测试 ---------------------------
namespace testStackAndQueue {

    void test_geneMyQueue() {

        cout << "test_geneMyQueue" << endl;

        MyQueue *queue = new MyQueue();
        queue->push(1);
        queue->push(2);
        cout << queue->peek() <<endl;  // 返回 1
        cout << queue->pop() << endl;   // 返回 1
        cout << queue->empty() << endl; // 返回 false
    }

    void test_geneMyStack() {

        cout << "test_geneMyStack" << endl;

        // MyStack2是优化后只使用一个queIn的版本
        MyStack2 *myStack = new MyStack2();
        myStack->push(1);
        myStack->push(2);
        cout << myStack->top() << endl; // 返回 2
        cout << myStack->pop() << endl; // 返回 2
        cout << myStack->empty() << endl; // 返回 False
    }

    void test_isValid() {

        cout << "test_isValid" << endl;

        string s = "([)]";
        cout << isValid(s) << endl;
    }

    void test_removeDuplicates() {

        cout << "test_removeDuplicates" << endl;

        string s = "abbaca";
        //string result = removeDuplicates(s);
        string result = removeDuplicates2(s);
        cout << result <<endl;
    }

    void test_evalRPN() {

        cout << "test_evalRPN" << endl;

        vector<string> tokens = { "10","6","9","3","+","-11","*","/","*","17","+","5","+" };
        //vector<string> tokens = { "18" };
        int result = evalRPN(tokens);
        cout << result << endl;
    }

    void test_maxSlidingWindow() {

        cout << "test_maxSlidingWindow" << endl;

        vector<int> nums = { 1,3,-1,-3,5,3,6,7 };
        int k = 3;
        vector<int>  result= maxSlidingWindow(nums, k);

        for (auto iter : result) {
            cout << iter <<endl;
        }
    }

    void test_topKFrequent() {

        cout << "test_topKFrequent" << endl;

        vector<int> nums = { 1,1,1,2,2,3 };
        int k = 2;

        vector<int> result = topKFrequent(nums, k);
    }
}

//------------------ 主程序 ---------------------------
//int main(int argc, char **argv)
void test1_5()
{
    // 数组二 双指针
    //testArray::test_removeElement();                // 27. 移除元素
    //testArray::test_removeDuplicates();             // 26. 删除有序数组中的重复项
    //testArray::test_moveZeros();                    // 283. 移动零
    //testArray::test_backspaceCompare();             // 844. 比较含退格的字符串
    //testArray::test_sortedSquares();                // 977.有序数组的平方

    // 数组三 滑动窗口
    //testArray::test_minSubArrayLen();               // 209.长度最小的子数组
    //testArray::test_totalFruit();                   // 904. 水果成篮    (medium)
    //testArray::test_minWindow();                    // 76. 最小覆盖子串   (hard)delay

    // 数组四 代码操作
    //testArray::test_generateMatrix();               // 59.螺旋矩阵II

    // 链表
    //testListNode::test_removeElements();            // 203. 移除链表元素
    //testListNode::test_MyLinkedList();              // 707. 设计链表  (leetcode结果有问题)
    //testListNode::test_reverseList();               // 206.反转链表
    //testListNode::test_swapPairs();                 // 24. 两两交换链表中的节点
    //testListNode::test_removeNthFromEnd();          // 19. 删除链表的倒数第 N 个结点
    //testListNode::test_getIntersectionNode();       // 面试题 02.07.链表相交
    //testListNode::test_detectCycle();               // 142. 环形链表 II

    // 哈希表
    //testHashCode::test_isAnagram();                 // 242. 有效的字母异位词
    //testHashCode::test_intersection();              // 349. 两个数组的交集
    //testHashCode::test_isHappy();                   // 202. 快乐数
    //testHashCode::test_twoSum();                    // 1. 两数之和
    //testHashCode::test_fourSumCount();              // 454. 四数相加 II
    //testHashCode::test_canConstruct();              // 383. 赎金信
    //testHashCode::test_threeSum();                  // 15. 三数之和
    //testHashCode::test_fourSum();                   // 18. 四数之和
    
    // 字符串
    //testString::test_reverseString();               // 344.反转字符串
    //testString::test_reverseStr();                  // 541. 反转字符串II
    //testString::test_replaceSpace();                // 剑指Offer 05.替换空格
    //testString::test_reverseWord();                 // 151. 翻转字符串里的单词
    //testString::test_reverseLeftWords();            // 剑指 Offer 58 - II.左旋转字符串
    //testString::test_strStr();                      // 28. 实现 strStr()        hard级别了，生成next数组可再写一次
    //testString::test_repeatedSubstringPattern();    // 459.重复的子字符串

    // 栈与队列
    //testStackAndQueue::test_geneMyQueue();          // 232. 用栈实现队列
    //testStackAndQueue::test_geneMyStack();          // 225. 用队列实现栈
    //testStackAndQueue::test_isValid();              // 20. 有效的括号
    //testStackAndQueue::test_removeDuplicates();     // 1047. 删除字符串中的所有相邻重复项
    //testStackAndQueue::test_evalRPN();              // 150. 逆波兰表达式求值
    //testStackAndQueue::test_maxSlidingWindow();     // 239. 滑动窗口最大值    (hard)
    //testStackAndQueue::test_topKFrequent();         // 347. 前 K 个高频元素   (hard)

    system("pause");

}