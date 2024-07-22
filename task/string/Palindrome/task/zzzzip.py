import zipfile

# 读取当前目录下的 *.in *.out scores.txt 文件
# 写入 data.zip
def zip_files(first, last):
    with zipfile.ZipFile('data.zip', 'w') as z:
        z.write('scores.txt')
        for i in range(first, last):
            for ext in ['in', 'out']:
                z.write(f'{i}.{ext}')


if __name__ == '__main__':
    zip_files(0, 10)
