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

// LC ������
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

    // ָ��Ӻ���ǰ��
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
            // ֻ�д������� >= target�������Ż��޸�result
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
                // // ����Ҫ����������ֱ�Ӹ�ֵΪfastFruitId
                slowFruitId = fruits[fastIndex - 1];
                // ��ָ��Ҫ����slowFruitId�����
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
    vector<vector<int>> res(n, vector<int>(n, 0)); // ʹ��vector����n*n�Ķ�ά����
    int startX = 0, startY = 0; // ÿѭ��һȦ����ʼλ��
    int loop = n / 2;           // ÿ��Ȧѭ�����Ρ�nΪ����/ż���ֱ���
    int mid = n / 2;            // �����м�λ�ã�n=1 (0,0) n=3 (1,1) n=5 (2,2)
    int count = 1;              // ��������ÿ���ո�ֵ
    int offset = 1;             // ÿȦѭ����Ҫ���Ƶ�ÿ���߱�������
    int i, j;

    int lenEveryLoop = n - 1;
    
    while (loop--) {
        i = startX;
        j = startY;

        // ģ��һȦ������ҿ�
        // ����
        for (j = startY; j < lenEveryLoop; j++){
            res[startX][j] = count++;
        }
        // ����
        for (i = startX; i < lenEveryLoop; i++) {
            res[i][j] = count++;
        }
        // ����
        for (; j > startY; j--) {
            res[i][j] = count++;
        }
        // ����
        for (; i > startX; i--) {
            res[i][j] = count++;
        }

        // ÿȦ��������ʼλ�ñ仯
        startX++;
        startY++;
        // ÿһȦҪ���Ʊ߳�
        offset += 2;

        lenEveryLoop -= 1;
    }

    // nΪ�������������м�λ�ø�ֵ
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

// ������reverseListд�ɵݹ飬ǰ��ݹ�
ListNode* reverseList1(ListNode* head) {
    return reverse(nullptr, head);
}

// �Ӻ���ǰ������ݹ�
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

        cur->next = cur->next->next;    // ����һ
        cur->next->next = tmp;          // �����
        cur->next->next->next = tmp1;   // ������

        cur = cur->next->next;
    }
    return dummyNode->next;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    
    // ����ͷ�ڵ�
    ListNode* dummyNode = new ListNode(0, head);
    ListNode* cur = dummyNode;
    ListNode* slow = dummyNode;     // slow�ڵ��nextָ�� ������n���� ��slow�����Ǵ�ɾ���ڵ����һ���ڵ�
    int interval = n;

    //˫ָ��
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

    // ���ڵ������ձ�
    if (head == nullptr) {
        return nullptr;
    }
    else if (head->next == nullptr) {
        return nullptr;
    }

    // �����ж��Ƿ�ջ�
    // ��: 2�� ��: 1��  ���1�������л� ���ǿ�׷����
    do {
        fastNode = fastNode->next->next;
        slowNode = slowNode->next;
    } while (fastNode != slowNode && fastNode != nullptr && fastNode->next != nullptr);

    if(fastNode == nullptr || fastNode->next == nullptr)
    {
        return nullptr;
    }

    // x = (n-1)*(y+z) + z;
    // ����fastNode��Ȼ����Ȧ����
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

        // �������Ķ�������
        if (sum == 1) {
            return true;
        }

        // �����˳�������sum�ظ��������ѭ��
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

    // ֱ�ӵ���������±�����
    for (int i : nums1) {
        for (int j : nums2) {
            umap[i + j]++;
        }
    }

    for (int i : nums3) {
        for (int j : nums4) {
            if (umap.find(0 - i - j) != umap.end())
                // ����Ҳ�� ������key
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

    // ���������ֱ��return
    if (nums.size() < 3 || nums[0] > 0) {
        return result;
    }

    // ���ɣ��̶�סi��˫ָ����(nums[leftPtr] + nums[rightPtr]) = -nums[i]
    for (int i = 0; i < nums.size(); i++){

        // iȥ��
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

    // ����
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++) {
        // �޳�i�ظ����߼�
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        for (int j = i + 1; j < nums.size(); j++) {
            // �޳�j�ظ����߼�
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

                    while ((leftPtr < rightPtr) && nums[rightPtr - 1] == nums[rightPtr]) rightPtr--;    // ��ָ��ȥ���߼�
                    while ((leftPtr < rightPtr) && nums[leftPtr + 1] == nums[leftPtr])  leftPtr++;      // ��ָ��ȥ���߼�

                    rightPtr--;
                    leftPtr++;
                }
            }
        }
    }
    return result;
}

void reverseString(vector<char>& s) {
    for (int i = 0; i <(s.size() / 2); i++) {   // ����ֱ��reverse(s.begin(), s.end());
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
    // �ҿո�����
    for (auto iter : s) {
        if (iter == ' ') {
            spaceNum++;
        }
    }

    //������ָ��
    int slowPtr = s.size() - 1;
    // �����С
    s.resize(s.size() + spaceNum * 2);
    // �����ָ��
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

    // ȥ��ͷ���ո��
    while (fastPtr < s.size() && s[fastPtr] == ' ') {
        fastPtr++;
    }
    // ȥ������Ŀո��
    for (; fastPtr < s.size(); fastPtr++) {
        
        if ( fastPtr > 0 && s[fastPtr] == ' ' && s[fastPtr - 1] == ' ') {
            continue;
        }

        s[slowPtr++] = s[fastPtr];
    }
    // ȥ��β���ո�
    while (s[slowPtr - 1] == ' ') {
        slowPtr--;
    }

    s.resize(slowPtr);
    // ��ת����
    reverse(s.begin(), s.end());
    // ��ת��������
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
�±�   0 1 2 3 4 5 6 7 8 9 10 11 
       A B A B A A A B A B A  A
ֵ     0 0 1 2 3 1 1 2 3 4 5  6
******************/
void getNext(vector<int>& next, const string &s) {

    // 1.��ʼ��������i=1,j=0�Ĳ���
    next.push_back(0);
    for (int i = 1, j = 0; i < s.size(); i++) {
        // 2.ǰ��׺����ͬ
        while (j > 0 && s[i] != s[j]) {
            j = next[j - 1];            // ����������һ��
        }
        // 3.ǰ��׺��ͬ
        if (s[i] == s[j]) {
            j++;
        }
        // 4.next���ݸ���
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

    // �����getNext�в�һ�����Ǵ�i = 0��ʼ��
    for (int i = 0; i < haystack.size(); i++) {
        while (j > 0 && haystack[i] != needle[j]) {
            j = next[j - 1];
        }

        if (haystack[i] == needle[j]) {
            j++;
        }

        // �˳�����
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

    // ������next����
    vector<int> next;
    getNext(next, s);

    // ��֪/�ܽ�����Ĺ���
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

        // ��һ�������س�ȥ
        while (queIn.size() > 1) {
            queOut.push(queIn.front());
            queIn.pop();
        }
        tempVal = queIn.front();
        queIn.pop();

        // ����queIn��
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

// �Ż��汾��ֻ��һ��queueʵ��
class MyStack2 {
    queue<int> queIn;

public:
    MyStack2() {}
    
    void push(int x) { queIn.push(x); }

    int pop() {
        
        int stackSize = queIn.size();
        int tempNum = 0;

        // �ƶ�size - 1��
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
         // �Ҳ������ || ��ƥ�� 
         else if (st.empty() || s[i] != st.top()) return false;
         else st.pop(); // �����ĳ�������ǰ�ַ���ջ���ַ���ͬ��pop��ȥ
    }
    // ��Ϊ�գ�������������true; �����������ˣ�����false
    return st.empty();
}

// ջ���������ǳ����á��Գ�ƥ�䡱����
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

// �Ż��汾����������һ��stack��
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
            //num.push(stoi(tokens[i]));        // ��ǰ�汾VS��֧��ȫ��C++11���ǿ���ֱ����ô��
            num.push(atoi(tokens[i].c_str()));
        }
    }
    return result;
}

// ΪmaxSlidingWindow��Ƶ���
class MyQueue2 {//��������(�Ӵ�С) 
public:
    deque<int> que; // ʹ��dequeʵ�ֵ�������

    // ÿ�ε�������ֵ�ǵ�����������ǰ�棨ֵ���Ԫ�أ��򵯳�
    void pop(int value) {
        if (!que.empty() && value == que.front()) {
            que.pop_front();
        }
    }

    // ��֤�������еĵ�����
    void push(int value) {
        while (!que.empty() && value > que.back()) {
            que.pop_back();
        }
        que.push_back(value);
    }

    // ��ǰ�����������ֵ������������Ԫ�أ�
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
    result.push_back(que.front());  // ��һ��ǰkԪ�����ֵ

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
    // ��ͳ�Ƹ�Ԫ�س��ֵ�Ƶ��
    for (int i = 0; i < nums.size(); i++) {
        map[nums[i]]++;
    }

    //�Ը�Ԫ��Ƶ�����򣬶����СΪK��С����
    priority_queue<pair<int, int>, vector<pair<int, int>>, topKFcomparison> pri_que;

    // ����map��ά����СΪk��С����
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

// ������ע�������Ǵ����д��������
// sequence container����ʹ��sort����Ҫ�Ȱ�map�ṹתΪvector
vector<int> topKFrequent2(vector<int>& nums, int k) {
    vector<int> result;
    unordered_map<int, int> map;

    // ��ͳ�Ƹ�Ԫ�س��ֵ�Ƶ��
    for (int i = 0; i < nums.size(); i++) {
        map[nums[i]]++;
    }

    // ����Ƶ�ʿ���map��Ƶ���ɴ�С
    sort(map.begin(), map.end(), topKFcomparison2);

    // ȡ��ǰk��
    for (int i = 0; i < k; i++) {
        result[i] = map[i];
    }
    return result;
}

//------------------ ������� ---------------------------
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

//------------------ ������� ---------------------------
#include <iostream>
#include <string>
#include <list>
#include <algorithm> 
namespace testListNode
{
    // ����ListNode
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

    // �ͷ�ListNode�ڴ�
    void deleteList(ListNode* pNode) {
        while (pNode->next != nullptr) {
            deleteList(pNode->next);
            break;
        }
        delete pNode;
    }

    // ��ӡListNode����
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
        linkedList->addAtIndex(2, 2);   //�����Ϊ1-> 3-> 2
        int ans = linkedList->get(1);   //����2
        linkedList->deleteAtIndex(2);   //����������1-> 3
        ans = linkedList->get(1);             //����3
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

//------------------ ��ϣ����� ---------------------------
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

//------------------ �ַ������� ---------------------------
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

//------------------ ջ����в��� ---------------------------
namespace testStackAndQueue {

    void test_geneMyQueue() {

        cout << "test_geneMyQueue" << endl;

        MyQueue *queue = new MyQueue();
        queue->push(1);
        queue->push(2);
        cout << queue->peek() <<endl;  // ���� 1
        cout << queue->pop() << endl;   // ���� 1
        cout << queue->empty() << endl; // ���� false
    }

    void test_geneMyStack() {

        cout << "test_geneMyStack" << endl;

        // MyStack2���Ż���ֻʹ��һ��queIn�İ汾
        MyStack2 *myStack = new MyStack2();
        myStack->push(1);
        myStack->push(2);
        cout << myStack->top() << endl; // ���� 2
        cout << myStack->pop() << endl; // ���� 2
        cout << myStack->empty() << endl; // ���� False
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

//------------------ ������ ---------------------------
//int main(int argc, char **argv)
void test1_5()
{
    // ����� ˫ָ��
    //testArray::test_removeElement();                // 27. �Ƴ�Ԫ��
    //testArray::test_removeDuplicates();             // 26. ɾ�����������е��ظ���
    //testArray::test_moveZeros();                    // 283. �ƶ���
    //testArray::test_backspaceCompare();             // 844. �ȽϺ��˸���ַ���
    //testArray::test_sortedSquares();                // 977.���������ƽ��

    // ������ ��������
    //testArray::test_minSubArrayLen();               // 209.������С��������
    //testArray::test_totalFruit();                   // 904. ˮ������    (medium)
    //testArray::test_minWindow();                    // 76. ��С�����Ӵ�   (hard)delay

    // ������ �������
    //testArray::test_generateMatrix();               // 59.��������II

    // ����
    //testListNode::test_removeElements();            // 203. �Ƴ�����Ԫ��
    //testListNode::test_MyLinkedList();              // 707. �������  (leetcode���������)
    //testListNode::test_reverseList();               // 206.��ת����
    //testListNode::test_swapPairs();                 // 24. �������������еĽڵ�
    //testListNode::test_removeNthFromEnd();          // 19. ɾ������ĵ����� N �����
    //testListNode::test_getIntersectionNode();       // ������ 02.07.�����ཻ
    //testListNode::test_detectCycle();               // 142. �������� II

    // ��ϣ��
    //testHashCode::test_isAnagram();                 // 242. ��Ч����ĸ��λ��
    //testHashCode::test_intersection();              // 349. ��������Ľ���
    //testHashCode::test_isHappy();                   // 202. ������
    //testHashCode::test_twoSum();                    // 1. ����֮��
    //testHashCode::test_fourSumCount();              // 454. ������� II
    //testHashCode::test_canConstruct();              // 383. �����
    //testHashCode::test_threeSum();                  // 15. ����֮��
    //testHashCode::test_fourSum();                   // 18. ����֮��
    
    // �ַ���
    //testString::test_reverseString();               // 344.��ת�ַ���
    //testString::test_reverseStr();                  // 541. ��ת�ַ���II
    //testString::test_replaceSpace();                // ��ָOffer 05.�滻�ո�
    //testString::test_reverseWord();                 // 151. ��ת�ַ�����ĵ���
    //testString::test_reverseLeftWords();            // ��ָ Offer 58 - II.����ת�ַ���
    //testString::test_strStr();                      // 28. ʵ�� strStr()        hard�����ˣ�����next�������дһ��
    //testString::test_repeatedSubstringPattern();    // 459.�ظ������ַ���

    // ջ�����
    //testStackAndQueue::test_geneMyQueue();          // 232. ��ջʵ�ֶ���
    //testStackAndQueue::test_geneMyStack();          // 225. �ö���ʵ��ջ
    //testStackAndQueue::test_isValid();              // 20. ��Ч������
    //testStackAndQueue::test_removeDuplicates();     // 1047. ɾ���ַ����е����������ظ���
    //testStackAndQueue::test_evalRPN();              // 150. �沨�����ʽ��ֵ
    //testStackAndQueue::test_maxSlidingWindow();     // 239. �����������ֵ    (hard)
    //testStackAndQueue::test_topKFrequent();         // 347. ǰ K ����ƵԪ��   (hard)

    system("pause");

}