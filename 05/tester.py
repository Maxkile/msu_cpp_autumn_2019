import subprocess

def check(expression,result):
    lstArgs = ["./main"] + expression.split(" ")
    out = subprocess.run(args = lstArgs,stdout=subprocess.PIPE,universal_newlines = False)
    if out.stdout != result:
        print('Error: got {1} instead of {0}'.format(result,out.stdout))
    else:
        print('OK')

print("Start testing:")

check('-test',b'')

check('-all 1 0 1',b'')

check('-all 2 1 1',b'')

check('-ser 1 0 1',b'1 false 1 ')

check('-ser 2 -2 2',b'2 true 2 ')

check('-des 0 true 1',b'0 1 1')

check('-des 123 false 23',b'123 0 23')