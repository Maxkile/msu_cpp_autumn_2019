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

check('123423 23121212 12 --reset 12',b'123423\n!23121212\n123411\n123423\n123411\n')
check('123 2 2 2 2 2 0 122 2 2 --reset 123 --reset',b'123\n121\n119\n117\n115\n113\n113\n!122\n111\n109\n123\n0\n123\n')
check('0 123 21 --reset',b'0\n!123\n!21\n0\n')
check('1 1 1 1 1 1 --reset 1 --reset 1 --reset 1',b'1\n0\n!1\n!1\n!1\n!1\n1\n0\n1\n0\n1\n0\n')
