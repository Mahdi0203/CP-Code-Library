template<typename T>
struct SegmentTree {
public:
  SegmentTree(int n, vector<T>& arr, T neutral, function<T(T, T)> combine)
      : n(n), neutral(neutral), combine(combine) {
    segmentTree.resize(4 * (n + 1), neutral);
    build(1, 1, n, arr);
  }

  void update(int idx, T val) {
    update(1, 1, n, idx, val);
  }

  T query(int l, int r) {
    return query(1, 1, n, l, r);
  }

private:
  int n;
  T neutral;
  vector<T> segmentTree;
  function<T(T, T)> combine;

  inline int lc(int node) { return node * 2; }
  inline int rc(int node) { return node * 2 + 1; }

  void build(int node, int s, int e, vector<T>& arr) {
    if (s == e) {
      segmentTree[node] = arr[s];
      return;
    }

    int mid = (s + e) / 2;
    build(lc(node), s, mid, arr);
    build(rc(node), mid + 1, e, arr);
    segmentTree[node] = combine(segmentTree[lc(node)], segmentTree[rc(node)]);
  }

  void update(int node, int s, int e, int idx, T val) {
    if (idx < s || idx > e) return;

    if (s == e) {
      segmentTree[node] = val;
      return;
    }

    int mid = (s + e) / 2;
    update(lc(node), s, mid, idx, val);
    update(rc(node), mid + 1, e, idx, val);
    segmentTree[node] = combine(segmentTree[lc(node)], segmentTree[rc(node)]);
  }

  T query(int node, int s, int e, int l, int r) {
    if (l > e || r < s) return neutral;
    if (l <= s && e <= r) return segmentTree[node];

    int mid = (s + e) / 2;
    return combine(query(lc(node), s, mid, l, r), query(rc(node), mid + 1, e, l, r));
  }
};