import subprocess

def check(expression,result):
    lstArgs = ["./main"] + expression.split(" ")
    out = subprocess.run(args = lstArgs,stdout=subprocess.PIPE,universal_newlines = False)
    if out.stdout != result:
        print('Error: got {1} instead of {0}'.format(result,out.stdout))
    else:
        print('OK')
        
#receiving binary strings from process out.stdout        
print("Start testing:")

check('--mult 23',b'46\n')
check('--elem 0 -1',b'Out of range!\n')
check('--elem 5 5',b'Out of range!\n')
check('--sizes',b'6 4\n')
check('--compare',b'false\n')#comparing m1 and m2
check('--default',b'')#default example from task
check('--mult 23',b'46\n')