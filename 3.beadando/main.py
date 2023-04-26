import random
import time
import multiprocessing as mp
import matplotlib.pyplot as plt
import sys

# A pi értékének kiszámolása


def calculate_pi(num_samples):
    count = 0
    for i in range(num_samples):
        # x,y koordináta véletlenszerű generálása 0 és 1 között
        x = random.uniform(0, 1)
        y = random.uniform(0, 1)
        if x**2 + y**2 < 1:  # Ha a pont a körön belül van
            count += 1  # Növeljük az összesített pontok számát
    return 4 * count / num_samples  # Pi értékének kiszámítása

# Szekvenciális számítás


def sequential(num_samples):
    start_time = time.time()
    pi = calculate_pi(num_samples)
    end_time = time.time()
    return end_time - start_time, pi

# Párhuzamos számítás


def parallel(num_samples, num_processes):
    start_time = time.time()
    # Process pool létrehozása a megadott processzorok számával
    pool = mp.Pool(num_processes)
    results = pool.map(
        calculate_pi, [num_samples // num_processes] * num_processes)  # Az egyes processzorokon végrehajtott számításokat az eredmények listába mentjük
    # A pi értékének átlaga a párhuzamosan futtatott processzorok eredményeiből
    pi = sum(results) / num_processes
    end_time = time.time()
    return end_time - start_time, pi


def plot_results(seq_time, par_time, seq_pi, par_pi, num_processes):
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 5))

    ax1.bar(['Sequential', f'Parallel ({num_processes} processes)'], [
            seq_time, par_time])
    ax1.set_title('Monte Carlo módszer - Futási idő')
    ax1.set_ylabel('Idő (s)')

    pi_errors = [abs(seq_pi - 3.141592653589793),
                 abs(par_pi - 3.141592653589793)]
    ax2.bar(['Sequential', f'Parallel ({num_processes} processes)'], pi_errors)
    ax2.set_title('Monte Carlo módszer - Pontosság')
    ax2.set_ylabel('Hiba')

    plt.tight_layout()
    plt.savefig('montecarlo.png')  # save the plot as a PNG file
    plt.show()


if __name__ == '__main__':
    num_samples = 10**7  # Pontok száma
    num_processes = int(sys.argv[1]) if len(sys.argv) > 1 else 2  # Magok száma

    seq_time, seq_pi = sequential(num_samples)  # Szekvenciális futási idő
    par_time, par_pi = parallel(
        num_samples, num_processes)  # Párhuzamos futási idő

    # Szekvenciál
    print(f"Sequential Time: {seq_time:.6f}s, Pi: {seq_pi:.6f}")
    # Párhuzamos futás adatainak kiíratása
    print(f"Parallel Time: {par_time:.6f}s, Pi: {par_pi:.6f}")

    # Eredmények ábrázolása
    plot_results(seq_time, par_time, seq_pi, par_pi, num_processes)
