import matplotlib.pyplot as plt
import sys
import math
from montecarlo import sequential, parallel
from decimal import Decimal
from decimal import getcontext
from bbp import time_seq_BBP


def plot_results(seq_time, par_time, seq_pi, par_pi, seqbbp_time, seqbbp_pi, num_processes):
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 5))

    ax1.bar(['Sequential', f'Parallel ({num_processes} processes)', 'Sequential BBP'], [
            seq_time, par_time, seqbbp_time])
    ax1.set_title('Monte Carlo módszer - Futási idő')
    ax1.set_ylabel('Idő (s)')

    pi_errors = [abs(seq_pi - 3.141592653589793), abs(par_pi -
                                                      3.141592653589793), abs(float(seqbbp_pi) - 3.141592653589793)]
    ax2.bar(
        ['Sequential', f'Parallel ({num_processes} processes)', 'Sequential BBP'], pi_errors)
    ax2.set_title('Monte Carlo módszer - Pontosság')
    ax2.set_ylabel('Hiba')

    plt.tight_layout()
    plt.savefig('montecarlo_bbp.png')  # save the plot as a PNG file
    plt.show()


def avg(lst):
    return sum(lst) / len(lst)


if __name__ == '__main__':
    num_samples = 10**7  # Pontok száma
    num_processes = int(sys.argv[1]) if len(sys.argv) > 1 else 2  # Magok száma
    range_value = int(sys.argv[2]) if len(sys.argv) > 2 else 3  # Range értéke

    seq_times = []
    par_times = []
    seq_pis = []
    par_pis = []

    for i in range(range_value):
        seq_times.append(0)
        par_times.append(0)
        seq_pis.append(0)
        par_pis.append(0)

        seq_times[i], seq_pis[i] = sequential(
            num_samples)  # Szekvenciális futási idő
        par_times[i], par_pis[i] = parallel(
            num_samples, num_processes)  # Párhuzamos futási idő

        # Szekvenciál
        print(
            f"{i+1}Sequential Time: {seq_times[i]:.6f}s, Pi: {seq_pis[i]:.50f}")
        # Párhuzamos futás adatainak kiíratása
        print(
            f"{i+1}Parallel Time: {par_times[i]:.6f}s, Pi: {par_pis[i]:.50f}")

    # Szekvenciál
    seqbbp = time_seq_BBP(50)

    print(f"Sequential BBP Time:{seqbbp[0]:.6f}s, Pi: {seqbbp[1]}")
    print(
        f"AVG Sequential Time: {avg(seq_times):.6f}s, Pi: {avg(seq_pis):.6f}")
    # Párhuzamos futás adatainak kiíratása
    print(f"AVG Parallel Time: {avg(par_times):.6f}s, Pi: {avg(par_pis):.6f}")
    # Eredmények ábrázolása
    plot_results(avg(seq_times), avg(par_times), avg(
        seq_pis), avg(par_pis), seqbbp[0], seqbbp[1], num_processes)
