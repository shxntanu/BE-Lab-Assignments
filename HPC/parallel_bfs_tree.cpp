#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

class TreeNode {
public:
  int val;
  TreeNode *right, *left;

  TreeNode(int v) {
    this->val = v;
    left = right = NULL;
  }
};

class BinaryTree {
public:
  TreeNode *root;

  BinaryTree(int rootVal) { this->root = new TreeNode(rootVal); }

  void parallel_bfs() {
    if (!root)
      return;

    cout << "Parallel BFS of Tree: " << endl;
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
      int level_size = q.size();

#pragma omp parallel for
      for (int i = 0; i < level_size; i++) {
        TreeNode *node = NULL;

#pragma omp critical
        {
          if (!q.empty()) {
            node = q.front();
            q.pop();
            cout << node->val << " ";
          }
        }

#pragma omp critical
        {
          if (node->left)
            q.push(node->left);
          if (node->right)
            q.push(node->right);
        }
      }
    }
    cout << endl;
  }

  void parallel_dfs() {
    if (!root)
      return;

    cout << "Parallel DFS of Tree: " << endl;
    stack<TreeNode *> s;
    s.push(root);

#pragma omp parallel
    {
      while (!s.empty()) {
        TreeNode *node = NULL;

#pragma omp critical
        {
          if (!s.empty()) {
            node = s.top();
            s.pop();
            cout << node->val << " ";
          }
        }

#pragma omp parallel sections
        {
#pragma omp section
          {
            if (node->left) {
#pragma omp critical
              s.push(node->left);
            }
          }

#pragma omp section
          {
            if (node->right) {
#pragma omp critical
              s.push(node->right);
            }
          }
        }
      }
    }
    cout << endl;
  }
};

int main() {
  BinaryTree tree(1);
  tree.root->left = new TreeNode(2);
  tree.root->right = new TreeNode(3);
  tree.root->left->left = new TreeNode(4);
  tree.root->left->right = new TreeNode(5);
  tree.root->right->left = new TreeNode(6);
  tree.root->right->right = new TreeNode(7);

  tree.parallel_bfs();
  tree.parallel_dfs();

  return 0;
}
