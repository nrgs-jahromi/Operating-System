from multiprocessing import  Process, Queue, Value,Array
from time import sleep
from Car import Car
import threading

mutex = threading.Semaphore()
empty = threading.Semaphore(10)
full = threading.Semaphore(0)

def producer(queue, id):
    print('Producer: Running', flush=True)
    while True:
        empty.acquire()
        mutex.acquire()
        value = Car(id.value)
        id.value += 1
        queue.put(value)
        mutex.release()
        full.release()
        sleep(value.time)


def consumer(queue, street):
    print('Consumer: Running', flush=True)
    while True:
        full.acquire()
        mutex.acquire()
        item = queue.get()     
        street.value = item.id
        print('car id: ', item.id, 'sleep: ', item.time)
        temp = street.value
        mutex.release()
        empty.release()
        if temp != street.value:
            print('Process conflict!')
        sleep(item.time)
   

