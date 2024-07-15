import random
# 压缩为 zip 包
import zipfile


def makedata(n):
    return [random.randint(1, 10**9) for _ in range(n)]


def changetoLF(file):
    with open(file, 'rb') as f:
        data = f.read()
    with open(file, 'wb') as f:
        f.write(data.replace(b'\r\n', b'\n'))


def main():
    # 10 个测试点数据
    # 前 3 个测试点 n <= 10**3
    # 接下来 3 个测试点 n <= 10**5
    # 接下来 4 个测试点 n <= 10**6
    # 最后一个测试点几乎有序
    for i in range(3):
        data = makedata(random.randint(1, 10**3))
        # Unix 格式 UTF-8 编码
        with open(f'{i + 1}.in', 'w', encoding='UTF-8') as f:
            f.write(f'{len(data)}\n')
            f.write(' '.join(map(str, data)))
        with open(f'{i + 1}.out', 'w', encoding='UTF-8') as f:
            f.write(' '.join(map(str, sorted(data))) + '\n')

    for i in range(3):
        data = makedata(random.randint(1, 10**5))
        with open(f'{i + 4}.in', 'w', encoding='UTF-8') as f:
            f.write(f'{len(data)}\n')
            f.write(' '.join(map(str, data)))
        with open(f'{i + 4}.out', 'w', encoding='UTF-8') as f:
            f.write(' '.join(map(str, sorted(data))) + '\n')

    for i in range(3):
        data = makedata(random.randint(1, 10**6))
        with open(f'{i + 7}.in', 'w', encoding='UTF-8') as f:
            f.write(f'{len(data)}\n')
            f.write(' '.join(map(str, data)))
        with open(f'{i + 7}.out', 'w', encoding='UTF-8') as f:
            f.write(' '.join(map(str, sorted(data))) + '\n')

    data = sorted(makedata(10**6))
    for i in (random.choice(range(10**6)) for _ in range(10)):
        data[i] = data[i] + random.randint(-10, 10)

    with open(f'10.in', 'w', encoding='UTF-8') as f:
        f.write(f'{len(data)}\n')
        f.write(' '.join(map(str, data)))
    with open(f'10.out', 'w', encoding='UTF-8') as f:
        f.write(' '.join(map(str, data)) + '\n')

    with open('scores.txt', 'w', encoding='UTF-8') as f:
        for i in range(1, 11):
            info = f'{i} 1 '
            if 1 <= i <= 3:
                info += f'#n<=10**3#'
            elif 4 <= i <= 6:
                info += f'#n<=10**5#'
            elif 7 <= i <= 9:
                info += f'#n<=10**6#'
            elif i == 10:
                info += f'#n=10**6#'
            f.write(info + '\n')

    for i in range(10):
        changetoLF(f'{i + 1}.in')
        changetoLF(f'{i + 1}.out')
    changetoLF('scores.txt')

    with zipfile.ZipFile('data.zip', 'w') as z:
        for i in range(10):
            z.write(f'{i + 1}.in')
            z.write(f'{i + 1}.out')
        z.write('scores.txt')


if __name__ == "__main__":
    main()
