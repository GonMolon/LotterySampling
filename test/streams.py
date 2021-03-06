import itertools
import math
import numpy as np
from abc import abstractmethod
from io import TextIOWrapper
from sorted_list import SortedList


class Stream():

    def __init__(self, length, save=True):
        self.length = length
        self.N = 0
        self.n = 0
        self.save = save
        self.elements = SortedList()


    def __iter__(self):
        return self


    def __next__(self):
        self.N += 1
        if self.N > self.length:
            raise StopIteration
        element = self.next_element()
        if self.save:  # To speed-up tests in which it is not necessary to check accuracy
            self.elements.process_element(element)
            self.n = self.elements.size()
        return element


    @abstractmethod
    def next_element(self):
        pass


    def top_k_query(self, k):
        return [(str(id), count/self.N) for id, count in itertools.islice(iter(self.elements), k)]


    def frequent_query(self, freq):
        return [(str(id), count/self.N) for id, count in itertools.takewhile(lambda element: element[1] >= math.ceil(freq * self.N), iter(self.elements))]


def chunk_stream(stream, chunk_size):
    it = iter(stream)
    while True:
        chunk = list(itertools.islice(it, chunk_size))
        if len(chunk) > 0:
            yield chunk
        else:
            return None


class MultiZipf(Stream):

    def __init__(self, length, alpha=1.5, segments=2, offset=10000, seed=None, save=True):
        super().__init__(length, save)
        self.alpha = alpha
        self.segments = segments
        self.offset = offset
        np.random.seed(seed)


    def next_element(self):
        element = np.random.zipf(self.alpha)
        element += self.offset * (self.N // (self.length / self.segments))
        return int(element)


class Zipf(MultiZipf):

    def __init__(self, length, alpha=1.5, seed=None, save=True):
        super().__init__(length, alpha=alpha, segments=1, seed=seed, save=save)


class Uniform(Stream):

    def __init__(self, length, n_max, seed=None, save=True):
        super().__init__(length, save)
        self.n_max = n_max
        np.random.seed(seed)


    def next_element(self):
        return np.random.randint(0, self.n_max)


class Unequal(Stream):

    def __init__(self, length, alpha, beta, seed=None, save=True):
        super().__init__(length, save)
        data = np.zeros(length, dtype=int)
        for i in range(alpha):
            for j in range(beta):
                data[i*beta + j] = i
        for i in range(alpha * beta, length):
            data[i] = i - alpha * (beta - 1)
        np.random.seed(seed)
        self.data = iter(np.random.permutation(data))


    def next_element(self):
        return next(self.data)


class File(Stream):

    def __init__(self, file_path, length=math.inf, shuffle=False, repetitions=1, seed=None, save=True):
        if shuffle or repetitions > 1:
            self.data = []
            with open(file_path, 'r') as file:
                for line in file:
                    element = line[:-1]
                    self.data.append(element)
            self.data *= repetitions
            length = min(len(self.data), length)
            if shuffle:
                np.random.seed(seed)
                self.data = np.random.permutation(self.data)
        else:
            with open(file_path, 'r') as file:
                length = min(sum(1 for _ in file), length)
            self.data = open(file_path, 'r')
        super().__init__(length, save)


    def next_element(self):
        if isinstance(self.data, TextIOWrapper):
            element = self.data.readline()[:-1]
            if element == '':
                raise StopIteration
            return element
        else:
            if self.N == len(self.data):
                raise StopIteration
            return self.data[self.N]


class ZipfNoiseZipf(Stream):

    def __init__(self, length, alpha=1.5, noise=0.3, offset=10000, seed=None, save=True):
        super().__init__(length, save)
        self.alpha = alpha
        self.noise = noise
        self.offset = offset
        np.random.seed(seed)


    def next_element(self):
        if self.N < self.length * (1 - self.noise) // 2:
            return int(np.random.zipf(self.alpha))
        elif self.N < self.length - self.length * (1 - self.noise) // 2:
            return self.N
        else:
            return int(np.random.zipf(self.alpha) + self.offset)



class ESA(Stream):

    def __init__(self, length, seed=None, save=True):
        super().__init__(length, save)
        np.random.seed(seed)


    def next_element(self):
        if self.N < self.length // 2:
            return self.N // 2
        else:
            return self.length