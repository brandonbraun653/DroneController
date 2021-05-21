from serial import Serial


def main():
    with Serial('/dev/ttyUSB0', 115200, timeout=0) as ser:
        print('Writing hello world')
        ser.write(b'hello world\n')


if __name__ == '__main__':
    main()
