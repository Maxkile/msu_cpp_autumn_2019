import subprocess

def check(expression,result):
    lstArgs = ["./main"] + expression.split(" ")
    out = subprocess.run(args = lstArgs,stdout=subprocess.PIPE,universal_newlines = False)
    if out.stdout != result:
        print('Error: got {1} instead of {0}'.format(result,out.stdout))
    else:
        print('OK')

print("Start testing:")

check('-n 2 -i -123 - 1231',b'-2585')

check('-i -n 100000 -123 - 123112212',b'-12311221200123')


check('-12345678 - -12345678',b'0')

check('1234567 - 1234567',b'0')

check('-i -n 15 123 - 123',b'-1722')

check('-i -n 14 1722 - 123',b'0')

check('-i -n 14 1722 + 123',b'3444')

check('-i -n 10 987654321 - -1',b'987654331')

check('-n 20 -987654321 + 101',b'-987652301')

check('123445 > -1',b'true')

check('-123445 > -1',b'false')

check('-12344534 >= -12344534',b'true')

check('-12344534 < -12344533',b'true')

check('-2 <= -1',b'true')

check('-203 >= -202',b'false')

check('-123456789 == -987654321',b'false')

check('0 != -0',b'false')