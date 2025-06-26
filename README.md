# 🚀 Multithreaded Web Server in C++17

A high-performance multithreaded web server built in C++17 using POSIX sockets, a thread pool, and asynchronous logging. Designed to handle multiple concurrent connections efficiently and serve static HTML content.

---

## 📁 Project Structure
```
.
├── include/         # ThreadPool and Logger headers
├── src/             # Server source code
├── static/          # HTML files served (index.html)
├── logs/            # Server request logs
├── test/            # ApacheBench benchmarking script
├── scripts/         # Python plotting script
├── results/         # Benchmark results and graph
├── Makefile         # Build instructions
├── README.md        # Project overview and usage
```

---

## ⚙️ Build & Run

### 📦 Requirements:
- g++ (C++17)
- make
- ab (ApacheBench)
- Python3 + matplotlib + pandas

### 🔨 Build Server:
```bash
make
```

### ▶️ Run Server:
```bash
./server
```
---

## 🧪 Benchmark with ApacheBench

### 📊 Run Benchmark Script:
```bash
chmod +x test/performance_test.sh
./test/performance_test.sh
```
This will:
- Run tests with concurrency levels [10, 50, 100, 200]
- Send 1000 requests per level
- Save metrics to `results/performance.csv`

### 📈 Plot Graph:
```bash
python3 scripts/plot_results.py
```
Generates: `results/graph.png`

---

## 📈 Sample Output Table (CSV)
| Concurrency | Requests | Requests/sec | Avg Time/request (ms) |
|-------------|----------|---------------|------------------------|
| 10          | 1000     | 310.82        | 32.17                  |
| 50          | 1000     | 301.14        | 166.04                 |
| 100         | 1000     | 319.07        | 313.41                 |
| 200         | 1000     | 326.60        | 612.37                 |

---

## 🧠 Features
- ✅ POSIX socket programming
- ✅ Fixed-size thread pool
- ✅ Thread-safe logging to `logs/server.log`
- ✅ Serves static HTML from `static/`
- ✅ Performance-tested with ApacheBench

---

## 📄 Performance Highlights
- **Peak Throughput:** ~326 requests/sec @ 200 clients
- **Avg Response Time:** ~32 ms under 10-client load
- **Scales up to 200 concurrent clients with ~600ms latency**

---

## 🧑‍💻 Author
**Mihir Patel**  