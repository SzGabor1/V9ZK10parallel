import os
import sys
import matplotlib.pyplot as plt


def parse_output_file(file_name):
    results = []
    with open(file_name, "r") as file:
        lines = file.readlines()
        for i in range(0, len(lines), 6):
            n = int(lines[i].split()[2])
            sequential_time = float(lines[i + 1].split()[-2])
            parallel_time = float(lines[i + 2].split()[-2])
            speedup_sp = float(lines[i + 3].split()[-1])
            parallel_block_time = float(lines[i + 4].split()[-2])
            speedup_sb = float(lines[i + 5].split()[-1])
            results.append((n, sequential_time, parallel_time,
                           speedup_sp, parallel_block_time, speedup_sb))
    return results


def plot_results(results):
    matrix_sizes, sequential_times, parallel_times, speedups_sp, parallel_block_times, speedups_sb = zip(
        *results)

    fig, ax1 = plt.subplots()

    ax1.set_xlabel("Matrix size")
    ax1.set_ylabel("Time (seconds)")
    ax1.plot(matrix_sizes, sequential_times,
             label="Sequential", marker='o', color='b')
    ax1.plot(matrix_sizes, parallel_times,
             label="Parallel", marker='o', color='g')
    ax1.plot(matrix_sizes, parallel_block_times,
             label="Parallel with blocks", marker='o', color='r')
    ax1.tick_params(axis='y', labelcolor='b')
    ax1.legend(loc="upper left")

    # ax2 = ax1.twinx()
    # ax2.set_ylabel("Speedup")
    # ax2.plot(matrix_sizes, speedups_sp,
    #          label="Speedup (sequential-parallel)", marker='o', color='g')
    # ax2.plot(matrix_sizes, speedups_sb,
    #          label="Speedup (sequential-block)", marker='o', color='r')
    # ax2.tick_params(axis='y', labelcolor='r')
    # ax2.legend(loc="upper right")

    fig.tight_layout()
    plt.savefig('matrix_mult.png')
    plt.show()


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <output_file>")
        sys.exit(1)

    output_file = sys.argv[1]
    results = parse_output_file(output_file)
    plot_results(results)
