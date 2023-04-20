import csv
import matplotlib.pyplot as plt

filename = "matrix_mult_times.csv"

trials = []
serial_times = []
parallel_times = []

with open(filename) as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        trials.append(int(row['trial']))
        serial_times.append(float(row['serial_time']))
        parallel_times.append(float(row['parallel_time']))

plt.plot(trials, serial_times, label="Serial", marker='o')
plt.plot(trials, parallel_times, label="Parallel", marker='x')
plt.xlabel("Trial")
plt.ylabel("Time (seconds)")
plt.title("Matrix Multiplication Times")
plt.legend()
plt.savefig("matrix_mult_times.png")
plt.show()
