from math import sin
from matplotlib import pyplot as plt


def main():
    x = 0
    max_x = 180
    step = 0.5

    x_list, y_list = [], []
    while x <= max_x:
        x_list.append(x)
        y_list.append(y(x))
        x += step

    ax = plt.figure(figsize=(5, 3.5)).gca()
    ax.plot(x_list, y_list)
    ax.set_xlabel('x')
    ax.set_ylabel('F(x)')
    plt.show()


def y(x):
    return 100 * (sin(x / 5.) + sin(x / 3.))


if __name__ == '__main__':
    main()
