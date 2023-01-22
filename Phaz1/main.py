from multiprocessing import Process, Value, Array, Queue
from time import sleep

def lock_process(id, q, pn):
    if any(pn):
        q.put(id)
        return False
    pn[id] = True
    return pn[id]

def free_process(id, q, pn):
    pn[id] = False
    if not q.empty():
        pn[q.get()] = True

def add(num, value, lock, release, q, pn):
    tmp = 0
    while True:
        while lock(0, q, pn):
            print('add')
            num.value += value
            tmp = num.value
            sleep(1)
            release(0, q, pn)
        if tmp != num.value:
            print("Process conflict")


def sub(num, value, lock, release, q, pn):
    tmp = 0
    while True:
        while lock(1, q, pn):
            print('sub')
            num.value += value
            tmp = num.value
            sleep(1.5)
            release(1, q, pn)
        if tmp != num.value:
            print("Process conflict")


def mul(num, value, lock, release, q, pn):
    tmp = 0
    while True:
        while lock(2, q, pn):
            print('mul')
            num.value *= value
            tmp = num.value
            sleep(2)
            release(2, q, pn)
        if tmp != num.value:
            print("Process conflict")


def div(num, value, lock, release, q, pn):
    tmp = 0
    while True:
        while lock(3, q, pn):
            print('div')
            num.value /= value
            tmp = num.value
            sleep(3)
            release(3, q, pn)
        if tmp != num.value:
            print("Process conflict")


def Show(num):
    while True:
        sleep(0.5)
        print(num.value)


if __name__ == '__main__':
    queue = Queue(4)
    pnumbers = [0, 0, 0, 0]

    num = Value('d', 0.0)
    arr = Array('i', range(2))
    q = Queue()


    p1 = Process(target=add, args=(num, 10, lock_process, free_process, queue, pnumbers))
    p2 = Process(target=sub, args=(num, 5, lock_process, free_process, queue, pnumbers))
    p3 = Process(target=add, args=(num, 2, lock_process, free_process, queue, pnumbers))
    p4 = Process(target=sub, args=(num, 4, lock_process, free_process, queue, pnumbers))

    show = Process(target=Show, args=(num,))
    show.start()
    sleep(1)
    p1.start()
    p2.start()
    p3.start()
    p4.start()


