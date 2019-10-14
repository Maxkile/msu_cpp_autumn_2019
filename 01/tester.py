import subprocess

def check(expression,result):
    out = subprocess.run(['./main',expression],stdout=subprocess.PIPE)
    if out.stdout != result:
        print('error {0} != {1}, got {2}'.format(expression,result,out.stdout))
    else:
        print('OK')
        
#receiving binary strings from cpp binary file         
print("Start testing:\n")
check(b'-2/12 + 2332/---2 + 21/-3 - 12',b'-1185.17')
check(b'1213-123/123 + 123-23*123*13 - 123 + 123 - 0 - 1/2',b'-35442.5')
check(b'-1000000000/5/5/5 + 13/1323*0',b'-8000000.0')