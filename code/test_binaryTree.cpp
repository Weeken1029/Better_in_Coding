//---------------------------------------------------
using namespace std;

//------------------ LeetCode Test ---------------------------
//------------------ From BinaryTree To ����--------------
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <functional>
#include <string>

// LC ����������
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// LC N�����ڵ㶨��
class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) :val(_val) {}
    Node(int _val, vector<Node*> _children) :val(_val), children(_children) {}
};

// �ݹ�����������٣�����⣩
void preorder(TreeNode* root, vector<int> &res) {
    if (root == nullptr) { return; }

    res.push_back(root->val);
    preorder(root->left, res);
    preorder(root->right, res);
}

vector<int> preorderTraversal(TreeNode* root) {

    vector<int> ans;
    preorder(root, ans);
    return ans;
}

void postorder(TreeNode *root, vector<int> &res) {

    if (root == nullptr) { return; }

    postorder(root->left, res);
    postorder(root->right, res);
    res.push_back(root->val);
}

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> ans;
    postorder(root, ans);
    return ans;
}

void inorder(TreeNode *root, vector<int>&res) {
    if (root == nullptr) { return; }

    inorder(root->left, res);
    res.push_back(root->val);
    inorder(root->right, res);
}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    inorder(root, ans);
    return ans;
}

// ��������
vector<int> preorderTraversal2(TreeNode *root) {

    stack<TreeNode*> st;
    vector<int> result;
    if (root == nullptr)return result;
    TreeNode *node;
    st.push(root);
    while (!st.empty()) {
        node = st.top();                        // ��
        st.pop();
        result.push_back(node->val);
        if (node->right) st.push(node->right);  // �ң��Ƚ����
        if (node->left) st.push(node->left);    // �󣬺���ȳ�
    }
    return result;
}

vector<int> inorderTraversal2(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* cur = root;

    while (!cur || !st.empty()) {
        // һֱ��������
        if (!cur) {
            st.push(cur);
            cur = cur->left;
        }
        else {
            cur = st.top();
            st.pop();
            result.push_back(cur->val);
            cur = cur->right;
        }
    }
    return result;
}

// ͳһ�ĵ���������ǰ�к������˳�򼴿ɣ��ǣ�����
vector<int> preorderTraversal3(TreeNode *root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* cur;

    if (root != NULL) st.push(root);
    while (!st.empty()) {
        cur = st.top();
        if (cur) {
            st.pop();   // ������ǰ�ڵ㣬�����ظ�������
            if (cur->right) st.push(cur->right);    // ��
            if (cur->left)  st.push(cur->left);     // ��

            st.push(cur);                           // ��
            st.push(nullptr);                       // �գ�����������ʶ��ǰ��
        }
        // �����սڵ㣬�Ž��в���
        else {
            st.pop();   // �����սڵ�
            cur = st.top();
            st.pop();
            result.push_back(cur->val);
        }
    }
    return result;
}

vector<int> inorderTraversal3(TreeNode *root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* cur;

    if (root != NULL) st.push(root);
    while (!st.empty()) {
        cur = st.top();
        if (cur) {
            st.pop();   // ������ǰ�ڵ㣬�����ظ�������
            if (cur->right) st.push(cur->right);    // ��

            st.push(cur);                           // ��
            st.push(nullptr);                       // �գ�����������ʶ��ǰ��

            if (cur->left)  st.push(cur->left);     // ��
        }
        // �����սڵ㣬�Ž��в���
        // ����˵����ڵ��Ѿ�Ϊ�գ��ʹ����нڵ�
        else {
            st.pop();   // �����սڵ�
            cur = st.top();
            st.pop();
            result.push_back(cur->val);
        }
    }
    return result;
}

// �����������������¼��ģ�������Ը�
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<int> ans;
    vector<vector<int>> result;
    queue<TreeNode*>que;
    TreeNode* cur;
    if (root) { que.push(root); }

    while (!que.empty()) {
        int size = que.size();                          // ��ǰ��Ľڵ���
        // ��������һ��������д��i < que.size()��que���ڱ�ã�������
        for (int i = 0; i < size; i++) {
            cur = que.front();
            que.pop();
            if (cur->left) que.push(cur->left);         // ��������ڵ�
            if (cur->right) que.push(cur->right);       // �������ҽڵ�
            ans.push_back(cur->val);                    // �ڵ㴦��
        }
        result.push_back(ans);
        ans.clear();
    }
    return result;
}

vector<int> rightSideView(TreeNode* root) {
    vector<int> ans;
    queue<TreeNode*> que;
    TreeNode* cur;
    if (root) que.push(root);

    while (!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {
            cur = que.front();
            que.pop();
            if (cur->left)que.push(cur->left);
            if (cur->right)que.push(cur->right);
            if (i == (size - 1)) {
                ans.push_back(cur->val);
            }
        }
    }
    return ans;
}

vector<double> averageOfLevels(TreeNode* root) {
    vector<double> res;
    queue<TreeNode*> que;
    TreeNode* cur;
    double sum = 0.0;
    if (root) que.push(root);

    while (!que.empty()) {
        int size = que.size();          // ��ǰ��Ľڵ���
        for (int i = 0; i < size; i++) {
            cur = que.front();
            que.pop();
            if (cur->left) que.push(cur->left);
            if (cur->right) que.push(cur->right);
            sum += cur->val;
        }
        res.push_back(sum / size);
        sum = 0.0;
    }
    return res;
}

vector<vector<int>> levelOrderinNTree(Node* root) {
    vector<vector<int>> result;
    vector<int> res;
    queue<Node*> que;
    Node* cur;

    if (root) { que.push(root); }
    
    while (!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {
            cur = que.front();
            que.pop();
            for (auto iter : cur->children) {
                if (iter) que.push(iter);
            }
            res.push_back(cur->val);
        }
        result.push_back(res);
        res.clear();
    }
    return result;
}

vector<int> largestValues(TreeNode* root) {
    vector<int> res;
    vector<int> temp;
    queue<TreeNode*> que;
    TreeNode* cur;

    if (root) que.push(root);

    while (!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {
            cur = que.front();
            que.pop();
            if (cur->left) que.push(cur->left);
            if (cur->right) que.push(cur->right);
            temp.push_back(cur->val);
        }
        sort(temp.begin(), temp.end(), greater<int>());
        res.push_back(temp[0]);
        temp.clear();
    }
    return res;
}

// ������Ŀ�����ǵݹ顢ͳһ���������������������
// ��ת������-���������
TreeNode* invertTreeByLevelOrder(TreeNode* root) {
    queue<TreeNode*> que;
    TreeNode* cur;
    
    if (root) que.push(root);

    while (!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {
            cur = que.front();
            que.pop();
            swap(cur->left, cur->right);
            if(cur->left)que.push(cur->left);
            if(cur->right)que.push(cur->right);
        }
    }
    return root;
}

// ��ת������-������
TreeNode* invertTreeByIteration(TreeNode* root) {

    stack<TreeNode*> st;
    TreeNode* cur;
    if (root)st.push(root);

    while (!st.empty()) {
        cur = st.top();
        if (cur) {
            st.pop();
            if (cur->right) st.push(cur->right);
            if (cur->left) st.push(cur->left);

            st.push(cur);
            st.push(nullptr);
        }
        else {
            st.pop();
            cur = st.top();
            st.pop();
            swap(cur->left, cur->right);
        }
    }
    return root;
}

// ��ת������-�ݹ鷨
TreeNode* invertTreeByRecursion(TreeNode* root) {
    if (root == nullptr) return root;
    swap(root->left, root->right);
    if(root->left)  invertTreeByRecursion(root->left);
    if(root->right) invertTreeByRecursion(root->right);
    return root;
}

// �Գƶ�����-�ݹ鷨
bool isSymmetricInRecu(TreeNode* left, TreeNode* right) {
    if (left == nullptr && right == nullptr) {
        return true;
    }
    else if ((left == nullptr && right != nullptr)
     || (left != nullptr && right == nullptr)
     || (left->val != right->val)) {
        return false;
    }
    else 
    {
        bool Decision1 = isSymmetricInRecu(left->left, right->right);
        bool Decision2 = isSymmetricInRecu(left->right, right->left);
        return (Decision1 && Decision2);
    }
}

bool isSymmetricByRecursion(TreeNode* root) {
    bool flag = isSymmetricInRecu(root->left, root->right);
    return flag;
}

// �Գƶ�����-������(��ͳһ����Ҳ�ǲ���������е�������stack���������˼)
bool isSymmetricByIteration(TreeNode* root) {

    stack<TreeNode*> st;
    if (root == nullptr) return true;
    st.push(root->left);
    st.push(root->right);
    TreeNode* leftNode;
    TreeNode* rightNode;

    while (!st.empty()) {
        rightNode = st.top(); st.pop();
        leftNode = st.top(); st.pop();
        // ���Ҿ�Ϊ��
        if (!leftNode && !rightNode) {
            continue;
        }

        if (!leftNode || !rightNode || (leftNode->val != rightNode->val)) {
            return false;
        }
        st.push(leftNode->right);
        st.push(rightNode->left);
        st.push(leftNode->left);
        st.push(rightNode->right);
    }
    return true;
}

// ��ͬ���� - �ݹ鷨
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr) {
        return true;
    }
    else if (p == nullptr || q == nullptr) {
        return false;
    }
    else if (p->val != q->val) {
        return false;
    }
    bool ansLeft = isSameTree(p->left, q->left);
    bool ansRight = isSameTree(p->right, q->right);

    return ansLeft && ansRight;
}

// ������-���������
int maxDepthByLevelOrder(TreeNode* root) {
    int depth = 0;
    queue<TreeNode*> que;
    TreeNode* cur;

    if (root) que.push(root);
    while (!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {
            cur = que.front();
            que.pop();
            if (cur->left)que.push(cur->left);
            if (cur->right)que.push(cur->right);
        }
        depth++;
    }
    return depth;
}

// ������-�ݹ鷨
int getTreeDepth(TreeNode* root) {
    if (root == nullptr)return 0;
    int leftdepth = getTreeDepth(root->left);
    int rightdepth = getTreeDepth(root->right);
    int depth = 1 + max(leftdepth, rightdepth);
    return depth;
}

int maxDepthByRecursion(TreeNode* root) {
    int depth = getTreeDepth(root);
    return depth;
}

// ��С���-�ݹ鷨
int getMinTreeDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr) {
        int rightdepth = getMinTreeDepth(root->right);
        return  rightdepth + 1;
    }
    else if (root->right == nullptr) {
        int  leftdepth = getMinTreeDepth(root->left);
        return leftdepth + 1;
    }
    int leftdepth = getMinTreeDepth(root->left);
    int rightdepth = getMinTreeDepth(root->right);
    int depth = 1 + min(leftdepth, rightdepth);
    return depth;
}

int minDepthByRecursion(TreeNode* root) {
    int depth = getMinTreeDepth(root);
    return depth;
}

// ��С���-���������
int minDepthByLevelOrder(TreeNode* root) {
    int minDepth = 0;
    queue<TreeNode*>que;
    TreeNode* cur;

    if (!root) return 0; 
    que.push(root);

    while (!que.empty()) {
        int queSize = que.size();
        minDepth++;
        for (int i = 0; i < queSize; i++) {
            cur = que.front();
            que.pop();
            if (!cur->left && !cur->right) { return minDepth; }
            que.push(cur->left);
            que.push(cur->right);
        }
    }
    return minDepth;
}

// ��ȫ�������Ľڵ���� - �ݹ鷨
int getNodeNum(TreeNode* root) {
    if (root->right == nullptr && root->left == nullptr) return 1;
    
    int leftNum  = 0;
    int rightNum = 0;

    if (root->left != nullptr) {
        leftNum = getNodeNum(root->left);
    }
    if (root->right != nullptr) {
        rightNum = getNodeNum(root->right);
    }

    return leftNum + rightNum + 1;
}

int countNodesByRecursion(TreeNode* root) {
    if (root == nullptr) return 0;
    return getNodeNum(root);
}

// ��ȫ�������Ľڵ���� - ���������
int countNodesByLevelOrder(TreeNode* root) {
    int result = 0;
    queue<TreeNode*>que;
    TreeNode* cur;

    if (root == nullptr) return 0;
    que.push(root);

    while (!que.empty()) {
        int queSize = que.size();
        for (int i = 0; i < queSize; i++) {
            cur = que.front();
            que.pop();
            if(cur->left) que.push(cur->left);
            if(cur->right) que.push(cur->right);
            result++;
        }
    }
    return result;
}

// ƽ������� - �ݹ鷨
int getHeight(TreeNode* root) {

    if (root == nullptr)return 0;

    int leftHeight = getHeight(root->left);
    if (leftHeight == -1) return -1;
    int rightHeight = getHeight(root->right);
    if (rightHeight == -1) return -1;

    int result;
    if (abs(leftHeight - rightHeight) > 1) {
        return -1;
    }
    else {
        result = 1 + max(leftHeight, rightHeight);
    }
    return result;
}

bool isBalancedByRecursion(TreeNode* root) {
    int height = getHeight(root);
    return height == -1 ? false : true;
}

// ƽ������� - ������
// getDepthtByIteration����������ǰ�ڵ��������������
int getDepthtByIteration(TreeNode* root) {
    int depth = 0;
    queue<TreeNode*> que;
    TreeNode *node;

    if (root == nullptr) return 0;
    que.push(root);

    while (!que.empty()) {
        int queSize = que.size();
        for (int i = 0; i < queSize; i++) {
            node = que.front();
            que.pop();
            if (node->left)  que.push(node->left);
            if (node->right) que.push(node->right);
        }
        depth++;
    }
    return depth;
}

bool isBalancedByIteration(TreeNode* root) {
    TreeNode* cur;
    stack<TreeNode*> st;
    int leftDepth, rightDepth;
    if (root == nullptr) return true;
    st.push(root);

    while (!st.empty()) {
        cur = st.top();
        if (cur) {
            st.pop();
            st.push(cur);
            st.push(nullptr);
            if (cur->right) st.push(cur->right);
            if (cur->left) st.push(cur->left);
        }
        else {
            st.pop();
            cur = st.top();
            st.pop();
            leftDepth = getDepthtByIteration(cur->left);
            rightDepth = getDepthtByIteration(cur->right);
            if (abs(leftDepth - rightDepth) > 1) {
                return false;
            }
        }
    }
    return true;
}

// ������������·�� - �ݹ鷨
void traversalTreePath(TreeNode* cur, vector<int>& path, vector<string>& result) {
    path.push_back(cur->val);   // ��
    // ��ǰҶ�ӽڵ��˳�����
    if (cur->left == nullptr && cur->right == nullptr) {
        string sPath;
        for (int i = 0; i < path.size() - 1; i++) {
            sPath += to_string(path[i]);
            sPath += "->";
        }
        sPath += to_string(path[path.size() - 1]);
        result.push_back(sPath);
        return;
    }
    if (cur->left) {            // ��
        traversalTreePath(cur->left, path, result);
        path.pop_back();        // ����
    }
    if (cur->right) {           // ��
        traversalTreePath(cur->right, path, result);
        path.pop_back();        // ����
    }
}

vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> ans;
    vector<int> path;
    if (root == nullptr) return ans;
    traversalTreePath(root, path, ans);
    return ans;
}

// ������������·�� - ������
vector<string> binaryTreePathsByIteration(TreeNode* root) {
    stack<TreeNode*> treeSt;    // �������ı����ڵ�
    stack<string> pathSt;       // �������·���ڵ�
    vector<string> ans;         // ����·��
    TreeNode* node;
    string path;

    if (root == nullptr) return ans;
    treeSt.push(root);
    pathSt.push(to_string(root->val));

    while (!treeSt.empty()) {
        node = treeSt.top(); treeSt.pop();  // �нڵ�
        path = pathSt.top(); pathSt.pop();  // ��Ӧ·��
        // ��ǰΪҶ�ӽڵ�
        if (node->left == nullptr && node->right == nullptr) {
            ans.push_back(path);
        }
        if (node->right) {  //��
            treeSt.push(node->right);
            pathSt.push(path + "->" + to_string(node->right->val));
        }
        if (node->left) {   // ��
            treeSt.push(node->left);
            pathSt.push(path + "->" + to_string(node->left->val));
        }
    }
    return ans;
}

// ��Ҷ��֮�� - �ݹ鷨
int leftLeavesTraversal(TreeNode* node) {
    int sum = 0;
    if (node->left && node->left->left == nullptr && node->left->right == nullptr) {
        sum += node->left->val;
    }
    if (node->left) {
        sum += leftLeavesTraversal(node->left);
    }
    if (node->right) {
        sum += leftLeavesTraversal(node->right);
    }
    return sum;
}

int sumOfLeftLeaves(TreeNode* root) {
    if (root == nullptr) return 0;
    return leftLeavesTraversal(root);
}

// �������½ǵ�ֵ - �ݹ鷨
int maxLen = INT32_MIN;
int maxLeftValue = 0;
void bottomLeftValueTraversal(TreeNode* node, int curLen) {
    // �˳�����
    if (node->left == nullptr && node->right == nullptr) {
        if (curLen > maxLen) {
            maxLen = curLen;
            maxLeftValue = node->val;
        }
        return;
    }
    if (node->left) {
        curLen++;
        bottomLeftValueTraversal(node->left, curLen);
        curLen--;      // ����
    }
    if (node->right) {
        curLen++;
        bottomLeftValueTraversal(node->right, curLen);
        curLen--;      // ����
    }
}

int findBottomLeftValue(TreeNode* root) {
    bottomLeftValueTraversal(root, 0);
    return maxLeftValue;
}

// �������½ǵ�ֵ - �������
int findBottomLeftValueByIteration(TreeNode* root) {
    int ans;
    TreeNode* node;
    queue<TreeNode*> que;
    if (root == nullptr) { return 0; }
    que.push(root);

    while (!que.empty()) {
        int size = que.size();
        ans = que.front()->val;
        for (int i = 0; i < size; i++) {
            node = que.front();
            que.pop();
            if (node->left)que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    return ans;
}

// ·���ܺ� - �ݹ鷨
bool pathSumTraversal(TreeNode* node, int targetSum) {
    if (node->left == nullptr && node->right == nullptr && targetSum == 0) {
        return true;
    }

    if (node->left) {
        // �����˻���
        if (pathSumTraversal(node->left, targetSum - node->left->val))return true;
    }
    if (node->right) {
        // �����˻���
        if (pathSumTraversal(node->right, targetSum - node->right->val))return true;
    }
    return false;
}

bool hasPathSumTraversal(TreeNode* root, int targetSum) {
    return pathSumTraversal(root, targetSum - root->val);
}

// ·���ܺ� - �������
bool hasPathSumIteration(TreeNode* root, int targetSum) {
    TreeNode* node;
    stack<TreeNode*> st;
    if (root == nullptr) return false;
    st.push(root);

    while (!st.empty()) {
        node = st.top();
        if (node) {
            st.pop();
            if (node)st.push(node);
            st.push(nullptr);
            if (node->right) st.push(node->right);
            if (node->left) st.push(node->left);
            targetSum -= node->val;
            if (node->left == nullptr && node->right == nullptr && targetSum == 0) {
                return true;
            }
        }
        else {
            st.pop();
            node = st.top();
            st.pop();
            // ����
            targetSum += node->val;
        }
    }
    return false;
}

// ����ͺ���������й��������
TreeNode* buildTree2(vector<int>& inorder, vector<int>& postorder) {
    // 1.�˳�����֮һ
    if (postorder.size() == 0) return nullptr;

    // 2.�ɺ�������ҵ��ڵ�
    int rootValue = postorder[postorder.size() - 1];
    TreeNode* root = new TreeNode(rootValue);

    // 3.�ҵ��и��
    int deliIndex;
    for (deliIndex = 0; deliIndex < inorder.size(); deliIndex++) {
        if (inorder[deliIndex] == rootValue) break;
    }

    // 4.�и���������
    vector<int> inorderLeft(inorder.begin(), inorder.begin() + deliIndex);
    vector<int> inorderRight(inorder.begin() + deliIndex + 1, inorder.end());

    // 5.�и��������
    vector<int> postorderLeft(postorder.begin(), postorder.begin() + deliIndex);
    vector<int> postorderRight(postorder.begin() + deliIndex, postorder.end() - 1);

    // 6.�ݹ�������ҽڵ�
    root->left = buildTree2(inorderLeft, postorderLeft);
    root->right = buildTree2(inorderRight, postorderRight);

    return root;
}

// �����ǰ��������й��������
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    // 1.�˳�����֮һ
    if (preorder.size() == 0) return nullptr;

    // 2.�ҵ���ǰ�ڵ�
    TreeNode* root = new TreeNode(preorder[0]);

    // 3.�ҵ��ָ��
    int deliIndex;
    for (deliIndex = 0; deliIndex < inorder.size(); deliIndex++) {
        if (inorder[deliIndex] == root->val) break;
    }

    // 5.������������
    vector<int> inorderLeft(inorder.begin(), inorder.begin() + deliIndex);
    vector<int> inorderRight(inorder.begin() + deliIndex+ 1, inorder.end());

    // 4.ǰ����������
    vector<int> preorderLeft(preorder.begin() + 1, preorder.begin() + 1 + deliIndex);
    vector<int> preorderRight(preorder.begin() + 1 + deliIndex, preorder.end());

    // 6���ݹ�
    root->left = buildTree(preorderLeft, inorderLeft);
    root->right = buildTree(preorderRight, inorderRight);

    return root;
}

// �������� �����⹹���µ�vector��
TreeNode* constructMaxBinaryTree(vector<int>& nums, int left, int right) {

    // 1.�˳�����֮һ
    if (right <= left) return nullptr;

    // 2.�ҵ���ǰ���ڵ�
    auto iter = max_element(nums.begin()+ left, nums.begin() + right);
    TreeNode* root = new TreeNode(*iter);

    // 3.ȷ���ָ��
    int deliIndex = 0;
    for (deliIndex = left; deliIndex < right; deliIndex++) {
        if (nums[deliIndex] == *iter) break;
    }

    // 4.�ݹ�
    root->left = constructMaxBinaryTree(nums, left, deliIndex);
    root->right = constructMaxBinaryTree(nums, deliIndex + 1, right);

    return root;
}

TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    return constructMaxBinaryTree(nums, 0, nums.size());

}

// �ϲ�������
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    // �������
    if (root1 == nullptr && root2 != nullptr) {
        return root2;
    }
    else if (root1 != nullptr && root2 == nullptr) {
        return root1;
    }
    else if (root1 == nullptr && root2 == nullptr) {
        return nullptr;
    }

    // ����Ϊnull
    root1->val = root1->val + root2->val;
    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);

    return root1;
}

// �����������е�����
TreeNode* searchBST(TreeNode* root, int val) {
    // �˳�����
    if (root == nullptr || root->val == val) return root;

    if (root->val > val) {
        return searchBST(root->left, val);
    }
    if (root->val < val) {
        return searchBST(root->right, val);
    }
}

// ��֤����������
void BSTToArray(TreeNode* root, vector<int>& vec) {
    if (root == nullptr) return;
    BSTToArray(root->left, vec);    // ��
    vec.push_back(root->val);       // �У�
    BSTToArray(root->right, vec);   // ��
}

bool isValidBST(TreeNode* root) {
    vector<int> vec = {};
    BSTToArray(root, vec);

    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] <= vec[i - 1]) return false;
    }
    return true;
}

// ��������������С���Բ�
int minDiff = INT32_MAX;
TreeNode* preNode;
void getMinDifference(TreeNode* curNode) {
    // �˳�����
    if (curNode == nullptr) return;

    // ��
    getMinDifference(curNode->left);
    // ��
    if (preNode != nullptr) {
        minDiff = min(minDiff, curNode->val - preNode->val);
    }
    preNode = curNode;
    // ��
    getMinDifference(curNode->right);
}

int getMinimumDifference(TreeNode* root) {
    getMinDifference(root);
    return minDiff;
}

// �����������е�����
int maxModeNum = INT_MIN;
vector<int> modeVec;
TreeNode* pre;
int modeNum = 0;
void findModeTraversal(TreeNode* node) {
    if (node == nullptr) return;

    findModeTraversal(node->left);     // ��
    
    // ��
    if (pre == nullptr) {                       // ��ʼ�ڵ�
        modeNum = 1;
    }
    else if (node->val == pre->val) {
        modeNum++;
    }
    else {
        modeNum = 1;
    }
    pre = node;

    if (maxModeNum < modeNum) {
        maxModeNum = modeNum;
        modeVec.clear();
        modeVec.push_back(node->val);
    }
    else if (maxModeNum == modeNum) {
        modeVec.push_back(node->val);
    }

    findModeTraversal(node->right);    // ��
}

vector<int> findMode(TreeNode* root) {
    modeVec.clear();
    findModeTraversal(root);
    return modeVec;
}

// �������Ĺ�������
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

    // 1.�˳�����
    if (root == p || root == q || root == nullptr) return root;

    // 2.����ݹ��߼�
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    // ���ҽڵ�Ĵ���
    if (left != nullptr && right != nullptr) return root;

    if (left != nullptr && right == nullptr) return left;
    else if (left == nullptr && right != nullptr) return right;
    else return nullptr;


}

// �����������Ĺ�������
TreeNode* lowestCommonAncestorOfBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    // 1.��ֹ����
    if (root == nullptr) return root;

    // root�����
    if (root->val < p->val && root->val < q->val) {
        TreeNode* right = lowestCommonAncestorOfBST(root->right, p, q);
        if (right) return right;
    }
    // root���Ҳ�
    else if (root->val > p->val && root->val > q->val) {
        TreeNode* left = lowestCommonAncestorOfBST(root->left, p, q);
        if (left) return left;
    }

    return root;
}

// �����������Ĺ�������
TreeNode* lowestCommonAncestorOfBSTIteration(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (root->val > p->val && root->val > q->val) {
            root = root->left;
        }
        else if (root->val > p->val && root->val > q->val) {
            root = root->right;
        }
        else return root;
    }
    return nullptr;
}

// �����������еĲ������ - �ݹ�
TreeNode* insertIntoBST(TreeNode* root, int val) {
    // 1.��ֹ����
    if (!root) {
        TreeNode* cur = new TreeNode(val);
        return cur;
    }

    // 2.���ҽڵ㴦���߼�
    if (root->val > val) {
        root->left = insertIntoBST(root->left, val);
    }
    else if (root->val < val) {
        root->right  = insertIntoBST(root->right, val);
    }
    return root;
}

// �����������еĲ������ - ����
TreeNode* insertIntoBSTIteration(TreeNode* root, int val) {
    // ˼·����λ���Ǹ��޷��ٽ�һ������Ľڵ�
    if (root == nullptr) {
        TreeNode* node = new TreeNode(val);
        return node;
    }

    TreeNode* cur = root;
    TreeNode* parent = root;
    while (cur != nullptr) {
        parent = cur;
        if (cur->val > val) cur = cur->left;
        else cur = cur->right;
    }

    TreeNode* node = new TreeNode(val);
    if (parent->val > val) parent->left = node;
    else parent->right = node;

    return root;
}

// ɾ�������������еĽڵ�
TreeNode* deleteNodeTraversal(TreeNode* root, int key) {
    // 1.��ֹ����
    if (root == nullptr) return root;

    //2.���㴦���߼�
    if (root->val > key) root->left = deleteNodeTraversal(root->left, key);
    if (root->val < key) root->right = deleteNodeTraversal(root->right, key);

    if (root->val == key) {
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            return nullptr;
        }
        if (root->left == nullptr) {
            TreeNode* tmp = root->right;
            delete root;
            return tmp;
        }
        else if (root->right == nullptr) {
            TreeNode* tmp = root->left;
            delete root;
            return tmp;
        }
        else if (root->left != nullptr && root->right != nullptr) {
            TreeNode* cur = root->right;
            while (cur->left != nullptr) {
                cur = cur->left;
            }
            cur->left = root->left;
            TreeNode* tmp = root->right;
            delete root;
            return tmp;
        }
    }
}

// �޼�����������
TreeNode* trimBST(TreeNode* root, int low, int high) {
    // 1.�˳�����
    if (root == nullptr) return nullptr;
    if (root->val < low) {
        TreeNode *cur = trimBST(root->right, low, high);
        return cur;
    }
    if (root->val > high) {
        TreeNode *cur = trimBST(root->left, low, high);
        return cur;
    }

    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    return root;
}

// ��������ת��ΪBST
TreeNode* sortedArrayToBSTTraversal(vector<int>& nums, int start, int end) {
    // 1.��ֹ����
    if (start > end) return nullptr;

    if (start == end) {
        TreeNode* cur = new TreeNode(nums[start]);
        return cur;
    }

    int middleIdx = (end + start + 1) / 2;
    TreeNode* root = new TreeNode(nums[middleIdx]);

    root->left = sortedArrayToBSTTraversal(nums, start, middleIdx - 1);
    root->right = sortedArrayToBSTTraversal(nums, middleIdx + 1, end);
    
    return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
    return sortedArrayToBSTTraversal(nums, 0, nums.size() - 1);
}

// ����������ת��Ϊ�ۼ��� - ����
TreeNode* convertBST(TreeNode* root) {
    if (root == nullptr) return nullptr;
    
    stack<TreeNode*> st;
    TreeNode* cur;
    TreeNode* pre = nullptr;
    st.push(root);

    while (!st.empty()) {
        cur = st.top();
        if (cur != nullptr) {
            st.pop();
            if (cur->left) st.push(cur->left);
            st.push(cur);
            st.push(nullptr);
            if (cur->right) st.push(cur->right);
        }
        else {
            st.pop();
            cur = st.top();
            st.pop();

            if (pre != nullptr) {
                cur->val += pre->val;
            }
            pre = cur;
        }
    }
    return root;
}

// ����������ת��Ϊ�ۼ��� - �ݹ�
TreeNode* preConvertBST = nullptr;
void traversalConvertBST(TreeNode* root) {
    if (root == nullptr) return;
    // ��
    traversalConvertBST(root->right);
    // �м�㴦��
    if (preConvertBST != nullptr) {
        root->val += preConvertBST->val;
    }
    preConvertBST = root;
    // ��
    traversalConvertBST(root->left);
}

TreeNode* convertBSTTraversal(TreeNode* root) {
    traversalConvertBST(root);
    return root;
}


//------------------ ���������� ---------------------------
#include <vector>
namespace testBinaryTree {

    void test_preorderTraversal() {
        cout << "test_preorderTraversal" << endl;

        TreeNode *root = new TreeNode(1);
        TreeNode *right1 = new TreeNode(2);
        TreeNode *left2 = new TreeNode(3);
        root->right = right1;
        right1->left = left2;

        vector<int> result;
        //result = preorderTraversal(root);
        //result = preorderTraversal2(root);
        result = preorderTraversal3(root);

        for (auto iter : result) {
            cout << iter << ", ";
        }
        cout << endl;

        free(root);
        free(right1);
        free(left2);
    }

    void test_postorderTraversal() {
        cout << "test_postorderTraversal" << endl;

        TreeNode *root = new TreeNode(1);
        TreeNode *right1 = new TreeNode(2);
        TreeNode *left2 = new TreeNode(3);
        root->right = right1;
        right1->left = left2;

        vector<int> result;
        result = postorderTraversal(root);

        for (auto iter : result) {
            cout << iter << ", ";
        }
        cout << endl;

        free(root);
        free(right1);
        free(left2);
    }

    void test_inorderTraversal() {
        cout << "test_inorderTraversal" << endl;

        TreeNode *root = new TreeNode(1);
        TreeNode *right1 = new TreeNode(2);
        TreeNode *left2 = new TreeNode(3);
        root->right = right1;
        right1->left = left2;

        vector<int> result;
        //result = inorderTraversal(root);
        //result = inorderTraversal2(root);
        result = inorderTraversal3(root);

        for (auto iter : result) {
            cout << iter << ", ";
        }
        cout << endl;

        free(root);
        free(right1);
        free(left2);
    }

    void test_levelOrder() {
        cout << "test_levelOrder" << endl;

        TreeNode *root = new TreeNode(3);
        TreeNode *left_1 = new TreeNode(9);
        TreeNode *right_1 = new TreeNode(20);
        TreeNode *left_2 = new TreeNode(15);
        TreeNode *right_2 = new TreeNode(7);
        root->left = left_1;
        root->right = right_1;
        right_1->left = left_2;
        right_1->right = right_2;

        vector<vector<int>> ans = levelOrder(root);

        for (auto iter1 : ans) {
            for (auto iter2 : iter1) {
                cout << iter2 << ",";
            }
            cout << endl;
        }
        free(root); free(left_1); free(right_1); free(left_2); free(right_2);
    }

    void test_rightSideView() {
        cout << "test_rightSideView" << endl;

        TreeNode *root = new TreeNode(1);
        TreeNode *left_1 = new TreeNode(2);
        TreeNode *right_1 = new TreeNode(3);
        TreeNode *left_2 = new TreeNode(4);
        TreeNode *right_2 = new TreeNode(5);

        root->left = left_1;
        root->right = right_1;
        left_1->right = right_2;
        right_1->right = left_2;

        vector<int> result = rightSideView(root);

        for (auto iter : result) {
            cout << iter << ",";
        }
        free(root); free(left_1); free(right_1); free(left_2); free(right_2);
    }

    void test_averageOfLevels() {
        cout << "test_levelOrder" << endl;

        TreeNode *root = new TreeNode(3);
        TreeNode *left_1 = new TreeNode(9);
        TreeNode *right_1 = new TreeNode(20);
        TreeNode *left_2 = new TreeNode(15);
        TreeNode *right_2 = new TreeNode(7);
        root->left = left_1;
        root->right = right_1;
        right_1->left = left_2;
        right_1->right = right_2;

        vector<double> result = averageOfLevels(root);

        for (auto iter : result) {
            cout << iter << ",";
        }
        free(root); free(left_1); free(right_1); free(left_2); free(right_2);
    }

    void test_levelOrderinNTree() {
        Node *root = new Node(1);
        Node *root_child1 = new Node(3);
        Node *root_child2 = new Node(2);
        Node *root_child3 = new Node(4);
        Node *child1_child1 = new Node(5);
        Node *child1_child2 = new Node(6);

        root->children.push_back(root_child1);
        root->children.push_back(root_child2);
        root->children.push_back(root_child3);
        root_child1->children.push_back(child1_child1);
        root_child1->children.push_back(child1_child2);

        vector<vector<int>>  ans = levelOrderinNTree(root);

        for (auto iter1 : ans) {
            for (auto iter2 : iter1) {
                cout << iter2 << ",";
            }
            cout << endl;
        }

        free(root); free(root_child1); free(root_child2);
        free(root_child3); free(child1_child1); free(child1_child2);
    }

    void test_largestValues() {
        cout << "test_largestValues" << endl;

        TreeNode* root = new TreeNode(1);
        TreeNode* level2_1 = new TreeNode(3);
        TreeNode* level2_2 = new TreeNode(2);
        TreeNode* level3_1 = new TreeNode(5);
        TreeNode* level3_2 = new TreeNode(3);
        TreeNode* level3_3 = new TreeNode(9);
        root->left      = level2_1;
        root->right     = level2_2;
        level2_1->left  = level3_1;
        level2_1->right = level3_2;
        level2_2->right = level3_3;

        vector<int> ans = largestValues(root);

        for (auto iter : ans) {
            cout << iter << " ";
        }
        cout << endl;
    }

    void test_invertTree() {
        cout << "test_invertTree" << endl;

        TreeNode *root = new TreeNode(4);
        TreeNode *root_left = new TreeNode(2);
        TreeNode *root_right = new TreeNode(7);
        TreeNode *level21_left = new TreeNode(1);
        TreeNode *level21_right = new TreeNode(3);
        TreeNode *level22_left = new TreeNode(6);
        TreeNode *level22_right = new TreeNode(9);
        root->left = root_left;
        root->right = root_right;
        root_left->left = level21_left;
        root_left->right = level21_right;
        root_right->left = level22_left;
        root_right->right = level22_right;
        
        TreeNode* node = invertTreeByLevelOrder(root);
        TreeNode* node1 = invertTreeByIteration(root);
        TreeNode* node2 = invertTreeByRecursion(root);
    }

    void test_isSymmetric() {
        cout << "test_isSymmetric" << endl;

        TreeNode *root = new TreeNode(1);
        TreeNode *root_left = new TreeNode(2);
        TreeNode *root_right = new TreeNode(2);
        TreeNode *level21_left = new TreeNode(3);
        TreeNode *level21_right = new TreeNode(4);
        TreeNode *level22_left = new TreeNode(4);
        TreeNode *level22_right = new TreeNode(3);
        root->left = root_left;
        root->right = root_right;
        root_left->left = level21_left;
        root_left->right = level21_right;
        root_right->left = level22_left;
        root_right->right = level22_right;

        //bool ans1 = isSymmetricByRecursion(root);
        bool ans2 = isSymmetricByIteration(root);
        cout << ans2 << endl;

        free(root); free(root_left); free(root_right);
        free(level21_left); free(level21_right); free(level22_left); free(level22_right);
    }

    void test_isSameTree() {
        TreeNode* p         = new TreeNode(1);
        TreeNode* pLevel11  = new TreeNode(2);
        TreeNode* pLevel12  = new TreeNode(3);
        TreeNode* q         = new TreeNode(1);
        TreeNode* qLevel11  = new TreeNode(2);
        TreeNode* qLevel12  = new TreeNode(3);

        p->left  = pLevel11;
        p->right = pLevel12;
        q->left  = qLevel11;
        q->right = qLevel12;

        bool ans = isSameTree(p, q);
        cout << ans << endl;
    }

    void test_maxDepth() {
        cout << "test_maxDepth" << endl;

        TreeNode *root = new TreeNode(3);
        TreeNode *left_1 = new TreeNode(9);
        TreeNode *right_1 = new TreeNode(20);
        TreeNode *left_2 = new TreeNode(15);
        TreeNode *right_2 = new TreeNode(7);
        root->left = left_1;
        root->right = right_1;
        right_1->left = left_2;
        right_1->right = right_2;

        //int ans = maxDepthByLevelOrder(root);
        int ans = maxDepthByRecursion(root);
        cout << ans << endl;

        free(root); free(left_1); free(right_1); free(left_2); free(right_2);
    }

    void test_minDepth() {

        TreeNode *root = new TreeNode(3);
        TreeNode *left_1 = new TreeNode(9);
        TreeNode *right_1 = new TreeNode(20);
        TreeNode *left_2 = new TreeNode(15);
        TreeNode *right_2 = new TreeNode(7);
        root->left = left_1;
        root->right = right_1;
        right_1->left = left_2;
        right_1->right = right_2;

        int ans = minDepthByLevelOrder(root);
        //int ans = minDepthByRecursion(root);
        cout << ans << endl;

        free(root); free(left_1); free(right_1); free(left_2); free(right_2);
    }

    void test_countNodes() {

        TreeNode *root = new TreeNode(1);
        TreeNode *level_11 = new TreeNode(2);
        TreeNode *level_12 = new TreeNode(3);
        TreeNode *level_21 = new TreeNode(4);
        TreeNode *level_22 = new TreeNode(5);
        TreeNode *level_23 = new TreeNode(6);
        root->left      = level_11;
        root->right     = level_12;
        level_11->left  = level_21;
        level_11->right = level_22;
        level_12->left  = level_23;

        int result = countNodesByRecursion(root);
        cout << result << endl;
        int result2 = countNodesByLevelOrder(root);
        cout << result2 << endl;

        free(root); free(level_11); free(level_12);
        free(level_21); free(level_22); free(level_23);
    }

    void test_isBalanced() {

        TreeNode *root      = new TreeNode(3);
        TreeNode *level_11  = new TreeNode(9);
        TreeNode *level_12  = new TreeNode(20);
        TreeNode *level_21  = new TreeNode(15);
        TreeNode *level_22  = new TreeNode(7);
        root->left      = level_11;
        root->right     = level_12;
        level_12->left  = level_21;
        level_12->right = level_22;

        bool ans = isBalancedByRecursion(root);
        cout << ans << endl;
        bool ans2 = isBalancedByIteration(root);
        cout << ans2 << endl;
    }

    void test_binaryTreePaths() {
        TreeNode *root      = new TreeNode(1);
        TreeNode *level_11  = new TreeNode(2);
        TreeNode *level_12  = new TreeNode(3);
        TreeNode *level_21  = new TreeNode(5);
        root->left = level_11;
        root->right = level_12;
        level_11->right = level_21;

        //vector<string> ans = binaryTreePaths(root);
        vector<string> ans2 = binaryTreePathsByIteration(root);

        for (auto iter : ans2) {
            cout << iter << endl;
        }

        free(root); free(level_11);
        free(level_12); free(level_21);
    }

    void test_sumOfLeftLeaves() {
        TreeNode *root      = new TreeNode(3);
        TreeNode *level_11  = new TreeNode(9);
        TreeNode *level_12  = new TreeNode(20);
        TreeNode *level_21  = new TreeNode(15);
        TreeNode *level_22  = new TreeNode(7);
        root->left = level_11;
        root->right = level_12;
        level_12->left = level_21;
        level_12->right = level_22;

        cout << sumOfLeftLeaves(root) << endl;

        free(root); free(level_11); free(level_12);
        free(level_21); free(level_22);
    }

    void test_findBottomLeftValue() {
        TreeNode *root = new TreeNode(1);
        TreeNode *level_11 = new TreeNode(2);
        TreeNode *level_12 = new TreeNode(3);
        TreeNode *level_21 = new TreeNode(4);
        TreeNode *level_22 = new TreeNode(5);
        TreeNode *level_23 = new TreeNode(6);
        TreeNode *level_31 = new TreeNode(7);
        root->left = level_11;
        root->right = level_12;
        level_11->left = level_21;
        level_12->left = level_22;
        level_12->right = level_23;
        level_22->left = level_31;

        cout << findBottomLeftValue(root) << endl;
        cout << findBottomLeftValueByIteration(root) << endl;

        free(root); free(level_11); free(level_12);
        free(level_21); free(level_22); free(level_23); free(level_31);
    }

    void test_hasPathSumTraversal() {
        TreeNode *root = new TreeNode(5);
        TreeNode *level_11 = new TreeNode(4);
        TreeNode *level_12 = new TreeNode(8);
        TreeNode *level_21 = new TreeNode(11);
        TreeNode *level_22 = new TreeNode(13);
        TreeNode *level_23 = new TreeNode(4);
        TreeNode *level_31 = new TreeNode(7);
        TreeNode *level_32 = new TreeNode(2);
        TreeNode *level_33 = new TreeNode(1);
        root->left = level_11; root->right = level_12; 
        level_11->left = level_21; level_12->left = level_22; level_12->right = level_23;
        level_21->left = level_31; level_21->right = level_32; level_23->right = level_33;

        //cout << hasPathSumTraversal(root,22) << endl;
        cout << hasPathSumIteration(root, 22) << endl;

        free(root); free(level_11); free(level_12);
        free(level_21); free(level_22); free(level_23);
        free(level_31); free(level_32); free(level_33);
    }

    void test_buildTree() {
        vector<int> preorder = { 3,9,20,15,7 };
        vector<int> inorder = { 9,3,15,20,7 };
        vector<int> postorder = { 9,15,7,20,3 };

        // ǰ�������
        TreeNode* ans = buildTree(preorder, inorder);

         //���������
        TreeNode* ans2 = buildTree2(inorder, postorder);
    }

    void test_constructMaximumBinaryTree() {
        vector<int> vec = { 3,2,1,6,0,5 };
        TreeNode* ans = constructMaximumBinaryTree(vec);
    }

    void test_mergeTrees() {
        TreeNode *root_1 = new TreeNode(1); TreeNode *level11_1 = new TreeNode(3);
        TreeNode *level12_1 = new TreeNode(2); TreeNode *level21_1 = new TreeNode(5);
        root_1->left = level11_1; root_1->right = level12_1; level11_1->left = level21_1;

        TreeNode *root_2 = new TreeNode(2); TreeNode *level11_2 = new TreeNode(1);
        TreeNode *level12_2 = new TreeNode(3); TreeNode *level21_2 = new TreeNode(4);
        TreeNode *level22_2 = new TreeNode(7);
        root_2->left = level11_2; root_2->right = level12_2;
        level11_2->right = level21_2; level12_2->right = level22_2;

        TreeNode* ans = mergeTrees(root_1, root_2);
    }

    void test_searchBST() {
        TreeNode* root = new TreeNode(4);
        TreeNode* level11 = new TreeNode(2);
        TreeNode* level12 = new TreeNode(7);
        TreeNode* level21 = new TreeNode(1);
        TreeNode* level22 = new TreeNode(3);
        root->left = level11; root->right = level12;
        level11->left = level21; level11->right = level22;

        TreeNode* ans = searchBST(root, 2);
    }

    void test_isValidBST() {
        TreeNode* root = new TreeNode(5);
        TreeNode* level11 = new TreeNode(1);
        TreeNode* level12 = new TreeNode(4);
        TreeNode* level21 = new TreeNode(3);
        TreeNode* level22 = new TreeNode(6);
        root->left = level11; root->right = level12;
        level12->left = level21; level12->right = level22;

        cout << isValidBST(root) << endl;
    }

    void test_getMinimumDifference() {
        TreeNode* root = new TreeNode(4);
        TreeNode* level11 = new TreeNode(2);
        TreeNode* level12 = new TreeNode(6);
        TreeNode* level21 = new TreeNode(1);
        TreeNode* level22 = new TreeNode(3);
        root->left = level11; root->right = level12;
        level11->left = level21; level11->right = level22;
        
        cout << getMinimumDifference(root) << endl;
    }

    void test_findMode() {
        TreeNode* root = new TreeNode(1);
        TreeNode* level11 = new TreeNode(1);
        //TreeNode* level21 = new TreeNode(2);
        root->left = level11; 
        //level11->left = level21;

        vector<int> ans = findMode(root);
    }

    void test_lowestCommonAncestor() {
        TreeNode *root = new TreeNode(3);
        TreeNode *level_11 = new TreeNode(5);
        TreeNode *level_12 = new TreeNode(1);
        TreeNode *level_21 = new TreeNode(6);
        TreeNode *level_22 = new TreeNode(2);
        TreeNode *level_23 = new TreeNode(0);
        TreeNode *level_24 = new TreeNode(8);
        TreeNode *level_31 = new TreeNode(7);
        TreeNode *level_32 = new TreeNode(4);
        root->left = level_11; root->right = level_12;
        level_11->left = level_21; level_11->right = level_22;
        level_12->left = level_23; level_12->right = level_24;
        level_22->left = level_31; level_22->right = level_32;

        TreeNode* ans = lowestCommonAncestor(root, level_11, level_12);
    }

    void test_lowestCommonAncestorOfBST() {
        TreeNode *root = new TreeNode(6);
        TreeNode *level_11 = new TreeNode(2);
        TreeNode *level_12 = new TreeNode(8);
        TreeNode *level_21 = new TreeNode(0);
        TreeNode *level_22 = new TreeNode(4);
        TreeNode *level_23 = new TreeNode(7);
        TreeNode *level_24 = new TreeNode(9);
        TreeNode *level_31 = new TreeNode(3);
        TreeNode *level_32 = new TreeNode(5);
        root->left = level_11; root->right = level_12;
        level_11->left = level_21; level_11->right = level_22;
        level_12->left = level_23; level_12->right = level_24;
        level_22->left = level_31; level_22->right = level_31;

        //TreeNode* ans1 = lowestCommonAncestorOfBST(root, level_11,level_12);
        TreeNode* ans2 = lowestCommonAncestorOfBSTIteration(root, level_11, level_12);
    }

    void test_insertIntoBST() {
        TreeNode *root = new TreeNode(4);
        TreeNode *level_11 = new TreeNode(2);
        TreeNode *level_12 = new TreeNode(7);
        TreeNode *level_21 = new TreeNode(1);
        TreeNode *level_22 = new TreeNode(3);
        root->left = level_11; root->right = level_12;
        level_11->left = level_21; level_11->right = level_22;

        //TreeNode* ans1 = insertIntoBST(root, 5);
        TreeNode* ans2 = insertIntoBSTIteration(root, 5);

    }

    void test_deleteNode() {
        //TreeNode* root = new TreeNode(5);
        //TreeNode* level_11 = new TreeNode(3);
        //TreeNode* level_12 = new TreeNode(6);
        //TreeNode* level_21 = new TreeNode(2);
        //TreeNode* level_22 = new TreeNode(4);
        //TreeNode* level_23 = new TreeNode(7);
        TreeNode* root = new TreeNode(50);
        TreeNode* level_11 = new TreeNode(30);
        TreeNode* level_12 = new TreeNode(70);
        TreeNode* level_21 = new TreeNode(40);
        TreeNode* level_22 = new TreeNode(60);
        TreeNode* level_23 = new TreeNode(80);
        root->left = level_11; root->right = level_12;
        level_11->right = level_21; 
        level_12->left = level_22; level_12->right = level_23;

        //TreeNode* ans = deleteNodeTraversal(root, 3);
        TreeNode* ans = deleteNodeTraversal(root, 50);
    }

    void test_trimBST() {
        TreeNode* root = new TreeNode(3);
        TreeNode* level_11 = new TreeNode(0);
        TreeNode* level_12 = new TreeNode(4);
        TreeNode* level_31 = new TreeNode(1);
        TreeNode* level_41 = new TreeNode(2);
        root->left = level_11; root->right = level_12;
        level_11->left = level_31; level_31->left = level_41;

        TreeNode* ans = trimBST(root, 1, 3);
    }

    void test_sortedArrayToBST() {
        vector<int> nums = { -10,-3,0,5,9 };
        TreeNode* ans = sortedArrayToBST(nums);
    }

    void test_convertBST() {
        TreeNode* root = new TreeNode(4);
        TreeNode* level_11 = new TreeNode(1);
        TreeNode* level_12 = new TreeNode(6);
        TreeNode* level_21 = new TreeNode(0);
        TreeNode* level_22 = new TreeNode(2);
        TreeNode* level_23 = new TreeNode(5);
        TreeNode* level_24 = new TreeNode(7);
        TreeNode* level_31 = new TreeNode(3);
        TreeNode* level_32 = new TreeNode(8);
        root->left = level_11; root->right = level_12;
        level_11->left = level_21; level_11->right = level_22;
        level_12->left = level_23; level_12->right = level_24;
        level_22->right = level_31; level_24->right = level_32;

        //TreeNode* ans = convertBST(root);
        TreeNode* ans = convertBSTTraversal(root);
    }

}


//------------------ ������ ---------------------------
int main(int argc, char **argv){

    /* * * * * * * * * * ����һ���������ı�����ʽ * * * * * * * * * */
    // ��һ��
    // ��ȱ���֮�ݹ顢������ͳһ��ʽ����
    //testBinaryTree::test_preorderTraversal();       // 144. ��������ǰ�����
    //testBinaryTree::test_postorderTraversal();      // 145. �������ĺ������
    //testBinaryTree::test_inorderTraversal();        // 94. ���������������
    // �������
    //testBinaryTree::test_levelOrder();              // 102. �������Ĳ������
    //testBinaryTree::test_rightSideView();           // 199. ������������ͼ
    //testBinaryTree::test_averageOfLevels();         // 637. �������Ĳ�ƽ��ֵ
    //testBinaryTree::test_levelOrderinNTree();       // 429. N �����Ĳ������
    //testBinaryTree::test_largestValues();           // 515. ��ÿ�������������ֵ
    // 116. ���ÿ���ڵ����һ���Ҳ�ڵ�ָ��
    // 117.���ÿ���ڵ����һ���Ҳ�ڵ�ָ��II
    // 111.����������С���

    /* * * * * * * * * * �������������������� * * * * * * * * * */
    // �ڶ���
    //testBinaryTree::test_isSymmetric();             // 101. �Գƶ�����
    //testBinaryTree::test_isSameTree();              // 100. ��ͬ����
    //testBinaryTree::test_maxDepth();                // 104. ��������������
    //testBinaryTree::test_minDepth();                // 111. ����������С���
    //testBinaryTree::test_countNodes();              // 222. ��ȫ�������Ľڵ����
    //testBinaryTree::test_isBalanced();              // 110. ƽ�������
    // ������
    //testBinaryTree::test_binaryTreePaths();         // 257. ������������·��
    //testBinaryTree::test_sumOfLeftLeaves();         // 404. ��Ҷ��֮��
    //testBinaryTree::test_findBottomLeftValue();     // 513. �������½ǵ�ֵ
    //testBinaryTree::test_hasPathSumTraversal();     // 112. ·���ܺ�

    /* * * * * * * * * * �����������������޸��빹�� * * * * * * * * * */
    //testBinaryTree::test_invertTree();              // 226. ��ת������
    //testBinaryTree::test_buildTree();               // 106. �����������������й�������� & 105 ǰ��+����
    //testBinaryTree::test_constructMaximumBinaryTree(); // 654. ��������
    // ������
    //testBinaryTree::test_mergeTrees();              // 617. �ϲ�������

    /* * * * * * * * * * �����ģ������������������ * * * * * * * * * */
    //testBinaryTree::test_searchBST();               // 700. �����������е�����
    //testBinaryTree::test_isValidBST();              // 98.��֤����������
    //testBinaryTree::test_getMinimumDifference();    // 530. ��������������С���Բ�
    //testBinaryTree::test_findMode();                // 501. �����������е�����
    //testBinaryTree::test_convertBST();              // 538. �Ѷ���������ת��Ϊ�ۼ����������ܣ�

    /* * * * * * * * * * �����壺������������������ * * * * * * * * * */
    //testBinaryTree::test_lowestCommonAncestor();    // 236. �������������������
    // ������
    //testBinaryTree::test_lowestCommonAncestorOfBST(); // 235. �����������������������

    /* * * * * * * * * * ���������������������޸��빹�� * * * * * * * * * */
    //testBinaryTree::test_insertIntoBST();           // 701. �����������еĲ������
    //testBinaryTree::test_deleteNode();              // 450. ɾ�������������еĽڵ�
    //testBinaryTree::test_trimBST();                 // 669. �޼�����������
    //testBinaryTree::test_sortedArrayToBST();        //108. ����������ת��Ϊ����������

    system("pause");
}