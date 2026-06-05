# Tower of Hanoi  
The Tower of Hanoi is a classic mathematical puzzle that is widely used to teach recursion, problem-solving, and algorithmic thinking in computer science. Although the puzzle appears simple at first glance, it reveals powerful concepts that form the foundation of many programming techniques.

## Rules
The Tower of Hanoi puzzle has three pegs **A**, **B**, **C** and n disks of different sizes stacked on peg **A** (largest at bottom, smallest at top).

Move all disks from peg A to peg C using peg B as auxiliary, following these rules:
+ Move only one disk at a time  
+ Only the topmost disk of any peg can be moved  
+ A larger disk may never be placed on top of a smaller disk    

## The Recursive Strategy
If you try to map out every single individual move for 4, 5, or 6 disks in your head, your brain will quickly freeze up. __The secret to cracking this puzzle and mastering recursion in general is to trust the function.__   

Instead of thinking about individual disk moves, think about moving sub-towers.  

Imagine you have a tower of **n** disks on **Peg A**, and you want to move them to **Peg C.** You can conceptually break this massive task down into exactly three steps:  
+ **Step 1:** Move the top **(n - 1)** disks out of the way. Shift them from the **Source (A)** to the **Auxiliary (B)** peg.  
+ **Step 2:** Move the single remaining largest disk **(the n-th disk)** directly from **Source (A)** to **Destination (C).**  
+ **Step 3:** Take those **(n - 1)** disks you left sitting on **Auxiliary (B)** and move them on top of the largest disk on **Destination (C).**  

```
[Start: n disks on A] 
       │
       ▼
[Step 1: Move n-1 disks from A to B]
       │
       ▼
[Step 2: Move disk n from A to C]
       │
       ▼
[Step 3: Move n-1 disks from B to C]
```
### Why Recursion Works
Consider **four** disks. To move all four disks:
1. Move the top three disks out of the way.
2. Move the fourth (largest) disk.
3. Move the three disks back on top of it.

But moving three disks requires solving another Tower of Hanoi problem.  

Similarly, moving three disks requires solving the problem for two disks.  
The process continues until only one disk remains, which can be moved directly.

This repeated breakdown into smaller identical problems is what makes recursion such a natural solution.

## Mathematical Analysis
One interesting question is: **What is the minimum number of moves required?**

> Let:  
> T(n) = minimum moves needed for n disks
>
> From the recursive process:  
> T(n) = T(n - 1) + 1 + T(n - 1)  
> T(n) = 2 * T(n − 1) + 1
> 
> This recurrence relation can be expanded:
> 
> T(1) = 1  
> T(2) = 3  
> T(3) = 7  
> T(4) = 15  
> T(5) = 31  
> 
> The general formula becomes: **T(n) = 2ⁿ − 1**  
> :D

This formula gives the minimum number of moves required to solve the puzzle.

## Time & Space Complexity
Since the number of moves is: **2ⁿ − 1**.  
> The time complexity of the Tower of Hanoi algorithm is:  **O(2ⁿ)**  
> The space complexity is: **O(n)**

## Source Code
**Classic Problem :** [Tower of Hanoi](https://repovive.com/problems/classics/22)

```C++
#include<bits/stdc++.h>
using namespace std;

#define bug(a) cout << #a << " : " << a <<endl;
using ll = long long;

vector<array<char,2>> moves;
void TowerOfHanoi(int n, char src, char des, char aux) {
  if ( n == 1 ) {
    moves.push_back({src, des});
    return;
  }

  TowerOfHanoi(n - 1, src, aux, des);
  moves.push_back({src, des});
  TowerOfHanoi(n - 1, aux, des, src);
}

void solve ( int cs ){
  int n;  cin >> n;

  moves.clear();
  TowerOfHanoi(n, 'A', 'C', 'B');

  for (auto a : moves) cout << a[0] << a[1] << '\n';
}

int main () {

  ios::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int testCase = 1, cs = 0;
  //cin >> testCase;

  while(testCase--){
    solve( ++cs );
  }
  return 0;
}
```

**CF Problem :** [Magical Tiered Cake](https://codeforces.com/contest/2232/problem/D)  
**TAG :** `constructive algorithms` `dfs and similar`  `dp` `greedy` `*2000`

```C++
#include<bits/stdc++.h>
using namespace std;

#define bug(a) cout << #a << " : " << a <<endl;
using ll = long long;

int a[25];
vector<array<int,3>> moves;

void TowerOfHanoi(int n, int src, int des, int aux) {
  if ( n < 1 ) return;

  if ( a[n] == 0 ) {
    TowerOfHanoi(n - 1, src, aux, des);
    moves.push_back({n, src, des});
    TowerOfHanoi(n - 1, aux, des, src);
  }
  else {
    TowerOfHanoi(n - a[n] - 1, src, aux, des);
    moves.push_back({n, src, des});
    TowerOfHanoi(n - a[n] - 1, aux, src, des);
    TowerOfHanoi(n - 1, src, des, aux);
  }
}

void solve ( int cs ){
  int n;  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  for (int i = 1; i <= n; i++) {
    if ( a[i] >= i ) {
      cout << "NO" << '\n';
      return;
    }
  }

  moves.clear();
  TowerOfHanoi(n, 1, 3, 2);

  cout << "YES" << '\n';
  cout << (int)moves.size() << '\n';
  for (auto x : moves) cout << x[0] << ' ' << x[1] << ' ' << x[2] << '\n';

}

int main () {

  ios::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int testCase = 1, cs = 0;
  cin >> testCase;

  while(testCase--){
    solve( ++cs );
  }
  return 0;
}
```


#### 5 June, 2026