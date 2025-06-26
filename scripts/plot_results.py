import matplotlib.pyplot as plt
import pandas as pd

# Load CSV
data = pd.read_csv("results/performance.csv")

# Plot throughput
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.plot(data["Concurrency"], data["RequestsPerSec"], marker='o', color='green')
plt.title("Throughput")
plt.xlabel("Concurrency")
plt.ylabel("Requests/sec")

# Plot latency
plt.subplot(1, 2, 2)
plt.plot(data["Concurrency"], data["AvgTimePerReq(ms)"], marker='x', color='red')
plt.title("Average Response Time")
plt.xlabel("Concurrency")
plt.ylabel("Time per request (ms)")

plt.tight_layout()
plt.savefig("results/graph.png")
plt.show()
