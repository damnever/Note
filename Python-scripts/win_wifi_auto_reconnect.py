# -*- coding: utf-8 -*-

from __future__ import print_function

import os
import sys
import time
import subprocess
import datetime


# Maybe: make the script as a Windows service.
# Maybe: log module is a good choice.

PING_SITES = ['www.baidu.com', 'www.qq.com']
FNULL = open(os.devnull, 'w')


def loop_forever(wifi_name, wait_time=30):
    now = datetime.datetime.now
    while 1:
        if is_reachable():
            print('[{:%H:%M:%S}] WIFI connection ok for now ...'.format(now()))
            time.sleep(wait_time)
        else:
            print('[{:%H:%M:%S}] Lost WIFI connection ...'.format(now()), end='')
            subprocess.call(['netsh', 'wlan', 'disconnect'])
            print('[{:%H:%M:%S}] Reconnect WIFI ...'.format(now()))
            subprocess.call(
                ['netsh', 'wlan', 'connect', 'name={}'.format(wifi_name)])
            # Frequent connection is not good, wait 5 seconds.
            time.sleep(5)

def is_reachable():
    for site in PING_SITES:
        # Does not display ping informations.
        retcode = subprocess.call(['ping', site], stdout=FNULL)
        if retcode == 0:
            return True
    return False if retcode else True


if __name__ == '__main__':
    wifi_name, wait_time = '', 30
    args = len(sys.argv)
    if args == 3:
        wifi_name = str(sys.argv[1])
        wait_time = int(sys.argv[2])
    elif args == 2:
        wifi_name = str(sys.argv[1])
    else:
        print("WIFI name is required, waiting time is optional!")
        exit()
    try:
        print("Please don't say love ...")
        loop_forever(wifi_name, wait_time)
    except KeyboardInterrupt:
        print("Stoping ...")
