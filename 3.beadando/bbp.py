from decimal import Decimal, getcontext
import time

# Bailey-Borwein-Plouffe-formula


def seq_BBP(precision):
    getcontext().prec = precision
    return sum(1/Decimal(16)**k *
               (Decimal(4)/(8*k+1) -
                Decimal(2)/(8*k+4) -
                Decimal(1)/(8*k+5) -
                Decimal(1)/(8*k+6)) for k in range(precision))


def time_seq_BBP(precision):
    start_time = time.perf_counter()
    pi = seq_BBP(precision)
    end_time = time.perf_counter()
    return end_time - start_time, pi
