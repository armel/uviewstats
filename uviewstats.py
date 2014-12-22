import psutil
import serial
import time
import random

# --- constants & variables

PORT = '/dev/tty.usbserial-DA0127FI'
SPEED = 19200

debug = False

history_cpu = []
history_mem = []

suffixes = ['B', 'KB', 'MB', 'GB', 'TB', 'PB']

mem = ['total', 'used', 'free']
disk = ['total', 'used', 'free']
net = ['bytes_sent', 'bytes_recv']

# -- public functions


# ---- send data

def send(data):
    if debug is True:
        if data == '\r':
            print '-----'
        else:
            print data
    else:
        arduino.write(data)


# ---- init

def init():
    values = psutil.cpu_times_percent(interval=1, percpu=True)
    nb = 0
    for core, idle in enumerate(values):
        nb += 1
    values = psutil.virtual_memory()
    send('0')
    send(str(nb) + ',' + format_size(values.total))
    send('\r')


# ---- format size

def format_size(nbytes):
    if nbytes == 0:
        return '0 B'
    i = 0
    while nbytes >= 1024 and i < len(suffixes)-1:
        nbytes /= 1024.
        i += 1
    f = ('%0.1f' % nbytes).rstrip('0').rstrip('.')
    return '%s%s' % (f, suffixes[i])


# ---- history

def history():
    values = psutil.cpu_times_percent(interval=1, percpu=False)
    if len(history_cpu) > 63:
        del history_cpu[0]
    history_cpu.append(str('%02d' % (100 - int(values.idle))))

    values = psutil.virtual_memory()
    if len(history_mem) > 63:
        del history_mem[0]
    history_mem.append(str(values.used / 1024))


# ---- core usage

def core_usage():
    for i in xrange(5):
        values = psutil.cpu_times_percent(interval=1, percpu=True)
        nb = 0
        tmp = []
        for core, idle in enumerate(values):
            nb += 1
            tmp.append(str('%02d' % (100 - int(values[core].idle))))
        tmp.insert(0, str('%02d' % nb))
        send('1')
        send(','.join(tmp))
        send('\r')


# ---- cpu usage

def cpu_usage():
    for i in xrange(5):
        send('2')
        send(','.join(history_cpu))
        send('\r')
        history()


# ---- memory usage

def mem_usage():
    values = psutil.virtual_memory()
    tmp = []
    for index, item in enumerate(mem):
        tmp.append(item[0].upper() +
                   ' ' +
                   '%8s' % format_size(values._asdict()[item]))
    send('3')
    send(','.join(tmp))
    send('\r')


# ---- disk usage

def disk_usage():
    values = psutil.disk_usage('/')
    tmp = []
    for index, item in enumerate(disk):
        tmp.append(item[0].upper() +
                   ' ' +
                   '%8s' % format_size(values._asdict()[item]))
    send('4')
    send(','.join(tmp))
    send('\r')


# ---- net usage

def net_usage():
    values = psutil.net_io_counters(pernic=False)
    tmp = []
    for index, item in enumerate(net):
        tmp.append(item[6].upper() +
                   ' ' +
                   '%8s' % format_size(values._asdict()[item]))
    send('5')
    send(','.join(tmp))
    send('\r')


# ---- connection

if debug is False:
    arduino = serial.Serial(PORT, SPEED, writeTimeout=1)
    time.sleep(2)


# -- main loop

def main():

    init()

    while True:

        history()

        choice = {1: core_usage,
                  2: cpu_usage,
                  3: mem_usage,
                  4: disk_usage,
                  5: net_usage}

        call = choice[random.randint(1, 5)]
        call()

if __name__ == '__main__':
    main()
