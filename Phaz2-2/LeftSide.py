
from multiprocessing import Process, Queue, Value,Array
from time import sleep
from Car import Car

def producer(queue, id,):
    print('Producer: Running', flush=True)
    while True:
        value = Car(id.value)
        queue.put(value)
        id.value += 1
        sleep(value.time)


def consumer(queue, street):
    print('Consumer: Running', flush=True)
    while True:
        item = queue.get()     
        street.value = item.id
        print('car id: ', item.id, 'sleep: ', item.time)
        temp = street.value
        if temp != street.value:
            print('Process conflict!')
        sleep(item.time)
