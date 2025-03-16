vector<int> nextGreater(vector<int>& v, int n) {
  stack<int> st;
  vector<int> res(n + 1, n + 1);
  for (int i = 1; i <= n; i++) {
    while (!st.empty() && v[st.top()] < v[i]) {
      res[st.top()] = i;
      st.pop();
    }
    st.push(i);
  }
  return res;
}

vector<int> prevGreater(vector<int>& v, int n) {
  stack<int> st;
  vector<int> res(n + 1, 0);
  for (int i = n; i >= 1; i--) {
    while (!st.empty() && v[st.top()] < v[i]) {
      res[st.top()] = i;
      st.pop();
    }
    st.push(i);
  }
  return res;
}