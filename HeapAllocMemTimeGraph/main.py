import matplotlib.pyplot as plt
import csv

# Adjust file names as appropriate for your tests
files = {
    "C": "c_alloc_data.csv",
    "C++": "cpp_alloc_data.csv",
    "Rust": "rust_alloc_data.csv"
}

plt.figure(figsize=(10, 6))

for label, filename in files.items():
    sizes = []
    times = []
    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)  # Skip header
        for row in reader:
            sizes.append(int(row[0]))
            times.append(int(row[1]))
    plt.plot(sizes, times, label=label)

plt.xlabel("Heap Memory Allocated (bytes)")
plt.ylabel("Average Allocation Time (ns)")
plt.title("Heap Memory Allocation Time vs. Size")
plt.legend()
plt.grid(True)
plt.show()
