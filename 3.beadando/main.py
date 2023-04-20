import random
import time
import multiprocessing as mp
import matplotlib.pyplot as plt

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


if __name__ == '__main__':
    num_samples = 10**7  # Pontok száma
    num_processes = 2  # Magok száma

    seq_time, seq_pi = sequential(num_samples)  # Szekvenciális futási idő
    par_time, par_pi = parallel(
        num_samples, num_processes)  # Párhuzamos futási idő

    # Szekvenciális futás adatainak kiíratása
    print(f"Sequential Time: {seq_time:.6f}s, Pi: {seq_pi:.6f}")
    plt.bar(['Sequential', f'Parallel ({num_processes} processes)'], [
        seq_time, par_time])
    plt.title('Monte Carlo módszer')
    plt.ylabel('Time (s)')
    plt.savefig('montecarlo.png')  # save the plot as a PNG file
    plt.show()
