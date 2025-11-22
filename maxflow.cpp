#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits> // Để sử dụng INT_MAX

using namespace std;

// Định nghĩa số lượng đỉnh tối đa (có thể thay đổi tùy bài toán)
const int MAX_V = 100;

// Ma trận chứa sức chứa (capacity) và lưu trạng thái đồ thị dư
// rGraph[u][v] sẽ tương ứng với (capacity[u][v] - flow[u][v]) trong mã giả
int rGraph[MAX_V][MAX_V];
int V; // Số lượng đỉnh thực tế

// 1. Hàm BFS để tìm đường tăng luồng ngắn nhất từ s đến t
// Trả về true nếu tìm thấy đường đi, false nếu không
bool bfs(int s, int t, vector<int>& parent) {
    // Đánh dấu tất cả các đỉnh là chưa thăm
    vector<bool> visited(V, false);
    
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            // Nếu chưa thăm v VÀ còn khả năng đi qua cạnh u-v (sức chứa dư > 0)
            if (!visited[v] && rGraph[u][v] > 0) {
                // Nếu tìm thấy đích đến t
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                // Ghi nhận đường đi và đẩy vào hàng đợi
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    // Không tìm thấy đường đi đến t
    return false;
}

// Hàm chính Edmonds-Karp
int edmondsKarp(int s, int t) {
    int u, v;
    int max_flow = 0; // Khởi tạo luồng cực đại = 0
    
    // Mảng parent để lưu vết đường đi tìm được bởi BFS
    vector<int> parent(V);

    // Vòng lặp chính: Lặp lại chừng nào còn đường tăng luồng từ s đến t
    // (Tương ứng: While True ... If parent[t] == NULL: Break)
    while (bfs(s, t, parent)) {
        
        // 2. Tính lượng luồng có thể tăng thêm (path_flow)
        int path_flow = INT_MAX;
        
        // Duyệt ngược từ t về s để tìm cạnh có sức chứa dư nhỏ nhất trên đường đi
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // 3. Cập nhật luồng trên đồ thị dư
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            
            // Giảm sức chứa cạnh xuôi (tương đương flow[u][v] += path_flow)
            rGraph[u][v] -= path_flow;
            
            // Tăng sức chứa cạnh ngược (tương đương flow[v][u] -= path_flow)
            rGraph[v][u] += path_flow;
        }

        // Cộng dồn vào luồng cực đại
        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    // Tối ưu nhập xuất
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int E; // Số cạnh
    int s, t; // Đỉnh nguồn (source) và đỉnh đích (sink)

    cout << "Nhap so dinh (V) va so canh (E): ";
    cin >> V >> E;

    cout << "Nhap dinh Nguon (s) va dinh Dich (t): ";
    cin >> s >> t;

    // Khởi tạo đồ thị với giá trị 0
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            rGraph[i][j] = 0;
        }
    }

    cout << "Nhap danh sach canh (u v capacity):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;
        // Đồ thị có hướng: từ u đến v có sức chứa cap
        rGraph[u][v] = cap; 
    }

    cout << "---------------------------------" << endl;
    cout << "Max Flow (Luong cuc dai): " << edmondsKarp(s, t) << endl;

    return 0;
}
