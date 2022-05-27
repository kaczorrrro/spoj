#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

typedef struct node
{
  int val;
  struct node* left;
  struct node* right;
  int ht;
} node;

// edge case: root change
int max_w = 80;

int depth(node* n) {
  if (!n) return 0;
  return std::max(depth(n->left), depth(n->right)) + 1;
}

bool cmp_val_eq(node* n0, node* n1) {
  if (!n0 && !n1) return true;
  if (!n0 | !n1)  return false;
  if (n0->val != n1->val) return false;
  return cmp_val_eq(n0->left, n1->left) && cmp_val_eq(n0->right, n1->right);
}

node* clone(node* n) {
  if (!n) return nullptr;
  node* n_copy = new node();
  n_copy->val = n->val;
  n_copy->left = clone(n->left);
  n_copy->right = clone(n->right);
  return n_copy;
}

node* follow(node* root, int pos) {
  std::vector<bool> path_l;
  int lastpos = pos;
  pos /= 2; // Go to parent
  while (pos > 0) {
    path_l.push_back(pos * 2 == lastpos);
    lastpos = pos;
    pos /= 2;
  }
  node* cur = root;
  for (auto it = path_l.rbegin(); it != path_l.rend() && cur; ++it)
    cur = (*it) ? cur->left : cur->right;

  return cur;
}

void print(node* root) {
  auto is_pow_2 = [](int i){
    return (i & (i - 1)) == 0;
  };
  auto print_node = [](node* n, int width){
    if (n) {
      if (isalpha(n->val))
        std::cout << std::setw(width / 2) << char(n->val) << std::string(width/2, ' ');
      else
        std::cout << std::setw(width / 2) << n->val << std::string(width/2, ' ');
    } else {
      std::cout << std::string(width, ' ');
    }
  };

  int num_levels = depth(root);
  int num_elems = (1 << num_levels) - 1;

  int width = 1 << (num_levels + 1);
  for (int i = 0; i < num_elems; i++) {
    node* node = follow(root, i + 1);
    print_node(node, width);
    if (is_pow_2(i + 2)) {
      width /= 2;
      std::cout << std::endl;
    }
  }
}



void rotate_left(node* root) {
  std::swap(root->val, root->right->val);
  std::swap(root->left, root->right);
  std::swap(root->right, root->left->right);
  std::swap(root->left->right, root->left->left);
}

void rotate_right(node* root) {
  std::swap(root->val, root->left->val);
  std::swap(root->right, root->left);
  std::swap(root->left, root->right->left);
  std::swap(root->right->left, root->right->right);
}

void rotate_left_right(node* root) {
  auto l = [root](){ return root->left; };
  auto lr = [root](){ return root->left->right; };
  auto ll = [root](){ return root->left->left; };

  std::swap(l()->val,   lr()->val);
  std::swap(l()->left,  l()->right);
  std::swap(l()->right, ll()->right);
  std::swap(ll()->left, ll()->right);

  std::swap(l()->val, root->val);
  std::swap(l()->left, root->right);
  std::swap(l()->left, l()->right);
  std::swap(root->left, root->right);
}

void rotate_right_left(node* root) {
  auto r  = [root](){ return root->right; };
  auto rr = [root](){ return root->right->right; };
  auto rl = [root](){ return root->right->left; };

  std::swap(r()->val,    rl()->val);
  std::swap(r()->right,  r()->left);
  std::swap(r()->left,   rr()->left);
  std::swap(rr()->right, rr()->left);

  std::swap(r()->val, root->val);
  std::swap(r()->right, root->left);
  std::swap(r()->right, r()->left);
  std::swap(root->right, root->left);
}

int calculate_balanance_factor(node* n) {
  int lht = n->left ? n->left->ht : -1;
  int rht = n->right ? n->right->ht : -1;
  int balance_factor = lht - rht;
  return balance_factor;
}

int calculate_ht(node* n) {
  int lht = n->left ? n->left->ht : -1;
  int rht = n->right ? n->right->ht : -1;
  return 1 + std::max(lht, rht);
}

void balance_tree(node* n) {
  int balance_factor = calculate_balanance_factor(n);
  bool rot = false;
  if (balance_factor < -1) {
    int bf = calculate_balanance_factor(n->right);
    if (bf <= 0) rotate_left(n);
    else rotate_right_left(n);
    rot = true;
  } else if (balance_factor > 1) {
    int bf = calculate_balanance_factor(n->left);
    if (bf >= 0) rotate_right(n);
    else rotate_left_right(n);
    rot = true;
  }

  if (rot) {
    n->left->ht = calculate_ht(n->left);
    n->right->ht = calculate_ht(n->right);
  }
  n->ht = calculate_ht(n);
}

node* insert(node * root, int val)
{
  node* new_node = new node();
  new_node->val = val;
  new_node->ht = 0;
  if (!root) {
    return new_node;
  }

  node* cur = root;
  std::vector<node*> path;
  while (cur != new_node) {
    path.push_back(cur);
    if (val < cur->val) {
      if (cur->left) cur = cur->left;
      else cur->left = new_node;
    }
    else {
      if (cur->right) cur = cur->right;
      else cur->right = new_node;
    }
  }
  for (auto it = path.rbegin(); it != path.rend(); ++it)
    balance_tree(*it);
  return root;
}


node* new_node(int val, node* l_child = nullptr, node* r_child = nullptr) {
  node* n = new node();
  n->val = val;
  n->left = l_child;
  n->right = r_child;
  return n;
}



void test_rotate_left_right() {
  node* root =
      new_node(5,
          new_node(3,
              new_node('A'),
              new_node(4, new_node('B'), new_node('C'))),
          new_node('D'));
  node* target =
      new_node(4,
          new_node(3, new_node('A'), new_node('B')),
          new_node(5, new_node('C'), new_node('D')));
  rotate_left_right(root);
  bool eq = cmp_val_eq(root, target);
  if (!eq) {
    throw std::logic_error("Test failed");
  }
}

void test_rotate_right_left() {
  node* root =
      new_node(3,
          new_node('A'),
          new_node(5,
              new_node(4, new_node('B'), new_node('C')),
              new_node('D')));
  print(root);

  node* target =
      new_node(4,
          new_node(3, new_node('A'), new_node('B')),
          new_node(5, new_node('C'), new_node('D')));
  rotate_right_left(root);
  print(root);
  bool eq = cmp_val_eq(root, target);
  if (!eq) {
    throw std::logic_error("Test failed");
  }
}

void test_rotate_left() {
  node* root = new_node('X',
      new_node(1),
      new_node('Z', new_node(23), new_node(4)));
  node* target = new_node('Z',
      new_node('X', new_node(1), new_node(23)),
      new_node(4));
  rotate_left(root);
  print(root);
  bool eq = cmp_val_eq(root, target);
  if (!eq) {
    throw std::logic_error("Test failed");
  }
}


void test_rotate_right() {
  node* root = new_node('X',
      new_node('Z', new_node(4), new_node(23)),
      new_node(1)
  );
  node* target = new_node('Z',
      new_node(4),
      new_node('X', new_node(23), new_node(1))
  );
  rotate_right(root);
  print(root);
  bool eq = cmp_val_eq(root, target);
  if (!eq) {
    throw std::logic_error("Test failed");
  }
}

void validate_ht_and_balance(node* root) {
  if (!root) return;
  if (root->ht != calculate_ht(root))
    throw std::logic_error("Invalid ht");
  int b = calculate_balanance_factor(root);
  if (b < -1 || b > 1)
    throw std::logic_error("Imbalance!");
  validate_ht_and_balance(root->left);
  validate_ht_and_balance(root->right);
}

void validate_tree(node* root) {
  validate_ht_and_balance(root);
}

void run_fuzzer_validator() {
  node* root = nullptr;
  std::mt19937 engine;
  std::uniform_int_distribution<int> dist (0, 10000);
  for (int insert_i = 0; insert_i < 100; insert_i++) {
    int value = dist(engine);
    // Additional loop to introduce imbalance
    for (int i = 0, n = dist(engine) % 4 + 1; i < n; i++) {
//    print(root);
//    std::cout << "Inserting " << value << std::endl;
      root = insert(root, value);
      validate_ht_and_balance(root);
      value = value + (insert_i % 2 == 0 ? 1 : -1);
    }
  }
  print(root);

}


int main() {
  test_rotate_left_right();
  test_rotate_right_left();
  test_rotate_left();
  test_rotate_right();
  run_fuzzer_validator();
}