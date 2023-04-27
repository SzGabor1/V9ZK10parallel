import random
import time
import multiprocessing as mp


class MonteCarlo:
    def __init__(self, num_samples):
        self.num_samples = num_samples

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
    # várni kell, hogy ne ugyan azok a random számok generálódjanak
    time.sleep(0.001)
    # A pi értékének átlaga a párhuzamosan futtatott processzorok eredményeiből
    pi = sum(results) / num_processes
    end_time = time.time()
    return end_time - start_time, pi
